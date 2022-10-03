#include "../../common/help.h"
#include "check.h"
#include "compares_complex_values.h"
#include "generate_c.hpp"
#include "NestedError.hpp"
#include "CodeGenerator.hpp"
// #include "generate_h.h"
#include "options.h"
#include "resources.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <memory>
#include <rumur/rumur.h>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <utility>
#include <vector>

// a pair of input streams
using dup_t =
    std::pair<std::shared_ptr<std::istream>, std::shared_ptr<std::istream>>;

static std::string in_filename = "<stdin>";
static dup_t in;
static std::shared_ptr<std::ostream> out;

// output C source? (as opposed to C header)
// static bool source = true;

std::filesystem::path make_path(std::string p) {
  std::filesystem::path _p = p;
  if (_p.is_relative())
    return std::filesystem::absolute(_p);
    return _p;
}

static void parse_args(int argc, char **argv) {
  bool no_sym_provided = false;
  unsigned int hist_len = ROMP_HISTORY_SIZE_PREPROCESSOR_VAR_DEFAULT_VALUE;
  for (;;) {
    static struct option options[] = {
        // clang-format off
        { "help",               no_argument,        0,  'h' },
        { "output",             required_argument,  0,  'o' },
        { "rule-history-len",   required_argument,  0,  'r' },
        { "no-symmetry",        no_argument,        0,  's' },
        { "enable-assume",      no_argument,        0,  'a' },
        { "enable-cover",       no_argument,        0,  'c' },
        { "enable-liveness",    no_argument,        0,  'l' },
        { "ignore-rumur-props", no_argument,        0,  'i' },
        // { "header",             no_argument,       0, 128 },
        // { "source",             no_argument,       0, 129 },
        { "value-type",         required_argument,  0,  130 },
        { "version",            no_argument,        0,  131 },
        { "do-measure",         no_argument,        0,  132 },
        { "simple-trace-rep",   no_argument,        0,  133 },
        { 0, 0, 0, 0 },
        // clang-format on
    };

    int option_index = 0;
    int c = getopt_long(argc, argv, "ho:sacl", options, &option_index);

    if (c == -1)
      break;

    switch (c) {

    case '?':
      std::cerr << "run `" << argv[0] << " --help` to see available options\n";
      exit(EXIT_SUCCESS);

    case 'h': // --help
      help(doc_romp_1, doc_romp_1_len);
      exit(EXIT_SUCCESS);

    case 'o': { // --output
      auto o = std::make_shared<std::ofstream>(optarg);
      if (!o->is_open()) {
        std::cerr << "failed to open " << optarg << "\n";
        exit(EXIT_FAILURE);
      }
      out = o;
      romp::CodeGenerator::output_file_path = make_path(optarg);
      break;
    }

    case 'r': // --rule-history-length <size>
      try {
        hist_len = std::stoul(optarg, nullptr, 0);
      } catch (std::invalid_argument &ia) {
        std::cerr << "invalid argument : provided rule history length value was not a number (NaN) !! (for -r/--rule-history-len flag)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      } catch (std::out_of_range &oor) {
        std::cerr << "invalid argument : provided rule history length value was out of range !! (for -r/--rule-history-len flag)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
      break;

    case 's': // --no-symmetry
      no_sym_provided = true;
      break;

    case 'a': // --enable-assume
      romp::CodeGenerator::enable_assume_property();
      break;

    case 'c': // --enable-cover
      romp::CodeGenerator::enable_cover_property();
      break;

    case 'l': // --enable-liveness
      romp::CodeGenerator::enable_liveness_property();
      break;

    case 'i': // --enable-liveness
      romp::CodeGenerator::disable_romp_prop_errors();
      break;

    case 132: // --do-measure
      romp::CodeGenerator::enable_preprocessor_option(ROMP_MEASURE_PREPROCESSOR_VAR);
      break;

    case 133: // --simple-trace-rep
      romp::CodeGenerator::enable_preprocessor_option(ROMP_SIMPLE_TRACE_PREPROCESSOR_VAR);
      break;

    // case 128: // --header
    //   source = false;
    //   break;

    // case 129: // --source
    //   source = true;
    //   break;

    case 130: // --value-type
      // note that we just assume the type the user gave us exists
      value_type = optarg;
      break;

    case 131: // --version
      std::cout << "ROMP version " ROMP_VERSION "\n"
                   "Rumur version " << rumur::get_version() << "\n";
      exit(EXIT_SUCCESS);

    default:
      std::cerr << "unexpected error\n";
      exit(EXIT_FAILURE);
    }
  }

  if (optind == argc - 1) {
    struct stat buf;
    if (stat(argv[optind], &buf) < 0) {
      std::cerr << "failed to open " << argv[optind] << ": " << strerror(errno)
                << "\n";
      exit(EXIT_FAILURE);
    }

    if (S_ISDIR(buf.st_mode)) {
      std::cerr << "failed to open " << argv[optind]
                << ": this is a directory\n";
      exit(EXIT_FAILURE);
    }

    in_filename = argv[optind];

    auto i = std::make_shared<std::ifstream>(in_filename);
    auto j = std::make_shared<std::ifstream>(in_filename);
    if (!i->is_open() || !j->is_open()) {
      std::cerr << "failed to open " << in_filename << "\n";
      exit(EXIT_FAILURE);
    }
    in = dup_t(i, j);
    romp::CodeGenerator::input_file_path = make_path(in_filename);
  }
  if (out == nullptr) {
    auto o = std::make_shared<std::ofstream>(in_filename + ".romp.cpp");
    if (!o->is_open()) {
      std::cerr << "failed to open " << in_filename << ".romp.cpp\n";
      exit(EXIT_FAILURE);
    }
    out = o;
    romp::CodeGenerator::output_file_path = make_path(in_filename + ".romp.cpp");
  }
  romp::CodeGenerator::enable_preprocessor_option(
      ROMP_HISTORY_SIZE_PREPROCESSOR_VAR " (" + std::to_string(hist_len) + "ul)"
    );
  if (not no_sym_provided)
    romp::CodeGenerator::enable_preprocessor_option(ROMP_SYMMETRY_PREPROCESSOR_VAR);
}

static dup_t make_stdin_dup() {

  // read stdin into memory
  auto buffer = std::make_shared<std::stringstream>();
  *buffer << std::cin.rdbuf();

  // duplicate the buffer
  auto copy = std::make_shared<std::istringstream>(buffer->str());

  return dup_t(buffer, copy);
}

std::string trim(const std::string &s)
{
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        start++;
    }
 
    auto end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
 
    return std::string(start, end + 1);
}

