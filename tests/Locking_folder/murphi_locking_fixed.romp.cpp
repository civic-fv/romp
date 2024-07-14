/*
	Generated code for a romp "parallel random walker" verification tool based off of the Murphi Model described in:
		Original Murphi Model: murphi_locking_fixed.m
	Please build with the following command(s):
		<not-implemented-yet>
*/


#define __romp__GENERATED_CODE


#define _ROMP_STATE_TYPE ::__model__::__romp__Model__


#define _ROMP_HIST_LEN (4ul)


#define _ROMP_THREAD_TO_RW_RATIO (16ul)


#define _ROMP_BFS_COEF (16ul)


#define __model__filepath "/home/ajantha/Desktop/Repos/romp/tests/Locking_folder/murphi_locking_fixed.m"


#define __model__filepath_contains_space (false)


#define __model__filename "murphi_locking_fixed.m"

#define __model__filename_contains_space (false)

namespace romp {
  typedef int range_t;
} // namespace romp


#define __romp__ENABLE_symmetry
namespace __model__ { struct __romp__Model__; } // helpful pre-definition


#pragma region romp_prefix

/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw/include.hpp
 *
 * @brief the includes needed for the generated model checker
 *
 * @date 2022/10/05
 * @version 0.2
 */

#ifndef __romp__GENERATED_CODE
#pragma once  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif

// #include <assert.h>
// #include <stdbool.h>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <iomanip>
// #include <stdlib.h>
#include <string>
#include <cstring>  // required for memset
#include <fstream>
#include <sstream>
#include <tuple>
#include <exception>
#include <vector>
#include <queue>
#include <memory>
#include <utility>
#include <functional>
#include <type_traits>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <ctime>

#ifndef __romp__GENERATED_CODE
#include "pregen-fix.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif


#ifdef __clang__
using nullptr_t=std::nullptr_t;
#endif

/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file decl.hpp
 *
 * @brief the General Declarations for the romp random walker generated model checker
 *
 * @date 2022/10/05
 * @version 0.2
 */




// << =============================== Preprocessor Declarations ================================ >>

#ifndef __romp__GENERATED_CODE  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#pragma once  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "pregen-fix.hpp"  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "include.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!


#define _ROMP_TRACE_JSON_VERSION "0.0.4"
#ifdef DEBUG
#define _ROMP_FLUSH_FREQ (32ul)
#else
#define _ROMP_FLUSH_FREQ (64ul)
#endif


// wrappers for producing literal expressions of value type
// legacy form rumur's design patterns (updated to new names)
#define VALUE_C(v) ((romp::range_t)(v))
#define SCALAR_C(v) ((romp::scalar_t)(v))

// << =================================== Useful Pre-decls ===================================== >>
namespace romp {
  struct TypeInfo; struct RuleInfo; struct PropertyInfo; struct StartStateInfo; struct MErrorInfo; struct FunctInfo;
  struct RuleSet; struct StartState; struct Property;
  class stream_void { nullptr_t none = nullptr; };
  const stream_void S_VOID;
  std::ostream& operator << (std::ostream& out, const stream_void& val) { return out; }
  class ostream_p;
  template <class O> class ojstream;
  struct Options;
  struct IModelError;
}

namespace __caller__ {
  extern const ::romp::RuleSet RULESETS[];
  extern const ::romp::StartState STARTSTATES[];
  extern const ::romp::Property PROPERTIES[];
} // namespace __caller__

namespace __info__ {
  extern const std::string TYPE_IDS[];
  extern const std::string RECORD_FIELD_LABELS[];
  // extern const ::romp::TypeInfo TYPE_INFOS[];
  extern const ::romp::RuleInfo RULE_SET_INFOS[];
  extern const ::romp::PropertyInfo PROPERTY_INFOS[];
  extern const ::romp::StartStateInfo STARTSTATE_INFOS[];
  extern const ::romp::MErrorInfo ERROR_INFOS[];
  extern const ::romp::FunctInfo FUNCT_INFOS[];
} // namespace __info__

// << ========================================================================================== >>
// <<                                           DECL                                             >>
// << ========================================================================================== >>

namespace romp {

  using duration_ms_t = std::chrono::duration<long double,std::milli>;
  using time_ms_t = std::chrono::time_point<std::chrono::high_resolution_clock,std::chrono::duration<long double,std::milli>>;

  // using duration_ms_t = std::chrono::duration<long long,std::milli>;
  // using time_ms_t = std::chrono::time_point<std::chrono::high_resolution_clock,std::chrono::duration<long long,std::milli>>;

  using duration_msf_t = std::chrono::duration<long double,std::milli>;

  time_ms_t time_ms() {
    return std::chrono::time_point_cast<duration_ms_t>(std::chrono::high_resolution_clock::now());
  }

  using duration_mr_t = std::chrono::duration<long long,std::chrono::high_resolution_clock::period>;
  using time_mr_t = std::chrono::time_point<std::chrono::high_resolution_clock,std::chrono::duration<long long,std::chrono::high_resolution_clock::period>>;

  time_mr_t time_mr() {
    return std::chrono::time_point_cast<duration_mr_t>(std::chrono::high_resolution_clock::now());
  }

  const std::string EMPTY_STR = "";
  const time_t ROMP_ID = std::time(nullptr);
  const auto INIT_TIME = *std::localtime(&ROMP_ID);
  const auto INIT_TIME_STAMP = std::put_time(&INIT_TIME, "%F_%T");


  typedef _ROMP_STATE_TYPE State_t;
  typedef unsigned int RandSeed_t;

  struct file_position {
    size_t row;
    size_t col;
    friend inline bool operator < (const file_position& l, const file_position& r) { return (l.row < r.row) || (l.col < r.col); }
    friend inline bool operator <= (const file_position& l, const file_position& r) { return (l.row <= r.row) || (l.col <= r.col); }
    friend inline bool operator == (const file_position& l, const file_position& r) { return (l.row == r.row) && (l.col == r.col); }
    friend inline bool operator != (const file_position& l, const file_position& r) { return (l.row != r.row) || (l.col != r.col); }
    friend inline bool operator > (const file_position& l, const file_position& r) { return (l.row > r.row) || (l.col > r.col); }
    friend inline bool operator >= (const file_position& l, const file_position& r) { return (l.row >= r.row) || (l.col >= r.col); }
  };

  struct location {
    // std::string model_obj;
    file_position start;
    file_position end;
    // friend bool operator < (const location& l, const location& r) { return (l.end < r.end) && (l.start <= r.start); }
    // friend bool operator <= (const location& l, const location& r) { return (l.end <= r.end) && (l.start <= r.start); }
    friend bool operator == (const location& l, const location& r) { return (l.start == r.start) && (l.end == r.end); }
    friend bool operator != (const location& l, const location& r) { return (l.start != r.start) || (l.end != r.end); }
    // friend bool operator > (const location& l, const location& r) { return (l.start > r.start) && (l.end >= r.end); }
    // friend bool operator >= (const location& l, const location& r) { return (l.start >= r.start) && (l.end >= r.end); }
  };

  // enum TypeType { BOOLEAN, RANGE, ENUM, SCALARSET, SCALARSET_UNION, ARRAY, MULTISET, RECORD, RECORD_MEMBER, TYPE_EXPR_ID };

  // struct TypeInfo {
  //   std::string label;
  //   TypeType type;
  //   std::string repr;
  //   location loc;
  //   std::vector<id_t> dependents;
  // };


  enum PropertyType { INVARIANT, ASSERTION, ASSUMPTION, COVER, LIVENESS };

  struct PropertyInfo {
    std::string label;
    PropertyType type;
    std::string expr;
    // size_t prop_id;
    id_t id;
    location loc;
    std::string json_h; // missing closing '}' so you can insert other fields if necessary
    IModelError* make_error() const;
  };

   struct Property {
    bool (*check)(const State_t&) ;
    const PropertyInfo& info;
    const std::string quant_json;
    const std::string quant_str;
    IModelError* make_error() const;
  };


  struct RuleInfo {
    std::string label;
    location loc;
    std::string json_h;
    IModelError* make_error() const;
  };

  struct Rule {
    bool (*guard)(const State_t&) ;
    void (*action)(State_t&) ;
    const RuleInfo& info;
    const std::string quant_json;
    const std::string quant_str;
    IModelError* make_error() const;
  };

  struct RuleSet {
    const RuleInfo& info;
    std::vector<Rule> rules;
    IModelError* make_error() const;
  };


  struct StartStateInfo {
    const std::string label;
    const location loc;
    const std::string json_h;
    IModelError* make_error() const;
  };

  struct StartState {
    void (*initialize)(State_t&) ;
    const StartStateInfo& info;
    const id_t id;
    const std::string quant_json;
    const std::string quant_str;
    IModelError* make_error() const;
  };


  struct MErrorInfo {
    const std::string label;
    location loc;
    // bool isFunct;
    const std::string json;
  };


  struct FunctInfo {
    const std::string label;
    location loc;
    const std::string json;
    const std::string signature;
  };


  /**
   * @brief Abstract parent of The Random Walker that the model will hold a reference to
   *        in order to bea ble to call it for various handlers
   */
  struct IRandWalker {
    /**
     * @brief the handler the model will call when it reaches an inline `assert`/`invariant` statement
     * @param eval_expr the expression to be evaluated (technically it will be evaluated before reaching this)
     * @param prop_id the id given to the property (value based upon the order it was processed by the code gen tool)
     * @return \c bool - the negation of whether or not the model calling this function should return an error or not.  ( \c true = DO throw, \c false = do NOT throw)
     */
    virtual bool assertion_handler(bool eval_expr, id_t prop_id) = 0;
    /**
     * @brief the handler the model will call when it reaches a global rule `assert`/`invariant`
     * @param eval_expr the expression to be evaluated (technically it will be evaluated before reaching this)
     * @param prop_id the id given to the property (value based upon the order it was processed by the code gen tool)
     * @return \c bool - the negation of whether or not the caller should report an error. ( \c true = DO throw, \c false = do NOT throw)
     */
    virtual bool invariant_handler(bool eval_expr, id_t prop_id) = 0;
    /**
     * @brief the handler the model will call when it reaches an `assumption` statement
     * @param eval_expr the expression to be evaluated (technically it will be evaluated before reaching this)
     * @param prop_id the id given to the property (value based upon the order it was processed by the code gen tool)
     * @return \c bool - whether or not the caller should report an error. ( \c true = DO throw, \c false = do NOT throw)
     */
    virtual bool assumption_handler(bool eval_expr, id_t prop_id) = 0;
    /**
     * @brief the handler the model will call when a `cover` statement is reached
     * @param eval_expr the expression to be evaluated (technically it will be evaluated before reaching this)
     * @param cover_id the id given to this specific `cover` statement (value based upon the order it was processed by the code gen tool)
     * @param prop_id the id given to the property (value based upon the order it was processed by the code gen tool)
     * @return \c bool - the negation of whether or not the caller should report an error. ( \c true = DO throw, \c false = do NOT throw)
     */
    virtual bool cover_handler(bool eval_expr, id_t cover_id, id_t prop_id) = 0;
    /**
     * @brief the handler the model will call when a `liveness` statement is reached
     * @param eval_expr the expression to be evaluated (technically it will be evaluated before reaching this)
     * @param liveness_id the id given to this specific `liveness` statement (value based upon the order it was processed by the code gen tool)
     * @param prop_id the id given to the property (value based upon the order it was processed by the code gen tool)
     * @return \c bool - the negation of whether or not the caller should report an error. ( \c true = DO throw, \c false = do NOT throw)
     */
    virtual bool liveness_handler(bool eval_expr, id_t liveness_id, id_t prop_id) = 0;
    /**
     * @brief the handler the model will call it reaches an `error` statement
     * @param error_id the id given to the error statement (value based upon the order it was processed by the code gen tool)
     * @return \c bool - the negation of whether or not the caller should report an error. ( \c true = DO throw, \c false = do NOT throw)
     */
    virtual bool error_handler(id_t error_id) = 0;
    /**
     * @brief A handler to use to select a random number between [0, \c occupancy ) to use for choose rules.
     * @param occupancy the current occupancy of the calling multiset
     * @param location the location of the choose rule's MultisetQualifier decl
     * @return \c size_t - the index in the multiset that has been choosen
     */
    // virtual size_t choose_handler(size_t occupancy, const location& loc) = 0;
    /**
     * @brief A handler for determining where and how things should be printed
     * @param put_action - a function that will perform the writing.
     * @param location the location of the put statement
     */
    virtual void put_handler(const std::function<void(ostream_p&)>& put_action, const location& loc) = 0;
  };

  struct Result {
    enum Cause {
        NO_CAUSE=0,
        RUNNING=0,
        UNKNOWN_CAUSE,
        ATTEMPT_LIMIT_REACHED,
        MAX_DEPTH_REACHED,
        PROPERTY_VIOLATED,
#ifdef __romp__ENABLE_cover_property
        COVER_COMPLETE,
#endif
#ifdef __romp__ENABLE_assume_property
        ASSUMPTION_VIOLATED,
#endif
        MERROR_REACHED
    };
    id_t id; // RandWalker id
    id_t root_seed; // the root seed of the RW
    id_t start_id; // id of start state
    Cause cause;  // the kind of cause that stoped the Rand Walker
    size_t depth; // depth reached
    const IModelError* tripped;  // what was tripped (promised not nested)
    const IModelError* inside;  // where it was tripped (could be nested w/ root cause)
#ifdef __ROMP__DO_MEASURE
    using duration_ms_t = std::chrono::duration<long double,std::milli>;
    using duration_mr_t = std::chrono::duration<long long,std::chrono::high_resolution_clock::period>;
    duration_mr_t active_time;
    duration_ms_t total_time;
#endif
    // Result(Result& old)
    //   : id(old.id), root_seed(old.root_seed), start_id(old.start_id),
    //     cause(old.cause), depth(old.depth),
    //     tripped(old.tripped), inside(old.inside)
    // { old.tripped = nullptr; old.inside = nullptr; }
    ~Result(); // { if (tripped != nullptr) delete tripped; if (inside != nullptr) delete inside; }
  };

} // namespace romp

namespace std {
  template<>
  struct hash<romp::location> {
    size_t operator () (const romp::location& loc) const {
      return (loc.start.row + loc.start.col + loc.end.row + loc.end.col) % UINT64_MAX;
    }
  };
  // template<>
  // class hash<romp::ModelPropertyError> {
  //   public: size_t operator () (const romp::ModelPropertyError& me) const { return me.hash(); }
  // };
  // template<>
  // class equal_to<romp::ModelPropertyError> {
  //   public: size_t operator () (const romp::ModelPropertyError& l, const romp::ModelPropertyError& r) const { return l.hash() == r.hash(); }
  // };
  // template<>
  // class hash<romp::ModelMErrorError> {
  //   public: size_t operator () (const romp::ModelMErrorError& me) const { return me.hash(); }
  // };
  // template<>
  // class equal_to<romp::ModelMErrorError> {
  //   public: size_t operator () (const romp::ModelMErrorError& l, const romp::ModelMErrorError& r) const { return l.hash() == r.hash(); }
  // };
} // namespace std

/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw/writers.hpp
 *
 * @brief The definitions for the writer objects
 *        used for outputting to trace files and the console.
 *
 * @date 2022/10/05
 * @version 0.2
 */

#ifndef __romp__GENERATED_CODE
#pragma once
#include "include.hpp"
#include "decl.hpp"
#include "options.hpp"
#endif

namespace romp {

  // << =========================== Helpful String Manipulation Utils ============================ >>

  static std::string octal(char c) {
    char buffer[sizeof("\\000")];
    snprintf(buffer, sizeof(buffer), "\\%03o", c);
    return buffer;
  }

  std::string escape_str(const std::string &s) {
    std::string out;
    for (size_t i=0; i<s.size(); ++i) {
      if (s[i] == '\\') {
        out += '\\';
        out += '\\';
      } else if (s[i] == '\"') {
        out += '\\';
        out += '"';
      // } else if (iscntrl(s[i])) {
      //   out += _octal_esc(s[i]);
      } else {
        out += s[i];
      }
    }
    return out;
  }

// << ========================================================================================== >>
// <<                                    WRITER DECLARATIONS                                     >>
// << ========================================================================================== >>

 // useful pre-decls
  template<class O> void __jprint_exception(ojstream<O>& json, const std::exception& ex) noexcept;
  template<class O> void __jprint_exception(ojstream<O>& json, const IModelError& ex) noexcept;

// << ====================================== Json Writer ======================================= >>

  template <class O>
  struct ojstream {
    static_assert(std::is_base_of<std::ostream, O>::value, "O must inherit from std::ostream");
    O out;
  protected: ojstream(O out_) : out(out_) {}
    // int ex_level = 0;
  public:
    ~ojstream() { out << std::flush; out.close(); } // probs move this to random walker
    template<typename... Args> ojstream(Args &&...args)
      : out(O(std::forward<Args>(args)...)) {}
    // template<typename T>
    // friend ojstream<O>& operator << (ojstream<O>& json, const T& val);
    template <typename T>
    ojstream<O>& operator << (const T* ptr) { if (ptr != nullptr) *this << *ptr; else out << "null"; return *this; }
    ojstream<O>& operator << (const std::string& str) { out << str; return *this; }
    ojstream<O>& operator << (const char* str) { out << str; return *this; }
    ojstream<O>& operator << (const unsigned char val) { out << val; return *this; }
    ojstream<O>& operator << (const char val) { out << val; return *this; }
    ojstream<O>& operator << (const unsigned long long val) { out << val; return *this; }
    ojstream<O>& operator << (const long long val) { out << val; return *this; }
    ojstream<O>& operator << (const unsigned long val) { out << val; return *this; }
    ojstream<O>& operator << (const long val) { out << val; return *this; }
    ojstream<O>& operator << (const unsigned int val) { out << val; return *this; }
    ojstream<O>& operator << (const int val) { out << val; return *this; }
    ojstream<O>& operator << (const unsigned short val) { out << val; return *this; }
    ojstream<O>& operator << (const short val) { out << val; return *this; }
    ojstream<O>& operator << (const long double val) { out << val; return *this; }
    ojstream<O>& operator << (const bool val) { out << ((val) ? "true" : "false"); return *this; }
    ojstream<O>& operator << (const stream_void& me) noexcept { return *this; };
    ojstream<O>& operator << (const IModelError& me) noexcept;
    ojstream<O>& operator << (const std::exception& ex) noexcept {
      // if (ex_level++ == 0) out << "],\"error-trace\":["
      out << "{\"$type\":\"exception\","
              "\"what\":\"" << escape_str(ex.what()) << "\"}";
      __jprint_exception(*this,ex);
      // if (--ex_level == 0) out << "],";
      return *this;
    }
    std::string str() {
      if (std::is_base_of<std::stringstream, O>::value) return out.str();
      else return "Not Allowed for non stringstream base (json_str_t) !!\t[dev-error]";
    }
  };
  template<>
  ojstream<std::ostream>::~ojstream() { out << std::flush; }

  typedef ojstream<std::ofstream> json_file_t;
  typedef ojstream<std::stringstream> json_str_t;


// << ================================= Pretty Format Writer =================================== >>

  class ostream_p {
  public:
    std::ostream& out;
    const Options& OPTIONS;
  protected:
    unsigned int _width;
    std::string _indentation;
  public:
    ostream_p(std::ostream& out_, const Options& OPTIONS_, unsigned int level_);
      //   : out(out_), _width(level_*OPTIONS.tab_size), OPTIONS(OPTIONS_)
      // { _indentation = std::string(_width,OPTIONS.tab_char); }
    inline int width() { return _width; }
    inline const stream_void indent(); // { _indentation = std::string((_width+=OPTIONS.tab_size),OPTIONS.tab_char); return S_VOID; }
    inline const std::string _indent() { indent(); return indentation(); }
    inline const stream_void dedent(); // { _indentation = std::string((_width-=OPTIONS.tab_size),OPTIONS.tab_char); return S_VOID; }
    inline const std::string _dedent() { dedent(); return indentation(); }
    inline const std::string indentation() { return _indentation; }
    inline const stream_void new_line() { out << '\n' << indentation(); return S_VOID; }
    inline const stream_void nl() { out << '\n' << indentation(); return S_VOID; }
    // template <typename T>
    // inline ostream_p& operator << (const T val);
    // ostream_p& operator << (const std::string& str) { out << str; return *this; }
    // ostream_p& operator << (const char* str) { out << str; return *this; }
    // ostream_p& operator << (const unsigned char val) { out << val; return *this; }
    // ostream_p& operator << (const char val) { out << val; return *this; }
    // ostream_p& operator << (const unsigned long long val) { out << val; return *this; }
    // ostream_p& operator << (const long long val) { out << val; return *this; }
    // ostream_p& operator << (const unsigned long val) { out << val; return *this; }
    // ostream_p& operator << (const long val) { out << val; return *this; }
    // ostream_p& operator << (const unsigned int val) { out << val; return *this; }
    // ostream_p& operator << (const int val) { out << val; return *this; }
    // ostream_p& operator << (const unsigned short val) { out << val; return *this; }
    // ostream_p& operator << (const short val) { out << val; return *this; }
    // ostream_p& operator << (const long double val) { out << val; return *this; }
    // ostream_p& operator << (const bool val) { out << ((val) ? "true" : "false"); return *this; }
    // ostream_p& operator << (const stream_void& me) noexcept { return *this; };
  };
  template <typename T>
  ostream_p& operator << (ostream_p& out, const T& val) { out.out << val; return out; }
  // template <>
  // inline ostream_p& operator << <std::_Setw>(ostream_p& out, const std::_Setw val) { _width = val._M_n; return *this; }
  template <>
  ostream_p& operator << <stream_void>(ostream_p& out, const stream_void& val) { return out; }
  template <>
  ostream_p& operator << <bool>(ostream_p& out, const bool& val) { (out.out << ((val) ? "YES" : "NO")); return out; }
  // template <typename T>
  // inline ostream_p& ostream_p::operator << (const T val) { out << val; return *this; }
  // // template <>
  // // inline ostream_p& ostream_p::operator << <std::_Setw>(const std::_Setw val) { out._width = val._M_n; return out; }
  // template <>
  // inline ostream_p& ostream_p::operator << <stream_void>(const stream_void val) { return *this; }
  // template <>
  // inline ostream_p& ostream_p::operator << <bool>(const bool val) { return (*this << ((val) ? "YES" : "NO")); }



// << ========================================================================================== >>
// <<                          WRITER STREAM OPERATOR IMPLEMENTATIONS                            >>
// << ========================================================================================== >>


// << =================================== Fancy Time Writer ==================================== >>

  template<typename ratio1, typename ratio2>
  struct CompareStdRatios {
    // std::static_assert(std::is_base_of<std::ratio,ratio1>::value, "ratio1, must be a ratio");
    // std::static_assert(std::is_base_of<std::ratio,ratio1>::value, "ratio2, must be a ratio");
    static constexpr long double dif() { return (ratio1::num/ratio1::den) - (ratio2::num/ratio2::den); };
  };

  template<typename T, class R>
  const std::string _pre0(const std::chrono::duration<T,R> dur) { return ((dur.count()<10) ? "0" : ""); }
  template<typename T, class R>
  ostream_p& operator << (ostream_p& out, const std::chrono::duration<T,R> _dur) noexcept {
    using namespace std::chrono;
    using day_t = duration<T, std::ratio<3600 * 24>>;
    using femtosecond_t = duration<T, std::femto>;
    using picosecond_t = duration<T, std::pico>;
    enum TimeUnit {__U,__ms,_fs,_ps,_ns,_us,_ms,_s,_min,_hr,_d};
    const TimeUnit _SU = __U;
    std::chrono::duration<long double,R> dur(_dur);
    day_t d(0);
    hours h(0);
    minutes m(0);
    seconds s(0);
    milliseconds ms(0);
    microseconds us(0);
    nanoseconds ns(0);
    picosecond_t ps(0);
    // femtosecond_t fs(0);
    TimeUnit msu = _fs;
    if (CompareStdRatios<R,std::milli>::dif() > 0.0l // case: lower precision clock
        || dur > seconds(10)) { // case: "large"/"macro" time format(s)
      if (dur > day_t(3)) {
        d = duration_cast<day_t>(dur);
        dur -= d; msu = _d;
      }
      if (msu > _hr || dur > hours(3)) {
        h = duration_cast<hours>(dur);
        dur -= h; msu = ((msu > _hr) ? msu : _hr);
      }
      if (msu > _min || dur > minutes(3)) {
        m = duration_cast<minutes>(dur);
        dur -= m; msu = ((msu > _min) ? msu : _min);
      }
      if (msu > _s || dur >= seconds(10)) {
        s = duration_cast<seconds>(dur);
        dur -= s; msu = ((msu > _s) ? msu : _s);
      }
      if (msu > _ms || dur >= microseconds(1)) {
        ms = duration_cast<milliseconds>(dur);
      } else msu = __ms;  // case: measured essentially 0 time ms
    } else /* if (CompareStdRatios<R,std::milli>::dif() < 0.0l) */ { // case: higher precision clock
      if (dur >= microseconds(10)) { // case: "small"/milli+micro time format
        ms = duration_cast<milliseconds>(dur);
        us = duration_cast<microseconds>(dur -= ms);
        msu = _ms;
      } else {
        if (dur >= picosecond_t(1)) { // case: "smaller"/nano+pico time format
          ns = duration_cast<nanoseconds>(dur);
          ps = duration_cast<picosecond_t>(dur -= ns);
          msu = _ns;
        } else                            // case: "smallest"/"too small to care about"/femto time "format"
          msu = _fs;
      // } else                              // case: "not needed "
      //   msu = __ms;
      }
    }

    switch (msu) {
      case _d:
        return (out << d.count() << "d "
                    << _pre0(h) << h.count() << ':'
                    << _pre0(m) << m.count() << ':'
                    << _pre0(s) << s.count() << '.'
                    << ms.count());
      case _hr:
        return (out << _pre0(h) << h.count() << ':'
                    << _pre0(m) << m.count() << ':'
                    << _pre0(s) << s.count() << '.'
                    << ms.count());
      case _min:
        return (out << _pre0(m) << m.count() << ':'
                    << _pre0(s) << s.count() << '.'
                    << ms.count());
      case _s:
        out << s.count();
        if (ms > milliseconds(0))
          out << '.' << ms.count();
        return (out << "s");
      case _ms:
      case _us:
        out << ms.count();
        if (us > microseconds(0))
          out << '.' << us.count();
        return (out << "ms");;
      case _ns:
      case _ps:
        out << ns.count();
        if (ps > picosecond_t(0))
          out << '.' << ps.count();
        return (out << "ns");
      case __ms:
        return (out << "<0.001ms");
      case _fs:
        return (out << "<0.001ns");
      case __U:
      default:
        return (out << "<ERROR_PARSING_DURATION>");
    }
    return out;
  }

// << =================================== Metadata Writers ===================================== >>

  // std::ostream& operator << (std::ostream& out, const TypeType& val) {
  //   switch (val) {
  //     case TypeType::BOOLEAN: return out << "Boolean";
  //     case TypeType::RANGE: return out << "Range";
  //     case TypeType::ENUM: return out << "Enum";
  //     case TypeType::SCALARSET: return out << "Scalarset";
  //     case TypeType::SCALARSET_UNION: return out << "Union";
  //     case TypeType::ARRAY: return out << "Array";
  //     case TypeType::MULTISET: return out << "Multiset";
  //     case TypeType::RECORD: return out << "Record";
  //     case TypeType::TYPE_EXPR_ID: return out; // write nothing
  //     default: return out << "<UNKNOWN_TYPE>";}
  // }


  template<class O>
  ojstream<O>& operator << (ojstream<O>& json, const file_position& fp) {
    return (json << '[' << fp.row << ',' << fp.col << ']');
  }
  std::ostream& operator << (std::ostream& out, const file_position& fp) {
    return (out << fp.row << ',' << fp.col);
  }

  template<class O>
  ojstream<O>& operator << (ojstream<O>& json, const location& loc) {
    return (json << "{\"$type\":\"location\","
            << "\"file\":\"" __model__filename "\","
            // << (loc.model_obj != "") ? "\"inside\":\""+loc.model_obj+"\"," : EMPTY_STR
            << "start" << ':' << loc.start << ','
            << "\"end\":" << loc.end
            << '}');
  }
  std::ostream& operator << (std::ostream& out, const location& loc) {
    out << ((__model__filename_contains_space) ? "\"" __model__filename "\":" : __model__filename ":");
    if (loc.start.row == loc.end.row) {
      out << loc.start.row << ',' << loc.start.col;
      if (loc.start.col != loc.end.col)
        out << '-' << loc.end.col;
    } else
      out << loc.start << '-' << loc.end;
    // if (loc.model_obj != "")
    //   out << " in ``" << loc.model_obj << "``";
    return out;
  }


  std::ostream& operator << (std::ostream& out, const PropertyType& val) {
    switch (val) {
      case PropertyType::ASSERTION: return out << "assert";
      case PropertyType::ASSUMPTION: return out << "assume";
      case PropertyType::COVER: return out << "cover";
      case PropertyType::LIVENESS: return out << "liveness";
      case PropertyType::INVARIANT: return out << "invariant";
      default: return out << "UNKNOWN";}
  }
  template<class O> ojstream<O>& operator << (ojstream<O>& json, const PropertyType& val) { json.out << val; return json; }

  std::ostream& operator << (std::ostream& out, const PropertyInfo& pi) noexcept {
    return (out << pi.type << " \"" << pi.label << "\" " /* << pi.expr */ << " @(" << pi.loc << ")");
  }
  template<class O> ojstream<O>& operator << (ojstream<O>& json, const PropertyInfo& pi) noexcept {
    return (json << pi.json_h << '}');
  }

  std::ostream& operator << (std::ostream& out, const Property& p) noexcept {
    out << p.info.type << " \"" << p.info.label << "\" ";
    if (p.quant_str.size() > 0)
      out << " Quantifiers(" << p.quant_str << ") ";
    return (out << "@(" << p.info.loc << ')');
  }
  template<class O> ojstream<O>& operator << (ojstream<O>& json, const Property& p) noexcept {
    return (json << p.info.json_h << ",\"quantifiers\":" << p.quant_json << '}');
  }


  template<class O> ojstream<O>& operator << (ojstream<O>& json, const RuleInfo& ri) noexcept {
#ifdef __ROMP__SIMPLE_TRACE
    json.out << "\"rule \\\""<< ri.label << "\\\""
                // " @(" << ri.loc << ")\"";
             << '"';
#else
    json << ri.json_h << '}';
#endif
    return json;
  }
  std::ostream& operator << (std::ostream& out, const RuleInfo& ri) noexcept {
    return (out << "rule \""<< ri.label << "\" @(" << ri.loc << ")");
  }

  template<class O> ojstream<O>& operator << (ojstream<O>& json, const Rule& r) noexcept {
#ifdef __ROMP__SIMPLE_TRACE
    json.out << "\"rule \\\"" << r.info.label << "\\\" ";
    if (r.quant_str.size() > 0)
      json.out << " Quantifiers(" << r.quant_str << ") ";
    // json.out << "@(" << r.info.loc << ")\"";
    json.out << '"';
#else
    json << r.info.json_h << ",\"quantifiers\":" << r.quant_json << '}';
#endif
    return json;
  }
  std::ostream& operator << (std::ostream& out, const Rule& r) noexcept {
    out << "rule \"" << r.info.label << "\" ";
    if (r.quant_str.size() > 0)
      out << " Quantifiers(" << r.quant_str << ") ";
    return (out << "@(" << r.info.loc << ')');
  }

  template<class O> ojstream<O>& operator << (ojstream<O>& json, const RuleSet& rs) noexcept {
    return (json << rs.info);
  }
  std::ostream& operator << (std::ostream& out, const RuleSet& rs) noexcept {
    return (out << rs.info);
  }



  template<class O> ojstream<O>& operator << (ojstream<O>& json, const StartStateInfo& si) noexcept {
    return (json << si.json_h << '}');
  }
  std::ostream& operator << (std::ostream& out, const StartStateInfo& si) noexcept {
    return (out << "startstate \""<< si.label << "\" @(" << si.loc << ")");
  }

  template<class O> ojstream<O>& operator << (ojstream<O>& json, const StartState& s) noexcept {
    json << s.info.json_h
         << ",\"id\":" << s.id
         << ",\"quantifiers\":" << s.quant_json << '}';
    return json;
  }
  std::ostream& operator << (std::ostream& out, const StartState& s) noexcept {
    out << "startstate \"" << s.info.label << "\" ";
    if (s.quant_str.size() > 0)
      out << "-- id: " << s.id
          << " -- Quantifiers(" << s.quant_str << ") ";
    return (out << "@(" << s.info.loc << ')');
  }


  template<class O> ojstream<O>& operator << (ojstream<O>& json, const MErrorInfo& ei) noexcept {
    return (json << ei.json);
  }
  std::ostream& operator << (std::ostream& out, const MErrorInfo& ei) noexcept {
    return (out << "error \""<< ei.label << "\" @(" << ei.loc << ")");
  }


  template<class O> ojstream<O>& operator << (ojstream<O>& json, const FunctInfo& fi) noexcept {
    return (json << fi.json);
  }
  std::ostream& operator << (std::ostream& out, const FunctInfo& fi) noexcept {
    return (out << fi.signature << " @(" << fi.loc << ")");
  }


  std::string get_color(Result::Cause val) {
    switch (val) {
      case romp::Result::UNKNOWN_CAUSE:
        return "\033[43;32m";
      case romp::Result::ATTEMPT_LIMIT_REACHED:
      case romp::Result::MAX_DEPTH_REACHED:
        return "\033[33m";
#ifdef __romp__ENABLE_assume_property
      case romp::Result::ASSUMPTION_VIOLATED:
#endif
      case romp::Result::MERROR_REACHED:
      case romp::Result::PROPERTY_VIOLATED:
        return "\033[31m";
#ifdef __romp__ENABLE_cover_property
      case romp::Result::COVER_COMPLETE:
        return "\033[32m";
#endif
      case romp::Result::NO_CAUSE:
      default:
        return "\033[45;30m";
    }
  }

} // namespace romp

namespace std {
  std::string to_string(::romp::Result::Cause val) {
    switch (val) {
      case romp::Result::UNKNOWN_CAUSE:
        return "UNKNOWN ISSUE";
      case romp::Result::ATTEMPT_LIMIT_REACHED:
        return "ATTEMPT LIMIT REACHED";
      case romp::Result::MAX_DEPTH_REACHED:
        return "MAX_DEPTH_REACHED";
      case romp::Result::PROPERTY_VIOLATED:
        return "PROPERTY VIOLATED";
#ifdef __romp__ENABLE_cover_property
      case romp::Result::COVER_COMPLETE:
        return "COVER COMPLETE";
#endif
#ifdef __romp__ENABLE_assume_property
      case romp::Result::ASSUMPTION_VIOLATED:
        return "ASSUMPTION VIOLATED";
#endif
      case romp::Result::MERROR_REACHED:
        return "ERROR STATEMENT REACHED";
      case romp::Result::NO_CAUSE:
      default:
        return "<!-- YOU SHOULD NEVER SEE THIS MESSAGE -->";
    }
  }
} // namespace std

#pragma endregion romp_prefix



#pragma region scalar_enums__generated_code
namespace __model__ {

  enum __romp__SCALAR_ENUM_t__ {
    _UNDEFINED_ = 0,
    /* procT: scalarset(Nprocs) */
      _romp_procT_6_1,
      _romp_procT_6_2,
      _romp_procT_6_3,
      _romp_procT_6_4,
      _romp_procT_6_5,
      _romp_procT_6_6,
    /* enum { ENTER, TRYING, BLOCKED, LOCKED, EXITING } */
      ENTER,
      TRYING,
      BLOCKED,
      LOCKED,
      EXITING,
    /* enum { HANDLE, TRYGRANT } */
      HANDLE,
      TRYGRANT,
  };

} // namespace __model__
namespace romp { typedef ::__model__::__romp__SCALAR_ENUM_t__ SCALAR_ENUM_t; }
namespace __info__ { std::string SCALAR_IDS[14] = { "<undef>", "procT_1", "procT_2", "procT_3", "procT_4", "procT_5", "procT_6", "ENTER", "TRYING", "BLOCKED", "LOCKED", "EXITING", "HANDLE", "TRYGRANT" }; }


#pragma endregion scalar_enums__generated_code


#pragma region romp_infix

/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw-options.hpp
 *
 * @brief the handler for the configuration of a random walk
 *
 * @date 2022/10/05
 * @version 0.2
 */

#ifndef __romp__GENERATED_CODE
#pragma once
#include "include.hpp"
#include "decl.hpp"
#include "writers.hpp"
#include "error.hpp"
#include <functional>
#include <iostream>
#include <string>
#endif

namespace romp {

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

