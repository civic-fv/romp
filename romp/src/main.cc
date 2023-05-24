#include "../../common/help.h"
#include "generate.hpp"
#include "check.h"
#include "NestedError.hpp"
#include "CodeGenerator.hpp"
// #include "generate_h.h"
// #include "options.h"
#include "resources.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <memory>
#include <murphi/murphi.h>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <utility>
#include <vector>
#include <regex>
#include <algorithm>
#include <optional>

// a pair of input streams
using dup_t =
    std::pair<std::shared_ptr<std::istream>, std::shared_ptr<std::istream>>;

static std::string in_filename = "<stdin>";
static dup_t in;
static std::shared_ptr<std::ofstream> out;

// output C source? (as opposed to C header)
// static bool source = true;

std::filesystem::path make_path(std::string p) {
  std::filesystem::path _p = p;
  if (_p.is_relative())
    return std::filesystem::absolute(_p);
    return _p;
}

void parse_args(romp::CodeGenerator& gen, int argc, char **argv) {
  bool out_file_provided = false;
  // unsigned int hist_len = ROMP_HISTORY_SIZE_PREPROCESSOR_VAR_DEFAULT_VALUE;
  for (;;) {
    static struct option options[] = {
        // clang-format off
        { "help",               no_argument,        0,  'h' },
        { "output",             required_argument,  0,  'o' },
        { "rule-history-len",   required_argument,  0,  'r' },
        { "selection-algo",     required_argument,  0,  's' },
        { "enable-assume",      no_argument,        0,  'a' },
        { "enable-cover",       no_argument,        0,  'c' },
        { "enable-liveness",    no_argument,        0,  'l' },
        { "ignore-rumur-props", no_argument,        0,  'i' },
        // { "header",             no_argument,       0, 128 },
        // { "source",             no_argument,       0, 129 },
        // { "scalar-type",        required_argument,  0,  130 },
        { "range-type",         required_argument,  0,  'R' },
        { "version",            no_argument,        0,  'v' },
        { "do-measure",         no_argument,        0,  'm' },
        { "simple-trace-rep",   no_argument,        0,  'S' },
        { "default-walk-multiplier",   required_argument,        0,  'w' },
        { "default-bfs-coefficient",   required_argument,        0,  'b' },
        { 0, 0, 0, 0 },
        // clang-format on
    };

    int option_index = 0;
    int c = getopt_long(argc, argv, "ho:r:s:acliR:vmSw:b:", options, &option_index);

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
      auto o = std::make_shared<std::ofstream>(optarg,std::ios::out);
      if (!o->is_open()) {
        std::cerr << "failed to open " << optarg << "\n";
        exit(EXIT_FAILURE);
      }
      gen.set_out(o);
      // out = o;
      gen.output_file_path = make_path(optarg);
      out_file_provided = true;
      break;
    }

    case 'r': // --rule-history-length <size>
      try {
        gen.hist_len = std::stoul(optarg, nullptr, 0);
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

    case 's': // --selection-algo
      try {
        gen.selection_algo = std::stoul(optarg, nullptr, 0);
      } catch (std::invalid_argument &ia) {
        std::cerr << "invalid argument : provided selection algorithm value was not a number (NaN) !! (for -s/--selection-algo flag)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      } catch (std::out_of_range &oor) {
        std::cerr << "invalid argument : provided selection algorithm value was out of range !! (for -s/--selection-algo flag)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
      if (gen.selection_algo > ROMP_RULE_SELECTION_ALGO_LIMIT) {
        std::cerr << "invalid argument : provided selection algorithm value was out of range !! [0," << ROMP_RULE_SELECTION_ALGO_LIMIT << "] (for -s/--selection-algo flag)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
      break;

    case 'a': // --enable-assume
      gen.enable_assume_property();
      break;

    case 'c': // --enable-cover
      gen.enable_cover_property();
      break;

    case 'l': // --enable-liveness
      gen.enable_liveness_property();
      break;

    case 'i': // --enable-liveness
      gen.disable_romp_prop_errors();
      break;

    case 'w': // --default-walk-multiplier <uint:size>
      try {
        gen.default_walk_multiplier = std::stoul(optarg, nullptr, 0);
      } catch (std::invalid_argument &ia) {
        std::cerr << "invalid argument : provided default walk multiplier value was not a number (NaN) !! (for -w/--default-wal-multiplier flag)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      } catch (std::out_of_range &oor) {
        std::cerr << "invalid argument : provided default walk multiplier value was out of range (pos ints only) !! (for -w/--default-wal-multiplier flag)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
      break;
    case 'b': // --default-bfs-coefficient <uint:size>
      try {
        gen.default_bfs_coefficient = std::stoul(optarg, nullptr, 0);
      } catch (std::invalid_argument &ia) {
        std::cerr << "invalid argument : provided default bfs coefficient value was not a number (NaN) !! (for -w/--default-wal-multiplier flag)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      } catch (std::out_of_range &oor) {
        std::cerr << "invalid argument : provided default bfs coefficient value was out of range (pos ints only) !! (for -w/--default-wal-multiplier flag)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
      break;

    case 'm': // --do-measure
      gen.enable_preprocessor_option(ROMP_MEASURE_PREPROCESSOR_VAR);
      break;

    case 'S': // --simple-trace-rep
      gen.enable_preprocessor_option(ROMP_SIMPLE_TRACE_PREPROCESSOR_VAR);
      break;

    // case 128: // --header
    //   source = false;
    //   break;

    // case 130: // --scalar-type
    //   gen.scalar_type = optarg;
    //   break;

    case 'R': // --range-type
      // note that we just assume the type the user gave us exists
      gen.value_type = optarg;
      break;

    case 'v': // --version
      std::cout << "ROMP version " ROMP_VERSION "\n"
                   "libmurphi version " << murphi::get_version() << "\n";
      exit(EXIT_SUCCESS);

    default:
      std::cerr << "unexpected error\n";
      exit(EXIT_FAILURE);
    }
  }

  if (optind == argc - 1) {
    struct stat buf;
    if (stat(argv[optind], &buf) < 0) {
      std::cerr << "failed to open \"" << argv[optind] << "\": " << strerror(errno)
                << std::endl;
      exit(EXIT_FAILURE);
    }

    if (S_ISDIR(buf.st_mode)) {
      std::cerr << "failed to open \"" << argv[optind]
                << "\": this is a directory\n"
                << std::flush;
      exit(EXIT_FAILURE);
    }

    gen.input_file_path = make_path(argv[optind]);

    auto i = std::make_shared<std::ifstream>(gen.input_file_path);
    auto j = std::make_shared<std::ifstream>(gen.input_file_path);
    if (!i->is_open() || !j->is_open()) {
      std::cerr << "failed to open \"" << gen.input_file_path << "\"\n" << std::flush;
      exit(EXIT_FAILURE);
    }
    in = dup_t(i, j);
  }
  if (not out_file_provided) {
    gen.output_file_path = gen.input_file_path;
    gen.output_file_path.replace_extension(".romp.cpp");
    auto o = std::make_shared<std::ofstream>(gen.output_file_path);
    if (!o->is_open()) {
      std::cerr << "failed to open \"" << gen.output_file_path << "\"\n"  << std::flush;
      exit(EXIT_FAILURE);
    }
    out = o;
    gen.set_out(o);
  }
  // gen.enable_preprocessor_option(
  //     ROMP_HISTORY_SIZE_PREPROCESSOR_VAR " (" + std::to_string(gen.hist_len) + "ul)"
  //   );
  if (gen.default_walk_multiplier == 0) {
    gen.default_walk_multiplier = 1u;
    std::cerr << "WARNING : `0` is an invalid value for default walk multiplier, `1` will used instead !! (for -w/--default-wal-multiplier flag)\n" 
              << std::flush;
  }
  
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

std::string _to_lower(const std::string& data) {
  std::string result;
  std::transform(data.begin(), data.end(), result.begin(),
    [](unsigned char c){ return std::tolower(c); });
  return result;
}

int main(int argc, char **argv) {

  romp::CodeGenerator gen;
  // parse command line options
  parse_args(gen, argc, argv);

  // if we are reading from stdin, duplicate it so that we can parse it both as
  // Murphi and for comments
  if (in.first == nullptr)
    in = make_stdin_dup();

  // parse input model
  murphi::Ptr<murphi::Model> m;
  std::regex bad_name_regex("_+[Rr][Oo][Mm][Pp]_+.*");
  try {
    m = murphi::parse(*in.first, [&](const std::string& name, auto type, auto loc) -> std::optional<std::string> {
                        if (std::regex_search(name, bad_name_regex))
                          throw murphi::Error("name/id (`"+name+"`) starts with the protected romp key phrase "
                                              "(regex:/_+[Rr][Oo][Mm][Pp]_+.*/)",loc);
                        if (name == "romp")
                          throw murphi::Error("name/id (`romp`) is a reserved word",loc);
                        // if (name == "")
                        //   throw murphi::Error("name/id (`romp`) is a reserved word",loc);
                        std::string name_lower = _to_lower(name);
                        auto res = gen.RESERVED_NAMES.find(name_lower);
                        if (res != gen.RESERVED_NAMES.end())
                          throw murphi::Error("name/id `"+name+"` is a reserved word",loc);
                        return {name};
                      });
  } catch (murphi::Error &e) {
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
    murphi::updateAST(*m);
    validate(*m);
    check(*m);
  } catch (const murphi::Error& e) {
    std::cerr << e << "\n";
    // std::cerr << e.loc << ":" << e.what() << "\n";
    return EXIT_FAILURE;
  } catch (const std::exception& ex) {
    std::cerr << "\n[[DEV ERROR : BEGIN]]\n"
              << ex << "\n"
              << "[[DEV ERROR : END]]\n";
    return EXIT_FAILURE;
  }

  // name any rules that are unnamed, so they get valid C++ symbols
  murphi::sanitize_rule_names(*m);

  // Determine if we have any == or != involving records or arrays, in which
  // case we will need to pack structs. See generate_c() for why.
  // bool pack = compares_complex_values(*m);

  // parse comments from the source code
  std::vector<murphi::Comment> comments = murphi::parse_comments(*in.second);

  try {
  // output code
  // if (source) {
    // in_filename = trim(in_filename);
    // auto start = ((in_filename[0]=='"') ? ++(in_filename.begin()) : in_filename.begin() );
    // auto stop = ((in_filename[in_filename.size()-1]=='"') ? --(in_filename.end()) : in_filename.end() );
    // file_path = std::string(start,stop);
    generate(*m, comments, gen, "<not-implemented-yet>");
  // } else {
  //   generate_h(*m, comments, pack, out == nullptr ? std::cout : *out);
  // }
  } catch (const murphi::Error& e) {
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