int main(int argc, char **argv) {

  // parse command line options
  parse_args(argc, argv);

  // if we are reading from stdin, duplicate it so that we can parse it both as
  // Murphi and for comments
  if (in.first == nullptr)
    in = make_stdin_dup();

  // parse input model
  rumur::Ptr<rumur::Model> m;
  try {
    m = rumur::parse(*in.first);
  } catch (rumur::Error &e) {
    romp::fprint_exception(std::cerr, e);
    // std::cerr << e.loc << ":" << e.what() << "\n";
    return EXIT_FAILURE;
  } catch (std::exception& ex) {
    std::cerr << "[[DEV ERROR : BEGIN]]\n";
    romp::fprint_exception(std::cerr, ex);
    std::cerr << "[[DEV ERROR : END]]\n";
    return EXIT_FAILURE;
  }

  assert(m != nullptr);

  // update unique identifiers within the model
  m->reindex();

  // check the model is valid
  try {
    resolve_symbols(*m);
    validate(*m);
  } catch (const rumur::Error& e) {
    std::cerr << e << "\n";
    // std::cerr << e.loc << ":" << e.what() << "\n";
    return EXIT_FAILURE;
  } catch (const std::exception& ex) {
    std::cerr << "\n[[DEV ERROR : BEGIN]]\n"
              << ex << "\n"
              << "[[DEV ERROR : END]]\n";
    return EXIT_FAILURE;
  }

  // validate that this model is OK to translate
  if (!check(*m))
    return EXIT_FAILURE;

  // name any rules that are unnamed, so they get valid C symbols
  rumur::sanitise_rule_names(*m);

  // Determine if we have any == or != involving records or arrays, in which
  // case we will need to pack structs. See generate_c() for why.
  bool pack = compares_complex_values(*m);

  // parse comments from the source code
  std::vector<rumur::Comment> comments = rumur::parse_comments(*in.second);

  try {
  // output code
  // if (source) {
    // in_filename = trim(in_filename);
    // auto start = ((in_filename[0]=='"') ? ++(in_filename.begin()) : in_filename.begin() );
    // auto stop = ((in_filename[in_filename.size()-1]=='"') ? --(in_filename.end()) : in_filename.end() );
    // file_path = std::string(start,stop);
    generate_c(*m, comments, pack, (out == nullptr) ? std::cout : *out, "<not-implemented-yet>");
  // } else {
  //   generate_h(*m, comments, pack, out == nullptr ? std::cout : *out);
  // }
  } catch (const rumur::Error& e) {
    std::cerr << e << "\n";
    // std::cerr << e.loc << ":" << e.what() << "\n";
    return EXIT_FAILURE;
  } catch (const std::exception& ex) {
    std::cerr << "[[DEV ERROR : BEGIN]]\n"
              << ex << "\n"
              << "[[DEV ERROR : END]]\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