    /**
     * @brief the number of concurrent threads a system supports \n
     *        \b NOTE: if \c 0 then number is unknown & user must provide with \c -ptn / \c --threads flags.
     */
    const unsigned int __SYSTEM_THREAD_COUNT = ::std::thread::hardware_concurrency();
    unsigned int get_default_thread_count() {
      switch (__SYSTEM_THREAD_COUNT) {
      case 0: return 0;
      case 1:
      case 2:
        return 1;
      default:
        return __SYSTEM_THREAD_COUNT - 2;
      }
    }

#define _ROMP_ATTEMPT_LIMIT_DEFAULT UINT16_MAX
#define _ROMP_START_ID_DEFAULT ((unsigned)(~(0u)))
struct Options {
  // size_t history_length = 4;
  bool do_trace = false;
  unsigned int threads =  get_default_thread_count();
  size_t depth = 1024ul; // INT16_MAX;
  unsigned int walks = threads*_ROMP_THREAD_TO_RW_RATIO;
  unsigned int rand_seed = ROMP_ID;
  std::string seed_str = std::to_string(ROMP_ID);
  bool do_single = false;
  bool do_even_start = false;
  id_t start_id = _ROMP_START_ID_DEFAULT;
  bool skip_launch_prompt = false;
  size_t attempt_limit = _ROMP_ATTEMPT_LIMIT_DEFAULT; // disabled if _ROMP_ATTEMPT_LIMIT_DEFAULT
  std::string trace_dir = "./traces/"; // path for the trace file to be created during each walk
  bool deadlock = true; // do deadlock protections
#ifdef __romp__ENABLE_liveness_property
  bool liveness = false;
  size_t lcount = INT16_MAX;
#endif
#ifdef __romp__ENABLE_cover_property
  bool complete_on_cover = false;
  id_t cover_count = INT16_MAX;
#endif
  bool r_cover = false;
// #ifdef __romp__ENABLE_assume_property
  bool r_assume = false;
// #endif
  bool report_error = false; // print results for each walker in addition to the summery
  bool report_all = false;
  bool report_show_type = false;
  bool report_emit_state = true;
  unsigned int tab_size = 2;
  char tab_char = ' ';
  // bfs options ----
  bool do_bfs = false;
  bool bfs_single = true;
  size_t bfs_coefficient = _ROMP_BFS_COEF;
  size_t bfs_limit = INT16_MAX; // max number of states to explore before giving up

  const std::string get_trace_dir() const noexcept {
    if (do_single) return trace_dir;
    std::stringstream buf; buf << INIT_TIME_STAMP;
    return trace_dir + "/" __model__filename "_" + buf.str();
  }
  const std::string get_trace_file_path(id_t rw_id) const noexcept {
    if (not do_single)
      return get_trace_dir() + "/" + std::to_string(rw_id) + ".trace.json";
    std::stringstream buf; buf << INIT_TIME_STAMP;
    return trace_dir + "/" + __model__filename + "_" + buf.str() + ".trace.json";
  }
  bool report_any() const {
    return (report_all || do_single || report_error || r_assume || r_cover);
  }

  template<class O>
  friend ojstream<O>& operator << (ojstream<O>& json, const Options& opts) noexcept;



  void parse_args(int argc, char **argv);

  const stream_void write_config(ostream_p& out) const noexcept;

}; // struct options


// Options OPTIONS;

} // namespace romp

/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file error.hpp
 *
 * @brief The definitions for the Error handling system used to interact with
 *        the generated model.
 *
 * @date 2022/10/05
 * @version 0.2
 */

#ifndef __romp__GENERATED_CODE
#pragma once
#include "pregen-fix.hpp"  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "include.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "decl.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "writers.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif

namespace romp {


// << ========================================================================================== >>
// <<                                ABSTRACT ERROR PARENT DECL                                  >>
// << ========================================================================================== >>

const std::exception_ptr __get_root_except(const std::exception_ptr& ex) {
  try { std::rethrow_if_nested(ex);
  } catch (const std::nested_exception& ne){
    if (ne.nested_ptr() == nullptr)
      return std::current_exception();
    return __get_root_except(ne.nested_ptr());
  } catch (...) {
    return std::current_exception();
  }
  return ex;
}

struct IModelError : public std::nested_exception {
  IModelError()
    : std::nested_exception() {}
  virtual ~IModelError() = default;
  const char* what() const noexcept {
    std::stringstream out;
    this->what(out);
    return out.str().c_str();
  }
  virtual void what(std::ostream& out) const noexcept = 0;
  virtual void to_json(json_file_t& json) const noexcept = 0;
  virtual void to_json(json_str_t& json) const noexcept = 0;
  virtual size_t hash() const noexcept = 0;
  virtual const std::string& label() const noexcept = 0;
  virtual const std::string& quants() const noexcept = 0;
  virtual bool is_generic() const noexcept = 0;
  virtual std::string get_type() const noexcept = 0;
  bool is_flat() const { return (quants() == ""); }
  const std::exception_ptr get_root_except() const {
    if (this->nested_ptr() == nullptr)
      try { throw this;
      } catch (...) { return std::current_exception(); }
    return __get_root_except(this->nested_ptr());
  }
  void write_root_excpt_what(std::ostream& out) const {
    try { throw this->get_root_except();
    } catch (const std::exception& ex) { out << ex.what(); }
  }
  friend bool operator == (const IModelError& l, const IModelError& r) { return (l.hash() == r.hash()); }
};

template<class O>
ojstream<O>& ojstream<O>::operator << (const IModelError& me) noexcept {
  me.to_json(*this);
  if (me.nested_ptr() != nullptr)
    __jprint_exception(*this,me);
  return *this;
}

// << ========================================================================================== >>
// <<                              DERIVED MODEL ERROR CLASS DECLS                               >>
// << ========================================================================================== >>


// << ================================= Model Property Error =================================== >>

struct ModelPropertyError : public IModelError {
    ModelPropertyError(const Property& prop_) : isProp(true) { data.prop = &prop_; }
    ModelPropertyError(const PropertyInfo& info_) : isProp(false) { data.info = &info_; }
    ModelPropertyError(id_t id) : isProp(false) { data.info = &(::__info__::PROPERTY_INFOS[id]); }
    ~ModelPropertyError() = default;
    void what(std::ostream& out) const noexcept { if (isProp) out << *data.prop; else out << *data.info; }
    void to_json(json_file_t& json) const noexcept { _to_json(json); }
    void to_json(json_str_t& json) const noexcept { _to_json(json); }
    const PropertyInfo& info() const noexcept { return ((isProp) ? data.prop->info : *data.info); }
  private:
    union {const Property* prop; const PropertyInfo* info;} data;
    const bool isProp;
    template<class O>
    void _to_json(ojstream<O>& json) const noexcept {
      json << "{\"$type\":\"model-error\","
               "\"type\":\"property\","
              //  "\"what\":\""<< escape_str(what()) << "\","
               "\"inside\":";
      if (isProp) json << *data.prop; else json << *data.info;
      json << '}';
    }
  public:
    size_t hash() const noexcept { return reinterpret_cast<size_t>((isProp) ? &(data.prop->info) : data.info); }
    const std::string& label() const noexcept { return ((isProp) ? data.prop->info.label : data.info->label); }
    const std::string& quants() const noexcept { return ((isProp) ? data.prop->quant_str : EMPTY_STR); }
    bool is_generic() const noexcept { return not isProp; }
    std::string get_type() const noexcept {
      std::stringstream tmp;
      tmp << info().type;
      return tmp.str();
    }
  };

  IModelError* PropertyInfo::make_error() const { return new ModelPropertyError(*this); }
  IModelError* Property::make_error() const { return new ModelPropertyError(*this); }


  // << ================================== Model Rule Error(s) =================================== >>

  struct ModelRuleError : public IModelError {
    enum Where {UNKNOWN,GUARD,ACTION};
    ModelRuleError(const Rule& rule_) : isRule(true), where(UNKNOWN) { data.rule = &rule_; }
    ModelRuleError(const RuleInfo& info_) : isRule(false), where(UNKNOWN) { data.info = &info_; }
    ModelRuleError(const RuleSet& rule_set_) : isRule(false), where(UNKNOWN) { data.info = &(rule_set_.info); }
    ModelRuleError(id_t id) : isRule(false), where(UNKNOWN) { data.info = &(::__info__::RULE_SET_INFOS[id]); }
    ModelRuleError(id_t id, Where where_) : isRule(false), where(where_) { data.info = &(::__info__::RULE_SET_INFOS[id]); }
    ~ModelRuleError() = default;
    void what(std::ostream& out) const noexcept { if (isRule) out << *data.rule; else out << *data.info; }
    void to_json(json_file_t& json) const noexcept { _to_json(json); }
    void to_json(json_str_t& json) const noexcept { _to_json(json); }
    const RuleInfo& info() const noexcept { return ((isRule) ? data.rule->info : *data.info); }
  private:
    union {const Rule* rule; const RuleInfo* info;} data;
    const bool isRule;
    const Where where;
    template<class O>
    void _to_json(ojstream<O>& json) const noexcept {
      json << "{\"$type\":\"model-error\","
               "\"type\":\"rule" << ((where==UNKNOWN) ? "" : ((where==GUARD) ? "-guard" : "-action")) << "\","
              //  "\"what\":\""<< escape_str(what()) << "\","
               "\"inside\":";
      if (isRule) json << *data.rule; else json << *data.info;
      json << '}';
    }
  public:
    size_t hash() const noexcept { return reinterpret_cast<size_t>(&(info())); }
    const std::string& label() const noexcept { return info().label; }
    const std::string& quants() const noexcept { return ((isRule) ? data.rule->quant_str : EMPTY_STR); }
    bool is_generic() const noexcept { return not isRule; }
    std::string get_type() const noexcept { return "rule"; }
  };

  IModelError* RuleInfo::make_error() const { return new ModelRuleError(*this); }
  IModelError* Rule::make_error() const { return new ModelRuleError(*this); }
  IModelError* RuleSet::make_error() const { return new ModelRuleError(*this); }



  // << =============================== Model StartState Error(s) ================================ >>

  struct ModelStartStateError : public IModelError {
    ModelStartStateError(const StartState& rule_) : isStartState(true) { data.rule = &rule_; }
    ModelStartStateError(const StartStateInfo& info_) : isStartState(false) { data.info = &info_; }
    ModelStartStateError(id_t id) : isStartState(false) { data.info = &(::__info__::STARTSTATE_INFOS[id]); }
    ~ModelStartStateError() = default;
    void what(std::ostream& out) const noexcept { if (isStartState) out << *data.rule; else out << *data.info; }
    void to_json(json_file_t& json) const noexcept { _to_json(json); }
    void to_json(json_str_t& json) const noexcept { _to_json(json); }
    const StartStateInfo& info() const noexcept { return ((isStartState) ? data.rule->info : *data.info); }
  private:
    union {const StartState* rule; const StartStateInfo* info;} data;
    const bool isStartState;
    template<class O>
    void _to_json(ojstream<O>& json) const noexcept {
      json << "{\"$type\":\"model-error\","
               "\"type\":\"startstate\","
              //  "\"what\":\""<< escape_str(what()) << "\","
               "\"inside\":";
      if (isStartState) json << *data.rule; else json << *data.info;
      json << '}';
    }
  public:
    size_t hash() const noexcept { return reinterpret_cast<size_t>((isStartState) ? &(data.rule->info) : data.info); }
    const std::string& label() const noexcept { return ((isStartState) ? data.rule->info.label : data.info->label); }
    const std::string& quants() const noexcept { return ((isStartState) ? data.rule->quant_str : EMPTY_STR); }
    bool is_generic() const noexcept { return not isStartState; }
    std::string get_type() const noexcept { return "startstate"; }
  };

  IModelError* StartStateInfo::make_error() const { return new ModelStartStateError(*this); }
  IModelError* StartState::make_error() const { return new ModelStartStateError(*this); }


  // << ================================= Model Error Error(s) =================================== >>

  struct ModelMErrorError : public IModelError {
    ModelMErrorError(const MErrorInfo& info_) : _info(info_) {}
    ModelMErrorError(id_t id) : _info(::__info__::ERROR_INFOS[id]) {}
    ~ModelMErrorError() = default;
    void what(std::ostream& out) const noexcept { out << _info; }
    void to_json(json_file_t& json) const noexcept { _to_json(json); }
    void to_json(json_str_t& json) const noexcept { _to_json(json); }
    const MErrorInfo& info() const noexcept { return _info; }
  private:
    const MErrorInfo& _info;
    template<class O>
    void _to_json(ojstream<O>& json) const noexcept {
      json << "{\"$type\":\"model-error\","
               "\"type\":\"error-statement\","
              //  "\"what\":\"" << escape_str(what()) << "\","
               "\"inside\":" << _info << '}';
    }
  public:
    size_t hash() const noexcept { return reinterpret_cast<size_t>(&_info); }
    const std::string& label() const noexcept { return _info.label; }
    const std::string& quants() const noexcept { return EMPTY_STR; }
    bool is_generic() const noexcept { return true; }
    std::string get_type() const noexcept { return "error"; }
  };


  // << ================================ Model Function Error(s) ================================= >>

  struct ModelFunctError : public IModelError {
    ModelFunctError(const FunctInfo& info_) : _info(info_) {}
    ModelFunctError(id_t id) : _info(::__info__::FUNCT_INFOS[id]) {}
    ~ModelFunctError() = default;
    void what(std::ostream& out) const noexcept { out << _info; }
    void to_json(json_file_t& json) const noexcept { _to_json(json); }
    void to_json(json_str_t& json) const noexcept { _to_json(json); }
    const FunctInfo& info() const noexcept { return _info; }
  private:
    const FunctInfo& _info;
    template<class O>
    void _to_json(ojstream<O>& json) const noexcept {
      json << "{\"$type\":\"model-error\","
               "\"type\":\"function\","
              //  "\"what\":\"" << escape_str(what()) << "\","
               "\"inside\":" << _info << '}';
    }
  public:
    size_t hash() const noexcept { return reinterpret_cast<size_t>(&_info); }
    const std::string& label() const noexcept { return _info.label; }
    const std::string& quants() const noexcept { return EMPTY_STR; }
    bool is_generic() const noexcept { return true; }
    std::string get_type() const noexcept { return "function"; }
  };


  // << =================================== Model Type Errors ==================================== >>

  struct ModelTypeError : public IModelError {
    std::string msg;
    location loc;
    ModelTypeError(const std::string& msg_, const location& loc_) : msg(msg_), loc(loc_) {}
    ~ModelTypeError() = default;
    void what(std::ostream& out) const noexcept {
      out << loc << " :: " << msg;
    }
    void to_json(json_file_t& json) const noexcept { _to_json(json); }
    void to_json(json_str_t& json) const noexcept { _to_json(json); }
    size_t hash() const noexcept { std::hash<location> _h; return _h(loc); }
    const std::string& label() const noexcept { return msg; }
    virtual const std::string& quants() const noexcept { return EMPTY_STR; }
    virtual bool is_generic() const noexcept { return true; }
    virtual std::string get_type() const noexcept { return "type"; }
  private:
    template<class O>
    void _to_json(ojstream<O>& json) const noexcept {
      json << "{\"$type\":\"model-type-error\","
               "\"location\":" << loc << ","
               "\"what\":\"" << escape_str(msg) << "\"}";
    }
  };


// << ========================================================================================== >>
// <<                              NESTED EXCEPTION/ERROR WRITERS                                >>
// << ========================================================================================== >>

  // << ========================== Json Nested Error/Exception Writers =========================== >>

  template<class O> void __jprint_exception(ojstream<O>& json, const std::exception& ex) noexcept {
    try {
        std::rethrow_if_nested(ex);
    } catch(const IModelError& mod_ex) {
      json << ',' << mod_ex;
    } catch(const std::exception& ex) {
      json << ',' << ex;
    } catch(...) {
      if (std::current_exception() != nullptr)
        json << ",{\"$type\":\"trace-error\",\"what\":\"unknown non-exception type thrown !!\"}";
    }
  }
  template<class O> void __jprint_exception(ojstream<O>& json, const IModelError& ex) noexcept {
    try {
        std::rethrow_if_nested(ex);
    } catch(const IModelError& mod_ex) {
      json << ',' << mod_ex;
    } catch(const std::exception& ex) {
      json << ',' << ex;
    } catch(...) {
      if (std::current_exception() != nullptr)
        json << ",{\"$type\":\"trace-error\",\"what\":\"unknown non-exception type thrown !!\"}";
    }
  }


  // << ====================== Pretty Print Nested Error/Exception Writers ======================= >>

  void __fprint_exception(ostream_p& out, const std::exception& ex) noexcept;
  void __fprint_exception(ostream_p& out, const IModelError& ex) noexcept;

  ostream_p& operator << (ostream_p& out, const IModelError& ex) noexcept {
    out << '{';
    ex.what(out.out);
    // out << out.nl();
    if (ex.nested_ptr() != nullptr)
      __fprint_exception(out, ex);
    out << '}';
    return out;
  }
  // std::ostream& operator << (std::ostream& out, const IModelError& ex) noexcept { ostream_p _out(out,0); _out << ex;  return out; }

  ostream_p& operator << (ostream_p& out, const std::exception& ex) noexcept {
    out << "{exception ``";
    out << ex.what(); // << out.nl();
    out << "``";
    __fprint_exception(out, ex);
    out << '}';
    return out;
  }
  // std::ostream& operator << (std::ostream& out, const std::exception& ex) noexcept { ostream_p _out(out,0); _out << ex;  return out; }

  void __fprint_exception(ostream_p& out, const std::exception& ex) noexcept {
    try {
        std::rethrow_if_nested(ex);
    } catch(const IModelError& mod_ex) {
      out << out.indent() << out.nl() << "cause=" << mod_ex << out.dedent();
    } catch(const std::exception& ex) {
      out << out.indent() << out.nl() << "cause=" << ex << out.dedent();
    } catch(...) {
      if (std::current_exception() != nullptr)
        out << out.indent() << out.nl() << "cause={!! UNKNOWN NON-EXCEPTION TYPE THROWN !!}"
            << out.dedent();
    }
  }
  void __fprint_exception(ostream_p& out, const IModelError& ex) noexcept {
    try {
        std::rethrow_if_nested(ex);
    } catch(const IModelError& mod_ex) {
      out << out.indent() << out.nl() << "cause=" << mod_ex << out.dedent();
    } catch(const std::exception& ex) {
      out << out.indent() << out.nl() << "cause=" << ex << out.dedent();
    } catch(...) {
      if (std::current_exception() != nullptr)
        out << out.indent() << out.nl() << "cause={!! UNKNOWN NON-EXCEPTION TYPE THROWN !!}"
            << out.dedent();
    }
  }

} // namespace romp

namespace std {
  template<>
  struct hash<romp::IModelError> {
    size_t operator () (const romp::IModelError& me) const { return me.hash(); }
  };
  template<>
  struct equal_to<romp::IModelError> {
    bool operator () (const romp::IModelError& l, const romp::IModelError& r) const { return l.hash() == r.hash(); }
  };
  template<>
  class hash<romp::ModelPropertyError> {
    public: size_t operator () (const romp::ModelPropertyError& me) const { return me.hash(); }
  };
  template<>
  class equal_to<romp::ModelPropertyError> {
    public: size_t operator () (const romp::ModelPropertyError& l, const romp::ModelPropertyError& r) const { return l.hash() == r.hash(); }
  };
  template<>
  class hash<romp::ModelMErrorError> {
    public: size_t operator () (const romp::ModelMErrorError& me) const { return me.hash(); }
  };
  template<>
  class equal_to<romp::ModelMErrorError> {
    public: size_t operator () (const romp::ModelMErrorError& l, const romp::ModelMErrorError& r) const { return l.hash() == r.hash(); }
  };
} // namespace std

/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw/types.hpp
 *
 * @brief The Template Type decls used to represent Murphi Types.
 *
 * @date 2022/10/05
 * @version 0.2
 */

#ifndef __romp__GENERATED_CODE  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#pragma once                // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "pregen-fix.hpp"  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "include.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "decl.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "writers.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
namespace __model__ { // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
  enum SCALAR {_UNDEFINED_=0}; // useful pre-decl // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
} // namespace __model__  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
namespace __info__ { // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
  const std::string SCALAR_IDS[1] {"<UNDEFINED>"}; // useful pre-decl // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
} // namespace __model__  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
namespace romp { // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
  typedef ::__model__::SCALAR SCALAR_ENUM_t;  // typemask for the enum type holding all scalar and enum values // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
} // namespace __model__  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif

namespace romp {

  // << ================================== Scalar Enum Helpers =================================== >>
  template<typename T>
  inline SCALAR_ENUM_t make_SCALAR_ENUM_t(T val) { return static_cast<SCALAR_ENUM_t>(val); }
  inline std::string to_str(const SCALAR_ENUM_t& scalar) { return ::__info__::SCALAR_IDS[static_cast<size_t>(scalar)]; }
  inline std::ostream& operator << (std::ostream& out, const SCALAR_ENUM_t& val) { return (out << to_str(val)); }
  // inline ostream_p& operator << (ostream_p& out, const SCALAR_ENUM_t& val) { return (out << to_str(val)); }
  template<class O>
  inline ojstream<O>& operator << (ojstream<O>& json, const SCALAR_ENUM_t& val) {
      if (val == SCALAR_ENUM_t::_UNDEFINED_) return (json << "null");
#   ifdef __ROMP__SIMPLE_TRACE
      return (json << static_cast<size_t>(val));
#   else
      return (json << '"' <<to_str(val)<< '"');
#   endif
  }


  // << ====================================== Base Types ======================================== >>

  // template<typename T>
  // inline void Assignment(T& container, const T& value, const location& loc) {
  //   try {
  //     container = value;
  //   } catch (...) {
  //     throw ModelTypeError("error durring assignment", loc);
  //   }
  // }
  template<typename T>
  inline void Assignment(T& container, const T value, const location& loc) {
    try {
      container = value;
    } catch (...) {
      throw ModelTypeError("error durring assignment", loc);
    }
  }

  /**
   * @brief A 0 width type to ensure all types have access to the metadata generated for them
   * @tparam TID the location in \c ::__info__::TYPE_INFOS that this type's metadata is stored.
   */
  // template<size_t TID>
  // class BaseType {
  // public:
  //   static inline constexpr const TypeInfo& __INFO() { return ::__info__::TYPE_INFOS[0]; }
  //   static inline const std::string __json_type() { return std::to_string(TID); }
  // protected:
  //   template<typename T, typename ET>
  //   static inline void throw_(std::string msg);
  // };

  template<typename T>
  class BaseUndefinableType {
    T value;
    bool is_defined;
  public: // NOTE: I was lazy and just made this section public instead of protected
    inline T get() const {
      if (not is_defined)
        throw std::logic_error("value was undefined");
      return value;
    }
    inline BaseUndefinableType& set(const T& value_) {
      value = value_;
      is_defined = true;
      return *this;
    }
    inline T unsafe_get() const { return value; }
  public:
    BaseUndefinableType() { Undefine(); }
    // BaseUndefinableType(T value_) : is_defined(true), value(value_) {}
    BaseUndefinableType(const T& value_) : is_defined(true), value(value_) {}
    inline void Undefine() { is_defined = false; std::memset(&value, 0u, sizeof(T)); }
    inline bool IsUndefined() const { return not is_defined; }

    static constexpr bool __IS_SIMPLE() { return true; }
    static constexpr bool __IS_RECORD() { return false; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() { return false; }

    explicit inline operator T () { return value; }

    // friend ostream_p& operator << (ostream_p& out, const BaseUndefinableType& val) {
    friend std::ostream& operator << (std::ostream& out, const BaseUndefinableType& val) {
      if (val.IsUndefined())
        return (out << SCALAR_ENUM_t::_UNDEFINED_);
      return (out << val.get());
    }
    static inline const std::string __json_type() { return "null"; }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& json, const BaseUndefinableType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        if (val.IsUndefined()) return (json << "null");
        return (json << val.get());
#     else
        json << "{\"$type\":\"undefinable-value\",\"type-id\":null,\"value\":";
        if (val.IsUndefined())
          return (json << "null}");
        return (json << val.get() << '}');
#     endif
    }
    friend class std::hash<BaseUndefinableType>;
  };


  // << ===================================== Type ID Mask ======================================= >>

  template<size_t TID, class T>
  class TypeIdType : public T {
  public:
    template<typename... Args>
    TypeIdType(Args &&... args) : T(std::forward<Args>(args)...) {}
    // template<typename... Args>
    // TypeIdType(const Args &&... args) : T(std::forward<Args>(args)...) {}
    operator T& () { return *((T*)this); }
    // operator T& () const { return T(*this); }
    // static inline constexpr const TypeInfo& __INFO() { return ::__info__::TYPE_INFOS[0]; }
    static inline constexpr bool __IS_TYPEID() { return true; }
    static inline const std::string& __id() { return ::__info__::TYPE_IDS[TID]; }
    static inline constexpr const std::string __json_type() {
      // return std::to_string(TID);
      return "{\"$type\":\"type-id\",\"tid\":"+std::to_string(TID)+",\"id\":\"" + __id() + "\",\"referent\":" + T::__json_type() + '}';
    }
    static inline constexpr const std::string __p_type() { return __id(); }
    template<template<size_t,class>class TId_t>
    friend
    typename std::enable_if<std::is_base_of<TypeIdType<TID,T>,
                                            TId_t<TID,T>>::value,
                            ostream_p>::type& operator << (ostream_p& out, TId_t<TID,T> val) {
      return (out << *((T*)&val));
    }
  };


  // << ===================================== Simple Types ======================================= >>

  class BooleanType : public BaseUndefinableType<bool>/* , public BaseType<0ul> */ {
  public:
    BooleanType() : BaseUndefinableType<bool>() {}
    BooleanType(bool val) : BaseUndefinableType<bool>(val) {}

    void Clear() { set(false); }
    inline operator bool () const { return get(); }
    // inline operator int () const { return static_cast<int>(get()); }
    inline operator range_t () const { return static_cast<range_t>(get()); }
    inline BooleanType operator = (bool val) { return ((BooleanType&)set(val)); }

    // static inline constexpr const TypeInfo& __INFO() { return ::__info__::TYPE_INFOS[0]; }
    // static inline constexpr BooleanType __LB() { return false; }
    // static inline constexpr BooleanType __UB() { return true; }
    // BooleanType& __step() { set(true); return *this; }
    static inline constexpr size_t __COUNT() { return 2u; }

    static inline const std::string __p_type() { return "Boolean"; }

    friend inline bool operator == (const BooleanType& l, const BooleanType& r) {
      return !(l.IsUndefined() || r.IsUndefined()) && (l.unsafe_get() == r.unsafe_get());
    }
    friend inline bool operator == (const BooleanType& l, const bool& r) {
      return (not l.IsUndefined()) && (l.unsafe_get() == r);
    }
    friend inline bool operator == (const bool& l, const BooleanType& r) {
      return (not r.IsUndefined()) && (l == r.unsafe_get());
    }

    // friend inline ostream_p& operator << (ostream_p& out, const BooleanType& val) {
    friend inline std::ostream& operator << (std::ostream& out, const BooleanType& val) {
      if (val.IsUndefined())
        return (out << SCALAR_ENUM_t::_UNDEFINED_);
      return (out << ((val.get()) ? "true" : "false"));
    }
    static inline const std::string __json_type() { return "{\"$type\":\"boolean-type\"}"; }
#   ifndef __ROMP__SIMPLE_TRACE
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const BooleanType& val) {
      out << "{\"$type\":\"undefinable-value\",\"type-id\":"<< __json_type() <<","
            "\"value\":";
      if (val.IsUndefined())
        return (out << "null}");
      return (out << val.get() << '}');
    }
#   endif
  };

  template<range_t LB, range_t UB, range_t STEP=(range_t)((LB<=UB) ? 1 : -1)>
  class RangeType : public BaseUndefinableType<range_t> {
    static_assert(not ((LB<=UB) xor (STEP>0)), "step must go in the same direction as bounds");
    static_assert((not (STEP==0) || (LB==UB)), "if STEP is 0, then LB must equal UB");
  protected:
    static void _check(range_t value_) {
      if (LB<=UB) { // compiler should optimize this top level if-else out
        if (LB <= value_ && value_ <= UB) return;
      } else {
        if (UB <= value_ && value_ <= LB) return;
      }
      throw std::out_of_range("value (`" +
                              std::to_string(value_) +
                              "`) is out of range (`"+
                              std::to_string(LB) +
                              ".."+
                              std::to_string(UB) +
                              "`)");
    }
  public:
    RangeType() : BaseUndefinableType<range_t>() {}
    RangeType(range_t value_) : BaseUndefinableType<range_t>(value_) { _check(value_); }
    template<range_t O_LB, range_t O_UB, range_t O_STEP>
    RangeType(const RangeType<O_LB,O_UB,O_STEP>& range_) {
      if (range_.IsUndefined()) Undefine();
      else { RangeType::_check(range_.__unsafe_get()); this->set(range_.__unsafe_get()); }
    }
    inline range_t __unsafe_get() const { return unsafe_get(); }
    void Clear() { set(LB); }
    inline operator range_t () { return get(); }
    inline RangeType& operator = (range_t other) {
      _check(other);
      return ((RangeType&)set(other));
    }
    template<range_t N_LB, range_t N_UB, range_t N_STEP>
    inline RangeType& operator = (const RangeType<N_LB,N_UB,N_STEP>& other) {
      if (other.IsUndefined()) {
        Undefine();
        return *this;
      }
      return (*this = other);
    }
    size_t __get_index_val() const { return static_cast<size_t>(get() - LB); }
    static constexpr RangeType __LB() { return RangeType(LB); }
    static constexpr RangeType __UB() { RangeType tmp(UB); tmp.set(UB+STEP); return tmp; }
    static constexpr size_t __COUNT() { return (((UB-LB)+1)/STEP); }
    RangeType& __step() {
      // step needs to account for uneven ranges or modifying values in model between steps
      range_t val = get() + STEP;
      if (LB<=UB) { // compiler should optimize this top level if-else out
        set((val <= UB) ? val : UB+STEP);
      } else {
        set((val >= UB) ? val : UB+STEP);
      }
      return *this;
    }

    inline range_t __get_value() const { return get(); }

    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator + (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() + r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator - (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() - r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator * (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() * r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator / (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() / r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator % (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() % r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator & (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() & r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator | (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() | r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator ^ (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() ^ r.__get_value(); }

    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator < (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return r.get() < r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator <= (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() <= r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator == (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return !(l.IsUndefined() || r.IsUndefined()) && l.get() == r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator != (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return !(l.IsUndefined() || r.IsUndefined()) && l.unsafe_get() != r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator >= (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.unsafe_get() >= r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator > (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() > r.__get_value(); }

    friend inline range_t operator + (const RangeType& l, const range_t& r) { return l.get() + r; }
    friend inline range_t operator - (const RangeType& l, const range_t& r) { return l.get() - r; }
    friend inline range_t operator * (const RangeType& l, const range_t& r) { return l.get() * r; }
    friend inline range_t operator / (const RangeType& l, const range_t& r) { return l.get() / r; }
    friend inline range_t operator % (const RangeType& l, const range_t& r) { return l.get() % r; }
    friend inline range_t operator & (const RangeType& l, const range_t& r) { return l.get() & r; }
    friend inline range_t operator | (const RangeType& l, const range_t& r) { return l.get() | r; }
    friend inline range_t operator ^ (const RangeType& l, const range_t& r) { return l.get() ^ r; }
    friend inline bool operator < (const RangeType& l, const range_t& r) { return l.get() < r; }
    friend inline bool operator <= (const RangeType& l, const range_t& r) { return l.get() <= r; }
    friend inline bool operator == (const RangeType& l, const range_t& r) { return (not l.IsUndefined()) && l.unsafe_get() == r; }
    friend inline bool operator != (const RangeType& l, const range_t& r) { return (not l.IsUndefined()) && l.unsafe_get() != r; }
    friend inline bool operator >= (const RangeType& l, const range_t& r) { return l.get() >= r; }
    friend inline bool operator > (const RangeType& l, const range_t& r) { return l.get() > r; }
    friend inline range_t operator + (const range_t& l, const RangeType& r) { return l + r.get(); }
    friend inline range_t operator - (const range_t& l, const RangeType& r) { return l - r.get(); }
    friend inline range_t operator * (const range_t& l, const RangeType& r) { return l * r.get(); }
    friend inline range_t operator / (const range_t& l, const RangeType& r) { return l / r.get(); }
    friend inline range_t operator % (const range_t& l, const RangeType& r) { return l % r.get(); }
    friend inline range_t operator & (const range_t& l, const RangeType& r) { return l & r.get(); }
    friend inline range_t operator | (const range_t& l, const RangeType& r) { return l | r.get(); }
    friend inline range_t operator ^ (const range_t& l, const RangeType& r) { return l ^ r.get(); }
    friend inline bool operator < (const range_t& l, const RangeType& r) { return l < r.get(); }
    friend inline bool operator <= (const range_t& l, const RangeType& r) { return l <= r.get(); }
    friend inline bool operator == (const range_t& l, const RangeType& r) { return (not r.IsUndefined()) && l == r.unsafe_get(); }
    friend inline bool operator != (const range_t& l, const RangeType& r) { return (not r.IsUndefined()) && l != r.unsafe_get(); }
    friend inline bool operator >= (const range_t& l, const RangeType& r) { return l >= r.get(); }
    friend inline bool operator > (const range_t& l, const RangeType& r) { return l > r.get(); }


    static constexpr const std::string __p_type() {
      if (-1 <= STEP && STEP <= 1) // compiler should optimize this out
        return std::to_string(LB) + ".." + std::to_string(UB);
      return std::to_string(LB) + " to " + std::to_string(UB) + " by " + std::to_string(STEP);
    }
    // friend ostream_p& operator << (ostream_p& out, RangeType& val) {
    //   return (out << get());
    // }
    static constexpr const std::string __json_type() {
      return "{\"$type\":\"range-type\","
                "\"bounds\":["+std::to_string(LB)+","+std::to_string(UB)+"]}";
    }
#   ifndef __ROMP__SIMPLE_TRACE
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const RangeType& val) {
      out << "{\"$type\":\"undefinable-value\",\"type-id\":"<< __json_type() <<","
            "\"value\":";
      if (val.IsUndefined())
        return (out << "null}");
      return (out << val.get() << '}');
    }
#   endif
  };



  // << =================================== Scalar/Enum Types ==================================== >>

  // useful pre-decls
  template<size_t ENUM_ID, size_t BOUND> class EnumType;
  template<size_t ENUM_ID, size_t BOUND> class ScalarsetType;
  template<class... UNION_MEMBERS> class ScalarsetUnionType;

  template<size_t ENUM_ID, size_t BOUND>
  class EnumType {
  protected:
    SCALAR_ENUM_t value;
  public:
    EnumType() : value(SCALAR_ENUM_t::_UNDEFINED_) {}
    EnumType(const SCALAR_ENUM_t& value_) : value(value_) {
      if (value_ != SCALAR_ENUM_t::_UNDEFINED_ && not IsMember(value_))
        throw std::logic_error("`"+ to_str(value_) +"` is not a member of this enum type");
    }
    template<class... UM>
    EnumType(const ScalarsetUnionType<UM...>& union_) : EnumType(union_.__get_scalar_value()) {}

    inline bool IsUndefined() const { return value == SCALAR_ENUM_t::_UNDEFINED_; }
    inline void Undefine() { value = SCALAR_ENUM_t::_UNDEFINED_; }
    inline void Clear() { value = make_SCALAR_ENUM_t(ENUM_ID); }

    static inline bool IsMember(const SCALAR_ENUM_t& v) {
      //NOTE: IsMember does not recognise Undefined as a Member of this type
      return (((make_SCALAR_ENUM_t(ENUM_ID) <= v)
                    && (v <= make_SCALAR_ENUM_t(ENUM_ID+BOUND))));
    }

    static constexpr size_t __ENUM_ID() { return ENUM_ID; }
    static constexpr size_t __BOUND() { return BOUND; }
    static constexpr EnumType __LB() { return make_SCALAR_ENUM_t(ENUM_ID); }
    static constexpr EnumType __UB() { return make_SCALAR_ENUM_t(ENUM_ID+BOUND); }
    EnumType& __step() { value = make_SCALAR_ENUM_t(static_cast<size_t>(value)+1); return *this; }
    static constexpr size_t __COUNT() { return BOUND; }
    static constexpr bool __IS_SIMPLE() { return true; }
    static constexpr bool __IS_RECORD() { return false; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() { return false; }

    // cast to index operator
    inline size_t __get_index_val() const {
      if (IsUndefined())
        throw std::logic_error("value was undefined");
      return static_cast<size_t>(value)-ENUM_ID;
    }
    const SCALAR_ENUM_t& __get_scalar_value() const { return value; }

    template<size_t EID, size_t B, class... U_M>
    friend inline void __assign(EnumType<EID,B>& _this, const ScalarsetUnionType<U_M...>& other);

    template<class... U_M>
    inline EnumType& operator = (const ScalarsetUnionType<U_M...>& other) { __assign(*this,other); return *this; }
    inline EnumType& operator = (const SCALAR_ENUM_t& val) {
      if (val != SCALAR_ENUM_t::_UNDEFINED_ && not IsMember(val))
        throw std::logic_error("`"+ to_str(value) +"` is not a member of this enum type");
      value = val;
      return *this;
    }

    template<class... U_M>
    explicit inline operator ScalarsetUnionType<U_M...> () { return __convert(*this); }
    template<class... U_M>
    friend ScalarsetUnionType<U_M...> __convert(const EnumType& _this);

    template<size_t R_EID, size_t R_B>
    friend inline bool operator == (const EnumType& l, const EnumType<R_EID,R_B> r) {
      return l.value == r.value;
    }
    template<size_t R_EID, size_t R_B>
    friend inline bool operator != (const EnumType& l, const EnumType<R_EID,R_B> r) {
      return l.value != r.value;
    }
    friend inline bool operator == (const EnumType& l, const SCALAR_ENUM_t& r) {
      return l.value == r;
    }
    friend inline bool operator != (const EnumType& l, const SCALAR_ENUM_t& r) {
      return l.value != r;
    }
    friend inline bool operator == (const SCALAR_ENUM_t& l, const EnumType& r) {
      return l == r.value;
    }
    friend inline bool operator != (const SCALAR_ENUM_t& l, const EnumType& r) {
      return l != r.value;
    }

    /* this IsMember is the one associated with the IsMember() Murphi language operator */
    template<typename T, class... U_M>
    friend inline bool IsMember(const ScalarsetUnionType<U_M...> u);

    static constexpr const std::string __p_type() {
      std::string res = "enum {";
      std::string sep;
      for (auto i=__LB(); i!=__UB(); i.__step()) {
        res += sep + to_str(make_SCALAR_ENUM_t(i.__get_scalar_value()));
        sep = ",";
      }
      return res + "}";
    }
    // friend ostream_p& operator << (ostream_p& out, const EnumType& val) { return (out << val.value); }
    friend std::ostream& operator << (std::ostream& out, const EnumType& val) { return (out << val.value); }
    static inline constexpr const std::string __json_type() {
      return "{\"$type\":\"enum-type\",\"first-member\":\""+to_str(make_SCALAR_ENUM_t(ENUM_ID))+"\",""\"member-count\":"+std::to_string(BOUND)+'}';
    }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const EnumType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.value);
#     else
        out << "{\"$type\":\"undefinable-value\",\"type-id\":" << EnumType::__json_type() << ",\"value\":";
        // if (val.IsUndefined())
        //   return (out << "null}");
        return (out << val.value << '}');
#     endif
    }
  };

  template<size_t ENUM_ID, size_t BOUND>
  class ScalarsetType : public EnumType<ENUM_ID,BOUND> {
  public:
    ScalarsetType() : EnumType<ENUM_ID,BOUND>() {}
    ScalarsetType(const SCALAR_ENUM_t& value_) {
      if (value_ != SCALAR_ENUM_t::_UNDEFINED_ && not EnumType<ENUM_ID,BOUND>::IsMember(value_))
        throw std::logic_error("`"+ to_str(value_) +"` is not a member of this scalarset type");
      this->value = value_;
    }
    template<class... UM>
    ScalarsetType(const ScalarsetUnionType<UM...>& union_) : ScalarsetType(union_.__get_scalar_value()) {}
    // static inline const std::string __id() { return ::__info__::TYPE_INFOS[TID].label; }


    static constexpr ScalarsetType __LB() { return make_SCALAR_ENUM_t(ENUM_ID); }
    static constexpr ScalarsetType __UB() { return make_SCALAR_ENUM_t(ENUM_ID+BOUND); }
    ScalarsetType& __step() { EnumType<ENUM_ID,BOUND>::__step(); return *this; }

    template<class... U_M>
    explicit inline operator ScalarsetUnionType<U_M...> () { return __convert(*this); }
    template<class... U_M>
    friend ScalarsetUnionType<U_M...> __convert(const ScalarsetType& _this);

    template<class... U_M>
    friend inline void __assign(ScalarsetType& _this, const ScalarsetUnionType<U_M...>& other);
    template<class... U_M>
    inline ScalarsetType& operator = (const ScalarsetUnionType<U_M...>& other) { __assign(*this,other); return *this; }
    inline ScalarsetType& operator = (const SCALAR_ENUM_t& val) {
      if (val != SCALAR_ENUM_t::_UNDEFINED_ && not EnumType<ENUM_ID,BOUND>::IsMember(val))
        throw std::logic_error("`"+ to_str(val) +"` is not a member of this scalarset type");
      this->value = val;
      return *this;
    }

    static constexpr const std::string __p_type() { return "scalarset("+std::to_string(BOUND)+')'; }
    // friend ostream_p& operator << (ostream_p& out, const ScalarsetType& val) { return (out << val.value); }
    friend std::ostream& operator << (std::ostream& out, const ScalarsetType& val) { return (out << val.value); }
    static constexpr const std::string __json_type() { return "{\"$type\":\"scalarset-type\",\"bound\":"+std::to_string(BOUND)+'}'; }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const ScalarsetType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.value);
#     else
        out << "{\"$type\":\"undefinable-value\",\"type-id\":" << ScalarsetType::__json_type() << ",\"value\":";
        // if (val.IsUndefined())
        //   return (out << "null}");
        return (out << val.value << '}');
#     endif
    }
  };


  template<class... UNION_MEMBERS>
  class ScalarsetUnionType {
    SCALAR_ENUM_t value;
  protected:
    // static const size_t MEMBER_COUNT;
    static const size_t ENUM_IDS[sizeof...(UNION_MEMBERS)+1];
    static const size_t BOUNDS[sizeof...(UNION_MEMBERS)+1];

    template<size_t E_ID, size_t B>
    static constexpr bool ContainsMember() {
#     if __cplusplus >= 201703L
        return (((UNION_MEMBERS::__ENUM_ID() == E_ID) || ...) && ((UNION_MEMBERS::__BOUND() == B) || ...)); // [[requires C++17]]
#     else
        bool res = false;
        for (size_t i=1; i<(sizeof...(UNION_MEMBERS)+1); ++i)
          res |= ((ENUM_IDS[i] == E_ID) && (BOUNDS[i] == B));
        return res;
#     endif
    }
    static inline bool MembersContain(const SCALAR_ENUM_t& v) {
      if (v == SCALAR_ENUM_t::_UNDEFINED_) return true;
#     if __cplusplus >= 201703L
        return (UNION_MEMBERS::IsMember(v) || ...); // [[requires C++17]]
#     else
        bool res = false;
        for (size_t i=1; i<(sizeof...(UNION_MEMBERS)+1); ++i)
          res |= ((ENUM_IDS[i] <= v) && (v <= ENUM_IDS[i]+BOUNDS[i]-1));
        return res;
#     endif
    }

    public:
    ScalarsetUnionType() : value(SCALAR_ENUM_t::_UNDEFINED_) {}
    ScalarsetUnionType(const SCALAR_ENUM_t& value_) : value(value_) {
      if (not MembersContain(value_)) // this is NOT evaluate-able at compile time
        throw std::out_of_range("`"+ to_str(value) +"` is not a member of the union (scalarset union)");
    }
    template<size_t E_ID, size_t B>
    ScalarsetUnionType(const EnumType<E_ID,B>& value_) {
      if (not ContainsMember<E_ID,B>()) // this is evaluate-able at compile time (if c++17)
        throw std::out_of_range("`"+ to_str(value) +"` is not a member of the union (scalarset union)");
      value = value_.__get_scalar_value();
    }
    template<class... UM>
    ScalarsetUnionType(const ScalarsetUnionType<UM...>& u_) : ScalarsetUnionType(u_.value) {}

    static inline bool IsMember(const SCALAR_ENUM_t& val) { return (val != SCALAR_ENUM_t::_UNDEFINED_ && MembersContain(val)); }
    inline bool IsUndefined() const { return (value == SCALAR_ENUM_t::_UNDEFINED_); }
    inline void Undefine() { value = SCALAR_ENUM_t::_UNDEFINED_; }
    inline void Clear() { value = (((sizeof...(UNION_MEMBERS))<=0) ? SCALAR_ENUM_t::_UNDEFINED_ : make_SCALAR_ENUM_t(ENUM_IDS[1]) ); }

    // get index value
    inline const size_t __get_index_val() const {
      if (IsUndefined())
        throw std::logic_error("value was undefined");
      size_t offset = 0ul;
      size_t i;
      for (i=0ul; i<(sizeof...(UNION_MEMBERS)+1); ++i) {
        if (ENUM_IDS[i] <= value && value <= (ENUM_IDS[i]+BOUNDS[i]-1))
          return offset + static_cast<size_t>(value) - ENUM_IDS[i] -1; // modified for dbg
        offset += BOUNDS[i];
      }
      throw std::runtime_error("DEV ERROR : could not convert union to index value");
    }
    const SCALAR_ENUM_t& __get_scalar_value() const { return value; }

    template<size_t EID, size_t B>
    explicit inline operator EnumType<EID,B> () {
      static_assert(ScalarsetUnionType::ContainsMember<EID,B>(),
                    "union must contain enum member type to cast to it!");
      return EnumType<EID,B>(value);
    }
    template<size_t EID, size_t B>
    friend inline ScalarsetUnionType __convert(const EnumType<EID,B>& _this) {
      static_assert((ScalarsetUnionType::ContainsMember<EID,B>()),
                  "enum type must be a member of the union type to be cast to it");
      return ScalarsetUnionType(_this.value);
    }
    template<size_t EID, size_t B>
    explicit inline operator ScalarsetType<EID,B> () {
      static_assert(ScalarsetUnionType::ContainsMember<EID,B>(),
                    "union must contain scalarset member type to cast to it!");
      return ScalarsetType<EID,B>(value);
    }
    template<size_t EID, size_t B>
    friend inline ScalarsetUnionType __convert(const ScalarsetType<EID,B>& _this) {
      static_assert((ScalarsetUnionType::ContainsMember<EID,B>()),
                  "scalarset type must be a member of the union type to be cast to it");
      return ScalarsetUnionType(_this.value);
    }

    template<size_t E_ID, size_t B>
    inline ScalarsetUnionType& operator = (const EnumType<E_ID,B>& other) { return (*this = other.__get_scalar_value()); }
    inline ScalarsetUnionType& operator = (const SCALAR_ENUM_t& val) {
      if (not MembersContain(val)) // this is evaluate-able at compile time
        throw std::out_of_range("`"+ to_str(value) +"` is not a member of the union (scalarset union)");
      value = val;
    }

    template<class... R_M>
    friend inline bool operator == (const ScalarsetUnionType& l, const ScalarsetUnionType<R_M...> r) {
      return l.value == r.value;
    }
    template<class... R_M>
    friend inline bool operator != (const ScalarsetUnionType& l, const ScalarsetUnionType<R_M...> r) {
      return l.value != r.value;
    }

    bool operator == (const SCALAR_ENUM_t& other) const { return value == other; }
    bool operator != (const SCALAR_ENUM_t& other) const { return value != other; }
    template<size_t EID, size_t B>
    bool operator == (const EnumType<EID,B>& other) const { return value == other.__get_scalar_value(); }
    template<size_t EID, size_t B>
    bool operator != (const EnumType<EID,B>& other) const { return value != other.__get_scalar_value(); }

    template<size_t EID, size_t B>
    friend inline bool operator == (const EnumType<EID,B>& e, const ScalarsetUnionType& u) { return u == e; }
    template<size_t EID, size_t B>
    friend inline bool operator != (const EnumType<EID,B>& e, const ScalarsetUnionType& u) { return u == e; }

    /* this IsMember is the one associated with the IsMember() Murphi language operator */
    // template<class ET, class... U_M>
    // friend inline bool IsMember(const ScalarsetUnionType<U_M...>& u);
    // template<size_t EID, size_t B, class... U_M>
    // friend inline bool IsMember(const ScalarsetUnionType<U_M...>& u);

    class iterator {
      ScalarsetUnionType u;
      size_t i;
      size_t j;
    public:
      iterator(size_t i_, size_t j_)
        : i(i_), j(j_)
        {
          if (i>sizeof...(UNION_MEMBERS)) {
            j = 0; u.value = SCALAR_ENUM_t::_UNDEFINED_;
          } else u.value = make_SCALAR_ENUM_t(ScalarsetUnionType::ENUM_IDS[i_]+j_);
        }
      ScalarsetUnionType& operator*() const { return u; }
      ScalarsetUnionType* operator->() { return &u; }
      iterator& operator += (int) { return (__step()); }
      iterator& __step() {
        // if (i>=sizeof...(UNION_MEMBERS)+1) {
        //   j = 0; u.value = SCALAR_ENUM_t::_UNDEFINED_;
        //   return *this;
        // }
        if (++j < ScalarsetUnionType::BOUNDS[i]) {
          u.value = make_SCALAR_ENUM_t(static_cast<size_t>(u.value)+1);
          return *this;
        }
        ++i; j=0;
        if (i>=sizeof...(UNION_MEMBERS)+1) {
          u.value = SCALAR_ENUM_t::_UNDEFINED_;
          return *this;
        }
        u.value = make_SCALAR_ENUM_t(ScalarsetUnionType::ENUM_IDS[i]+j);
        return *this;
      }
      friend bool operator <= (const iterator& l, const iterator& r) {
        return (l.i<=r.i && l.j <= r.j);
      }
      operator ScalarsetUnionType () { return ScalarsetUnionType(u); }
      operator SCALAR_ENUM_t () { return u.value; }
      iterator& operator = (const ScalarsetUnionType& other) {
        throw std::logic_error("you cannot assign to a quantifier or for-loop iterator");
      }
      inline SCALAR_ENUM_t __get_scalar_value() const { return u.value; }
      friend inline bool operator == (const iterator& l, const iterator& r) { return (l.i==r.i && l.j==r.j); }
      friend inline bool operator != (const iterator& l, const iterator& r) { return (l.i!=r.i || l.j!=r.j); }
      friend inline bool operator == (const ScalarsetUnionType& l, const iterator& r) { return l == r.u; }
      friend inline bool operator != (const ScalarsetUnionType& l, const iterator& r) { return l != r.u; }
      friend inline bool operator == (const iterator& l, const ScalarsetUnionType& r) { return l.u == r; }
      friend inline bool operator != (const iterator& l, const ScalarsetUnionType& r) { return l.u != r; }
      template<size_t EID, size_t B>
      friend inline bool operator == (const EnumType<EID,B>& e, const ScalarsetUnionType::iterator& ui) { return ui.u == e; }
      template<size_t EID, size_t B>
      friend inline bool operator != (const EnumType<EID,B>& e, const ScalarsetUnionType::iterator& ui) { return ui.u == e; }
      template<size_t EID, size_t B>
      friend inline bool operator == (const ScalarsetUnionType::iterator& ui, const EnumType<EID,B>& e) { return ui.u == e; }
      template<size_t EID, size_t B>
      friend inline bool operator != (const ScalarsetUnionType::iterator& ui, const EnumType<EID,B>& e) { return ui.u == e; }
      friend std::ostream& operator << (std::ostream& out, const iterator& val) { return (out << val.u); }
    };

    ScalarsetUnionType(const iterator& it_)
      : ScalarsetUnionType(it_.__get_scalar_value()) {}
    template<class... UM>
    ScalarsetUnionType(const typename ScalarsetUnionType<UM...>::iterator& it_)
      : ScalarsetUnionType(it_.__get_scalar_value()) {}

    static constexpr iterator __LB() { return iterator(1, 0); }
    static constexpr iterator __UB() { return iterator(sizeof...(UNION_MEMBERS)+1, 0); }
    // static constexpr int __STEP() { return 1; }

    static constexpr size_t __COUNT() {
#     if __cplusplus >= 201703L
        return ((UNION_MEMBERS::__COUNT()) + ...); // [[requires C++17]]
#     else
        size_t counts[sizeof...(UNION_MEMBERS)] = {(UNION_MEMBERS::__COUNT())...};
        size_t res=0;
        for (size_t i=0; i<sizeof...(UNION_MEMBERS); ++i)
          res += counts[i];
        return res;
#     endif
    }
    static constexpr bool __IS_SIMPLE() { return true; }
    static constexpr bool __IS_RECORD() { return false; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() { return false; }

    static constexpr const std::string __p_type() {
#     if __cplusplus >= 201703L
        return "union {" + ((UNION_MEMBERS::__p_type()) + ...) + "}"; // [[requires C++17]]
#     else
        const std::string member_types[sizeof...(UNION_MEMBERS)] = {(UNION_MEMBERS::__p_type())...};
        std::string res = "union {";
        std::string sep;
        for (size_t i=0; i<sizeof...(UNION_MEMBERS); ++i) {
          res += sep + member_types[i];
          sep = ", ";
        }
        return res + "}";
#     endif
    }
    // friend ostream_p& operator << (ostream_p& out, const ScalarsetUnionType& val) { return (out << val.value); }
    friend std::ostream& operator << (std::ostream& out, const ScalarsetUnionType& val) { return (out << val.value); }
    static constexpr const std::string __json_type() {
      return "{\"$type\":\"scalarset-union-type\","
                "\"member-count\":"+std::to_string(sizeof...(UNION_MEMBERS))+","
                "\"\"bound\":"+ std::to_string(__COUNT()) +'}';
    }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const ScalarsetUnionType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.value);
#     else
        out << "{\"$type\":\"undefinable-value\",\"type-id\":" << ScalarsetUnionType::__json_type() << ",\"value\":";
        // if (val.IsUndefined())
        //   return (out << "null}");
        return (out << val.value << '}');
#     endif
    }
  };

  template<class... UNION_MEMBERS>
  const size_t ScalarsetUnionType<UNION_MEMBERS...>::ENUM_IDS[sizeof...(UNION_MEMBERS)+1] = {0,UNION_MEMBERS::__ENUM_ID()...};

  template<class... UNION_MEMBERS>
  const size_t ScalarsetUnionType<UNION_MEMBERS...>::BOUNDS[sizeof...(UNION_MEMBERS)+1] = {1,UNION_MEMBERS::__BOUND()...};


  /* this IsMember is the one associated with the IsMember() Murphi language operator */
  template<class ET, typename VT>
  inline bool IsMember(const VT& u) {
    return ET::IsMember(u.__get_scalar_value());
  }


  // << ===================================== Complex Types ====================================== >>
  template<typename INDEX_t, typename ELEMENT_t>
  class ArrayType;

  template<typename INDEX_t, typename ELEMENT_t>
  inline ELEMENT_t& Element(ArrayType<INDEX_t,ELEMENT_t>& array, const INDEX_t& index, const location& loc);
  template<typename INDEX_t, typename ELEMENT_t>
  inline const ELEMENT_t& Element(const ArrayType<INDEX_t,ELEMENT_t>& array, const INDEX_t& index, const location& loc);
  // template<template<typename INDEX_t, typename ELEMENT_t>class ARRAY_t>
  // inline ELEMENT_t& Element(ARRAY_t& array, const INDEX_t& index, const location& loc);

  template<typename INDEX_t, typename ELEMENT_t>
  class ArrayType {
    ELEMENT_t data[INDEX_t::__COUNT()];
  public:
    ArrayType() { Undefine(); }
    ELEMENT_t& operator [] (const INDEX_t& i) { return data[i.__get_index_val()]; }
    const ELEMENT_t& operator [] (const INDEX_t& i) const { return data[i.__get_index_val()]; }
    // typename std::enable_if<(not std::is_convertible<INDEX_t,size_t>::value), ELEMENT_t>::type
    // ELEMENT_t operator [] (const size_t i) {
    //   if ((0 > i) || (i >= INDEX_t::__COUNT()))
    //     throw std::out_of_range("`"+std::to_string(i)+"` is out of bounds of the array");
    //   return data[i];
    // }
    // friend inline ELEMENT_t& Element(ArrayType& array, const INDEX_t& index, const location& loc) {
    //   try {
    //     return (array[index]);
    //   } catch (...) {
    //     throw ModelTypeError("error durring array element access", loc);
    //   }
    // }

    bool IsUndefined() const {
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i)
        if (not data[i].IsUndefined())
          return false;
      return true;
    }
    void Undefine() { std::memset(&data, 0u, sizeof(data)); } // for now design still allows for setting all to 0 to undefine
    void Clear() {
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i)
        data[i].Clear();
    }

    static constexpr bool __IS_SIMPLE() { return false; }
    static constexpr bool __IS_RECORD() { return false; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() {
      return ((ELEMENT_t::__DO_P_SEP()) || ((INDEX_t::__COUNT()>4))
              || (sizeof(ELEMENT_t)>(sizeof(BooleanType)*((ELEMENT_t::__IS_RECORD()) ? 2 : 3))));
    }

    template<typename RI, typename RE>
    friend bool operator == (const ArrayType& l, const ArrayType<RI,RE>& r) {
      if (INDEX_t::__COUNT() != RI::__COUNT()) return false; // evaluate-able at compile time
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i)
        if (l.data[i] != r.data[i])
          return false;
      return true;
    }
    template<typename RI, typename RE>
    friend bool operator != (const ArrayType& l, const ArrayType<RI,RE>& r) {
      if (INDEX_t::__COUNT() != RI::__COUNT()) return true; // evaluate-able at compile time
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i)
        if (l.data[i] == r.data[i])
          return false;
      return true;
    }

  protected:
    // write split line if there is a lot of info in the data structure
    inline void _pWrite_comp(ostream_p& out) const {
      std::string sep;
      out.indent();
      for (auto i=INDEX_t::__LB(); i!=INDEX_t::__UB(); i.__step()) {
        out << sep << out.nl() << '[' << i << "]: " << (*this)[i]; sep = ",";
      }
      out.dedent();
    }
    // write single line if there is NOT a lot of info in the data structure
    inline void _pWrite_simp(ostream_p& out) const {
      std::string sep;
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i) {
        out << sep << data[i]; sep = ", ";
      }
    }
  public:
    static constexpr const std::string __p_type() {
      return "Array["+INDEX_t::__p_type()+"] of " + ELEMENT_t::__p_type();
    }
    // template<typename It, typename Et>
    // friend inline ostream_p& operator << (ostream_p& out, const ArrayType& val) {
    template<template<typename,typename>class Arr_t>
    friend
    typename std::enable_if<std::is_base_of<ArrayType<INDEX_t,ELEMENT_t>,
                                            Arr_t<INDEX_t,ELEMENT_t>>::value,
                            ostream_p>::type& operator << (ostream_p& out, const Arr_t<INDEX_t,ELEMENT_t>& val) {
      if (val.IsUndefined()) return (out << SCALAR_ENUM_t::_UNDEFINED_);
      out << '[';
      if (ArrayType::__DO_P_SEP()) {
        val._pWrite_comp(out);
        out.nl();
      } else
        val._pWrite_simp(out);
      return (out << ']');
    }
    static constexpr const std::string __json_type() {
      return "{\"$type\":\"array-type\",\"size\":"+ std::to_string(INDEX_t::__COUNT())+'}';
    }
    template<class O>
    friend inline ojstream<O>& operator << (ojstream<O>& json, const ArrayType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        // json << '[';
        std::string sep;
        for (size_t i=0; i<INDEX_t::__COUNT(); ++i) {
          json << sep << val.data[i]; sep = ",";
        }
        return (json /*<< ']'*/);
#     else
        json << "{\"$type\":\"complex-value\",\"type\":" << ArrayType::__json_type() << ","
                  "\"value\":";
        if (val.IsUndefined())
          return (json << "null}");
        json << '['; std::string sep;
        for (size_t i=0; i<INDEX_t::__COUNT(); ++i) {
          json << sep << val.data[i]; sep = ",";
        }
        return (json << "]}");
#     endif
    }
    friend std::hash<ArrayType>;
  };

  template<typename INDEX_t, typename ELEMENT_t>
  inline ELEMENT_t& Element(ArrayType<INDEX_t,ELEMENT_t>& array, const INDEX_t& index, const location& loc) {
    try {
      return (array[index]);
    } catch (...) {
      throw ModelTypeError("error durring array element access", loc);
    }
  }
  template<typename INDEX_t, typename ELEMENT_t>
  inline const ELEMENT_t& Element(const ArrayType<INDEX_t,ELEMENT_t>& array, const INDEX_t& index, const location& loc) {
    try {
      return (array[index]);
    } catch (...) {
      throw ModelTypeError("error durring array element access", loc);
    }
  }



  template<size_t MAX, typename ELEMENT_t> class MultisetType;

  template<size_t MAX, typename ELEMENT_t>
  inline const ELEMENT_t& MultisetElement(const MultisetType<MAX,ELEMENT_t>& ms, const size_t i, const location& loc);



  template<size_t MAX, typename ELEMENT_t>
  class MultisetType {
    static_assert(MAX != ~((size_t)0u), "multiset is not the same size as the empty option");
    static_assert(MAX != 0, "multiset is not of zero size");
    ELEMENT_t data[MAX];
    size_t occupancy = 0;
    bool is_defined = false;
  public:
    MultisetType() { Undefine(); }

    bool IsUndefined() const { return ((not is_defined) && (occupancy == 0)); }
    void Undefine() { std::memset(&data, 0u, sizeof(data)); occupancy = 0; is_defined = false; } // for now design still allows for setting all to 0 to undefine
    // Do nothing, should never be called, just here for record & array templates
    void Clear() { Undefine(); is_defined = true; }

    static constexpr bool __IS_SIMPLE() { return false; }
    static constexpr bool __IS_RECORD() { return false; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() {
      return ((ELEMENT_t::__DO_P_SEP()) || (MAX>3)
             || (sizeof(ELEMENT_t)>(sizeof(BooleanType)*((ELEMENT_t::__IS_RECORD()) ? 2 : 3))));
    }

    size_t MultisetCount(const std::function<bool(const size_t)>& cond) const {
      size_t count = 0;
      for (size_t i=0; i<occupancy; ++i)
        if (cond(i)) count++;
      return count;
    }
    void MultisetAdd(const ELEMENT_t& val) {
      if (occupancy >= MAX || val.IsUndefined())
        return;
      is_defined = true;
      data[occupancy++] = val;
    }
  protected:
    void MultisetRemove(const size_t i) {
      if (i != occupancy-1) {
        data[i] = data[occupancy-1];
      }
      data[--occupancy].Undefine();
    }
  public:
    void MultisetRemovePred(const std::function<bool(const size_t)>& pred) {
      for (long i=occupancy; i>0; --i)
        if (pred(i-1)) MultisetRemove(i-1);
    }

    // size_t Choose(IRandWalker* __rw__) const {
    //   if (not is_defined || occupancy == 0)
    //     return ~((size_t)0u); // no choice possible value
    //   return __rw__->choose_handler(occupancy);
    // }

    // friend inline const ELEMENT_t& MultisetElement(const MultisetType& ms, const size_t i, const location& loc);
    const ELEMENT_t& operator [] (size_t index) const { return data[index]; }

    template<size_t RM, typename RE>
    friend bool operator == (const MultisetType& l, const MultisetType<RM,RE>& r) {
      if (l.occupancy != r.occupancy) return false; // makes multiplicity matter
      bool res = true;
      size_t found = 0;
      bool matched[MAX];
      for (size_t j=0; j<l.occupancy; ++j) matched[j] = false;
      for (size_t i=0; i<r.occupancy; ++i) {
        for (size_t j=0; j<l.occupancy; ++j) {
          if (r.data[i] == l.data[j] && not matched[j]) {
            matched[j] = true; ++found;
          }
        }
        if (found!=i) return false;
      }
      for (size_t j=0; j<l.occupancy; ++j) res &= matched[j];
      return res;
      /* // rewriting to make multiplicity matter and order not matter
      // if (MAX != RM) return false; // evaluate-able at compile time
      if (l.occupancy != r.occupancy) return false;
      for (size_t i=0; i<l.occupancy; ++i)
        if (l.data[i] != r.data[i])
          return false;
      return true; */
    }
    template< size_t RM, typename RE>
    friend bool operator != (const MultisetType& l, const MultisetType<RM,RE>& r) {
      return not (l == r);
      /* // rewriting to make multiplicity matter and order not matter
      // if (LM != RM) return true; // evaluate-able at compile time
      if (l.occupancy != r.occupancy) return true;
      for (size_t i=0; i<l.occupancy; ++i)
        if (l.data[i] == r.data[i])
          return false;
      return true; */
    }

  protected:
    // write split line if there is a lot of info in data structure
    inline void _pWrite_comp(ostream_p& out) const {
      std::string sep;
      out.indent();
      for (size_t i=0; i<occupancy; ++i) {
        out << sep << out.nl() << data[i]; sep = ",";
      }
      out.dedent();
    }
    // write single line if there is NOT a lot of info in data structure
    inline void _pWrite_simp(ostream_p& out) const {
      std::string sep;
      for (size_t i=0; i<occupancy; ++i) {
        out << sep << data[i]; sep = ", ";
      }
    }
  public:
    static constexpr const std::string __p_type() {
      return "Multiset["+std::to_string(MAX)+"] of " + ELEMENT_t::__p_type();
    }
    // friend inline ostream_p& operator << (ostream_p& out, const MultisetType& val) {
    template<template<size_t,typename>class MS_t>
    friend
    typename std::enable_if<std::is_base_of<MultisetType<MAX,ELEMENT_t>,
                                            MS_t<MAX,ELEMENT_t>>::value,
                            ostream_p>::type& operator << (ostream_p& out, const MS_t<MAX,ELEMENT_t>& val) {
      if (val.IsUndefined()) return (out << SCALAR_ENUM_t::_UNDEFINED_);
      out << '(' << val.occupancy;
      if (ELEMENT_t::__DO_P_SEP() || sizeof(ELEMENT_t)*val.occupancy > sizeof(RangeType<0,1>)*4) {
        val._pWrite_comp(out << "/" << MAX << "){");
        out.nl();
      } else
        val._pWrite_simp(out << "){");
      return (out << '}');
    }
    // template<>
    // friend inline ostream_p& operator << <MultisetType>(ostream_p& out, const MultisetType& val); // {
    static constexpr const std::string __json_type() {
      return "{\"$type\":\"multiset-type\",\"max\":"+std::to_string(MAX)+'}';
    }
    template<class O>
    friend inline ojstream<O>& operator << (ojstream<O>& json, const MultisetType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        if (val.occupancy<=0) return (json << "null");
        json << "{\"multiset\":["; std::string sep;
        for (size_t i=0; i<val.occupancy; ++i) {
          json << sep << '[' << val.data[i] << ']'; sep = ", ";
        }
        return (json << "]}");
#     else
        json << "{\"$type\":\"complex-value\",\"type\":" << MultisetType::__json_type() << ","
              "\"value\":";
        if (val.IsUndefined())
          return (json << "null}");
        json << '['; std::string sep;
        for (size_t i=0; i<val.occupancy; ++i) {
          json << sep << val.data[i]; sep = ",";
        }
        return (json << "]}");
#     endif
    }
    friend std::hash<MultisetType>;
  };

  template<size_t MAX, typename ELEMENT_t>
  inline const ELEMENT_t& MultisetElement(const MultisetType<MAX,ELEMENT_t>& ms, const size_t i, const location& loc) {
    try {
      return ms[i];
    } catch (...) {
      throw ModelTypeError("error during multiset element access", loc);
    }
  }



  template<size_t FID_START, typename... FIELDS>
  class RecordType {
    std::tuple<FIELDS...> data;
  protected:
    template<size_t I>
    static inline constexpr const std::string& _GET_FIELD_NAME() { return ::__info__::RECORD_FIELD_LABELS[FID_START+I]; }
    template<size_t I>
    inline typename std::enable_if<(I>=sizeof...(FIELDS)),bool>::type _IsUndefined() const { return true; }
    template<size_t I>
    inline typename std::enable_if<(I<sizeof...(FIELDS)),bool>::type _IsUndefined() const {
      if (not std::get<I>(data).IsUndefined()) return false;
      return _IsUndefined<I+1>();
    }
    template<size_t I>
    inline typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type _Clear() { return; }
    template<size_t I>
    inline typename std::enable_if<(I<sizeof...(FIELDS)),void>::type _Clear() {
      std::get<I>(data).Clear();
      _Clear<I+1>();
    }
    template<size_t I>
    static inline typename std::enable_if<(I>=sizeof...(FIELDS)),bool>::type _Equal(const RecordType& l, const RecordType& r) { return true; }
    template<size_t I>
    static inline typename std::enable_if<(I<sizeof...(FIELDS)),bool>::type _Equal(const RecordType& l, const RecordType& r) {
      if (std::get<I>(l.data) != std::get<I>(r.data)) return false;
      return _Equal<I+1>(l,r);
    }
    template<size_t I>
    static inline typename std::enable_if<(I>=sizeof...(FIELDS)),bool>::type _NEqual(const RecordType& l, const RecordType& r) { return true; }
    template<size_t I>
    static inline typename std::enable_if<(I<sizeof...(FIELDS)),bool>::type _NEqual(const RecordType& l, const RecordType& r) {
      if (std::get<I>(l.data) == std::get<I>(r.data)) return false;
      return _NEqual<I+1>(l,r);
    }
  public:
    RecordType() { Undefine(); }

    bool IsUndefined() const { return _IsUndefined<0>(); }
    void Undefine() { std::memset(&data, 0u, sizeof(data)); } // for now design still allows for setting all to 0 to undefine
    void Clear() { _Clear<0>(); }

    static constexpr bool __IS_SIMPLE() { return false; }
    static constexpr bool __IS_RECORD() { return true; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() {
// #     if __cplusplus >= 201703L
//         return ((sizeof...(FIELDS)>3) || (FIELDS::__DO_P_SEP() || ...)); // [[requires C++17]]
// #     else
        bool f_p_seps[] = {FIELDS::__DO_P_SEP()...};
        bool res = false;
        for (size_t i=0; i<(sizeof...(FIELDS)); ++i)
          res |= f_p_seps[i];
        return res || (sizeof...(FIELDS)>3);
// #     endif
    }

    template<size_t I>
    typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type& get() {
      throw std::out_of_range("field does not exist in record");
    }
    template<size_t I>
    typename std::enable_if<(I<sizeof...(FIELDS)),typename std::tuple_element<I,std::tuple<FIELDS...>>::type>::type& get() {
      return std::get<I>(data);
    }
    template<size_t I>
    const typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type& get() const {
      throw std::out_of_range("field does not exist in record");
    }
    template<size_t I>
    const typename std::enable_if<(I<sizeof...(FIELDS)),typename std::tuple_element<I,std::tuple<FIELDS...>>::type>::type& get() const {
      return std::get<I>(data);
    }

    // template<size_t O_FID>
    // friend bool operator == (const RecordType& l, const RecordType<O_FID,FIELDS...>& r) { return RecordType::_Equal<0>(l,r); }
    // template<size_t O_FID>
    // friend bool operator != (const RecordType& l, const RecordType<O_FID,FIELDS...>& r) { return RecordType::_NEqual<0>(l,r); }
    template<size_t O_FID>
    friend bool operator == (const RecordType& l, const RecordType<O_FID,FIELDS...>& r) { return l.data == r.data; }
    template<size_t O_FID>
    friend bool operator != (const RecordType& l, const RecordType<O_FID,FIELDS...>& r) { return l.data != r.data; }

  protected:
    template<size_t I>
    typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type _pWrite_comp(ostream_p& out) const { return; }
    template<size_t I=0>
    typename std::enable_if<(I<sizeof...(FIELDS)),void>::type _pWrite_comp(ostream_p& out) const {
      // if (I > 0) out << sep;
      if (__DO_P_SEP() || out.OPTIONS.report_show_type) out.nl();
      if ((not (std::get<I>(data).__IS_RECORD()) || std::get<I>(data).__IS_TYPEID())
          && out.OPTIONS.report_show_type)
        out << _GET_FIELD_NAME<I>() << ": " << std::get<I>(data).__p_type() << " = " << std::get<I>(data) << ';';
      else
        out << _GET_FIELD_NAME<I>() << " := " << std::get<I>(data) << ';';
      _pWrite_comp<I+1>(out);
    }
    template<size_t I>
    typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type _pWrite_simp(ostream_p& out) const { return; }
    template<size_t I=0>
    typename std::enable_if<(I<sizeof...(FIELDS)),void>::type _pWrite_simp(ostream_p& out) const {
      out << _GET_FIELD_NAME<I>() << ": " << std::get<I>(data);
      if (I+1<sizeof...(FIELDS)) out << "; ";
      _pWrite_simp<I+1>(out);
    }
    template<class O, size_t I>
    typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type _jWrite(ojstream<O>& json) const { return; }
    template<class O, size_t I>
    typename std::enable_if<(I<sizeof...(FIELDS)),void>::type _jWrite(ojstream<O>& json) const {
#     ifdef __ROMP__SIMPLE_TRACE
        if (I > 0) json << ',';
        json << std::get<I>(data);
        _jWrite<O,I+1>(json);
#     else
        if (I > 0) json << ',';
        json << "{\"$type\":\"kv-pair\",\"key\":\"" << _GET_FIELD_NAME<I>() << "\","
                  "\"value\":" << std::get<I>(data) << '}';
        _jWrite<O,I+1>(json);
#     endif
    }
  public:
    static constexpr const std::string __p_type() { return "Record"; }
    // friend ostream_p& operator << (ostream_p& out, const RecordType& val) {
    template<template<size_t,typename...>class Rec_t>
    friend
    typename std::enable_if<std::is_base_of<RecordType<FID_START,FIELDS...>,
                                            Rec_t<FID_START,FIELDS...>>::value,
                            ostream_p>::type& operator << (ostream_p& out, const Rec_t<FID_START,FIELDS...>& val) {
      if (val.IsUndefined()) return (out << SCALAR_ENUM_t::_UNDEFINED_);
      if (RecordType::__DO_P_SEP()) {
        out << '{'; // "Record";
        out.indent(); out.indent();
        val._pWrite_comp(out);
        // val._pWrite_comp<0>(out);
        return (out << out.dedent() << out.nl() << '}' /* "EndRecord" */ << out.dedent());
      } else {
        out << "{";
        val._pWrite_simp(out);
        // val._pWrite_simp<0>(out);
        return (out << "}");
      }
    }
    static constexpr std::string __json_type() {
      return "{\"$type\":\"record-type\",\"field-count\":"+std::to_string(sizeof...(FIELDS))+'}';
    }
    template<class O>
    friend inline ojstream<O>& operator << (ojstream<O>& json, const RecordType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        // json << '[';
        val._jWrite<O,0>(json);
        return (json /* << ']' */);
#     else
        json << "{\"$type\":\"complex-value\",\"type-id\":" << RecordType::__json_type() << ","
                  "\"value\":";
        if (val.IsUndefined())
          return (json << "null}");
        json << "[";
        val._jWrite<O,0>(json);
        return (json << "]}");
#     endif
    }
    friend std::hash<RecordType>;
  };





} // namespace romp

namespace __model__ {
  // typedef ::romp::BooleanType Boolean;
  typedef ::romp::BooleanType boolean;
  // typedef ::romp::BooleanType BOOLEAN;
} // namespace __model__

/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file hash.hpp
 *
 * @brief where the hashing objects for the murphi types are defined
 *
 * @date 2023/01/10
 * @version 0.2
 */


#ifndef __romp__GENERATED_CODE
#include "include.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#include "types.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#endif


namespace romp {
  /**
   * @brief Cascade a hash by adding a new value
   * @tparam T the type of the object being added to the hash
   * @param seed the starting value fo a hash or the hash at this stage (modified durring call)
   * @param v the value to hash using std::hash<T>
   */
  template <class T>
  inline void hash_combine(std::size_t& seed, const T& v) {
    // credit: geeks4geeks.com
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

} //namespace romp

namespace std {

template<>
struct hash<::romp::SCALAR_ENUM_t> {
  inline size_t operator () (const ::romp::SCALAR_ENUM_t val) const { return static_cast<size_t>(val); }
};


template<typename T>
struct hash<::romp::BaseUndefinableType<T>> {
  inline size_t operator () (const ::romp::BaseUndefinableType<T>& val) const {
    return static_cast<size_t>(val.value) + 1ul * static_cast<size_t>(val.is_defined);
  }
};


template<size_t TID, class T>
struct hash<::romp::TypeIdType<TID,T>> {
  inline size_t operator () (const ::romp::TypeIdType<TID,T>& val) const {
    return std::hash<T>()(val);
  }
};


template<>
struct hash<::romp::BooleanType> {
  inline size_t operator () (const ::romp::BooleanType& val) const {
    return ((val.IsUndefined()) ? 0ul : static_cast<size_t>(val==true)+1ul);
  }
};


template<::romp::range_t LB, ::romp::range_t UB, ::romp::range_t S>
struct hash<::romp::RangeType<LB,UB,S>> {
  inline size_t operator () (const ::romp::RangeType<LB,UB,S>& val) const {
    return ((val.IsUndefined()) ? 0ul : val.__get_index_val());
  }
};


template<size_t EID, size_t B>
struct hash<::romp::EnumType<EID,B>> {
  inline size_t operator () (const ::romp::EnumType<EID,B>& val) const {
    return static_cast<size_t>(val.__get_scalar_value()); // same as SCALAR_ENUM_t that is it's only stored data
  }
};

template<size_t EID, size_t B>
struct hash<::romp::ScalarsetType<EID,B>> {
  inline size_t operator () (const ::romp::ScalarsetType<EID,B>& val) const {
    return static_cast<size_t>(val.__get_scalar_value()); // same as SCALAR_ENUM_t that is it's only stored data
  }
};


template<class... MEM>
struct hash<::romp::ScalarsetUnionType<MEM...>> {
  inline size_t operator () (const ::romp::ScalarsetUnionType<MEM...>& val) const {
    return static_cast<size_t>(val.__get_scalar_value()); // same as SCALAR_ENUM_t that is it's only stored data
  }
};


template<typename I_t, typename E_t>
struct hash<::romp::ArrayType<I_t,E_t>> {
  inline size_t operator () (const ::romp::ArrayType<I_t,E_t>& val) const {
    size_t _hash = 0ul;
    for (size_t i=0; i<I_t::__COUNT(); ++i)
      ::romp::hash_combine(_hash,val.data[i]);
    return _hash;
  }
};


template<size_t M, typename E_t>
struct hash<::romp::MultisetType<M,E_t>> {
  // credit: Alex Reinking (https://stackoverflow.com/users/2137996/alex-reinking)
  // from: https://stackoverflow.com/questions/36520235/algorithm-for-hash-crc-of-unordered-multiset
  inline size_t operator () (const ::romp::MultisetType<M,E_t>& val) const {
    size_t _h = 0ul;
    std::hash<E_t> _hash;
    for (size_t i=0; i<val.occupancy; ++i)
      _h += log_pow(_hash(val.data[i]));
    return _h % UINT64_MAX;
  }
  size_t log_pow(size_t ex) const {
    size_t res = 1;
    size_t base = 0xA67; // set base to a reasonably large prime
    while (ex > 0) {
        if (ex % 2)
            res = res * base;
        base *= base;
        ex /= 2;
    }
    return res;
   }
};


template<size_t FID, typename... FIELDS>
struct hash<::romp::RecordType<FID,FIELDS...>> {
  inline size_t operator () (const ::romp::RecordType<FID,FIELDS...>& val) const {
    // return std::hash<tuple<FIELDS...>>()(val);
    size_t _h = 0ul; return _hash(val,_h);
  }
protected:
  template<size_t I>
  typename std::enable_if<(I>=sizeof...(FIELDS)),size_t>::type _hash(const ::romp::RecordType<FID,FIELDS...>& val, size_t _h) const { return _h; }
  template<size_t I=0>
  typename std::enable_if<(I<sizeof...(FIELDS)),size_t>::type _hash(const ::romp::RecordType<FID,FIELDS...>& val, size_t _h) const {
    ::romp::hash_combine(_h,std::get<I>(val.data));
    return _hash<I+1>(val,_h);
  }
};


/* // defined in bfs.hpp for orderings sake
template<>
struct hash<::romp::State_t> {
  inline size_t operator () (const ::romp::State_t& state) const {
    return state.__romp__model_hash();
  }
};
*/


} //namespace std


#pragma endregion romp_infix



#pragma region model__generated_code

namespace __model__ {
struct __romp__Model__ {

  ::romp::IRandWalker* __rw__; // pointer to associated romp rand walker

  //---------------------------------------------------------------------------
  // Murphi code for the locking protocol
  // Author : Ganesh Gopalakrishnan, written circa year 2000
  // Derived from Dilip Khandekar and John Carter's work
  // Compare against Promela model studied in Asg3, CS 6110, Spring 2022
  //---------------------------------------------------------------------------
  // begin of locking.m --
  const ::romp::range_t Nprocs = ((::romp::range_t)(6)); // >= 2 reqd to satisfy request_bufT type declaration.

  //-----------------------------------------------------
  typedef ::romp::TypeIdType<0,::romp::ScalarsetType<1,(/*Nprocs*/(6))>> procT;

  typedef ::romp::TypeIdType<1,::romp::RecordType<0,/*Ar*/::romp::ArrayType<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>,/*Count*/::romp::RangeType<(/*((-1))*/(-1)),(/*((Nprocs - 2))*/(4))>>> request_bufT;

  // legal range is 0..Nprocs-2
  // -1 acts as empty indicator
  /* With Nprocs=1, we get 0..-1 which makes sense
   mathematically (empty) but perhaps not in Murphi.
   So, avoid Nprocs <= 1. Similar caveats apply for
   all array declarations of the form 0..N-2. */
  typedef ::romp::TypeIdType<2,::romp::EnumType<(/*ENTER*/7),(5)>> stateT;

  typedef ::romp::TypeIdType<3,::romp::EnumType<(/*HANDLE*/12),(2)>> hstateT;

  //-----------------------------------------------------
  ::romp::ArrayType<procT,request_bufT> request_bufs;

  ::romp::ArrayType<procT,procT> prob_owners;

  ::romp::ArrayType<procT,request_bufT> waiters;

  ::romp::ArrayType<procT,boolean> mutexes;

  ::romp::ArrayType<procT,stateT> ar_states;

  ::romp::ArrayType<procT,hstateT> hstates;

  //-----------------------------------------------------

  void initq(request_bufT& queue)  {
    try {
      // queue of Array range 0..Nprocs-2
      for (auto i=::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>::__LB(); i!=::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>::__UB(); i.__step()) {
        // Undefine queue.Ar[i];
        ((::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((queue).get</*Ar*/0>()), (i), ::romp::location{{49,11},{49,22}}))).Undefine();
      }

      // queue.Count := (-1); // empty queue
      ::romp::Assignment<::romp::RangeType<(/*((-1))*/(-1)),(/*((Nprocs - 2))*/(4))>>(((queue).get</*Count*/1>()), (-((::romp::range_t)(1))), ::romp::location{{51,3},{51,20}});
    } catch (...) { throw ::romp::ModelFunctError(0); }
}


  procT frontq(const request_bufT queue)  {
    try {
      // queue of Array range 0..Nprocs-2
      if (((queue).get</*Count*/1>()) < ((::romp::range_t)(0))) {
        if (this->__rw__->error_handler(0u))
          throw ::romp::ModelMErrorError(0);

      } else {
        return ((::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((queue).get</*Ar*/0>()), ((::romp::range_t)(0)), ::romp::location{{59,15},{59,26}})));
      }
    } catch (...) { throw ::romp::ModelFunctError(1); }
}


  boolean nonemptyq(const request_bufT queue) const  {
    try {
      return ((((queue).get</*Count*/1>()) >= ((::romp::range_t)(0))));
    } catch (...) { throw ::romp::ModelFunctError(2); }
}


  boolean emptyq(const request_bufT queue)  {
    try {
      if (((queue).get</*Count*/1>()) < (-((::romp::range_t)(1)))) {
        if (this->__rw__->error_handler(1u))
          throw ::romp::ModelMErrorError(1);

      } else {
        return ((((queue).get</*Count*/1>()) == (-((::romp::range_t)(1)))));
      }
    } catch (...) { throw ::romp::ModelFunctError(3); }
}


  void dequeue(request_bufT& queue)  {
    try {
      // queue of Array range 0..Nprocs-2
      if (((queue).get</*Count*/1>()) == (-((::romp::range_t)(1)))) {
        if (this->__rw__->error_handler(2u))
          throw ::romp::ModelMErrorError(2);

      } else {
        // queue.Count := (queue.Count - 1);
        ::romp::Assignment<::romp::RangeType<(/*((-1))*/(-1)),(/*((Nprocs - 2))*/(4))>>(((queue).get</*Count*/1>()), (((queue).get</*Count*/1>()) - ((::romp::range_t)(1))), ::romp::location{{81,7},{81,37}});
        if (((queue).get</*Count*/1>()) == (-((::romp::range_t)(1)))) {
          // Undefine queue.Ar[0];
          ((::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((queue).get</*Ar*/0>()), ((::romp::range_t)(0)), ::romp::location{{83,21},{83,32}}))).Undefine();
        } else {
          for (romp::range_t i=((::romp::range_t)(0)); (((1)>0) ? (i<=((queue).get</*Count*/1>())) : (i>=((queue).get</*Count*/1>()))); i += 1) {
            // queue.Ar[i] := queue.Ar[(i + 1)];
            ::romp::Assignment<procT>((::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((queue).get</*Ar*/0>()), (i), ::romp::location{{85,7},{85,18}})), (::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((queue).get</*Ar*/0>()), ((i) + ((::romp::range_t)(1))), ::romp::location{{85,22},{85,35}})), ::romp::location{{85,7},{85,35}});
          }

          // Undefine queue.Ar[(queue.Count + 1)];
          ((::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((queue).get</*Ar*/0>()), (((queue).get</*Count*/1>()) + ((::romp::range_t)(1))), ::romp::location{{87,21},{87,44}}))).Undefine();
        }
      }
    } catch (...) { throw ::romp::ModelFunctError(4); }
}


  void enqueue(request_bufT& queue, const procT pid)  {
    try {
      // queue of Array range 0..Nprocs-2
      if (((queue).get</*Count*/1>()) == ((Nprocs) - ((::romp::range_t)(2)))) {
        if (this->__rw__->error_handler(3u))
          throw ::romp::ModelMErrorError(3);

      } else {
        // queue.Count := (queue.Count + 1);
        ::romp::Assignment<::romp::RangeType<(/*((-1))*/(-1)),(/*((Nprocs - 2))*/(4))>>(((queue).get</*Count*/1>()), (((queue).get</*Count*/1>()) + ((::romp::range_t)(1))), ::romp::location{{97,8},{97,38}});
        // queue.Ar[queue.Count] := pid;
        ::romp::Assignment<procT>((::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((queue).get</*Ar*/0>()), ((queue).get</*Count*/1>()), ::romp::location{{98,9},{98,30}})), (pid), ::romp::location{{98,9},{98,37}});
      }
    } catch (...) { throw ::romp::ModelFunctError(5); }
}

  //-----------------------------------------------------

  void place_request(const procT prob_owner, const procT p)  {
    try {
      enqueue((::romp::Element<procT,request_bufT>((request_bufs), (prob_owner), ::romp::location{{106,10},{106,34}})), (p));
    } catch (...) { throw ::romp::ModelFunctError(6); }
}


  void copytail(request_bufT& source_queue, request_bufT& destination_queue)  {
    try {
      /* Called only when source_queue is non_empty, i.e. source_queue.Count >= 0.
       Copies the tail of the queue "source_queue" into
       "destination_queue" (which, in actual use, happens to be
       at the new prob_owner),  and also undefines "source_queue" and
       the unused locations of "destination_queue" (at the new probable owner).
       If source_queue.Count = 0, there is no tail to be copied, and we are done.
       */
      if (((source_queue).get</*Count*/1>()) > ((::romp::range_t)(0))) {
        // non-empty and has >= 1 element
        for (romp::range_t i=((::romp::range_t)(1)); (((1)>0) ? (i<=((source_queue).get</*Count*/1>())) : (i>=((source_queue).get</*Count*/1>()))); i += 1) {
          // destination_queue.Ar[(i - 1)] := source_queue.Ar[i];
          ::romp::Assignment<procT>((::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((destination_queue).get</*Ar*/0>()), ((i) - ((::romp::range_t)(1))), ::romp::location{{121,6},{121,31}})), (::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((source_queue).get</*Ar*/0>()), (i), ::romp::location{{121,35},{121,53}})), ::romp::location{{121,6},{121,53}});
          // Undefine source_queue.Ar[i];
          ((::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((source_queue).get</*Ar*/0>()), (i), ::romp::location{{122,12},{122,30}}))).Undefine();
        }

        // destination_queue.Count := (source_queue.Count - 1);
        ::romp::Assignment<::romp::RangeType<(/*((-1))*/(-1)),(/*((Nprocs - 2))*/(4))>>(((destination_queue).get</*Count*/1>()), (((source_queue).get</*Count*/1>()) - ((::romp::range_t)(1))), ::romp::location{{124,5},{124,54}});
        // Undefine destination_queue.Ar[source_queue.Count];
        ((::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((destination_queue).get</*Ar*/0>()), ((source_queue).get</*Count*/1>()), ::romp::location{{125,14},{125,54}}))).Undefine();
        // Undefine source_queue.Ar[0];
        ((::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((source_queue).get</*Ar*/0>()), ((::romp::range_t)(0)), ::romp::location{{126,14},{126,32}}))).Undefine();
        // source_queue.Count := (-1);
        ::romp::Assignment<::romp::RangeType<(/*((-1))*/(-1)),(/*((Nprocs - 2))*/(4))>>(((source_queue).get</*Count*/1>()), (-((::romp::range_t)(1))), ::romp::location{{127,12},{127,36}});
      } else {
        // Undefine source_queue.Ar[0];
        ((::romp::Element<::romp::RangeType<(/*(0)*/(0)),(/*((Nprocs - 2))*/(4))>,procT>(((source_queue).get</*Ar*/0>()), ((::romp::range_t)(0)), ::romp::location{{129,15},{129,33}}))).Undefine();
        // source_queue.Count := (-1);
        ::romp::Assignment<::romp::RangeType<(/*((-1))*/(-1)),(/*((Nprocs - 2))*/(4))>>(((source_queue).get</*Count*/1>()), (-((::romp::range_t)(1))), ::romp::location{{130,12},{130,36}});
      }
    } catch (...) { throw ::romp::ModelFunctError(7); }
}

  //-----------------------------------------------------

  bool __romp__Rule_guard__Try_acquiring_the_lock(const procT p) const {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      return (((state()) == (ENTER)) && (!(mutex())));
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(0,::romp::ModelRuleError::GUARD); }
  }


  void __romp__Rule_action__Try_acquiring_the_lock(const procT p) {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      // mutex := true;
      ::romp::Assignment<boolean>((mutex()), (true), ::romp::location{{146,8},{146,21}});
      // state := TRYING;
      ::romp::Assignment<stateT>((state()), (TRYING), ::romp::location{{147,8},{147,23}});
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(0,::romp::ModelRuleError::ACTION); }
  }


  bool __romp__Rule_guard__If_the_lock_is_around__grab_it(const procT p) const {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      return ((((state()) == (TRYING)) && ((prob_owner()) == (p))) && (mutex()));
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(1,::romp::ModelRuleError::GUARD); }
  }


  void __romp__Rule_action__If_the_lock_is_around__grab_it(const procT p) {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      //-----------------------------------------------------
      // mutex := false;
      ::romp::Assignment<boolean>((mutex()), (false), ::romp::location{{153,8},{153,22}});
      // state := LOCKED;
      ::romp::Assignment<stateT>((state()), (LOCKED), ::romp::location{{154,29},{154,44}});
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(1,::romp::ModelRuleError::ACTION); }
  }


  bool __romp__Rule_guard__If_the_lock_isn_t_around__send_request_out(const procT p) const {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      return ((((state()) == (TRYING)) && ((prob_owner()) != (p))) && (mutex()));
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(2,::romp::ModelRuleError::GUARD); }
  }


  void __romp__Rule_action__If_the_lock_isn_t_around__send_request_out(const procT p) {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      //-----------------------------------------------------
      // mutex := false;
      ::romp::Assignment<boolean>((mutex()), (false), ::romp::location{{161,8},{161,22}});
      place_request((prob_owner()), (p));
      // state := BLOCKED;
      ::romp::Assignment<stateT>((state()), (BLOCKED), ::romp::location{{163,8},{163,24}});
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(2,::romp::ModelRuleError::ACTION); }
  }


  bool __romp__Rule_guard__Locked____Enter_if_no_waiters(const procT p) const {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      return (((state()) == (LOCKED)) && emptyq((waiter())));
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(3,::romp::ModelRuleError::GUARD); }
  }


  void __romp__Rule_action__Locked____Enter_if_no_waiters(const procT p) {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      //-----------------------------------------------------
      // state := ENTER;
      ::romp::Assignment<stateT>((state()), (ENTER), ::romp::location{{168,43},{168,57}});
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(3,::romp::ModelRuleError::ACTION); }
  }


  bool __romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(const procT p) const {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      return ((((state()) == (LOCKED)) && (!emptyq((waiter())))) && (!(mutex())));
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(4,::romp::ModelRuleError::GUARD); }
  }


  void __romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(const procT p) {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      //-----------------------------------------------------
      // mutex := true;
      ::romp::Assignment<boolean>((mutex()), (true), ::romp::location{{174,8},{174,21}});
      // state := EXITING;
      ::romp::Assignment<stateT>((state()), (EXITING), ::romp::location{{175,11},{175,27}});
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(4,::romp::ModelRuleError::ACTION); }
  }


  bool __romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(const procT p) const {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      return ((((state()) == (EXITING)) && (!emptyq((waiter())))) && (mutex()));
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(5,::romp::ModelRuleError::GUARD); }
  }


  void __romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(const procT p) {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      //-----------------------------------------------------
      // added emptyq check for waiter
      // mutex := false;
      ::romp::Assignment<boolean>((mutex()), (false), ::romp::location{{182,10},{182,24}});
      // set the PO variable at node frontq(waiters) and
      // also our own PO variable to frontq(waiters)
      // the former step unblocks node frontq(waiters),
      // giving it the lock
      // prob_owners[frontq(waiter)] := frontq(waiter);
      ::romp::Assignment<procT>((::romp::Element<procT,procT>((prob_owners), frontq((waiter())), ::romp::location{{187,17},{187,44}})), frontq((waiter())), ::romp::location{{187,17},{187,62}});
      // prob_owner := frontq(waiter);
      ::romp::Assignment<procT>((prob_owner()), frontq((waiter())), ::romp::location{{188,13},{188,41}});
      // added this new line to update the state of acquire's thread state when passing the lock
      // ar_states[frontq(waiter)] := LOCKED;
      ::romp::Assignment<stateT>((::romp::Element<procT,stateT>((ar_states), frontq((waiter())), ::romp::location{{191,10},{191,35}})), (LOCKED), ::romp::location{{191,10},{191,45}});
      copytail((waiter()), (::romp::Element<procT,request_bufT>((waiters), (prob_owner()), ::romp::location{{193,27},{193,46}})));
      // state := ENTER;
      ::romp::Assignment<stateT>((state()), (ENTER), ::romp::location{{194,10},{194,24}});
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(5,::romp::ModelRuleError::ACTION); }
  }


  bool __romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(const procT p) const {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      return ((((hstate()) == (HANDLE)) && (!emptyq((request_buf())))) && (!(mutex())));
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(6,::romp::ModelRuleError::GUARD); }
  }


  void __romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(const procT p) {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      //-----------------------------------------------------
      // GG : 3/23/23 : did not see a need for this rule
      // added this new rule which will get fired when there are no waiters in the queue
      // Rule "In EXITING state, release the lock if no waiters."
      //        ((state = EXITING) & emptyq(waiter) & mutex)
      //                ==>
      //                    state := ENTER;
      //                    mutex := false;
      // Endrule;
      //-----------------------------------------------------
      // mutex := true;
      ::romp::Assignment<boolean>((mutex()), (true), ::romp::location{{211,8},{211,21}});
      // hstate := TRYGRANT;
      ::romp::Assignment<hstateT>((hstate()), (TRYGRANT), ::romp::location{{212,11},{212,29}});
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(6,::romp::ModelRuleError::ACTION); }
  }


  bool __romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it_(const procT p) const {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      return (((((hstate()) == (TRYGRANT)) && ((prob_owner()) == (p))) && ((state()) != (LOCKED))) && (mutex()));
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(7,::romp::ModelRuleError::GUARD); }
  }


  void __romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it_(const procT p) {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      //-----------------------------------------------------
      // mutex := false;
      ::romp::Assignment<boolean>((mutex()), (false), ::romp::location{{220,23},{220,37}});
      //if ((state != ENTER) | (state != EXITING))
      //then Error
      //   "State can't be TRYING/LOCKED/EXIT(due to mutex) or BLOCKED (due to prob_owner)"
      //else
      if ((!emptyq((waiter())))) {
        if (this->__rw__->error_handler(4u))
          throw ::romp::ModelMErrorError(4);

      } else {
        // this step will unblock process hd(request_buf) effectively giving it the lock
        // prob_owners[frontq(request_buf)] := frontq(request_buf);
        ::romp::Assignment<procT>((::romp::Element<procT,procT>((prob_owners), frontq((request_buf())), ::romp::location{{232,8},{232,40}})), frontq((request_buf())), ::romp::location{{232,8},{232,63}});
        // ar_states[frontq(request_buf)] := LOCKED;
        ::romp::Assignment<stateT>((::romp::Element<procT,stateT>((ar_states), frontq((request_buf())), ::romp::location{{233,8},{233,38}})), (LOCKED), ::romp::location{{233,8},{233,48}});
        // prob_owner := frontq(request_buf);
        ::romp::Assignment<procT>((prob_owner()), frontq((request_buf())), ::romp::location{{235,11},{235,44}});
        dequeue((request_buf()));
        // hstate := HANDLE;
        ::romp::Assignment<hstateT>((hstate()), (HANDLE), ::romp::location{{238,11},{238,27}});
      }
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(7,::romp::ModelRuleError::ACTION); }
  }


  bool __romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(const procT p) const {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      return (((((hstate()) == (TRYGRANT)) && (!emptyq((request_buf())))) && ((prob_owner()) != (p))) && (mutex()));
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(8,::romp::ModelRuleError::GUARD); }
  }


  void __romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(const procT p) {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      //-----------------------------------------------------
      // mutex := false;
      ::romp::Assignment<boolean>((mutex()), (false), ::romp::location{{248,8},{248,22}});
      place_request((prob_owner()), frontq((request_buf())));
      dequeue((request_buf()));
      // hstate := HANDLE;
      ::romp::Assignment<hstateT>((hstate()), (HANDLE), ::romp::location{{251,11},{251,27}});
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(8,::romp::ModelRuleError::ACTION); }
  }


  bool __romp__Rule_guard__If_lock_around_but_busy__enqueue_request(const procT p) const {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      return (((((hstate()) == (TRYGRANT)) && ((prob_owner()) == (p))) && ((state()) == (LOCKED))) && (mutex()));
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(9,::romp::ModelRuleError::GUARD); }
  }


  void __romp__Rule_action__If_lock_around_but_busy__enqueue_request(const procT p) {
    try {
#define request_buf() (::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{137,25},{137,40}}))
#define prob_owner() (::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{138,24},{138,38}}))
#define waiter() (::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{139,23},{139,33}}))
#define state() (::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{140,22},{140,34}}))
#define hstate() (::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{141,23},{141,33}}))
#define mutex() (::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{142,22},{142,32}}))
      //-----------------------------------------------------
      // mutex := false;
      ::romp::Assignment<boolean>((mutex()), (false), ::romp::location{{259,8},{259,22}});
      enqueue((waiter()), frontq((request_buf())));
      dequeue((request_buf()));
      // hstate := HANDLE;
      ::romp::Assignment<hstateT>((hstate()), (HANDLE), ::romp::location{{262,11},{262,27}});
#undef request_buf
#undef prob_owner
#undef waiter
#undef state
#undef hstate
#undef mutex
    } catch (...) { throw ::romp::ModelRuleError(9,::romp::ModelRuleError::ACTION); }
  }

  //-----------------------------------------------------
  //-----------------------------------------------------
   void __romp__StartState__startstate8(const procT n){
    try {
      for (auto p=procT::__LB(); p!=procT::__UB(); p.__step()) {
        initq((::romp::Element<procT,request_bufT>((request_bufs), (p), ::romp::location{{280,11},{280,26}})));
        // prob_owners[p] := n; // designate some n in procT  to be the owner
        ::romp::Assignment<procT>((::romp::Element<procT,procT>((prob_owners), (p), ::romp::location{{281,5},{281,19}})), (n), ::romp::location{{281,5},{281,24}});
        initq((::romp::Element<procT,request_bufT>((waiters), (p), ::romp::location{{282,11},{282,21}})));
        // ar_states[p] := ENTER;
        ::romp::Assignment<stateT>((::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{283,5},{283,17}})), (ENTER), ::romp::location{{283,5},{283,26}});
        // hstates[p] := HANDLE;
        ::romp::Assignment<hstateT>((::romp::Element<procT,hstateT>((hstates), (p), ::romp::location{{284,5},{284,15}})), (HANDLE), ::romp::location{{284,5},{284,25}});
        // mutexes[p] := false;
        ::romp::Assignment<boolean>((::romp::Element<procT,boolean>((mutexes), (p), ::romp::location{{285,5},{285,15}})), (false), ::romp::location{{285,5},{285,24}});
      }

    } catch (...) { throw ::romp::ModelStartStateError(0); }
  }


  //-----------------------------------------------------
  // Due to symmetry, we key-off "n"

  bool __romp__Property__property9(void) const {
    try {
      return this->__rw__->invariant_handler(({ bool res_ = false; for (auto n=procT::__LB(); n!=procT::__UB(); n.__step()) { res_ |= (!((::romp::Element<procT,stateT>((ar_states), (n), ::romp::location{{295,4},{295,16}})) == (LOCKED)) || ({bool res_ = true; for (auto p=procT::__LB(); p!=procT::__UB(); p.__step()) { res_ &= (((p) == (n)) || ((::romp::Element<procT,stateT>((ar_states), (p), ::romp::location{{297,14},{297,26}})) != (LOCKED))); } res_; })); } res_; }),0u);
    } catch (...) { throw ::romp::ModelPropertyError(0); }
  }


  friend ::romp::ostream_p& operator << (::romp::ostream_p& out, const ::__model__::__romp__Model__& s) {
     return (out << '{' << out._indent() << out.nl()
         << "request_bufs" << ((((not s.request_bufs.__IS_RECORD())||(s.request_bufs.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.request_bufs.__p_type() + " = " : " := ") << s.request_bufs << ';' << out.nl()
         << "prob_owners" << ((((not s.prob_owners.__IS_RECORD())||(s.prob_owners.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.prob_owners.__p_type() + " = " : " := ") << s.prob_owners << ';' << out.nl()
         << "waiters" << ((((not s.waiters.__IS_RECORD())||(s.waiters.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.waiters.__p_type() + " = " : " := ") << s.waiters << ';' << out.nl()
         << "mutexes" << ((((not s.mutexes.__IS_RECORD())||(s.mutexes.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.mutexes.__p_type() + " = " : " := ") << s.mutexes << ';' << out.nl()
         << "ar_states" << ((((not s.ar_states.__IS_RECORD())||(s.ar_states.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.ar_states.__p_type() + " = " : " := ") << s.ar_states << ';' << out.nl()
         << "hstates" << ((((not s.hstates.__IS_RECORD())||(s.hstates.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.hstates.__p_type() + " = " : " := ") << s.hstates << ';'
        << out.dedent() << out.nl() << '}');  }
  friend ::std::ostream& operator << (::std::ostream& out_, const ::__model__::__romp__Model__& s) { ::romp::ostream_p out(out_,::romp::Options(),2); out << s; return out_; }

#ifdef __ROMP__SIMPLE_TRACE
  template<class O> friend ::romp::ojstream<O>& operator << (::romp::ojstream<O>& json, const ::__model__::__romp__Model__& s) { return (json << '['  << s.request_bufs << ',' << s.prob_owners << ',' << s.waiters << ',' << s.mutexes << ',' << s.ar_states << ',' << s.hstates << ']'); }
#else
  template<class O> friend ::romp::ojstream<O>& operator << (::romp::ojstream<O>& json, const ::__model__::__romp__Model__& s) { return (json << "{\"$type\":\"model-state\",\"value\":[" << "{\"$type\":\"kv-pair\",\"key\":\"request_bufs\",\"value\":" << s.request_bufs << '}' << ',' << "{\"$type\":\"kv-pair\",\"key\":\"prob_owners\",\"value\":" << s.prob_owners << '}' << ',' << "{\"$type\":\"kv-pair\",\"key\":\"waiters\",\"value\":" << s.waiters << '}' << ',' << "{\"$type\":\"kv-pair\",\"key\":\"mutexes\",\"value\":" << s.mutexes << '}' << ',' << "{\"$type\":\"kv-pair\",\"key\":\"ar_states\",\"value\":" << s.ar_states << '}' << ',' << "{\"$type\":\"kv-pair\",\"key\":\"hstates\",\"value\":" << s.hstates << '}' << "]}"); }
#endif

  inline size_t __romp__model_hash() const {
    size_t _hash = 0ul;
    ::romp::hash_combine(_hash, request_bufs);
    ::romp::hash_combine(_hash, prob_owners);
    ::romp::hash_combine(_hash, waiters);
    ::romp::hash_combine(_hash, mutexes);
    ::romp::hash_combine(_hash, ar_states);
    ::romp::hash_combine(_hash, hstates);
    return _hash;
  }

  friend inline bool operator == (const ::__model__::__romp__Model__& l, const ::__model__::__romp__Model__& r) {
    return (    l.request_bufs == r.request_bufs &&
    l.prob_owners == r.prob_owners &&
    l.waiters == r.waiters &&
    l.mutexes == r.mutexes &&
    l.ar_states == r.ar_states &&
    l.hstates == r.hstates);
  }


};


} // namespace __model__


#pragma endregion model__generated_code



#pragma region metadata__generated_code

namespace __info__ {
/* the number possible variations in the state (# of permutations of the state-space) */
#define _ROMP_STATESPACE_COUNT_str "317670951548474763611435515181222752405841374225069765583437824000000"
  const std::string TYPE_IDS[] = {"procT","request_bufT","stateT","hstateT"};
  const std::string RECORD_FIELD_LABELS[] = {"Ar","Count"};
  const ::romp::RuleInfo RULE_SET_INFOS[] = {{"Try_acquiring_the_lock",::romp::location{{144,6},{148,9}},"{\"$type\":\"rule\",\"expr\":\"((state = ENTER) & (!mutex))\",\"label\":\"Try_acquiring_the_lock\",\"loc\":{\"$type\":\"location\",\"start\":[144,6],\"end\":[148,9]}"},{"If_the_lock_is_around__grab_it",::romp::location{{151,6},{156,9}},"{\"$type\":\"rule\",\"expr\":\"(((state = TRYING) & (prob_owner = p)) & mutex)\",\"label\":\"If_the_lock_is_around__grab_it\",\"loc\":{\"$type\":\"location\",\"start\":[151,6],\"end\":[156,9]}"},{"If_the_lock_isn_t_around__send_request_out",::romp::location{{159,6},{164,9}},"{\"$type\":\"rule\",\"expr\":\"(((state = TRYING) & (prob_owner != p)) & mutex)\",\"label\":\"If_the_lock_isn_t_around__send_request_out\",\"loc\":{\"$type\":\"location\",\"start\":[159,6],\"end\":[164,9]}"},{"Locked____Enter_if_no_waiters",::romp::location{{167,2},{169,9}},"{\"$type\":\"rule\",\"expr\":\"((state = LOCKED) & emptyq(waiter))\",\"label\":\"Locked____Enter_if_no_waiters\",\"loc\":{\"$type\":\"location\",\"start\":[167,2],\"end\":[169,9]}"},{"When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state",::romp::location{{172,6},{176,9}},"{\"$type\":\"rule\",\"expr\":\"(((state = LOCKED) & (!emptyq(waiter))) & (!mutex))\",\"label\":\"When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state\",\"loc\":{\"$type\":\"location\",\"start\":[172,6],\"end\":[176,9]}"},{"In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_",::romp::location{{180,6},{196,9}},"{\"$type\":\"rule\",\"expr\":\"(((state = EXITING) & (!emptyq(waiter))) & mutex)\",\"label\":\"In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_\",\"loc\":{\"$type\":\"location\",\"start\":[180,6],\"end\":[196,9]}"},{"In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT",::romp::location{{209,6},{213,9}},"{\"$type\":\"rule\",\"expr\":\"(((hstate = HANDLE) & (!emptyq(request_buf))) & (!mutex))\",\"label\":\"In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT\",\"loc\":{\"$type\":\"location\",\"start\":[209,6],\"end\":[213,9]}"},{"In_state_TRYGRANT__if_lock_is_free__grant_it_",::romp::location{{217,7},{242,9}},"{\"$type\":\"rule\",\"expr\":\"((((hstate = TRYGRANT) & (prob_owner = p)) & (state != LOCKED)) & mutex)\",\"label\":\"In_state_TRYGRANT__if_lock_is_free__grant_it_\",\"loc\":{\"$type\":\"location\",\"start\":[217,7],\"end\":[242,9]}"},{"If_lock_not_around__pass_buck_along_to_who_we_think_is_PO",::romp::location{{246,6},{253,9}},"{\"$type\":\"rule\",\"expr\":\"((((hstate = TRYGRANT) & (!emptyq(request_buf))) & (prob_owner != p)) & mutex)\",\"label\":\"If_lock_not_around__pass_buck_along_to_who_we_think_is_PO\",\"loc\":{\"$type\":\"location\",\"start\":[246,6],\"end\":[253,9]}"},{"If_lock_around_but_busy__enqueue_request",::romp::location{{257,6},{264,9}},"{\"$type\":\"rule\",\"expr\":\"((((hstate = TRYGRANT) & (prob_owner = p)) & (state = LOCKED)) & mutex)\",\"label\":\"If_lock_around_but_busy__enqueue_request\",\"loc\":{\"$type\":\"location\",\"start\":[257,6],\"end\":[264,9]}"},};
  const ::romp::PropertyInfo PROPERTY_INFOS[] = {{"property9",::romp::PropertyType::INVARIANT,"exists n : procT do ((ar_states[n] = LOCKED) -> forall p : procT do ((p = n) | (ar_states[p] != LOCKED)) endforall) endexists",4294967295,::romp::location{{293,1},{300,10}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"exists n : procT do ((ar_states[n] = LOCKED) -> forall p : procT do ((p = n) | (ar_states[p] != LOCKED)) endforall) endexists\",\"label\":\"property9\",\"loc\":{\"$type\":\"location\",\"start\":[293,1],\"end\":[300,10]}"},};
/* the number of cover property statements & rules in the model */
#define _ROMP_COVER_PROP_COUNT (0ul)
/* the number of liveness property rules in the model */
#define _ROMP_LIVENESS_PROP_COUNT (0ul)

  const ::romp::PropertyInfo* LIVENESS_INFOS[_ROMP_LIVENESS_PROP_COUNT] = {};
  const ::romp::PropertyInfo* COVER_INFOS[_ROMP_COVER_PROP_COUNT] = {};

  const ::romp::StartStateInfo STARTSTATE_INFOS[] = {{"startstate8",::romp::location{{278,1},{287,14}},"{\"$type\":\"startstate\",\"label\":\"startstate8\",\"loc\":{\"$type\":\"location\",\"start\":[278,1],\"end\":[287,14]}"},};
  const ::romp::FunctInfo FUNCT_INFOS[] = {{"initq",::romp::location{{45,1},{52,5}},"{\"$type\":\"procedure\",\"label\":\"initq\",\"params\":[{\"$type\":\"param\",\"id\":\"queue\",\"type\":\"request_bufT\"}],\"loc\":{\"$type\":\"location\",\"start\":[45,1],\"end\":[52,5]}}","procedure initq(queue: request_bufT);"},{"frontq",::romp::location{{54,1},{61,5}},"{\"$type\":\"function\",\"return-type\":\"procT\",\"label\":\"frontq\",\"params\":[{\"$type\":\"param\",\"id\":\"queue\",\"type\":\"request_bufT\"}],\"loc\":{\"$type\":\"location\",\"start\":[54,1],\"end\":[61,5]}}","function frontq(var queue: request_bufT) : procT;"},{"nonemptyq",::romp::location{{63,1},{66,5}},"{\"$type\":\"function\",\"return-type\":\"boolean\",\"label\":\"nonemptyq\",\"params\":[{\"$type\":\"param\",\"id\":\"queue\",\"type\":\"request_bufT\"}],\"loc\":{\"$type\":\"location\",\"start\":[63,1],\"end\":[66,5]}}","function nonemptyq(var queue: request_bufT) : boolean;"},{"emptyq",::romp::location{{68,1},{74,5}},"{\"$type\":\"function\",\"return-type\":\"boolean\",\"label\":\"emptyq\",\"params\":[{\"$type\":\"param\",\"id\":\"queue\",\"type\":\"request_bufT\"}],\"loc\":{\"$type\":\"location\",\"start\":[68,1],\"end\":[74,5]}}","function emptyq(var queue: request_bufT) : boolean;"},{"dequeue",::romp::location{{76,1},{90,5}},"{\"$type\":\"procedure\",\"label\":\"dequeue\",\"params\":[{\"$type\":\"param\",\"id\":\"queue\",\"type\":\"request_bufT\"}],\"loc\":{\"$type\":\"location\",\"start\":[76,1],\"end\":[90,5]}}","procedure dequeue(queue: request_bufT);"},{"enqueue",::romp::location{{92,1},{100,5}},"{\"$type\":\"procedure\",\"label\":\"enqueue\",\"params\":[{\"$type\":\"param\",\"id\":\"queue\",\"type\":\"request_bufT\"},{\"$type\":\"param\",\"id\":\"pid\",\"type\":\"procT\"}],\"loc\":{\"$type\":\"location\",\"start\":[92,1],\"end\":[100,5]}}","procedure enqueue(queue: request_bufT; var pid: procT);"},{"place_request",::romp::location{{104,1},{107,5}},"{\"$type\":\"procedure\",\"label\":\"place_request\",\"params\":[{\"$type\":\"param\",\"id\":\"prob_owner\",\"type\":\"procT\"},{\"$type\":\"param\",\"id\":\"p\",\"type\":\"procT\"}],\"loc\":{\"$type\":\"location\",\"start\":[104,1],\"end\":[107,5]}}","procedure place_request(var prob_owner,p: procT);"},{"copytail",::romp::location{{109,1},{132,5}},"{\"$type\":\"procedure\",\"label\":\"copytail\",\"params\":[{\"$type\":\"param\",\"id\":\"source_queue\",\"type\":\"request_bufT\"},{\"$type\":\"param\",\"id\":\"destination_queue\",\"type\":\"request_bufT\"}],\"loc\":{\"$type\":\"location\",\"start\":[109,1],\"end\":[132,5]}}","procedure copytail(source_queue,destination_queue: request_bufT);"},};
  const ::romp::MErrorInfo ERROR_INFOS[] = {{"Front of empty queue is undefined",::romp::location{{58,8},{58,49}},"{\"$type\":\"error-statement\",\"label\":\"Front of empty queue is undefined\",\"loc\":{\"$type\":\"location\",\"start\":[58,8],\"end\":[58,49]}"},{"Illegal queue count value",::romp::location{{71,8},{71,41}},"{\"$type\":\"error-statement\",\"label\":\"Illegal queue count value\",\"loc\":{\"$type\":\"location\",\"start\":[71,8],\"end\":[71,41]}"},{"Queue is empty",::romp::location{{80,7},{80,29}},"{\"$type\":\"error-statement\",\"label\":\"Queue is empty\",\"loc\":{\"$type\":\"location\",\"start\":[80,7],\"end\":[80,29]}"},{"Queue is full",::romp::location{{96,8},{96,29}},"{\"$type\":\"error-statement\",\"label\":\"Queue is full\",\"loc\":{\"$type\":\"location\",\"start\":[96,8],\"end\":[96,29]}"},{"Lock is HERE and FREE while there is a waiter.",::romp::location{{228,12},{228,66}},"{\"$type\":\"error-statement\",\"label\":\"Lock is HERE and FREE while there is a waiter.\",\"loc\":{\"$type\":\"location\",\"start\":[228,12],\"end\":[228,66]}"},};

} // namespace __info__


#pragma endregion metadata__generated_code



#pragma region rule_caller__generated_code

namespace __caller__ {

// << ==================================== Rule Expansions ===================================== >>

/* --- Rules Generated by: `Try_acquiring_the_lock` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Try_acquiring_the_lock__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Try_acquiring_the_lock(_romp_procT_6_1); }
 void __romp__Rule_action__Try_acquiring_the_lock__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Try_acquiring_the_lock(_romp_procT_6_1); }
 bool __romp__Rule_guard__Try_acquiring_the_lock__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Try_acquiring_the_lock(_romp_procT_6_2); }
 void __romp__Rule_action__Try_acquiring_the_lock__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Try_acquiring_the_lock(_romp_procT_6_2); }
 bool __romp__Rule_guard__Try_acquiring_the_lock__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Try_acquiring_the_lock(_romp_procT_6_3); }
 void __romp__Rule_action__Try_acquiring_the_lock__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Try_acquiring_the_lock(_romp_procT_6_3); }
 bool __romp__Rule_guard__Try_acquiring_the_lock__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Try_acquiring_the_lock(_romp_procT_6_4); }
 void __romp__Rule_action__Try_acquiring_the_lock__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Try_acquiring_the_lock(_romp_procT_6_4); }
 bool __romp__Rule_guard__Try_acquiring_the_lock__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Try_acquiring_the_lock(_romp_procT_6_5); }
 void __romp__Rule_action__Try_acquiring_the_lock__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Try_acquiring_the_lock(_romp_procT_6_5); }
 bool __romp__Rule_guard__Try_acquiring_the_lock__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Try_acquiring_the_lock(_romp_procT_6_6); }
 void __romp__Rule_action__Try_acquiring_the_lock__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Try_acquiring_the_lock(_romp_procT_6_6); }
/* --- Rules Generated by: `If_the_lock_is_around__grab_it` (RuleSet expansions) --- */
 bool __romp__Rule_guard__If_the_lock_is_around__grab_it__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_is_around__grab_it(_romp_procT_6_1); }
 void __romp__Rule_action__If_the_lock_is_around__grab_it__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_is_around__grab_it(_romp_procT_6_1); }
 bool __romp__Rule_guard__If_the_lock_is_around__grab_it__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_is_around__grab_it(_romp_procT_6_2); }
 void __romp__Rule_action__If_the_lock_is_around__grab_it__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_is_around__grab_it(_romp_procT_6_2); }
 bool __romp__Rule_guard__If_the_lock_is_around__grab_it__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_is_around__grab_it(_romp_procT_6_3); }
 void __romp__Rule_action__If_the_lock_is_around__grab_it__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_is_around__grab_it(_romp_procT_6_3); }
 bool __romp__Rule_guard__If_the_lock_is_around__grab_it__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_is_around__grab_it(_romp_procT_6_4); }
 void __romp__Rule_action__If_the_lock_is_around__grab_it__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_is_around__grab_it(_romp_procT_6_4); }
 bool __romp__Rule_guard__If_the_lock_is_around__grab_it__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_is_around__grab_it(_romp_procT_6_5); }
 void __romp__Rule_action__If_the_lock_is_around__grab_it__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_is_around__grab_it(_romp_procT_6_5); }
 bool __romp__Rule_guard__If_the_lock_is_around__grab_it__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_is_around__grab_it(_romp_procT_6_6); }
 void __romp__Rule_action__If_the_lock_is_around__grab_it__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_is_around__grab_it(_romp_procT_6_6); }
/* --- Rules Generated by: `If_the_lock_isn_t_around__send_request_out` (RuleSet expansions) --- */
 bool __romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_1); }
 void __romp__Rule_action__If_the_lock_isn_t_around__send_request_out__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_1); }
 bool __romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_2); }
 void __romp__Rule_action__If_the_lock_isn_t_around__send_request_out__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_2); }
 bool __romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_3); }
 void __romp__Rule_action__If_the_lock_isn_t_around__send_request_out__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_3); }
 bool __romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_4); }
 void __romp__Rule_action__If_the_lock_isn_t_around__send_request_out__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_4); }
 bool __romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_5); }
 void __romp__Rule_action__If_the_lock_isn_t_around__send_request_out__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_5); }
 bool __romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_6); }
 void __romp__Rule_action__If_the_lock_isn_t_around__send_request_out__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_the_lock_isn_t_around__send_request_out(_romp_procT_6_6); }
/* --- Rules Generated by: `Locked____Enter_if_no_waiters` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Locked____Enter_if_no_waiters__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Locked____Enter_if_no_waiters(_romp_procT_6_1); }
 void __romp__Rule_action__Locked____Enter_if_no_waiters__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Locked____Enter_if_no_waiters(_romp_procT_6_1); }
 bool __romp__Rule_guard__Locked____Enter_if_no_waiters__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Locked____Enter_if_no_waiters(_romp_procT_6_2); }
 void __romp__Rule_action__Locked____Enter_if_no_waiters__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Locked____Enter_if_no_waiters(_romp_procT_6_2); }
 bool __romp__Rule_guard__Locked____Enter_if_no_waiters__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Locked____Enter_if_no_waiters(_romp_procT_6_3); }
 void __romp__Rule_action__Locked____Enter_if_no_waiters__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Locked____Enter_if_no_waiters(_romp_procT_6_3); }
 bool __romp__Rule_guard__Locked____Enter_if_no_waiters__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Locked____Enter_if_no_waiters(_romp_procT_6_4); }
 void __romp__Rule_action__Locked____Enter_if_no_waiters__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Locked____Enter_if_no_waiters(_romp_procT_6_4); }
 bool __romp__Rule_guard__Locked____Enter_if_no_waiters__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Locked____Enter_if_no_waiters(_romp_procT_6_5); }
 void __romp__Rule_action__Locked____Enter_if_no_waiters__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Locked____Enter_if_no_waiters(_romp_procT_6_5); }
 bool __romp__Rule_guard__Locked____Enter_if_no_waiters__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Locked____Enter_if_no_waiters(_romp_procT_6_6); }
 void __romp__Rule_action__Locked____Enter_if_no_waiters__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Locked____Enter_if_no_waiters(_romp_procT_6_6); }
/* --- Rules Generated by: `When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state` (RuleSet expansions) --- */
 bool __romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_1); }
 void __romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_1); }
 bool __romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_2); }
 void __romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_2); }
 bool __romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_3); }
 void __romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_3); }
 bool __romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_4); }
 void __romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_4); }
 bool __romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_5); }
 void __romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_5); }
 bool __romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_6); }
 void __romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state(_romp_procT_6_6); }
/* --- Rules Generated by: `In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_` (RuleSet expansions) --- */
 bool __romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_1); }
 void __romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_1); }
 bool __romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_2); }
 void __romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_2); }
 bool __romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_3); }
 void __romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_3); }
 bool __romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_4); }
 void __romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_4); }
 bool __romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_5); }
 void __romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_5); }
 bool __romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_6); }
 void __romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along_(_romp_procT_6_6); }
/* --- Rules Generated by: `In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT` (RuleSet expansions) --- */
 bool __romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_1); }
 void __romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_1); }
 bool __romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_2); }
 void __romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_2); }
 bool __romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_3); }
 void __romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_3); }
 bool __romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_4); }
 void __romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_4); }
 bool __romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_5); }
 void __romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_5); }
 bool __romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_6); }
 void __romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT(_romp_procT_6_6); }
/* --- Rules Generated by: `In_state_TRYGRANT__if_lock_is_free__grant_it_` (RuleSet expansions) --- */
 bool __romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_1); }
 void __romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_1); }
 bool __romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_2); }
 void __romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_2); }
 bool __romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_3); }
 void __romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_3); }
 bool __romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_4); }
 void __romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_4); }
 bool __romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_5); }
 void __romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_5); }
 bool __romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_6); }
 void __romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it_(_romp_procT_6_6); }
/* --- Rules Generated by: `If_lock_not_around__pass_buck_along_to_who_we_think_is_PO` (RuleSet expansions) --- */
 bool __romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_1); }
 void __romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_1); }
 bool __romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_2); }
 void __romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_2); }
 bool __romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_3); }
 void __romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_3); }
 bool __romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_4); }
 void __romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_4); }
 bool __romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_5); }
 void __romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_5); }
 bool __romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_6); }
 void __romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO(_romp_procT_6_6); }
/* --- Rules Generated by: `If_lock_around_but_busy__enqueue_request` (RuleSet expansions) --- */
 bool __romp__Rule_guard__If_lock_around_but_busy__enqueue_request__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_around_but_busy__enqueue_request(_romp_procT_6_1); }
 void __romp__Rule_action__If_lock_around_but_busy__enqueue_request__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_around_but_busy__enqueue_request(_romp_procT_6_1); }
 bool __romp__Rule_guard__If_lock_around_but_busy__enqueue_request__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_around_but_busy__enqueue_request(_romp_procT_6_2); }
 void __romp__Rule_action__If_lock_around_but_busy__enqueue_request__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_around_but_busy__enqueue_request(_romp_procT_6_2); }
 bool __romp__Rule_guard__If_lock_around_but_busy__enqueue_request__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_around_but_busy__enqueue_request(_romp_procT_6_3); }
 void __romp__Rule_action__If_lock_around_but_busy__enqueue_request__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_around_but_busy__enqueue_request(_romp_procT_6_3); }
 bool __romp__Rule_guard__If_lock_around_but_busy__enqueue_request__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_around_but_busy__enqueue_request(_romp_procT_6_4); }
 void __romp__Rule_action__If_lock_around_but_busy__enqueue_request__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_around_but_busy__enqueue_request(_romp_procT_6_4); }
 bool __romp__Rule_guard__If_lock_around_but_busy__enqueue_request__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_around_but_busy__enqueue_request(_romp_procT_6_5); }
 void __romp__Rule_action__If_lock_around_but_busy__enqueue_request__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_around_but_busy__enqueue_request(_romp_procT_6_5); }
 bool __romp__Rule_guard__If_lock_around_but_busy__enqueue_request__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__If_lock_around_but_busy__enqueue_request(_romp_procT_6_6); }
 void __romp__Rule_action__If_lock_around_but_busy__enqueue_request__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__If_lock_around_but_busy__enqueue_request(_romp_procT_6_6); }

#define _ROMP_RULE_COUNT (60ul)

#define _ROMP_RULESETS_LEN (10ul)
const ::romp::RuleSet RULESETS[] = {
		{::__info__::RULE_SET_INFOS[0],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Try_acquiring_the_lock__0,__romp__Rule_action__Try_acquiring_the_lock__0,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_1\"}}}]","p:=procT_1"}, ::romp::Rule{__romp__Rule_guard__Try_acquiring_the_lock__1,__romp__Rule_action__Try_acquiring_the_lock__1,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_2\"}}}]","p:=procT_2"}, ::romp::Rule{__romp__Rule_guard__Try_acquiring_the_lock__2,__romp__Rule_action__Try_acquiring_the_lock__2,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_3\"}}}]","p:=procT_3"}, ::romp::Rule{__romp__Rule_guard__Try_acquiring_the_lock__3,__romp__Rule_action__Try_acquiring_the_lock__3,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":3,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_4\"}}}]","p:=procT_4"}, ::romp::Rule{__romp__Rule_guard__Try_acquiring_the_lock__4,__romp__Rule_action__Try_acquiring_the_lock__4,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":4,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_5\"}}}]","p:=procT_5"}, ::romp::Rule{__romp__Rule_guard__Try_acquiring_the_lock__5,__romp__Rule_action__Try_acquiring_the_lock__5,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":5,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_6\"}}}]","p:=procT_6"}	}},
		{::__info__::RULE_SET_INFOS[1],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__If_the_lock_is_around__grab_it__0,__romp__Rule_action__If_the_lock_is_around__grab_it__0,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_1\"}}}]","p:=procT_1"}, ::romp::Rule{__romp__Rule_guard__If_the_lock_is_around__grab_it__1,__romp__Rule_action__If_the_lock_is_around__grab_it__1,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_2\"}}}]","p:=procT_2"}, ::romp::Rule{__romp__Rule_guard__If_the_lock_is_around__grab_it__2,__romp__Rule_action__If_the_lock_is_around__grab_it__2,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_3\"}}}]","p:=procT_3"}, ::romp::Rule{__romp__Rule_guard__If_the_lock_is_around__grab_it__3,__romp__Rule_action__If_the_lock_is_around__grab_it__3,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":3,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_4\"}}}]","p:=procT_4"}, ::romp::Rule{__romp__Rule_guard__If_the_lock_is_around__grab_it__4,__romp__Rule_action__If_the_lock_is_around__grab_it__4,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":4,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_5\"}}}]","p:=procT_5"}, ::romp::Rule{__romp__Rule_guard__If_the_lock_is_around__grab_it__5,__romp__Rule_action__If_the_lock_is_around__grab_it__5,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":5,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_6\"}}}]","p:=procT_6"}	}},
		{::__info__::RULE_SET_INFOS[2],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__0,__romp__Rule_action__If_the_lock_isn_t_around__send_request_out__0,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_1\"}}}]","p:=procT_1"}, ::romp::Rule{__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__1,__romp__Rule_action__If_the_lock_isn_t_around__send_request_out__1,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_2\"}}}]","p:=procT_2"}, ::romp::Rule{__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__2,__romp__Rule_action__If_the_lock_isn_t_around__send_request_out__2,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_3\"}}}]","p:=procT_3"}, ::romp::Rule{__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__3,__romp__Rule_action__If_the_lock_isn_t_around__send_request_out__3,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":3,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_4\"}}}]","p:=procT_4"}, ::romp::Rule{__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__4,__romp__Rule_action__If_the_lock_isn_t_around__send_request_out__4,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":4,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_5\"}}}]","p:=procT_5"}, ::romp::Rule{__romp__Rule_guard__If_the_lock_isn_t_around__send_request_out__5,__romp__Rule_action__If_the_lock_isn_t_around__send_request_out__5,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":5,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_6\"}}}]","p:=procT_6"}	}},
		{::__info__::RULE_SET_INFOS[3],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Locked____Enter_if_no_waiters__0,__romp__Rule_action__Locked____Enter_if_no_waiters__0,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_1\"}}}]","p:=procT_1"}, ::romp::Rule{__romp__Rule_guard__Locked____Enter_if_no_waiters__1,__romp__Rule_action__Locked____Enter_if_no_waiters__1,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_2\"}}}]","p:=procT_2"}, ::romp::Rule{__romp__Rule_guard__Locked____Enter_if_no_waiters__2,__romp__Rule_action__Locked____Enter_if_no_waiters__2,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_3\"}}}]","p:=procT_3"}, ::romp::Rule{__romp__Rule_guard__Locked____Enter_if_no_waiters__3,__romp__Rule_action__Locked____Enter_if_no_waiters__3,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":3,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_4\"}}}]","p:=procT_4"}, ::romp::Rule{__romp__Rule_guard__Locked____Enter_if_no_waiters__4,__romp__Rule_action__Locked____Enter_if_no_waiters__4,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":4,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_5\"}}}]","p:=procT_5"}, ::romp::Rule{__romp__Rule_guard__Locked____Enter_if_no_waiters__5,__romp__Rule_action__Locked____Enter_if_no_waiters__5,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":5,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_6\"}}}]","p:=procT_6"}	}},
		{::__info__::RULE_SET_INFOS[4],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__0,__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__0,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_1\"}}}]","p:=procT_1"}, ::romp::Rule{__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__1,__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__1,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_2\"}}}]","p:=procT_2"}, ::romp::Rule{__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__2,__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__2,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_3\"}}}]","p:=procT_3"}, ::romp::Rule{__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__3,__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__3,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":3,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_4\"}}}]","p:=procT_4"}, ::romp::Rule{__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__4,__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__4,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":4,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_5\"}}}]","p:=procT_5"}, ::romp::Rule{__romp__Rule_guard__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__5,__romp__Rule_action__When_unlocking_if_waiter_queue_isn_t_empty__go_to_EXITING_state__5,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":5,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_6\"}}}]","p:=procT_6"}	}},
		{::__info__::RULE_SET_INFOS[5],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___0,__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___0,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_1\"}}}]","p:=procT_1"}, ::romp::Rule{__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___1,__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___1,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_2\"}}}]","p:=procT_2"}, ::romp::Rule{__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___2,__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___2,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_3\"}}}]","p:=procT_3"}, ::romp::Rule{__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___3,__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___3,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":3,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_4\"}}}]","p:=procT_4"}, ::romp::Rule{__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___4,__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___4,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":4,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_5\"}}}]","p:=procT_5"}, ::romp::Rule{__romp__Rule_guard__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___5,__romp__Rule_action__In_EXITING_state__pass_hd_waiter_and_tail_of_waiters_along___5,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":5,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_6\"}}}]","p:=procT_6"}	}},
		{::__info__::RULE_SET_INFOS[6],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__0,__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__0,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_1\"}}}]","p:=procT_1"}, ::romp::Rule{__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__1,__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__1,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_2\"}}}]","p:=procT_2"}, ::romp::Rule{__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__2,__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__2,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_3\"}}}]","p:=procT_3"}, ::romp::Rule{__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__3,__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__3,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":3,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_4\"}}}]","p:=procT_4"}, ::romp::Rule{__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__4,__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__4,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":4,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_5\"}}}]","p:=procT_5"}, ::romp::Rule{__romp__Rule_guard__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__5,__romp__Rule_action__In_state_HANDLE__if_there_is_a_waiting_request__goto_TRYGRANT__5,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":5,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_6\"}}}]","p:=procT_6"}	}},
		{::__info__::RULE_SET_INFOS[7],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___0,__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___0,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_1\"}}}]","p:=procT_1"}, ::romp::Rule{__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___1,__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___1,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_2\"}}}]","p:=procT_2"}, ::romp::Rule{__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___2,__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___2,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_3\"}}}]","p:=procT_3"}, ::romp::Rule{__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___3,__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___3,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":3,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_4\"}}}]","p:=procT_4"}, ::romp::Rule{__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___4,__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___4,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":4,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_5\"}}}]","p:=procT_5"}, ::romp::Rule{__romp__Rule_guard__In_state_TRYGRANT__if_lock_is_free__grant_it___5,__romp__Rule_action__In_state_TRYGRANT__if_lock_is_free__grant_it___5,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":5,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_6\"}}}]","p:=procT_6"}	}},
		{::__info__::RULE_SET_INFOS[8],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__0,__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__0,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_1\"}}}]","p:=procT_1"}, ::romp::Rule{__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__1,__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__1,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_2\"}}}]","p:=procT_2"}, ::romp::Rule{__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__2,__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__2,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_3\"}}}]","p:=procT_3"}, ::romp::Rule{__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__3,__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__3,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":3,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_4\"}}}]","p:=procT_4"}, ::romp::Rule{__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__4,__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__4,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":4,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_5\"}}}]","p:=procT_5"}, ::romp::Rule{__romp__Rule_guard__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__5,__romp__Rule_action__If_lock_not_around__pass_buck_along_to_who_we_think_is_PO__5,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":5,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_6\"}}}]","p:=procT_6"}	}},
		{::__info__::RULE_SET_INFOS[9],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__If_lock_around_but_busy__enqueue_request__0,__romp__Rule_action__If_lock_around_but_busy__enqueue_request__0,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_1\"}}}]","p:=procT_1"}, ::romp::Rule{__romp__Rule_guard__If_lock_around_but_busy__enqueue_request__1,__romp__Rule_action__If_lock_around_but_busy__enqueue_request__1,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_2\"}}}]","p:=procT_2"}, ::romp::Rule{__romp__Rule_guard__If_lock_around_but_busy__enqueue_request__2,__romp__Rule_action__If_lock_around_but_busy__enqueue_request__2,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_3\"}}}]","p:=procT_3"}, ::romp::Rule{__romp__Rule_guard__If_lock_around_but_busy__enqueue_request__3,__romp__Rule_action__If_lock_around_but_busy__enqueue_request__3,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":3,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_4\"}}}]","p:=procT_4"}, ::romp::Rule{__romp__Rule_guard__If_lock_around_but_busy__enqueue_request__4,__romp__Rule_action__If_lock_around_but_busy__enqueue_request__4,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":4,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_5\"}}}]","p:=procT_5"}, ::romp::Rule{__romp__Rule_guard__If_lock_around_but_busy__enqueue_request__5,__romp__Rule_action__If_lock_around_but_busy__enqueue_request__5,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":5,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_6\"}}}]","p:=procT_6"}	}}};


// << =============================== Property Rule Expansions ================================= >>

/* --- Property Rule(s) generated by: `property9` (RuleSet expansions) --- */
 bool __romp__Property__property9__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__property9(); }

#ifdef __romp__ENABLE_assume_property
#define ___propRule_assume_count___ (0ul)
#else
#define ___propRule_assume_count___ (0ul)
#endif
#ifdef __romp__ENABLE_cover_property
#define ___propRule_cover_count___ (0ul)
#else
#define ___propRule_cover_count___ (0ul)
#endif
#ifdef __romp__ENABLE_liveness_property
#define ___propRule_liveness_count___ (0ul)
#else
#define ___propRule_liveness_count___ (0ul)
#endif

/* the number of property rules (after ruleset expansion) in the model */
#define _ROMP_PROPERTY_RULES_LEN ((1ul) + ___propRule_assume_count___ + ___propRule_cover_count___ + ___propRule_liveness_count___)

/* All of the property rules expanded in one place */
const ::romp::Property PROPERTIES[] = {
		{__romp__Property__property9__0,::__info__::PROPERTY_INFOS[0],"[]",""},
};


// << ================================= Startstate Expansions ================================== >>

/* --- StartState Rule(s) generated by: `startstate8` (RuleSet expansions) --- */
 void __romp__StartState__startstate8__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__StartState__startstate8(_romp_procT_6_1); }
 void __romp__StartState__startstate8__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__StartState__startstate8(_romp_procT_6_2); }
 void __romp__StartState__startstate8__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__StartState__startstate8(_romp_procT_6_3); }
 void __romp__StartState__startstate8__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__StartState__startstate8(_romp_procT_6_4); }
 void __romp__StartState__startstate8__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__StartState__startstate8(_romp_procT_6_5); }
 void __romp__StartState__startstate8__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__StartState__startstate8(_romp_procT_6_6); }


#define _ROMP_STARTSTATES_LEN (6ul) // the number of property rules (after ruleset expansion) in the model
// all of the startstates in one place (post ruleset expansion)
const ::romp::StartState STARTSTATES[] = {{__romp__StartState__startstate8__0,::__info__::STARTSTATE_INFOS[0],0,"[{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"quantifier\",\"id\":\"n\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_1\"}}}]","n:=procT_1"}, {__romp__StartState__startstate8__1,::__info__::STARTSTATE_INFOS[0],1,"[{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"quantifier\",\"id\":\"n\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_2\"}}}]","n:=procT_2"}, {__romp__StartState__startstate8__2,::__info__::STARTSTATE_INFOS[0],2,"[{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"quantifier\",\"id\":\"n\",\"type\":\"scalarset-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_3\"}}}]","n:=procT_3"}, {__romp__StartState__startstate8__3,::__info__::STARTSTATE_INFOS[0],3,"[{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"quantifier\",\"id\":\"n\",\"type\":\"scalarset-quantifier\",\"index\":3,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_4\"}}}]","n:=procT_4"}, {__romp__StartState__startstate8__4,::__info__::STARTSTATE_INFOS[0],4,"[{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"quantifier\",\"id\":\"n\",\"type\":\"scalarset-quantifier\",\"index\":4,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_5\"}}}]","n:=procT_5"}, {__romp__StartState__startstate8__5,::__info__::STARTSTATE_INFOS[0],5,"[{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"quantifier\",\"id\":\"n\",\"type\":\"scalarset-quantifier\",\"index\":5,\"value\":{\"$type\":\"value\",\"display-type\":\"procT\",\"value\":\"_romp_procT_6_6\"}}}]","n:=procT_6"}};


} // namespace __caller__


#pragma endregion rule_caller__generated_code


#pragma region romp_postfix

/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw.hpp
 *
 * @brief The primary simulation/random walk functions of romp-rw.
 *
 * @date 2022/05/11
 * @version 0.2
 */
#include <thread>
#include <mutex>
#ifndef __romp__GENERATED_CODE
#pragma once            // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "include.hpp"  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "decl.hpp"     // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "writer.hpp"  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "error.hpp"    // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "options.hpp"    // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "impls.hpp"    // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif

// << =================================== Type Declarations ==================================== >>

namespace romp {

using duration_ms_t = std::chrono::duration<long double,std::milli>;
using time_ms_t = std::chrono::time_point<std::chrono::high_resolution_clock,std::chrono::duration<long double,std::milli>>;

// using duration_ms_t = std::chrono::duration<long long,std::milli>;
// using time_ms_t = std::chrono::time_point<std::chrono::high_resolution_clock,std::chrono::duration<long long,std::milli>>;

using duration_msf_t = std::chrono::duration<long double,std::milli>;

using duration_mr_t = std::chrono::duration<long long,std::chrono::high_resolution_clock::period>;
using time_mr_t = std::chrono::time_point<std::chrono::high_resolution_clock,std::chrono::duration<long long,std::chrono::high_resolution_clock::period>>;

/**
 * @brief helper function rand_choice
 *
 */
template<typename T>
T rand_choice(RandSeed_t &seed, T min, T max) {
    //not done fully
    seed = (((seed ^ (seed >> 3)) >> 12) & 0xffff) | ((seed & 0x7fff) << 16); // modifies the seed
    int choice = seed % (max-min) + min;  // generates the random number
    return choice;
}

class BFSWalker; // useful pre-definition

class RandWalker : public ::romp::IRandWalker {
private:
  static id_t next_id;
  const id_t id;
  const Options& OPTIONS;
  const bool IS_BFS;
  id_t start_id;
  const RandSeed_t init_rand_seed;
  RandSeed_t rand_seed;
  size_t _fuel; // = OPTIONS.depth;
  bool _valid = true;  // legacy
  bool _is_error = false; // legacy
  Result::Cause status = Result::RUNNING;
  json_file_t* json = nullptr;
  // tripped thing
  IModelError* tripped = nullptr;
  IModelError* tripped_inside = nullptr;
  size_t _attempt_limit; // = OPTIONS.attempt_limit;
  const size_t init_attempt_limit; // = OPTIONS.attempt_limit;
public:
  struct History {
    const Rule* rule;
  };
private:
  size_t history_level = 0;
  constexpr size_t history_size() const {return _ROMP_HIST_LEN;}
  History history[_ROMP_HIST_LEN];
  size_t history_start = 0;
  /**
   * @brief call if rule is applied to store what rule made the change in the
   * history circular buffer.
   * @param r reference to the rule that was applied
   */
  void add_to_history(const Rule& r) {
    history[history_level%history_size()] = History{&r};
    ++history_level;
    if (history_level > history_size())
      ++history_start;
  }
#ifdef __ROMP__DO_MEASURE
  time_ms_t init_time;
  time_mr_t start_time;
  duration_mr_t active_time = duration_mr_t(0l);
  duration_ms_t total_time = duration_ms_t(0l);
#endif

  void init_state() noexcept {
    const StartState& startstate = ::__caller__::STARTSTATES[start_id];
#ifdef __ROMP__DO_MEASURE
    start_time = time_mr();
#endif
    try {
      startstate.initialize(state);
      if (OPTIONS.do_trace)
        *json << "{\"$type\":\"init\",\"startstate\":" << startstate << ",\"state\":" << state <<"}";
    } catch (const IModelError& me) {
       __handle_exception/*<StartState,IModelError>*/(startstate,me);
    } catch (const std::exception& ex) {
      status = Result::UNKNOWN_CAUSE;
      __handle_exception/*<StartState,std::exception>*/(startstate,ex);
    } catch (...) {
      status = Result::UNKNOWN_CAUSE;
      tripped_inside = new ModelStartStateError(startstate);
    }
    for (const auto& prop : ::__caller__::PROPERTIES)
      try {
        if (prop.check(state)) { // if tripped
          tripped = new ModelPropertyError(prop);
          tripped_inside = new ModelStartStateError(startstate);
          break;
        }
      } catch(IModelError& me) {
        __handle_exception/*<Property,IModelError>*/(prop,me);
      } catch (std::exception& ex) {
        __handle_exception/*<Property,std::exception>*/(prop,ex);
        status = Result::UNKNOWN_CAUSE;
      } catch (...) {
        status = Result::UNKNOWN_CAUSE;
      }
    // if (json != nullptr) delete json;
#ifdef __ROMP__DO_MEASURE
    active_time += time_mr() - start_time;
#endif
  }

  template<typename R, typename E>
  void __handle_exception(const R& r, const E& er) noexcept {
    if (OPTIONS.do_trace) {
       *json << "],\"error-trace\":[" << er; // << "]";
    }
    tripped_inside = r.make_error();
  }

public:
  const std::function<void()> sim1Step;
  size_t fuel() { return _fuel; }
  size_t attempt_limit() { return _attempt_limit; }
  // bool is_valid() { return _valid; }
  // bool is_error() { return _is_error; }
#ifdef __romp__ENABLE_cover_property
  // bool is_done() const { return (_is_error || (not _valid) || _fuel <= 0 || _attempt_limit <= 0 || complete_cover()); }
  bool is_done() const { return ((status != Result::RUNNING) ||  _fuel <= 0 || _attempt_limit <= 0 || complete_cover()); }
#else
  // bool is_done() const { return (_is_error || (not _valid) || _fuel <= 0 || _attempt_limit <= 0); }
  bool is_done() const { return not (_valid && _fuel > 0 && _attempt_limit > 0); }
#endif


protected:
//   RandWalker(const Options& OPTIONS_)
//     : id(RandWalker::next_id++),
//       OPTIONS(OPTIONS_),
//       sim1Step(((OPTIONS.do_trace)
//                   ? std::function<void()>([this](){sim1Step_trace();})
//                   : std::function<void()>([this](){sim1Step_no_trace();}))),
// #     ifdef __romp__ENABLE_cover_property
//         enable_cover(OPTIONS_.complete_on_cover), goal_cover_count(OPTIONS_.cover_count),
// #     endif
// #     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
//         enable_liveness(OPTIONS_.liveness), init_lcount(OPTIONS.lcount),
// #     endif
//       _attempt_limit(OPTIONS_.attempt_limit), init_attempt_limit(OPTIONS_.attempt_limit)
//     {
//       if (OPTIONS.do_trace) init_trace();
//       for (int i=0; i<history_size(); ++i) this->history[i] = History{nullptr};
// #ifdef __romp__ENABLE_symmetry
//     for (int i=0; i<_ROMP_RULESETS_LEN; ++i) next_rule[i] = 0;
// #endif
// #ifdef __romp__ENABLE_cover_property
//     for (int i=0; i<_ROMP_COVER_PROP_COUNT; ++i) cover_counts[i] = 0;
// #endif
// #if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
//     for (int i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i) lcounts[i] = init_lcount;
// #endif
//     }

public:
  RandWalker(RandSeed_t rand_seed_, const Options& OPTIONS_)
    : // RandWalker(OPTIONS_),
      rand_seed(rand_seed_), init_rand_seed(rand_seed_),
      _fuel(OPTIONS_.depth), IS_BFS(false),
      id(RandWalker::next_id++),
      OPTIONS(OPTIONS_),
      sim1Step(((OPTIONS.do_trace)
                  ? std::function<void()>([this](){sim1Step_trace();})
                  : std::function<void()>([this](){sim1Step_no_trace();}))),
#     ifdef __romp__ENABLE_cover_property
        enable_cover(OPTIONS_.complete_on_cover), goal_cover_count(OPTIONS_.cover_count),
#     endif
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        enable_liveness(OPTIONS_.liveness), init_lcount(OPTIONS.lcount),
#     endif
      _attempt_limit(OPTIONS_.attempt_limit), init_attempt_limit(OPTIONS_.attempt_limit)
  {
    if (OPTIONS.start_id != ~0u) {
      rand_choice(rand_seed,0ul,_ROMP_STARTSTATES_LEN); // burn one rand operation for consistency
      start_id = OPTIONS.start_id;
    } else if (OPTIONS.do_even_start) {
      rand_choice(rand_seed,0ul,_ROMP_STARTSTATES_LEN); // burn one rand operation for consistency
      start_id = id % _ROMP_STARTSTATES_LEN;
    } else
      start_id = rand_choice(rand_seed,0ul,_ROMP_STARTSTATES_LEN);
    state.__rw__ = this; /* provide a semi-hidden reference to this random walker for calling the property handlers */
    if (OPTIONS.do_trace) init_trace();
    for (int i=0; i<history_size(); ++i) this->history[i] = History{nullptr};
#ifdef __romp__ENABLE_symmetry
    for (int i=0; i<_ROMP_RULESETS_LEN; ++i) next_rule[i] = 0;
#endif
#ifdef __romp__ENABLE_cover_property
    for (int i=0; i<_ROMP_COVER_PROP_COUNT; ++i) cover_counts[i] = 0;
#endif
#if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
    for (int i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i) lcounts[i] = init_lcount;
#endif
  }

  RandWalker(const BFSWalker& bfs, RandSeed_t rand_seed_, const Options& OPTIONS_); //defined in impls.hpp


  ~RandWalker() {
    if (json != nullptr) delete json;
    if (tripped != nullptr) delete tripped;
    if (tripped_inside != nullptr) delete tripped_inside;
    // if (history != nullptr) delete[] history;
  }

  inline void init() noexcept {
#ifdef __ROMP__DO_MEASURE
    init_time = time_ms();
#endif
    init_state();
  }

  inline void finalize() noexcept {
#ifdef __ROMP__DO_MEASURE
    total_time = (time_ms() - init_time);
#endif
    if (status == Result::UNKNOWN_CAUSE) {
    } else if (_attempt_limit <= 0) {
      status = Result::ATTEMPT_LIMIT_REACHED;
      const Rule* _last = history[(history_level-1)%history_size()].rule;
      if (_last != nullptr)
        tripped_inside = new ModelRuleError(*_last);
      else tripped_inside = nullptr;
    } else if (_fuel <= 0) {
      status = Result::MAX_DEPTH_REACHED;
#ifdef __romp__ENABLE_cover_property
    } else if (complete_cover()) {
      status = Result::COVER_COMPLETE;
      tripped_inside = new ModelRuleError(*history[(history_level-1)%history_size()].rule);
#endif
    }
  }

  const Result* get_result() noexcept {
    if (OPTIONS.do_trace && json != nullptr) {
      trace_result_out();
      // delete json;
    }
    Result* result = new Result{
                  id,init_rand_seed,start_id,
                  status,
                  OPTIONS.depth - _fuel,
                  tripped,tripped_inside
#ifdef __ROMP__DO_MEASURE
                  ,active_time, total_time
#endif
                  };
    tripped = nullptr;
    tripped_inside = nullptr;
    return result;
  }


private:

  /**
   * @brief to pick a rule in random for simulation step
   */
  // const RuleSet& rand_ruleset(){
  //   return ::__caller__::RULESETS[rand_choice<size_t>(rand_seed,0ul,_ROMP_RULESETS_LEN)];
  // }

#ifdef __romp__ENABLE_symmetry
  // keeps track of what rule to call next for our heuristic symmetry reduction
  id_t next_rule[_ROMP_RULESETS_LEN];
#endif
  /**
   * @brief to pick a rule in random for simulation step
   */
  const Rule& get_rand_rule(){
    const size_t rs_id = rand_choice<size_t>(rand_seed,0ul,_ROMP_RULESETS_LEN);
    const RuleSet& rs = ::__caller__::RULESETS[rs_id];
#ifdef __romp__ENABLE_symmetry
    id_t& r_id = next_rule[rs_id];  // this is a reference
    const Rule& r = rs.rules[r_id];
    if (++r_id >= rs.rules.size())
      r_id = 0;
#else
     const Rule& r = rs.rules[rand_choice<size_t>(rand_seed,0ul,rs.rules.size())];
#endif
    return r;
  }

  void sim1Step_trace() noexcept {
#ifdef __ROMP__DO_MEASURE
    start_time = time_mr();
#endif
    // const RuleSet& rs = rand_ruleset();
    // const Rule& r = rand_rule(rs);
    const Rule& r = get_rand_rule();
    bool pass = false;
    try {
      if ((pass = r.guard(state)) == true) {
        r.action(state);
        --_fuel;
        _attempt_limit = init_attempt_limit;
        add_to_history(r);
        *json << ",{\"$type\":\"rule-hit\",\"rule\":" << r << ","
                 "\"state\":" << state
              << "}";
      } else {
        *json << ",{\"$type\":\"rule-miss\",\"rule\":" << r << "}";
        --_attempt_limit;
      }
    } catch(IModelError& me) {
      __handle_exception/*<Rule,IModelError>*/(r,me);
      pass = false;
    } catch (std::exception& ex) {
      __handle_exception/*<Rule,std::exception>*/(r,ex);
      pass = false;
      status = Result::UNKNOWN_CAUSE;
    } catch (...) {
      pass = false;
      status = Result::UNKNOWN_CAUSE;
    }
    if (pass)
      for (const auto& prop : ::__caller__::PROPERTIES)
        try {
          if (prop.check(state)) { // if tripped
            tripped = new ModelPropertyError(prop);
            tripped_inside = new ModelRuleError(r);
            *json << "],\"error-trace\":[" << *tripped; // << "]";
            break;
          }
        } catch(IModelError& me) {
          __handle_exception/*<Property,IModelError>*/(prop,me);
        } catch (std::exception& ex) {
          __handle_exception/*<Property,std::exception>*/(prop,ex);
          status = Result::UNKNOWN_CAUSE;
        } catch (...) {
          status = Result::UNKNOWN_CAUSE;
        }
#ifdef __ROMP__DO_MEASURE
    active_time += time_mr() - start_time;
#endif
    if (_fuel % _ROMP_FLUSH_FREQ == 0)
      json->out.flush();
  }

  void sim1Step_no_trace() noexcept {
#ifdef __ROMP__DO_MEASURE
    start_time = time_mr();
#endif
    // const RuleSet& rs= rand_ruleset();
    // const Rule& r= rand_rule(rs);
    const Rule& r = get_rand_rule();
    bool pass = false;
    try {
      if ((pass = r.guard(state)) == true) {
        r.action(state);
        --_fuel;
        _attempt_limit = init_attempt_limit;
        add_to_history(r);
      } else { --_attempt_limit; }
    } catch(IModelError& me) {
      __handle_exception/*<Rule,IModelError>*/(r,me);
      pass = false;
    } catch (std::exception& ex) {
      __handle_exception/*<Rule,std::exception>*/(r,ex);
      pass = false;
      status = Result::UNKNOWN_CAUSE;
    } catch (...) {
      pass = false;
      status = Result::UNKNOWN_CAUSE;
    }
    if (pass)
      for (const auto& prop : ::__caller__::PROPERTIES)
        try {
          if (prop.check(state)) { // if tripped
            tripped = new ModelPropertyError(prop);
            tripped_inside = new ModelRuleError(r);
            break;
          }
        } catch(IModelError& me) {
          __handle_exception/*<Property,IModelError>*/(prop,me);
        } catch (std::exception& ex) {
          __handle_exception/*<Property,std::exception>*/(prop,ex);
          status = Result::UNKNOWN_CAUSE;
        } catch (...) {
          status = Result::UNKNOWN_CAUSE;
        }
#ifdef __ROMP__DO_MEASURE
    active_time += time_mr() - start_time;
#endif
  }

  void init_trace() {
    json = new json_file_t(OPTIONS.get_trace_file_path(id));
    *json << "{\"$type\":\"";
#ifdef __ROMP__SIMPLE_TRACE
    *json << "romp-simple-trace";
#else
    *json << "romp-trace";
#endif
    *json << "\",\"$version\":\"" _ROMP_TRACE_JSON_VERSION "\"";
    *json << ",\"trace-id\":" << id
          << ",\"seed\":" << init_rand_seed
          << ",\"start-id\":" << start_id
          << ",\"metadata\":" << OPTIONS // .write_metadata_json(json->out)
          << ",\"trace\":[";
  }

  void bfs_trace(const BFSWalker& bfs); // defined in impls.hpp

  void trace_result_out() const {
    using namespace std::chrono;
    *json << "]"; // close trace
    // if (_valid && tripped == nullptr) // if it didn't end in an error we need to:
    if (tripped_inside == nullptr) // if it didn't end in an error we need to:
      *json << ",\"error-trace\":[]"; // output empty error-trace
    *json << ",\"results\":{\"depth\":"<< OPTIONS.depth-_fuel <<",\"valid\":null,\"is-error\":null"
          << ",\"result\":\"" << std::to_string(status) << "\""
#ifdef __ROMP__DO_MEASURE
                                << ",\"active-time\":" << (duration_cast<duration_msf_t>(active_time).count())
                                << ",\"total-time\":" << (duration_cast<duration_msf_t>(total_time).count())
#else
                                << ",\"active-time\":null,\"total-time\":null"
#endif
            << ",\"property-violated\":" << tripped
            << ",\"tripped-inside\":" << tripped_inside
            << ",\"attempts-final\":" << _attempt_limit
                              << "}" // closes results object
              << "}"; // closes top level trace object
    json->out.flush();
  }

public:
  bool do_report() const {
    if (OPTIONS.report_all) return true;
    switch (status) {
      case Result::UNKNOWN_CAUSE:
        return true;
      case Result::PROPERTY_VIOLATED:
      case Result::MERROR_REACHED:
        return OPTIONS.report_error;
#ifdef __romp__ENABLE_assume_property
      case Result::ASSUMPTION_VIOLATED:
        return OPTIONS.r_assume;
#endif
#ifdef __romp__ENABLE_cover_property
      case Result::COVER_COMPLETE:
        return OPTIONS.r_cover;
#endif
      default: return false;
    }
  }

  // called when trying to print the results of the random walker when it finishes (will finish up trace file if necessary too)
  //  the calling context should ensure that the RandWalker is not being used else where & safe output to the ostream
  friend ostream_p& operator << (ostream_p& out, const RandWalker& rw) {
    std::string res_color = get_color(rw.status);
    out << out.nl()
        << "======== BEGIN :: Report of Walk #" << rw.id << " ========"             << out.nl()
        << "BASIC INFO: "                                           << out.indent() << out.nl()
        << "         w#: " << rw.id                                                 << out.nl()
        << "       Seed: " << rw.init_rand_seed                                     << out.nl()
        << "      Depth: " << rw.OPTIONS.depth - rw._fuel                              << out.nl()
        << "   Start ID: " << rw.start_id                                           << out.nl()
        << " StartState: " << ::__caller__::STARTSTATES[rw.start_id]                << out.nl()
        << "     Result: " << res_color << std::to_string(rw.status) << "\033[0m"   << out.nl()
        << out.dedent()                                                             << out.nl()
        << "TRACE LITE:"                                            << out.indent() << out.nl()
        << "NOTE - " << ((rw.OPTIONS.do_trace)
                          ? "see \"" + rw.OPTIONS.trace_dir + std::to_string(rw.init_rand_seed) + ".json\" for full trace."
                          : "use the --trace/-t option to generate a full & detailed trace." ) << out.nl()
        << "History: ["                             << out.indent() << out.indent() << out.nl()
        << "-(0) " << ::__caller__::STARTSTATES[rw.start_id] << '\n';
      if (rw.history_start > 0)
        out << out.indentation() << "-(..) ... forgotten past ...\n";
      for (size_t i=rw.history_start; i<rw.history_level; ++i)
        out << out.indentation() << "-(" << i+1 <<") " << *(rw.history[i%rw.history_size()].rule) << "\n";
    out << out.dedent() << out.indentation() << ']' << out.dedent() << out.dedent();
    if (rw.OPTIONS.report_emit_state)
      out                                                                           << out.nl()
          << "  State: " <<  out.indent() << out.indent() << rw.state << out.dedent() << out.dedent();
    if (rw.tripped != nullptr || rw.tripped_inside != nullptr) {
      out                                                                           << out.nl()
          << "ISSUE REPORT:"                                        << out.indent() << out.nl();
      if (rw.tripped != nullptr) {
        out << "Tripped: \033[31m" << *rw.tripped << "\033[0m"                      << out.nl();
        if (rw.tripped_inside != nullptr)
          out << "  Trace: "                                        << out.indent() << out.nl()
              << *rw.tripped_inside                                 << out.dedent() << out.nl();
              // << '}'                                                               << out.nl();
      }
    }
    if (rw.put_msgs.size() > 0) {
      out << "Put Statements: \"\"\""               << out.indent() << out.indent() << out.nl();
      for (auto msg : rw.put_msgs) {
        try {
          msg.first(out);
        } catch (std::exception& ex) {
          out << out.indent() << out.nl() << msg.second << " :: error occurred while evaluating put statement"
              << out.nl() << ex << out.dedent() << out.nl();
        }
      }
      out << out.dedent() << out.nl() << "\"\"\"" << out.dedent() << out.nl();
    }

#ifdef __ROMP__DO_MEASURE
    out << out.dedent()                                                             << out.nl()
        << "TIME REPORT:"                                           << out.indent() << out.nl()
        << "Active Time: " << rw.active_time                                        << out.nl()
        << " Total Time: " << rw.total_time                                         ;// << out.nl();
#endif
    out << out.dedent()                                                             << out.nl()
        << "======== END :: Report of Walk #" << rw.id << " ========"               << out.nl();
    out.out.flush();

    return out;
  }
  // called when trying to print the results of the random walker when it finishes (will finish up trace file if necessary too)
  //  the calling context should ensure that the RandWalker is not being used else where & safe output to the ostream
  friend std::ostream& operator << (std::ostream& out, const RandWalker& rw)
  { ostream_p _out(out,rw.OPTIONS,0); _out << rw; return out; }

  // NOTE: currently not supporting choose rules
  // size_t choose_handler(size_t occupance, const location& loc) {}

  std::vector<std::pair<std::function<void(ostream_p&)>,location>> put_msgs;
  void put_handler(const std::function<void(ostream_p&)>& put_action, const location& loc) {
    put_msgs.push_back(std::make_pair(put_action,loc));
  }

  bool error_handler(id_t error_id) {
    tripped = new ModelMErrorError(error_id);
    _valid = true; // legacy
    _is_error = true; // legacy
    status = Result::MERROR_REACHED;
    return true;
  }

  bool assertion_handler(bool expr, id_t prop_id) {
    if (expr) return false;
    tripped = new ModelPropertyError(prop_id);
    _valid = false;  // legacy
    _is_error = true;  // legacy
    status = Result::PROPERTY_VIOLATED;
    return true;
  }
  bool invariant_handler(bool expr, id_t prop_id) {
    if (expr) return false;
    // no need to store exception in tripped if a property rule the catch will give us a better error dump
    // invar_handler is only called from a property rule
    _valid = false;  // legacy
    _is_error = true; // legacy
    status = Result::PROPERTY_VIOLATED;
    return true;
  }
#ifdef __romp__ENABLE_assume_property
  bool assumption_handler(bool expr, id_t prop_id) {
    if (expr) return false;
    tripped = new ModelPropertyError(prop_id);
    _valid = false;  // legacy
    // this is what makes an assumption different from an assertion
    _is_error = false; // legacy
    status = Result::ASSUMPTION_VIOLATED;
    return true;
  }
#else
  bool assumption_handler(bool expr, id_t prop_id) {
    return false;  // don't do anything if the assume property is nto enabled
  }
#endif
#ifdef __romp__ENABLE_cover_property
  const bool enable_cover; // = OPTIONS.complete_on_cover;
  const id_t goal_cover_count; // = OPTIONS.cover_count;
  size_t cover_counts[_ROMP_COVER_PROP_COUNT];
  bool cover_handler(bool expr, id_t cover_id, id_t prop_id) {
    if (expr) cover_counts[cover_id]++;
    return false; // cover never throws an error
  }
#ifdef __GNUC__
  __attribute__((optimize("unroll-loops")))
#endif
  bool complete_cover() const {
    if (not enable_cover) return false;
    bool res = true;
    for (int i=0; i<_ROMP_COVER_PROP_COUNT; ++i)
      res &= (cover_counts[i] >= goal_cover_count);
    return res;
  }
#else
  bool cover_handler(bool expr, id_t cover_id, id_t prop_id) {
    return false;  // never throw anything if cover is not enabled by romp generator
  }
#endif
#if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
private:
  const bool enable_liveness; // = OPTIONS.liveness;
  const size_t init_lcount; // = OPTIONS.lcount;
  size_t lcounts[_ROMP_LIVENESS_PROP_COUNT];
public:
  bool liveness_handler(bool expr, id_t liveness_id, id_t prop_id) {
    if (not enable_liveness) return false;
    if (expr) {
      lcounts[liveness_id] = init_lcount;
      return false;
    }
    if (--lcounts[liveness_id] > 0) return false;
    _valid = false;
    _is_error = true;
    tripped = new ModelPropertyError(prop_id);
    return true;  // [?]TODO actually handle this as described in the help page
  }
#else
  bool liveness_handler(bool expr, id_t liveness_id, id_t prop_id) {
    return false;  // never throw anything if cover is not enabled by romp generator
  }
#endif

protected:
  // always have this at the end of the RandWalker object def
  State_t state;
}; //? END class RandomWalker

id_t RandWalker::next_id = 0u;



/**
 * @brief A class that indexes and groups the various results a RandWalker can produce,
 *        and provides a helpful operator for writing a nice summary of the results
 *        to a \c std::ostream as well.
 */
class ResultTree {
  const Options& OPTIONS;
  time_ms_t start_time = time_ms();
  time_ms_t end_time;
  size_t rules_fired = 0;
  size_t size = 0;
#ifdef __ROMP__DO_MEASURE
  duration_mr_t total_walk_active_time = duration_mr_t(0);
  duration_ms_t total_walk_time = duration_ms_t(0);
#endif
  std::vector<const Result*> unknown_causes;
  std::vector<const Result*> attempt_limits_reached;
  std::vector<const Result*> max_depths_reached;
  std::unordered_map<ModelPropertyError,std::vector<const Result*>> properties_violated;
  size_t n_properties_violated = 0;
#ifdef __romp__ENABLE_cover_property
  std::vector<const Result*> completed_covers;
#endif
#ifdef __romp__ENABLE_assume_property
  std::unordered_map<ModelPropertyError,std::vector<const Result*>> assumptions_violated;
  size_t n_assumptions_violated = 0;
#endif
  std::unordered_map<ModelMErrorError,std::vector<const Result*>> merrors_reached;
  size_t n_merrors_reached = 0;
public:
  ResultTree(const Options& OPTIONS_) : OPTIONS(OPTIONS_) {}
  ~ResultTree();
  void insert(const Result* res);
  void start_timer() { start_time = time_ms(); }
  void reset_timer() { start_time = time_ms(); }
  void stop_timer() { end_time = time_ms(); }
  duration_ms_t get_time() const { return end_time - start_time; }
  friend std::ostream& operator << (std::ostream& out, const ResultTree& results);
  friend ostream_p& operator << (ostream_p& out, const ResultTree& r);
};

/**
 * @brief to generate random seeds for the no of random-walkers
 * rand is generated using UNIX timestamp
 * @param root_seed the parent seed for generating the random seeds.
 */
RandSeed_t gen_random_seed(RandSeed_t &root_seed) {
  return rand_choice(root_seed, 1u, UINT32_MAX);
}

/**
 * @brief generate all the random seeds for the various rand walkers
 *
 */
std::unordered_set<RandSeed_t> gen_random_seeds(const Options& OPTIONS, RandSeed_t root_seed)   {
  std::unordered_set<RandSeed_t> seeds;
  for(int i=0; (seeds.size()<OPTIONS.walks) && (i<OPTIONS.walks*2); i++)
    seeds.insert(gen_random_seed(root_seed));
  if (seeds.size()<OPTIONS.walks)
    std::cerr << "\nWARNING : provided seed was only able to produce " << seeds.size() << " unique walker seeds before timing out !!\n"
                 "        |-> ONLY " << seeds.size() << "/" << OPTIONS.walks << " walkers will be run!\n\n" << std::flush;
  return seeds;
}

// example of how to get a copy of an object in C++:
//   use the copy constructor (always has the signature)
//    ClassName(const ClassName &obj)
//  this means your's should look like:
//    auto copied_state = State_t(startstates[i%startstates.size()]);

void print_romp_results_summary(const ResultTree& summary) {
  std::cout << "\n\033[34;1m"
         "================================\n"
         "          ROMP RESULTS:         \n"
         "================================\n"
         "\033[0m\n\n"
         << summary;
}


/**
 * @brief implementing \c rw_count parallel \c RandWalker "simulations" which has the threads
 *        and no of random-walkers specified by the user options .
 * @param rw_count the number of \c RandWalker 's to use.
 * @param rand_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 * @param thread_count the max number of threads to use to accomplish all said random walks.
 */
void launch_OpenMP(RandSeed_t root_seed) {
  std::cout << "\n\t!! NOT YET IMPLEMENTED !!\n" << std::endl; return; //!! temp, remove when finished !!

  // std::vector<RandWalker> rws;
  // try {
  //   rws = gen_random_walkers(rw_count, root_seed, fuel);
  // } catch (const IModelError& ex) {
  //   std::cerr << "\nModel raised an error when initializing our start state(s)!! (message below)\n"
  //             << ex << std::endl;
  // }
  //[?]TODO: launch the random walkers !!
}

/**
 * @brief implementing \c rw_count parallel \c RandWalker "simulations" which has the threads
 *        and no of random-walkers specified by the user options .
 * @param rw_count the number of \c RandWalker 's to use.
 * @param rand_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 * @param thread_count the max number of threads to use to accomplish all said random walks.
 */
void launch_threads(const Options& OPTIONS) {
  auto tmp_seeds = gen_random_seeds(OPTIONS,OPTIONS.rand_seed);
  std::queue<RandSeed_t> in_seeds(std::deque<RandSeed_t>(tmp_seeds.begin(),tmp_seeds.end()));
  // std::queue<RandWalkers*> parallel_rws; // probs threads
  std::queue<RandWalker*> out_rws;
  size_t walks_done = 0;
  std::mutex in_queue;
  std::mutex out_queue;
  // std::mutex _in_queue_mutex;
  // std::mutex _out_queue_mutex;

#ifdef DEBUG
  const auto pause_delay = std::chrono::milliseconds(250); //DEBUG SLOW ME DOWN
#else
  const auto pause_delay = std::chrono::milliseconds(5);
#endif

  auto lambda = [&]() { // code the threads run
    // std::lock_guard<std::mutex> in_queue(_in_queue_mutex);
    // std::lock_guard<std::mutex> out_queue(_out_queue_mutex);
    in_queue.lock();
    while (in_seeds.size() > 0) {

      in_seeds.front(); RandWalker *rw = new RandWalker(in_seeds.front(),OPTIONS);
      in_seeds.pop();
      in_queue.unlock();

      rw->init();
      while (not rw->is_done())
        rw->sim1Step();
      rw->finalize();

      out_queue.lock();
      out_rws.push(rw);
      ++walks_done;
      out_queue.unlock();

      in_queue.lock();
    }
    in_queue.unlock();
  };

  ostream_p out(std::cout,OPTIONS,0);
  std::vector<std::thread> threads;
  ResultTree summary(OPTIONS);
  // std::vector<std::thread> threads(OPTIONS.threads);
  for (size_t i=0; i<OPTIONS.threads; ++i) {
    threads.push_back(std::thread(lambda));
  }
  // std::lock_guard<std::mutex> in_queue(_in_queue_mutex);
  // std::lock_guard<std::mutex> out_queue(_out_queue_mutex);

  if (OPTIONS.report_any()) {
    out << "\n\033[34;1m"
           "===================================\n"
           "  WALKS OF INTEREST ROMP RESULTS:  \n"
           "===================================\n"
           "\033[0m\n\n";
    out.out.flush();
  }
  std::this_thread::sleep_for(pause_delay*2);
  while (true) {
    while (true) {  // handel outputs
      std::this_thread::sleep_for(pause_delay);
      out_queue.lock();
      if (not (out_rws.size() > 0)) {
        out_queue.unlock();
        break;
      }
      RandWalker* rw = out_rws.front();
      out_rws.pop();
      out_queue.unlock();
      if (rw != nullptr) {
        if (rw->do_report())
          std::cout << *rw << std::endl;
        summary.insert(rw->get_result());
        delete rw;
      }
    }
    std::this_thread::sleep_for(pause_delay);
    out_queue.lock();
    if (not (walks_done < OPTIONS.walks)) {
      out_queue.unlock();
      break;
    }
    out_queue.unlock();
  }
  // we might need to do this one more time for the last one

  summary.stop_timer();

  for (size_t i=0; i<OPTIONS.threads; ++i) // join threads
     threads[i].join();

  print_romp_results_summary(summary);
}


/**
 * @brief (NOT YET IMPLEMENTED) \n
 *        Implementing \c rw_count parallel \c RandWalker "simulations" which has the threads
 *        and no of random-walkers specified by the user options .
 * @param root_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 */
void launch_CUDA(RandSeed_t root_seed);


/**
 * @brief (NOT YET IMPLEMENTED) \n
 *        Implementing \c rw_count parallel \c RandWalker "simulations" which has the threads
 *        and no of random-walkers specified by the user options .
 * @param root_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 */
void launch_SYCL(RandSeed_t root_seed);


/**
 * @brief (NOT YET IMPLEMENTED) \n
 *        Implementing \c rw_count parallel \c RandWalker "simulations" which has the threads
 *        and no of random-walkers specified by the user options .
 * @param root_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 */
void launch_OpenMPI(RandSeed_t root_seed);


/**
 * @brief Launches a single RandWalker (basically jst a simulation).
 * @param rand_seed the random seed
 * @param fuel the max number of rules to try to apply
 */
void launch_single(const Options& OPTIONS) {
  RandWalker* rw = new RandWalker(OPTIONS.rand_seed, OPTIONS);
  rw->init();
  ResultTree summary(OPTIONS);
  while( not rw->is_done() )
    rw->sim1Step();
  rw->finalize();
  std::cout << "SINGLE ROMP RESULT:\n\t"
            << *rw << '\n' << std::endl;
  summary.stop_timer();
  summary.insert(rw->get_result());
  delete rw;
  print_romp_results_summary(summary);
}


} //namespace romp
/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file bfs.hpp
 *
 * @brief code for the preemptive bfs before romp launch
 *
 * @date 2023/01/10
 * @version 0.2
 */


#ifndef __romp__GENERATED_CODE
#include "include.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#include "types.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "walker.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "options.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#endif

namespace std {
  template<>
  struct hash<::romp::State_t> {
    inline size_t operator () (const ::romp::State_t& state) const {
      return state.__romp__model_hash();
    }
  };

} //namespace std

namespace romp {

  class BFSWalker : public IRandWalker {
    const Options& OPTIONS;
    id_t _start_id;
    size_t _depth = 0ul;
    Result::Cause status = Result::NO_CAUSE;
    IModelError* tripped = nullptr;
    IModelError* tripped_inside = nullptr;
    size_t history_level = 0ul;
    constexpr size_t history_size() const { return _ROMP_HIST_LEN*2+1; }
    RandWalker::History history[_ROMP_HIST_LEN*2+1];
    size_t history_start = 0ul;
    /**
     * @brief call if rule is applied to store what rule made the change in the
     * history circular buffer.
     * @param r reference to the rule that was applied
     */
    void add_to_history(const Rule& r) {
      history[history_level%history_size()] = RandWalker::History{&r};
      ++history_level;
      if (history_level > history_size())
        ++history_start;
    }
#   ifdef __ROMP__DO_MEASURE
      time_mr_t start_time;
      duration_mr_t active_time = duration_mr_t(0l);
#   endif

    template<typename R, typename E>
    void __handle_exception(const R& r, const E& er) noexcept {
      tripped_inside = r.make_error();
    }

  public:

    BFSWalker(const Options OPTIONS_, id_t start_id_)
      : OPTIONS(OPTIONS_),
#       if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
          enable_liveness(OPTIONS_.liveness),
#       endif
        _start_id(start_id_)
    {
      state.__rw__ = this;
    }

    ~BFSWalker() {
      if (tripped != nullptr) delete tripped;
      if (tripped_inside != nullptr) delete tripped_inside;
    }

  void init_state() noexcept {
    const StartState& startstate = ::__caller__::STARTSTATES[_start_id];
#   ifdef __ROMP__DO_MEASURE
      start_time = time_mr();
#   endif
    try {
      startstate.initialize(state);
    } catch (const IModelError& me) {
       __handle_exception(startstate,me);
    } catch (const std::exception& ex) {
      status = Result::UNKNOWN_CAUSE;
      __handle_exception(startstate,ex);
    } catch (...) {
      status = Result::UNKNOWN_CAUSE;
      tripped_inside = new ModelStartStateError(startstate);
    }
    for (const auto& prop : ::__caller__::PROPERTIES)
      try {
        if (prop.check(state)) { // if tripped
          tripped = new ModelPropertyError(prop);
          tripped_inside = new ModelStartStateError(startstate);
          break;
        }
      } catch(IModelError& me) {
        __handle_exception(prop,me);
      } catch (std::exception& ex) {
        __handle_exception(prop,ex);
        status = Result::UNKNOWN_CAUSE;
      } catch (...) {
        status = Result::UNKNOWN_CAUSE;
      }
#   ifdef __ROMP__DO_MEASURE
      active_time += time_mr() - start_time;
#   endif
    }

  inline void finalize() noexcept {
    if (status == Result::UNKNOWN_CAUSE) {
    } else if (_depth >= OPTIONS.depth) {
      status = Result::MAX_DEPTH_REACHED;
    }
  }

  const Result* get_result() noexcept {
    Result* result = new Result{
                  0ul, 0ul,
                  _start_id, status, _depth,
                  tripped, tripped_inside
#ifdef __ROMP__DO_MEASURE
                  ,active_time, duration_mr_t(0ul)
#endif
                  };
    tripped = nullptr;
    tripped_inside = nullptr;
    return result;
  }

    bool is_done() const { return status != Result::RUNNING || _depth >= OPTIONS.depth; }

    bool pass = false;

    void sim1Step_no_trace(const Rule& r) noexcept {
#     ifdef __ROMP__DO_MEASURE
        start_time = time_mr();
#     endif
      pass = false;
      try {
        if ((pass = r.guard(state)) == true) {
          r.action(state);
          ++_depth;
          add_to_history(r);
        }
      } catch(IModelError& me) {
        __handle_exception(r,me);
        pass = false;
      } catch (std::exception& ex) {
        __handle_exception(r,ex);
        pass = false;
        status = Result::UNKNOWN_CAUSE;
      } catch (...) {
        pass = false;
        status = Result::UNKNOWN_CAUSE;
      }
      if (pass)
        for (const auto& prop : ::__caller__::PROPERTIES)
          try {
            if (prop.check(state)) { // if tripped
              tripped = new ModelPropertyError(prop);
              tripped_inside = new ModelRuleError(r);
              break;
            }
          } catch(IModelError& me) {
            __handle_exception(prop,me);
          } catch (std::exception& ex) {
            __handle_exception(prop,ex);
            status = Result::UNKNOWN_CAUSE;
          } catch (...) {
            status = Result::UNKNOWN_CAUSE;
          }
#     ifdef __ROMP__DO_MEASURE
        active_time += time_mr() - start_time;
#     endif
    }


    std::vector<std::pair<std::function<void(ostream_p&)>,location>> put_msgs;
    void put_handler(const std::function<void(ostream_p&)>& put_action, const location& loc) {
      put_msgs.push_back(std::make_pair(put_action,loc));
    }

    bool error_handler(id_t error_id) {
      tripped = new ModelMErrorError(error_id);
      status = Result::MERROR_REACHED;
      return true;
    }

    bool assertion_handler(bool expr, id_t prop_id) {
      if (expr) return false;
      tripped = new ModelPropertyError(prop_id);
      status = Result::PROPERTY_VIOLATED;
      return true;
    }
    bool invariant_handler(bool expr, id_t prop_id) {
      if (expr) return false;
      // no need to store exception in tripped if a property rule the catch will give us a better error dump
      // invar_handler is only called from a property rule
      status = Result::PROPERTY_VIOLATED;
      return true;
    }
# ifdef __romp__ENABLE_assume_property
    bool assumption_handler(bool expr, id_t prop_id) {
      if (expr) return false;
      tripped = new ModelPropertyError(prop_id);
      status = Result::ASSUMPTION_VIOLATED;
      return true;
    }
# else
    bool assumption_handler(bool expr, id_t prop_id) {
      return false;  // don't do anything if the assume property is not enabled
    }
# endif
    bool cover_handler(bool expr, id_t cover_id, id_t prop_id) {
      return false;  // BFS does not currently implement liveness
    }
# if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
  private:
    const bool enable_liveness; // = OPTIONS.liveness;
  public:
    bool is_live[_ROMP_LIVENESS_PROP_COUNT];
    bool liveness_handler(bool expr, id_t liveness_id, id_t prop_id) {
      if (not enable_liveness) return false;
      if (expr) {
        is_live[liveness_id] = true;
        return false;
      }
      if (--lcounts[liveness_id] > 0) return false;
      tripped = new ModelPropertyError(prop_id);
      return true;  // [?]TODO actually handle this as described in the help page
    }
    void reset_liveness() {
      for (size_t i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i)
        is_live[i] = false;
    }
    void merge_liveness(bool *liveness) {
      for (size_t i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i) {
        liveness[i] |= is_live[i];
        is_live[i] = false;
      }
    }
    void set_liveness_violation(id_t liveness_id) {
      tripped = new ModelPropertyError(*::__info__::LIVENESS_INFOS[liveness_id]);
      status = Result::PROPERTY_VIOLATED;
    }
# else
    bool liveness_handler(bool expr, id_t liveness_id, id_t prop_id) {
      return false;  // BFS does not currently implement liveness
    }
# endif

    // called when trying to print the results of the BFS walker when it finishes (will finish up trace file if necessary too)
    //  the calling context should ensure that the BFSWalker is not being used else where & safe output to the ostream
    friend ostream_p& operator << (ostream_p& out, const BFSWalker& rw) {
      std::string res_color = get_color(rw.status);
      out << out.nl()
          << "======== BEGIN :: Report of BFS ERROR ========"                         << out.nl()
          << "BASIC INFO: "                                                           << out.indent() << out.nl()
          << "      Depth: " << rw._depth                                             << out.nl()
          << "   Start ID: " << rw._start_id                                          << out.nl()
          << " StartState: " << ::__caller__::STARTSTATES[rw._start_id]               << out.nl()
          << "     Result: " << res_color << std::to_string(rw.status) << "\033[0m"   << out.nl()
          << out.dedent()                                                             << out.nl()
          << "TRACE LITE:"                                            << out.indent() << out.nl();
      if (rw.OPTIONS.do_trace)
        out << "NOTE - BFS does not currently support rich json traces" << out.nl();
      out << "History: ["                             << out.indent() << out.indent() << out.nl()
          << "-(0) " << ::__caller__::STARTSTATES[rw._start_id] << '\n';
        if (rw.history_start > 0)
          out << out.indentation() << "-(..) ... forgotten past ...\n";
        for (size_t i=rw.history_start; i<rw.history_level; ++i)
          out << out.indentation() << "-(" << i+1 <<") " << *(rw.history[i%rw.history_size()].rule) << "\n";
      out << out.dedent() << out.indentation() << ']' << out.dedent() << out.dedent();
      if (rw.OPTIONS.report_emit_state)
        out                                                                           << out.nl()
            << "  State: " <<  out.indent() << out.indent() << rw.state << out.dedent() << out.dedent();
      if (rw.tripped != nullptr || rw.tripped_inside != nullptr) {
        out                                                                           << out.nl()
            << "ISSUE REPORT:"                                        << out.indent() << out.nl();
        if (rw.tripped != nullptr) {
          out << "Tripped: \033[31m" << *rw.tripped << "\033[0m"                      << out.nl();
          if (rw.tripped_inside != nullptr)
            out << "  Trace: "                                        << out.indent() << out.nl()
                << *rw.tripped_inside                                 << out.dedent() << out.nl();
                // << '}'                                                               << out.nl();
        }
      }
      if (rw.put_msgs.size() > 0) {
        out << "Put Statements: \"\"\""               << out.indent() << out.indent() << out.nl();
        for (auto msg : rw.put_msgs) {
          try {
            msg.first(out);
          } catch (std::exception& ex) {
            out << out.indent() << out.nl() << msg.second << " :: error occurred while evaluating put statement"
                << out.nl() << ex << out.dedent() << out.nl();
          }
        }
        out << out.dedent() << out.nl() << "\"\"\"" << out.dedent() << out.nl();
      }

#     ifdef __ROMP__DO_MEASURE
        out << out.dedent()                                                         << out.nl()
            << "TIME REPORT:"                                       << out.indent() << out.nl()
            << "Active Time: " << rw.active_time                                    << out.nl();
#     endif
      out << out.dedent()                                                           << out.nl()
          << "======== END :: Report of BFS ERROR ========"                         << out.nl();
      out.out.flush();

      return out;
    }
    // called when trying to print the results of the BFS walker when it finishes (will finish up trace file if necessary too)
    //  the calling context should ensure that the BFSWalker is not being used else where & safe output to the ostream
    friend std::ostream& operator << (std::ostream& out, const BFSWalker& rw)
    { ostream_p _out(out,rw.OPTIONS,0); _out << rw; return out; }

    State_t state;
    friend RandWalker;
  };



struct BFSHandler {
protected:
  const Options& OPTIONS;
  std::deque<BFSWalker*> q;
  std::unordered_set<State_t> states;
  size_t rules_applied = 0ul;
  const size_t TARGET;
  time_ms_t start_time;
  ostream_p out;


public:

  BFSHandler(const Options& OPTIONS_)
    : OPTIONS(OPTIONS_),
      TARGET(OPTIONS_.walks / OPTIONS_.bfs_coefficient),
      out(std::cout,OPTIONS_,0)
  {}

  ~BFSHandler() {
    for (BFSWalker* w : q) if (w != nullptr) delete w;
  }

  /**
   * @brief Launch a romp run where we first do a single threaded BFS before
   *        launching the swarm of random walkers.
   * @param OPTIONS the options object defining how the romp run should work.
   *                (required that bfs and do_even start be true)
   */
  void launch() {
    start_time = time_ms();

    // - run through the startstates and add them to the queue ----
    for (size_t i=0; i<_ROMP_STARTSTATES_LEN; ++i) {
      auto walker = new BFSWalker(OPTIONS,i);
      walker->init_state();
      ++rules_applied;
      if (walker->is_done()) {  // discover error during
        end_bfs_report_error(walker);
        return;
      } else if (insert_state(walker->state))
        q.push_back(walker);
    }

    if (OPTIONS.bfs_single) single_bfs();
    else multithreaded_bfs();

  }


protected:
  /**
   * @brief Perform the bfs in a single threaded manner
   *        NOTE: must be called after processing start states
   */
  void single_bfs() {
#   if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
      const bool enable_liveness = OPTIONS.liveness;
      bool liveness[_ROMP_LIVENESS_PROP_COUNT];
#   endif
    while (not q.empty() && q.size()<TARGET && rules_applied < OPTIONS.bfs_limit) {
      auto b_w = q.front();
      q.pop_front();
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        if (enable_liveness) std::memset(liveness,0u,sizeof(bool)*_ROMP_LIVENESS_PROP_COUNT);
#     endif
      for (size_t i=0; q.size()<TARGET && i<_ROMP_RULESETS_LEN; ++i)
        for (auto rule : ::__caller__::RULESETS[i].rules) {
          BFSWalker* walker = (BFSWalker*) std::malloc(sizeof(BFSWalker));
          std::memcpy(walker,b_w,sizeof(BFSWalker)); // copy base walker
          // walker->sim1step(rule);
          walker->sim1Step_no_trace(rule);
          if (walker->is_done()) {
            end_bfs_report_error(walker);
            return;
          }
#         if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
            if (enable_liveness) walker->merge_liveness(liveness);
#         endif
          if (walker->pass) ++rules_applied;
          if (insert_state(walker->state)) {
              q.push_back(walker);
            if (q.size() >= TARGET)
              break;
          } else delete walker;
        }
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        // end if liveness property violated
        if (enable_liveness && (size_t liveness_id = is_live(liveness)) < _ROMP_LIVENESS_PROP_COUNT) {
          b_w->set_liveness_violation(liveness_id);
          end_bfs_report_error(b_w);
          return;
        }
#     endif
      delete b_w;
    }

    if (not q.empty()) {
      end_bfs();
      this->launch_threads();
    } else
      end_bfs_solved();
  }


  /**
   * @brief Perform the bfs in a multithreaded manner
   *        NOTE: must be called after processing start states
   */
  void multithreaded_bfs() {
    //TODO code this part & hope it performs well without too many data race checkpoints
    std::mutex mut_in, mut_out;
    BFSWalker* bad = nullptr;
    std::vector<std::thread> threads;
    size_t cycle = 0ul;

#   ifdef DEBUG
      const auto pause_delay = std::chrono::milliseconds(20); //DEBUG SLOW ME DOWN
      const size_t update_coef = 1<<3;
#   else
      const auto pause_delay = std::chrono::milliseconds(50);
      const size_t update_coef = 1<<4;
#   endif

    std::function<void(BFSWalker*)> end_bfs_with_error_mt = [&] (BFSWalker* w) -> void {
      mut_out.lock();
      bad = w;
      mut_out.unlock();
    };

    std::function<void()> lambda_bfs = [&]() -> void {
      std::vector<BFSWalker*> buffer;
      const size_t bfs_limit = OPTIONS.bfs_limit;
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        const bool enable_liveness = OPTIONS.liveness;
        bool liveness[_ROMP_LIVENESS_PROP_COUNT];
#     endif
      mut_in.lock();
      mut_out.lock();
      while (not q.empty() && q.size()<TARGET && rules_applied < bfs_limit && bad == nullptr) {
        mut_out.unlock();
        auto b_w = q.front();
        q.pop_front();
        mut_in.unlock();
#       if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
          if (enable_liveness) std::memset(liveness,0u,sizeof(bool)*_ROMP_LIVENESS_PROP_COUNT);
#       endif
        for (size_t i=0; /*q.size()<TARGET &&*/ i<_ROMP_RULESETS_LEN; ++i)
          for (auto rule : ::__caller__::RULESETS[i].rules) {
            BFSWalker* walker = (BFSWalker*) std::malloc(sizeof(BFSWalker));
            std::memcpy(walker,b_w,sizeof(BFSWalker)); // copy base walker
            // walker->sim1step(rule);
            walker->sim1Step_no_trace(rule);
            if (walker->is_done()) {
              end_bfs_with_error_mt(walker);
              return;
            }
#           if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
              if (enable_liveness) walker->merge_liveness(liveness);
#           endif
            buffer.push_back(walker);
            // if (insert_state(walker->state)) {
            //   // ++rules_applied;
            //   // if (q.size() >= TARGET) break;
            // }
          }
#       if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
          // end if liveness property violated
          if (enable_liveness && (size_t liveness_id = is_live(liveness)) < _ROMP_LIVENESS_PROP_COUNT) {
            b_w->set_liveness_violation(liveness_id);
            end_bfs_with_error_mt(b_w);
            return;
          }
#       endif
        mut_out.lock();
        if (bad != nullptr) return; // end early if another thread found an error
        mut_out.unlock();
        mut_in.lock();
        for (BFSWalker* w : buffer) {
          if (w->pass) ++rules_applied;
          if (insert_state(w->state)) {
            q.push_back(w);
          } else delete w;
        }
        buffer.clear();
        delete b_w;
        mut_out.lock();
      }
      mut_out.unlock();
      mut_in.unlock();
    };

    for (size_t i=0; i<OPTIONS.threads; ++i) {
      threads.push_back(std::thread(lambda_bfs));
    }

    out << "\n\033[34;1m"
          "=====================================\n"
          "  INITIAL BFS MULTITHREADED STATUS:  \n"
          "=====================================\n"
          "\033[0m\n\n";
    out.out.flush();
    std::this_thread::sleep_for(pause_delay*2);

    mut_in.lock();
    mut_out.lock();
    while (not q.empty() && q.size()<TARGET && rules_applied < OPTIONS.bfs_limit && bad == nullptr) {
      mut_out.unlock();
      // if (cycle % update_coef == 0) {
      //   out << out.indentation()
      //       << '[' << (time_mr() - start_time) << "] "
      //         "States found: " << states.size() << "; "
      //         "Rules Applied: " << rules_applied << "; "
      //         "BFS Progress: " << ((long long)((q.size()*100)/(TARGET*100)))
      //       << " (" << q.size() << '/' << TARGET << ");\n";
      //   mut_in.unlock();
      //   out.out.flush();
      // } else
        mut_in.unlock();
      // ++cycle;
      std::this_thread::sleep_for(pause_delay);
      mut_in.lock();
      mut_out.lock();
    }
    mut_in.unlock();
    mut_out.unlock();

    std::this_thread::sleep_for(pause_delay*2); // might be able to skip this
    for (auto& t : threads) {
      t.join(); // might be able to skip this
    }

    if (bad != nullptr) {
      end_bfs_report_error(bad);
      return;
    }

    if (not q.empty()) {
      out << "\n\033[34;1m"
             "=====================================\n"
             "   INITIAL BFS MULTITHREADED DONE    \n"
             "=====================================\n"
             "\033[0m\n\n";
      out.out.flush();
      end_bfs();
      this->launch_threads();
    } else
      end_bfs_solved();
    /* Ideas
        - short term store new states in vector per threads then lock to add new states in bulk
    */
  }

  /**
   * @brief Launch threads with a collection of states to start with
   */
  void launch_threads() {
    states.clear(); // clear states to free up memory
    // RandWalker::reset_ids();
    auto tmp_seeds = gen_random_seeds(OPTIONS,OPTIONS.rand_seed);
    std::vector<BFSWalker*> l(q.begin(),q.end()); // transfer contents for speed later
    std::queue<RandSeed_t> in_seeds(std::deque<RandSeed_t>(tmp_seeds.begin(),tmp_seeds.end()));
    // std::queue<RandWalkers*> parallel_rws; // probs threads
    std::queue<RandWalker*> out_rws;
    size_t walks_done = 0;
    std::mutex in_queue;
    std::mutex out_queue;
    size_t cycles = 0ul;
    size_t progress = 0ul;
    // std::mutex _in_queue_mutex;
    // std::mutex _out_queue_mutex;

#   ifdef DEBUG
      const auto pause_delay = std::chrono::milliseconds(250); //DEBUG SLOW ME DOWN
      const size_t update_coef = 1<<6;
#   else
      const auto pause_delay = std::chrono::milliseconds(20);
      const size_t update_coef = 1<<8;
#   endif

    auto lambda = [&]() { // code the threads run
      in_queue.lock();
      while (in_seeds.size() > 0) {
        in_seeds.front(); RandWalker *rw = new RandWalker(*l[in_seeds.size()%OPTIONS.bfs_coefficient%l.size()],
                                                          in_seeds.front(),OPTIONS);
        in_seeds.pop();
        in_queue.unlock();

        // rw->init(); // no need to init when starting from bfs
        while (not rw->is_done())
          rw->sim1Step();
        rw->finalize();

        out_queue.lock();
        out_rws.push(rw);
        ++walks_done;
        out_queue.unlock();

        in_queue.lock();
      }
      in_queue.unlock();
    };

    ostream_p out(std::cout,OPTIONS,0);
    std::vector<std::thread> threads;
    ResultTree summary(OPTIONS);
    // std::vector<std::thread> threads(OPTIONS.threads);
    for (size_t i=0; i<OPTIONS.threads; ++i) {
      threads.push_back(std::thread(lambda));
    }
    // std::lock_guard<std::mutex> in_queue(_in_queue_mutex);
    // std::lock_guard<std::mutex> out_queue(_out_queue_mutex);

    out << "\n\033[34;1m"
          "==================================\n"
          "   PARALLEL RANDOM WALK STATUS:   \n"
          "==================================\n"
          "\033[0m\n\n";
    out.out.flush();

    std::this_thread::sleep_for(pause_delay*2);
    while (true) {
      while (true) {  // handel outputs
        // if (cycles % update_coef == 0) { // this really slows things down
        //   out.indent();
        //   out << '[' << (time_ms() - start_time) << "] "
        //       << progress << '/' << OPTIONS.walks
        //       << " walks complete" << out.nl();
        //   out.dedent();
        //   out.out.flush();
        // }
        ++cycles;
        std::this_thread::sleep_for(pause_delay);
        out_queue.lock();
        if (not (out_rws.size() > 0)) {
          out_queue.unlock();
          break;
        }
        RandWalker* rw = out_rws.front();
        out_rws.pop();
        out_queue.unlock();
        if (rw != nullptr) {
          ++progress;
          if (rw->do_report())
            std::cout << *rw << std::endl;
          // todo get the results
          summary.insert(rw->get_result());
          delete rw;
        }
      }

      std::this_thread::sleep_for(pause_delay);
      out_queue.lock();
      if (not (walks_done < OPTIONS.walks)) {
        out_queue.unlock();
        break;
      }
      out_queue.unlock();
    }
    // we might need to do this one more time for the last one

    summary.stop_timer();

    for (size_t i=0; i<OPTIONS.threads; ++i) // join threads
      threads[i].join();

    print_romp_results_summary(summary);
    out.indent();
    out << out.nl() << "Actual Runtime: " << (time_ms()-start_time) << "\n\n";
    out.dedent();
    out.out.flush();
  }


  /**
   * @brief Helper function to insert states into the state hash set
   * @param state the state to be hashed and stored in the state.
   * @return \c bool - true if the state is a new addition false if seen before
   */
  inline bool insert_state(const State_t& state) {
    return std::get<1>(states.insert(state));
  }

# if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
    size_t was_live(bool* is_live) const {
      for (size_t i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i)
        if (not is_live[i]) return i;
      return _ROMP_LIVENESS_PROP_COUNT;
    }
# endif

  /**
   * @brief call when an error occurs during BFS (ends run early)
   *        NOTE: will delete walker
   * @param walker the walker that finished its run (will be deleted during call)
   */
  inline void end_bfs_report_error(BFSWalker* walker) {
    auto t = time_ms() - start_time;
    walker->finalize();
    std::string color = "\033[30;1;4m";
    out << '\n' << out.nl()
        << "Error found during initial BFS"
        << out.nl() << *walker << '\n'
        << out.nl() << "\033[1;4mBFS SUMMARY:\033[0m" << out.indent()
        << out.nl() << "Error found see above for details"
        << out.nl() << "    States Found: " << states.size()
        << out.nl() << "   Rules Applied: " << rules_applied
        << out.nl() << "  Actual Runtime: " << t
        << "\n\n";
    delete walker;
    out.out << std::flush;
  }

  /**
   * @brief call when bfs ends with no new items in the queue
   */
  inline void end_bfs_solved() {
    auto t = time_ms() - start_time;
    std::string color = "\033[32;1m";
    out << out.nl()
        << "NO ERRORS found!  BFS had FULL COVERAGE!"
        << out.nl() << "\033[1;4mBFS SUMMARY:\033[0m" << out.indent()
        << out.nl() << "    States Found: " << states.size()
        << out.nl() << "   Rules Applied: " << rules_applied
        << out.nl() << "  Actual Runtime: " << t
        << "\n\n";
    out.out << std::flush;
  }

  inline void end_bfs() {
    auto t = time_ms() - start_time;
    out << out.nl()
        << "NO ERRORS found during initial BFS\n"
        << out.nl()
          << ((rules_applied >= OPTIONS.bfs_limit)
                ? "WARNING : BFS limit was reached, statespace might not have been sufficiently explored before launching the walkers !!\n"
                : std::string(""))
        << out.nl() << "\033[1;4mBFS SUMMARY:\033[0m" << out.indent()
        << out.nl() << "    States Found: " << states.size()
        << out.nl() << "   Rules Applied: " << rules_applied
        << out.nl() << "     BFS Runtime: " << t
        << "\n\n";
    out.out << std::flush;
  }

};


} // namespace romp
/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file impls.cpp
 *
 * @brief implementations of functions that could not be put where they were declared,
 *        because they required something pre-decl'ed to be fully declared first.
 *
 * @date 2022/10/05
 * @version 0.1
 */

#ifndef __romp__GENERATED_CODE
#pragma once
#include "pregen-fix.hpp"  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "include.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "decl.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "writers.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "types.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "error.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
// #include "walker.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif

namespace romp {

  template<size_t EID, size_t B, class... U_M>
  inline void __assign(EnumType<EID,B>& _this, const ScalarsetUnionType<U_M...>& other) { _this = other.__get_value(); }
  template<size_t EID, size_t B, class... U_M>
  inline void __assign(ScalarsetType<EID,B>& _this, const ScalarsetUnionType<U_M...>& other) { _this = other.__get_value(); }

  Result::~Result() { if (tripped != nullptr) delete tripped; if (inside != nullptr) delete inside; }

  // template<size_t L_ID, size_t L_B, size_t R_ID, size_t R_B>
  // inline bool operator == (const EnumType<L_ID,L_B>& l, const EnumType<R_ID,R_B> r) {
  //   return ((L_ID == R_ID) // this static expr should help the compiler optimize this per type definition.
  //           && (l.value == r.value));
  // }
  // template<size_t L_ID, size_t L_B, size_t R_ID, size_t R_B>
  // inline bool operator != (const EnumType<L_ID,L_B>& l, const EnumType<R_ID,R_B> r) {
  //   return ((L_ID != R_ID) // this should help the compiler optimize this per type definition.
  //           || (l.value != r.value));
  // }

  // template<class... L_M, class... R_M>
  // inline bool operator == (const ScalarsetUnionType<L_M...>& l, const ScalarsetUnionType<R_M...> r) { return l.value == r.value; }
  // template<class... L_M, class... R_M>
  // inline bool operator != (const ScalarsetUnionType<L_M...>& l, const ScalarsetUnionType<R_M...> r) { return l.value != r.value; }

//   template<size_t EID, size_t B, class... U_M>
//   inline bool operator == (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u) {
// #   if __cplusplus >= 201703L
//       return ((ScalarsetUnionType<U_M...>::ContainsMember<EID,B>()) // this should help the compiler optimize this per specific templated instance. [[requires c++17]] to be static
//               && (e.value == u.value));
// #   else
//       return e.value == u.value;
// #   endif
//   }
//   template<size_t EID, size_t B, class... U_M>
//   inline bool operator != (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u) {
// #   if __cplusplus >= 201703L
//       return (not (ScalarsetUnionType<U_M...>::ContainsMember<EID,B>()) // this should help the compiler optimize this per specific templated instance. [[requires c++17]]
//               || (e.value != u.value));
// #   else
//       return e.value != u.value;
// #   endif
//   }
//   template<class... U_M, size_t EID, size_t B>
//   inline bool operator == (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e) { return (e == u); }
//   template<class... U_M, size_t EID, size_t B>
//   inline bool operator != (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e) { return (e != u); }

  // /* this IsMember is the one associated with the IsMember() Murphi language operator */
  // template<class ET, typename VT>
  // inline bool IsMember(const VT& u) {
  //   return ET::IsMember(u.__get_value());
  // }
  // template<size_t EID, size_t B, class... U_M>
  // inline bool IsMember(const ScalarsetUnionType<U_M...>& u) {
  //   return EnumType<EID,B>::IsMember(u.value);
  // }

  // << ------------------------------------------------------------------------------------------ >>

  ostream_p::ostream_p(std::ostream& out_, const Options& OPTIONS_, unsigned int level_)
    : out(out_), _width(level_*OPTIONS_.tab_size), OPTIONS(OPTIONS_)
    { _indentation = std::string(_width,OPTIONS_.tab_char); }
  inline const stream_void ostream_p::dedent() {
    if (((signed)_width)-((signed)OPTIONS.tab_size) >= 0)
      _width-=OPTIONS.tab_size;
    _indentation = std::string(_width,OPTIONS.tab_char);
    return S_VOID;
  }
  inline const stream_void ostream_p::indent() { _indentation = std::string((_width+=OPTIONS.tab_size),OPTIONS.tab_char); return S_VOID; }

  // << ------------------------------------------------------------------------------------------ >>

  ResultTree::~ResultTree() {
    for (auto p : unknown_causes) if (p!=nullptr) delete p;
    for (auto p : attempt_limits_reached) if (p!=nullptr) delete p;
    for (auto p : max_depths_reached) if (p!=nullptr) delete p;
#ifdef __romp__ENABLE_cover_property
    for (auto p : completed_covers) if (p!=nullptr) delete p;
#endif
    for (auto _p : properties_violated)
      for (auto p : _p.second) if (p!=nullptr) delete p;
    for (auto _p : merrors_reached)
      for (auto p : _p.second) if (p!=nullptr) delete p;
#ifdef __romp__ENABLE_assume_property
    for (auto _p : assumptions_violated)
      for (auto p : _p.second) if (p!=nullptr) delete p;
#endif
  }

  void ResultTree::insert(const Result* res) {
    switch (res->cause) {
      case Result::ATTEMPT_LIMIT_REACHED:
        attempt_limits_reached.push_back(res);
        break;
      case Result::MAX_DEPTH_REACHED:
        max_depths_reached.push_back(res);
        break;
      case Result::PROPERTY_VIOLATED: {
        const auto _me_p = dynamic_cast<const ModelPropertyError*>(res->tripped);
        if (properties_violated.find(*_me_p) == properties_violated.end())
          properties_violated[*_me_p] = std::vector<const Result*>{res};
        else
          properties_violated[*_me_p].push_back(res);
        ++n_properties_violated;
        break;
      }
      case Result::MERROR_REACHED: {
        const auto _me_e = dynamic_cast<const ModelMErrorError*>(res->tripped);
        if (merrors_reached.find(*_me_e) == merrors_reached.end())
          merrors_reached[*_me_e] = std::vector<const Result*>{res};
        else
          merrors_reached[*_me_e].push_back(res);
        ++n_merrors_reached;
        break;
      }
#ifdef __romp__ENABLE_assume_property
      case Result::ASSUMPTION_VIOLATED: {
        const auto _me_a = dynamic_cast<const ModelPropertyError*>(res->tripped);
        if (assumptions_violated.find(*_me_a) == assumptions_violated.end())
          assumptions_violated[*_me_a] = std::vector<const Result*>{res};
        else
          assumptions_violated[*_me_a].push_back(res);
        ++n_assumptions_violated;
        break;
      }
#endif
#ifdef __romp__ENABLE_cover_property
      case Result::COVER_COMPLETE:
        completed_covers.push_back(res);
        break;
#endif
      case Result::UNKNOWN_CAUSE:
      default:
        unknown_causes.push_back(res);
        break;
    }
#ifdef __ROMP__DO_MEASURE
    total_walk_active_time += res->active_time;
    total_walk_time += res->total_time;
#endif
    ++size;
    rules_fired += res->depth;
  }

  std::ostream& operator << (std::ostream& out, const ResultTree& results) {
    ostream_p _out(out, results.OPTIONS, 0);
    _out << results;
    return out;
  }

  ostream_p& operator << (ostream_p& out, const ResultTree& r) {
    int i = 1; // int j = 1;
    size_t issues = 0; size_t abs_issues = 0;
#ifdef __romp__ENABLE_assume_property
    if (r.OPTIONS.r_assume && r.n_assumptions_violated > 0) {
      issues += r.assumptions_violated.size();
      abs_issues += r.n_assumptions_violated;
      out << out.indentation() << "\033[1;4mASSUMPTION(S) VIOLATED (n="<< r.assumptions_violated.size()
          << " |n|=" << r.n_assumptions_violated << "):\033[0m\n";
      out.indent(); i = 1;
      for (const auto& _a : r.assumptions_violated) {
        if (i > _ROMP_HIST_LEN && not (r.OPTIONS.report_all || r.OPTIONS.report_error)) {
          out << out.indentation() << "-(..) ... " << _a.second.size()-(i-1) << " more ...\n";
          break;
        }
        out << out.indentation()
            << "\033[1m-(" << (i++) << ") assume \"" << _a.first.label() << "\":\033[0m\n";
        out.indent();
        for (const auto& a : _a.second) {
          out << out.indentation()
              << "-[w#" << a->id << "] seed=" << a->root_seed << " start-id=" << a->start_id <<" depth=" << a->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << a->active_time << " (Δt=" << a->total_time << ')';
#endif
          if (not a->tripped->is_flat())
            out << out.nl()
                << "        quantifiers(" << a->tripped->quants() << ")\n";
          out << out.indentation()
              << ((a->tripped->is_generic())
                  ? "        inside"
                  : "        last-rule")
              << "={"
              << a->inside->get_type()
              <<" \"" << a->inside->label() << "\"";
          if (not a->inside->is_flat())
              out << " quantifiers(" << a->inside->quants() << ")";
          out << "}\n";
        }
        out.dedent();
        ++i;
      }
      out.out << out._dedent() << std::endl;
    }
#endif
    if ((r.OPTIONS.attempt_limit != _ROMP_ATTEMPT_LIMIT_DEFAULT && r.OPTIONS.deadlock)
          && r.attempt_limits_reached.size() > 0) {
        out << out.indentation() << "\033[1;4mATTEMPT LIMIT(S) REACHED (n="
                << r.attempt_limits_reached.size() << "):\033[0m\n";
        out.indent();
        i = 1;
        for (const auto& _al : r.attempt_limits_reached) {
          if (i > _ROMP_HIST_LEN && not (r.OPTIONS.report_all)) {
            out << out.indentation() << "-(..) ... " << r.attempt_limits_reached.size()-(i-1) << " more ...\n";
            break;
          }
          out << out.indentation()
              << "-(" << i << ") [w#" << _al->id << "] seed=" << _al->root_seed << " start-id=" << _al->start_id <<" depth=" << _al->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << _al->active_time << " (Δt=" << _al->total_time << ')';
#endif
          out << out.nl()
              << "        last-rule=";
          if (_al->inside != nullptr) {
            out << '{' << _al->inside->get_type() << " \"" << _al->inside->label() << "\"";
            if (not _al->inside->is_flat())
              out << " quantifiers(" << _al->inside->quants() << ")";
            out << "}\n";
          } else {
            out << "none\n";
          }
          ++i;
        }
      out.out << out._dedent() << std::endl;
     }
#ifdef __romp__ENABLE_cover_property
     if (r.OPTIONS.r_cover && r.completed_covers.size() > 0) {
      out << out.indentation() << "\033[1;4mCOVER(S) COMPLETED (n="
                << r.completed_covers.size() << "):\033[0m\n";
        out.indent();
        i = 1;
        for (const auto& _c : r.completed_covers) {
          if (i > _ROMP_HIST_LEN+1 && not (r.OPTIONS.report_all)) {
            out << out.indentation() << "-[..] ... " << r.completed_covers.size()-(i-1) << " more ...\n";
            break;
          }
          out << out.indentation()
              << "-(" << i << ") [w#" << _c->id << "] seed=" << _c->root_seed << " start-id=" << _c->start_id <<" depth=" << _c->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << _c->active_time << " (Δt=" << _c->total_time << ')';
#endif
          out << out.nl()
              << "        last-rule={" << _c->inside->get_type() << " \"" << _c->inside->label() << "\"";
              if (not _c->inside->is_flat())
                out << " quantifiers(" << _c->inside->quants() << ")";
          out << "}\n";
          ++i;
        }
      out.out << out._dedent() << std::endl;
     }
#endif
    if (r.OPTIONS.report_all && r.max_depths_reached.size() > 0) {
      out << out.indentation() << "\033[1;4mMAX DEPTH(S) REACHED (n="
                << r.max_depths_reached.size() << "):\033[0m";
        out.indent();
        i = 1;
        for (const auto& _r : r.max_depths_reached) {
          if (i > _ROMP_HIST_LEN && not (r.OPTIONS.report_all)) {
            out << out.indentation() << "-(..) ... " << r.max_depths_reached.size()-(i-1) << " more ...\n";
            break;
          }
            out << out.nl()
              << "-(" << i++ << ") [w#" << _r->id << "] seed=" << _r->root_seed << " start-id=" << _r->start_id;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << _r->active_time << " (Δt=" << _r->total_time << ')';
#endif
        }
      out.out << out._dedent() << std::endl;
    }
    if (r.n_merrors_reached > 0) {
      issues += r.merrors_reached.size();
      abs_issues += r.n_merrors_reached;
      out << out.indentation() << "\033[1;4mERROR STATEMENT(S) REACHED (n="<< r.merrors_reached.size()
          << " |n|=" << r.n_merrors_reached << "):\033[0m\n";
      out.indent(); i = 1;
      for (const auto& _a : r.merrors_reached) {
        out << out.indentation()
            << "\033[1m-(" << (i++) << ") error \"" << _a.first.label() << "\":\033[0m\n";
        out.indent();
        int j = 0;
        for (const auto& a : _a.second) {
          if (j > _ROMP_HIST_LEN && not (r.OPTIONS.report_all || r.OPTIONS.report_error)) {
            out << out.indentation() << "-[..] ... " << _a.second.size()-j << " more ...\n";
            break;
          }
          out << out.indentation()
              << "-[w#" << a->id << "] seed=" << a->root_seed << " start-id=" << a->start_id <<" depth=" << a->depth
#ifdef __ROMP__DO_MEASURE
              << " t=" << a->active_time << " (Δt={" << a->total_time << ')'
#endif
              << out.nl()
              << "        IN-RULE"
              << "={" << a->inside->get_type() << " \"" << a->inside->label() << "\"";
          if (not a->inside->is_flat())
              out << " quantifiers(" << a->inside->quants() << ")";
          out << "}\n";
        }
        out.dedent();
        ++i;
      }
      out.out << out._dedent() << std::endl;
    }
    if (r.n_properties_violated > 0) {
      issues += r.properties_violated.size();
      abs_issues += r.n_properties_violated;
      out << out.indentation() << "\033[1;4mPROPERTY(S) VIOLATED (n="<< r.properties_violated.size()
          << " |n|=" << r.n_properties_violated << "):\033[0m\n";
      out.indent(); i = 1;
      for (const auto& _a : r.properties_violated) {
        const PropertyInfo& _info =_a.first.info();
        out << out.indentation()
            << "\033[1m-(" << (i) << ") " << _info.type << " \"" << _info.label << "\":\033[0m "
                "(x"<< _a.second.size() <<")\n";
        out.indent();
        int j = 0;
        for (const auto& a : _a.second) {
          if (j > 2 && not (r.OPTIONS.report_all || r.OPTIONS.report_error)) {
            out << out.indentation() << "-[..] ... " << _a.second.size()-j << " more ...\n";
            break;
          }
          out << out.indentation()
              << "-[w#" << a->id << "] seed=" << a->root_seed << " start-id=" << a->start_id <<" depth=" << a->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << a->active_time << " (Δt=" << a->total_time << ')';
#endif
          if (not a->tripped->is_flat())
            out << out.nl()
                << "        quantifiers(" << a->tripped->quants() << ")";
          out << out.nl()
              << ((a->tripped->is_generic())
                  ? "        inside"
                  : "        last-rule")
              << "={"
              << a->inside->get_type()
              <<" \"" << a->inside->label() << "\"";
          if (not a->inside->is_flat())
              out << " quantifiers(" << a->inside->quants() << ")";
          out << "}\n";
          ++j;
        }
        out.dedent();
        ++i;
      }
      out.out << out._dedent() << std::endl;
    }
    if (r.OPTIONS.report_all && r.unknown_causes.size() > 0) {
      issues += r.unknown_causes.size();
      abs_issues += r.unknown_causes.size();
      out << out.indentation() << "\033[41;37;1;4mUNKNOWN ERROR(S) (n="
                << r.unknown_causes.size() << "):\033[21;24m\n";
        out.indent();
        i = 1;
        for (const auto& _r : r.unknown_causes) {
          out << out.indentation()
              << "-(" << i++ << ") ``" << ({_r->inside->write_root_excpt_what(out.out); "''\n";})
              << out._indent()
              << "-[w#" << _r->id << "] seed=" << _r->root_seed << " start-id=" << _r->start_id << " depth=" << _r->depth
#ifdef __ROMP__DO_MEASURE
              << " t=" << _r->active_time << " (Δt=" << _r->total_time << ")\n"
#endif
              << "        inside={"
              << _r->inside->get_type()
              << " \"" << _r->inside->label() << '"';
          if (not _r->inside->is_flat())
            out << " quantifiers(" << _r->inside->quants() << ")";
          out << "}\n";
          out.dedent();
        }
      out.out << out._dedent() << "\033[0m" << std::endl;
    }
    std::string color = ((issues>0) ? "\033[30;1;4m" : "\033[32;1m");
    out << out.nl()
        << out.nl() << "\033[1;4mRW SUMMARY:\033[0m" << out.indent()
        << out.nl() << "       issues found: n=" << color << issues << "\033[0m"
                                          << "  (|n|=" << color << abs_issues << "\033[0m)"
        << out.nl() << "total rules applied: " << r.rules_fired
        << out.nl() << "  avg rules applied: " << std::setprecision(1) << (r.rules_fired/r.size)
#ifndef __ROMP__DO_MEASURE
        << out.nl() << "            runtime: " << r.get_time();
#else
        << out.nl() << "    total walk time: t=" << r.total_walk_active_time << " "
                                          "(Δt=" << r.total_walk_time << ")"
        << out.nl() << "     mean walk time: mean(t)=" << (r.total_walk_active_time/r.size) << " "
                                           "(mean(Δt)=" << (r.total_walk_time/r.size) << ')'
        << out.nl() << "         RW runtime: " << r.get_time();
#endif
    out.out << "\n\n" << std::flush;
    return out;
  }


void print_help() {
  using namespace std;
  Options default_opts;
  // clang-format off
  std::cout <<
    "This is a murphi model checker generated from the romp random walker tool.\n"
    "   generated from: " __model__filename "\n"
    "\n\n"
    "CLI USAGE:    <> - required  {} - optional  * - can have 0 or more\n"
    "   ./<this-file> {options}*\n"
    "\n\n"
    "NOTE:\n"
    "  Option flags and arguments are NOT POSIX compliant!\n"
    "  Please separate all options and their arguments with spaces,\n"
    "   and do not join multiple short option flags into one.\n"
    "    (i.e. `-s <str/int>` and `-y` must be input as\n"
    "          ``-y -s 5`` and NOT ``-ys 5``, ``-ys5``, \n"
    "            ``-ys=5``, ``-y -s=5``, or ``-y --seed=5``)\n"
    "\n"
    "GENERAL OPTIONS:\n"
    "   -h | --help      Display help information (this page).\n"
    "   -y | -l          Launch without prompting (skip launch prompt).\n"
    "   --list-starts    Output a list of all the ruleset expanded\n"
    "     | -ls            startstates & their id's\n"
    "                     (see --start-id/-sid for more info)\n"
    "\n"
    "RANDOM WALKER OPTIONS:\n"
    "  --depth <int>     Maximum number of rules to apply in a walk \n"
    "    | -d <int>        before termination.\n"
    "                      default: " << default_opts.depth << "\n"
    "  --threads <int>   Specifies the number of threads to use.\n"
    "    | -ptn <int>      default: " << default_opts.threads << " (machine specific)\n"
    "  --walks <int>     Specifies the number of random  walks to do.\n"
    "     | -w <int>       default: " << _ROMP_THREAD_TO_RW_RATIO << " * #-of-threads\n"
    "  --single-walk     Perform a single random walker on a single thread.\n"
    "     | -sw            note: overrides -ptn/--threads \n"
    "                              & -w/--walks/--walk-count\n"
    "  --seed <str/int>  Random seed for generating the random walks\n"
    "    | -s <str/int>    default: current system time\n"
    "  --even-start      Determine startstate for even distribution\n"
    "    | -es             rather than random choice (default behavior).\n"
    "  --start-id <id>   Set a single startstate to use (For all walks).\n"
    "    | -sid <id>       <id> is an int determined by a startstate's\n"
    "                      position in the file after ruleset expansion.\n"
    "                      Valid <id> values are integers between:\n"
    "                         0 to " << _ROMP_STARTSTATES_LEN-1 << " inclusive\n"
    "                      Use -ls/--list-starts to see mappings of id's\n"
    "                        to the ruleset expanded startstates of\n"
    "                        of your model.\n"
    "                      NOTE: overrides --even-start/-es\n"
    "\n"
    "INITIAL BFS CONFIGURATION:\n"
    "You can start your romp with a limited Breadth first search by using the\n"
    " following command.  This can allow you to increase the likely converge of the\n"
    " statespace covered by each romp, but does prevent you from using the normal\n"
    " strategy of using a mass romp then repeating walks of interest in a \n"
    " single walk with traces enabled.  This is because the pseudo random nature of\n"
    " the romp process is not preserved through the BFS process.  We recommend\n"
    " instead just rerunning the same config with traces enabled if you need more\n"
    " detailed information, it may be slower but it will work.\n"
    "  --bfs {single|multi} {int}  Enables an initial Breadth First Search of the\n"
    "    | -bfs {s|m} {int}          statespace, that is either single threaded or\n"
    "                                multithreaded (defaults to single).\n"
    "                                The BFS will terminate and a swarm of random\n"
    "                                walkers will start when there are enough\n"
    "                                unique states in the BFS queue to have the\n"
    "                                number of walkers specified with the `-w` flag\n"
    "                                where each unique state gets {int} random walks\n"
    "                                to increase the total coverage\n"
    "                                ({int} defaults to " << default_opts.bfs_coefficient << ").\n"
    "  --bfs-limit <int>           Sets a limit on how long the initial BFS can go\n"
    "    | -bfsl <int>               on for.  This is measured in number of rules\n"
    "                                applied. (<int> defaults to " << default_opts.bfs_limit << ")\n"
    "\n"
    "PROPERTY CONFIGURATIONS:\n"
    "  --no-deadlock           Disable Deadlock detection.\n"
    "    | -nd                   (overrides all property options below)\n"
#ifdef __romp__ENABLE_liveness_property
    "  --liveness-check {int}  Allows you to enable a heuristic test for\n"
    "    | -lc {int}             rumur's liveness property. Where it \n"
    "                            require the properties expr to resolve\n"
    "                            to true with in {int} rule applications\n"
    "                            since the start or the last time it was\n"
    "                            true."
    "                            {int} - an optional arg (see above).\n"
    "                              default: " << default_opts.lcount << "\n"
#endif
#ifdef __romp__ENABLE_cover_property
    "  --complete-on-cover {int} Allows you to enable a heuristic test"
    "    | --cover-check {int}     for rumur's cover property. Where it\n"
    "    | -cc {int}               considers a walk complete once every\n"
    "                              cover property has been reached {int}\n"
    "                              times.\n"
    "                              {int} - an optional arg (see above).\n"
    "                                default: " << default_opts.cover_count << "\n"
#endif
    "  --attempt-guard {int}   Stop a random walk if no randomly \n"
    "    | -ag {int}             selected rule can be applied to a State\n"
    "                            after {int} many rules in a row.\n"
    "                            {int} - an optional arg (see above).\n"
    "                              (default: 2x #-of-rules in the model)\n"
    "  --loop-limit {int}      Same thing as --attempt-guard/-ag. \n"
    "    | -ll {int}             {int} - an optional arg (see above).\n"
    "                              (default: 2x #-of-rules in the model)\n"
    "\n"
    "Trace Options\t\n"
    "  --trace {dir-path}    Enable detailed traces to be made for every\n"
    "    | -t {dir-path}       random walk performed. Outputs as a \n"
    "                          separate ``compressed json'' file for \n"
    "                          each random walk performed.\n"
    "                          NOTE: slows down the process noticeably!\n"
    "                          {dir-path} - (optional) the directory you\n"
    "                            want to have the trace files output to.\n"
    "                            default: \""<< default_opts.trace_dir <<"\"\n"
    "\n"
    "RESULT OUTPUT OPTIONS:\n"
    "  --report-error        Provide detailed report for each walk that\n"
    "    | -re                 ends in an ``error''.\n"
    "    | -e                  (aka: violates a property or reaches a \n"
    "                            murphi error statement)\n"
    "                          (NOTE: --single-walk/-sw only outputs \n"
    "                            this and not the summery data)"
    "  --report-all          Report on all walks not just those with \n"
    "    | --all              ``errors''. Including those stopped by \n"
    "    | -a                  the --attempt-guard/-ag/--loop-limit/-ll\n"
    "                          option, or max --depth/-d being reached.\n"
#ifdef __romp__ENABLE_assume_property
    "                          This also performs --report-assume/-ra.\n"
    "  --report-assume       Report walks that are violate an assume\n"
    "    | --r-assume          property (defined by rumur), rather than\n"
    "    | -ra                 just discarding them as invalid states.\n"
    "                          (NOTE: only effective if --report-error\n"
    "                            is provided)\n"
#endif
#ifdef __romp__ENABLE_cover_property
    "                          This also performs --report-assume/-ra.\n"
    "  --report-cover        Report walks that ``complete on cover''\n"
    "    | --r-cover           (see --complete-on-cover for more info)\n"
    "    | -rc                 \n"
#endif
  //  "  --r-history <int>     Specify how much of a history of rules\n"
  //  "    | -rhl <int>          applied you want to see in a walks report\n"
  //  "                          <int> - (required) size of history buffer\n"
  //  "                            default: " << default_opts.history_length << "\n"
  //  "                          NOTE: larger the size == more RAM used.\n"
    "  --r-omit-state        Don't output the values in the model state\n"
    "    | -ros                in the results\n"
    "  --r-show-type         Output variable type next to name when\n"
    "    | -rst                reporting the value of the model state\n"
    "  --r-tab-size <int>    Set the indentation size for the result \n"
    "    | -rts <int>          output (NOTE: not used for trace output)\n"
    "                          (default: "<< default_opts.tab_size <<")\n"
    "  --r-use-tab           Indent using tab chars instead of spaces.\n"
    "    | -rut                (NOTE: not used in json trace output)\n"
    "                          (NOTE: overrides --r-tab-size/-rts)\n"
  //  "  --output <file-path>  Specify a file you wish to output to\n"
  //  "    | -o <file-path>      instead of to stdout.\n"
    "\n"
    << std::endl;
    // clang-format on
}

std::string validate_dir_path(const std::string val) {
  auto start = val.begin();
  auto end = --(val.end());
  while (start != val.end() && isspace(*start))
    ++start;
  while (end != start && isspace(*end))
    --end;
  if (start == end) {
    std::cerr << "invalid argument : ``" << val << "`` is not a valid file/dir path !!\n" << std::flush;
    exit(EXIT_FAILURE);
  }
  if (*end != '/' && *end != '\\')
    return std::string(start, end) + '/';
  return std::string(start, end);
}

void list_starts() {
  std::cout << "\nStartState List (w/ id's)\n";
  for (size_t i=0; i<_ROMP_STARTSTATES_LEN; ++i)
    std::cout << "  (" << i << ") " << ::__caller__::STARTSTATES[i] << "\n";
  std::cout << std::flush;
}


void Options::parse_args(int argc, char **argv) {
  Options default_opts;
  bool threads_provided = false;
  bool walks_provided = false;
  bool start_provided = false;
  bool guard_provided = false;

  for (int i = 0; i < argc; ++i) {

    if ("-h" == std::string(argv[i]) || "--help" == std::string(argv[i])) { // to print help message and ( result of comparison
                                                  // against a string literal is unspecified)
      print_help();
      exit(EXIT_SUCCESS);
    } else if ("-l" == std::string(argv[i]) || "-y" == std::string(argv[i])) {
      skip_launch_prompt = true;
    } else if ("-es" == std::string(argv[i]) || "--even-start" == std::string(argv[i])) {
      do_even_start = true;
    } else if ("-ls" == std::string(argv[i]) || "--list-starts" == std::string(argv[i])) {
      list_starts();
      exit(EXIT_SUCCESS);
    }
     else if ("-sid" == std::string(argv[i]) || "--start-id" == std::string(argv[i])) {
      start_provided = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        ++i;
        try {
          start_id = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided start-id was not a number (NaN) !! (for -sid/--start-id flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided start-id was out of range (for --sid/--start-id flag) must be "
                       "between 0 and " << _ROMP_STARTSTATES_LEN-1 << " to be a valid start-id!\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "invalid argument : -sid/--start-id requires you to provide a value immediately after (positive integer),\n"
                     "                      else exclude it to use default value: "
                  <<start_id<< std::endl;
        exit(EXIT_FAILURE);
      }
      if (start_id >= _ROMP_STARTSTATES_LEN) {
        std::cerr << "invalid argument : provided start-id was out of range (for --sid/--start-id flag) must be "
                      "between 0 and " << _ROMP_STARTSTATES_LEN-1 << " to be a valid start-id!\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
    }
     else if ("-d" == std::string(argv[i]) || "--depth" == std::string(argv[i])) {
      if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
        ++i;
        try {
          depth = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided walk/search depth was not a number (NaN) !! (for -d/--depth flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided walk/search depth was out of range (for -d/--depth flag) must be "
                       "unsigned int (aka must be positive)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "invalid argument : -d/--depth requires you to provide a value immediately after (positive integer),\n"
                     "                      else exclude it to use default value: "
                  << ((depth == INT32_MAX) ? "INT32_MAX" : std::to_string(depth)) << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if ("-ptn" == std::string(argv[i]) || "--threads" == std::string(argv[i])) {
      threads_provided = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        ++i;
        try {
          threads = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided walk/search threads was not a number (NaN) !! (for -ptn/--threads flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided walk/search threads was out of range (for -ptn/--threads flag) must be "
                       "unsigned int (aka must be positive)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr
            << "invalid argument : -ptn/--threads requires you to provide a value immediately after (positive integer),\n"
               "                      else exclude it to use default value: "
            << threads << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if ("-sw" == std::string(argv[i]) || "--single-walk" == std::string(argv[i])) {
      do_single = true;
    } else if ("-w" == std::string(argv[i]) || "--walks" == std::string(argv[i]) || "--walk-count" == std::string(argv[i])) {
      walks_provided = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
        ++i;
        try {
          walks = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided number of random walkers was not a number (NaN) !! (for "
                       "-w/--walk-count flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided number of random walkers was out of range "
                       "(for -w/--walks/--walk-count flag) must "
                       "be unsigned int (aka must be positive)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "invalid argument : -w/--walks requires you to provide a value immediately after (positive integer),\n"
                     "                      else exclude it to use default value (default: "
                  << _ROMP_THREAD_TO_RW_RATIO << " x #-of-threads)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
    } else if ("-s" == std::string(argv[i]) || "--seed" == std::string(argv[i])) {
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        seed_str = argv[i + 1];
        try {
          rand_seed = std::stoul(argv[i + 1], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::hash<std::string> str_hash;
          rand_seed = str_hash(argv[i + 1]);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided seed was out of range (for -s/--seed flag) must be unsigned int\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else { // rand_seed = std::time(NULL); // no need
        std::cerr << "invalid argument : -s/--seed requires you to provide a seed after the flag\n"
                     "                   else exclude it to use default value: (current_system_time)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
    } else if ("-nd" == std::string(argv[i]) || "--no-deadlock" == std::string(argv[i])) {
      deadlock = false;
#ifdef __romp__ENABLE_liveness_property
    } else if ("-lc" == std::string(argv[i]) || "--liveness-check" == std::string(argv[i])) {
      liveness = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
        ++i;
        try {
          lcount = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided liveness check limit was not a number (NaN) !! (for -lc/--liveness-check "
                       "flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided liveness check limit was out of range (for -lc/--liveness-check flag) "
                       "must be unsigned "
                       "int (aka must be positive)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      }
#endif
#ifdef __romp__ENABLE_cover_property
    } else if ("-cc" == std::string(argv[i]) || "--complete-on-cover" == std::string(argv[i]) || "--cover-check" == std::string(argv[i])) {
      complete_on_cover = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
        ++i;
        try {
          cover_count = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided cover property coverage goal was not a number (NaN) !!\n"
                       "                   |-> (for -cc/--cover-check/--complete-on-cover flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided cover property coverage goal was out of range must be unsigned int (aka "
                       "must be positive & less than 2.147 billion)\n"
                       "                 |-> (for -cc/--cover-check/--complete-on-cover flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      }
    } else if ("-rc" == std::string(argv[i]) || "--r-cover" == std::string(argv[i]) || "--report-cover" == std::string(argv[i])) {
      r_cover = true;
#endif
    } else if ("-ag" == std::string(argv[i]) || "-ll" == std::string(argv[i]) || "-al" == std::string(argv[i])
                || "--attempt-guard" == std::string(argv[i]) || "--loop-limit" == std::string(argv[i]) || "--attempt-limit" == std::string(argv[i])) {
      // do_attempt_guard = true;  // just check to make sure this value is not 0
      guard_provided = true;
      attempt_limit = _ROMP_RULE_COUNT * 2;
      if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
        ++i;
        try {
          attempt_limit = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided attempt limit was not a number (NaN) !!\n"
                       "                   |-> (for -al/--attempt-limit or -ag/--attempt-guard or -ll/--loop-limit flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided attempt limit was out of range must be unsigned int (aka "
                       "must be positive & less than 2.147 billion)\n"
                       "                   |-> (for -al/--attempt-limit or -ag/--attempt-guard or -ll/--loop-limit flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        attempt_limit = _ROMP_RULE_COUNT;
        std::cerr << "\nWARNING : no attempt limit was provided, but it was enabled.\n"
                     "        |-> default value will be used (default: " << _ROMP_RULE_COUNT << " (# of rules post ruleset expansion))\n"
                  << std::flush;
      }
    // } else if ("-rhl" == std::string(argv[i]) || "--r-history" == std::string(argv[i])) {
    //   // result_history = true;
    //   if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
    //     ++i;
    //     try {
    //       history_length = std::stoul(argv[i], nullptr, 0);
    //     } catch (std::invalid_argument &ia) {
    //       std::cerr << "invalid argument : provided history length count was not a number (NaN) !! (for "
    //                    "-rhl/--r-history flag)\n"
    //                 << std::flush;
    //       exit(EXIT_FAILURE);
    //     } catch (std::out_of_range &oor) {
    //       std::cerr << "invalid argument : provided history length count was out of range (for -rhl/--r-history flag) must "
    //                    "be unsigned int (aka must be positive)\n"
    //                 << std::flush;
    //       exit(EXIT_FAILURE);
    //     }
    //   }
    } else if ("-e" == std::string(argv[i]) || "-re" == std::string(argv[i]) || "--report-error" == std::string(argv[i])) {
      report_error = true;
    } else if ("-a" == std::string(argv[i]) || "--all" == std::string(argv[i]) || "--report-all" == std::string(argv[i]) || "-all" == std::string(argv[i])) {
      report_error = true;
      report_all = true;
#ifdef __romp__ENABLE_assume_property
      r_assume = true;
#else
      r_assume = false;
#endif
#ifdef __romp__ENABLE_cover_property
      r_cover = true;
#else
      r_cover = false;
#endif
    } else if ("-rst" == std::string(argv[i]) || "--show-type" == std::string(argv[i]) || "--r-show-type" == std::string(argv[i])) {
      report_show_type = true;
    } else if ("-ros" == std::string(argv[i]) || "--omit-state" == std::string(argv[i]) || "--r-omit-state" == std::string(argv[i])) {
      report_emit_state = false;
    } else if ("-rtc" == std::string(argv[i]) || "--tab-char" == std::string(argv[i]) || "--r-tab-char" == std::string(argv[i])) {
      tab_char = '\t';
    } else if ("-rts" == std::string(argv[i]) || "--tab-size" == std::string(argv[i]) || "--r-tab-size-" == std::string(argv[i])) {
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        ++i;
        try {
          tab_size = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided tab size was not a number (NaN) !!\n"
                       "                   |-> (for --r-tab-size/--tab-size/-rts flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided tab size was out of range must be unsigned int (aka "
                       "must be positive & less than 2.147 billion)\n"
                       "                   |-> (for --r-tab-size/--tab-size/-rts flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "invalid argument : --r-tab-size/--tab-size/-rts requires an unsigned int to follow as a parameter !!\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
#ifdef __romp__ENABLE_assume_property
    } else if ("-ra" == std::string(argv[i]) || "--r-assume" == std::string(argv[i]) || "--report-assume" == std::string(argv[i])) {
      r_assume = true;
#endif
    // } else if ("-o" == std::string(argv[i]) || "--output" == std::string(argv[i])) {
    //   output_results = true;
    //   if (i + 1 < argc && argv[i + 1][0] != '-')
    //     result_out_file = std::string(argv[++i]);
    //   else
    //     std::cerr << "\nWARNING : you have not specified an outfile after using the -o/--output flag !!\n"
    //                  "        |-> `${CWD}/results.txt` will be used by default !!\n"
    //               << std::flush;
    } else if ("-t" == std::string(argv[i]) || "--trace" == std::string(argv[i])) {
      do_trace = true;
      if (i + 1 < argc && argv[i + 1][0] != '-')
        trace_dir = validate_dir_path(std::string(argv[++i]));
      else
        std::cerr << "\nWARNING : you have not specified an out directory after using the -t/--trace flag !!\n"
                     "        |-> `./traces/` will be used by default !!\n"
                  << std::flush;
      std::cerr << "\nWARNING : enabling traces can significantly reduce performance "
                   "& can take up a large amount of system recourses !!\n"
                << std::flush;
    } else if ("-bfs" == std::string(argv[i]) || "--bfs" == std::string(argv[i])
               || "-BFS" == std::string(argv[i]) || "--BFS" == std::string(argv[i])) {
      do_bfs = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        ++i;
        if ('m' == argv[i][0] || 'M' == argv[i][0]) {
          bfs_single = false;
          if (i + 1 < argc && '-' != argv[i + 1][0]) ++i;
        } else if ('s' == argv[i][0] || 'S' == argv[i][0]) {
          bfs_single == true;
          if (i + 1 < argc && '-' != argv[i + 1][0]) ++i;
        }
        try {
          bfs_coefficient = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided initial BFS Coefficient was not a number (NaN) !!\n"
                       "                   |-> (for --bfs/-bfs {single|multiple} {int} flag)\n"
                       "                                                         ^^^^^\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided initial BFS Coefficient was out of range must be unsigned int (aka "
                       "must be positive & less than 2.147 billion)\n"
                       "                   |-> (for --bfs/-bfs {single|multiple} {int} flag)\n"
                       "                                                         ^^^^^\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      }
    } else if ("-bfsl" == std::string(argv[i]) || "--bfs-limit" == std::string(argv[i])
               || "-bfs-l" == std::string(argv[i]) || "--bfsl" == std::string(argv[i])
               || "-bfs-limit" == std::string(argv[i]) || "--bfs-l" == std::string(argv[i])) {
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        ++i;
        try {
          bfs_limit = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided initial BFS Limit was not a number (NaN) !!\n"
                       "                   |-> (for " << argv[i-1] << " flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided initial BFS Limit was out of range must be unsigned int (aka "
                       "must be positive & less than 2.147 billion)\n"
                       "                   |-> (for `" << argv[i-1] << "` flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "invalid argument : `" << argv[i] << "` requires an unsigned int to follow as a parameter !!\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
    }
  } // end for loop
    // modifying values to match complex default values
    if (tab_char == '\t') {
      tab_size = 1;
    }
    if (do_single) {
      threads = 1;
      walks = 1;
      if (do_bfs) {
        do_bfs = false;
        std::cerr << "\nWARNING : Single walk (`--single-walk`/`-sw`) is not compatible and overrides initial BFS (`--bfs`)\n" << std::flush;
      }
    } else if (do_bfs) {
      if (bfs_limit == 0) {
        std::cerr << "\nERROR : The BFS Limit must be greater than 0 to be of any effect (usually a really big number) !!\n" << std::flush;
        exit(EXIT_FAILURE);
      }
    }

    // check for inconsistent or contradictory options here
    //[X]TODO (OPTIONAL) check OPTIONS to make sure config is valid and output
    // if (history_length == 0) {
    //   std::cerr << "\nERROR : history size cannot be 0 (--r-history/-rhl)\n" << std::flush;
    //   exit(EXIT_FAILURE);
    // }
    if (attempt_limit == 0) {
      std::cerr << "\nERROR : attempt limit cannot be 0 (--attempt-limit/-al/--loop-limit/-ll/--attempt-guard/-ag)\n" << std::flush;
      exit(EXIT_FAILURE);
    }
    if (depth == 0) {
      std::cerr << "\nERROR : max depth cannot be 0 (--depth/-d)\n" << std::flush;
      exit(EXIT_FAILURE);
    }
#ifdef __romp__ENABLE_cover_property
    if (complete_on_cover && cover_count == 0) {
      std::cerr << "\nERROR : cover check goal cannot be 0 (--cover-check/-cc)\n" << std::flush;
      exit(EXIT_FAILURE);
    }
#endif
#ifdef __romp__ENABLE_liveness_property
    if (liveness && lcount == 0) {
      std::cerr << "\nERROR : liveness limit cannot be 0 (--liveness-check/-lc)\n" << std::flush;
      exit(EXIT_FAILURE);
    }
#endif
    if (do_single) {
      if (walks_provided)
        std::cerr << "\nWARNING : -w/--walks/--walk_count is ignored when the -sw/--single-walk flag is set !!\n"
                  << std::flush;
      if (threads_provided)
        std::cerr << "\nWARNING : -ptn/--threads is ignored when the -sw/--single-walk flag(s) is set !!\n" << std::flush;
    } else { // not doing a single walk
      if (not threads_provided && threads == 0) {
        std::cerr << "\nERROR : could not determine hardware thread capacity & no --threads/-ptn option was provided !!\n"
                    "         try again using the --threads/-ptn flag to set the number of threads you want to use.\n"
                    <<std::flush;
        exit(EXIT_FAILURE);
      }
      if (threads == 0) {
        std::cerr << "\nERROR : number of threads cannot be 0 (--threads/-ptn)\n" << std::flush;
        exit(EXIT_FAILURE);
      }
      if (walks == 0) {
        std::cerr << "\nERROR : number of walks cannot be 0 (--walks/-w)\n" << std::flush;
        exit(EXIT_FAILURE);
      }
      if (not threads_provided)
        std::cerr << "\nINFO : the number of threads to use was not specified (with -ptn/--threads flags)\n"
                     "     |-> defaults to "
                  << threads << std::endl;
      if (not walks_provided)
        std::cerr << "\nINFO : the number of random walkers was not specified (with -w/--walks/--walk-count flags)\n"
                     "     |-> defaults to "
                  << _ROMP_THREAD_TO_RW_RATIO * threads << "(= " << _ROMP_THREAD_TO_RW_RATIO << " * "
                  << threads << ")\n"
                  << std::flush;
      if (threads_provided && not walks_provided)
        walks = _ROMP_THREAD_TO_RW_RATIO * threads;  // post parse assign default value
      if (threads_provided && walks_provided && threads > walks) {
        threads = walks;
        std::cerr << "\nWARNING : you specified more threads than walks !!\n"
                      "        |-> we will only launch `" << walks << "` threads!\n"
                  << std::flush;
      }
    }
    if (start_provided && do_even_start)
      std::cerr << "\nWARNING : --even-start/-es is ignored when --start-id/-sid is provided !!\n"
                  << std::flush;
    // warnings and end with errors as appropriate
    if (deadlock == false) {
      if (guard_provided && report_error)
        std::cerr << "\nWARNING : --no-deadlock/-nd suppresses the output of walks terminated for violating the rule attempt limit !!\n"
                       "        |-> (aka the --attempt-limit/-al/--loop-limit/-ll/--attempt-guard/-ag flags)\n" << std::flush;
#ifdef __romp__ENABLE_liveness_property
      if (liveness) {
        liveness = false;
        lcount = default_opts.lcount;
        std::cerr << "\nWARNING : --no-deadlock/-nd overrides/disables the --liveness-check/-lc flag !!\n" << std::flush;
      }
#endif
    }
// #ifdef __romp__ENABLE_assume_property
//     if (r_assume && not report_error) {
//       std::cerr << "\nINFO : --report-assume/--r-assume/-ra does nothing unless the --report-error/-re flag is set !!\n" << std::flush;
//     }
// #endif
#ifdef __romp__ENABLE_cover_property
    if (r_cover && not complete_on_cover) {
      std::cerr << "\nINFO : --report-cover/--r-cover/-rc does nothing unless the --complete-on-cover/-cc flag is set !!\n" << std::flush;
    }
#endif
}

const stream_void Options::write_config(ostream_p& out) const noexcept {
  Options defaults;
  std::string sep = "";
  std::string startstate_str = ((start_id < _ROMP_STARTSTATES_LEN)
                                ? ({std::stringstream buf; buf << __caller__::STARTSTATES[start_id]; buf.str();})
                                : ((do_even_start)
                                    ? ("even/distributed (" + std::to_string(walks/_ROMP_STARTSTATES_LEN) + " walks per startstate)" )
                                    : "randomly assigned \t(default)"));
  std::string deadlock_str = "";
  if (deadlock) {
#ifdef __romp__ENABLE_liveness_property
    if (liveness) {
      deadlock_str += sep + "liveness property violations";
      sep = ", ";
    }
#endif
    if (attempt_limit != defaults.attempt_limit) deadlock_str += sep + "attempt limit";
  } else deadlock_str = "NO DETECTION (" + std::string((deadlock == defaults.deadlock) ? " \t(default)" : "");
  sep = "";
  std::string report_str = "property violations | error statements reached";
  std::string pw_report_str = "";
  bool _compound = false;
#ifdef __romp__ENABLE_assume_property
  if (r_assume) {
    _compound = true;
    // report_str += " | " "assume property violated";
    pw_report_str += "assume property violated";
    sep = " | ";
  }
#endif
#ifdef __romp__ENABLE_cover_property
  // if (complete_on_cover) report_str += " | " "cover properties completed";
  if (complete_on_cover && r_cover) {
    _compound = true;
    pw_report_str += sep + "cover properties completed";
    sep = " | ";
  }
#endif
  if (report_all) pw_report_str = "ALL WALKS";
  else if (report_error) pw_report_str += sep + "property violations | error statements reached";
  else if (not _compound) pw_report_str = "NONE \t(default)";
  out << out.indentation()
      << "BASE LAUNCH CONFIG:"                                      << out.indent() << out.nl()
      << "    threads: " << threads << ((threads==defaults.threads) ? " \t(default)" : "")<< out.nl()
      << "      walks: " << walks << ((walks==defaults.walks) ? " \t(default)" : "")<< out.nl()
      << "       seed: " << rand_seed << ((rand_seed==defaults.rand_seed) ? " \t(default:time)" : "")  << out.nl()
      << " startstate: " << startstate_str                                          << out.nl()
      << "  max depth: " << depth << ((depth==defaults.depth) ? " \t(default)" : "")  << out.nl()
      << "   deadlock: " << deadlock_str                                            << out.nl()
#ifdef __romp__ENABLE_symmetry
      << "   symmetry: YES, heuristic \t(config when generating with romp)"
#else
      << "   symmetry: NO  \t(config when generating with romp)"
#endif
      << out.dedent()                                                               << out.nl()
      << "INITIAL BFS OPTIONS:"                                     << out.indent() << out.nl();
  if (do_bfs) {
    out<<"   do initial BFS: YES"                                                         << out.nl()
       <<"  concurency mode: " << ((bfs_single) ? "SINGLE threaded \t(default)" : "MULTI-threaded" ) << out.nl()
       <<"  BFS coefficient: " << bfs_coefficient << out.nl()
       <<"        BFS limit: " << bfs_limit << ((bfs_limit==defaults.bfs_limit) ? " \t(default)" : "");
  } else {
    out << "\t>>\tDISABLED \t(default)\t<<";
  }
  out << out.dedent()                                                               << out.nl()
      << "TRACE OPTIONS:"                                           << out.indent() << out.nl();
  if (do_trace) {
    out<<"   do trace: YES"                                                         << out.nl()
       <<"  trace dir: \"" << trace_dir << '"' << ((trace_dir==defaults.trace_dir) ? " \t(default)" : "");
  } else {
    out << "\t>>\tDISABLED \t(default)\t<<";
  }
  out << out.dedent()                                                               << out.nl();
#if defined(__romp__ENABLE_assume_property) || defined(__romp__ENABLE_cover_property) || defined(__romp__ENABLE_liveness_property)
  out << "ENABLED SPECIAL/RUMUR PROPERTIES:"                        << out.indent()
#ifdef __romp__ENABLE_assume_property
                                                                                    << out.nl()
      << "      assume: YES, " << (r_assume ? "reporting" : "non-reporting \t(default)")
#endif
#ifdef __romp__ENABLE_cover_property
                                                                                    << out.nl()
      << "       cover: " << ((complete_on_cover)
                              ? "YES, " + std::string((r_cover) ? "reporting" : "non-reporting")
                              : "NO \t(default)" )                                    << out.nl()
      << " cover-count: " << ((complete_on_cover)
                              ? std::to_string(cover_count)
                              : "n/a")
#endif
#ifdef __romp__ENABLE_liveness_property
                                                                                    << out.nl()
      << "    liveness: " << ((liveness) ? "YES" : "NO \t(default)")                << out.nl()
      << "liveness lim: " << ((liveness)
                              ? std::to_string(lcount)
                              : "n/a")
#endif
      << out.dedent()                                                               << out.nl();
#endif
  out << "PER WALK REPORTS:"                                        << out.indent() << out.nl()
      << "     report: " << pw_report_str                                           << out.nl()
      << "history len: " << _ROMP_HIST_LEN << " \t(config when generating with romp)"<< out.nl()
      << "print state: " << ((report_emit_state)
                             ? ("YES"
                                + std::string((report_show_type)
                                                ? ", w/ type info"
                                                : "")
                                + std::string((report_emit_state==defaults.report_emit_state
                                                && report_show_type==defaults.report_show_type)
                                              ? " \t(default)"
                                              : ""))
                             : ("NO"
                                + std::string((report_emit_state==defaults.report_emit_state)
                                              ? " \t(default)"
                                              : "")))                               << out.nl()
#ifdef __ROMP__DO_MEASURE
      << "report time: YES \t(config when generating with romp)"
#else
      << "report time: NO  \t(config when generating with romp)"
#endif
      << out.dedent()                                                               << out.nl()
      << "WALKS INCLUDED IN FINAL REPORT:" << ((report_all) ? " \t[ALL]" : "")
                                                    << out.indent() << out.indent() << out.nl()
      << " - property violations      \t(default)"                                  << out.nl()
      << " - error statements reached \t(default)"                                  << out.nl();
  if (r_assume) out << " - assumptions violation"                                   << out.nl();
  if (r_cover) out << " - walks with completed cover property coverage"             << out.nl();
  if (report_all) {
    out << " - max depth reached"                                                   << out.nl()
        << " - attempt limit reached"
            << ((attempt_limit == defaults.attempt_limit)
                ? (" \t(`built-in`"
                    + std::string((deadlock)
                                  ? ")"
                                  : "; ignores -nd/--no-deadlock)"))
                : ((deadlock)
                    ? ""
                    : " \t(ignores -nd/--no-deadlock; DBG:``shouldn't be possible'')"))
                                                                                    << out.nl();
  }
  out << out.dedent() << out.dedent()                                               << out.nl();
  return S_VOID;
}

template<class O>
ojstream<O>& operator << (ojstream<O>& json, const Options& opts) noexcept {
  json << "{"
            "\"model\":\"" __model__filepath "\","
            "\"romp-id\":" << ROMP_ID << ","
            "\"root-seed\":\"" << opts.seed_str << "\","
            "\"walks\":" << opts.walks << ","
            "\"threads\":" << opts.threads << ","
            "\"do-single\":" << opts.do_single << ","
            "\"initial-bfs\":" << opts.do_bfs << ","
            "\"bfs-mode\":" << ((opts.do_bfs) ? ((opts.bfs_single) ? "\"single\"" : "\"multi\"") : "null") << ","
            "\"bfs-coef\":" << ((opts.do_bfs) ? std::to_string(opts.bfs_coefficient) : "null") << ","
            "\"bfs-limit\":" << ((opts.do_bfs) ? std::to_string(opts.bfs_limit) : "null") << ","
            "\"max-depth\":" << opts.depth << ","
            "\"abs-attempt-limit\":" << std::to_string(_ROMP_ATTEMPT_LIMIT_DEFAULT) << ","
            "\"attempt-limit\":" << ((opts.attempt_limit != _ROMP_ATTEMPT_LIMIT_DEFAULT
                                        && opts.deadlock)
                                      ? std::to_string(opts.attempt_limit)
                                      : "null") << ","
            "\"start-mode\":" << ((opts.start_id != _ROMP_START_ID_DEFAULT)
                                  ? ("\"single\"")
                                  : (((opts.do_even_start)
                                                  ? ("\"even\"")
                                                  : ("\"random\"")))) << ","
            "\"single-start-id\":" << ((opts.start_id != _ROMP_START_ID_DEFAULT)
                                        ? std::to_string(opts.start_id)
                                        : "null") << ","
#ifdef __romp__ENABLE_symmetry
            "\"symmetry-reduction\":true,"
#else
            "\"symmetry-reduction\":false,"
#endif
#ifdef __romp__ENABLE_assume_property
            "\"enable-assume\":true,"
#else
            "\"enable-assume\":false,"
#endif
#ifdef __romp__ENABLE_cover_property
            "\"enable-cover\":" << opts.complete_on_cover << ","
            "\"cover-count\":" << ((opts.complete_on_cover)
                                    ? std::to_string(opts.cover_count)
                                    : "null") << ","
#else
            "\"enable-cover\":false,"
            "\"cover-count\":null,"
#endif
#ifdef __romp__ENABLE_liveness_property
            "\"enable-liveness\":" << opts.liveness << ","
            "\"liveness-limit\":" << ((opts.liveness)
                                      ? std::to_string(opts.lcount)
                                      : "null") << ","
#else
            "\"enable-liveness\":false,"
            "\"liveness-limit\":null,"
#endif
#ifdef __ROMP__DO_MEASURE
            "\"do-measure\":true,"
#else
            "\"do-measure\":false,"
#endif
#ifdef __ROMP__SIMPLE_TRACE
            "\"simple-trace\":true,"
#else
            "\"simple-trace\":false,"
#endif
            "\"total-rule-count\":" << std::to_string(_ROMP_RULE_COUNT) << ","
            "\"possible-state-count\":" _ROMP_STATESPACE_COUNT_str ""
       << "}";
  return json;
}

inline std::ostream& operator << (std::ostream& out, const Options& opts) {
  ostream_p _out(out,opts,0); opts.write_config(_out); return out;
}
ostream_p& operator << (ostream_p& out, const Options& opts) noexcept { opts.write_config(out); return out; }


  RandWalker::RandWalker(const BFSWalker& bfs, RandSeed_t rand_seed_, const Options& OPTIONS_)
    : // RandWalker(OPTIONS_),
      rand_seed(rand_seed_), init_rand_seed(rand_seed_),
      _fuel(OPTIONS_.depth-bfs._depth),
      state(bfs.state), start_id(bfs._start_id), status(bfs.status), IS_BFS(true),
      history_start(bfs.history_start), history_level(bfs.history_level),
      put_msgs(bfs.put_msgs),
      id(RandWalker::next_id++),
      OPTIONS(OPTIONS_),
      sim1Step(((OPTIONS.do_trace)
                  ? std::function<void()>([this](){sim1Step_trace();})
                  : std::function<void()>([this](){sim1Step_no_trace();}))),
#     ifdef __romp__ENABLE_cover_property
        enable_cover(OPTIONS_.complete_on_cover), goal_cover_count(OPTIONS_.cover_count),
#     endif
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        enable_liveness(OPTIONS_.liveness), init_lcount(OPTIONS.lcount),
#     endif
      _attempt_limit(OPTIONS_.attempt_limit), init_attempt_limit(OPTIONS_.attempt_limit)
  {
#   ifdef __romp__ENABLE_symmetry
      for (int i=0; i<_ROMP_RULESETS_LEN; ++i) next_rule[i] = 0;
    #endif
#   ifdef __romp__ENABLE_cover_property
      for (int i=0; i<_ROMP_COVER_PROP_COUNT; ++i) cover_counts[i] = 0;
#   endif
#   if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
      for (int i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i) lcounts[i] = init_lcount;
#   endif
    state.__rw__ = this;
    if (OPTIONS.do_trace) {
      init_trace();
      bfs_trace(bfs);
    }
    // transfer history from bfs
    for (size_t i=bfs.history_start; i<bfs.history_level; ++i)
      history[i%history_size()] = bfs.history[i%bfs.history_size()];
    //NOTE: this is lazy and overwrites previous data while transferring data
    //     since the history buffer on a BFS Walker is always larger than a random walker
  }

  void RandWalker::bfs_trace(const BFSWalker& bfs) {
    *json << "{\"$type\":\"bfs-init\","
             "\"startstate\":" << ::__caller__::STARTSTATES[start_id] << ","
             "\"depth\":" << bfs._depth << ","
             "\"history\":[";
    std::string sep;
    for (size_t i=bfs.history_start; i<bfs.history_level; ++i) {
      *json << sep << *bfs.history[i%bfs.history_size()].rule;
    }
    *json << "],"
            "\"state\":" << bfs.state << '}';
  }


} // namespace romp

#pragma endregion romp_postfix


#pragma region romp_main

/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw-main.hpp
 *
 * @brief
 *
 * @date 2022/07/12
 * @version 0.2
 */


#ifndef __romp__GENERATED_CODE
#include "walker.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "bfs.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "options.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#endif

// #include <unistd.h>
namespace romp {
  void init_trace_dir(const Options& OPTIONS) {
    std::string args = "mkdir -p \"" + OPTIONS.get_trace_dir() + "\"";
    int err = system(args.c_str());
    if (err) {
      std::cerr << "\nERROR :: trace directory ``" << OPTIONS.get_trace_dir() << "`` does not exists and could not be created !!\n\n"
                << std::flush;
      exit(EXIT_FAILURE);
    }
  }

  void launch_prompt(const Options& OPTIONS) {
    ostream_p out(std::cout,OPTIONS,0);
    std::cout << '\n';
    OPTIONS.write_config(out);
    std::cout.flush();
    for (;;) {
      std::cout << "Correct Config? [yes=launch/no=exit]: " << std::flush;
      std::string _val; char val;
      std::cin >> _val;
      if (_val.size()>0) val = std::tolower(_val[0]);
      switch (val) {
        case 'y':
        case 'l':
          return;
        case 'n':
        case 'e':
          exit(EXIT_SUCCESS); break;
        default:
          break;
      }
      std::cout << "COULDN'T RECOGNISE RESPONSE; TRY AGAIN\n";
    }
  }
}

int main(int argc, char **argv) {
  ::romp::Options OPTIONS;
  OPTIONS.parse_args(argc, argv);

  if (not (OPTIONS.skip_launch_prompt))
    ::romp::launch_prompt(OPTIONS);

  if (OPTIONS.do_trace)
    ::romp::init_trace_dir(OPTIONS);

  if (OPTIONS.do_bfs)
    ::romp::BFSHandler(OPTIONS).launch();
  else if (OPTIONS.do_single)
    ::romp::launch_single(OPTIONS);

  else
    ::romp::launch_threads(OPTIONS);
    // ::romp::launch_OpenMP(::romp::OPTIONS.rand_seed);


  return EXIT_SUCCESS;
}

//TODO add in signal intercept for kill/Ctrl-C to gracefully kill threads & output traces etc.

#pragma endregion romp_main

/* << === EOF === >> */