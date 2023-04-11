/*
	Generated code for a romp "parallel random walker" verification tool based off of the Murphi Model described in:
		Original Murphi Model: xiaofang_protocol.m
	Please build with the following command(s):
		<not-implemented-yet>
*/


#define __romp__GENERATED_CODE


#define _ROMP_STATE_TYPE ::__model__::__romp__Model__


#define _ROMP_HIST_LEN (4ul)


#define _ROMP_THREAD_TO_RW_RATIO (16ul)


#define _ROMP_BFS_COEF (16ul)


#define __model__filepath "/home/ajantha/Desktop/Repos/romp/tests/xiaofang_protocol.m"


#define __model__filepath_contains_space (false)


#define __model__filename "xiaofang_protocol.m"

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
    /* NODE: scalarset(NODE_NUM) */
      _romp_NODE_2_1,
      _romp_NODE_2_2,
    /* Datas: scalarset(DataCnt) */
      _romp_Datas_2_1,
      _romp_Datas_2_2,
    /* enum { L2 } */
      L2,
    /* enum { Home } */
      Home,
    /* Rmt: scalarset(RmtCnt) */
      _romp_Rmt_2_1,
      _romp_Rmt_2_2,
    /* enum { Inval, WRD, WRDO, WRDX, WINV, RRD } */
      Inval,
      WRD,
      WRDO,
      WRDX,
      WINV,
      RRD,
    /* enum { CACHE_I, CACHE_S, CACHE_E, CACHE_M } */
      CACHE_I,
      CACHE_S,
      CACHE_E,
      CACHE_M,
    /* enum { Invld, Shrd, Excl } */
      Invld,
      Shrd,
      Excl,
    /* enum { NODE_None, NODE_Get, NODE_GetX } */
      NODE_None,
      NODE_Get,
      NODE_GetX,
    /* enum { UNI_None, UNI_Get, UNI_GetX, UNI_Put, UNI_PutX, UNI_Nak, UNI_PutXX, WB_WbAck } */
      UNI_None,
      UNI_Get,
      UNI_GetX,
      UNI_Put,
      UNI_PutX,
      UNI_Nak,
      UNI_PutXX,
      WB_WbAck,
    /* enum { INV_None, INV_Inv, INV_InvAck } */
      INV_None,
      INV_Inv,
      INV_InvAck,
    /* enum { WB_None, WB_Wb } */
      WB_None,
      WB_Wb,
    /* enum { SHWB_None, SHWB_ShWb, SHWB_FAck } */
      SHWB_None,
      SHWB_ShWb,
      SHWB_FAck,
    /* enum { NAKC_None, NAKC_Nakc, NAKC_SD } */
      NAKC_None,
      NAKC_Nakc,
      NAKC_SD,
    /* enum { GUNI_None, RD_H, RD_RAC, RDX_H, RDX_RAC, ACK, NAK, NAK_Home, IACK, IACKX, WB_Ack } */
      GUNI_None,
      RD_H,
      RD_RAC,
      RDX_H,
      RDX_RAC,
      ACK,
      NAK,
      NAK_Home,
      IACK,
      IACKX,
      WB_Ack,
    /* enum { GINV_None, INV, SACK } */
      GINV_None,
      INV,
      SACK,
    /* enum { GWB_None, WB } */
      GWB_None,
      WB,
    /* enum { GSHWB_None, SHWB, DXFER } */
      GSHWB_None,
      SHWB,
      DXFER,
    /* enum { GNAKC_None, GNAKC_Nakc, GNAKC_DIR } */
      GNAKC_None,
      GNAKC_Nakc,
      GNAKC_DIR,
  };

} // namespace __model__
namespace romp { typedef ::__model__::__romp__SCALAR_ENUM_t__ SCALAR_ENUM_t; }
namespace __info__ { std::string SCALAR_IDS[66] = { "<undef>", "NODE_1", "NODE_2", "Datas_1", "Datas_2", "L2", "Home", "Rmt_1", "Rmt_2", "Inval", "WRD", "WRDO", "WRDX", "WINV", "RRD", "CACHE_I", "CACHE_S", "CACHE_E", "CACHE_M", "Invld", "Shrd", "Excl", "NODE_None", "NODE_Get", "NODE_GetX", "UNI_None", "UNI_Get", "UNI_GetX", "UNI_Put", "UNI_PutX", "UNI_Nak", "UNI_PutXX", "WB_WbAck", "INV_None", "INV_Inv", "INV_InvAck", "WB_None", "WB_Wb", "SHWB_None", "SHWB_ShWb", "SHWB_FAck", "NAKC_None", "NAKC_Nakc", "NAKC_SD", "GUNI_None", "RD_H", "RD_RAC", "RDX_H", "RDX_RAC", "ACK", "NAK", "NAK_Home", "IACK", "IACKX", "WB_Ack", "GINV_None", "INV", "SACK", "GWB_None", "WB", "GSHWB_None", "SHWB", "DXFER", "GNAKC_None", "GNAKC_Nakc", "GNAKC_DIR" }; }


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

  //-----------------------------------------------------------------------------
  //----    common part    ------
  const ::romp::range_t DataCnt = ((::romp::range_t)(2));

  //---- outside a cluster ------
  const ::romp::range_t HomeCnt = ((::romp::range_t)(1));

  const ::romp::range_t RmtCnt = ((::romp::range_t)(2));

  const ::romp::range_t ProcCnt = ((HomeCnt) + (RmtCnt));

  //---- inside a cluster  ------
  const ::romp::range_t NODE_NUM = ((::romp::range_t)(2));

  //-----------------------------------------------------------------------------
  //----    common part    ------
  typedef ::romp::TypeIdType<0,::romp::RangeType<(/*(0)*/(0)),(/*(ProcCnt)*/(3))>> ClusterCnt;

  typedef ::romp::TypeIdType<1,::romp::ScalarsetType<1,(/*NODE_NUM*/(2))>> NODE;

  typedef ::romp::TypeIdType<2,::romp::ScalarsetType<3,(/*DataCnt*/(2))>> Datas;

  typedef ::romp::TypeIdType<3,::romp::EnumType<(/*L2*/5),(1)>> L2Name;

  typedef ::romp::TypeIdType<4,::romp::ScalarsetUnionType<NODE,L2Name>> NODE_L2;

  typedef ::romp::TypeIdType<5,::romp::EnumType<(/*Home*/6),(1)>> Homes;

  typedef ::romp::TypeIdType<6,::romp::ScalarsetType<7,(/*RmtCnt*/(2))>> Rmt;

  typedef ::romp::TypeIdType<7,::romp::ScalarsetUnionType<Homes,Rmt>> Procss;

  typedef ::romp::TypeIdType<8,::romp::RangeType<(/*(0)*/(0)),(/*(NODE_NUM)*/(2))>> CacheCnt;

  typedef ::romp::TypeIdType<9,::romp::EnumType<(/*Inval*/9),(6)>> RACState;

  // Invalid
  // basic operation -- waiting for a read reply
  // basic operation -- waiting for a read reply
  // with ownership transfer
  // basic operation -- waiting for a read exclusive reply
  // basic operation -- waiting for invalidate acknowledges
  // basic operation -- invalidated read/read
  typedef ::romp::TypeIdType<10,::romp::EnumType<(/*CACHE_I*/15),(4)>> CACHE_STATE;

  typedef ::romp::TypeIdType<11,::romp::EnumType<(/*Invld*/19),(3)>> L2State;

  typedef ::romp::TypeIdType<12,::romp::EnumType<(/*NODE_None*/22),(3)>> NODE_CMD;

  typedef ::romp::TypeIdType<13,::romp::RecordType<0,/*ProcCmd*/NODE_CMD,/*InvMarked*/boolean,/*CacheState*/CACHE_STATE,/*CacheData*/Datas,/*block_WB*/boolean>> NODE_STATE;

  // uni msg channel
  typedef ::romp::TypeIdType<14,::romp::EnumType<(/*UNI_None*/25),(8)>> UNI_CMD;

  typedef ::romp::TypeIdType<15,::romp::RecordType<5,/*Cmd*/UNI_CMD,/*Proc*/NODE_L2,/*Data*/Datas>> UNI_MSG;

  // invalidation msg channel
  typedef ::romp::TypeIdType<16,::romp::EnumType<(/*INV_None*/33),(3)>> INV_CMD;

  typedef ::romp::TypeIdType<17,::romp::RecordType<8,/*Cmd*/INV_CMD>> INV_MSG;

  // writeback msg channel
  typedef ::romp::TypeIdType<18,::romp::EnumType<(/*WB_None*/36),(2)>> WB_CMD;

  typedef ::romp::TypeIdType<19,::romp::RecordType<9,/*Cmd*/WB_CMD,/*Proc*/NODE_L2,/*Data*/Datas>> WB_MSG;

  // ShWb msg channel
  typedef ::romp::TypeIdType<20,::romp::EnumType<(/*SHWB_None*/38),(3)>> SHWB_CMD;

  typedef ::romp::TypeIdType<21,::romp::RecordType<12,/*Cmd*/SHWB_CMD,/*Proc*/NODE_L2,/*Data*/Datas,/*Aux*/NODE_L2>> SHWB_MSG;

  // nack-home msg channel
  typedef ::romp::TypeIdType<22,::romp::EnumType<(/*NAKC_None*/41),(3)>> NAKC_CMD;

  typedef ::romp::TypeIdType<23,::romp::RecordType<16,/*Cmd*/NAKC_CMD,/*Proc*/NODE_L2,/*Aux*/NODE_L2>> NAKC_MSG;

  // main structure
  typedef ::romp::TypeIdType<24,::romp::RecordType<35,/*CurrData*/Datas,/*PrevData*/Datas,/*Collecting*/boolean,/*Proc*/::romp::ArrayType<NODE,NODE_STATE>,/*UniMsg*/::romp::ArrayType<NODE_L2,UNI_MSG>,/*InvMsg*/::romp::ArrayType<NODE_L2,INV_MSG>,/*WbMsg*/WB_MSG,/*ShWbMsg*/SHWB_MSG,/*NakcMsg*/NAKC_MSG,/*L2*/::romp::RecordType<19,/*State*/L2State,/*Data*/Datas,/*pending*/boolean,/*Dirty*/boolean,/*ShrSet*/::romp::ArrayType<NODE,boolean>,/*InvCnt*/CacheCnt,/*HeadPtr*/NODE_L2,/*ReqId*/NODE,/*OnlyCopy*/boolean,/*ReqCluster*/Procss,/*ReqType*/boolean,/*Gblock_WB*/boolean,/*isRetired*/boolean,/*ifHoldMsg*/boolean>,/*RAC*/::romp::RecordType<33,/*State*/RACState,/*InvCnt*/ClusterCnt>>> ProcState;

  // these 3 are for invariant purposes
  // structure inside a cluster 
  // local dir
  // requesting L1 whose req is pending 
  // if this cluster has the only copy
  // fwded req cluster
  // fwded req type: true if Get otherwise GetX 
  // Apr 8
  // communicating with outside cluster
  //---- outside a cluster  ------
  typedef ::romp::TypeIdType<25,::romp::RecordType<46,/*isBusy*/boolean,/*Mem*/Datas,/*State*/L2State,/*ShrSet*/::romp::ArrayType<Procss,boolean>,/*InvCnt*/ClusterCnt,/*isLocal*/boolean,/*HeadPtr*/Procss,/*Collecting*/boolean,/*CurrData*/Datas,/*PrevData*/Datas>> DirState;

  // not really used
  // invariant purpose
  typedef ::romp::TypeIdType<26,::romp::EnumType<(/*GUNI_None*/44),(11)>> GUNI_CMD;

  typedef ::romp::TypeIdType<27,::romp::RecordType<56,/*Cmd*/GUNI_CMD,/*Cluster*/Procss,/*InvCnt*/ClusterCnt,/*Data*/Datas>> GUNI_MSG;

  typedef ::romp::TypeIdType<28,::romp::EnumType<(/*GINV_None*/55),(3)>> GINV_CMD;

  typedef ::romp::TypeIdType<29,::romp::RecordType<60,/*Cmd*/GINV_CMD,/*Cluster*/Procss>> GINV_MSG;

  typedef ::romp::TypeIdType<30,::romp::EnumType<(/*GWB_None*/58),(2)>> GWB_CMD;

  typedef ::romp::TypeIdType<31,::romp::RecordType<62,/*Cmd*/GWB_CMD,/*Cluster*/Procss,/*Data*/Datas>> GWB_MSG;

  typedef ::romp::TypeIdType<32,::romp::EnumType<(/*GSHWB_None*/60),(3)>> GSHWB_CMD;

  typedef ::romp::TypeIdType<33,::romp::RecordType<65,/*Cmd*/GSHWB_CMD,/*Cluster*/Procss,/*Data*/Datas>> GSHWB_MSG;

  typedef ::romp::TypeIdType<34,::romp::EnumType<(/*GNAKC_None*/63),(3)>> GNAKC_CMD;

  typedef ::romp::TypeIdType<35,::romp::RecordType<68,/*Cmd*/GNAKC_CMD,/*Cluster*/Procss>> GNAKC_MSG;

  //-----------------------------------------------------------------------------
  ::romp::ArrayType<Procss,GUNI_MSG> GUniMsg;

  ::romp::ArrayType<Procss,GINV_MSG> GInvMsg;

  GWB_MSG GWbMsg;

  GSHWB_MSG GShWbMsg;

  GNAKC_MSG GNakcMsg;

  ::romp::ArrayType<Procss,ProcState> Procs;

  DirState Dir;

  //-----------------------------------------------------------------------------
   void __romp__StartState__Init(const Datas d){
    try {
      for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) {
        // Undefine GUniMsg[p];
        ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{218,14},{218,24}}))).Undefine();
        // Undefine GInvMsg[p];
        ((::romp::Element<Procss,GINV_MSG>((GInvMsg), (p), ::romp::location{{219,14},{219,24}}))).Undefine();
        // GUniMsg[p].Cmd := GUNI_None;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{220,5},{220,15}})).get</*Cmd*/0>()), (GUNI_None), ::romp::location{{220,5},{220,32}});
        // GInvMsg[p].Cmd := GINV_None;
        ::romp::Assignment<GINV_CMD>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (p), ::romp::location{{221,5},{221,15}})).get</*Cmd*/0>()), (GINV_None), ::romp::location{{221,5},{221,32}});
      }

      // GWbMsg.Cmd := GWB_None;
      ::romp::Assignment<GWB_CMD>(((GWbMsg).get</*Cmd*/0>()), (GWB_None), ::romp::location{{223,3},{223,25}});
      // GShWbMsg.Cmd := GSHWB_None;
      ::romp::Assignment<GSHWB_CMD>(((GShWbMsg).get</*Cmd*/0>()), (GSHWB_None), ::romp::location{{224,3},{224,29}});
      // GNakcMsg.Cmd := GNAKC_None;
      ::romp::Assignment<GNAKC_CMD>(((GNakcMsg).get</*Cmd*/0>()), (GNAKC_None), ::romp::location{{225,3},{225,29}});
      for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) {
        // Undefine Procs[p];
        ((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{229,14},{229,22}}))).Undefine();
        // invariant purpose
        // Procs[p].Collecting := false;
        ::romp::Assignment<boolean>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{232,5},{232,13}})).get</*Collecting*/2>()), (false), ::romp::location{{232,5},{232,33}});
        for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) {
          // Procs[p].Proc[n].ProcCmd := NODE_None;
          ::romp::Assignment<NODE_CMD>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{235,7},{235,15}})).get</*Proc*/3>()), (n), ::romp::location{{235,7},{235,23}})).get</*ProcCmd*/0>()), (NODE_None), ::romp::location{{235,7},{235,44}});
          // Procs[p].Proc[n].InvMarked := false;
          ::romp::Assignment<boolean>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{236,7},{236,15}})).get</*Proc*/3>()), (n), ::romp::location{{236,7},{236,23}})).get</*InvMarked*/1>()), (false), ::romp::location{{236,7},{236,42}});
          // Procs[p].Proc[n].CacheState := CACHE_I;
          ::romp::Assignment<CACHE_STATE>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{237,7},{237,15}})).get</*Proc*/3>()), (n), ::romp::location{{237,7},{237,23}})).get</*CacheState*/2>()), (CACHE_I), ::romp::location{{237,7},{237,45}});
          // Procs[p].Proc[n].block_WB := false;
          ::romp::Assignment<boolean>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{238,7},{238,15}})).get</*Proc*/3>()), (n), ::romp::location{{238,7},{238,23}})).get</*block_WB*/4>()), (false), ::romp::location{{238,7},{238,41}});
        }

        // Procs[p].L2.State := Invld;
        ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{241,5},{241,13}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{241,5},{241,31}});
        // Procs[p].L2.pending := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{242,5},{242,13}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{242,5},{242,33}});
        // Procs[p].L2.InvCnt := 0;
        ::romp::Assignment<CacheCnt>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{243,5},{243,13}})).get</*L2*/9>()).get</*InvCnt*/5>()), ((::romp::range_t)(0)), ::romp::location{{243,5},{243,28}});
        for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) {
          // Procs[p].L2.ShrSet[n] := false;
          ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{245,7},{245,15}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{245,7},{245,28}})), (false), ::romp::location{{245,7},{245,37}});
        }

        // Procs[p].L2.isRetired := true;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{247,5},{247,13}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{247,5},{247,34}});
        // Procs[p].L2.InvCnt := 0;
        ::romp::Assignment<CacheCnt>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{249,5},{249,13}})).get</*L2*/9>()).get</*InvCnt*/5>()), ((::romp::range_t)(0)), ::romp::location{{249,5},{249,28}});
        // Procs[p].L2.Dirty := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{250,5},{250,13}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{250,5},{250,31}});
        // Procs[p].L2.OnlyCopy := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{251,5},{251,13}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{251,5},{251,34}});
        // Procs[p].L2.Gblock_WB := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{252,5},{252,13}})).get</*L2*/9>()).get</*Gblock_WB*/11>()), (false), ::romp::location{{252,5},{252,35}});
        // Procs[p].RAC.State := Inval;
        ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{253,5},{253,13}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{253,5},{253,32}});
        // Procs[p].RAC.InvCnt := 0;
        ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{254,5},{254,13}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((::romp::range_t)(0)), ::romp::location{{254,5},{254,29}});
        // Apr 8
        // Procs[p].L2.ifHoldMsg := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{257,5},{257,13}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()), (false), ::romp::location{{257,5},{257,35}});
        for (auto n=NODE_L2::__LB(); n!=NODE_L2::__UB(); n.__step()) {
          // Procs[p].UniMsg[n].Cmd := UNI_None;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{260,7},{260,15}})).get</*UniMsg*/4>()), (n), ::romp::location{{260,7},{260,25}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{260,7},{260,41}});
          // Procs[p].InvMsg[n].Cmd := INV_None;
          ::romp::Assignment<INV_CMD>(((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{261,7},{261,15}})).get</*InvMsg*/5>()), (n), ::romp::location{{261,7},{261,25}})).get</*Cmd*/0>()), (INV_None), ::romp::location{{261,7},{261,41}});
        }

        // Procs[p].WbMsg.Cmd := WB_None;
        ::romp::Assignment<WB_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{263,5},{263,13}})).get</*WbMsg*/6>()).get</*Cmd*/0>()), (WB_None), ::romp::location{{263,5},{263,34}});
        // Procs[p].ShWbMsg.Cmd := SHWB_None;
        ::romp::Assignment<SHWB_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{264,5},{264,13}})).get</*ShWbMsg*/7>()).get</*Cmd*/0>()), (SHWB_None), ::romp::location{{264,5},{264,38}});
        // Procs[p].NakcMsg.Cmd := NAKC_None;
        ::romp::Assignment<NAKC_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{265,5},{265,13}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()), (NAKC_None), ::romp::location{{265,5},{265,38}});
      }

      // Undefine Dir;
      ((Dir)).Undefine();
      // Dir.isBusy := false;
      ::romp::Assignment<boolean>(((Dir).get</*isBusy*/0>()), (false), ::romp::location{{270,3},{270,22}});
      // Dir.Mem := d;
      ::romp::Assignment<Datas>(((Dir).get</*Mem*/1>()), (d), ::romp::location{{271,3},{271,15}});
      // Dir.State := Invld;
      ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Invld), ::romp::location{{272,3},{272,21}});
      // Dir.isLocal := false;
      ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (false), ::romp::location{{273,3},{273,23}});
      for (auto p=Rmt::__LB(); p!=Rmt::__UB(); p.__step()) {
        // Dir.ShrSet[p] := false;
        ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (p), ::romp::location{{275,5},{275,18}})), (false), ::romp::location{{275,5},{275,27}});
      }

      // invariant purpose
      // Dir.Collecting := false;
      ::romp::Assignment<boolean>(((Dir).get</*Collecting*/7>()), (false), ::romp::location{{279,3},{279,26}});
      // Dir.PrevData := d;
      ::romp::Assignment<Datas>(((Dir).get</*PrevData*/9>()), (d), ::romp::location{{280,3},{280,20}});
      // Dir.CurrData := d;
      ::romp::Assignment<Datas>(((Dir).get</*CurrData*/8>()), (d), ::romp::location{{281,3},{281,20}});
    } catch (...) { throw ::romp::ModelStartStateError(0); }
  }


  //RuleBase
  
  bool __romp__Rule_guard__L1_Update_Data(const Procss p, const NODE src, const Datas data) const {
    try {
      return ((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{291,3},{291,11}})).get</*Proc*/3>()), (src), ::romp::location{{291,3},{291,21}})).get</*CacheState*/2>()) == (CACHE_E)) || (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{292,3},{292,11}})).get</*Proc*/3>()), (src), ::romp::location{{292,3},{292,21}})).get</*CacheState*/2>()) == (CACHE_M)));
    } catch (...) { throw ::romp::ModelRuleError(0,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1_Update_Data(const Procss p, const NODE src, const Datas data) {
    try {
      // Procs[p].Proc[src].CacheState := CACHE_M;
      ::romp::Assignment<CACHE_STATE>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{295,3},{295,11}})).get</*Proc*/3>()), (src), ::romp::location{{295,3},{295,21}})).get</*CacheState*/2>()), (CACHE_M), ::romp::location{{295,3},{295,43}});
      // Procs[p].Proc[src].CacheData := data;
      ::romp::Assignment<Datas>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{296,3},{296,11}})).get</*Proc*/3>()), (src), ::romp::location{{296,3},{296,21}})).get</*CacheData*/3>()), (data), ::romp::location{{296,3},{296,39}});
      // invariant purpose
      // Procs[p].CurrData := data;
      ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{299,3},{299,11}})).get</*CurrData*/0>()), (data), ::romp::location{{299,3},{299,28}});
    } catch (...) { throw ::romp::ModelRuleError(0,::romp::ModelRuleError::ACTION); }
  }

  //RuleBase
  
  bool __romp__Rule_guard__L1_Get(const Procss p, const NODE src) const {
    try {
      return (((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{308,4},{308,12}})).get</*Proc*/3>()), (src), ::romp::location{{308,4},{308,22}})).get</*ProcCmd*/0>()) == (NODE_None)) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{309,4},{309,12}})).get</*Proc*/3>()), (src), ::romp::location{{309,4},{309,22}})).get</*CacheState*/2>()) == (CACHE_I))) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{310,4},{310,12}})).get</*Proc*/3>()), (src), ::romp::location{{310,4},{310,22}})).get</*block_WB*/4>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(1,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1_Get(const Procss p, const NODE src) {
    try {
      // Procs[p].Proc[src].ProcCmd := NODE_Get;
      ::romp::Assignment<NODE_CMD>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{313,3},{313,11}})).get</*Proc*/3>()), (src), ::romp::location{{313,3},{313,21}})).get</*ProcCmd*/0>()), (NODE_Get), ::romp::location{{313,3},{313,41}});
      // Procs[p].UniMsg[src].Cmd := UNI_Get;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{314,3},{314,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{314,3},{314,23}})).get</*Cmd*/0>()), (UNI_Get), ::romp::location{{314,3},{314,38}});
      // Procs[p].UniMsg[src].Proc := L2;
      ::romp::Assignment<NODE_L2>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{315,3},{315,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{315,3},{315,23}})).get</*Proc*/1>()), (L2), ::romp::location{{315,3},{315,34}});
      // Undefine Procs[p].UniMsg[src].Data;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{316,12},{316,20}})).get</*UniMsg*/4>()), (src), ::romp::location{{316,12},{316,32}})).get</*Data*/2>())).Undefine();
    } catch (...) { throw ::romp::ModelRuleError(1,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L2_Recv_Get_Put(const Procss p, const NODE src) const {
    try {
      return (((((((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{325,5},{325,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{325,5},{325,25}})).get</*Cmd*/0>()) == (UNI_Get)) && (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{326,5},{326,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{326,5},{326,25}})).get</*Proc*/1>()) == (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{328,5},{328,13}})).get</*L2*/9>()).get</*pending*/2>()) == (false))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{329,5},{329,13}})).get</*L2*/9>()).get</*State*/0>()) == (Shrd))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{330,17},{330,25}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined()));
    } catch (...) { throw ::romp::ModelRuleError(2,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2_Recv_Get_Put(const Procss p, const NODE src) {
    try {
      // this expr is added to differentiate rule "L2HeadPtr_Recv_Get_Put"
      // Procs[p].L2.ShrSet[src] := true;
      ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{333,5},{333,13}})).get</*L2*/9>()).get</*ShrSet*/4>()), (src), ::romp::location{{333,5},{333,28}})), (true), ::romp::location{{333,5},{333,36}});
      // Procs[p].UniMsg[src].Cmd := UNI_Put;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{334,5},{334,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{334,5},{334,25}})).get</*Cmd*/0>()), (UNI_Put), ::romp::location{{334,5},{334,40}});
      // Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
      ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{335,5},{335,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{335,5},{335,25}})).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{335,34},{335,42}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{335,5},{335,50}});
      // Undefine Procs[p].UniMsg[src].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{336,14},{336,22}})).get</*UniMsg*/4>()), (src), ::romp::location{{336,14},{336,34}})).get</*Proc*/1>())).Undefine();
    } catch (...) { throw ::romp::ModelRuleError(2,::romp::ModelRuleError::ACTION); }
  }

  // Ruleset
  
  bool __romp__Rule_guard__L2_busy_Recv_Get_X__Nak(const Procss p, const NODE src) const {
    try {
      return ((((((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{346,6},{346,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{346,6},{346,26}})).get</*Cmd*/0>()) == (UNI_Get)) || (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{347,6},{347,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{347,6},{347,26}})).get</*Cmd*/0>()) == (UNI_GetX))) && (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{348,5},{348,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{348,5},{348,25}})).get</*Proc*/1>()) == (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{350,5},{350,13}})).get</*L2*/9>()).get</*pending*/2>()) == (true)));
    } catch (...) { throw ::romp::ModelRuleError(3,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2_busy_Recv_Get_X__Nak(const Procss p, const NODE src) {
    try {
      // Procs[p].UniMsg[src].Cmd := UNI_Nak;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{353,5},{353,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{353,5},{353,25}})).get</*Cmd*/0>()), (UNI_Nak), ::romp::location{{353,5},{353,40}});
      // Undefine Procs[p].UniMsg[src].Data;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{354,14},{354,22}})).get</*UniMsg*/4>()), (src), ::romp::location{{354,14},{354,34}})).get</*Data*/2>())).Undefine();
      // Undefine Procs[p].UniMsg[src].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{355,14},{355,22}})).get</*UniMsg*/4>()), (src), ::romp::location{{355,14},{355,34}})).get</*Proc*/1>())).Undefine();
    } catch (...) { throw ::romp::ModelRuleError(3,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L2HeadPtr_Recv_Get_Put(const Procss p, const NODE src) const {
    try {
      return (((((((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{364,3},{364,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{364,3},{364,23}})).get</*Cmd*/0>()) == (UNI_Get)) && (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{365,3},{365,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{365,3},{365,23}})).get</*Proc*/1>()) == (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{367,3},{367,11}})).get</*L2*/9>()).get</*pending*/2>()) == (false))) && (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{368,16},{368,24}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined()))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{369,3},{369,11}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2)));
    } catch (...) { throw ::romp::ModelRuleError(4,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2HeadPtr_Recv_Get_Put(const Procss p, const NODE src) {
    try {
      // Procs[p].L2.State := Shrd;
      ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{372,3},{372,11}})).get</*L2*/9>()).get</*State*/0>()), (Shrd), ::romp::location{{372,3},{372,28}});
      // Undefine Procs[p].L2.HeadPtr;
      ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{373,12},{373,20}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
      // Procs[p].L2.ShrSet[src] := true;
      ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{374,3},{374,11}})).get</*L2*/9>()).get</*ShrSet*/4>()), (src), ::romp::location{{374,3},{374,26}})), (true), ::romp::location{{374,3},{374,34}});
      // Procs[p].UniMsg[src].Cmd := UNI_Put;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{376,3},{376,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{376,3},{376,23}})).get</*Cmd*/0>()), (UNI_Put), ::romp::location{{376,3},{376,38}});
      // Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
      ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{377,3},{377,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{377,3},{377,23}})).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{377,32},{377,40}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{377,3},{377,48}});
      // Undefine Procs[p].UniMsg[src].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{378,12},{378,20}})).get</*UniMsg*/4>()), (src), ::romp::location{{378,12},{378,32}})).get</*Proc*/1>())).Undefine();
    } catch (...) { throw ::romp::ModelRuleError(4,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L2_Fwd_Get_X_(const Procss p, const NODE src) const {
    try {
      return (((((((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{387,5},{387,13}})).get</*L2*/9>()).get</*pending*/2>()) == (false)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{388,5},{388,13}})).get</*L2*/9>()).get</*State*/0>()) == (Excl))) && (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{389,19},{389,27}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined()))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{390,5},{390,13}})).get</*L2*/9>()).get</*HeadPtr*/6>()) != (L2))) && ((((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{392,6},{392,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{392,6},{392,26}})).get</*Cmd*/0>()) == (UNI_Get)) || (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{393,6},{393,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{393,6},{393,26}})).get</*Cmd*/0>()) == (UNI_GetX)))) && (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{394,5},{394,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{394,5},{394,25}})).get</*Proc*/1>()) == (L2)));
    } catch (...) { throw ::romp::ModelRuleError(5,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2_Fwd_Get_X_(const Procss p, const NODE src) {
    try {
      NODE owner;
      boolean isGet;
      // owner := Procs[p].L2.HeadPtr;
      ::romp::Assignment<NODE>((owner), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{400,14},{400,22}})).get</*L2*/9>()).get</*HeadPtr*/6>()), ::romp::location{{400,5},{400,33}});
      // isGet := true;
      ::romp::Assignment<boolean>((isGet), (true), ::romp::location{{401,5},{401,18}});
      if (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{402,9},{402,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{402,9},{402,29}})).get</*Cmd*/0>()) == (UNI_GetX)) {
        // isGet := false;
        ::romp::Assignment<boolean>((isGet), (false), ::romp::location{{403,7},{403,21}});
      }
      // must have silentdropped itself
      if ((src) == (owner)) {
        if ((isGet) == (true)) {
          // Procs[p].L2.State := Shrd;
          ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{409,9},{409,17}})).get</*L2*/9>()).get</*State*/0>()), (Shrd), ::romp::location{{409,9},{409,34}});
          // Procs[p].L2.ShrSet[owner] := true;
          ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{410,9},{410,17}})).get</*L2*/9>()).get</*ShrSet*/4>()), (owner), ::romp::location{{410,9},{410,34}})), (true), ::romp::location{{410,9},{410,42}});
          // Undefine Procs[p].L2.HeadPtr;
          ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{411,18},{411,26}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
          // Procs[p].UniMsg[src].Cmd := UNI_Put;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{412,9},{412,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{412,9},{412,29}})).get</*Cmd*/0>()), (UNI_Put), ::romp::location{{412,9},{412,44}});
          // Undefine Procs[p].UniMsg[src].Proc;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{413,18},{413,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{413,18},{413,38}})).get</*Proc*/1>())).Undefine();
          // Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{414,9},{414,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{414,9},{414,29}})).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{414,38},{414,46}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{414,9},{414,54}});
        } else {
          // Procs[p].UniMsg[src].Cmd := UNI_PutX;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{416,9},{416,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{416,9},{416,29}})).get</*Cmd*/0>()), (UNI_PutX), ::romp::location{{416,9},{416,45}});
          // Undefine Procs[p].UniMsg[src].Proc;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{417,18},{417,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{417,18},{417,38}})).get</*Proc*/1>())).Undefine();
          // Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{418,9},{418,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{418,9},{418,29}})).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{418,38},{418,46}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{418,9},{418,54}});
        }
      } else {
        // fwd req to remote owner
        // Procs[p].L2.pending := true;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{423,7},{423,15}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{423,7},{423,34}});
        if ((isGet) == (true)) {
          // Procs[p].UniMsg[src].Cmd := UNI_Get;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{425,9},{425,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{425,9},{425,29}})).get</*Cmd*/0>()), (UNI_Get), ::romp::location{{425,9},{425,44}});
          // Procs[p].UniMsg[src].Proc := owner;
          ::romp::Assignment<NODE_L2>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{426,9},{426,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{426,9},{426,29}})).get</*Proc*/1>()), (owner), ::romp::location{{426,9},{426,43}});
          // Undefine Procs[p].UniMsg[src].Data;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{427,18},{427,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{427,18},{427,38}})).get</*Data*/2>())).Undefine();
        } else {
          // Procs[p].UniMsg[src].Cmd := UNI_GetX;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{429,9},{429,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{429,9},{429,29}})).get</*Cmd*/0>()), (UNI_GetX), ::romp::location{{429,9},{429,45}});
          // Procs[p].UniMsg[src].Proc := owner;
          ::romp::Assignment<NODE_L2>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{430,9},{430,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{430,9},{430,29}})).get</*Proc*/1>()), (owner), ::romp::location{{430,9},{430,43}});
          // Undefine Procs[p].UniMsg[src].Data;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{431,18},{431,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{431,18},{431,38}})).get</*Data*/2>())).Undefine();
        }
      }
    } catch (...) { throw ::romp::ModelRuleError(5,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L2_Recv_Get_X__OutGet_X_(const Procss p, const NODE src) const {
    try {
      return (((((((((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{442,6},{442,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{442,6},{442,26}})).get</*Cmd*/0>()) == (UNI_Get)) || (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{443,6},{443,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{443,6},{443,26}})).get</*Cmd*/0>()) == (UNI_GetX))) && (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{444,5},{444,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{444,5},{444,25}})).get</*Proc*/1>()) == (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{446,5},{446,13}})).get</*L2*/9>()).get</*State*/0>()) == (Invld))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{447,5},{447,13}})).get</*L2*/9>()).get</*pending*/2>()) == (false))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{448,5},{448,13}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{449,5},{449,13}})).get</*L2*/9>()).get</*Gblock_WB*/11>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(6,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2_Recv_Get_X__OutGet_X_(const Procss p, const NODE src) {
    try {
      boolean isGet;
      // Procs[p].L2.pending := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{453,5},{453,13}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{453,5},{453,32}});
      // Procs[p].L2.ReqId := src;
      ::romp::Assignment<NODE>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{454,5},{454,13}})).get</*L2*/9>()).get</*ReqId*/7>()), (src), ::romp::location{{454,5},{454,29}});
      // isGet := true;
      ::romp::Assignment<boolean>((isGet), (true), ::romp::location{{456,5},{456,18}});
      if (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{457,9},{457,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{457,9},{457,29}})).get</*Cmd*/0>()) == (UNI_GetX)) {
        // isGet := false;
        ::romp::Assignment<boolean>((isGet), (false), ::romp::location{{458,7},{458,21}});
      }
      if ((isGet) == (true)) {
        if ((p) == (Home)) {
          // Procs[p].RAC.State := WRDO;
          ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{462,9},{462,17}})).get</*RAC*/10>()).get</*State*/0>()), (WRDO), ::romp::location{{462,9},{462,35}});
        } else {
          // Procs[p].RAC.State := WRD;
          ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{464,9},{464,17}})).get</*RAC*/10>()).get</*State*/0>()), (WRD), ::romp::location{{464,9},{464,34}});
          // GUniMsg[p].Cmd := RD_H;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{465,9},{465,19}})).get</*Cmd*/0>()), (RD_H), ::romp::location{{465,9},{465,31}});
          // Undefine GUniMsg[p].Cluster;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{466,18},{466,28}})).get</*Cluster*/1>())).Undefine();
          // Undefine GUniMsg[p].Data;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{467,18},{467,28}})).get</*Data*/3>())).Undefine();
          // Undefine GUniMsg[p].InvCnt;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{468,18},{468,28}})).get</*InvCnt*/2>())).Undefine();
        }
      } else {
        // Procs[p].RAC.State := WRDX;
        ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{471,7},{471,15}})).get</*RAC*/10>()).get</*State*/0>()), (WRDX), ::romp::location{{471,7},{471,33}});
        if ((p) != (Home)) {
          // GUniMsg[p].Cmd := RDX_H;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{473,9},{473,19}})).get</*Cmd*/0>()), (RDX_H), ::romp::location{{473,9},{473,32}});
          // Undefine GUniMsg[p].Cluster;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{474,18},{474,28}})).get</*Cluster*/1>())).Undefine();
          // Undefine GUniMsg[p].Data;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{475,18},{475,28}})).get</*Data*/3>())).Undefine();
          // Undefine GUniMsg[p].InvCnt;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{476,18},{476,28}})).get</*InvCnt*/2>())).Undefine();
        }
      }
      // Procs[p].L2.isRetired := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{479,5},{479,13}})).get</*L2*/9>()).get</*isRetired*/12>()), (false), ::romp::location{{479,5},{479,35}});
      // Undefine Procs[p].UniMsg[src];
      ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{481,14},{481,22}})).get</*UniMsg*/4>()), (src), ::romp::location{{481,14},{481,34}}))).Undefine();
      // Procs[p].UniMsg[src].Cmd := UNI_None;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{482,5},{482,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{482,5},{482,25}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{482,5},{482,41}});
    } catch (...) { throw ::romp::ModelRuleError(6,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__L1_GetX(const Procss p, const NODE src) const {
    try {
      return ((((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{490,3},{490,11}})).get</*Proc*/3>()), (src), ::romp::location{{490,3},{490,21}})).get</*ProcCmd*/0>()) == (NODE_None)) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{491,3},{491,11}})).get</*Proc*/3>()), (src), ::romp::location{{491,3},{491,21}})).get</*CacheState*/2>()) != (CACHE_E))) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{492,3},{492,11}})).get</*Proc*/3>()), (src), ::romp::location{{492,3},{492,21}})).get</*CacheState*/2>()) != (CACHE_M))) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{493,3},{493,11}})).get</*Proc*/3>()), (src), ::romp::location{{493,3},{493,21}})).get</*block_WB*/4>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(7,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1_GetX(const Procss p, const NODE src) {
    try {
      // Procs[p].UniMsg[src].Cmd := UNI_GetX;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{496,3},{496,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{496,3},{496,23}})).get</*Cmd*/0>()), (UNI_GetX), ::romp::location{{496,3},{496,39}});
      // Procs[p].UniMsg[src].Proc := L2;
      ::romp::Assignment<NODE_L2>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{497,3},{497,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{497,3},{497,23}})).get</*Proc*/1>()), (L2), ::romp::location{{497,3},{497,34}});
      // Undefine Procs[p].UniMsg[src].Data;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{498,12},{498,20}})).get</*UniMsg*/4>()), (src), ::romp::location{{498,12},{498,32}})).get</*Data*/2>())).Undefine();
      // Procs[p].Proc[src].ProcCmd := NODE_GetX;
      ::romp::Assignment<NODE_CMD>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{500,3},{500,11}})).get</*Proc*/3>()), (src), ::romp::location{{500,3},{500,21}})).get</*ProcCmd*/0>()), (NODE_GetX), ::romp::location{{500,3},{500,42}});
    } catch (...) { throw ::romp::ModelRuleError(7,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX(const Procss p, const NODE src) const {
    try {
      return ((((((((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{509,3},{509,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{509,3},{509,23}})).get</*Cmd*/0>()) == (UNI_GetX)) && (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{510,3},{510,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{510,3},{510,23}})).get</*Proc*/1>()) == (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{512,3},{512,11}})).get</*L2*/9>()).get</*pending*/2>()) == (false))) && (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{513,16},{513,24}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined()))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{514,3},{514,11}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{515,3},{515,11}})).get</*L2*/9>()).get</*State*/0>()) != (Invld)));
    } catch (...) { throw ::romp::ModelRuleError(8,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2HeadPtr_Recv_GetX_PutX(const Procss p, const NODE src) {
    try {
      if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{518,7},{518,15}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (true)) {
        // Procs[p].L2.State := Excl;
        ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{519,5},{519,13}})).get</*L2*/9>()).get</*State*/0>()), (Excl), ::romp::location{{519,5},{519,30}});
        // Procs[p].L2.HeadPtr := src;
        ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{520,5},{520,13}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (src), ::romp::location{{520,5},{520,31}});
        // Procs[p].UniMsg[src].Cmd := UNI_PutX;
        ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{522,5},{522,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{522,5},{522,25}})).get</*Cmd*/0>()), (UNI_PutX), ::romp::location{{522,5},{522,41}});
        // Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
        ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{523,5},{523,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{523,5},{523,25}})).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{523,34},{523,42}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{523,5},{523,50}});
        // Undefine Procs[p].UniMsg[src].Proc;
        (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{524,14},{524,22}})).get</*UniMsg*/4>()), (src), ::romp::location{{524,14},{524,34}})).get</*Proc*/1>())).Undefine();
      } else {
        if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{527,9},{527,17}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)) {
          // Procs[p].L2.pending := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{528,7},{528,15}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{528,7},{528,34}});
          // Procs[p].L2.ReqId := src;
          ::romp::Assignment<NODE>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{529,7},{529,15}})).get</*L2*/9>()).get</*ReqId*/7>()), (src), ::romp::location{{529,7},{529,31}});
          // Procs[p].RAC.State := WRDX;
          ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{530,7},{530,15}})).get</*RAC*/10>()).get</*State*/0>()), (WRDX), ::romp::location{{530,7},{530,33}});
          if ((p) != (Home)) {
            // GUniMsg[p].Cmd := RDX_H;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{532,9},{532,19}})).get</*Cmd*/0>()), (RDX_H), ::romp::location{{532,9},{532,32}});
            // Undefine GUniMsg[p].Cluster;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{533,18},{533,28}})).get</*Cluster*/1>())).Undefine();
            // Undefine GUniMsg[p].Data;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{534,18},{534,28}})).get</*Data*/3>())).Undefine();
            // Undefine GUniMsg[p].InvCnt;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{535,18},{535,28}})).get</*InvCnt*/2>())).Undefine();
          }
          // Undefine Procs[p].UniMsg[src];
          ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{538,16},{538,24}})).get</*UniMsg*/4>()), (src), ::romp::location{{538,16},{538,36}}))).Undefine();
          // Procs[p].UniMsg[src].Cmd := UNI_None;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{539,7},{539,15}})).get</*UniMsg*/4>()), (src), ::romp::location{{539,7},{539,27}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{539,7},{539,43}});
          // Procs[p].L2.isRetired := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{540,7},{540,15}})).get</*L2*/9>()).get</*isRetired*/12>()), (false), ::romp::location{{540,7},{540,37}});
        } else {
          // Undefine Procs[p].UniMsg[src];
          ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{543,16},{543,24}})).get</*UniMsg*/4>()), (src), ::romp::location{{543,16},{543,36}}))).Undefine();
          // Procs[p].UniMsg[src].Cmd := UNI_Nak;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{544,7},{544,15}})).get</*UniMsg*/4>()), (src), ::romp::location{{544,7},{544,27}})).get</*Cmd*/0>()), (UNI_Nak), ::romp::location{{544,7},{544,42}});
        }
      }
    } catch (...) { throw ::romp::ModelRuleError(8,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L2Shrd_Recv_GetX__PutX_(const Procss p, const NODE src) const {
    try {
      return ((((((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{555,5},{555,13}})).get</*L2*/9>()).get</*State*/0>()) == (Shrd)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{556,5},{556,13}})).get</*L2*/9>()).get</*pending*/2>()) == (false))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{557,17},{557,25}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{559,5},{559,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{559,5},{559,25}})).get</*Cmd*/0>()) == (UNI_GetX))) && (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{560,5},{560,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{560,5},{560,25}})).get</*Proc*/1>()) == (L2)));
    } catch (...) { throw ::romp::ModelRuleError(9,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2Shrd_Recv_GetX__PutX_(const Procss p, const NODE src) {
    try {
      CacheCnt iCnt;
      // this cluster has the only copy
      if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{566,9},{566,17}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (true)) {
        // Procs[p].L2.State := Excl;
        ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{568,7},{568,15}})).get</*L2*/9>()).get</*State*/0>()), (Excl), ::romp::location{{568,7},{568,32}});
        // Procs[p].L2.HeadPtr := src;
        ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{569,7},{569,15}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (src), ::romp::location{{569,7},{569,33}});
        // Procs[p].UniMsg[src].Cmd := UNI_PutX;
        ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{570,7},{570,15}})).get</*UniMsg*/4>()), (src), ::romp::location{{570,7},{570,27}})).get</*Cmd*/0>()), (UNI_PutX), ::romp::location{{570,7},{570,43}});
        // Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
        ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{571,7},{571,15}})).get</*UniMsg*/4>()), (src), ::romp::location{{571,7},{571,27}})).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{571,36},{571,44}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{571,7},{571,52}});
        // Undefine Procs[p].UniMsg[src].Proc;
        (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{572,16},{572,24}})).get</*UniMsg*/4>()), (src), ::romp::location{{572,16},{572,36}})).get</*Proc*/1>())).Undefine();
        // src is the only sharer
        if (({bool res_ = true; for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) { res_ &= (!((n) != (src)) || ((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{575,40},{575,48}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{575,40},{575,61}})) == (false))); } res_; })) {
          // Procs[p].L2.ShrSet[src] := false;
          ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{576,9},{576,17}})).get</*L2*/9>()).get</*ShrSet*/4>()), (src), ::romp::location{{576,9},{576,32}})), (false), ::romp::location{{576,9},{576,41}});
        } else {
          // Procs[p].L2.pending := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{578,9},{578,17}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{578,9},{578,36}});
          // iCnt := 0;
          ::romp::Assignment<CacheCnt>((iCnt), ((::romp::range_t)(0)), ::romp::location{{579,9},{579,18}});
          for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) {
            if ((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{581,15},{581,23}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{581,15},{581,36}})) == (true)) {
              // iCnt := (iCnt + 1);
              ::romp::Assignment<CacheCnt>((iCnt), ((iCnt) + ((::romp::range_t)(1))), ::romp::location{{582,7},{582,23}});
              // Procs[p].InvMsg[n].Cmd := INV_Inv;
              ::romp::Assignment<INV_CMD>(((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{583,13},{583,21}})).get</*InvMsg*/5>()), (n), ::romp::location{{583,13},{583,31}})).get</*Cmd*/0>()), (INV_Inv), ::romp::location{{583,13},{583,46}});
              // Procs[p].L2.ShrSet[n] := false;
              ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{584,13},{584,21}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{584,13},{584,34}})), (false), ::romp::location{{584,13},{584,43}});
            }
          }

          // Procs[p].L2.InvCnt := iCnt;
          ::romp::Assignment<CacheCnt>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{587,9},{587,17}})).get</*L2*/9>()).get</*InvCnt*/5>()), (iCnt), ::romp::location{{587,9},{587,35}});
          // invariant purpose
          // Procs[p].PrevData := Procs[p].CurrData;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{589,9},{589,17}})).get</*PrevData*/1>()), ((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{589,30},{589,38}})).get</*CurrData*/0>()), ::romp::location{{589,9},{589,47}});
          // Procs[p].Collecting := true;
          ::romp::Assignment<boolean>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{590,9},{590,17}})).get</*Collecting*/2>()), (true), ::romp::location{{590,9},{590,36}});
        }
      } else {
        // no pending activity with RAC
        if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{596,11},{596,19}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)) {
          // Procs[p].L2.pending := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{597,9},{597,17}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{597,9},{597,36}});
          if ((!({bool res_ = true; for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) { res_ &= ((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{598,33},{598,41}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{598,33},{598,54}})) == (false)); } res_; }))) {
            // iCnt := 0;
            ::romp::Assignment<CacheCnt>((iCnt), ((::romp::range_t)(0)), ::romp::location{{599,4},{599,13}});
            for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) {
              if ((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{601,17},{601,25}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{601,17},{601,38}})) == (true)) {
                // iCnt := (iCnt + 1);
                ::romp::Assignment<CacheCnt>((iCnt), ((iCnt) + ((::romp::range_t)(1))), ::romp::location{{602,8},{602,24}});
                // Procs[p].InvMsg[n].Cmd := INV_Inv;
                ::romp::Assignment<INV_CMD>(((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{603,15},{603,23}})).get</*InvMsg*/5>()), (n), ::romp::location{{603,15},{603,33}})).get</*Cmd*/0>()), (INV_Inv), ::romp::location{{603,15},{603,48}});
                // Procs[p].L2.ShrSet[n] := false;
                ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{604,15},{604,23}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{604,15},{604,36}})), (false), ::romp::location{{604,15},{604,45}});
              }
            }

            // Procs[p].L2.InvCnt := iCnt;
            ::romp::Assignment<CacheCnt>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{607,11},{607,19}})).get</*L2*/9>()).get</*InvCnt*/5>()), (iCnt), ::romp::location{{607,11},{607,37}});
            // Procs[p].PrevData := Procs[p].CurrData;
            ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{608,11},{608,19}})).get</*PrevData*/1>()), ((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{608,32},{608,40}})).get</*CurrData*/0>()), ::romp::location{{608,11},{608,49}});
            // Procs[p].Collecting := true;
            ::romp::Assignment<boolean>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{609,11},{609,19}})).get</*Collecting*/2>()), (true), ::romp::location{{609,11},{609,38}});
          }
          // Procs[p].RAC.State := WRDX;
          ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{611,9},{611,17}})).get</*RAC*/10>()).get</*State*/0>()), (WRDX), ::romp::location{{611,9},{611,35}});
          // Procs[p].L2.ReqId := src;
          ::romp::Assignment<NODE>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{612,9},{612,17}})).get</*L2*/9>()).get</*ReqId*/7>()), (src), ::romp::location{{612,9},{612,33}});
          if ((p) != (Home)) {
            // GUniMsg[p].Cmd := RDX_H;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{614,11},{614,21}})).get</*Cmd*/0>()), (RDX_H), ::romp::location{{614,11},{614,34}});
            // Undefine GUniMsg[p].Cluster;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{615,20},{615,30}})).get</*Cluster*/1>())).Undefine();
            // Undefine GUniMsg[p].Data;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{616,20},{616,30}})).get</*Data*/3>())).Undefine();
            // Undefine GUniMsg[p].InvCnt;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{617,20},{617,30}})).get</*InvCnt*/2>())).Undefine();
          }
          // Undefine Procs[p].UniMsg[src];
          ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{619,18},{619,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{619,18},{619,38}}))).Undefine();
          // Procs[p].UniMsg[src].Cmd := UNI_None;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{620,9},{620,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{620,9},{620,29}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{620,9},{620,45}});
          // Procs[p].L2.isRetired := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{621,2},{621,10}})).get</*L2*/9>()).get</*isRetired*/12>()), (false), ::romp::location{{621,2},{621,32}});
        } else {
          // Procs[p].UniMsg[src].Cmd := UNI_Nak;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{624,9},{624,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{624,9},{624,29}})).get</*Cmd*/0>()), (UNI_Nak), ::romp::location{{624,9},{624,44}});
          // Undefine Procs[p].UniMsg[src].Data;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{625,18},{625,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{625,18},{625,38}})).get</*Data*/2>())).Undefine();
          // Undefine Procs[p].UniMsg[src].Proc;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{626,18},{626,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{626,18},{626,38}})).get</*Proc*/1>())).Undefine();
        }
      }
    } catch (...) { throw ::romp::ModelRuleError(9,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L1_Recv_Inv(const Procss p, const NODE dst) const {
    try {
      return (((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{637,5},{637,13}})).get</*InvMsg*/5>()), (dst), ::romp::location{{637,5},{637,25}})).get</*Cmd*/0>()) == (INV_Inv));
    } catch (...) { throw ::romp::ModelRuleError(10,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1_Recv_Inv(const Procss p, const NODE dst) {
    try {
      // Procs[p].InvMsg[dst].Cmd := INV_InvAck;
      ::romp::Assignment<INV_CMD>(((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{640,5},{640,13}})).get</*InvMsg*/5>()), (dst), ::romp::location{{640,5},{640,25}})).get</*Cmd*/0>()), (INV_InvAck), ::romp::location{{640,5},{640,43}});
      if ((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{642,9},{642,17}})).get</*Proc*/3>()), (dst), ::romp::location{{642,9},{642,27}})).get</*CacheState*/2>()) != (CACHE_E)) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{643,2},{643,10}})).get</*Proc*/3>()), (dst), ::romp::location{{643,2},{643,20}})).get</*CacheState*/2>()) != (CACHE_M))) {
        // Procs[p].Proc[dst].CacheState := CACHE_I;
        ::romp::Assignment<CACHE_STATE>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{644,7},{644,15}})).get</*Proc*/3>()), (dst), ::romp::location{{644,7},{644,25}})).get</*CacheState*/2>()), (CACHE_I), ::romp::location{{644,7},{644,47}});
        // Undefine Procs[p].Proc[dst].CacheData;
        (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{645,16},{645,24}})).get</*Proc*/3>()), (dst), ::romp::location{{645,16},{645,34}})).get</*CacheData*/3>())).Undefine();
      }
      if (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{647,9},{647,17}})).get</*Proc*/3>()), (dst), ::romp::location{{647,9},{647,27}})).get</*ProcCmd*/0>()) == (NODE_Get)) {
        // Procs[p].Proc[dst].InvMarked := true;
        ::romp::Assignment<boolean>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{648,7},{648,15}})).get</*Proc*/3>()), (dst), ::romp::location{{648,7},{648,25}})).get</*InvMarked*/1>()), (true), ::romp::location{{648,7},{648,43}});
      }
    } catch (...) { throw ::romp::ModelRuleError(10,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L2_Recv_InvAck(const Procss p, const NODE src) const {
    try {
      return (((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{658,5},{658,13}})).get</*InvMsg*/5>()), (src), ::romp::location{{658,5},{658,25}})).get</*Cmd*/0>()) == (INV_InvAck));
    } catch (...) { throw ::romp::ModelRuleError(11,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2_Recv_InvAck(const Procss p, const NODE src) {
    try {
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{661,13},{661,21}})).get</*L2*/9>()).get</*pending*/2>()) == (true)),0u)) throw ::romp::ModelPropertyError(0);

      // Procs[p].L2.InvCnt := (Procs[p].L2.InvCnt - 1);
      ::romp::Assignment<CacheCnt>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{662,5},{662,13}})).get</*L2*/9>()).get</*InvCnt*/5>()), ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{662,27},{662,35}})).get</*L2*/9>()).get</*InvCnt*/5>()) - ((::romp::range_t)(1))), ::romp::location{{662,5},{662,49}});
      if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{664,9},{664,17}})).get</*L2*/9>()).get</*InvCnt*/5>()) == ((::romp::range_t)(0))) {
        // invariant purpose
        // Procs[p].Collecting := false;
        ::romp::Assignment<boolean>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{666,7},{666,15}})).get</*Collecting*/2>()), (false), ::romp::location{{666,7},{666,35}});
        if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{667,11},{667,19}})).get</*L2*/9>()).get</*State*/0>()) == (Invld)) {
          // invariant purpose
          // Undefine Procs[p].CurrData;
          (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{669,18},{669,26}})).get</*CurrData*/0>())).Undefine();
          // Undefine Procs[p].PrevData;
          (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{670,18},{670,26}})).get</*PrevData*/1>())).Undefine();
        }
        if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{673,11},{673,19}})).get</*L2*/9>()).get</*isRetired*/12>()) == (true)) {
          // Procs[p].L2.pending := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{674,9},{674,17}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{674,9},{674,37}});
        }
      }
      // Procs[p].InvMsg[src].Cmd := INV_None;
      ::romp::Assignment<INV_CMD>(((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{678,5},{678,13}})).get</*InvMsg*/5>()), (src), ::romp::location{{678,5},{678,25}})).get</*Cmd*/0>()), (INV_None), ::romp::location{{678,5},{678,41}});
    } catch (...) { throw ::romp::ModelRuleError(11,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(const Procss p, const NODE dst, const NODE_L2 src) const {
    try {
      return ((((((((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{688,6},{688,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{688,6},{688,26}})).get</*Cmd*/0>()) == (UNI_Get)) || (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{689,6},{689,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{689,6},{689,26}})).get</*Cmd*/0>()) == (UNI_GetX))) && (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{690,5},{690,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{690,5},{690,25}})).get</*Proc*/1>()) == (dst))) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{692,5},{692,13}})).get</*Proc*/3>()), (dst), ::romp::location{{692,5},{692,23}})).get</*CacheState*/2>()) != (CACHE_E))) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{693,5},{693,13}})).get</*Proc*/3>()), (dst), ::romp::location{{693,5},{693,23}})).get</*CacheState*/2>()) != (CACHE_M))) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{694,5},{694,13}})).get</*Proc*/3>()), (dst), ::romp::location{{694,5},{694,23}})).get</*block_WB*/4>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(12,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak(const Procss p, const NODE dst, const NODE_L2 src) {
    try {
      if (this->__rw__->assertion_handler(((src) != (dst)),1u)) throw ::romp::ModelPropertyError(1);

      if ((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{699,9},{699,17}})).get</*Proc*/3>()), (dst), ::romp::location{{699,9},{699,27}})).get</*CacheState*/2>()) == (CACHE_I)) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{700,2},{700,10}})).get</*Proc*/3>()), (dst), ::romp::location{{700,2},{700,20}})).get</*ProcCmd*/0>()) == (NODE_None))) {
        if ((src) == (L2)) {
          // Procs[p].NakcMsg.Cmd := NAKC_SD;
          ::romp::Assignment<NAKC_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{702,9},{702,17}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()), (NAKC_SD), ::romp::location{{702,9},{702,40}});
          // Procs[p].NakcMsg.Proc := dst;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{703,9},{703,17}})).get</*NakcMsg*/8>()).get</*Proc*/1>()), (dst), ::romp::location{{703,9},{703,37}});
          // Procs[p].NakcMsg.Aux := src;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{704,9},{704,17}})).get</*NakcMsg*/8>()).get</*Aux*/2>()), (src), ::romp::location{{704,9},{704,36}});
          // Undefine Procs[p].UniMsg[src];
          ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{705,18},{705,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{705,18},{705,38}}))).Undefine();
          // Procs[p].UniMsg[src].Cmd := UNI_None;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{706,9},{706,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{706,9},{706,29}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{706,9},{706,45}});
        } else {
          // Procs[p].NakcMsg.Cmd := NAKC_SD;
          ::romp::Assignment<NAKC_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{708,9},{708,17}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()), (NAKC_SD), ::romp::location{{708,9},{708,40}});
          // Procs[p].NakcMsg.Proc := dst;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{709,9},{709,17}})).get</*NakcMsg*/8>()).get</*Proc*/1>()), (dst), ::romp::location{{709,9},{709,37}});
          // Procs[p].NakcMsg.Aux := src;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{710,9},{710,17}})).get</*NakcMsg*/8>()).get</*Aux*/2>()), (src), ::romp::location{{710,9},{710,36}});
          // Procs[p].UniMsg[src].Cmd := UNI_Nak;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{711,9},{711,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{711,9},{711,29}})).get</*Cmd*/0>()), (UNI_Nak), ::romp::location{{711,9},{711,44}});
          // Undefine Procs[p].UniMsg[src].Proc;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{712,18},{712,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{712,18},{712,38}})).get</*Proc*/1>())).Undefine();
          // Undefine Procs[p].UniMsg[src].Data;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{713,18},{713,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{713,18},{713,38}})).get</*Data*/2>())).Undefine();
        }
      } else {
        if ((src) == (L2)) {
          // Procs[p].NakcMsg.Cmd := NAKC_Nakc;
          ::romp::Assignment<NAKC_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{718,9},{718,17}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()), (NAKC_Nakc), ::romp::location{{718,9},{718,42}});
          // Procs[p].NakcMsg.Proc := dst;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{719,9},{719,17}})).get</*NakcMsg*/8>()).get</*Proc*/1>()), (dst), ::romp::location{{719,9},{719,37}});
          // Procs[p].NakcMsg.Aux := src;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{720,9},{720,17}})).get</*NakcMsg*/8>()).get</*Aux*/2>()), (src), ::romp::location{{720,9},{720,36}});
          // Undefine Procs[p].UniMsg[src];
          ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{721,18},{721,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{721,18},{721,38}}))).Undefine();
          // Procs[p].UniMsg[src].Cmd := UNI_None;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{722,9},{722,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{722,9},{722,29}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{722,9},{722,45}});
        } else {
          // Procs[p].NakcMsg.Cmd := NAKC_Nakc;
          ::romp::Assignment<NAKC_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{724,9},{724,17}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()), (NAKC_Nakc), ::romp::location{{724,9},{724,42}});
          // Procs[p].NakcMsg.Proc := dst;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{725,9},{725,17}})).get</*NakcMsg*/8>()).get</*Proc*/1>()), (dst), ::romp::location{{725,9},{725,37}});
          // Procs[p].NakcMsg.Aux := src;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{726,9},{726,17}})).get</*NakcMsg*/8>()).get</*Aux*/2>()), (src), ::romp::location{{726,9},{726,36}});
          // Procs[p].UniMsg[src].Cmd := UNI_Nak;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{727,9},{727,17}})).get</*UniMsg*/4>()), (src), ::romp::location{{727,9},{727,29}})).get</*Cmd*/0>()), (UNI_Nak), ::romp::location{{727,9},{727,44}});
          // Undefine Procs[p].UniMsg[src].Proc;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{728,18},{728,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{728,18},{728,38}})).get</*Proc*/1>())).Undefine();
          // Undefine Procs[p].UniMsg[src].Data;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{729,18},{729,26}})).get</*UniMsg*/4>()), (src), ::romp::location{{729,18},{729,38}})).get</*Data*/2>())).Undefine();
        }
      }
    } catch (...) { throw ::romp::ModelRuleError(12,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L2_Recv_NAKC_Nakc(const Procss p, const NODE src) const {
    try {
      return ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{740,5},{740,13}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()) == (NAKC_Nakc));
    } catch (...) { throw ::romp::ModelRuleError(13,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2_Recv_NAKC_Nakc(const Procss p, const NODE src) {
    try {
      Procss aux;
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{744,13},{744,21}})).get</*L2*/9>()).get</*pending*/2>()) == (true)),2u)) throw ::romp::ModelPropertyError(2);

      // Procs[p].L2.pending := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{745,5},{745,13}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{745,5},{745,33}});
      if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{747,9},{747,17}})).get</*NakcMsg*/8>()).get</*Aux*/2>()) == (L2)) {
        if (this->__rw__->assertion_handler((!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{748,28},{748,36}})).get</*L2*/9>()).get</*ReqCluster*/9>()).IsUndefined())),3u)) throw ::romp::ModelPropertyError(3);

        // aux := Procs[p].L2.ReqCluster;
        ::romp::Assignment<Procss>((aux), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{749,14},{749,22}})).get</*L2*/9>()).get</*ReqCluster*/9>()), ::romp::location{{749,7},{749,36}});
        // Apr 8
        if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{753,15},{753,23}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()) == (true)),4u)) throw ::romp::ModelPropertyError(4);

        // Procs[p].L2.ifHoldMsg := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{754,7},{754,15}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()), (false), ::romp::location{{754,7},{754,37}});
        if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{755,11},{755,19}})).get</*L2*/9>()).get</*ReqType*/10>()) == (true)) {
          if ((p) == (Home)) {
            if (this->__rw__->assertion_handler((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{757,19},{757,31}})).get</*Cmd*/0>()) == (RD_H)),5u)) throw ::romp::ModelPropertyError(5);

          } else {
            if (this->__rw__->assertion_handler(((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{759,19},{759,31}})).get</*Cmd*/0>()) == (RD_RAC)) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{759,47},{759,59}})).get</*Cluster*/1>()) == (p))),6u)) throw ::romp::ModelPropertyError(6);

          }
        } else {
          if ((p) == (Home)) {
            if (this->__rw__->assertion_handler((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{765,19},{765,31}})).get</*Cmd*/0>()) == (RDX_H)),7u)) throw ::romp::ModelPropertyError(7);

          } else {
            if (this->__rw__->assertion_handler(((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{767,19},{767,31}})).get</*Cmd*/0>()) == (RDX_RAC)) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{767,48},{767,60}})).get</*Cluster*/1>()) == (p))),8u)) throw ::romp::ModelPropertyError(8);

          }
        }
        // GUniMsg[aux].Cmd := NAK;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{773,7},{773,19}})).get</*Cmd*/0>()), (NAK), ::romp::location{{773,7},{773,30}});
        // Undefine GUniMsg[aux].Data;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{774,16},{774,28}})).get</*Data*/3>())).Undefine();
        // Undefine GUniMsg[aux].InvCnt;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{775,16},{775,28}})).get</*InvCnt*/2>())).Undefine();
        // Undefine GUniMsg[aux].Cluster;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{776,16},{776,28}})).get</*Cluster*/1>())).Undefine();
        if (((p) != (Home)) && ((aux) != (Home))) {
          // GNakcMsg.Cmd := GNAKC_Nakc;
          ::romp::Assignment<GNAKC_CMD>(((GNakcMsg).get</*Cmd*/0>()), (GNAKC_Nakc), ::romp::location{{779,9},{779,35}});
          // GNakcMsg.Cluster := p;
          ::romp::Assignment<Procss>(((GNakcMsg).get</*Cluster*/1>()), (p), ::romp::location{{780,9},{780,30}});
        }
        // Undefine Procs[p].L2.ReqCluster;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{782,16},{782,24}})).get</*L2*/9>()).get</*ReqCluster*/9>())).Undefine();
        // Undefine Procs[p].L2.ReqType;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{783,16},{783,24}})).get</*L2*/9>()).get</*ReqType*/10>())).Undefine();
      }
      // Undefine Procs[p].NakcMsg;
      (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{785,14},{785,22}})).get</*NakcMsg*/8>())).Undefine();
      // Procs[p].NakcMsg.Cmd := NAKC_None;
      ::romp::Assignment<NAKC_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{786,5},{786,13}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()), (NAKC_None), ::romp::location{{786,5},{786,38}});
    } catch (...) { throw ::romp::ModelRuleError(13,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__RmtCluster_Recv_NAKC_SD(const Rmt p) const {
    try {
      return ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{796,5},{796,13}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()) == (NAKC_SD));
    } catch (...) { throw ::romp::ModelRuleError(14,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__RmtCluster_Recv_NAKC_SD(const Rmt p) {
    try {
      Procss aux;
      boolean isGet;
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{801,13},{801,21}})).get</*L2*/9>()).get</*pending*/2>()) == (true)),9u)) throw ::romp::ModelPropertyError(9);

      // Procs[p].L2.pending := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{802,5},{802,13}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{802,5},{802,33}});
      if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{804,9},{804,17}})).get</*NakcMsg*/8>()).get</*Aux*/2>()) == (L2)) {
        if (this->__rw__->assertion_handler((!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{805,28},{805,36}})).get</*L2*/9>()).get</*ReqCluster*/9>()).IsUndefined())),10u)) throw ::romp::ModelPropertyError(10);

        // aux := Procs[p].L2.ReqCluster;
        ::romp::Assignment<Procss>((aux), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{806,14},{806,22}})).get</*L2*/9>()).get</*ReqCluster*/9>()), ::romp::location{{806,7},{806,36}});
        if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{807,11},{807,19}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{807,33},{807,41}})).get</*NakcMsg*/8>()).get</*Proc*/1>())) {
          // Procs[p].L2.HeadPtr := L2;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{808,9},{808,17}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (L2), ::romp::location{{808,9},{808,34}});
        }
        // Apr 8
        if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{813,15},{813,23}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()) == (true)),11u)) throw ::romp::ModelPropertyError(11);

        // Procs[p].L2.ifHoldMsg := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{814,7},{814,15}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()), (false), ::romp::location{{814,7},{814,37}});
        if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{815,11},{815,19}})).get</*L2*/9>()).get</*ReqType*/10>()) == (true)) {
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{816,19},{816,31}})).get</*Cmd*/0>()) == (RD_RAC)) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{816,47},{816,59}})).get</*Cluster*/1>()) == (p))),12u)) throw ::romp::ModelPropertyError(12);

        } else {
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{819,19},{819,31}})).get</*Cmd*/0>()) == (RDX_RAC)) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{819,48},{819,60}})).get</*Cluster*/1>()) == (p))),13u)) throw ::romp::ModelPropertyError(13);

        }
        // isGet := Procs[p].L2.ReqType;
        ::romp::Assignment<boolean>((isGet), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{825,16},{825,24}})).get</*L2*/9>()).get</*ReqType*/10>()), ::romp::location{{825,7},{825,35}});
        if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{826,11},{826,19}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2)) {
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{827,17},{827,25}})).get</*L2*/9>()).get</*State*/0>()) != (Invld)),14u)) throw ::romp::ModelPropertyError(14);

          if ((isGet) == (true)) {
            // GUniMsg[aux].Cmd := ACK;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{830,11},{830,23}})).get</*Cmd*/0>()), (ACK), ::romp::location{{830,11},{830,34}});
          } else {
            if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{832,8},{832,16}})).get</*L2*/9>()).get</*Dirty*/3>()) == (false)) {
              // GUniMsg[aux].Cmd := IACK;
              ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{833,13},{833,25}})).get</*Cmd*/0>()), (IACK), ::romp::location{{833,13},{833,37}});
            } else {
              // GUniMsg[aux].Cmd := IACKX;
              ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{835,13},{835,25}})).get</*Cmd*/0>()), (IACKX), ::romp::location{{835,13},{835,38}});
            }
          }
          // GUniMsg[aux].Data := Procs[p].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{838,9},{838,21}})).get</*Data*/3>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{838,30},{838,38}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{838,9},{838,46}});
          // GUniMsg[aux].Cluster := p;
          ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{839,9},{839,21}})).get</*Cluster*/1>()), (p), ::romp::location{{839,9},{839,34}});
          // GUniMsg[aux].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{840,9},{840,21}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{840,9},{840,33}});
          if ((isGet) == (true)) {
            // Procs[p].L2.State := Shrd;
            ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{843,11},{843,19}})).get</*L2*/9>()).get</*State*/0>()), (Shrd), ::romp::location{{843,11},{843,36}});
            // Procs[p].L2.OnlyCopy := false;
            ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{844,11},{844,19}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{844,11},{844,40}});
            // Procs[p].L2.Dirty := false;
            ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{845,11},{845,19}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{845,11},{845,37}});
            if ((aux) != (Home)) {
              // GShWbMsg.Cmd := SHWB;
              ::romp::Assignment<GSHWB_CMD>(((GShWbMsg).get</*Cmd*/0>()), (SHWB), ::romp::location{{847,13},{847,33}});
              // GShWbMsg.Data := Procs[p].L2.Data;
              ::romp::Assignment<Datas>(((GShWbMsg).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{848,30},{848,38}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{848,13},{848,46}});
              // GShWbMsg.Cluster := aux;
              ::romp::Assignment<Procss>(((GShWbMsg).get</*Cluster*/1>()), (aux), ::romp::location{{849,13},{849,36}});
            }
          } else {
            if ((aux) != (Home)) {
              // GShWbMsg.Cmd := DXFER;
              ::romp::Assignment<GSHWB_CMD>(((GShWbMsg).get</*Cmd*/0>()), (DXFER), ::romp::location{{854,13},{854,34}});
              // GShWbMsg.Cluster := aux;
              ::romp::Assignment<Procss>(((GShWbMsg).get</*Cluster*/1>()), (aux), ::romp::location{{855,13},{855,36}});
              // Undefine GShWbMsg.Data;
              (((GShWbMsg).get</*Data*/2>())).Undefine();
            }
            // Procs[p].L2.State := Invld;
            ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{859,4},{859,12}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{859,4},{859,30}});
            // Procs[p].L2.OnlyCopy := false;
            ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{860,11},{860,19}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{860,11},{860,40}});
            // Procs[p].L2.Dirty := false;
            ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{861,11},{861,19}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{861,11},{861,37}});
            // Undefine Procs[p].L2.HeadPtr;
            ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{862,20},{862,28}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
            // Undefine Procs[p].L2.Data;
            ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{863,20},{863,28}})).get</*L2*/9>()).get</*Data*/1>())).Undefine();
            // Undefine Procs[p].CurrData;
            (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{864,20},{864,28}})).get</*CurrData*/0>())).Undefine();
            // Undefine Procs[p].PrevData;
            (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{865,20},{865,28}})).get</*PrevData*/1>())).Undefine();
          }
        } else {
          // impossible to this branch?
          if (this->__rw__->assertion_handler((false),15u)) throw ::romp::ModelPropertyError(15);

          // GUniMsg[aux].Cmd := NAK;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{871,9},{871,21}})).get</*Cmd*/0>()), (NAK), ::romp::location{{871,9},{871,32}});
          // Undefine GUniMsg[aux].Data;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{872,18},{872,30}})).get</*Data*/3>())).Undefine();
          // Undefine GUniMsg[aux].InvCnt;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{873,18},{873,30}})).get</*InvCnt*/2>())).Undefine();
          // Undefine GUniMsg[aux].Cluster;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{874,18},{874,30}})).get</*Cluster*/1>())).Undefine();
          if ((aux) != (Home)) {
            // GNakcMsg.Cmd := GNAKC_Nakc;
            ::romp::Assignment<GNAKC_CMD>(((GNakcMsg).get</*Cmd*/0>()), (GNAKC_Nakc), ::romp::location{{877,11},{877,37}});
            // GNakcMsg.Cluster := p;
            ::romp::Assignment<Procss>(((GNakcMsg).get</*Cluster*/1>()), (p), ::romp::location{{878,11},{878,32}});
          }
        }
        // Undefine Procs[p].L2.ReqCluster;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{881,16},{881,24}})).get</*L2*/9>()).get</*ReqCluster*/9>())).Undefine();
        // Undefine Procs[p].L2.ReqType;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{882,16},{882,24}})).get</*L2*/9>()).get</*ReqType*/10>())).Undefine();
      } else {
        if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{885,11},{885,19}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{885,33},{885,41}})).get</*NakcMsg*/8>()).get</*Proc*/1>())) {
          // Procs[p].L2.HeadPtr := L2;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{886,9},{886,17}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (L2), ::romp::location{{886,9},{886,34}});
        }
      }
      // Undefine Procs[p].NakcMsg;
      (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{890,14},{890,22}})).get</*NakcMsg*/8>())).Undefine();
      // Procs[p].NakcMsg.Cmd := NAKC_None;
      ::romp::Assignment<NAKC_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{891,5},{891,13}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()), (NAKC_None), ::romp::location{{891,5},{891,38}});
    } catch (...) { throw ::romp::ModelRuleError(14,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__Home_Recv_NAKC_SD(void) const {
    try {
      return ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{898,5},{898,16}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()) == (NAKC_SD));
    } catch (...) { throw ::romp::ModelRuleError(15,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Home_Recv_NAKC_SD(void) {
    try {
      Procss aux;
      boolean isGet;
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{903,13},{903,24}})).get</*L2*/9>()).get</*pending*/2>()) == (true)),16u)) throw ::romp::ModelPropertyError(16);

      // Procs[Home].L2.pending := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{904,5},{904,16}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{904,5},{904,36}});
      if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{906,9},{906,20}})).get</*NakcMsg*/8>()).get</*Aux*/2>()) == (L2)) {
        if (this->__rw__->assertion_handler((!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{907,28},{907,39}})).get</*L2*/9>()).get</*ReqCluster*/9>()).IsUndefined())),17u)) throw ::romp::ModelPropertyError(17);

        // aux := Procs[Home].L2.ReqCluster;
        ::romp::Assignment<Procss>((aux), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{908,14},{908,25}})).get</*L2*/9>()).get</*ReqCluster*/9>()), ::romp::location{{908,7},{908,39}});
        if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{909,11},{909,22}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{909,36},{909,47}})).get</*NakcMsg*/8>()).get</*Proc*/1>())) {
          // Procs[Home].L2.HeadPtr := L2;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{910,9},{910,20}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (L2), ::romp::location{{910,9},{910,37}});
        }
        // Apr 8
        if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{915,15},{915,26}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()) == (true)),18u)) throw ::romp::ModelPropertyError(18);

        // Procs[Home].L2.ifHoldMsg := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{916,7},{916,18}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()), (false), ::romp::location{{916,7},{916,40}});
        if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{917,11},{917,22}})).get</*L2*/9>()).get</*ReqType*/10>()) == (true)) {
          if (this->__rw__->assertion_handler((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{918,17},{918,29}})).get</*Cmd*/0>()) == (RD_H)),19u)) throw ::romp::ModelPropertyError(19);

        } else {
          if (this->__rw__->assertion_handler((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{920,19},{920,31}})).get</*Cmd*/0>()) == (RDX_H)),20u)) throw ::romp::ModelPropertyError(20);

        }
        // isGet := Procs[Home].L2.ReqType;
        ::romp::Assignment<boolean>((isGet), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{925,16},{925,27}})).get</*L2*/9>()).get</*ReqType*/10>()), ::romp::location{{925,7},{925,38}});
        if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{926,11},{926,22}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2)) {
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{927,17},{927,28}})).get</*L2*/9>()).get</*State*/0>()) != (Invld)),21u)) throw ::romp::ModelPropertyError(21);

          if ((isGet) == (true)) {
            // GUniMsg[aux].Cmd := ACK;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{930,11},{930,23}})).get</*Cmd*/0>()), (ACK), ::romp::location{{930,11},{930,34}});
            // Dir.ShrSet[aux] := true;
            ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (aux), ::romp::location{{931,11},{931,26}})), (true), ::romp::location{{931,11},{931,34}});
            // Dir.Mem := Procs[Home].L2.Data;
            ::romp::Assignment<Datas>(((Dir).get</*Mem*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{932,22},{932,33}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{932,11},{932,41}});
            // Dir.CurrData := Procs[Home].L2.Data;
            // Dir.State := Shrd;
            ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{934,11},{934,28}});
          } else {
            if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{936,8},{936,19}})).get</*L2*/9>()).get</*Dirty*/3>()) == (false)) {
              // GUniMsg[aux].Cmd := IACK;
              ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{937,13},{937,25}})).get</*Cmd*/0>()), (IACK), ::romp::location{{937,13},{937,37}});
            } else {
              // GUniMsg[aux].Cmd := IACKX;
              ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{939,13},{939,25}})).get</*Cmd*/0>()), (IACKX), ::romp::location{{939,13},{939,38}});
            }
            // Dir.HeadPtr := aux;
            ::romp::Assignment<Procss>(((Dir).get</*HeadPtr*/6>()), (aux), ::romp::location{{941,11},{941,29}});
            // Dir.isLocal := false;
            ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (false), ::romp::location{{942,11},{942,31}});
          }
          // GUniMsg[aux].Data := Procs[Home].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{944,9},{944,21}})).get</*Data*/3>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{944,30},{944,41}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{944,9},{944,49}});
          // Undefine GUniMsg[aux].Cluster;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{945,18},{945,30}})).get</*Cluster*/1>())).Undefine();
          // GUniMsg[aux].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{946,9},{946,21}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{946,9},{946,33}});
          if ((isGet) == (true)) {
            // Procs[Home].L2.State := Shrd;
            ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{949,11},{949,22}})).get</*L2*/9>()).get</*State*/0>()), (Shrd), ::romp::location{{949,11},{949,39}});
            // Procs[Home].L2.OnlyCopy := false;
            ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{950,11},{950,22}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{950,11},{950,43}});
            // Procs[Home].L2.Dirty := false;
            ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{951,11},{951,22}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{951,11},{951,40}});
          } else {
            // Procs[Home].L2.State := Invld;
            ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{954,4},{954,15}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{954,4},{954,33}});
            // Procs[Home].L2.OnlyCopy := false;
            ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{955,11},{955,22}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{955,11},{955,43}});
            // Procs[Home].L2.Dirty := false;
            ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{956,11},{956,22}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{956,11},{956,40}});
            // Undefine Procs[Home].L2.HeadPtr;
            ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{957,20},{957,31}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
            // Undefine Procs[Home].L2.Data;
            ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{958,20},{958,31}})).get</*L2*/9>()).get</*Data*/1>())).Undefine();
            // Undefine Procs[Home].CurrData;
            (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{959,20},{959,31}})).get</*CurrData*/0>())).Undefine();
            // Undefine Procs[Home].PrevData;
            (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{960,20},{960,31}})).get</*PrevData*/1>())).Undefine();
          }
        } else {
          // impossible to this branch?
          if (this->__rw__->assertion_handler((false),22u)) throw ::romp::ModelPropertyError(22);

          // GUniMsg[aux].Cmd := NAK;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{966,9},{966,21}})).get</*Cmd*/0>()), (NAK), ::romp::location{{966,9},{966,32}});
          // Undefine GUniMsg[aux].Data;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{967,18},{967,30}})).get</*Data*/3>())).Undefine();
          // Undefine GUniMsg[aux].InvCnt;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{968,18},{968,30}})).get</*InvCnt*/2>())).Undefine();
          // Undefine GUniMsg[aux].Cluster;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{969,18},{969,30}})).get</*Cluster*/1>())).Undefine();
        }
        // Undefine Procs[Home].L2.ReqCluster;
        ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{971,16},{971,27}})).get</*L2*/9>()).get</*ReqCluster*/9>())).Undefine();
        // Undefine Procs[Home].L2.ReqType;
        ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{972,16},{972,27}})).get</*L2*/9>()).get</*ReqType*/10>())).Undefine();
      } else {
        if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{975,11},{975,22}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{975,36},{975,47}})).get</*NakcMsg*/8>()).get</*Proc*/1>())) {
          // Procs[Home].L2.HeadPtr := L2;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{976,9},{976,20}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (L2), ::romp::location{{976,9},{976,37}});
        }
      }
      // Undefine Procs[Home].NakcMsg;
      (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{980,14},{980,25}})).get</*NakcMsg*/8>())).Undefine();
      // Procs[Home].NakcMsg.Cmd := NAKC_None;
      ::romp::Assignment<NAKC_CMD>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{981,5},{981,16}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()), (NAKC_None), ::romp::location{{981,5},{981,41}});
    } catch (...) { throw ::romp::ModelRuleError(15,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L1Rmt_Recv_Get_Put(const Procss p, const NODE dst, const NODE_L2 src) const {
    try {
      return (((((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{988,5},{988,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{988,5},{988,25}})).get</*Cmd*/0>()) == (UNI_Get)) && (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{989,5},{989,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{989,5},{989,25}})).get</*Proc*/1>()) == (dst))) && ((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{991,6},{991,14}})).get</*Proc*/3>()), (dst), ::romp::location{{991,6},{991,24}})).get</*CacheState*/2>()) == (CACHE_E)) || (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{992,6},{992,14}})).get</*Proc*/3>()), (dst), ::romp::location{{992,6},{992,24}})).get</*CacheState*/2>()) == (CACHE_M))));
    } catch (...) { throw ::romp::ModelRuleError(16,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1Rmt_Recv_Get_Put(const Procss p, const NODE dst, const NODE_L2 src) {
    try {
      if (this->__rw__->assertion_handler(((src) != (dst)),23u)) throw ::romp::ModelPropertyError(23);

      // Procs[p].ShWbMsg.Cmd := SHWB_ShWb;
      ::romp::Assignment<SHWB_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{997,5},{997,13}})).get</*ShWbMsg*/7>()).get</*Cmd*/0>()), (SHWB_ShWb), ::romp::location{{997,5},{997,38}});
      // Procs[p].ShWbMsg.Proc := dst;
      ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{998,5},{998,13}})).get</*ShWbMsg*/7>()).get</*Proc*/1>()), (dst), ::romp::location{{998,5},{998,33}});
      // Procs[p].ShWbMsg.Aux := src;
      ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{999,5},{999,13}})).get</*ShWbMsg*/7>()).get</*Aux*/3>()), (src), ::romp::location{{999,5},{999,32}});
      if (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1000,9},{1000,17}})).get</*Proc*/3>()), (dst), ::romp::location{{1000,9},{1000,27}})).get</*CacheState*/2>()) == (CACHE_E)) {
        // Undefine Procs[p].ShWbMsg.Data;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1001,16},{1001,24}})).get</*ShWbMsg*/7>()).get</*Data*/2>())).Undefine();
      } else {
        // Procs[p].ShWbMsg.Data := Procs[p].Proc[dst].CacheData;
        ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1003,7},{1003,15}})).get</*ShWbMsg*/7>()).get</*Data*/2>()), ((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1003,32},{1003,40}})).get</*Proc*/3>()), (dst), ::romp::location{{1003,32},{1003,50}})).get</*CacheData*/3>()), ::romp::location{{1003,7},{1003,60}});
      }
      // Undefine Procs[p].UniMsg[src];
      ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1005,14},{1005,22}})).get</*UniMsg*/4>()), (src), ::romp::location{{1005,14},{1005,34}}))).Undefine();
      // Procs[p].UniMsg[src].Cmd := UNI_None;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1006,5},{1006,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{1006,5},{1006,25}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{1006,5},{1006,41}});
      if ((src) != (L2)) {
        // Procs[p].UniMsg[src].Cmd := UNI_Put;
        ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1009,7},{1009,15}})).get</*UniMsg*/4>()), (src), ::romp::location{{1009,7},{1009,27}})).get</*Cmd*/0>()), (UNI_Put), ::romp::location{{1009,7},{1009,42}});
        // Procs[p].UniMsg[src].Data := Procs[p].Proc[dst].CacheData;
        ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1010,7},{1010,15}})).get</*UniMsg*/4>()), (src), ::romp::location{{1010,7},{1010,27}})).get</*Data*/2>()), ((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1010,36},{1010,44}})).get</*Proc*/3>()), (dst), ::romp::location{{1010,36},{1010,54}})).get</*CacheData*/3>()), ::romp::location{{1010,7},{1010,64}});
        // Undefine Procs[p].UniMsg[src].Proc;
        (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1011,16},{1011,24}})).get</*UniMsg*/4>()), (src), ::romp::location{{1011,16},{1011,36}})).get</*Proc*/1>())).Undefine();
      }
      // Procs[p].Proc[dst].CacheState := CACHE_S;
      ::romp::Assignment<CACHE_STATE>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1014,5},{1014,13}})).get</*Proc*/3>()), (dst), ::romp::location{{1014,5},{1014,23}})).get</*CacheState*/2>()), (CACHE_S), ::romp::location{{1014,5},{1014,45}});
    } catch (...) { throw ::romp::ModelRuleError(16,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L2_Recv_SHWB(const Procss p) const {
    try {
      return ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1023,5},{1023,13}})).get</*ShWbMsg*/7>()).get</*Cmd*/0>()) == (SHWB_ShWb));
    } catch (...) { throw ::romp::ModelRuleError(17,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2_Recv_SHWB(const Procss p) {
    try {
      NODE_L2 src;
      NODE_L2 dst;
      Procss aux;
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1030,13},{1030,21}})).get</*L2*/9>()).get</*pending*/2>()) == (true)),24u)) throw ::romp::ModelPropertyError(24);

      // Procs[p].L2.pending := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1032,5},{1032,13}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{1032,5},{1032,33}});
      // Procs[p].L2.State := Shrd;
      ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1033,5},{1033,13}})).get</*L2*/9>()).get</*State*/0>()), (Shrd), ::romp::location{{1033,5},{1033,30}});
      // src := Procs[p].ShWbMsg.Aux;
      ::romp::Assignment<NODE_L2>((src), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1034,12},{1034,20}})).get</*ShWbMsg*/7>()).get</*Aux*/3>()), ::romp::location{{1034,5},{1034,32}});
      // dst := Procs[p].ShWbMsg.Proc;
      ::romp::Assignment<NODE_L2>((dst), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1035,12},{1035,20}})).get</*ShWbMsg*/7>()).get</*Proc*/1>()), ::romp::location{{1035,5},{1035,33}});
      if ((src) != (L2)) {
        if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1038,15},{1038,23}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (dst)),25u)) throw ::romp::ModelPropertyError(25);

        // Procs[p].L2.ShrSet[dst] := true;
        ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1039,7},{1039,15}})).get</*L2*/9>()).get</*ShrSet*/4>()), (dst), ::romp::location{{1039,7},{1039,30}})), (true), ::romp::location{{1039,7},{1039,38}});
        // Procs[p].L2.ShrSet[src] := true;
        ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1040,7},{1040,15}})).get</*L2*/9>()).get</*ShrSet*/4>()), (src), ::romp::location{{1040,7},{1040,30}})), (true), ::romp::location{{1040,7},{1040,38}});
        // Undefine Procs[p].L2.HeadPtr;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1041,16},{1041,24}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
        if ((!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1042,24},{1042,32}})).get</*ShWbMsg*/7>()).get</*Data*/2>()).IsUndefined()))) {
          // Procs[p].L2.Dirty := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1043,9},{1043,17}})).get</*L2*/9>()).get</*Dirty*/3>()), (true), ::romp::location{{1043,9},{1043,34}});
          // Procs[p].L2.Data := Procs[p].ShWbMsg.Data;
          ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1044,9},{1044,17}})).get</*L2*/9>()).get</*Data*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1044,29},{1044,37}})).get</*ShWbMsg*/7>()).get</*Data*/2>()), ::romp::location{{1044,9},{1044,50}});
          // Dir.CurrData := Procs[p].ShWbMsg.Data;
          ::romp::Assignment<Datas>(((Dir).get</*CurrData*/8>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1045,25},{1045,33}})).get</*ShWbMsg*/7>()).get</*Data*/2>()), ::romp::location{{1045,9},{1045,46}});
        }
      } else {
        // Procs[p].L2.ShrSet[dst] := true;
        ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1049,7},{1049,15}})).get</*L2*/9>()).get</*ShrSet*/4>()), (dst), ::romp::location{{1049,7},{1049,30}})), (true), ::romp::location{{1049,7},{1049,38}});
        if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1050,15},{1050,23}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (dst)),26u)) throw ::romp::ModelPropertyError(26);

        // Undefine Procs[p].L2.HeadPtr;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1051,16},{1051,24}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
        // Procs[p].L2.Dirty := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1053,7},{1053,15}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{1053,7},{1053,33}});
        // Procs[p].L2.OnlyCopy := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1054,7},{1054,15}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{1054,7},{1054,36}});
        if ((!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1055,24},{1055,32}})).get</*ShWbMsg*/7>()).get</*Data*/2>()).IsUndefined()))) {
          // Procs[p].L2.Data := Procs[p].ShWbMsg.Data;
          ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1056,9},{1056,17}})).get</*L2*/9>()).get</*Data*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1056,29},{1056,37}})).get</*ShWbMsg*/7>()).get</*Data*/2>()), ::romp::location{{1056,9},{1056,50}});
          // Dir.CurrData := Procs[p].ShWbMsg.Data;
          ::romp::Assignment<Datas>(((Dir).get</*CurrData*/8>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1057,25},{1057,33}})).get</*ShWbMsg*/7>()).get</*Data*/2>()), ::romp::location{{1057,9},{1057,46}});
        }
        if (this->__rw__->assertion_handler((!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1060,28},{1060,36}})).get</*L2*/9>()).get</*ReqCluster*/9>()).IsUndefined())),27u)) throw ::romp::ModelPropertyError(27);

        // aux := Procs[p].L2.ReqCluster;
        ::romp::Assignment<Procss>((aux), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1061,14},{1061,22}})).get</*L2*/9>()).get</*ReqCluster*/9>()), ::romp::location{{1061,7},{1061,36}});
        if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1062,15},{1062,23}})).get</*L2*/9>()).get</*ReqType*/10>()) == (true)),28u)) throw ::romp::ModelPropertyError(28);

        // Apr 8
        if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1066,15},{1066,23}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()) == (true)),29u)) throw ::romp::ModelPropertyError(29);

        // Procs[p].L2.ifHoldMsg := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1067,7},{1067,15}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()), (false), ::romp::location{{1067,7},{1067,37}});
        if ((p) == (Home)) {
          if (this->__rw__->assertion_handler((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1069,19},{1069,31}})).get</*Cmd*/0>()) == (RD_H)),30u)) throw ::romp::ModelPropertyError(30);

        } else {
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1071,19},{1071,31}})).get</*Cmd*/0>()) == (RD_RAC)) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1071,47},{1071,59}})).get</*Cluster*/1>()) == (p))),31u)) throw ::romp::ModelPropertyError(31);

        }
        // GUniMsg[aux].Cmd := ACK;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1076,7},{1076,19}})).get</*Cmd*/0>()), (ACK), ::romp::location{{1076,7},{1076,30}});
        // GUniMsg[aux].Data := Procs[p].L2.Data;
        ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1077,7},{1077,19}})).get</*Data*/3>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1077,28},{1077,36}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1077,7},{1077,44}});
        // GUniMsg[aux].Cluster := p;
        ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1078,7},{1078,19}})).get</*Cluster*/1>()), (p), ::romp::location{{1078,7},{1078,32}});
        // GUniMsg[aux].InvCnt := 0;
        ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1079,7},{1079,19}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{1079,7},{1079,31}});
        if ((p) == (Home)) {
          // Dir.State := Shrd;
          ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{1082,9},{1082,26}});
          // Dir.ShrSet[aux] := true;
          ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (aux), ::romp::location{{1083,9},{1083,24}})), (true), ::romp::location{{1083,9},{1083,32}});
          // Dir.Mem := Procs[p].L2.Data;
          ::romp::Assignment<Datas>(((Dir).get</*Mem*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1084,20},{1084,28}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1084,9},{1084,36}});
          // Dir.CurrData := Procs[p].L2.Data;
          ::romp::Assignment<Datas>(((Dir).get</*CurrData*/8>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1085,25},{1085,33}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1085,9},{1085,41}});
        } else {
          if ((aux) != (Home)) {
            // GShWbMsg.Cmd := SHWB;
            ::romp::Assignment<GSHWB_CMD>(((GShWbMsg).get</*Cmd*/0>()), (SHWB), ::romp::location{{1089,11},{1089,31}});
            // GShWbMsg.Data := Procs[p].L2.Data;
            ::romp::Assignment<Datas>(((GShWbMsg).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1090,28},{1090,36}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1090,11},{1090,44}});
            // GShWbMsg.Cluster := aux;
            ::romp::Assignment<Procss>(((GShWbMsg).get</*Cluster*/1>()), (aux), ::romp::location{{1091,11},{1091,34}});
          }
        }
        // Undefine Procs[p].L2.ReqCluster;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1094,16},{1094,24}})).get</*L2*/9>()).get</*ReqCluster*/9>())).Undefine();
        // Undefine Procs[p].L2.ReqType;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1095,16},{1095,24}})).get</*L2*/9>()).get</*ReqType*/10>())).Undefine();
      }
      // Undefine Procs[p].ShWbMsg;
      (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1098,14},{1098,22}})).get</*ShWbMsg*/7>())).Undefine();
      // Procs[p].ShWbMsg.Cmd := SHWB_None;
      ::romp::Assignment<SHWB_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1099,5},{1099,13}})).get</*ShWbMsg*/7>()).get</*Cmd*/0>()), (SHWB_None), ::romp::location{{1099,5},{1099,38}});
    } catch (...) { throw ::romp::ModelRuleError(17,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX(const Procss p, const NODE dst, const NODE_L2 src) const {
    try {
      return (((((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1108,3},{1108,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{1108,3},{1108,23}})).get</*Cmd*/0>()) == (UNI_GetX)) && (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1109,3},{1109,11}})).get</*UniMsg*/4>()), (src), ::romp::location{{1109,3},{1109,23}})).get</*Proc*/1>()) == (dst))) && ((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1111,4},{1111,12}})).get</*Proc*/3>()), (dst), ::romp::location{{1111,4},{1111,22}})).get</*CacheState*/2>()) == (CACHE_E)) || (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1112,4},{1112,12}})).get</*Proc*/3>()), (dst), ::romp::location{{1112,4},{1112,22}})).get</*CacheState*/2>()) == (CACHE_M))));
    } catch (...) { throw ::romp::ModelRuleError(18,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1Rmt_Recv_GetX_PutX(const Procss p, const NODE dst, const NODE_L2 src) {
    try {
      if ((src) == (L2)) {
        // Procs[p].ShWbMsg.Cmd := SHWB_FAck;
        ::romp::Assignment<SHWB_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1116,5},{1116,13}})).get</*ShWbMsg*/7>()).get</*Cmd*/0>()), (SHWB_FAck), ::romp::location{{1116,5},{1116,38}});
        // Procs[p].ShWbMsg.Proc := dst;
        ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1117,5},{1117,13}})).get</*ShWbMsg*/7>()).get</*Proc*/1>()), (dst), ::romp::location{{1117,5},{1117,33}});
        // Procs[p].ShWbMsg.Aux := src;
        ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1118,5},{1118,13}})).get</*ShWbMsg*/7>()).get</*Aux*/3>()), (src), ::romp::location{{1118,5},{1118,32}});
        if (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1119,9},{1119,17}})).get</*Proc*/3>()), (dst), ::romp::location{{1119,9},{1119,27}})).get</*CacheState*/2>()) == (CACHE_E)) {
          // Undefine Procs[p].ShWbMsg.Data;
          ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1120,16},{1120,24}})).get</*ShWbMsg*/7>()).get</*Data*/2>())).Undefine();
        } else {
          // Procs[p].ShWbMsg.Data := Procs[p].Proc[dst].CacheData;
          ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1122,7},{1122,15}})).get</*ShWbMsg*/7>()).get</*Data*/2>()), ((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1122,32},{1122,40}})).get</*Proc*/3>()), (dst), ::romp::location{{1122,32},{1122,50}})).get</*CacheData*/3>()), ::romp::location{{1122,7},{1122,60}});
        }
        // Undefine Procs[p].UniMsg[src];
        ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1124,14},{1124,22}})).get</*UniMsg*/4>()), (src), ::romp::location{{1124,14},{1124,34}}))).Undefine();
        // Procs[p].UniMsg[src].Cmd := UNI_None;
        ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1125,5},{1125,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{1125,5},{1125,25}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{1125,5},{1125,41}});
      } else {
        // Procs[p].UniMsg[src].Data := Procs[p].Proc[dst].CacheData;
        ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1128,5},{1128,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{1128,5},{1128,25}})).get</*Data*/2>()), ((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1128,34},{1128,42}})).get</*Proc*/3>()), (dst), ::romp::location{{1128,34},{1128,52}})).get</*CacheData*/3>()), ::romp::location{{1128,5},{1128,62}});
        // Undefine Procs[p].UniMsg[src].Proc;
        (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1129,14},{1129,22}})).get</*UniMsg*/4>()), (src), ::romp::location{{1129,14},{1129,34}})).get</*Proc*/1>())).Undefine();
        if (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1130,9},{1130,17}})).get</*Proc*/3>()), (dst), ::romp::location{{1130,9},{1130,27}})).get</*CacheState*/2>()) == (CACHE_E)) {
          // Procs[p].UniMsg[src].Cmd := UNI_PutX;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1131,7},{1131,15}})).get</*UniMsg*/4>()), (src), ::romp::location{{1131,7},{1131,27}})).get</*Cmd*/0>()), (UNI_PutX), ::romp::location{{1131,7},{1131,43}});
        } else {
          // Procs[p].UniMsg[src].Cmd := UNI_PutXX;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1133,7},{1133,15}})).get</*UniMsg*/4>()), (src), ::romp::location{{1133,7},{1133,27}})).get</*Cmd*/0>()), (UNI_PutXX), ::romp::location{{1133,7},{1133,44}});
        }
        // Procs[p].ShWbMsg.Cmd := SHWB_FAck;
        ::romp::Assignment<SHWB_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1135,5},{1135,13}})).get</*ShWbMsg*/7>()).get</*Cmd*/0>()), (SHWB_FAck), ::romp::location{{1135,5},{1135,38}});
        // Procs[p].ShWbMsg.Proc := dst;
        ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1136,5},{1136,13}})).get</*ShWbMsg*/7>()).get</*Proc*/1>()), (dst), ::romp::location{{1136,5},{1136,33}});
        // Procs[p].ShWbMsg.Aux := src;
        ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1137,5},{1137,13}})).get</*ShWbMsg*/7>()).get</*Aux*/3>()), (src), ::romp::location{{1137,5},{1137,32}});
        // Undefine Procs[p].ShWbMsg.Data;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1138,14},{1138,22}})).get</*ShWbMsg*/7>()).get</*Data*/2>())).Undefine();
      }
      // Procs[p].Proc[dst].CacheState := CACHE_I;
      ::romp::Assignment<CACHE_STATE>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1141,3},{1141,11}})).get</*Proc*/3>()), (dst), ::romp::location{{1141,3},{1141,21}})).get</*CacheState*/2>()), (CACHE_I), ::romp::location{{1141,3},{1141,43}});
      // Undefine Procs[p].Proc[dst].CacheData;
      (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1142,12},{1142,20}})).get</*Proc*/3>()), (dst), ::romp::location{{1142,12},{1142,30}})).get</*CacheData*/3>())).Undefine();
    } catch (...) { throw ::romp::ModelRuleError(18,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L2_Recv_SHWB_FAck(const Procss p) const {
    try {
      return ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1151,3},{1151,11}})).get</*ShWbMsg*/7>()).get</*Cmd*/0>()) == (SHWB_FAck));
    } catch (...) { throw ::romp::ModelRuleError(19,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2_Recv_SHWB_FAck(const Procss p) {
    try {
      NODE_L2 src;
      NODE_L2 dst;
      Procss aux;
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1158,11},{1158,19}})).get</*L2*/9>()).get</*pending*/2>()) == (true)),32u)) throw ::romp::ModelPropertyError(32);

      // Procs[p].L2.pending := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1159,3},{1159,11}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{1159,3},{1159,31}});
      // src := Procs[p].ShWbMsg.Aux;
      ::romp::Assignment<NODE_L2>((src), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1161,10},{1161,18}})).get</*ShWbMsg*/7>()).get</*Aux*/3>()), ::romp::location{{1161,3},{1161,30}});
      // dst := Procs[p].ShWbMsg.Proc;
      ::romp::Assignment<NODE_L2>((dst), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1162,10},{1162,18}})).get</*ShWbMsg*/7>()).get</*Proc*/1>()), ::romp::location{{1162,3},{1162,31}});
      if ((src) == (L2)) {
        if (this->__rw__->assertion_handler((!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1165,26},{1165,34}})).get</*L2*/9>()).get</*ReqCluster*/9>()).IsUndefined())),33u)) throw ::romp::ModelPropertyError(33);

        // aux := Procs[p].L2.ReqCluster;
        ::romp::Assignment<Procss>((aux), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1166,12},{1166,20}})).get</*L2*/9>()).get</*ReqCluster*/9>()), ::romp::location{{1166,5},{1166,34}});
        if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1167,13},{1167,21}})).get</*L2*/9>()).get</*ReqType*/10>()) == (false)),34u)) throw ::romp::ModelPropertyError(34);

        // Apr 8
        if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1172,15},{1172,23}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()) == (true)),35u)) throw ::romp::ModelPropertyError(35);

        // Procs[p].L2.ifHoldMsg := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1173,7},{1173,15}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()), (false), ::romp::location{{1173,7},{1173,37}});
        if ((p) == (Home)) {
          if (this->__rw__->assertion_handler((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1175,19},{1175,31}})).get</*Cmd*/0>()) == (RDX_H)),36u)) throw ::romp::ModelPropertyError(36);

        } else {
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1177,19},{1177,31}})).get</*Cmd*/0>()) == (RDX_RAC)) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1177,48},{1177,60}})).get</*Cluster*/1>()) == (p))),37u)) throw ::romp::ModelPropertyError(37);

        }
        if ((!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1183,22},{1183,30}})).get</*ShWbMsg*/7>()).get</*Data*/2>()).IsUndefined()))) {
          // Procs[p].L2.Data := Procs[p].ShWbMsg.Data;
          ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1184,7},{1184,15}})).get</*L2*/9>()).get</*Data*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1184,27},{1184,35}})).get</*ShWbMsg*/7>()).get</*Data*/2>()), ::romp::location{{1184,7},{1184,48}});
          // Dir.CurrData := Procs[p].ShWbMsg.Data;
          ::romp::Assignment<Datas>(((Dir).get</*CurrData*/8>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1185,23},{1185,31}})).get</*ShWbMsg*/7>()).get</*Data*/2>()), ::romp::location{{1185,7},{1185,44}});
        }
        if ((p) == (Home)) {
          // Dir.isLocal := false;
          ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (false), ::romp::location{{1189,7},{1189,27}});
          // Dir.HeadPtr := aux;
          ::romp::Assignment<Procss>(((Dir).get</*HeadPtr*/6>()), (aux), ::romp::location{{1190,7},{1190,25}});
        } else {
          if ((aux) != (Home)) {
            // GShWbMsg.Cmd := DXFER;
            ::romp::Assignment<GSHWB_CMD>(((GShWbMsg).get</*Cmd*/0>()), (DXFER), ::romp::location{{1194,9},{1194,30}});
            // GShWbMsg.Cluster := aux;
            ::romp::Assignment<Procss>(((GShWbMsg).get</*Cluster*/1>()), (aux), ::romp::location{{1195,9},{1195,32}});
            // Undefine GShWbMsg.Data;
            (((GShWbMsg).get</*Data*/2>())).Undefine();
          }
        }
        // GUniMsg[aux].Data := Procs[p].L2.Data;
        ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1201,5},{1201,17}})).get</*Data*/3>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1201,26},{1201,34}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1201,5},{1201,42}});
        // GUniMsg[aux].Cluster := p;
        ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1202,5},{1202,17}})).get</*Cluster*/1>()), (p), ::romp::location{{1202,5},{1202,30}});
        // GUniMsg[aux].InvCnt := 0;
        ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1203,5},{1203,17}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{1203,5},{1203,29}});
        if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1204,9},{1204,17}})).get</*L2*/9>()).get</*Dirty*/3>()) == (true)) {
          // GUniMsg[aux].Cmd := IACKX;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1205,7},{1205,19}})).get</*Cmd*/0>()), (IACKX), ::romp::location{{1205,7},{1205,32}});
        } else if ((!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1206,25},{1206,33}})).get</*ShWbMsg*/7>()).get</*Data*/2>()).IsUndefined()))) {
          // GUniMsg[aux].Cmd := IACKX;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1207,7},{1207,19}})).get</*Cmd*/0>()), (IACKX), ::romp::location{{1207,7},{1207,32}});
        } else {
          // GUniMsg[aux].Cmd := IACK;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (aux), ::romp::location{{1209,7},{1209,19}})).get</*Cmd*/0>()), (IACK), ::romp::location{{1209,7},{1209,31}});
        }
        // Procs[p].L2.State := Invld;
        ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1212,5},{1212,13}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{1212,5},{1212,31}});
        // Procs[p].L2.OnlyCopy := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1213,5},{1213,13}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{1213,5},{1213,34}});
        // Procs[p].L2.Dirty := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1214,5},{1214,13}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{1214,5},{1214,31}});
        // Undefine Procs[p].CurrData;
        (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1215,14},{1215,22}})).get</*CurrData*/0>())).Undefine();
        // Undefine Procs[p].PrevData;
        (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1216,14},{1216,22}})).get</*PrevData*/1>())).Undefine();
        // Undefine Procs[p].L2.Data;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1217,14},{1217,22}})).get</*L2*/9>()).get</*Data*/1>())).Undefine();
        // Undefine Procs[p].L2.HeadPtr;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1218,14},{1218,22}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
        // Undefine Procs[p].L2.ReqCluster;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1220,14},{1220,22}})).get</*L2*/9>()).get</*ReqCluster*/9>())).Undefine();
        // Undefine Procs[p].L2.ReqType;
        ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1221,14},{1221,22}})).get</*L2*/9>()).get</*ReqType*/10>())).Undefine();
      } else {
        if ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1224,9},{1224,17}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (dst)) {
          // Procs[p].L2.HeadPtr := src;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1225,7},{1225,15}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (src), ::romp::location{{1225,7},{1225,33}});
        }
      }
      // Undefine Procs[p].ShWbMsg;
      (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1229,12},{1229,20}})).get</*ShWbMsg*/7>())).Undefine();
      // Procs[p].ShWbMsg.Cmd := SHWB_None;
      ::romp::Assignment<SHWB_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1230,3},{1230,11}})).get</*ShWbMsg*/7>()).get</*Cmd*/0>()), (SHWB_None), ::romp::location{{1230,3},{1230,36}});
    } catch (...) { throw ::romp::ModelRuleError(19,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L1_Recv_Nak(const Procss p, const NODE dst) const {
    try {
      return (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1238,5},{1238,13}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1238,5},{1238,25}})).get</*Cmd*/0>()) == (UNI_Nak));
    } catch (...) { throw ::romp::ModelRuleError(20,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1_Recv_Nak(const Procss p, const NODE dst) {
    try {
      // Procs[p].Proc[dst].ProcCmd := NODE_None;
      ::romp::Assignment<NODE_CMD>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1241,5},{1241,13}})).get</*Proc*/3>()), (dst), ::romp::location{{1241,5},{1241,23}})).get</*ProcCmd*/0>()), (NODE_None), ::romp::location{{1241,5},{1241,44}});
      // Procs[p].Proc[dst].InvMarked := false;
      ::romp::Assignment<boolean>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1242,5},{1242,13}})).get</*Proc*/3>()), (dst), ::romp::location{{1242,5},{1242,23}})).get</*InvMarked*/1>()), (false), ::romp::location{{1242,5},{1242,42}});
      // Undefine Procs[p].UniMsg[dst];
      ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1243,14},{1243,22}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1243,14},{1243,34}}))).Undefine();
      // Procs[p].UniMsg[dst].Cmd := UNI_None;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1244,5},{1244,13}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1244,5},{1244,25}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{1244,5},{1244,41}});
    } catch (...) { throw ::romp::ModelRuleError(20,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L1_Recv_Put(const Procss p, const NODE dst) const {
    try {
      return (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1252,5},{1252,13}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1252,5},{1252,25}})).get</*Cmd*/0>()) == (UNI_Put));
    } catch (...) { throw ::romp::ModelRuleError(21,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1_Recv_Put(const Procss p, const NODE dst) {
    try {
      if (this->__rw__->assertion_handler((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1256,13},{1256,21}})).get</*Proc*/3>()), (dst), ::romp::location{{1256,13},{1256,31}})).get</*ProcCmd*/0>()) == (NODE_Get)),38u)) throw ::romp::ModelPropertyError(38);

      // Procs[p].Proc[dst].ProcCmd := NODE_None;
      ::romp::Assignment<NODE_CMD>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1258,5},{1258,13}})).get</*Proc*/3>()), (dst), ::romp::location{{1258,5},{1258,23}})).get</*ProcCmd*/0>()), (NODE_None), ::romp::location{{1258,5},{1258,44}});
      if (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1259,9},{1259,17}})).get</*Proc*/3>()), (dst), ::romp::location{{1259,9},{1259,27}})).get</*InvMarked*/1>()) == (true)) {
        // Procs[p].Proc[dst].CacheState := CACHE_I;
        ::romp::Assignment<CACHE_STATE>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1260,7},{1260,15}})).get</*Proc*/3>()), (dst), ::romp::location{{1260,7},{1260,25}})).get</*CacheState*/2>()), (CACHE_I), ::romp::location{{1260,7},{1260,47}});
        // Undefine Procs[p].Proc[dst].CacheData;
        (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1261,16},{1261,24}})).get</*Proc*/3>()), (dst), ::romp::location{{1261,16},{1261,34}})).get</*CacheData*/3>())).Undefine();
        // Procs[p].Proc[dst].InvMarked := false;
        ::romp::Assignment<boolean>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1262,7},{1262,15}})).get</*Proc*/3>()), (dst), ::romp::location{{1262,7},{1262,25}})).get</*InvMarked*/1>()), (false), ::romp::location{{1262,7},{1262,44}});
      } else {
        // Procs[p].Proc[dst].CacheState := CACHE_S;
        ::romp::Assignment<CACHE_STATE>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1264,7},{1264,15}})).get</*Proc*/3>()), (dst), ::romp::location{{1264,7},{1264,25}})).get</*CacheState*/2>()), (CACHE_S), ::romp::location{{1264,7},{1264,47}});
        if (this->__rw__->assertion_handler((!(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1265,29},{1265,37}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1265,29},{1265,49}})).get</*Data*/2>()).IsUndefined())),39u)) throw ::romp::ModelPropertyError(39);

        // Procs[p].Proc[dst].CacheData := Procs[p].UniMsg[dst].Data;
        ::romp::Assignment<Datas>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1266,7},{1266,15}})).get</*Proc*/3>()), (dst), ::romp::location{{1266,7},{1266,25}})).get</*CacheData*/3>()), ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1266,39},{1266,47}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1266,39},{1266,59}})).get</*Data*/2>()), ::romp::location{{1266,7},{1266,64}});
      }
      // Undefine Procs[p].UniMsg[dst];
      ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1268,14},{1268,22}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1268,14},{1268,34}}))).Undefine();
      // Procs[p].UniMsg[dst].Cmd := UNI_None;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1269,5},{1269,13}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1269,5},{1269,25}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{1269,5},{1269,41}});
    } catch (...) { throw ::romp::ModelRuleError(21,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L1_Recv_PutX(const Procss p, const NODE dst) const {
    try {
      return (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1278,5},{1278,13}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1278,5},{1278,25}})).get</*Cmd*/0>()) == (UNI_PutX));
    } catch (...) { throw ::romp::ModelRuleError(22,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1_Recv_PutX(const Procss p, const NODE dst) {
    try {
      if (this->__rw__->assertion_handler((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1281,13},{1281,21}})).get</*Proc*/3>()), (dst), ::romp::location{{1281,13},{1281,31}})).get</*ProcCmd*/0>()) == (NODE_GetX)),40u)) throw ::romp::ModelPropertyError(40);

      // Procs[p].Proc[dst].ProcCmd := NODE_None;
      ::romp::Assignment<NODE_CMD>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1282,5},{1282,13}})).get</*Proc*/3>()), (dst), ::romp::location{{1282,5},{1282,23}})).get</*ProcCmd*/0>()), (NODE_None), ::romp::location{{1282,5},{1282,44}});
      // Procs[p].Proc[dst].CacheState := CACHE_E;
      ::romp::Assignment<CACHE_STATE>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1283,5},{1283,13}})).get</*Proc*/3>()), (dst), ::romp::location{{1283,5},{1283,23}})).get</*CacheState*/2>()), (CACHE_E), ::romp::location{{1283,5},{1283,45}});
      if (this->__rw__->assertion_handler((!(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1284,27},{1284,35}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1284,27},{1284,47}})).get</*Data*/2>()).IsUndefined())),41u)) throw ::romp::ModelPropertyError(41);

      // Procs[p].Proc[dst].CacheData := Procs[p].UniMsg[dst].Data;
      ::romp::Assignment<Datas>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1285,5},{1285,13}})).get</*Proc*/3>()), (dst), ::romp::location{{1285,5},{1285,23}})).get</*CacheData*/3>()), ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1285,37},{1285,45}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1285,37},{1285,57}})).get</*Data*/2>()), ::romp::location{{1285,5},{1285,62}});
      // Undefine Procs[p].UniMsg[dst];
      ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1287,14},{1287,22}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1287,14},{1287,34}}))).Undefine();
      // Procs[p].UniMsg[dst].Cmd := UNI_None;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1288,5},{1288,13}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1288,5},{1288,25}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{1288,5},{1288,41}});
    } catch (...) { throw ::romp::ModelRuleError(22,::romp::ModelRuleError::ACTION); }
  }

  // dirty excl owner transfer
  
  bool __romp__Rule_guard__L1_Recv_PutXX(const Procss p, const NODE dst) const {
    try {
      return (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1297,5},{1297,13}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1297,5},{1297,25}})).get</*Cmd*/0>()) == (UNI_PutXX));
    } catch (...) { throw ::romp::ModelRuleError(23,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1_Recv_PutXX(const Procss p, const NODE dst) {
    try {
      if (this->__rw__->assertion_handler((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1300,13},{1300,21}})).get</*Proc*/3>()), (dst), ::romp::location{{1300,13},{1300,31}})).get</*ProcCmd*/0>()) == (NODE_GetX)),42u)) throw ::romp::ModelPropertyError(42);

      // Procs[p].Proc[dst].ProcCmd := NODE_None;
      ::romp::Assignment<NODE_CMD>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1301,5},{1301,13}})).get</*Proc*/3>()), (dst), ::romp::location{{1301,5},{1301,23}})).get</*ProcCmd*/0>()), (NODE_None), ::romp::location{{1301,5},{1301,44}});
      // Procs[p].Proc[dst].CacheState := CACHE_M;
      ::romp::Assignment<CACHE_STATE>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1302,5},{1302,13}})).get</*Proc*/3>()), (dst), ::romp::location{{1302,5},{1302,23}})).get</*CacheState*/2>()), (CACHE_M), ::romp::location{{1302,5},{1302,45}});
      if (this->__rw__->assertion_handler((!(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1303,27},{1303,35}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1303,27},{1303,47}})).get</*Data*/2>()).IsUndefined())),43u)) throw ::romp::ModelPropertyError(43);

      // Procs[p].Proc[dst].CacheData := Procs[p].UniMsg[dst].Data;
      ::romp::Assignment<Datas>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1304,5},{1304,13}})).get</*Proc*/3>()), (dst), ::romp::location{{1304,5},{1304,23}})).get</*CacheData*/3>()), ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1304,37},{1304,45}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1304,37},{1304,57}})).get</*Data*/2>()), ::romp::location{{1304,5},{1304,62}});
      // Undefine Procs[p].UniMsg[dst];
      ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1306,14},{1306,22}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1306,14},{1306,34}}))).Undefine();
      // Procs[p].UniMsg[dst].Cmd := UNI_None;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1307,5},{1307,13}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1307,5},{1307,25}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{1307,5},{1307,41}});
    } catch (...) { throw ::romp::ModelRuleError(23,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L1_SilentDrop(const Procss p, const NODE src) const {
    try {
      return ((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1315,3},{1315,11}})).get</*Proc*/3>()), (src), ::romp::location{{1315,3},{1315,21}})).get</*ProcCmd*/0>()) == (NODE_None)) && ((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1316,4},{1316,12}})).get</*Proc*/3>()), (src), ::romp::location{{1316,4},{1316,22}})).get</*CacheState*/2>()) == (CACHE_S)) || (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1317,4},{1317,12}})).get</*Proc*/3>()), (src), ::romp::location{{1317,4},{1317,22}})).get</*CacheState*/2>()) == (CACHE_E))));
    } catch (...) { throw ::romp::ModelRuleError(24,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1_SilentDrop(const Procss p, const NODE src) {
    try {
      // Procs[p].Proc[src].CacheState := CACHE_I;
      ::romp::Assignment<CACHE_STATE>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1320,3},{1320,11}})).get</*Proc*/3>()), (src), ::romp::location{{1320,3},{1320,21}})).get</*CacheState*/2>()), (CACHE_I), ::romp::location{{1320,3},{1320,43}});
      // Undefine Procs[p].Proc[src].CacheData;
      (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1321,12},{1321,20}})).get</*Proc*/3>()), (src), ::romp::location{{1321,12},{1321,30}})).get</*CacheData*/3>())).Undefine();
    } catch (...) { throw ::romp::ModelRuleError(24,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L1_WriteBack(const Procss p, const NODE src) const {
    try {
      return ((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1330,3},{1330,11}})).get</*Proc*/3>()), (src), ::romp::location{{1330,3},{1330,21}})).get</*CacheState*/2>()) == (CACHE_M)) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1331,3},{1331,11}})).get</*Proc*/3>()), (src), ::romp::location{{1331,3},{1331,21}})).get</*ProcCmd*/0>()) == (NODE_None)));
    } catch (...) { throw ::romp::ModelRuleError(25,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1_WriteBack(const Procss p, const NODE src) {
    try {
      // Procs[p].Proc[src].CacheState := CACHE_I;
      ::romp::Assignment<CACHE_STATE>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1334,3},{1334,11}})).get</*Proc*/3>()), (src), ::romp::location{{1334,3},{1334,21}})).get</*CacheState*/2>()), (CACHE_I), ::romp::location{{1334,3},{1334,43}});
      // Procs[p].WbMsg.Cmd := WB_Wb;
      ::romp::Assignment<WB_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1335,3},{1335,11}})).get</*WbMsg*/6>()).get</*Cmd*/0>()), (WB_Wb), ::romp::location{{1335,3},{1335,30}});
      // Procs[p].WbMsg.Proc := src;
      ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1336,3},{1336,11}})).get</*WbMsg*/6>()).get</*Proc*/1>()), (src), ::romp::location{{1336,3},{1336,29}});
      // Procs[p].WbMsg.Data := Procs[p].Proc[src].CacheData;
      ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1337,3},{1337,11}})).get</*WbMsg*/6>()).get</*Data*/2>()), ((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1337,26},{1337,34}})).get</*Proc*/3>()), (src), ::romp::location{{1337,26},{1337,44}})).get</*CacheData*/3>()), ::romp::location{{1337,3},{1337,54}});
      // Undefine Procs[p].Proc[src].CacheData;
      (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1339,12},{1339,20}})).get</*Proc*/3>()), (src), ::romp::location{{1339,12},{1339,30}})).get</*CacheData*/3>())).Undefine();
      // Procs[p].Proc[src].block_WB := true;
      ::romp::Assignment<boolean>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1340,3},{1340,11}})).get</*Proc*/3>()), (src), ::romp::location{{1340,3},{1340,21}})).get</*block_WB*/4>()), (true), ::romp::location{{1340,3},{1340,38}});
    } catch (...) { throw ::romp::ModelRuleError(25,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__L2_Recv_WB_Remain(const Procss p) const {
    try {
      return ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1348,5},{1348,13}})).get</*WbMsg*/6>()).get</*Cmd*/0>()) == (WB_Wb));
    } catch (...) { throw ::romp::ModelRuleError(26,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2_Recv_WB_Remain(const Procss p) {
    try {
      NODE src;
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1352,13},{1352,21}})).get</*L2*/9>()).get</*State*/0>()) == (Excl)),44u)) throw ::romp::ModelPropertyError(44);

      // Procs[p].L2.HeadPtr := L2;
      ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1353,5},{1353,13}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (L2), ::romp::location{{1353,5},{1353,30}});
      // Procs[p].L2.Dirty := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1354,5},{1354,13}})).get</*L2*/9>()).get</*Dirty*/3>()), (true), ::romp::location{{1354,5},{1354,30}});
      // Procs[p].L2.Data := Procs[p].WbMsg.Data;
      ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1355,5},{1355,13}})).get</*L2*/9>()).get</*Data*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1355,25},{1355,33}})).get</*WbMsg*/6>()).get</*Data*/2>()), ::romp::location{{1355,5},{1355,44}});
      // Dir.CurrData := Procs[p].WbMsg.Data;
      ::romp::Assignment<Datas>(((Dir).get</*CurrData*/8>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1356,21},{1356,29}})).get</*WbMsg*/6>()).get</*Data*/2>()), ::romp::location{{1356,5},{1356,40}});
      // src := Procs[p].WbMsg.Proc;
      ::romp::Assignment<NODE>((src), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1358,12},{1358,20}})).get</*WbMsg*/6>()).get</*Proc*/1>()), ::romp::location{{1358,5},{1358,31}});
      // Procs[p].UniMsg[src].Cmd := WB_WbAck;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1359,5},{1359,13}})).get</*UniMsg*/4>()), (src), ::romp::location{{1359,5},{1359,25}})).get</*Cmd*/0>()), (WB_WbAck), ::romp::location{{1359,5},{1359,41}});
      // Undefine Procs[p].UniMsg[src].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1360,14},{1360,22}})).get</*UniMsg*/4>()), (src), ::romp::location{{1360,14},{1360,34}})).get</*Proc*/1>())).Undefine();
      // Undefine Procs[p].UniMsg[src].Data;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1361,14},{1361,22}})).get</*UniMsg*/4>()), (src), ::romp::location{{1361,14},{1361,34}})).get</*Data*/2>())).Undefine();
      // Undefine Procs[p].WbMsg;
      (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1363,14},{1363,22}})).get</*WbMsg*/6>())).Undefine();
      // Procs[p].WbMsg.Cmd := WB_None;
      ::romp::Assignment<WB_CMD>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1364,5},{1364,13}})).get</*WbMsg*/6>()).get</*Cmd*/0>()), (WB_None), ::romp::location{{1364,5},{1364,34}});
    } catch (...) { throw ::romp::ModelRuleError(26,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__L1_Recv_WbAck(const Procss p, const NODE dst) const {
    try {
      return (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1372,3},{1372,11}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1372,3},{1372,23}})).get</*Cmd*/0>()) == (WB_WbAck));
    } catch (...) { throw ::romp::ModelRuleError(27,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L1_Recv_WbAck(const Procss p, const NODE dst) {
    try {
      if (this->__rw__->assertion_handler(((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1375,11},{1375,19}})).get</*Proc*/3>()), (dst), ::romp::location{{1375,11},{1375,29}})).get</*block_WB*/4>()) == (true)) && (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1376,4},{1376,12}})).get</*Proc*/3>()), (dst), ::romp::location{{1376,4},{1376,22}})).get</*ProcCmd*/0>()) == (NODE_None))),45u)) throw ::romp::ModelPropertyError(45);

      // Procs[p].Proc[dst].block_WB := false;
      ::romp::Assignment<boolean>(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1379,3},{1379,11}})).get</*Proc*/3>()), (dst), ::romp::location{{1379,3},{1379,21}})).get</*block_WB*/4>()), (false), ::romp::location{{1379,3},{1379,39}});
      // Undefine Procs[p].UniMsg[dst];
      ((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1380,12},{1380,20}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1380,12},{1380,32}}))).Undefine();
      // Procs[p].UniMsg[dst].Cmd := UNI_None;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1381,3},{1381,11}})).get</*UniMsg*/4>()), (dst), ::romp::location{{1381,3},{1381,23}})).get</*Cmd*/0>()), (UNI_None), ::romp::location{{1381,3},{1381,39}});
    } catch (...) { throw ::romp::ModelRuleError(27,::romp::ModelRuleError::ACTION); }
  }

  // RuleBase
  
  bool __romp__Rule_guard__L2_SilentDrop(const Procss p) const {
    try {
      return (((((((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1390,3},{1390,11}})).get</*L2*/9>()).get</*State*/0>()) != (Invld)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1391,3},{1391,11}})).get</*L2*/9>()).get</*pending*/2>()) == (false))) && ({bool res_ = true; for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) { res_ &= ((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1393,9},{1393,17}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{1393,9},{1393,30}})) == (false)); } res_; })) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1394,3},{1394,11}})).get</*L2*/9>()).get</*Dirty*/3>()) == (false))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1395,3},{1395,11}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1396,3},{1396,11}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)));
    } catch (...) { throw ::romp::ModelRuleError(28,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__L2_SilentDrop(const Procss p) {
    try {
      // Procs[p].L2.State := Invld;
      ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1399,3},{1399,11}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{1399,3},{1399,29}});
      // Procs[p].L2.OnlyCopy := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1400,3},{1400,11}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{1400,3},{1400,32}});
      // Undefine Procs[p].L2.Data;
      ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1401,12},{1401,20}})).get</*L2*/9>()).get</*Data*/1>())).Undefine();
      // Undefine Procs[p].L2.HeadPtr;
      ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1402,12},{1402,20}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
      // invariant purpose
      // Undefine Procs[p].PrevData;
      (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1405,12},{1405,20}})).get</*PrevData*/1>())).Undefine();
      // Undefine Procs[p].CurrData;
      (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{1406,12},{1406,20}})).get</*CurrData*/0>())).Undefine();
    } catch (...) { throw ::romp::ModelRuleError(28,::romp::ModelRuleError::ACTION); }
  }

  //---- outside a cluster  ------
  
  bool __romp__Rule_guard__Dir_HomeGet_Put(void) const {
    try {
      return ((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1415,3},{1415,14}})).get</*RAC*/10>()).get</*State*/0>()) == (WRDO)) && (((Dir).get</*isBusy*/0>()) == (false))) && ((((Dir).get</*State*/2>()) == (Invld)) || (((Dir).get</*State*/2>()) == (Shrd))));
    } catch (...) { throw ::romp::ModelRuleError(29,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_HomeGet_Put(void) {
    try {
      NODE src;
      // Dir.State := Shrd;
      ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{1421,3},{1421,20}});
      // Dir.isLocal := true;
      ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (true), ::romp::location{{1422,3},{1422,22}});
      // Procs[Home].L2.State := Shrd;
      ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1423,3},{1423,14}})).get</*L2*/9>()).get</*State*/0>()), (Shrd), ::romp::location{{1423,3},{1423,31}});
      // Procs[Home].L2.Data := Dir.Mem;
      ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1424,3},{1424,14}})).get</*L2*/9>()).get</*Data*/1>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1424,3},{1424,33}});
      // Procs[Home].RAC.State := Inval;
      ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1425,3},{1425,14}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{1425,3},{1425,33}});
      // Procs[Home].L2.pending := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1426,3},{1426,14}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{1426,3},{1426,34}});
      if (this->__rw__->assertion_handler((!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1427,24},{1427,35}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined())),46u)) throw ::romp::ModelPropertyError(46);

      // src := Procs[Home].L2.ReqId;
      ::romp::Assignment<NODE>((src), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1428,10},{1428,21}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1428,3},{1428,30}});
      // Procs[Home].L2.ShrSet[src] := true;
      ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1429,3},{1429,14}})).get</*L2*/9>()).get</*ShrSet*/4>()), (src), ::romp::location{{1429,3},{1429,29}})), (true), ::romp::location{{1429,3},{1429,37}});
      // Procs[Home].CurrData := Dir.Mem;
      ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1431,3},{1431,14}})).get</*CurrData*/0>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1431,3},{1431,34}});
      // Procs[Home].UniMsg[src].Cmd := UNI_Put;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1432,3},{1432,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1432,3},{1432,26}})).get</*Cmd*/0>()), (UNI_Put), ::romp::location{{1432,3},{1432,41}});
      // Procs[Home].UniMsg[src].Data := Procs[Home].L2.Data;
      ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1433,3},{1433,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1433,3},{1433,26}})).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1433,35},{1433,46}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1433,3},{1433,54}});
      // Undefine Procs[Home].UniMsg[src].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1434,12},{1434,23}})).get</*UniMsg*/4>()), (src), ::romp::location{{1434,12},{1434,35}})).get</*Proc*/1>())).Undefine();
      // Undefine Procs[Home].L2.ReqId;
      ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1435,12},{1435,23}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1437,11},{1437,22}})).get</*L2*/9>()).get</*isRetired*/12>()) == (false)),47u)) throw ::romp::ModelPropertyError(47);

      // Procs[Home].L2.isRetired := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1438,3},{1438,14}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{1438,3},{1438,35}});
    } catch (...) { throw ::romp::ModelRuleError(29,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_HomeGet_RmtGet(void) const {
    try {
      return (((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1444,3},{1444,14}})).get</*RAC*/10>()).get</*State*/0>()) == (WRDO)) && (((Dir).get</*isBusy*/0>()) == (false))) && (((Dir).get</*State*/2>()) == (Excl))) && (((Dir).get</*isLocal*/5>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(30,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_HomeGet_RmtGet(void) {
    try {
      // Dir.isBusy := true;
      ::romp::Assignment<boolean>(((Dir).get</*isBusy*/0>()), (true), ::romp::location{{1450,3},{1450,21}});
      if (this->__rw__->assertion_handler((!(((Dir).get</*HeadPtr*/6>()).IsUndefined())),48u)) throw ::romp::ModelPropertyError(48);

      // GUniMsg[Home].Cmd := RD_RAC;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1452,3},{1452,16}})).get</*Cmd*/0>()), (RD_RAC), ::romp::location{{1452,3},{1452,30}});
      // GUniMsg[Home].Cluster := Dir.HeadPtr;
      ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1453,3},{1453,16}})).get</*Cluster*/1>()), ((Dir).get</*HeadPtr*/6>()), ::romp::location{{1453,3},{1453,39}});
      // Undefine GUniMsg[Home].Data;
      (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1454,12},{1454,25}})).get</*Data*/3>())).Undefine();
      // Undefine GUniMsg[Home].InvCnt;
      (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1455,12},{1455,25}})).get</*InvCnt*/2>())).Undefine();
    } catch (...) { throw ::romp::ModelRuleError(30,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_HomeGet_isLocal_Put(void) const {
    try {
      return (((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1461,3},{1461,14}})).get</*RAC*/10>()).get</*State*/0>()) == (WRDO)) && (((Dir).get</*isBusy*/0>()) == (false))) && (((Dir).get</*State*/2>()) == (Excl))) && (((Dir).get</*isLocal*/5>()) == (true)));
    } catch (...) { throw ::romp::ModelRuleError(31,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_HomeGet_isLocal_Put(void) {
    try {
      NODE src;
      if (this->__rw__->assertion_handler((((Dir).get</*HeadPtr*/6>()).IsUndefined()),49u)) throw ::romp::ModelPropertyError(49);

      // Dir.State := Shrd;
      ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{1470,3},{1470,20}});
      // Procs[Home].L2.State := Shrd;
      ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1471,3},{1471,14}})).get</*L2*/9>()).get</*State*/0>()), (Shrd), ::romp::location{{1471,3},{1471,31}});
      // Procs[Home].L2.Data := Dir.Mem;
      ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1472,3},{1472,14}})).get</*L2*/9>()).get</*Data*/1>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1472,3},{1472,33}});
      // Procs[Home].L2.OnlyCopy := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1473,3},{1473,14}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{1473,3},{1473,35}});
      // Procs[Home].RAC.State := Inval;
      ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1474,3},{1474,14}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{1474,3},{1474,33}});
      // Procs[Home].L2.pending := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1475,3},{1475,14}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{1475,3},{1475,34}});
      if (this->__rw__->assertion_handler((!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1476,24},{1476,35}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined())),50u)) throw ::romp::ModelPropertyError(50);

      // src := Procs[Home].L2.ReqId;
      ::romp::Assignment<NODE>((src), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1477,10},{1477,21}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1477,3},{1477,30}});
      // Procs[Home].L2.ShrSet[src] := true;
      ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1478,3},{1478,14}})).get</*L2*/9>()).get</*ShrSet*/4>()), (src), ::romp::location{{1478,3},{1478,29}})), (true), ::romp::location{{1478,3},{1478,37}});
      // invariant purpose
      // Procs[Home].CurrData := Dir.Mem;
      ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1481,3},{1481,14}})).get</*CurrData*/0>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1481,3},{1481,34}});
      // Procs[Home].UniMsg[src].Cmd := UNI_Put;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1482,3},{1482,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1482,3},{1482,26}})).get</*Cmd*/0>()), (UNI_Put), ::romp::location{{1482,3},{1482,41}});
      // Procs[Home].UniMsg[src].Data := Dir.Mem;
      ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1483,3},{1483,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1483,3},{1483,26}})).get</*Data*/2>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1483,3},{1483,42}});
      // Undefine Procs[Home].UniMsg[src].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1484,12},{1484,23}})).get</*UniMsg*/4>()), (src), ::romp::location{{1484,12},{1484,35}})).get</*Proc*/1>())).Undefine();
      // Undefine Procs[Home].L2.ReqId;
      ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1485,12},{1485,23}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1487,11},{1487,22}})).get</*L2*/9>()).get</*isRetired*/12>()) == (false)),51u)) throw ::romp::ModelPropertyError(51);

      // Procs[Home].L2.isRetired := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1488,3},{1488,14}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{1488,3},{1488,35}});
    } catch (...) { throw ::romp::ModelRuleError(31,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_HomeGetX_RmtGetX(void) const {
    try {
      return (((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1494,3},{1494,14}})).get</*RAC*/10>()).get</*State*/0>()) == (WRDX)) && (((Dir).get</*isBusy*/0>()) == (false))) && (((Dir).get</*State*/2>()) == (Excl))) && (((Dir).get</*isLocal*/5>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(32,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_HomeGetX_RmtGetX(void) {
    try {
      // Dir.isBusy := true;
      ::romp::Assignment<boolean>(((Dir).get</*isBusy*/0>()), (true), ::romp::location{{1500,3},{1500,21}});
      if (this->__rw__->assertion_handler((!(((Dir).get</*HeadPtr*/6>()).IsUndefined())),52u)) throw ::romp::ModelPropertyError(52);

      // GUniMsg[Home].Cmd := RDX_RAC;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1503,3},{1503,16}})).get</*Cmd*/0>()), (RDX_RAC), ::romp::location{{1503,3},{1503,31}});
      // GUniMsg[Home].Cluster := Dir.HeadPtr;
      ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1504,3},{1504,16}})).get</*Cluster*/1>()), ((Dir).get</*HeadPtr*/6>()), ::romp::location{{1504,3},{1504,39}});
      // Undefine GUniMsg[Home].InvCnt;
      (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1505,12},{1505,25}})).get</*InvCnt*/2>())).Undefine();
      // Undefine GUniMsg[Home].Data;
      (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1506,12},{1506,25}})).get</*Data*/3>())).Undefine();
    } catch (...) { throw ::romp::ModelRuleError(32,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_HomeGetX_isLocal_PutX(void) const {
    try {
      return (((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1512,3},{1512,14}})).get</*RAC*/10>()).get</*State*/0>()) == (WRDX)) && (((Dir).get</*isBusy*/0>()) == (false))) && (((Dir).get</*State*/2>()) == (Excl))) && (((Dir).get</*isLocal*/5>()) == (true)));
    } catch (...) { throw ::romp::ModelRuleError(33,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_HomeGetX_isLocal_PutX(void) {
    try {
      NODE src;
      if (this->__rw__->assertion_handler((((Dir).get</*HeadPtr*/6>()).IsUndefined()),53u)) throw ::romp::ModelPropertyError(53);

      // Dir.State := Excl;
      ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Excl), ::romp::location{{1521,3},{1521,20}});
      // Procs[Home].L2.State := Excl;
      ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1522,3},{1522,14}})).get</*L2*/9>()).get</*State*/0>()), (Excl), ::romp::location{{1522,3},{1522,31}});
      // Procs[Home].L2.Data := Dir.Mem;
      ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1523,3},{1523,14}})).get</*L2*/9>()).get</*Data*/1>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1523,3},{1523,33}});
      // Procs[Home].L2.OnlyCopy := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1524,3},{1524,14}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (true), ::romp::location{{1524,3},{1524,34}});
      if (this->__rw__->assertion_handler((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1526,11},{1526,22}})).get</*L2*/9>()).get</*pending*/2>()) == (true)) && (!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1526,56},{1526,67}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined()))),54u)) throw ::romp::ModelPropertyError(54);

      // Procs[Home].RAC.State := Inval;
      ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1528,3},{1528,14}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{1528,3},{1528,33}});
      // Procs[Home].L2.HeadPtr := Procs[Home].L2.ReqId;
      ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1529,3},{1529,14}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1529,29},{1529,40}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1529,3},{1529,49}});
      // Procs[Home].L2.Dirty := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1530,3},{1530,14}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{1530,3},{1530,32}});
      if (this->__rw__->assertion_handler((({bool res_ = true; for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) { res_ &= ((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1532,29},{1532,40}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{1532,29},{1532,53}})) == (false)); } res_; }) && ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1533,4},{1533,15}})).get</*L2*/9>()).get</*InvCnt*/5>()) == ((::romp::range_t)(0)))),55u)) throw ::romp::ModelPropertyError(55);

      // Procs[Home].L2.pending := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1535,3},{1535,14}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{1535,3},{1535,34}});
      // invariant purpose  
      // Procs[Home].CurrData := Dir.Mem;
      ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1537,3},{1537,14}})).get</*CurrData*/0>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1537,3},{1537,34}});
      // src := Procs[Home].L2.ReqId;
      ::romp::Assignment<NODE>((src), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1539,10},{1539,21}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1539,3},{1539,30}});
      // Procs[Home].UniMsg[src].Cmd := UNI_PutX;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1540,3},{1540,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1540,3},{1540,26}})).get</*Cmd*/0>()), (UNI_PutX), ::romp::location{{1540,3},{1540,42}});
      // Procs[Home].UniMsg[src].Data := Dir.Mem;
      ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1541,3},{1541,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1541,3},{1541,26}})).get</*Data*/2>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1541,3},{1541,42}});
      // Undefine Procs[Home].UniMsg[src].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1542,12},{1542,23}})).get</*UniMsg*/4>()), (src), ::romp::location{{1542,12},{1542,35}})).get</*Proc*/1>())).Undefine();
      // Undefine Procs[Home].L2.ReqId;
      ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1543,12},{1543,23}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1545,11},{1545,22}})).get</*L2*/9>()).get</*isRetired*/12>()) == (false)),56u)) throw ::romp::ModelPropertyError(56);

      // Procs[Home].L2.isRetired := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1546,3},{1546,14}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{1546,3},{1546,35}});
    } catch (...) { throw ::romp::ModelRuleError(33,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_HomeGetX_PutX(void) const {
    try {
      return ((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1552,3},{1552,14}})).get</*RAC*/10>()).get</*State*/0>()) == (WRDX)) && (((Dir).get</*isBusy*/0>()) == (false))) && (((Dir).get</*State*/2>()) == (Invld)));
    } catch (...) { throw ::romp::ModelRuleError(34,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_HomeGetX_PutX(void) {
    try {
      NODE src;
      if (this->__rw__->assertion_handler(((((Dir).get</*isLocal*/5>()) == (false)) && (((Dir).get</*HeadPtr*/6>()).IsUndefined())),57u)) throw ::romp::ModelPropertyError(57);

      // Dir.State := Excl;
      ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Excl), ::romp::location{{1561,3},{1561,20}});
      // Dir.isLocal := true;
      ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (true), ::romp::location{{1562,3},{1562,22}});
      // Procs[Home].L2.State := Excl;
      ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1563,3},{1563,14}})).get</*L2*/9>()).get</*State*/0>()), (Excl), ::romp::location{{1563,3},{1563,31}});
      // Procs[Home].L2.OnlyCopy := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1564,3},{1564,14}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (true), ::romp::location{{1564,3},{1564,34}});
      // Procs[Home].L2.Data := Dir.Mem;
      ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1565,3},{1565,14}})).get</*L2*/9>()).get</*Data*/1>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1565,3},{1565,33}});
      // Procs[Home].L2.Dirty := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1566,3},{1566,14}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{1566,3},{1566,32}});
      if (this->__rw__->assertion_handler((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1568,11},{1568,22}})).get</*L2*/9>()).get</*pending*/2>()) == (true)) && (!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1568,56},{1568,67}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined()))),58u)) throw ::romp::ModelPropertyError(58);

      // Procs[Home].RAC.State := Inval;
      ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1570,3},{1570,14}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{1570,3},{1570,33}});
      // Procs[Home].L2.HeadPtr := Procs[Home].L2.ReqId;
      ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1571,3},{1571,14}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1571,29},{1571,40}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1571,3},{1571,49}});
      if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1572,7},{1572,18}})).get</*L2*/9>()).get</*InvCnt*/5>()) == ((::romp::range_t)(0))) {
        // Procs[Home].L2.pending := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1573,5},{1573,16}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{1573,5},{1573,36}});
      }
      // invariant purpose  
      // Procs[Home].CurrData := Dir.Mem;
      ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1576,3},{1576,14}})).get</*CurrData*/0>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1576,3},{1576,34}});
      // src := Procs[Home].L2.ReqId;
      ::romp::Assignment<NODE>((src), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1578,10},{1578,21}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1578,3},{1578,30}});
      // Procs[Home].UniMsg[src].Cmd := UNI_PutX;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1579,3},{1579,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1579,3},{1579,26}})).get</*Cmd*/0>()), (UNI_PutX), ::romp::location{{1579,3},{1579,42}});
      // Procs[Home].UniMsg[src].Data := Dir.Mem;
      ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1580,3},{1580,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1580,3},{1580,26}})).get</*Data*/2>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1580,3},{1580,42}});
      // Undefine Procs[Home].UniMsg[src].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1581,12},{1581,23}})).get</*UniMsg*/4>()), (src), ::romp::location{{1581,12},{1581,35}})).get</*Proc*/1>())).Undefine();
      // Undefine Procs[Home].L2.ReqId;
      ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1582,12},{1582,23}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1584,11},{1584,22}})).get</*L2*/9>()).get</*isRetired*/12>()) == (false)),59u)) throw ::romp::ModelPropertyError(59);

      // Procs[Home].L2.isRetired := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1585,3},{1585,14}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{1585,3},{1585,35}});
    } catch (...) { throw ::romp::ModelRuleError(34,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_Shrd_HomeGetX_PutX(void) const {
    try {
      return ((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1591,3},{1591,14}})).get</*RAC*/10>()).get</*State*/0>()) == (WRDX)) && (((Dir).get</*isBusy*/0>()) == (false))) && (((Dir).get</*State*/2>()) == (Shrd)));
    } catch (...) { throw ::romp::ModelRuleError(35,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Shrd_HomeGetX_PutX(void) {
    try {
      ClusterCnt ShrCnt;
      NODE src;
      // Dir.State := Excl;
      ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Excl), ::romp::location{{1598,3},{1598,20}});
      if (this->__rw__->assertion_handler((((Dir).get</*HeadPtr*/6>()).IsUndefined()),60u)) throw ::romp::ModelPropertyError(60);

      // Procs[Home].L2.State := Excl;
      ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1600,3},{1600,14}})).get</*L2*/9>()).get</*State*/0>()), (Excl), ::romp::location{{1600,3},{1600,31}});
      // Procs[Home].L2.Data := Dir.Mem;
      ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1601,3},{1601,14}})).get</*L2*/9>()).get</*Data*/1>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1601,3},{1601,33}});
      // Procs[Home].L2.Dirty := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1602,3},{1602,14}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{1602,3},{1602,32}});
      // Procs[Home].L2.OnlyCopy := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1603,3},{1603,14}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (true), ::romp::location{{1603,3},{1603,34}});
      // Home is the only sharer
      if (({bool res_ = true; for (auto r=Rmt::__LB(); r!=Rmt::__UB(); r.__step()) { res_ &= ((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (r), ::romp::location{{1607,7},{1607,20}})) == (false)); } res_; })) {
        if (this->__rw__->assertion_handler((((Dir).get</*isLocal*/5>()) == (true)),61u)) throw ::romp::ModelPropertyError(61);

        // Procs[Home].RAC.State := Inval;
        ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1609,5},{1609,16}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{1609,5},{1609,35}});
      } else {
        // exist remote cluster sharer
        // ShrCnt := 0;
        ::romp::Assignment<ClusterCnt>((ShrCnt), ((::romp::range_t)(0)), ::romp::location{{1613,5},{1613,16}});
        for (auto r=Rmt::__LB(); r!=Rmt::__UB(); r.__step()) {
          if ((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (r), ::romp::location{{1615,11},{1615,24}})) == (true)) {
            // Dir.ShrSet[r] := false;
            ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (r), ::romp::location{{1616,9},{1616,22}})), (false), ::romp::location{{1616,9},{1616,31}});
            // ShrCnt := (ShrCnt + 1);
            ::romp::Assignment<ClusterCnt>((ShrCnt), ((ShrCnt) + ((::romp::range_t)(1))), ::romp::location{{1617,9},{1617,29}});
            // GInvMsg[r].Cmd := INV;
            ::romp::Assignment<GINV_CMD>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (r), ::romp::location{{1618,9},{1618,19}})).get</*Cmd*/0>()), (INV), ::romp::location{{1618,9},{1618,30}});
            // GInvMsg[r].Cluster := Home;
            ::romp::Assignment<Procss>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (r), ::romp::location{{1619,9},{1619,19}})).get</*Cluster*/1>()), (Home), ::romp::location{{1619,9},{1619,35}});
          }
        }

        // Procs[Home].RAC.State := WINV;
        ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1622,5},{1622,16}})).get</*RAC*/10>()).get</*State*/0>()), (WINV), ::romp::location{{1622,5},{1622,34}});
        // Procs[Home].RAC.InvCnt := ShrCnt;
        ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1623,5},{1623,16}})).get</*RAC*/10>()).get</*InvCnt*/1>()), (ShrCnt), ::romp::location{{1623,5},{1623,37}});
        // invariant purpose
        // Dir.Collecting := true;
        ::romp::Assignment<boolean>(((Dir).get</*Collecting*/7>()), (true), ::romp::location{{1626,5},{1626,27}});
        // Dir.PrevData := Dir.CurrData;
        ::romp::Assignment<Datas>(((Dir).get</*PrevData*/9>()), ((Dir).get</*CurrData*/8>()), ::romp::location{{1627,5},{1627,33}});
      }
      // Dir.isLocal := true;
      ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (true), ::romp::location{{1630,3},{1630,22}});
      if (this->__rw__->assertion_handler((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1631,11},{1631,22}})).get</*L2*/9>()).get</*pending*/2>()) == (true)) && (!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1631,56},{1631,67}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined()))),62u)) throw ::romp::ModelPropertyError(62);

      // Procs[Home].L2.HeadPtr := Procs[Home].L2.ReqId;
      ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1633,3},{1633,14}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1633,29},{1633,40}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1633,3},{1633,49}});
      // src := Procs[Home].L2.ReqId;
      ::romp::Assignment<NODE>((src), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1634,10},{1634,21}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1634,3},{1634,30}});
      if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1636,7},{1636,18}})).get</*L2*/9>()).get</*InvCnt*/5>()) == ((::romp::range_t)(0))) {
        // Procs[Home].L2.pending := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1637,5},{1637,16}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{1637,5},{1637,36}});
      }
      // Procs[Home].CurrData := Dir.Mem;
      ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1640,3},{1640,14}})).get</*CurrData*/0>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1640,3},{1640,34}});
      // src := Procs[Home].L2.ReqId;
      ::romp::Assignment<NODE>((src), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1641,10},{1641,21}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1641,3},{1641,30}});
      // Procs[Home].UniMsg[src].Cmd := UNI_PutX;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1642,3},{1642,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1642,3},{1642,26}})).get</*Cmd*/0>()), (UNI_PutX), ::romp::location{{1642,3},{1642,42}});
      // Procs[Home].UniMsg[src].Data := Dir.Mem;
      ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1643,3},{1643,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1643,3},{1643,26}})).get</*Data*/2>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1643,3},{1643,42}});
      // Undefine Procs[Home].UniMsg[src].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1644,12},{1644,23}})).get</*UniMsg*/4>()), (src), ::romp::location{{1644,12},{1644,35}})).get</*Proc*/1>())).Undefine();
      // Undefine Procs[Home].L2.ReqId;
      ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1645,12},{1645,23}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1647,11},{1647,22}})).get</*L2*/9>()).get</*isRetired*/12>()) == (false)),63u)) throw ::romp::ModelPropertyError(63);

      // Procs[Home].L2.isRetired := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1648,3},{1648,14}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{1648,3},{1648,35}});
    } catch (...) { throw ::romp::ModelRuleError(35,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Home_Recv_InvAck(const Procss src) const {
    try {
      return ((((::romp::Element<Procss,GINV_MSG>((GInvMsg), (src), ::romp::location{{1655,3},{1655,15}})).get</*Cmd*/0>()) == (SACK)) && (((::romp::Element<Procss,GINV_MSG>((GInvMsg), (src), ::romp::location{{1656,3},{1656,15}})).get</*Cluster*/1>()) == (Home)));
    } catch (...) { throw ::romp::ModelRuleError(36,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Home_Recv_InvAck(const Procss src) {
    try {
      do {
        __typeof__((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1660,10},{1660,21}})).get</*RAC*/10>()).get</*State*/0>())) res_ = (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1660,10},{1660,21}})).get</*RAC*/10>()).get</*State*/0>());
        if (res_ == (WINV)) {
          // receive InvAck after reply from Dir
          // Procs[Home].RAC.InvCnt := (Procs[Home].RAC.InvCnt - 1);
          ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1664,5},{1664,16}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1664,31},{1664,42}})).get</*RAC*/10>()).get</*InvCnt*/1>()) - ((::romp::range_t)(1))), ::romp::location{{1664,5},{1664,57}});
          // all InvAck received
          if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1667,9},{1667,20}})).get</*RAC*/10>()).get</*InvCnt*/1>()) == ((::romp::range_t)(0))) {
            // Procs[Home].RAC.State := Inval;
            ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1668,7},{1668,18}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{1668,7},{1668,37}});
            // invariant purpose
            // Dir.Collecting := false;
            ::romp::Assignment<boolean>(((Dir).get</*Collecting*/7>()), (false), ::romp::location{{1670,7},{1670,30}});
          }
        } else {
          if (this->__rw__->error_handler(0u))
            throw ::romp::ModelMErrorError(0);

        }
      } while (0);
      // Undefine GInvMsg[src];
      ((::romp::Element<Procss,GINV_MSG>((GInvMsg), (src), ::romp::location{{1677,12},{1677,24}}))).Undefine();
      // GInvMsg[src].Cmd := GINV_None;
      ::romp::Assignment<GINV_CMD>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (src), ::romp::location{{1678,3},{1678,15}})).get</*Cmd*/0>()), (GINV_None), ::romp::location{{1678,3},{1678,32}});
    } catch (...) { throw ::romp::ModelRuleError(36,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Home_Recv_IACK_X_(void) const {
    try {
      return ((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1685,3},{1685,16}})).get</*Cmd*/0>()) == (IACK)) || (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1686,3},{1686,16}})).get</*Cmd*/0>()) == (IACKX)));
    } catch (...) { throw ::romp::ModelRuleError(37,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Home_Recv_IACK_X_(void) {
    try {
      Procss dst;
      NODE src;
      if (this->__rw__->assertion_handler((((Dir).get</*isBusy*/0>()) == (true)),64u)) throw ::romp::ModelPropertyError(64);

      // Dir.isBusy := false;
      ::romp::Assignment<boolean>(((Dir).get</*isBusy*/0>()), (false), ::romp::location{{1692,3},{1692,22}});
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1693,11},{1693,22}})).get</*RAC*/10>()).get</*State*/0>()) == (WRDX)),65u)) throw ::romp::ModelPropertyError(65);

      // Procs[Home].L2.Data := GUniMsg[Home].Data;
      ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1695,3},{1695,14}})).get</*L2*/9>()).get</*Data*/1>()), ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1695,26},{1695,39}})).get</*Data*/3>()), ::romp::location{{1695,3},{1695,44}});
      // Procs[Home].CurrData := GUniMsg[Home].Data;
      ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1696,3},{1696,14}})).get</*CurrData*/0>()), ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1696,27},{1696,40}})).get</*Data*/3>()), ::romp::location{{1696,3},{1696,45}});
      // Dir.CurrData := GUniMsg[Home].Data;
      // Procs[Home].L2.State := Excl;
      ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1698,3},{1698,14}})).get</*L2*/9>()).get</*State*/0>()), (Excl), ::romp::location{{1698,3},{1698,31}});
      // Procs[Home].L2.OnlyCopy := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1699,3},{1699,14}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (true), ::romp::location{{1699,3},{1699,34}});
      if (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1700,7},{1700,20}})).get</*Cmd*/0>()) == (IACK)) {
        // Procs[Home].L2.Dirty := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1701,5},{1701,16}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{1701,5},{1701,34}});
      } else {
        // Procs[Home].L2.Dirty := true;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1703,5},{1703,16}})).get</*L2*/9>()).get</*Dirty*/3>()), (true), ::romp::location{{1703,5},{1703,33}});
      }
      if (this->__rw__->assertion_handler((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1706,11},{1706,22}})).get</*L2*/9>()).get</*pending*/2>()) == (true)) && (!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1706,56},{1706,67}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined()))),66u)) throw ::romp::ModelPropertyError(66);

      // src := Procs[Home].L2.ReqId;
      ::romp::Assignment<NODE>((src), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1708,10},{1708,21}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1708,3},{1708,30}});
      // Procs[Home].L2.HeadPtr := src;
      ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1709,3},{1709,14}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (src), ::romp::location{{1709,3},{1709,32}});
      if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1710,7},{1710,18}})).get</*L2*/9>()).get</*InvCnt*/5>()) == ((::romp::range_t)(0))) {
        // Procs[Home].L2.pending := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1711,5},{1711,16}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{1711,5},{1711,36}});
      }
      // Procs[Home].UniMsg[src].Cmd := UNI_PutX;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1713,3},{1713,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1713,3},{1713,26}})).get</*Cmd*/0>()), (UNI_PutX), ::romp::location{{1713,3},{1713,42}});
      // Procs[Home].UniMsg[src].Data := Procs[Home].L2.Data;
      ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1714,3},{1714,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1714,3},{1714,26}})).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1714,35},{1714,46}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1714,3},{1714,54}});
      // Undefine Procs[Home].UniMsg[src].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1715,12},{1715,23}})).get</*UniMsg*/4>()), (src), ::romp::location{{1715,12},{1715,35}})).get</*Proc*/1>())).Undefine();
      // Undefine Procs[Home].L2.ReqId;
      ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1716,12},{1716,23}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
      if (this->__rw__->assertion_handler((((((Dir).get</*State*/2>()) == (Excl)) && (!(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1718,43},{1718,56}})).get</*Cluster*/1>()).IsUndefined()))) && (((Dir).get</*HeadPtr*/6>()) == ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1719,18},{1719,31}})).get</*Cluster*/1>()))),67u)) throw ::romp::ModelPropertyError(67);

      // Undefine Dir.HeadPtr;
      (((Dir).get</*HeadPtr*/6>())).Undefine();
      // Dir.isLocal := true;
      ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (true), ::romp::location{{1722,3},{1722,22}});
      // Procs[Home].RAC.State := Inval;
      ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1723,3},{1723,14}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{1723,3},{1723,33}});
      // Procs[Home].RAC.InvCnt := 0;
      ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1724,3},{1724,14}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((::romp::range_t)(0)), ::romp::location{{1724,3},{1724,30}});
      // Undefine GUniMsg[Home];
      ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1726,12},{1726,25}}))).Undefine();
      // GUniMsg[Home].Cmd := GUNI_None;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1727,3},{1727,16}})).get</*Cmd*/0>()), (GUNI_None), ::romp::location{{1727,3},{1727,33}});
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1729,11},{1729,22}})).get</*L2*/9>()).get</*isRetired*/12>()) == (false)),68u)) throw ::romp::ModelPropertyError(68);

      // Procs[Home].L2.isRetired := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1730,3},{1730,14}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{1730,3},{1730,35}});
    } catch (...) { throw ::romp::ModelRuleError(37,::romp::ModelRuleError::ACTION); }
  }

  // we can grant Home req when NAK_Home, but it will need another 
  // ReqType inside L2.
  
  bool __romp__Rule_guard__Home_Recv_Nak(void) const {
    try {
      return ((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1737,3},{1737,16}})).get</*Cmd*/0>()) == (NAK)) || (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1738,3},{1738,16}})).get</*Cmd*/0>()) == (NAK_Home)));
    } catch (...) { throw ::romp::ModelRuleError(38,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Home_Recv_Nak(void) {
    try {
      NODE src;
      if (this->__rw__->assertion_handler((((Dir).get</*isBusy*/0>()) == (true)),69u)) throw ::romp::ModelPropertyError(69);

      // Dir.isBusy := false;
      ::romp::Assignment<boolean>(((Dir).get</*isBusy*/0>()), (false), ::romp::location{{1743,3},{1743,22}});
      // Procs[Home].RAC.State := Inval;
      ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1745,3},{1745,14}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{1745,3},{1745,33}});
      // Procs[Home].RAC.InvCnt := 0;
      ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1746,3},{1746,14}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((::romp::range_t)(0)), ::romp::location{{1746,3},{1746,30}});
      if (this->__rw__->assertion_handler((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1747,11},{1747,22}})).get</*L2*/9>()).get</*pending*/2>()) == (true)) && (!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1747,56},{1747,67}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined()))),70u)) throw ::romp::ModelPropertyError(70);

      if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1749,7},{1749,18}})).get</*L2*/9>()).get</*InvCnt*/5>()) == ((::romp::range_t)(0))) {
        // Procs[Home].L2.pending := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1750,5},{1750,16}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{1750,5},{1750,36}});
      }
      // src := Procs[Home].L2.ReqId;
      ::romp::Assignment<NODE>((src), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1753,10},{1753,21}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1753,3},{1753,30}});
      // Procs[Home].UniMsg[src].Cmd := UNI_Nak;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1754,3},{1754,14}})).get</*UniMsg*/4>()), (src), ::romp::location{{1754,3},{1754,26}})).get</*Cmd*/0>()), (UNI_Nak), ::romp::location{{1754,3},{1754,41}});
      // Undefine Procs[Home].UniMsg[src].Data;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1755,12},{1755,23}})).get</*UniMsg*/4>()), (src), ::romp::location{{1755,12},{1755,35}})).get</*Data*/2>())).Undefine();
      // Undefine Procs[Home].UniMsg[src].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1756,12},{1756,23}})).get</*UniMsg*/4>()), (src), ::romp::location{{1756,12},{1756,35}})).get</*Proc*/1>())).Undefine();
      // Undefine Procs[Home].L2.ReqId;
      ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1757,12},{1757,23}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
      if (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1759,7},{1759,20}})).get</*Cmd*/0>()) == (NAK_Home)) {
        if (this->__rw__->assertion_handler((!(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1760,26},{1760,39}})).get</*Cluster*/1>()).IsUndefined())),71u)) throw ::romp::ModelPropertyError(71);

        if ((((Dir).get</*State*/2>()) == (Excl)) && (((Dir).get</*HeadPtr*/6>()) == ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1761,42},{1761,55}})).get</*Cluster*/1>()))) {
          // remove old owner
          // Dir.State := Invld;
          ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Invld), ::romp::location{{1763,7},{1763,25}});
          // Undefine Dir.HeadPtr;
          (((Dir).get</*HeadPtr*/6>())).Undefine();
        }
      }
      // Undefine GUniMsg[Home];
      ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1767,12},{1767,25}}))).Undefine();
      // GUniMsg[Home].Cmd := GUNI_None;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1768,3},{1768,16}})).get</*Cmd*/0>()), (GUNI_None), ::romp::location{{1768,3},{1768,33}});
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1770,11},{1770,22}})).get</*L2*/9>()).get</*isRetired*/12>()) == (false)),72u)) throw ::romp::ModelPropertyError(72);

      // Procs[Home].L2.isRetired := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1771,3},{1771,14}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{1771,3},{1771,35}});
    } catch (...) { throw ::romp::ModelRuleError(38,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_Recv_NAKC_DIR(void) const {
    try {
      return ((((GNakcMsg).get</*Cmd*/0>()) == (GNAKC_DIR)) || (((GNakcMsg).get</*Cmd*/0>()) == (GNAKC_Nakc)));
    } catch (...) { throw ::romp::ModelRuleError(39,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Recv_NAKC_DIR(void) {
    try {
      if (this->__rw__->assertion_handler((((Dir).get</*isBusy*/0>()) == (true)),73u)) throw ::romp::ModelPropertyError(73);

      // Dir.isBusy := false;
      ::romp::Assignment<boolean>(((Dir).get</*isBusy*/0>()), (false), ::romp::location{{1782,3},{1782,22}});
      if (((GNakcMsg).get</*Cmd*/0>()) == (GNAKC_DIR)) {
        if (this->__rw__->assertion_handler((!(((GNakcMsg).get</*Cluster*/1>()).IsUndefined())),74u)) throw ::romp::ModelPropertyError(74);

        if ((((Dir).get</*State*/2>()) == (Excl)) && (((Dir).get</*HeadPtr*/6>()) == ((GNakcMsg).get</*Cluster*/1>()))) {
          // Dir.State := Invld;
          ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Invld), ::romp::location{{1787,7},{1787,25}});
          // Undefine Dir.HeadPtr;
          (((Dir).get</*HeadPtr*/6>())).Undefine();
        }
      }
      // Undefine GNakcMsg;
      ((GNakcMsg)).Undefine();
      // GNakcMsg.Cmd := GNAKC_None;
      ::romp::Assignment<GNAKC_CMD>(((GNakcMsg).get</*Cmd*/0>()), (GNAKC_None), ::romp::location{{1793,3},{1793,29}});
    } catch (...) { throw ::romp::ModelRuleError(39,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Home_Recv_ACK(void) const {
    try {
      return (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1799,3},{1799,16}})).get</*Cmd*/0>()) == (ACK));
    } catch (...) { throw ::romp::ModelRuleError(40,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Home_Recv_ACK(void) {
    try {
      NODE src;
      if (this->__rw__->assertion_handler((((Dir).get</*isBusy*/0>()) == (true)),75u)) throw ::romp::ModelPropertyError(75);

      // Dir.isBusy := false;
      ::romp::Assignment<boolean>(((Dir).get</*isBusy*/0>()), (false), ::romp::location{{1804,3},{1804,22}});
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1806,11},{1806,22}})).get</*L2*/9>()).get</*pending*/2>()) == (true)),76u)) throw ::romp::ModelPropertyError(76);

      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1807,11},{1807,22}})).get</*RAC*/10>()).get</*State*/0>()) != (Inval)),77u)) throw ::romp::ModelPropertyError(77);

      do {
        __typeof__((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1809,10},{1809,21}})).get</*RAC*/10>()).get</*State*/0>())) res_ = (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1809,10},{1809,21}})).get</*RAC*/10>()).get</*State*/0>());
        if (res_ == (WRDO)) {
          // home wait read reply
          // Procs[Home].L2.State := Shrd;
          ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1813,5},{1813,16}})).get</*L2*/9>()).get</*State*/0>()), (Shrd), ::romp::location{{1813,5},{1813,33}});
          // Procs[Home].L2.Data := GUniMsg[Home].Data;
          ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1814,5},{1814,16}})).get</*L2*/9>()).get</*Data*/1>()), ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1814,28},{1814,41}})).get</*Data*/3>()), ::romp::location{{1814,5},{1814,46}});
          // Procs[Home].RAC.State := Inval;
          ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1815,5},{1815,16}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{1815,5},{1815,35}});
          // Procs[Home].RAC.InvCnt := 0;
          ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1816,5},{1816,16}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((::romp::range_t)(0)), ::romp::location{{1816,5},{1816,32}});
          // Dir.Mem := GUniMsg[Home].Data;
          ::romp::Assignment<Datas>(((Dir).get</*Mem*/1>()), ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1817,16},{1817,29}})).get</*Data*/3>()), ::romp::location{{1817,5},{1817,34}});
          // Dir.CurrData := GUniMsg[Home].Data;
          if (this->__rw__->assertion_handler(((((Dir).get</*State*/2>()) == (Excl)) && (((Dir).get</*HeadPtr*/6>()) == ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1820,46},{1820,59}})).get</*Cluster*/1>()))),78u)) throw ::romp::ModelPropertyError(78);

          // Dir.State := Shrd;
          ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{1822,5},{1822,22}});
          // Dir.ShrSet[Dir.HeadPtr] := true;
          ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), ((Dir).get</*HeadPtr*/6>()), ::romp::location{{1823,5},{1823,28}})), (true), ::romp::location{{1823,5},{1823,36}});
          // Undefine Dir.HeadPtr;
          (((Dir).get</*HeadPtr*/6>())).Undefine();
          // Dir.isLocal := true;
          ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (true), ::romp::location{{1825,5},{1825,24}});
          // Procs[Home].L2.OnlyCopy := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1827,5},{1827,16}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{1827,5},{1827,37}});
          // Procs[Home].L2.pending := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1828,5},{1828,16}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{1828,5},{1828,36}});
          // src := Procs[Home].L2.ReqId;
          ::romp::Assignment<NODE>((src), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1829,12},{1829,23}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1829,5},{1829,32}});
          // Procs[Home].L2.ShrSet[src] := true;
          ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1830,5},{1830,16}})).get</*L2*/9>()).get</*ShrSet*/4>()), (src), ::romp::location{{1830,5},{1830,31}})), (true), ::romp::location{{1830,5},{1830,39}});
          // invariant purpose
          // Procs[Home].CurrData := Dir.Mem;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1833,5},{1833,16}})).get</*CurrData*/0>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1833,5},{1833,36}});
          // Procs[Home].UniMsg[src].Cmd := UNI_Put;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1834,5},{1834,16}})).get</*UniMsg*/4>()), (src), ::romp::location{{1834,5},{1834,28}})).get</*Cmd*/0>()), (UNI_Put), ::romp::location{{1834,5},{1834,43}});
          // Procs[Home].UniMsg[src].Data := Dir.Mem;
          ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1835,5},{1835,16}})).get</*UniMsg*/4>()), (src), ::romp::location{{1835,5},{1835,28}})).get</*Data*/2>()), ((Dir).get</*Mem*/1>()), ::romp::location{{1835,5},{1835,44}});
          // Undefine Procs[Home].UniMsg[src].Proc;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1836,14},{1836,25}})).get</*UniMsg*/4>()), (src), ::romp::location{{1836,14},{1836,37}})).get</*Proc*/1>())).Undefine();
          // Undefine Procs[Home].L2.ReqId;
          ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1837,14},{1837,25}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
        } else if (res_ == (RRD)) {
          // invalidated before reply come back
          // Procs[Home].RAC.State := Inval;
          ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1841,5},{1841,16}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{1841,5},{1841,35}});
          // Procs[Home].RAC.InvCnt := 0;
          ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1842,5},{1842,16}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((::romp::range_t)(0)), ::romp::location{{1842,5},{1842,32}});
          if (this->__rw__->assertion_handler((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1844,13},{1844,24}})).get</*L2*/9>()).get</*pending*/2>()) == (true)) && (!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1844,58},{1844,69}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined()))),79u)) throw ::romp::ModelPropertyError(79);

          // Procs[Home].L2.pending := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1846,5},{1846,16}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{1846,5},{1846,36}});
          if (this->__rw__->assertion_handler(((((Dir).get</*State*/2>()) == (Excl)) && (((Dir).get</*HeadPtr*/6>()) == ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1848,46},{1848,59}})).get</*Cluster*/1>()))),80u)) throw ::romp::ModelPropertyError(80);

          // Dir.State := Shrd;
          ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{1850,5},{1850,22}});
          // Dir.ShrSet[Dir.HeadPtr] := true;
          ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), ((Dir).get</*HeadPtr*/6>()), ::romp::location{{1851,5},{1851,28}})), (true), ::romp::location{{1851,5},{1851,36}});
          // Undefine Dir.HeadPtr;
          (((Dir).get</*HeadPtr*/6>())).Undefine();
          // Dir.Mem := GUniMsg[Home].Data;
          ::romp::Assignment<Datas>(((Dir).get</*Mem*/1>()), ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1853,16},{1853,29}})).get</*Data*/3>()), ::romp::location{{1853,5},{1853,34}});
          // Dir.CurrData := GUniMsg[Home].Data;
          // src := Procs[Home].L2.ReqId;
          ::romp::Assignment<NODE>((src), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1856,12},{1856,23}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{1856,5},{1856,32}});
          // Procs[Home].UniMsg[src].Cmd := UNI_Nak;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1857,5},{1857,16}})).get</*UniMsg*/4>()), (src), ::romp::location{{1857,5},{1857,28}})).get</*Cmd*/0>()), (UNI_Nak), ::romp::location{{1857,5},{1857,43}});
          // Undefine Procs[Home].UniMsg[src].Data;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1858,14},{1858,25}})).get</*UniMsg*/4>()), (src), ::romp::location{{1858,14},{1858,37}})).get</*Data*/2>())).Undefine();
          // Undefine Procs[Home].UniMsg[src].Proc;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1859,14},{1859,25}})).get</*UniMsg*/4>()), (src), ::romp::location{{1859,14},{1859,37}})).get</*Proc*/1>())).Undefine();
          // Undefine Procs[Home].L2.ReqId;
          ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1860,14},{1860,25}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
        } else {
          if (this->__rw__->error_handler(1u))
            throw ::romp::ModelMErrorError(1);

        }
      } while (0);
      // Undefine GUniMsg[Home];
      ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1866,12},{1866,25}}))).Undefine();
      // GUniMsg[Home].Cmd := GUNI_None;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{1867,3},{1867,16}})).get</*Cmd*/0>()), (GUNI_None), ::romp::location{{1867,3},{1867,33}});
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1869,11},{1869,22}})).get</*L2*/9>()).get</*isRetired*/12>()) == (false)),81u)) throw ::romp::ModelPropertyError(81);

      // Procs[Home].L2.isRetired := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{1870,3},{1870,14}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{1870,3},{1870,35}});
    } catch (...) { throw ::romp::ModelRuleError(40,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__RmtCluster_Recv_Get(const Rmt r, const Procss src) const {
    try {
      return ((((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1876,3},{1876,15}})).get</*Cmd*/0>()) == (RD_RAC)) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1877,3},{1877,15}})).get</*Cluster*/1>()) == (r))) && ((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1878,3},{1878,11}})).get</*L2*/9>()).get</*Gblock_WB*/11>()) == (false))) && ((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1881,3},{1881,11}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(41,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__RmtCluster_Recv_Get(const Rmt r, const Procss src) {
    try {
      // Apr 8
      if (this->__rw__->assertion_handler(((src) != (r)),82u)) throw ::romp::ModelPropertyError(82);

      if (((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1886,7},{1886,15}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)) && ((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1886,36},{1886,44}})).get</*L2*/9>()).get</*pending*/2>()) == (false))) {
        if ((!((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1887,22},{1887,30}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && ((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1887,45},{1887,53}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) {
          // Procs[r].L2.OnlyCopy := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1888,7},{1888,15}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{1888,7},{1888,36}});
          // Procs[r].L2.Dirty := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1889,7},{1889,15}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{1889,7},{1889,33}});
          // Procs[r].L2.State := Shrd;
          ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1890,7},{1890,15}})).get</*L2*/9>()).get</*State*/0>()), (Shrd), ::romp::location{{1890,7},{1890,32}});
          // GUniMsg[src].Cmd := ACK;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1892,7},{1892,19}})).get</*Cmd*/0>()), (ACK), ::romp::location{{1892,7},{1892,30}});
          // GUniMsg[src].Data := Procs[r].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1893,7},{1893,19}})).get</*Data*/3>()), (((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1893,28},{1893,36}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1893,7},{1893,44}});
          // GUniMsg[src].Cluster := r;
          ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1894,7},{1894,19}})).get</*Cluster*/1>()), (r), ::romp::location{{1894,7},{1894,32}});
          // GUniMsg[src].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1895,7},{1895,19}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{1895,7},{1895,31}});
          if ((src) != (Home)) {
            // GShWbMsg.Cmd := SHWB;
            ::romp::Assignment<GSHWB_CMD>(((GShWbMsg).get</*Cmd*/0>()), (SHWB), ::romp::location{{1898,9},{1898,29}});
            // GShWbMsg.Cluster := src;
            ::romp::Assignment<Procss>(((GShWbMsg).get</*Cluster*/1>()), (src), ::romp::location{{1899,9},{1899,32}});
            // GShWbMsg.Data := Procs[r].L2.Data;
            ::romp::Assignment<Datas>(((GShWbMsg).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1900,26},{1900,34}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1900,9},{1900,42}});
          }
        } else if (((!((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1903,25},{1903,33}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && ((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1903,48},{1903,56}})).get</*L2*/9>()).get</*HeadPtr*/6>()) != (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1904,5},{1904,13}})).get</*L2*/9>()).get</*State*/0>()) == (Excl))) {
          // Procs[r].L2.pending := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1905,7},{1905,15}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{1905,7},{1905,34}});
          // Procs[r].UniMsg[L2].Cmd := UNI_Get;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1906,7},{1906,15}})).get</*UniMsg*/4>()), (L2), ::romp::location{{1906,7},{1906,26}})).get</*Cmd*/0>()), (UNI_Get), ::romp::location{{1906,7},{1906,41}});
          // Undefine Procs[r].UniMsg[L2].Data;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1907,16},{1907,24}})).get</*UniMsg*/4>()), (L2), ::romp::location{{1907,16},{1907,35}})).get</*Data*/2>())).Undefine();
          // Procs[r].UniMsg[L2].Proc := Procs[r].L2.HeadPtr;
          ::romp::Assignment<NODE_L2>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1908,7},{1908,15}})).get</*UniMsg*/4>()), (L2), ::romp::location{{1908,7},{1908,26}})).get</*Proc*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1908,35},{1908,43}})).get</*L2*/9>()).get</*HeadPtr*/6>()), ::romp::location{{1908,7},{1908,54}});
          // Procs[r].L2.ReqCluster := src;
          ::romp::Assignment<Procss>((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1910,7},{1910,15}})).get</*L2*/9>()).get</*ReqCluster*/9>()), (src), ::romp::location{{1910,7},{1910,36}});
          // Procs[r].L2.ReqType := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1911,7},{1911,15}})).get</*L2*/9>()).get</*ReqType*/10>()), (true), ::romp::location{{1911,7},{1911,34}});
          // Apr 8
          // undefine GUniMsg[src];
          // GUniMsg[src].Cmd := GUNI_None;
          // Procs[r].L2.ifHoldMsg := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1916,7},{1916,15}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()), (true), ::romp::location{{1916,7},{1916,36}});
        } else if ((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1918,12},{1918,20}})).get</*L2*/9>()).get</*State*/0>()) == (Shrd)) {
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1919,15},{1919,23}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (true)),83u)) throw ::romp::ModelPropertyError(83);

          // Procs[r].L2.OnlyCopy := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1920,7},{1920,15}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{1920,7},{1920,36}});
          // Procs[r].L2.Dirty := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1921,7},{1921,15}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{1921,7},{1921,33}});
          // GUniMsg[src].Cmd := ACK;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1923,7},{1923,19}})).get</*Cmd*/0>()), (ACK), ::romp::location{{1923,7},{1923,30}});
          // GUniMsg[src].Data := Procs[r].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1924,7},{1924,19}})).get</*Data*/3>()), (((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1924,28},{1924,36}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1924,7},{1924,44}});
          // GUniMsg[src].Cluster := r;
          ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1925,7},{1925,19}})).get</*Cluster*/1>()), (r), ::romp::location{{1925,7},{1925,32}});
          // GUniMsg[src].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1926,7},{1926,19}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{1926,7},{1926,31}});
          if ((src) != (Home)) {
            // GShWbMsg.Cmd := SHWB;
            ::romp::Assignment<GSHWB_CMD>(((GShWbMsg).get</*Cmd*/0>()), (SHWB), ::romp::location{{1929,9},{1929,29}});
            // GShWbMsg.Cluster := src;
            ::romp::Assignment<Procss>(((GShWbMsg).get</*Cluster*/1>()), (src), ::romp::location{{1930,9},{1930,32}});
            // GShWbMsg.Data := Procs[r].L2.Data;
            ::romp::Assignment<Datas>(((GShWbMsg).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{1931,26},{1931,34}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1931,9},{1931,42}});
          }
        } else {
          if ((src) == (Home)) {
            // GUniMsg[src].Cmd := NAK_Home;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1936,9},{1936,21}})).get</*Cmd*/0>()), (NAK_Home), ::romp::location{{1936,9},{1936,37}});
            // Undefine GUniMsg[src].Data;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1937,18},{1937,30}})).get</*Data*/3>())).Undefine();
            // GUniMsg[src].Cluster := r;
            ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1938,9},{1938,21}})).get</*Cluster*/1>()), (r), ::romp::location{{1938,9},{1938,34}});
            // Undefine GUniMsg[src].InvCnt;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1939,18},{1939,30}})).get</*InvCnt*/2>())).Undefine();
          } else {
            // GUniMsg[src].Cmd := NAK;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1941,9},{1941,21}})).get</*Cmd*/0>()), (NAK), ::romp::location{{1941,9},{1941,32}});
            // Undefine GUniMsg[src].Data;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1942,18},{1942,30}})).get</*Data*/3>())).Undefine();
            // GUniMsg[src].Cluster := r;
            ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1943,9},{1943,21}})).get</*Cluster*/1>()), (r), ::romp::location{{1943,9},{1943,34}});
            // Undefine GUniMsg[src].InvCnt;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1944,18},{1944,30}})).get</*InvCnt*/2>())).Undefine();
            // GNakcMsg.Cmd := GNAKC_DIR;
            ::romp::Assignment<GNAKC_CMD>(((GNakcMsg).get</*Cmd*/0>()), (GNAKC_DIR), ::romp::location{{1946,9},{1946,34}});
            // GNakcMsg.Cluster := r;
            ::romp::Assignment<Procss>(((GNakcMsg).get</*Cluster*/1>()), (r), ::romp::location{{1947,9},{1947,30}});
          }
        }
      } else {
        // GUniMsg[src].Cmd := NAK;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1953,5},{1953,17}})).get</*Cmd*/0>()), (NAK), ::romp::location{{1953,5},{1953,28}});
        // Undefine GUniMsg[src].Data;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1954,14},{1954,26}})).get</*Data*/3>())).Undefine();
        // GUniMsg[src].Cluster := r;
        ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1955,5},{1955,17}})).get</*Cluster*/1>()), (r), ::romp::location{{1955,5},{1955,30}});
        // Undefine GUniMsg[src].InvCnt;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1956,14},{1956,26}})).get</*InvCnt*/2>())).Undefine();
        if ((src) != (Home)) {
          // GNakcMsg.Cmd := GNAKC_Nakc;
          ::romp::Assignment<GNAKC_CMD>(((GNakcMsg).get</*Cmd*/0>()), (GNAKC_Nakc), ::romp::location{{1958,7},{1958,33}});
          // GNakcMsg.Cluster := r;
          ::romp::Assignment<Procss>(((GNakcMsg).get</*Cluster*/1>()), (r), ::romp::location{{1959,7},{1959,28}});
        }
      }
    } catch (...) { throw ::romp::ModelRuleError(41,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__RmtCluster_Recv_GetX(const Rmt dst, const Procss src) const {
    try {
      return ((((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1969,3},{1969,15}})).get</*Cmd*/0>()) == (RDX_RAC)) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1970,3},{1970,15}})).get</*Cluster*/1>()) == (dst))) && ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{1971,3},{1971,13}})).get</*L2*/9>()).get</*Gblock_WB*/11>()) == (false))) && ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{1974,3},{1974,13}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(42,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__RmtCluster_Recv_GetX(const Rmt dst, const Procss src) {
    try {
      // Apr 8
      CacheCnt iCnt;
      if (this->__rw__->assertion_handler(((src) != (dst)),84u)) throw ::romp::ModelPropertyError(84);

      if (((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{1981,7},{1981,17}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)) && ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{1981,38},{1981,48}})).get</*L2*/9>()).get</*pending*/2>()) == (false))) {
        if ((!((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{1982,22},{1982,32}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{1982,47},{1982,57}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) {
          // Procs[dst].L2.OnlyCopy := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{1983,7},{1983,17}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{1983,7},{1983,38}});
          // Procs[dst].L2.State := Invld;
          ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{1984,7},{1984,17}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{1984,7},{1984,35}});
          // GUniMsg[src].Data := Procs[dst].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1985,7},{1985,19}})).get</*Data*/3>()), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{1985,28},{1985,38}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{1985,7},{1985,46}});
          // GUniMsg[src].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1986,7},{1986,19}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{1986,7},{1986,31}});
          // GUniMsg[src].Cluster := dst;
          ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1987,7},{1987,19}})).get</*Cluster*/1>()), (dst), ::romp::location{{1987,7},{1987,34}});
          if ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{1988,11},{1988,21}})).get</*L2*/9>()).get</*Dirty*/3>()) == (true)) {
            // GUniMsg[src].Cmd := IACKX;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1989,9},{1989,21}})).get</*Cmd*/0>()), (IACKX), ::romp::location{{1989,9},{1989,34}});
          } else {
            // GUniMsg[src].Cmd := IACK;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{1991,9},{1991,21}})).get</*Cmd*/0>()), (IACK), ::romp::location{{1991,9},{1991,33}});
          }
          if ((src) != (Home)) {
            // GShWbMsg.Cmd := DXFER;
            ::romp::Assignment<GSHWB_CMD>(((GShWbMsg).get</*Cmd*/0>()), (DXFER), ::romp::location{{1995,9},{1995,30}});
            // GShWbMsg.Cluster := src;
            ::romp::Assignment<Procss>(((GShWbMsg).get</*Cluster*/1>()), (src), ::romp::location{{1996,9},{1996,32}});
            // Undefine GShWbMsg.Data;
            (((GShWbMsg).get</*Data*/2>())).Undefine();
          }
          // Procs[dst].L2.Dirty := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2000,7},{2000,17}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{2000,7},{2000,35}});
          // Undefine Procs[dst].L2.HeadPtr;
          ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2001,16},{2001,26}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
          // Undefine Procs[dst].L2.Data;
          ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2002,16},{2002,26}})).get</*L2*/9>()).get</*Data*/1>())).Undefine();
          // Undefine Procs[dst].PrevData;
          (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2003,16},{2003,26}})).get</*PrevData*/1>())).Undefine();
          // Undefine Procs[dst].CurrData;
          (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2004,16},{2004,26}})).get</*CurrData*/0>())).Undefine();
        } else if (((!((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2006,25},{2006,35}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2006,50},{2006,60}})).get</*L2*/9>()).get</*HeadPtr*/6>()) != (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2007,5},{2007,15}})).get</*L2*/9>()).get</*State*/0>()) == (Excl))) {
          // Procs[dst].L2.pending := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2008,7},{2008,17}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{2008,7},{2008,36}});
          // Apr 8
          // undefine GUniMsg[src];
          // GUniMsg[src].Cmd := GUNI_None;
          // Procs[dst].L2.ifHoldMsg := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2013,7},{2013,17}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()), (true), ::romp::location{{2013,7},{2013,38}});
          // Procs[dst].UniMsg[L2].Cmd := UNI_GetX;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2016,7},{2016,17}})).get</*UniMsg*/4>()), (L2), ::romp::location{{2016,7},{2016,28}})).get</*Cmd*/0>()), (UNI_GetX), ::romp::location{{2016,7},{2016,44}});
          // Undefine Procs[dst].UniMsg[L2].Data;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2017,16},{2017,26}})).get</*UniMsg*/4>()), (L2), ::romp::location{{2017,16},{2017,37}})).get</*Data*/2>())).Undefine();
          // Procs[dst].UniMsg[L2].Proc := Procs[dst].L2.HeadPtr;
          ::romp::Assignment<NODE_L2>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2018,7},{2018,17}})).get</*UniMsg*/4>()), (L2), ::romp::location{{2018,7},{2018,28}})).get</*Proc*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2018,37},{2018,47}})).get</*L2*/9>()).get</*HeadPtr*/6>()), ::romp::location{{2018,7},{2018,58}});
          // Procs[dst].L2.ReqCluster := src;
          ::romp::Assignment<Procss>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2020,7},{2020,17}})).get</*L2*/9>()).get</*ReqCluster*/9>()), (src), ::romp::location{{2020,7},{2020,38}});
          // Procs[dst].L2.ReqType := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2021,7},{2021,17}})).get</*L2*/9>()).get</*ReqType*/10>()), (false), ::romp::location{{2021,7},{2021,37}});
        } else if ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2023,12},{2023,22}})).get</*L2*/9>()).get</*State*/0>()) == (Shrd)) {
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2024,15},{2024,25}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (true)),85u)) throw ::romp::ModelPropertyError(85);

          // Procs[dst].L2.pending := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2026,7},{2026,17}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{2026,7},{2026,36}});
          // Procs[dst].Collecting := true;
          ::romp::Assignment<boolean>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2027,7},{2027,17}})).get</*Collecting*/2>()), (true), ::romp::location{{2027,7},{2027,36}});
          // Procs[dst].PrevData := Procs[dst].CurrData;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2028,7},{2028,17}})).get</*PrevData*/1>()), ((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2028,30},{2028,40}})).get</*CurrData*/0>()), ::romp::location{{2028,7},{2028,49}});
          // iCnt := 0;
          ::romp::Assignment<CacheCnt>((iCnt), ((::romp::range_t)(0)), ::romp::location{{2029,7},{2029,16}});
          for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) {
            if ((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2031,12},{2031,22}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{2031,12},{2031,35}})) == (true)) {
              // Procs[dst].InvMsg[n].Cmd := INV_Inv;
              ::romp::Assignment<INV_CMD>(((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2032,11},{2032,21}})).get</*InvMsg*/5>()), (n), ::romp::location{{2032,11},{2032,31}})).get</*Cmd*/0>()), (INV_Inv), ::romp::location{{2032,11},{2032,46}});
              // iCnt := (iCnt + 1);
              ::romp::Assignment<CacheCnt>((iCnt), ((iCnt) + ((::romp::range_t)(1))), ::romp::location{{2033,11},{2033,27}});
              // Procs[dst].L2.ShrSet[n] := false;
              ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2034,11},{2034,21}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{2034,11},{2034,34}})), (false), ::romp::location{{2034,11},{2034,43}});
            }
          }

          // Procs[dst].L2.InvCnt := iCnt;
          ::romp::Assignment<CacheCnt>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2037,7},{2037,17}})).get</*L2*/9>()).get</*InvCnt*/5>()), (iCnt), ::romp::location{{2037,7},{2037,35}});
          // GUniMsg[src].Data := Procs[dst].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2039,7},{2039,19}})).get</*Data*/3>()), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2039,28},{2039,38}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{2039,7},{2039,46}});
          // GUniMsg[src].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2040,7},{2040,19}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2040,7},{2040,31}});
          // GUniMsg[src].Cluster := dst;
          ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2041,7},{2041,19}})).get</*Cluster*/1>()), (dst), ::romp::location{{2041,7},{2041,34}});
          if ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2042,11},{2042,21}})).get</*L2*/9>()).get</*Dirty*/3>()) == (true)) {
            // GUniMsg[src].Cmd := IACKX;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2043,9},{2043,21}})).get</*Cmd*/0>()), (IACKX), ::romp::location{{2043,9},{2043,34}});
          } else {
            // GUniMsg[src].Cmd := IACK;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2045,9},{2045,21}})).get</*Cmd*/0>()), (IACK), ::romp::location{{2045,9},{2045,33}});
          }
          if ((src) != (Home)) {
            // GShWbMsg.Cmd := DXFER;
            ::romp::Assignment<GSHWB_CMD>(((GShWbMsg).get</*Cmd*/0>()), (DXFER), ::romp::location{{2049,9},{2049,30}});
            // GShWbMsg.Cluster := src;
            ::romp::Assignment<Procss>(((GShWbMsg).get</*Cluster*/1>()), (src), ::romp::location{{2050,9},{2050,32}});
            // Undefine GShWbMsg.Data;
            (((GShWbMsg).get</*Data*/2>())).Undefine();
          }
          // Procs[dst].L2.State := Invld;
          ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2054,7},{2054,17}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{2054,7},{2054,35}});
          // Procs[dst].L2.OnlyCopy := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2055,7},{2055,17}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{2055,7},{2055,38}});
          // Procs[dst].L2.Dirty := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2056,7},{2056,17}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{2056,7},{2056,35}});
          // Undefine Procs[dst].L2.Data;
          ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2057,16},{2057,26}})).get</*L2*/9>()).get</*Data*/1>())).Undefine();
        } else {
          if ((src) == (Home)) {
            // GUniMsg[src].Cmd := NAK_Home;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2061,9},{2061,21}})).get</*Cmd*/0>()), (NAK_Home), ::romp::location{{2061,9},{2061,37}});
            // Undefine GUniMsg[src].Data;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2062,18},{2062,30}})).get</*Data*/3>())).Undefine();
            // GUniMsg[src].Cluster := dst;
            ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2063,9},{2063,21}})).get</*Cluster*/1>()), (dst), ::romp::location{{2063,9},{2063,36}});
            // Undefine GUniMsg[src].InvCnt;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2064,18},{2064,30}})).get</*InvCnt*/2>())).Undefine();
          } else {
            // GUniMsg[src].Cmd := NAK;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2066,9},{2066,21}})).get</*Cmd*/0>()), (NAK), ::romp::location{{2066,9},{2066,32}});
            // Undefine GUniMsg[src].Data;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2067,18},{2067,30}})).get</*Data*/3>())).Undefine();
            // GUniMsg[src].Cluster := dst;
            ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2068,9},{2068,21}})).get</*Cluster*/1>()), (dst), ::romp::location{{2068,9},{2068,36}});
            // Undefine GUniMsg[src].InvCnt;
            (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2069,18},{2069,30}})).get</*InvCnt*/2>())).Undefine();
            // GNakcMsg.Cmd := GNAKC_DIR;
            ::romp::Assignment<GNAKC_CMD>(((GNakcMsg).get</*Cmd*/0>()), (GNAKC_DIR), ::romp::location{{2071,9},{2071,34}});
            // GNakcMsg.Cluster := dst;
            ::romp::Assignment<Procss>(((GNakcMsg).get</*Cluster*/1>()), (dst), ::romp::location{{2072,9},{2072,32}});
          }
        }
      } else {
        // GUniMsg[src].Cmd := NAK;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2077,5},{2077,17}})).get</*Cmd*/0>()), (NAK), ::romp::location{{2077,5},{2077,28}});
        // Undefine GUniMsg[src].Data;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2078,14},{2078,26}})).get</*Data*/3>())).Undefine();
        // GUniMsg[src].Cluster := dst;
        ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2079,5},{2079,17}})).get</*Cluster*/1>()), (dst), ::romp::location{{2079,5},{2079,32}});
        // Undefine GUniMsg[src].InvCnt;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{2080,14},{2080,26}})).get</*InvCnt*/2>())).Undefine();
        if ((src) != (Home)) {
          // GNakcMsg.Cmd := GNAKC_Nakc;
          ::romp::Assignment<GNAKC_CMD>(((GNakcMsg).get</*Cmd*/0>()), (GNAKC_Nakc), ::romp::location{{2082,7},{2082,33}});
          // GNakcMsg.Cluster := dst;
          ::romp::Assignment<Procss>(((GNakcMsg).get</*Cluster*/1>()), (dst), ::romp::location{{2083,7},{2083,30}});
        }
      }
    } catch (...) { throw ::romp::ModelRuleError(42,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_Recv_DXFER(void) const {
    try {
      return (((GShWbMsg).get</*Cmd*/0>()) == (DXFER));
    } catch (...) { throw ::romp::ModelRuleError(43,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Recv_DXFER(void) {
    try {
      if (this->__rw__->assertion_handler((((Dir).get</*isBusy*/0>()) == (true)),86u)) throw ::romp::ModelPropertyError(86);

      // Dir.isBusy := false;
      ::romp::Assignment<boolean>(((Dir).get</*isBusy*/0>()), (false), ::romp::location{{2096,3},{2096,22}});
      if ((((Dir).get</*State*/2>()) == (Excl)) && (!(((Dir).get</*HeadPtr*/6>()).IsUndefined()))) {
        // Dir.HeadPtr := GShWbMsg.Cluster;
        ::romp::Assignment<Procss>(((Dir).get</*HeadPtr*/6>()), ((GShWbMsg).get</*Cluster*/1>()), ::romp::location{{2098,5},{2098,36}});
      }
      // Undefine GShWbMsg;
      ((GShWbMsg)).Undefine();
      // GShWbMsg.Cmd := GSHWB_None;
      ::romp::Assignment<GSHWB_CMD>(((GShWbMsg).get</*Cmd*/0>()), (GSHWB_None), ::romp::location{{2101,3},{2101,29}});
    } catch (...) { throw ::romp::ModelRuleError(43,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_Recv_ShWb(void) const {
    try {
      return (((GShWbMsg).get</*Cmd*/0>()) == (SHWB));
    } catch (...) { throw ::romp::ModelRuleError(44,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Recv_ShWb(void) {
    try {
      if (this->__rw__->assertion_handler((((Dir).get</*isBusy*/0>()) == (true)),87u)) throw ::romp::ModelPropertyError(87);

      // Dir.isBusy := false;
      ::romp::Assignment<boolean>(((Dir).get</*isBusy*/0>()), (false), ::romp::location{{2111,3},{2111,22}});
      if (this->__rw__->assertion_handler((((Dir).get</*State*/2>()) == (Excl)),88u)) throw ::romp::ModelPropertyError(88);

      if (this->__rw__->assertion_handler(((!(((Dir).get</*HeadPtr*/6>()).IsUndefined())) && (((Dir).get</*isLocal*/5>()) == (false))),89u)) throw ::romp::ModelPropertyError(89);

      // Dir.Mem := GShWbMsg.Data;
      ::romp::Assignment<Datas>(((Dir).get</*Mem*/1>()), ((GShWbMsg).get</*Data*/2>()), ::romp::location{{2116,3},{2116,27}});
      // Dir.CurrData := GShWbMsg.Data;
      // Dir.State := Shrd;
      ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{2118,3},{2118,20}});
      // Dir.ShrSet[GShWbMsg.Cluster] := true;
      ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), ((GShWbMsg).get</*Cluster*/1>()), ::romp::location{{2119,3},{2119,31}})), (true), ::romp::location{{2119,3},{2119,39}});
      // Dir.ShrSet[Dir.HeadPtr] := true;
      ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), ((Dir).get</*HeadPtr*/6>()), ::romp::location{{2120,3},{2120,26}})), (true), ::romp::location{{2120,3},{2120,34}});
      // Undefine Dir.HeadPtr;
      (((Dir).get</*HeadPtr*/6>())).Undefine();
      // Undefine GShWbMsg;
      ((GShWbMsg)).Undefine();
      // GShWbMsg.Cmd := GSHWB_None;
      ::romp::Assignment<GSHWB_CMD>(((GShWbMsg).get</*Cmd*/0>()), (GSHWB_None), ::romp::location{{2124,3},{2124,29}});
    } catch (...) { throw ::romp::ModelRuleError(44,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__RmtCluster_Recv_ACK(const Rmt dst) const {
    try {
      return (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2131,3},{2131,15}})).get</*Cmd*/0>()) == (ACK));
    } catch (...) { throw ::romp::ModelRuleError(45,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__RmtCluster_Recv_ACK(const Rmt dst) {
    try {
      NODE aux;
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2135,11},{2135,21}})).get</*RAC*/10>()).get</*State*/0>()) != (Inval)),90u)) throw ::romp::ModelPropertyError(90);

      do {
        __typeof__((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2137,10},{2137,20}})).get</*RAC*/10>()).get</*State*/0>())) res_ = (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2137,10},{2137,20}})).get</*RAC*/10>()).get</*State*/0>());
        if (res_ == (WRD)) {
          // remote wait read reply
          // Procs[dst].L2.State := Shrd;
          ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2141,5},{2141,15}})).get</*L2*/9>()).get</*State*/0>()), (Shrd), ::romp::location{{2141,5},{2141,32}});
          // Procs[dst].L2.Data := GUniMsg[dst].Data;
          ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2142,5},{2142,15}})).get</*L2*/9>()).get</*Data*/1>()), ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2142,27},{2142,39}})).get</*Data*/3>()), ::romp::location{{2142,5},{2142,44}});
          // Procs[dst].RAC.State := Inval;
          ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2143,5},{2143,15}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{2143,5},{2143,34}});
          // Procs[dst].RAC.InvCnt := 0;
          ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2144,5},{2144,15}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((::romp::range_t)(0)), ::romp::location{{2144,5},{2144,31}});
          if (this->__rw__->assertion_handler((!((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2146,26},{2146,36}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined())),91u)) throw ::romp::ModelPropertyError(91);

          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2147,13},{2147,23}})).get</*L2*/9>()).get</*pending*/2>()) == (true)),92u)) throw ::romp::ModelPropertyError(92);

          // Procs[dst].L2.pending := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2148,5},{2148,15}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{2148,5},{2148,35}});
          // aux := Procs[dst].L2.ReqId;
          ::romp::Assignment<NODE>((aux), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2149,12},{2149,22}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{2149,5},{2149,31}});
          // Procs[dst].L2.ShrSet[aux] := true;
          ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2150,5},{2150,15}})).get</*L2*/9>()).get</*ShrSet*/4>()), (aux), ::romp::location{{2150,5},{2150,30}})), (true), ::romp::location{{2150,5},{2150,38}});
          // Procs[dst].UniMsg[aux].Cmd := UNI_Put;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2151,5},{2151,15}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2151,5},{2151,27}})).get</*Cmd*/0>()), (UNI_Put), ::romp::location{{2151,5},{2151,42}});
          // Procs[dst].UniMsg[aux].Data := Procs[dst].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2152,5},{2152,15}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2152,5},{2152,27}})).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2152,36},{2152,46}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{2152,5},{2152,54}});
          // Undefine Procs[dst].UniMsg[aux].Proc;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2153,14},{2153,24}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2153,14},{2153,36}})).get</*Proc*/1>())).Undefine();
          // Undefine Procs[dst].L2.ReqId;
          ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2154,14},{2154,24}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
          // invariant purpose
          // Procs[dst].CurrData := GUniMsg[dst].Data;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2157,5},{2157,15}})).get</*CurrData*/0>()), ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2157,28},{2157,40}})).get</*Data*/3>()), ::romp::location{{2157,5},{2157,45}});
        } else if (res_ == (WRDO)) {
          // home wait read reply
          if (this->__rw__->error_handler(2u))
            throw ::romp::ModelMErrorError(2);

        } else if (res_ == (WRDX)) {
          // cluster wait excl reply
          // Procs[dst].L2.State := Excl;
          ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2165,5},{2165,15}})).get</*L2*/9>()).get</*State*/0>()), (Excl), ::romp::location{{2165,5},{2165,32}});
          // Procs[dst].L2.Data := GUniMsg[dst].Data;
          ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2166,5},{2166,15}})).get</*L2*/9>()).get</*Data*/1>()), ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2166,27},{2166,39}})).get</*Data*/3>()), ::romp::location{{2166,5},{2166,44}});
          // Procs[dst].L2.OnlyCopy := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2167,5},{2167,15}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (true), ::romp::location{{2167,5},{2167,35}});
          // Procs[dst].RAC.State := Inval;
          ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2168,5},{2168,15}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{2168,5},{2168,34}});
          // Procs[dst].RAC.InvCnt := 0;
          ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2169,5},{2169,15}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((::romp::range_t)(0)), ::romp::location{{2169,5},{2169,31}});
          // Procs[dst].L2.Dirty := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2170,5},{2170,15}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{2170,5},{2170,33}});
          // invariant purpose
          // Procs[dst].CurrData := Procs[dst].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2172,5},{2172,15}})).get</*CurrData*/0>()), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2172,28},{2172,38}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{2172,5},{2172,46}});
          if (this->__rw__->assertion_handler((!((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2174,26},{2174,36}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined())),93u)) throw ::romp::ModelPropertyError(93);

          // aux := Procs[dst].L2.ReqId;
          ::romp::Assignment<NODE>((aux), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2175,12},{2175,22}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{2175,5},{2175,31}});
          // Procs[dst].L2.HeadPtr := aux;
          ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2176,5},{2176,15}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (aux), ::romp::location{{2176,5},{2176,33}});
          // Procs[dst].UniMsg[aux].Cmd := UNI_PutX;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2177,5},{2177,15}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2177,5},{2177,27}})).get</*Cmd*/0>()), (UNI_PutX), ::romp::location{{2177,5},{2177,43}});
          // Procs[dst].UniMsg[aux].Data := Procs[dst].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2178,5},{2178,15}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2178,5},{2178,27}})).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2178,36},{2178,46}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{2178,5},{2178,54}});
          // Undefine Procs[dst].UniMsg[aux].Proc;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2179,14},{2179,24}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2179,14},{2179,36}})).get</*Proc*/1>())).Undefine();
          // Undefine Procs[dst].L2.ReqId;
          ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2180,14},{2180,24}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2182,13},{2182,23}})).get</*L2*/9>()).get</*pending*/2>()) == (true)),94u)) throw ::romp::ModelPropertyError(94);

          if ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2183,9},{2183,19}})).get</*L2*/9>()).get</*InvCnt*/5>()) == ((::romp::range_t)(0))) {
            // Procs[dst].L2.pending := false;
            ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2184,7},{2184,17}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{2184,7},{2184,37}});
          }
        } else if (res_ == (RRD)) {
          // invalidated before reply come back
          // Procs[dst].RAC.State := Inval;
          ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2189,5},{2189,15}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{2189,5},{2189,34}});
          // Procs[dst].RAC.InvCnt := 0;
          ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2190,5},{2190,15}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((::romp::range_t)(0)), ::romp::location{{2190,5},{2190,31}});
          if (this->__rw__->assertion_handler((!((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2192,26},{2192,36}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined())),95u)) throw ::romp::ModelPropertyError(95);

          // aux := Procs[dst].L2.ReqId;
          ::romp::Assignment<NODE>((aux), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2193,12},{2193,22}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{2193,5},{2193,31}});
          // Procs[dst].UniMsg[aux].Cmd := UNI_Nak;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2194,5},{2194,15}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2194,5},{2194,27}})).get</*Cmd*/0>()), (UNI_Nak), ::romp::location{{2194,5},{2194,42}});
          // Undefine Procs[dst].UniMsg[aux].Data;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2195,14},{2195,24}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2195,14},{2195,36}})).get</*Data*/2>())).Undefine();
          // Undefine Procs[dst].UniMsg[aux].Proc;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2196,14},{2196,24}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2196,14},{2196,36}})).get</*Proc*/1>())).Undefine();
          // Undefine Procs[dst].L2.ReqId;
          ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2197,14},{2197,24}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2199,13},{2199,23}})).get</*L2*/9>()).get</*pending*/2>()) == (true)),96u)) throw ::romp::ModelPropertyError(96);

          // Procs[dst].L2.pending := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2200,5},{2200,15}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{2200,5},{2200,35}});
        }
      } while (0);
      // Undefine GUniMsg[dst];
      ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2203,12},{2203,24}}))).Undefine();
      // GUniMsg[dst].Cmd := GUNI_None;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2204,3},{2204,15}})).get</*Cmd*/0>()), (GUNI_None), ::romp::location{{2204,3},{2204,32}});
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2206,11},{2206,21}})).get</*L2*/9>()).get</*isRetired*/12>()) == (false)),97u)) throw ::romp::ModelPropertyError(97);

      // Procs[dst].L2.isRetired := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2207,3},{2207,13}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{2207,3},{2207,34}});
    } catch (...) { throw ::romp::ModelRuleError(45,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__RmtCluster_Recv_Nak(const Rmt dst) const {
    try {
      return (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2215,3},{2215,15}})).get</*Cmd*/0>()) == (NAK));
    } catch (...) { throw ::romp::ModelRuleError(46,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__RmtCluster_Recv_Nak(const Rmt dst) {
    try {
      NODE aux;
      if (this->__rw__->assertion_handler((((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2219,12},{2219,22}})).get</*RAC*/10>()).get</*State*/0>()) != (Inval)) && ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2219,46},{2219,56}})).get</*RAC*/10>()).get</*State*/0>()) != (WINV))),98u)) throw ::romp::ModelPropertyError(98);

      // Procs[dst].RAC.State := Inval;
      ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2221,3},{2221,13}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{2221,3},{2221,32}});
      // Procs[dst].RAC.InvCnt := 0;
      ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2222,3},{2222,13}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((::romp::range_t)(0)), ::romp::location{{2222,3},{2222,29}});
      if (this->__rw__->assertion_handler((!((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2224,24},{2224,34}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined())),99u)) throw ::romp::ModelPropertyError(99);

      // aux := Procs[dst].L2.ReqId;
      ::romp::Assignment<NODE>((aux), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2225,10},{2225,20}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{2225,3},{2225,29}});
      // Procs[dst].UniMsg[aux].Cmd := UNI_Nak;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2226,3},{2226,13}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2226,3},{2226,25}})).get</*Cmd*/0>()), (UNI_Nak), ::romp::location{{2226,3},{2226,40}});
      // Undefine Procs[dst].UniMsg[aux].Data;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2227,12},{2227,22}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2227,12},{2227,34}})).get</*Data*/2>())).Undefine();
      // Undefine Procs[dst].UniMsg[aux].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2228,12},{2228,22}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2228,12},{2228,34}})).get</*Proc*/1>())).Undefine();
      // Undefine Procs[dst].L2.ReqId;
      ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2229,12},{2229,22}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2231,11},{2231,21}})).get</*L2*/9>()).get</*pending*/2>()) == (true)),100u)) throw ::romp::ModelPropertyError(100);

      if ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2232,7},{2232,17}})).get</*L2*/9>()).get</*InvCnt*/5>()) == ((::romp::range_t)(0))) {
        // Procs[dst].L2.pending := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2233,5},{2233,15}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{2233,5},{2233,35}});
      }
      // Undefine GUniMsg[dst];
      ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2236,12},{2236,24}}))).Undefine();
      // GUniMsg[dst].Cmd := GUNI_None;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2237,3},{2237,15}})).get</*Cmd*/0>()), (GUNI_None), ::romp::location{{2237,3},{2237,32}});
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2239,11},{2239,21}})).get</*L2*/9>()).get</*isRetired*/12>()) == (false)),101u)) throw ::romp::ModelPropertyError(101);

      // Procs[dst].L2.isRetired := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2240,3},{2240,13}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{2240,3},{2240,34}});
    } catch (...) { throw ::romp::ModelRuleError(46,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Cluster_Recv_Inv(const Procss dst) const {
    try {
      return (((::romp::Element<Procss,GINV_MSG>((GInvMsg), (dst), ::romp::location{{2248,3},{2248,15}})).get</*Cmd*/0>()) == (INV));
    } catch (...) { throw ::romp::ModelRuleError(47,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Cluster_Recv_Inv(const Procss dst) {
    try {
      Procss proc;
      CacheCnt iCnt;
      // proc := GInvMsg[dst].Cluster;
      ::romp::Assignment<Procss>((proc), ((::romp::Element<Procss,GINV_MSG>((GInvMsg), (dst), ::romp::location{{2253,11},{2253,23}})).get</*Cluster*/1>()), ::romp::location{{2253,3},{2253,31}});
      do {
        __typeof__((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2255,10},{2255,20}})).get</*RAC*/10>()).get</*State*/0>())) res_ = (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2255,10},{2255,20}})).get</*RAC*/10>()).get</*State*/0>());
        if (res_ == (Inval)) {
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2257,13},{2257,23}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) != (true)),102u)) throw ::romp::ModelPropertyError(102);

          if ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2258,9},{2258,19}})).get</*L2*/9>()).get</*State*/0>()) == (Shrd)) {
            if ((!((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2259,24},{2259,34}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2259,49},{2259,59}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) {
              // Undefine Procs[dst].L2.HeadPtr;
              ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2260,18},{2260,28}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
              // Undefine Procs[dst].PrevData;
              (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2261,18},{2261,28}})).get</*PrevData*/1>())).Undefine();
              // Undefine Procs[dst].CurrData;
              (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2262,18},{2262,28}})).get</*CurrData*/0>())).Undefine();
            } else if ((!({bool res_ = true; for (auto m=NODE::__LB(); m!=NODE::__UB(); m.__step()) { res_ &= ((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2264,34},{2264,44}})).get</*L2*/9>()).get</*ShrSet*/4>()), (m), ::romp::location{{2264,34},{2264,57}})) == (false)); } res_; }))) {
              // invariant purpose
              // Procs[dst].PrevData := Procs[dst].CurrData;
              ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2266,9},{2266,19}})).get</*PrevData*/1>()), ((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2266,32},{2266,42}})).get</*CurrData*/0>()), ::romp::location{{2266,9},{2266,51}});
              // Procs[dst].Collecting := true;
              ::romp::Assignment<boolean>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2267,9},{2267,19}})).get</*Collecting*/2>()), (true), ::romp::location{{2267,9},{2267,38}});
              // Procs[dst].L2.pending := true;
              ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2268,9},{2268,19}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{2268,9},{2268,38}});
              // iCnt := 0;
              ::romp::Assignment<CacheCnt>((iCnt), ((::romp::range_t)(0)), ::romp::location{{2269,9},{2269,18}});
              for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) {
                if ((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2271,15},{2271,25}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{2271,15},{2271,38}})) == (true)) {
                  // iCnt := (iCnt + 1);
                  ::romp::Assignment<CacheCnt>((iCnt), ((iCnt) + ((::romp::range_t)(1))), ::romp::location{{2272,6},{2272,22}});
                  // Procs[dst].InvMsg[n].Cmd := INV_Inv;
                  ::romp::Assignment<INV_CMD>(((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2273,13},{2273,23}})).get</*InvMsg*/5>()), (n), ::romp::location{{2273,13},{2273,33}})).get</*Cmd*/0>()), (INV_Inv), ::romp::location{{2273,13},{2273,48}});
                  // Procs[dst].L2.ShrSet[n] := false;
                  ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2274,13},{2274,23}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{2274,13},{2274,36}})), (false), ::romp::location{{2274,13},{2274,45}});
                }
              }

              // Procs[dst].L2.InvCnt := iCnt;
              ::romp::Assignment<CacheCnt>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2277,9},{2277,19}})).get</*L2*/9>()).get</*InvCnt*/5>()), (iCnt), ::romp::location{{2277,9},{2277,37}});
            }
          }
          // Procs[dst].L2.State := Invld;
          ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2281,5},{2281,15}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{2281,5},{2281,33}});
          // Undefine Procs[dst].L2.Data;
          ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2282,14},{2282,24}})).get</*L2*/9>()).get</*Data*/1>())).Undefine();
        } else if (res_ == (WRD)) {
          // Procs[dst].RAC.State := RRD;
          ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2285,5},{2285,15}})).get</*RAC*/10>()).get</*State*/0>()), (RRD), ::romp::location{{2285,5},{2285,32}});
        } else if (res_ == (WRDO)) {
          // Procs[dst].RAC.State := RRD;
          ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2287,5},{2287,15}})).get</*RAC*/10>()).get</*State*/0>()), (RRD), ::romp::location{{2287,5},{2287,32}});
        } else if (res_ == (WRDX)) {
          if ((proc) == (dst)) {
            // Procs[dst].RAC.InvCnt := (Procs[dst].RAC.InvCnt + 1);
            ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2290,7},{2290,17}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2290,32},{2290,42}})).get</*RAC*/10>()).get</*InvCnt*/1>()) + ((::romp::range_t)(1))), ::romp::location{{2290,7},{2290,57}});
          } else {
            // Procs[dst].L2.State := Invld;
            ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2292,7},{2292,17}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{2292,7},{2292,35}});
            // Undefine Procs[dst].L2.Data;
            ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2293,16},{2293,26}})).get</*L2*/9>()).get</*Data*/1>())).Undefine();
            if ((!((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2294,24},{2294,34}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2294,49},{2294,59}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) {
              // Undefine Procs[dst].L2.HeadPtr;
              ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2295,18},{2295,28}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
            }
          }
        } else if (res_ == (WINV)) {
          if ((proc) == (dst)) {
            // Procs[dst].RAC.InvCnt := (Procs[dst].RAC.InvCnt - 1);
            ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2300,7},{2300,17}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2300,32},{2300,42}})).get</*RAC*/10>()).get</*InvCnt*/1>()) - ((::romp::range_t)(1))), ::romp::location{{2300,7},{2300,57}});
            // all InvAck received
            if ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2302,11},{2302,21}})).get</*RAC*/10>()).get</*InvCnt*/1>()) == ((::romp::range_t)(0))) {
              // Procs[dst].RAC.State := Inval;
              ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2303,9},{2303,19}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{2303,9},{2303,38}});
              // invariant purpose
              // Dir.Collecting := false;
              ::romp::Assignment<boolean>(((Dir).get</*Collecting*/7>()), (false), ::romp::location{{2305,9},{2305,32}});
            }
          } else {
            if (this->__rw__->error_handler(3u))
              throw ::romp::ModelMErrorError(3);

          }
        }
      } while (0);
      if ((proc) != (dst)) {
        // GInvMsg[dst].Cmd := SACK;
        ::romp::Assignment<GINV_CMD>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (dst), ::romp::location{{2314,5},{2314,17}})).get</*Cmd*/0>()), (SACK), ::romp::location{{2314,5},{2314,29}});
        // GInvMsg[dst].Cluster := proc;
        ::romp::Assignment<Procss>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (dst), ::romp::location{{2315,5},{2315,17}})).get</*Cluster*/1>()), (proc), ::romp::location{{2315,5},{2315,33}});
      } else {
        // Undefine GInvMsg[dst];
        ((::romp::Element<Procss,GINV_MSG>((GInvMsg), (dst), ::romp::location{{2317,14},{2317,26}}))).Undefine();
        // GInvMsg[dst].Cmd := GINV_None;
        ::romp::Assignment<GINV_CMD>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (dst), ::romp::location{{2318,5},{2318,17}})).get</*Cmd*/0>()), (GINV_None), ::romp::location{{2318,5},{2318,34}});
      }
    } catch (...) { throw ::romp::ModelRuleError(47,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__RmtCluster_Recv_InvAck(const Rmt dst, const Procss src) const {
    try {
      return ((((::romp::Element<Procss,GINV_MSG>((GInvMsg), (src), ::romp::location{{2327,3},{2327,15}})).get</*Cmd*/0>()) == (SACK)) && (((::romp::Element<Procss,GINV_MSG>((GInvMsg), (src), ::romp::location{{2328,3},{2328,15}})).get</*Cluster*/1>()) == (dst)));
    } catch (...) { throw ::romp::ModelRuleError(48,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__RmtCluster_Recv_InvAck(const Rmt dst, const Procss src) {
    try {
      if (this->__rw__->assertion_handler(((src) != (dst)),103u)) throw ::romp::ModelPropertyError(103);

      do {
        __typeof__((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2333,10},{2333,20}})).get</*RAC*/10>()).get</*State*/0>())) res_ = (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2333,10},{2333,20}})).get</*RAC*/10>()).get</*State*/0>());
        if (res_ == (WRDX)) {
          // receive InvAck before reply from Dir
          // Procs[dst].RAC.InvCnt := (Procs[dst].RAC.InvCnt + 1);
          ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2336,5},{2336,15}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2336,30},{2336,40}})).get</*RAC*/10>()).get</*InvCnt*/1>()) + ((::romp::range_t)(1))), ::romp::location{{2336,5},{2336,55}});
        } else if (res_ == (WINV)) {
          // receive InvAck after reply from Dir
          // Procs[dst].RAC.InvCnt := (Procs[dst].RAC.InvCnt - 1);
          ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2340,5},{2340,15}})).get</*RAC*/10>()).get</*InvCnt*/1>()), ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2340,30},{2340,40}})).get</*RAC*/10>()).get</*InvCnt*/1>()) - ((::romp::range_t)(1))), ::romp::location{{2340,5},{2340,55}});
          // all InvAck received
          if ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2342,9},{2342,19}})).get</*RAC*/10>()).get</*InvCnt*/1>()) == ((::romp::range_t)(0))) {
            // Procs[dst].RAC.State := Inval;
            ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2343,7},{2343,17}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{2343,7},{2343,36}});
            // invariant purpose
            // Dir.Collecting := false;
            ::romp::Assignment<boolean>(((Dir).get</*Collecting*/7>()), (false), ::romp::location{{2345,7},{2345,30}});
          }
        } else {
          if (this->__rw__->error_handler(4u))
            throw ::romp::ModelMErrorError(4);

        }
      } while (0);
      // Undefine GInvMsg[src];
      ((::romp::Element<Procss,GINV_MSG>((GInvMsg), (src), ::romp::location{{2352,12},{2352,24}}))).Undefine();
      // GInvMsg[src].Cmd := GINV_None;
      ::romp::Assignment<GINV_CMD>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (src), ::romp::location{{2353,3},{2353,15}})).get</*Cmd*/0>()), (GINV_None), ::romp::location{{2353,3},{2353,32}});
    } catch (...) { throw ::romp::ModelRuleError(48,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__RmtCluster_Recv_IACK_X_(const Rmt dst) const {
    try {
      return ((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2361,3},{2361,15}})).get</*Cmd*/0>()) == (IACK)) || (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2362,3},{2362,15}})).get</*Cmd*/0>()) == (IACKX)));
    } catch (...) { throw ::romp::ModelRuleError(49,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__RmtCluster_Recv_IACK_X_(const Rmt dst) {
    try {
      NODE aux;
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2366,11},{2366,21}})).get</*RAC*/10>()).get</*State*/0>()) == (WRDX)),104u)) throw ::romp::ModelPropertyError(104);

      // Procs[dst].RAC.InvCnt := (GUniMsg[dst].InvCnt - Procs[dst].RAC.InvCnt);
      ::romp::Assignment<ClusterCnt>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2368,3},{2368,13}})).get</*RAC*/10>()).get</*InvCnt*/1>()), (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2368,28},{2368,40}})).get</*InvCnt*/2>()) - (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2368,50},{2368,60}})).get</*RAC*/10>()).get</*InvCnt*/1>())), ::romp::location{{2368,3},{2368,71}});
      // Procs[dst].L2.Data := GUniMsg[dst].Data;
      ::romp::Assignment<Datas>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2369,3},{2369,13}})).get</*L2*/9>()).get</*Data*/1>()), ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2369,25},{2369,37}})).get</*Data*/3>()), ::romp::location{{2369,3},{2369,42}});
      // Procs[dst].CurrData := GUniMsg[dst].Data;
      ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2370,3},{2370,13}})).get</*CurrData*/0>()), ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2370,26},{2370,38}})).get</*Data*/3>()), ::romp::location{{2370,3},{2370,43}});
      // Procs[dst].L2.State := Excl;
      ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2371,3},{2371,13}})).get</*L2*/9>()).get</*State*/0>()), (Excl), ::romp::location{{2371,3},{2371,30}});
      // Procs[dst].L2.OnlyCopy := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2372,3},{2372,13}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (true), ::romp::location{{2372,3},{2372,33}});
      if (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2373,7},{2373,19}})).get</*Cmd*/0>()) == (IACK)) {
        // Procs[dst].L2.Dirty := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2374,5},{2374,15}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{2374,5},{2374,33}});
      } else {
        // Procs[dst].L2.Dirty := true;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2376,5},{2376,15}})).get</*L2*/9>()).get</*Dirty*/3>()), (true), ::romp::location{{2376,5},{2376,32}});
      }
      // still wait for InvAck
      if ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2380,7},{2380,17}})).get</*RAC*/10>()).get</*InvCnt*/1>()) > ((::romp::range_t)(0))) {
        // Procs[dst].RAC.State := WINV;
        ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2381,6},{2381,16}})).get</*RAC*/10>()).get</*State*/0>()), (WINV), ::romp::location{{2381,6},{2381,34}});
      } else {
        // all InvAck received
        // Procs[dst].RAC.State := Inval;
        ::romp::Assignment<RACState>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2384,5},{2384,15}})).get</*RAC*/10>()).get</*State*/0>()), (Inval), ::romp::location{{2384,5},{2384,34}});
        // Dir.Collecting := false;
        ::romp::Assignment<boolean>(((Dir).get</*Collecting*/7>()), (false), ::romp::location{{2385,5},{2385,28}});
      }
      if (this->__rw__->assertion_handler((((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2388,11},{2388,21}})).get</*L2*/9>()).get</*pending*/2>()) == (true)) && (!((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2388,55},{2388,65}})).get</*L2*/9>()).get</*ReqId*/7>()).IsUndefined()))),105u)) throw ::romp::ModelPropertyError(105);

      if ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2390,7},{2390,17}})).get</*L2*/9>()).get</*InvCnt*/5>()) == ((::romp::range_t)(0))) {
        // Procs[dst].L2.pending := false;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2391,5},{2391,15}})).get</*L2*/9>()).get</*pending*/2>()), (false), ::romp::location{{2391,5},{2391,35}});
      }
      // aux := Procs[dst].L2.ReqId;
      ::romp::Assignment<NODE>((aux), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2393,10},{2393,20}})).get</*L2*/9>()).get</*ReqId*/7>()), ::romp::location{{2393,3},{2393,29}});
      // Procs[dst].UniMsg[aux].Cmd := UNI_PutX;
      ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2394,3},{2394,13}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2394,3},{2394,25}})).get</*Cmd*/0>()), (UNI_PutX), ::romp::location{{2394,3},{2394,41}});
      // Undefine Procs[dst].UniMsg[aux].Proc;
      (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2395,12},{2395,22}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2395,12},{2395,34}})).get</*Proc*/1>())).Undefine();
      // Procs[dst].UniMsg[aux].Data := Procs[dst].L2.Data;
      ::romp::Assignment<Datas>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2396,3},{2396,13}})).get</*UniMsg*/4>()), (aux), ::romp::location{{2396,3},{2396,25}})).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2396,34},{2396,44}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{2396,3},{2396,52}});
      // Procs[dst].L2.HeadPtr := aux;
      ::romp::Assignment<NODE_L2>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2397,3},{2397,13}})).get</*L2*/9>()).get</*HeadPtr*/6>()), (aux), ::romp::location{{2397,3},{2397,31}});
      // Undefine Procs[dst].L2.ReqId;
      ((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2398,12},{2398,22}})).get</*L2*/9>()).get</*ReqId*/7>())).Undefine();
      // Undefine GUniMsg[dst];
      ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2400,12},{2400,24}}))).Undefine();
      // GUniMsg[dst].Cmd := GUNI_None;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (dst), ::romp::location{{2401,3},{2401,15}})).get</*Cmd*/0>()), (GUNI_None), ::romp::location{{2401,3},{2401,32}});
      if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2403,11},{2403,21}})).get</*L2*/9>()).get</*isRetired*/12>()) == (false)),106u)) throw ::romp::ModelPropertyError(106);

      // Procs[dst].L2.isRetired := true;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (dst), ::romp::location{{2404,3},{2404,13}})).get</*L2*/9>()).get</*isRetired*/12>()), (true), ::romp::location{{2404,3},{2404,34}});
    } catch (...) { throw ::romp::ModelRuleError(49,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_Recv_RmtGet_Put(const Rmt r) const {
    try {
      return ((((((Dir).get</*State*/2>()) == (Invld)) || (((Dir).get</*State*/2>()) == (Shrd))) && (((Dir).get</*isBusy*/0>()) == (false))) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2415,3},{2415,13}})).get</*Cmd*/0>()) == (RD_H)));
    } catch (...) { throw ::romp::ModelRuleError(50,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Recv_RmtGet_Put(const Rmt r) {
    try {
      // Dir.State := Shrd;
      ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{2418,3},{2418,20}});
      // Dir.ShrSet[r] := true;
      ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (r), ::romp::location{{2419,3},{2419,16}})), (true), ::romp::location{{2419,3},{2419,24}});
      // GUniMsg[r].Cmd := ACK;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2421,3},{2421,13}})).get</*Cmd*/0>()), (ACK), ::romp::location{{2421,3},{2421,24}});
      // GUniMsg[r].Data := Dir.Mem;
      ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2422,3},{2422,13}})).get</*Data*/3>()), ((Dir).get</*Mem*/1>()), ::romp::location{{2422,3},{2422,29}});
      // Undefine GUniMsg[r].Cluster;
      (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2423,12},{2423,22}})).get</*Cluster*/1>())).Undefine();
      // GUniMsg[r].InvCnt := 0;
      ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2424,3},{2424,13}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2424,3},{2424,25}});
    } catch (...) { throw ::romp::ModelRuleError(50,::romp::ModelRuleError::ACTION); }
  }

  /*
   -- commenting this rule will in fact queue those requests coming to
   -- Dir when Dir is busy.
   ruleset r: Rmt do
   rule "Dir_Recv_RmtGet(X)_Nak"
   Dir.isBusy = true &
   (GUniMsg[r].Cmd = RD_H |
   GUniMsg[r].Cmd = RDX_H)
   ==>
   begin
   GUniMsg[r].Cmd := NAK;
   undefine GUniMsg[r].Data;
   undefine GUniMsg[r].Cluster;
   GUniMsg[r].InvCnt := 0;
   endrule;
   endruleset;
   */
  
  bool __romp__Rule_guard__Dir_Recv_RmtGet__RmtGet_(const Rmt r) const {
    try {
      return ((((((Dir).get</*State*/2>()) == (Excl)) && (((Dir).get</*isBusy*/0>()) == (false))) && (((Dir).get</*isLocal*/5>()) == (false))) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2453,3},{2453,13}})).get</*Cmd*/0>()) == (RD_H)));
    } catch (...) { throw ::romp::ModelRuleError(51,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Recv_RmtGet__RmtGet_(const Rmt r) {
    try {
      if (this->__rw__->assertion_handler((!(((Dir).get</*HeadPtr*/6>()).IsUndefined())),107u)) throw ::romp::ModelPropertyError(107);

      if (((Dir).get</*HeadPtr*/6>()) == (r)) {
        // GUniMsg[r].Cmd := ACK;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2458,5},{2458,15}})).get</*Cmd*/0>()), (ACK), ::romp::location{{2458,5},{2458,26}});
        // GUniMsg[r].Data := Dir.Mem;
        ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2459,5},{2459,15}})).get</*Data*/3>()), ((Dir).get</*Mem*/1>()), ::romp::location{{2459,5},{2459,31}});
        // Undefine GUniMsg[r].Cluster;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2460,14},{2460,24}})).get</*Cluster*/1>())).Undefine();
        // GUniMsg[r].InvCnt := 0;
        ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2461,5},{2461,15}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2461,5},{2461,27}});
        // Dir.State := Shrd;
        ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{2463,5},{2463,22}});
        // Dir.ShrSet[r] := true;
        ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (r), ::romp::location{{2464,5},{2464,18}})), (true), ::romp::location{{2464,5},{2464,26}});
        // Undefine Dir.HeadPtr;
        (((Dir).get</*HeadPtr*/6>())).Undefine();
      } else {
        // Dir.isBusy := true;
        ::romp::Assignment<boolean>(((Dir).get</*isBusy*/0>()), (true), ::romp::location{{2467,5},{2467,23}});
        // GUniMsg[r].Cmd := RD_RAC;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2468,5},{2468,15}})).get</*Cmd*/0>()), (RD_RAC), ::romp::location{{2468,5},{2468,29}});
        // Undefine GUniMsg[r].Data;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2469,14},{2469,24}})).get</*Data*/3>())).Undefine();
        // GUniMsg[r].Cluster := Dir.HeadPtr;
        ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2470,5},{2470,15}})).get</*Cluster*/1>()), ((Dir).get</*HeadPtr*/6>()), ::romp::location{{2470,5},{2470,38}});
        // Undefine GUniMsg[r].InvCnt;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2471,14},{2471,24}})).get</*InvCnt*/2>())).Undefine();
      }
    } catch (...) { throw ::romp::ModelRuleError(51,::romp::ModelRuleError::ACTION); }
  }

  // no need to ABS
  
  bool __romp__Rule_guard__Dir_Recv_RmtGetX__RmtGetX_(const Rmt r) const {
    try {
      return ((((((Dir).get</*State*/2>()) == (Excl)) && (((Dir).get</*isBusy*/0>()) == (false))) && (((Dir).get</*isLocal*/5>()) == (false))) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2484,3},{2484,13}})).get</*Cmd*/0>()) == (RDX_H)));
    } catch (...) { throw ::romp::ModelRuleError(52,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Recv_RmtGetX__RmtGetX_(const Rmt r) {
    try {
      if (((Dir).get</*HeadPtr*/6>()) == (r)) {
        // GUniMsg[r].Cmd := ACK;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2488,5},{2488,15}})).get</*Cmd*/0>()), (ACK), ::romp::location{{2488,5},{2488,26}});
        // GUniMsg[r].Data := Dir.Mem;
        ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2489,5},{2489,15}})).get</*Data*/3>()), ((Dir).get</*Mem*/1>()), ::romp::location{{2489,5},{2489,31}});
        // Undefine GUniMsg[r].Cluster;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2490,14},{2490,24}})).get</*Cluster*/1>())).Undefine();
        // GUniMsg[r].InvCnt := 0;
        ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2491,5},{2491,15}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2491,5},{2491,27}});
      } else {
        // Dir.isBusy := true;
        ::romp::Assignment<boolean>(((Dir).get</*isBusy*/0>()), (true), ::romp::location{{2493,5},{2493,23}});
        // GUniMsg[r].Cmd := RDX_RAC;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2494,5},{2494,15}})).get</*Cmd*/0>()), (RDX_RAC), ::romp::location{{2494,5},{2494,30}});
        // Undefine GUniMsg[r].Data;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2495,14},{2495,24}})).get</*Data*/3>())).Undefine();
        // GUniMsg[r].Cluster := Dir.HeadPtr;
        ::romp::Assignment<Procss>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2496,5},{2496,15}})).get</*Cluster*/1>()), ((Dir).get</*HeadPtr*/6>()), ::romp::location{{2496,5},{2496,38}});
        // Undefine GUniMsg[r].InvCnt;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2497,14},{2497,24}})).get</*InvCnt*/2>())).Undefine();
      }
    } catch (...) { throw ::romp::ModelRuleError(52,::romp::ModelRuleError::ACTION); }
  }

  // no need to ABS
  
  bool __romp__Rule_guard__Dir_Recv_RmtGetX_isLocal(const Rmt r) const {
    try {
      return (((((((Dir).get</*State*/2>()) == (Excl)) && (((Dir).get</*isBusy*/0>()) == (false))) && (((Dir).get</*isLocal*/5>()) == (true))) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2510,3},{2510,13}})).get</*Cmd*/0>()) == (RDX_H))) && ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2513,3},{2513,14}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(53,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Recv_RmtGetX_isLocal(const Rmt r) {
    try {
      // Apr 8
      CacheCnt iCnt;
      if (((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2517,7},{2517,18}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)) && ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2517,39},{2517,50}})).get</*L2*/9>()).get</*pending*/2>()) == (false))) {
        if ((!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2518,22},{2518,33}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2518,48},{2518,59}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) {
          // Procs[Home].L2.OnlyCopy := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2519,7},{2519,18}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{2519,7},{2519,39}});
          // Procs[Home].L2.State := Invld;
          ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2520,7},{2520,18}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{2520,7},{2520,36}});
          // GUniMsg[r].Data := Procs[Home].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2522,7},{2522,17}})).get</*Data*/3>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2522,26},{2522,37}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{2522,7},{2522,45}});
          // GUniMsg[r].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2523,7},{2523,17}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2523,7},{2523,29}});
          // Undefine GUniMsg[r].Cluster;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2524,16},{2524,26}})).get</*Cluster*/1>())).Undefine();
          if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2525,11},{2525,22}})).get</*L2*/9>()).get</*Dirty*/3>()) == (true)) {
            // GUniMsg[r].Cmd := IACKX;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2526,9},{2526,19}})).get</*Cmd*/0>()), (IACKX), ::romp::location{{2526,9},{2526,32}});
          } else {
            // GUniMsg[r].Cmd := IACK;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2528,9},{2528,19}})).get</*Cmd*/0>()), (IACK), ::romp::location{{2528,9},{2528,31}});
          }
          // Procs[Home].L2.Dirty := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2531,7},{2531,18}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{2531,7},{2531,36}});
          // Undefine Procs[Home].L2.HeadPtr;
          ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2532,16},{2532,27}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
          // Undefine Procs[Home].L2.Data;
          ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2533,16},{2533,27}})).get</*L2*/9>()).get</*Data*/1>())).Undefine();
          // Undefine Procs[Home].CurrData;
          (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2534,16},{2534,27}})).get</*CurrData*/0>())).Undefine();
          // Undefine Procs[Home].PrevData;
          (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2535,16},{2535,27}})).get</*PrevData*/1>())).Undefine();
          // Dir.isLocal := false;
          ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (false), ::romp::location{{2536,7},{2536,27}});
          // Dir.HeadPtr := r;
          ::romp::Assignment<Procss>(((Dir).get</*HeadPtr*/6>()), (r), ::romp::location{{2537,7},{2537,23}});
        } else if ((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2539,12},{2539,23}})).get</*L2*/9>()).get</*State*/0>()) == (Excl)) && (!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2539,55},{2539,66}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined()))) && ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2540,5},{2540,16}})).get</*L2*/9>()).get</*HeadPtr*/6>()) != (L2))) {
          // Procs[Home].L2.pending := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2541,7},{2541,18}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{2541,7},{2541,37}});
          // Procs[Home].UniMsg[L2].Cmd := UNI_GetX;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2542,7},{2542,18}})).get</*UniMsg*/4>()), (L2), ::romp::location{{2542,7},{2542,29}})).get</*Cmd*/0>()), (UNI_GetX), ::romp::location{{2542,7},{2542,45}});
          // Procs[Home].UniMsg[L2].Proc := Procs[Home].L2.HeadPtr;
          ::romp::Assignment<NODE_L2>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2543,7},{2543,18}})).get</*UniMsg*/4>()), (L2), ::romp::location{{2543,7},{2543,29}})).get</*Proc*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2543,38},{2543,49}})).get</*L2*/9>()).get</*HeadPtr*/6>()), ::romp::location{{2543,7},{2543,60}});
          // Undefine Procs[Home].UniMsg[L2].Data;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2544,16},{2544,27}})).get</*UniMsg*/4>()), (L2), ::romp::location{{2544,16},{2544,38}})).get</*Data*/2>())).Undefine();
          // Procs[Home].L2.ReqCluster := r;
          ::romp::Assignment<Procss>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2546,7},{2546,18}})).get</*L2*/9>()).get</*ReqCluster*/9>()), (r), ::romp::location{{2546,7},{2546,37}});
          // Procs[Home].L2.ReqType := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2547,7},{2547,18}})).get</*L2*/9>()).get</*ReqType*/10>()), (false), ::romp::location{{2547,7},{2547,38}});
          // Apr 8
          // undefine GUniMsg[r];
          // GUniMsg[r].Cmd := GUNI_None;
          // Procs[Home].L2.ifHoldMsg := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2552,7},{2552,18}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()), (true), ::romp::location{{2552,7},{2552,39}});
        } else if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2555,12},{2555,23}})).get</*L2*/9>()).get</*State*/0>()) == (Shrd)) {
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2556,15},{2556,26}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (true)),108u)) throw ::romp::ModelPropertyError(108);

          // Procs[Home].L2.pending := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2557,7},{2557,18}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{2557,7},{2557,37}});
          // iCnt := 0;
          ::romp::Assignment<CacheCnt>((iCnt), ((::romp::range_t)(0)), ::romp::location{{2558,7},{2558,16}});
          for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) {
            if ((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2560,13},{2560,24}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{2560,13},{2560,37}})) == (true)) {
              // Procs[Home].InvMsg[n].Cmd := INV_Inv;
              ::romp::Assignment<INV_CMD>(((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2561,11},{2561,22}})).get</*InvMsg*/5>()), (n), ::romp::location{{2561,11},{2561,32}})).get</*Cmd*/0>()), (INV_Inv), ::romp::location{{2561,11},{2561,47}});
              // iCnt := (iCnt + 1);
              ::romp::Assignment<CacheCnt>((iCnt), ((iCnt) + ((::romp::range_t)(1))), ::romp::location{{2562,11},{2562,27}});
              // Procs[Home].L2.ShrSet[n] := false;
              ::romp::Assignment<boolean>((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2563,11},{2563,22}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{2563,11},{2563,35}})), (false), ::romp::location{{2563,11},{2563,44}});
            }
          }

          // Procs[Home].L2.InvCnt := iCnt;
          ::romp::Assignment<CacheCnt>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2566,7},{2566,18}})).get</*L2*/9>()).get</*InvCnt*/5>()), (iCnt), ::romp::location{{2566,7},{2566,36}});
          // Procs[Home].PrevData := Procs[Home].CurrData;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2567,7},{2567,18}})).get</*PrevData*/1>()), ((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2567,31},{2567,42}})).get</*CurrData*/0>()), ::romp::location{{2567,7},{2567,51}});
          // Procs[Home].Collecting := true;
          ::romp::Assignment<boolean>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2568,7},{2568,18}})).get</*Collecting*/2>()), (true), ::romp::location{{2568,7},{2568,37}});
          // GUniMsg[r].Data := Procs[Home].L2.Data;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2570,7},{2570,17}})).get</*Data*/3>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2570,26},{2570,37}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{2570,7},{2570,45}});
          // GUniMsg[r].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2571,7},{2571,17}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2571,7},{2571,29}});
          // Undefine GUniMsg[r].Cluster;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2572,16},{2572,26}})).get</*Cluster*/1>())).Undefine();
          if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2573,11},{2573,22}})).get</*L2*/9>()).get</*Dirty*/3>()) == (true)) {
            // GUniMsg[r].Cmd := IACKX;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2574,9},{2574,19}})).get</*Cmd*/0>()), (IACKX), ::romp::location{{2574,9},{2574,32}});
          } else {
            // GUniMsg[r].Cmd := IACK;
            ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2576,9},{2576,19}})).get</*Cmd*/0>()), (IACK), ::romp::location{{2576,9},{2576,31}});
          }
          // Procs[Home].L2.State := Invld;
          ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2579,7},{2579,18}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{2579,7},{2579,36}});
          // Procs[Home].L2.OnlyCopy := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2580,7},{2580,18}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{2580,7},{2580,39}});
          // Procs[Home].L2.Dirty := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2581,7},{2581,18}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{2581,7},{2581,36}});
          // Undefine Procs[Home].L2.Data;
          ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2582,16},{2582,27}})).get</*L2*/9>()).get</*Data*/1>())).Undefine();
          // Dir.isLocal := false;
          ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (false), ::romp::location{{2583,7},{2583,27}});
          // Dir.HeadPtr := r;
          ::romp::Assignment<Procss>(((Dir).get</*HeadPtr*/6>()), (r), ::romp::location{{2584,7},{2584,23}});
        } else {
          // GUniMsg[r].Data := Dir.Mem;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2587,7},{2587,17}})).get</*Data*/3>()), ((Dir).get</*Mem*/1>()), ::romp::location{{2587,7},{2587,33}});
          // GUniMsg[r].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2588,7},{2588,17}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2588,7},{2588,29}});
          // Undefine GUniMsg[r].Cluster;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2589,16},{2589,26}})).get</*Cluster*/1>())).Undefine();
          // GUniMsg[r].Cmd := IACK;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2590,7},{2590,17}})).get</*Cmd*/0>()), (IACK), ::romp::location{{2590,7},{2590,29}});
          // Dir.isLocal := false;
          ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (false), ::romp::location{{2592,7},{2592,27}});
          // Dir.HeadPtr := r;
          ::romp::Assignment<Procss>(((Dir).get</*HeadPtr*/6>()), (r), ::romp::location{{2593,7},{2593,23}});
        }
      } else {
        // home busy
        // Undefine GUniMsg[r].Data;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2599,14},{2599,24}})).get</*Data*/3>())).Undefine();
        // Undefine GUniMsg[r].InvCnt;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2600,14},{2600,24}})).get</*InvCnt*/2>())).Undefine();
        // Undefine GUniMsg[r].Cluster;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2601,14},{2601,24}})).get</*Cluster*/1>())).Undefine();
        // GUniMsg[r].Cmd := NAK;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2602,5},{2602,15}})).get</*Cmd*/0>()), (NAK), ::romp::location{{2602,5},{2602,26}});
      }
    } catch (...) { throw ::romp::ModelRuleError(53,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_Recv_RmtGet_isLocal(const Rmt r) const {
    try {
      return (((((((Dir).get</*State*/2>()) == (Excl)) && (((Dir).get</*isBusy*/0>()) == (false))) && (((Dir).get</*isLocal*/5>()) == (true))) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2614,3},{2614,13}})).get</*Cmd*/0>()) == (RD_H))) && ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2617,3},{2617,14}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(54,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Recv_RmtGet_isLocal(const Rmt r) {
    try {
      // Apr 8
      if (((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2620,7},{2620,18}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)) && ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2620,39},{2620,50}})).get</*L2*/9>()).get</*pending*/2>()) == (false))) {
        if ((!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2621,22},{2621,33}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2621,48},{2621,59}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) {
          // Procs[Home].L2.State := Shrd;
          ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2622,7},{2622,18}})).get</*L2*/9>()).get</*State*/0>()), (Shrd), ::romp::location{{2622,7},{2622,35}});
          // Procs[Home].L2.OnlyCopy := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2623,7},{2623,18}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{2623,7},{2623,39}});
          // Procs[Home].L2.Dirty := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2624,7},{2624,18}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{2624,7},{2624,36}});
          // Dir.State := Shrd;
          ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{2625,7},{2625,24}});
          // Dir.Mem := Procs[Home].L2.Data;
          ::romp::Assignment<Datas>(((Dir).get</*Mem*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2626,18},{2626,29}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{2626,7},{2626,37}});
          // Dir.CurrData := Procs[Home].L2.Data;
          // GUniMsg[r].Cmd := ACK;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2628,7},{2628,17}})).get</*Cmd*/0>()), (ACK), ::romp::location{{2628,7},{2628,28}});
          // GUniMsg[r].Data := Dir.Mem;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2629,7},{2629,17}})).get</*Data*/3>()), ((Dir).get</*Mem*/1>()), ::romp::location{{2629,7},{2629,33}});
          // GUniMsg[r].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2630,7},{2630,17}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2630,7},{2630,29}});
          // Undefine GUniMsg[r].Cluster;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2631,16},{2631,26}})).get</*Cluster*/1>())).Undefine();
          // Dir.ShrSet[r] := true;
          ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (r), ::romp::location{{2632,7},{2632,20}})), (true), ::romp::location{{2632,7},{2632,28}});
        } else if ((((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2634,12},{2634,23}})).get</*L2*/9>()).get</*State*/0>()) == (Excl)) && (!((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2634,55},{2634,66}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined()))) && ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2635,5},{2635,16}})).get</*L2*/9>()).get</*HeadPtr*/6>()) != (L2))) {
          // Procs[Home].L2.pending := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2636,7},{2636,18}})).get</*L2*/9>()).get</*pending*/2>()), (true), ::romp::location{{2636,7},{2636,37}});
          // Procs[Home].UniMsg[L2].Cmd := UNI_Get;
          ::romp::Assignment<UNI_CMD>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2637,7},{2637,18}})).get</*UniMsg*/4>()), (L2), ::romp::location{{2637,7},{2637,29}})).get</*Cmd*/0>()), (UNI_Get), ::romp::location{{2637,7},{2637,44}});
          // Procs[Home].UniMsg[L2].Proc := Procs[Home].L2.HeadPtr;
          ::romp::Assignment<NODE_L2>(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2638,7},{2638,18}})).get</*UniMsg*/4>()), (L2), ::romp::location{{2638,7},{2638,29}})).get</*Proc*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2638,38},{2638,49}})).get</*L2*/9>()).get</*HeadPtr*/6>()), ::romp::location{{2638,7},{2638,60}});
          // Undefine Procs[Home].UniMsg[L2].Data;
          (((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2639,16},{2639,27}})).get</*UniMsg*/4>()), (L2), ::romp::location{{2639,16},{2639,38}})).get</*Data*/2>())).Undefine();
          // Procs[Home].L2.ReqCluster := r;
          ::romp::Assignment<Procss>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2641,7},{2641,18}})).get</*L2*/9>()).get</*ReqCluster*/9>()), (r), ::romp::location{{2641,7},{2641,37}});
          // Procs[Home].L2.ReqType := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2642,7},{2642,18}})).get</*L2*/9>()).get</*ReqType*/10>()), (true), ::romp::location{{2642,7},{2642,37}});
          // Apr 8
          // undefine GUniMsg[r];
          // GUniMsg[r].Cmd := GUNI_None;
          // Procs[Home].L2.ifHoldMsg := true;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2648,7},{2648,18}})).get</*L2*/9>()).get</*ifHoldMsg*/13>()), (true), ::romp::location{{2648,7},{2648,39}});
        } else if ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2651,12},{2651,23}})).get</*L2*/9>()).get</*State*/0>()) == (Shrd)) {
          if (this->__rw__->assertion_handler(((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2652,15},{2652,26}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (true)),109u)) throw ::romp::ModelPropertyError(109);

          // Procs[Home].L2.OnlyCopy := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2653,7},{2653,18}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{2653,7},{2653,39}});
          // Procs[Home].L2.Dirty := false;
          ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2654,7},{2654,18}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{2654,7},{2654,36}});
          // Dir.Mem := Procs[Home].L2.Data;
          ::romp::Assignment<Datas>(((Dir).get</*Mem*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{2655,18},{2655,29}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{2655,7},{2655,37}});
          // Dir.CurrData := Procs[Home].L2.Data;
          // Dir.ShrSet[r] := true;
          ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (r), ::romp::location{{2657,7},{2657,20}})), (true), ::romp::location{{2657,7},{2657,28}});
          // Dir.State := Shrd;
          ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{2658,7},{2658,24}});
          // GUniMsg[r].Cmd := ACK;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2660,7},{2660,17}})).get</*Cmd*/0>()), (ACK), ::romp::location{{2660,7},{2660,28}});
          // GUniMsg[r].Data := Dir.Mem;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2661,7},{2661,17}})).get</*Data*/3>()), ((Dir).get</*Mem*/1>()), ::romp::location{{2661,7},{2661,33}});
          // GUniMsg[r].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2662,7},{2662,17}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2662,7},{2662,29}});
          // Undefine GUniMsg[r].Cluster;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2663,16},{2663,26}})).get</*Cluster*/1>())).Undefine();
        } else {
          // Dir.isLocal := false;
          ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (false), ::romp::location{{2666,7},{2666,27}});
          // Dir.State := Shrd;
          ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Shrd), ::romp::location{{2667,7},{2667,24}});
          // Dir.ShrSet[r] := true;
          ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (r), ::romp::location{{2668,7},{2668,20}})), (true), ::romp::location{{2668,7},{2668,28}});
          // GUniMsg[r].Cmd := ACK;
          ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2669,7},{2669,17}})).get</*Cmd*/0>()), (ACK), ::romp::location{{2669,7},{2669,28}});
          // GUniMsg[r].Data := Dir.Mem;
          ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2670,7},{2670,17}})).get</*Data*/3>()), ((Dir).get</*Mem*/1>()), ::romp::location{{2670,7},{2670,33}});
          // GUniMsg[r].InvCnt := 0;
          ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2671,7},{2671,17}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2671,7},{2671,29}});
          // Undefine GUniMsg[r].Cluster;
          (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2672,16},{2672,26}})).get</*Cluster*/1>())).Undefine();
        }
      } else {
        // home busy
        // GUniMsg[r].Cmd := NAK;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2678,5},{2678,15}})).get</*Cmd*/0>()), (NAK), ::romp::location{{2678,5},{2678,26}});
        // Undefine GUniMsg[r].Data;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2679,14},{2679,24}})).get</*Data*/3>())).Undefine();
        // Undefine GUniMsg[r].InvCnt;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2680,14},{2680,24}})).get</*InvCnt*/2>())).Undefine();
        // Undefine GUniMsg[r].Cluster;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2681,14},{2681,24}})).get</*Cluster*/1>())).Undefine();
      }
    } catch (...) { throw ::romp::ModelRuleError(54,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_Recv_RmtGetX_PutX(const Rmt r) const {
    try {
      return (((((Dir).get</*State*/2>()) == (Invld)) && (((Dir).get</*isBusy*/0>()) == (false))) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2692,3},{2692,13}})).get</*Cmd*/0>()) == (RDX_H)));
    } catch (...) { throw ::romp::ModelRuleError(55,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Recv_RmtGetX_PutX(const Rmt r) {
    try {
      // Dir.State := Excl;
      ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Excl), ::romp::location{{2695,3},{2695,20}});
      // Dir.HeadPtr := r;
      ::romp::Assignment<Procss>(((Dir).get</*HeadPtr*/6>()), (r), ::romp::location{{2696,3},{2696,19}});
      if (this->__rw__->assertion_handler((((Dir).get</*isLocal*/5>()) == (false)),110u)) throw ::romp::ModelPropertyError(110);

      // GUniMsg[r].Cmd := ACK;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2699,3},{2699,13}})).get</*Cmd*/0>()), (ACK), ::romp::location{{2699,3},{2699,24}});
      // GUniMsg[r].InvCnt := 0;
      ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2700,3},{2700,13}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2700,3},{2700,25}});
      // GUniMsg[r].Data := Dir.Mem;
      ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2701,3},{2701,13}})).get</*Data*/3>()), ((Dir).get</*Mem*/1>()), ::romp::location{{2701,3},{2701,29}});
      // Undefine GUniMsg[r].Cluster;
      (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2702,12},{2702,22}})).get</*Cluster*/1>())).Undefine();
    } catch (...) { throw ::romp::ModelRuleError(55,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Cluster_WriteBack(const Procss p) const {
    try {
      return ((((((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2710,3},{2710,11}})).get</*L2*/9>()).get</*State*/0>()) == (Excl)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2711,3},{2711,11}})).get</*L2*/9>()).get</*Dirty*/3>()) == (true))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2712,3},{2712,11}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2713,3},{2713,11}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2714,3},{2714,11}})).get</*L2*/9>()).get</*pending*/2>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(56,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Cluster_WriteBack(const Procss p) {
    try {
      for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) {
        if (this->__rw__->assertion_handler(((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2718,13},{2718,21}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{2718,13},{2718,34}})) == (false)),111u)) throw ::romp::ModelPropertyError(111);

      }

      // Undefine Procs[p].L2.HeadPtr;
      ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2721,12},{2721,20}})).get</*L2*/9>()).get</*HeadPtr*/6>())).Undefine();
      // Procs[p].L2.State := Invld;
      ::romp::Assignment<L2State>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2722,3},{2722,11}})).get</*L2*/9>()).get</*State*/0>()), (Invld), ::romp::location{{2722,3},{2722,29}});
      // Procs[p].L2.OnlyCopy := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2723,3},{2723,11}})).get</*L2*/9>()).get</*OnlyCopy*/8>()), (false), ::romp::location{{2723,3},{2723,32}});
      // Procs[p].L2.Dirty := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2724,3},{2724,11}})).get</*L2*/9>()).get</*Dirty*/3>()), (false), ::romp::location{{2724,3},{2724,29}});
      if ((p) == (Home)) {
        // Dir.isLocal := false;
        ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (false), ::romp::location{{2726,5},{2726,25}});
        // Dir.Mem := Procs[p].L2.Data;
        ::romp::Assignment<Datas>(((Dir).get</*Mem*/1>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2727,16},{2727,24}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{2727,5},{2727,32}});
        // Dir.CurrData := Procs[p].L2.Data;
        // Dir.State := Invld;
        ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Invld), ::romp::location{{2729,5},{2729,23}});
      } else {
        // Procs[p].L2.Gblock_WB := true;
        ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2731,5},{2731,13}})).get</*L2*/9>()).get</*Gblock_WB*/11>()), (true), ::romp::location{{2731,5},{2731,34}});
        // GWbMsg.Cmd := WB;
        ::romp::Assignment<GWB_CMD>(((GWbMsg).get</*Cmd*/0>()), (WB), ::romp::location{{2732,5},{2732,21}});
        // GWbMsg.Cluster := p;
        ::romp::Assignment<Procss>(((GWbMsg).get</*Cluster*/1>()), (p), ::romp::location{{2733,5},{2733,24}});
        // GWbMsg.Data := Procs[p].L2.Data;
        ::romp::Assignment<Datas>(((GWbMsg).get</*Data*/2>()), (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2734,20},{2734,28}})).get</*L2*/9>()).get</*Data*/1>()), ::romp::location{{2734,5},{2734,36}});
      }
      // Undefine Procs[p].L2.Data;
      ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2736,12},{2736,20}})).get</*L2*/9>()).get</*Data*/1>())).Undefine();
      // invariant purpose
      // Undefine Procs[p].PrevData;
      (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2739,12},{2739,20}})).get</*PrevData*/1>())).Undefine();
      // Undefine Procs[p].CurrData;
      (((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2740,12},{2740,20}})).get</*CurrData*/0>())).Undefine();
    } catch (...) { throw ::romp::ModelRuleError(56,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_Recv_WB(void) const {
    try {
      return (((GWbMsg).get</*Cmd*/0>()) == (WB));
    } catch (...) { throw ::romp::ModelRuleError(57,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Recv_WB(void) {
    try {
      /*
       -- cannot assert the following:
       assert (Dir.State = Excl & Dir.HeadPtr = r & Dir.isLocal = false) 
       "Writeback with funny directory state.";
       -- counterexample:
       Rmt_Send_GetX, r:Rmt_1
       Dir_RmtGetX_PutX, r:Rmt_1
       Rmt_Send_GetX, r:Rmt_2
       Dir_RmtGetX_(RmtGetX), r:Rmt_2
       RmtCluster_Recv_ACK, dst:Rmt_1
       Cluster_Update_Data, d:Datas_1, p:Rmt_1
       RmtCluster_Recv_GetX, dst:Rmt_1
       RmtCluster_Recv_IACK, dst:Rmt_2
       Cluster_WriteBack, p:Rmt_2
       */
      if (this->__rw__->assertion_handler((((((Dir).get</*State*/2>()) == (Excl)) && (!(((Dir).get</*HeadPtr*/6>()).IsUndefined()))) && (((Dir).get</*isLocal*/5>()) == (false))),112u)) throw ::romp::ModelPropertyError(112);

      // Dir.State := Invld;
      ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Invld), ::romp::location{{2766,3},{2766,21}});
      // Undefine Dir.HeadPtr;
      (((Dir).get</*HeadPtr*/6>())).Undefine();
      // Dir.Mem := GWbMsg.Data;
      ::romp::Assignment<Datas>(((Dir).get</*Mem*/1>()), ((GWbMsg).get</*Data*/2>()), ::romp::location{{2768,3},{2768,25}});
      // GUniMsg[GWbMsg.Cluster].Cmd := WB_Ack;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), ((GWbMsg).get</*Cluster*/1>()), ::romp::location{{2770,3},{2770,26}})).get</*Cmd*/0>()), (WB_Ack), ::romp::location{{2770,3},{2770,40}});
      // Undefine GUniMsg[GWbMsg.Cluster].Data;
      (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), ((GWbMsg).get</*Cluster*/1>()), ::romp::location{{2771,12},{2771,35}})).get</*Data*/3>())).Undefine();
      // Undefine GUniMsg[GWbMsg.Cluster].Cluster;
      (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), ((GWbMsg).get</*Cluster*/1>()), ::romp::location{{2772,12},{2772,35}})).get</*Cluster*/1>())).Undefine();
      // Undefine GUniMsg[GWbMsg.Cluster].InvCnt;
      (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), ((GWbMsg).get</*Cluster*/1>()), ::romp::location{{2773,12},{2773,35}})).get</*InvCnt*/2>())).Undefine();
      // Undefine GWbMsg;
      ((GWbMsg)).Undefine();
      // GWbMsg.Cmd := GWB_None;
      ::romp::Assignment<GWB_CMD>(((GWbMsg).get</*Cmd*/0>()), (GWB_None), ::romp::location{{2776,3},{2776,25}});
    } catch (...) { throw ::romp::ModelRuleError(57,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__RmtCluster_Recv_WBAck(const Rmt r) const {
    try {
      return (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2782,3},{2782,13}})).get</*Cmd*/0>()) == (WB_Ack));
    } catch (...) { throw ::romp::ModelRuleError(58,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__RmtCluster_Recv_WBAck(const Rmt r) {
    try {
      if (this->__rw__->assertion_handler((((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{2785,11},{2785,19}})).get</*L2*/9>()).get</*Gblock_WB*/11>()) == (true)) && ((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{2785,42},{2785,50}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval))),113u)) throw ::romp::ModelPropertyError(113);

      // Procs[r].L2.Gblock_WB := false;
      ::romp::Assignment<boolean>((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{2787,3},{2787,11}})).get</*L2*/9>()).get</*Gblock_WB*/11>()), (false), ::romp::location{{2787,3},{2787,33}});
      // Undefine GUniMsg[r];
      ((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2788,12},{2788,22}}))).Undefine();
      // GUniMsg[r].Cmd := GUNI_None;
      ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2789,3},{2789,13}})).get</*Cmd*/0>()), (GUNI_None), ::romp::location{{2789,3},{2789,30}});
    } catch (...) { throw ::romp::ModelRuleError(58,::romp::ModelRuleError::ACTION); }
  }

  
  bool __romp__Rule_guard__Dir_Shrd_RmtGetX_PutX(const Rmt r) const {
    try {
      return (((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2797,3},{2797,13}})).get</*Cmd*/0>()) == (RDX_H)) && (((Dir).get</*State*/2>()) == (Shrd))) && (((Dir).get</*isBusy*/0>()) == (false)));
    } catch (...) { throw ::romp::ModelRuleError(59,::romp::ModelRuleError::GUARD); }
  }

  
  void __romp__Rule_action__Dir_Shrd_RmtGetX_PutX(const Rmt r) {
    try {
      ClusterCnt ShrCnt;
      // Dir.ShrSet[r] := false;
      // ShrCnt := 0;
      ::romp::Assignment<ClusterCnt>((ShrCnt), ((::romp::range_t)(0)), ::romp::location{{2804,3},{2804,14}});
      if (((Dir).get</*isLocal*/5>()) == (true)) {
        // ShrCnt := 1;
        ::romp::Assignment<ClusterCnt>((ShrCnt), ((::romp::range_t)(1)), ::romp::location{{2806,5},{2806,16}});
        // GInvMsg[Home].Cmd := INV;
        ::romp::Assignment<GINV_CMD>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (Home), ::romp::location{{2807,5},{2807,18}})).get</*Cmd*/0>()), (INV), ::romp::location{{2807,5},{2807,29}});
        // GInvMsg[Home].Cluster := r;
        ::romp::Assignment<Procss>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (Home), ::romp::location{{2808,5},{2808,18}})).get</*Cluster*/1>()), (r), ::romp::location{{2808,5},{2808,31}});
        // Dir.Collecting := true;
        ::romp::Assignment<boolean>(((Dir).get</*Collecting*/7>()), (true), ::romp::location{{2809,5},{2809,27}});
        // Dir.PrevData := Dir.CurrData;
        ::romp::Assignment<Datas>(((Dir).get</*PrevData*/9>()), ((Dir).get</*CurrData*/8>()), ::romp::location{{2810,5},{2810,33}});
        // Dir.isLocal := false;
        ::romp::Assignment<boolean>(((Dir).get</*isLocal*/5>()), (false), ::romp::location{{2811,5},{2811,25}});
      }
      // Dir.State := Excl;
      ::romp::Assignment<L2State>(((Dir).get</*State*/2>()), (Excl), ::romp::location{{2814,3},{2814,20}});
      // Dir.HeadPtr := r;
      ::romp::Assignment<Procss>(((Dir).get</*HeadPtr*/6>()), (r), ::romp::location{{2815,3},{2815,19}});
      // only r is in the sharer list
      if (((ShrCnt) == ((::romp::range_t)(0))) && ({bool res_ = true; for (auto i=Rmt::__LB(); i!=Rmt::__UB(); i.__step()) { res_ &= (!((i) != (r)) || ((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (i), ::romp::location{{2819,34},{2819,47}})) == (false))); } res_; })) {
        // GUniMsg[r].Cmd := ACK;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2820,5},{2820,15}})).get</*Cmd*/0>()), (ACK), ::romp::location{{2820,5},{2820,26}});
        // GUniMsg[r].Data := Dir.Mem;
        ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2821,5},{2821,15}})).get</*Data*/3>()), ((Dir).get</*Mem*/1>()), ::romp::location{{2821,5},{2821,31}});
        // GUniMsg[r].InvCnt := 0;
        ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2822,5},{2822,15}})).get</*InvCnt*/2>()), ((::romp::range_t)(0)), ::romp::location{{2822,5},{2822,27}});
        // Undefine GUniMsg[r].Cluster;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2823,14},{2823,24}})).get</*Cluster*/1>())).Undefine();
      } else {
        for (auto p=Rmt::__LB(); p!=Rmt::__UB(); p.__step()) {
          if ((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (p), ::romp::location{{2827,11},{2827,24}})) == (true)) {
            // ShrCnt := (ShrCnt + 1);
            ::romp::Assignment<ClusterCnt>((ShrCnt), ((ShrCnt) + ((::romp::range_t)(1))), ::romp::location{{2828,9},{2828,29}});
            // Dir.ShrSet[p] := false;
            ::romp::Assignment<boolean>((::romp::Element<Procss,boolean>(((Dir).get</*ShrSet*/3>()), (p), ::romp::location{{2829,9},{2829,22}})), (false), ::romp::location{{2829,9},{2829,31}});
            // GInvMsg[p].Cmd := INV;
            ::romp::Assignment<GINV_CMD>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (p), ::romp::location{{2830,9},{2830,19}})).get</*Cmd*/0>()), (INV), ::romp::location{{2830,9},{2830,30}});
            // GInvMsg[p].Cluster := r;
            ::romp::Assignment<Procss>(((::romp::Element<Procss,GINV_MSG>((GInvMsg), (p), ::romp::location{{2831,9},{2831,19}})).get</*Cluster*/1>()), (r), ::romp::location{{2831,9},{2831,32}});
            // invariant purpose
            // Dir.Collecting := true;
            ::romp::Assignment<boolean>(((Dir).get</*Collecting*/7>()), (true), ::romp::location{{2834,9},{2834,31}});
            // Dir.PrevData := Dir.CurrData;
            ::romp::Assignment<Datas>(((Dir).get</*PrevData*/9>()), ((Dir).get</*CurrData*/8>()), ::romp::location{{2835,9},{2835,37}});
          }
        }

        // GUniMsg[r].Cmd := IACK;
        ::romp::Assignment<GUNI_CMD>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2838,5},{2838,15}})).get</*Cmd*/0>()), (IACK), ::romp::location{{2838,5},{2838,27}});
        // GUniMsg[r].Data := Dir.Mem;
        ::romp::Assignment<Datas>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2839,5},{2839,15}})).get</*Data*/3>()), ((Dir).get</*Mem*/1>()), ::romp::location{{2839,5},{2839,31}});
        // GUniMsg[r].InvCnt := ShrCnt;
        ::romp::Assignment<ClusterCnt>(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2840,5},{2840,15}})).get</*InvCnt*/2>()), (ShrCnt), ::romp::location{{2840,5},{2840,32}});
        // Undefine GUniMsg[r].Cluster;
        (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (r), ::romp::location{{2841,14},{2841,24}})).get</*Cluster*/1>())).Undefine();
      }
    } catch (...) { throw ::romp::ModelRuleError(59,::romp::ModelRuleError::ACTION); }
  }

  //-----------------------------------------------------------------------------
  //---- inside a cluster ------
  
  bool __romp__Property__CacheStateProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= ({bool res_ = true; for (auto n1=NODE::__LB(); n1!=NODE::__UB(); n1.__step()) { res_ &= ({bool res_ = true; for (auto n2=NODE::__LB(); n2!=NODE::__UB(); n2.__step()) { res_ &= (!((n1) != (n2)) || (!(((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2854,8},{2854,16}})).get</*Proc*/3>()), (n1), ::romp::location{{2854,8},{2854,25}})).get</*CacheState*/2>()) == (CACHE_E)) || (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2855,8},{2855,16}})).get</*Proc*/3>()), (n1), ::romp::location{{2855,8},{2855,25}})).get</*CacheState*/2>()) == (CACHE_M))) && ((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2856,8},{2856,16}})).get</*Proc*/3>()), (n2), ::romp::location{{2856,8},{2856,25}})).get</*CacheState*/2>()) == (CACHE_E)) || (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2857,8},{2857,16}})).get</*Proc*/3>()), (n2), ::romp::location{{2857,8},{2857,25}})).get</*CacheState*/2>()) == (CACHE_M)))))); } res_; }); } res_; }); } res_; }),114u);
    } catch (...) { throw ::romp::ModelPropertyError(114); }
  }

  
  bool __romp__Property__CacheDataProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= ({bool res_ = true; for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) { res_ &= ((!((((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2864,7},{2864,15}})).get</*Proc*/3>()), (n), ::romp::location{{2864,7},{2864,23}})).get</*CacheState*/2>()) == (CACHE_E)) || (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2865,7},{2865,15}})).get</*Proc*/3>()), (n), ::romp::location{{2865,7},{2865,23}})).get</*CacheState*/2>()) == (CACHE_M))) || (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2867,6},{2867,14}})).get</*Proc*/3>()), (n), ::romp::location{{2867,6},{2867,22}})).get</*CacheData*/3>()) == ((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2867,35},{2867,43}})).get</*CurrData*/0>()))) && (!(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2868,6},{2868,14}})).get</*Proc*/3>()), (n), ::romp::location{{2868,6},{2868,22}})).get</*CacheState*/2>()) == (CACHE_S)) || ((!((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2869,8},{2869,16}})).get</*Collecting*/2>()) || (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2869,31},{2869,39}})).get</*Proc*/3>()), (n), ::romp::location{{2869,31},{2869,47}})).get</*CacheData*/3>()) == ((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2869,60},{2869,68}})).get</*PrevData*/1>()))) && (!(!((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2870,9},{2870,17}})).get</*Collecting*/2>())) || (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2870,32},{2870,40}})).get</*Proc*/3>()), (n), ::romp::location{{2870,32},{2870,48}})).get</*CacheData*/3>()) == ((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2870,61},{2870,69}})).get</*CurrData*/0>())))))); } res_; }); } res_; }),115u);
    } catch (...) { throw ::romp::ModelPropertyError(115); }
  }

  
  bool __romp__Property__OnlyCopyProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2876,5},{2876,13}})).get</*L2*/9>()).get</*Dirty*/3>()) == (true)) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2876,32},{2876,40}})).get</*L2*/9>()).get</*State*/0>()) == (Excl))) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2877,5},{2877,13}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (true))); } res_; }),116u);
    } catch (...) { throw ::romp::ModelPropertyError(116); }
  }

  
  bool __romp__Property__CacheInvldDataProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= ({bool res_ = true; for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) { res_ &= (!(((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2883,5},{2883,13}})).get</*Proc*/3>()), (n), ::romp::location{{2883,5},{2883,21}})).get</*CacheState*/2>()) == (CACHE_I)) || (((::romp::Element<NODE,NODE_STATE>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2883,58},{2883,66}})).get</*Proc*/3>()), (n), ::romp::location{{2883,58},{2883,74}})).get</*CacheData*/3>()).IsUndefined())); } res_; }); } res_; }),117u);
    } catch (...) { throw ::romp::ModelPropertyError(117); }
  }

  
  bool __romp__Property__L2InvldDataProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2889,6},{2889,14}})).get</*L2*/9>()).get</*State*/0>()) == (Invld)) || ((((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2891,18},{2891,26}})).get</*L2*/9>()).get</*Data*/1>()).IsUndefined()) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2892,6},{2892,14}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (false))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2893,6},{2893,14}})).get</*L2*/9>()).get</*Dirty*/3>()) == (false)))); } res_; }),118u);
    } catch (...) { throw ::romp::ModelPropertyError(118); }
  }

  //---- outside a cluster  ------
  
  bool __romp__Property__Remote_cluster_cannot_be_WRDO_(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto r=Rmt::__LB(); r!=Rmt::__UB(); r.__step()) { res_ &= ((((::romp::Element<Procss,ProcState>((Procs), (r), ::romp::location{{2901,7},{2901,15}})).get</*RAC*/10>()).get</*State*/0>()) != (WRDO)); } res_; }),119u);
    } catch (...) { throw ::romp::ModelPropertyError(119); }
  }

  
  bool __romp__Property__ClusterStateProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= ({bool res_ = true; for (auto q=Procss::__LB(); q!=Procss::__UB(); q.__step()) { res_ &= (!(((p) != (q)) && (((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2909,10},{2909,18}})).get</*L2*/9>()).get</*State*/0>()) == (Excl)) && ((((::romp::Element<Procss,ProcState>((Procs), (q), ::romp::location{{2909,37},{2909,45}})).get</*L2*/9>()).get</*State*/0>()) == (Excl))))); } res_; }); } res_; }),120u);
    } catch (...) { throw ::romp::ModelPropertyError(120); }
  }

  
  bool __romp__Property__InvldDataProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2915,6},{2915,14}})).get</*L2*/9>()).get</*State*/0>()) == (Invld)) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2916,18},{2916,26}})).get</*L2*/9>()).get</*Data*/1>()).IsUndefined())); } res_; }),121u);
    } catch (...) { throw ::romp::ModelPropertyError(121); }
  }

  
  bool __romp__Property__RACINvalProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2922,6},{2922,14}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2923,6},{2923,14}})).get</*RAC*/10>()).get</*InvCnt*/1>()) == ((::romp::range_t)(0)))); } res_; }),122u);
    } catch (...) { throw ::romp::ModelPropertyError(122); }
  }

  
  bool __romp__Property__InvStateProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= ({bool res_ = true; for (auto q=Procss::__LB(); q!=Procss::__UB(); q.__step()) { res_ &= (!((((p) != (q)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2931,18},{2931,26}})).get</*RAC*/10>()).get</*State*/0>()) == (WINV))) && ((((::romp::Element<Procss,ProcState>((Procs), (q), ::romp::location{{2931,48},{2931,56}})).get</*L2*/9>()).get</*State*/0>()) == (Shrd))) || (((::romp::Element<Procss,GINV_MSG>((GInvMsg), (q), ::romp::location{{2933,6},{2933,16}})).get</*Cmd*/0>()) == (INV))); } res_; }); } res_; }),123u);
    } catch (...) { throw ::romp::ModelPropertyError(123); }
  }

  /*
   -- not a valid invariant, counterexample as following:
   Start rule :
   Init, d:Datas_1
   Other rules:
   L1_GetX, src:NODE_1, p:Home
   L2_Recv_Get(X)_OutGet(X), src:NODE_1, p:Home
   L1_Get, src:NODE_2, p:Home
   L1_Get, src:NODE_1, p:Rmt_1
   L2_Recv_Get(X)_OutGet(X), src:NODE_1, p:Rmt_2
   Dir_Recv_RmtGet_Put, r:Rmt_2
   Dir_Shrd_HomeGetX_PutX
   L1_Recv_PutX, dst:NODE_1, p:Home
   L2_Fwd_Get(X), src:NODE_2, p:Home
   L1_Update_Data, data:Datas_2, src:NODE_1, p:Home
   L1Rmt_Recv_Get_Put, dst:NODE_1, p:Home
   L2_Recv_SHWB, src:NODE_1, p:Home
   
   invariant "ClusterShrdDataProp"
   forall p: Procss do
   ((Procs[p].L2.State = Shrd) ->
   ((Dir.Collecting -> Procs[p].L2.Data = Dir.PrevData) &
   (!Dir.Collecting -> Procs[p].L2.Data = Dir.CurrData)))
   end;
   */
  
  bool __romp__Property__MemDataProp(void) const {
    try {
      return this->__rw__->invariant_handler((!(!(((Dir).get</*State*/2>()) == (Excl))) || (((Dir).get</*Mem*/1>()) == ((Dir).get</*CurrData*/8>()))),124u);
    } catch (...) { throw ::romp::ModelPropertyError(124); }
  }

  /*
   -- not a valid invariant
   -- counterexample:
   -- 1. p1 gets shared
   -- 2. p1 silent drop
   -- 3. p1 req shared
   -- 4. p2 req excl, dir invalidates p1, grants p2
   -- 5. p1 get Invalidated
   -- 6. dir receives p1's req, forwards to p2
   -- 7. p2 grants p1's req, shwb to dir
   -- 8. dir set p1 & p2 to be sharers
   -- 9. p3 req excl, dir invalidates p1 and p2, grants p3
   -- 10 p1 receives 2nd INV before p2's reply to p1.
   invariant "ClusterRecvInvProp"
   forall p: Procss do 
   (GInvMsg[p].Cmd = INV) 
   ->
   (Procs[p].RAC.State != RRD )
   end;
   */
  
  bool __romp__Property__tmpProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= ({bool res_ = true; for (auto src=NODE::__LB(); src!=NODE::__UB(); src.__step()) { res_ &= (!(((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2991,6},{2991,14}})).get</*InvMsg*/5>()), (src), ::romp::location{{2991,6},{2991,26}})).get</*Cmd*/0>()) == (INV_InvAck)) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{2993,5},{2993,13}})).get</*L2*/9>()).get</*pending*/2>()) == (true))); } res_; }); } res_; }),125u);
    } catch (...) { throw ::romp::ModelPropertyError(125); }
  }

  
  bool __romp__Property__L2_InvCnt__0(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= ({bool res_ = true; for (auto src=NODE::__LB(); src!=NODE::__UB(); src.__step()) { res_ &= (!(((::romp::Element<NODE_L2,INV_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3000,6},{3000,14}})).get</*InvMsg*/5>()), (src), ::romp::location{{3000,6},{3000,26}})).get</*Cmd*/0>()) == (INV_InvAck)) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3002,6},{3002,14}})).get</*L2*/9>()).get</*InvCnt*/5>()) > ((::romp::range_t)(0)))); } res_; }); } res_; }),126u);
    } catch (...) { throw ::romp::ModelPropertyError(126); }
  }

  
  bool __romp__Property__Nak_Inval_WINV(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!(((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (p), ::romp::location{{3008,4},{3008,14}})).get</*Cmd*/0>()) == (NAK)) || (((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3010,4},{3010,12}})).get</*RAC*/10>()).get</*State*/0>()) != (Inval)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3010,34},{3010,42}})).get</*RAC*/10>()).get</*State*/0>()) != (WINV)))); } res_; }),127u);
    } catch (...) { throw ::romp::ModelPropertyError(127); }
  }

  
  bool __romp__Property__Uni_PutwithDataProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= ({bool res_ = true; for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) { res_ &= (!(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3019,5},{3019,13}})).get</*UniMsg*/4>()), (n), ::romp::location{{3019,5},{3019,23}})).get</*Cmd*/0>()) == (UNI_Put)) || (!(((::romp::Element<NODE_L2,UNI_MSG>(((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3021,18},{3021,26}})).get</*UniMsg*/4>()), (n), ::romp::location{{3021,18},{3021,36}})).get</*Data*/2>()).IsUndefined()))); } res_; }); } res_; }),128u);
    } catch (...) { throw ::romp::ModelPropertyError(128); }
  }

  
  bool __romp__Property__HomeRecvIACK_X_Prop(void) const {
    try {
      return this->__rw__->invariant_handler((!((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{3025,3},{3025,16}})).get</*Cmd*/0>()) == (IACK)) || (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (Home), ::romp::location{{3026,3},{3026,16}})).get</*Cmd*/0>()) == (IACKX))) || (((Dir).get</*isBusy*/0>()) == (true))),129u);
    } catch (...) { throw ::romp::ModelPropertyError(129); }
  }

  
  bool __romp__Property__isRetiredProp1(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3033,3},{3033,11}})).get</*L2*/9>()).get</*isRetired*/12>()) == (true)) || ((((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3035,3},{3035,11}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3036,3},{3036,11}})).get</*RAC*/10>()).get</*State*/0>()) == (WINV))) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3037,3},{3037,11}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (true)))); } res_; }),130u);
    } catch (...) { throw ::romp::ModelPropertyError(130); }
  }

  
  bool __romp__Property__isRetiredProp2(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3043,3},{3043,11}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3044,3},{3044,11}})).get</*RAC*/10>()).get</*State*/0>()) == (WINV))) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3046,3},{3046,11}})).get</*L2*/9>()).get</*isRetired*/12>()) == (true))); } res_; }),131u);
    } catch (...) { throw ::romp::ModelPropertyError(131); }
  }

  
  bool __romp__Property__StateProp(void) const {
    try {
      return this->__rw__->invariant_handler((!(((Dir).get</*isLocal*/5>()) == (false)) || ((((::romp::Element<Procss,ProcState>((Procs), (Home), ::romp::location{{3053,3},{3053,14}})).get</*L2*/9>()).get</*State*/0>()) != (Excl))),132u);
    } catch (...) { throw ::romp::ModelPropertyError(132); }
  }

  
  bool __romp__Property__HeadPtrProp(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!((((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3058,3},{3058,11}})).get</*L2*/9>()).get</*pending*/2>()) == (false)) && (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3059,16},{3059,24}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined()))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3060,3},{3060,11}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3062,3},{3062,11}})).get</*L2*/9>()).get</*State*/0>()) != (Invld))); } res_; }),133u);
    } catch (...) { throw ::romp::ModelPropertyError(133); }
  }

  
  bool __romp__Property__Excl__OnlyCopy(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3068,3},{3068,11}})).get</*L2*/9>()).get</*State*/0>()) == (Excl)) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3070,3},{3070,11}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (true))); } res_; }),134u);
    } catch (...) { throw ::romp::ModelPropertyError(134); }
  }

  
  bool __romp__Property__HeadPtrL2__NoSharers(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!((!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3076,16},{3076,24}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3077,3},{3077,11}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) || ({bool res_ = true; for (auto n=NODE::__LB(); n!=NODE::__UB(); n.__step()) { res_ &= ((::romp::Element<NODE,boolean>((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3080,5},{3080,13}})).get</*L2*/9>()).get</*ShrSet*/4>()), (n), ::romp::location{{3080,5},{3080,26}})) == (false)); } res_; })); } res_; }),135u);
    } catch (...) { throw ::romp::ModelPropertyError(135); }
  }

  
  bool __romp__Property__HeadPtrL2OnlyCopy__Excl(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!(((!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3088,16},{3088,24}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3089,3},{3089,11}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3090,3},{3090,11}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (true))) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3092,3},{3092,11}})).get</*L2*/9>()).get</*State*/0>()) == (Excl))); } res_; }),136u);
    } catch (...) { throw ::romp::ModelPropertyError(136); }
  }

  
  bool __romp__Property__HeadPtrL2_OnlyCopy__Shrd(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!(((!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3099,16},{3099,24}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined())) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3100,3},{3100,11}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3101,3},{3101,11}})).get</*L2*/9>()).get</*OnlyCopy*/8>()) == (false))) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3103,3},{3103,11}})).get</*L2*/9>()).get</*State*/0>()) == (Shrd))); } res_; }),137u);
    } catch (...) { throw ::romp::ModelPropertyError(137); }
  }

  
  bool __romp__Property___Invld___Gblock_WB(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3109,3},{3109,11}})).get</*L2*/9>()).get</*State*/0>()) != (Invld)) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3111,3},{3111,11}})).get</*L2*/9>()).get</*Gblock_WB*/11>()) == (false))); } res_; }),138u);
    } catch (...) { throw ::romp::ModelPropertyError(138); }
  }

  
  bool __romp__Property__NAKC_Nakc__Excl_Inval(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3117,3},{3117,11}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()) == (NAKC_Nakc)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3118,3},{3118,11}})).get</*NakcMsg*/8>()).get</*Aux*/2>()) == (L2))) || (((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3120,3},{3120,11}})).get</*L2*/9>()).get</*State*/0>()) == (Excl)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3121,3},{3121,11}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)))); } res_; }),139u);
    } catch (...) { throw ::romp::ModelPropertyError(139); }
  }

  
  bool __romp__Property__NAKC_SD__Excl_Inval__Gblock_WB(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3127,3},{3127,11}})).get</*NakcMsg*/8>()).get</*Cmd*/0>()) == (NAKC_SD)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3128,3},{3128,11}})).get</*NakcMsg*/8>()).get</*Aux*/2>()) == (L2))) || ((((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3130,3},{3130,11}})).get</*L2*/9>()).get</*State*/0>()) == (Excl)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3131,3},{3131,11}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3132,3},{3132,11}})).get</*L2*/9>()).get</*Gblock_WB*/11>()) == (false)))); } res_; }),140u);
    } catch (...) { throw ::romp::ModelPropertyError(140); }
  }

  
  bool __romp__Property__SHWB_ShWb_L2__Excl_Inval(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3139,3},{3139,11}})).get</*ShWbMsg*/7>()).get</*Cmd*/0>()) == (SHWB_ShWb)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3140,3},{3140,11}})).get</*ShWbMsg*/7>()).get</*Aux*/3>()) == (L2))) || (((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3142,3},{3142,11}})).get</*L2*/9>()).get</*State*/0>()) == (Excl)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3143,3},{3143,11}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)))); } res_; }),141u);
    } catch (...) { throw ::romp::ModelPropertyError(141); }
  }

  
  bool __romp__Property__SHWB_ShWb__Excl(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3150,3},{3150,11}})).get</*ShWbMsg*/7>()).get</*Cmd*/0>()) == (SHWB_ShWb)) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3152,3},{3152,11}})).get</*L2*/9>()).get</*State*/0>()) == (Excl))); } res_; }),142u);
    } catch (...) { throw ::romp::ModelPropertyError(142); }
  }

  
  bool __romp__Property__SHWB_FAck_L2__Excl_Inval(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= (!(((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3158,3},{3158,11}})).get</*ShWbMsg*/7>()).get</*Cmd*/0>()) == (SHWB_FAck)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3159,3},{3159,11}})).get</*ShWbMsg*/7>()).get</*Aux*/3>()) == (L2))) || (((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3161,3},{3161,11}})).get</*L2*/9>()).get</*State*/0>()) == (Excl)) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3162,3},{3162,11}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval)))); } res_; }),143u);
    } catch (...) { throw ::romp::ModelPropertyError(143); }
  }

  
  bool __romp__Property__l2HeadPtr_RD_RAC__Excl(void) const {
    try {
      return this->__rw__->invariant_handler(({bool res_ = true; for (auto p=Procss::__LB(); p!=Procss::__UB(); p.__step()) { res_ &= ({bool res_ = true; for (auto src=Procss::__LB(); src!=Procss::__UB(); src.__step()) { res_ &= (!((((((((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{3169,4},{3169,16}})).get</*Cmd*/0>()) == (RD_RAC)) || (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{3170,4},{3170,16}})).get</*Cmd*/0>()) == (RDX_RAC))) && (((::romp::Element<Procss,GUNI_MSG>((GUniMsg), (src), ::romp::location{{3171,3},{3171,15}})).get</*Cluster*/1>()) == (p))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3172,3},{3172,11}})).get</*RAC*/10>()).get</*State*/0>()) == (Inval))) && (!((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3173,16},{3173,24}})).get</*L2*/9>()).get</*HeadPtr*/6>()).IsUndefined()))) && ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3174,3},{3174,11}})).get</*L2*/9>()).get</*HeadPtr*/6>()) == (L2))) || ((((::romp::Element<Procss,ProcState>((Procs), (p), ::romp::location{{3176,3},{3176,11}})).get</*L2*/9>()).get</*State*/0>()) == (Excl))); } res_; }); } res_; }),144u);
    } catch (...) { throw ::romp::ModelPropertyError(144); }
  }


  friend ::romp::ostream_p& operator << (::romp::ostream_p& out, const ::__model__::__romp__Model__& s) {
     return (out << '{' << out._indent() << out.nl()
         << "GUniMsg" << ((((not s.GUniMsg.__IS_RECORD())||(s.GUniMsg.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.GUniMsg.__p_type() + " = " : " := ") << s.GUniMsg << ';' << out.nl()
         << "GInvMsg" << ((((not s.GInvMsg.__IS_RECORD())||(s.GInvMsg.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.GInvMsg.__p_type() + " = " : " := ") << s.GInvMsg << ';' << out.nl()
         << "GWbMsg" << ((((not s.GWbMsg.__IS_RECORD())||(s.GWbMsg.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.GWbMsg.__p_type() + " = " : " := ") << s.GWbMsg << ';' << out.nl()
         << "GShWbMsg" << ((((not s.GShWbMsg.__IS_RECORD())||(s.GShWbMsg.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.GShWbMsg.__p_type() + " = " : " := ") << s.GShWbMsg << ';' << out.nl()
         << "GNakcMsg" << ((((not s.GNakcMsg.__IS_RECORD())||(s.GNakcMsg.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.GNakcMsg.__p_type() + " = " : " := ") << s.GNakcMsg << ';' << out.nl()
         << "Procs" << ((((not s.Procs.__IS_RECORD())||(s.Procs.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.Procs.__p_type() + " = " : " := ") << s.Procs << ';' << out.nl()
         << "Dir" << ((((not s.Dir.__IS_RECORD())||(s.Dir.__IS_TYPEID()))&&(out.OPTIONS.report_show_type)) ? ": " + s.Dir.__p_type() + " = " : " := ") << s.Dir << ';'
        << out.dedent() << out.nl() << '}');  }
  friend ::std::ostream& operator << (::std::ostream& out_, const ::__model__::__romp__Model__& s) { ::romp::ostream_p out(out_,::romp::Options(),2); out << s; return out_; }

#ifdef __ROMP__SIMPLE_TRACE
  template<class O> friend ::romp::ojstream<O>& operator << (::romp::ojstream<O>& json, const ::__model__::__romp__Model__& s) { return (json << '['  << s.GUniMsg << ',' << s.GInvMsg << ',' << s.GWbMsg << ',' << s.GShWbMsg << ',' << s.GNakcMsg << ',' << s.Procs << ',' << s.Dir << ']'); }
#else
  template<class O> friend ::romp::ojstream<O>& operator << (::romp::ojstream<O>& json, const ::__model__::__romp__Model__& s) { return (json << "{\"$type\":\"model-state\",\"value\":[" << "{\"$type\":\"kv-pair\",\"key\":\"GUniMsg\",\"value\":" << s.GUniMsg << '}' << ',' << "{\"$type\":\"kv-pair\",\"key\":\"GInvMsg\",\"value\":" << s.GInvMsg << '}' << ',' << "{\"$type\":\"kv-pair\",\"key\":\"GWbMsg\",\"value\":" << s.GWbMsg << '}' << ',' << "{\"$type\":\"kv-pair\",\"key\":\"GShWbMsg\",\"value\":" << s.GShWbMsg << '}' << ',' << "{\"$type\":\"kv-pair\",\"key\":\"GNakcMsg\",\"value\":" << s.GNakcMsg << '}' << ',' << "{\"$type\":\"kv-pair\",\"key\":\"Procs\",\"value\":" << s.Procs << '}' << ',' << "{\"$type\":\"kv-pair\",\"key\":\"Dir\",\"value\":" << s.Dir << '}' << "]}"); }
#endif

  inline size_t __romp__model_hash() const {
    size_t _hash = 0ul;
    ::romp::hash_combine(_hash, GUniMsg);
    ::romp::hash_combine(_hash, GInvMsg);
    ::romp::hash_combine(_hash, GWbMsg);
    ::romp::hash_combine(_hash, GShWbMsg);
    ::romp::hash_combine(_hash, GNakcMsg);
    ::romp::hash_combine(_hash, Procs);
    ::romp::hash_combine(_hash, Dir);
    return _hash;
  }

  friend inline bool operator == (const ::__model__::__romp__Model__& l, const ::__model__::__romp__Model__& r) {
    return (    l.GUniMsg == r.GUniMsg && 
    l.GInvMsg == r.GInvMsg && 
    l.GWbMsg == r.GWbMsg && 
    l.GShWbMsg == r.GShWbMsg && 
    l.GNakcMsg == r.GNakcMsg && 
    l.Procs == r.Procs && 
    l.Dir == r.Dir);
  }


};


} // namespace __model__


#pragma endregion model__generated_code



#pragma region metadata__generated_code

namespace __info__ {
/* the number possible variations in the state (# of permutations of the state-space) */
#define _ROMP_STATESPACE_COUNT_str "1733256222834513949095047476091682306524765717005801711979770250844956827031030464512"
  const std::string TYPE_IDS[] = {"ClusterCnt","NODE","Datas","L2Name","NODE_L2","Homes","Rmt","Procss","CacheCnt","RACState","CACHE_STATE","L2State","NODE_CMD","NODE_STATE","UNI_CMD","UNI_MSG","INV_CMD","INV_MSG","WB_CMD","WB_MSG","SHWB_CMD","SHWB_MSG","NAKC_CMD","NAKC_MSG","ProcState","DirState","GUNI_CMD","GUNI_MSG","GINV_CMD","GINV_MSG","GWB_CMD","GWB_MSG","GSHWB_CMD","GSHWB_MSG","GNAKC_CMD","GNAKC_MSG"};
  const std::string RECORD_FIELD_LABELS[] = {"ProcCmd","InvMarked","CacheState","CacheData","block_WB","Cmd","Proc","Data","Cmd","Cmd","Proc","Data","Cmd","Proc","Data","Aux","Cmd","Proc","Aux","State","Data","pending","Dirty","ShrSet","InvCnt","HeadPtr","ReqId","OnlyCopy","ReqCluster","ReqType","Gblock_WB","isRetired","ifHoldMsg","State","InvCnt","CurrData","PrevData","Collecting","Proc","UniMsg","InvMsg","WbMsg","ShWbMsg","NakcMsg","L2","RAC","isBusy","Mem","State","ShrSet","InvCnt","isLocal","HeadPtr","Collecting","CurrData","PrevData","Cmd","Cluster","InvCnt","Data","Cmd","Cluster","Cmd","Cluster","Data","Cmd","Cluster","Data","Cmd","Cluster"};
  const ::romp::RuleInfo RULE_SET_INFOS[] = {{"L1_Update_Data",::romp::location{{290,1},{300,8}},"{\"$type\":\"rule\",\"expr\":\"((Procs[p].Proc[src].CacheState = CACHE_E) | (Procs[p].Proc[src].CacheState = CACHE_M))\",\"label\":\"L1_Update_Data\",\"loc\":{\"$type\":\"location\",\"start\":[290,1],\"end\":[300,8]}"},{"L1_Get",::romp::location{{307,1},{317,8}},"{\"$type\":\"rule\",\"expr\":\"(((Procs[p].Proc[src].ProcCmd = NODE_None) & (Procs[p].Proc[src].CacheState = CACHE_I)) & (Procs[p].Proc[src].block_WB = false))\",\"label\":\"L1_Get\",\"loc\":{\"$type\":\"location\",\"start\":[307,1],\"end\":[317,8]}"},{"L2_Recv_Get_Put",::romp::location{{324,3},{337,10}},"{\"$type\":\"rule\",\"expr\":\"(((((Procs[p].UniMsg[src].Cmd = UNI_Get) & (Procs[p].UniMsg[src].Proc = L2)) & (Procs[p].L2.pending = false)) & (Procs[p].L2.State = Shrd)) & isundefined(Procs[p].L2.HeadPtr))\",\"label\":\"L2_Recv_Get_Put\",\"loc\":{\"$type\":\"location\",\"start\":[324,3],\"end\":[337,10]}"},{"L2_busy_Recv_Get_X__Nak",::romp::location{{345,3},{356,10}},"{\"$type\":\"rule\",\"expr\":\"((((Procs[p].UniMsg[src].Cmd = UNI_Get) | (Procs[p].UniMsg[src].Cmd = UNI_GetX)) & (Procs[p].UniMsg[src].Proc = L2)) & (Procs[p].L2.pending = true))\",\"label\":\"L2_busy_Recv_Get_X__Nak\",\"loc\":{\"$type\":\"location\",\"start\":[345,3],\"end\":[356,10]}"},{"L2HeadPtr_Recv_Get_Put",::romp::location{{363,1},{379,8}},"{\"$type\":\"rule\",\"expr\":\"(((((Procs[p].UniMsg[src].Cmd = UNI_Get) & (Procs[p].UniMsg[src].Proc = L2)) & (Procs[p].L2.pending = false)) & (!isundefined(Procs[p].L2.HeadPtr))) & (Procs[p].L2.HeadPtr = L2))\",\"label\":\"L2HeadPtr_Recv_Get_Put\",\"loc\":{\"$type\":\"location\",\"start\":[363,1],\"end\":[379,8]}"},{"L2_Fwd_Get_X_",::romp::location{{386,3},{434,10}},"{\"$type\":\"rule\",\"expr\":\"((((((Procs[p].L2.pending = false) & (Procs[p].L2.State = Excl)) & (!isundefined(Procs[p].L2.HeadPtr))) & (Procs[p].L2.HeadPtr != L2)) & ((Procs[p].UniMsg[src].Cmd = UNI_Get) | (Procs[p].UniMsg[src].Cmd = UNI_GetX))) & (Procs[p].UniMsg[src].Proc = L2))\",\"label\":\"L2_Fwd_Get_X_\",\"loc\":{\"$type\":\"location\",\"start\":[386,3],\"end\":[434,10]}"},{"L2_Recv_Get_X__OutGet_X_",::romp::location{{441,3},{483,10}},"{\"$type\":\"rule\",\"expr\":\"(((((((Procs[p].UniMsg[src].Cmd = UNI_Get) | (Procs[p].UniMsg[src].Cmd = UNI_GetX)) & (Procs[p].UniMsg[src].Proc = L2)) & (Procs[p].L2.State = Invld)) & (Procs[p].L2.pending = false)) & (Procs[p].RAC.State = Inval)) & (Procs[p].L2.Gblock_WB = false))\",\"label\":\"L2_Recv_Get_X__OutGet_X_\",\"loc\":{\"$type\":\"location\",\"start\":[441,3],\"end\":[483,10]}"},{"L1_GetX",::romp::location{{489,1},{501,8}},"{\"$type\":\"rule\",\"expr\":\"((((Procs[p].Proc[src].ProcCmd = NODE_None) & (Procs[p].Proc[src].CacheState != CACHE_E)) & (Procs[p].Proc[src].CacheState != CACHE_M)) & (Procs[p].Proc[src].block_WB = false))\",\"label\":\"L1_GetX\",\"loc\":{\"$type\":\"location\",\"start\":[489,1],\"end\":[501,8]}"},{"L2HeadPtr_Recv_GetX_PutX",::romp::location{{508,1},{547,8}},"{\"$type\":\"rule\",\"expr\":\"((((((Procs[p].UniMsg[src].Cmd = UNI_GetX) & (Procs[p].UniMsg[src].Proc = L2)) & (Procs[p].L2.pending = false)) & (!isundefined(Procs[p].L2.HeadPtr))) & (Procs[p].L2.HeadPtr = L2)) & (Procs[p].L2.State != Invld))\",\"label\":\"L2HeadPtr_Recv_GetX_PutX\",\"loc\":{\"$type\":\"location\",\"start\":[508,1],\"end\":[547,8]}"},{"L2Shrd_Recv_GetX__PutX_",::romp::location{{554,3},{629,10}},"{\"$type\":\"rule\",\"expr\":\"(((((Procs[p].L2.State = Shrd) & (Procs[p].L2.pending = false)) & isundefined(Procs[p].L2.HeadPtr)) & (Procs[p].UniMsg[src].Cmd = UNI_GetX)) & (Procs[p].UniMsg[src].Proc = L2))\",\"label\":\"L2Shrd_Recv_GetX__PutX_\",\"loc\":{\"$type\":\"location\",\"start\":[554,3],\"end\":[629,10]}"},{"L1_Recv_Inv",::romp::location{{636,3},{650,10}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].InvMsg[dst].Cmd = INV_Inv)\",\"label\":\"L1_Recv_Inv\",\"loc\":{\"$type\":\"location\",\"start\":[636,3],\"end\":[650,10]}"},{"L2_Recv_InvAck",::romp::location{{657,3},{679,10}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].InvMsg[src].Cmd = INV_InvAck)\",\"label\":\"L2_Recv_InvAck\",\"loc\":{\"$type\":\"location\",\"start\":[657,3],\"end\":[679,10]}"},{"L1Rmt_Recv_Get_X__Nak",::romp::location{{687,3},{732,10}},"{\"$type\":\"rule\",\"expr\":\"((((((Procs[p].UniMsg[src].Cmd = UNI_Get) | (Procs[p].UniMsg[src].Cmd = UNI_GetX)) & (Procs[p].UniMsg[src].Proc = dst)) & (Procs[p].Proc[dst].CacheState != CACHE_E)) & (Procs[p].Proc[dst].CacheState != CACHE_M)) & (Procs[p].Proc[dst].block_WB = false))\",\"label\":\"L1Rmt_Recv_Get_X__Nak\",\"loc\":{\"$type\":\"location\",\"start\":[687,3],\"end\":[732,10]}"},{"L2_Recv_NAKC_Nakc",::romp::location{{739,3},{787,10}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].NakcMsg.Cmd = NAKC_Nakc)\",\"label\":\"L2_Recv_NAKC_Nakc\",\"loc\":{\"$type\":\"location\",\"start\":[739,3],\"end\":[787,10]}"},{"RmtCluster_Recv_NAKC_SD",::romp::location{{795,3},{892,10}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].NakcMsg.Cmd = NAKC_SD)\",\"label\":\"RmtCluster_Recv_NAKC_SD\",\"loc\":{\"$type\":\"location\",\"start\":[795,3],\"end\":[892,10]}"},{"Home_Recv_NAKC_SD",::romp::location{{897,3},{982,10}},"{\"$type\":\"rule\",\"expr\":\"(Procs[Home].NakcMsg.Cmd = NAKC_SD)\",\"label\":\"Home_Recv_NAKC_SD\",\"loc\":{\"$type\":\"location\",\"start\":[897,3],\"end\":[982,10]}"},{"L1Rmt_Recv_Get_Put",::romp::location{{987,3},{1015,10}},"{\"$type\":\"rule\",\"expr\":\"(((Procs[p].UniMsg[src].Cmd = UNI_Get) & (Procs[p].UniMsg[src].Proc = dst)) & ((Procs[p].Proc[dst].CacheState = CACHE_E) | (Procs[p].Proc[dst].CacheState = CACHE_M)))\",\"label\":\"L1Rmt_Recv_Get_Put\",\"loc\":{\"$type\":\"location\",\"start\":[987,3],\"end\":[1015,10]}"},{"L2_Recv_SHWB",::romp::location{{1022,3},{1100,10}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].ShWbMsg.Cmd = SHWB_ShWb)\",\"label\":\"L2_Recv_SHWB\",\"loc\":{\"$type\":\"location\",\"start\":[1022,3],\"end\":[1100,10]}"},{"L1Rmt_Recv_GetX_PutX",::romp::location{{1107,1},{1143,8}},"{\"$type\":\"rule\",\"expr\":\"(((Procs[p].UniMsg[src].Cmd = UNI_GetX) & (Procs[p].UniMsg[src].Proc = dst)) & ((Procs[p].Proc[dst].CacheState = CACHE_E) | (Procs[p].Proc[dst].CacheState = CACHE_M)))\",\"label\":\"L1Rmt_Recv_GetX_PutX\",\"loc\":{\"$type\":\"location\",\"start\":[1107,1],\"end\":[1143,8]}"},{"L2_Recv_SHWB_FAck",::romp::location{{1150,1},{1231,8}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].ShWbMsg.Cmd = SHWB_FAck)\",\"label\":\"L2_Recv_SHWB_FAck\",\"loc\":{\"$type\":\"location\",\"start\":[1150,1],\"end\":[1231,8]}"},{"L1_Recv_Nak",::romp::location{{1237,3},{1245,10}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].UniMsg[dst].Cmd = UNI_Nak)\",\"label\":\"L1_Recv_Nak\",\"loc\":{\"$type\":\"location\",\"start\":[1237,3],\"end\":[1245,10]}"},{"L1_Recv_Put",::romp::location{{1251,3},{1270,10}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].UniMsg[dst].Cmd = UNI_Put)\",\"label\":\"L1_Recv_Put\",\"loc\":{\"$type\":\"location\",\"start\":[1251,3],\"end\":[1270,10]}"},{"L1_Recv_PutX",::romp::location{{1277,3},{1289,10}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].UniMsg[dst].Cmd = UNI_PutX)\",\"label\":\"L1_Recv_PutX\",\"loc\":{\"$type\":\"location\",\"start\":[1277,3],\"end\":[1289,10]}"},{"L1_Recv_PutXX",::romp::location{{1296,3},{1308,10}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].UniMsg[dst].Cmd = UNI_PutXX)\",\"label\":\"L1_Recv_PutXX\",\"loc\":{\"$type\":\"location\",\"start\":[1296,3],\"end\":[1308,10]}"},{"L1_SilentDrop",::romp::location{{1314,1},{1322,8}},"{\"$type\":\"rule\",\"expr\":\"((Procs[p].Proc[src].ProcCmd = NODE_None) & ((Procs[p].Proc[src].CacheState = CACHE_S) | (Procs[p].Proc[src].CacheState = CACHE_E)))\",\"label\":\"L1_SilentDrop\",\"loc\":{\"$type\":\"location\",\"start\":[1314,1],\"end\":[1322,8]}"},{"L1_WriteBack",::romp::location{{1329,1},{1341,8}},"{\"$type\":\"rule\",\"expr\":\"((Procs[p].Proc[src].CacheState = CACHE_M) & (Procs[p].Proc[src].ProcCmd = NODE_None))\",\"label\":\"L1_WriteBack\",\"loc\":{\"$type\":\"location\",\"start\":[1329,1],\"end\":[1341,8]}"},{"L2_Recv_WB_Remain",::romp::location{{1347,3},{1365,10}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].WbMsg.Cmd = WB_Wb)\",\"label\":\"L2_Recv_WB_Remain\",\"loc\":{\"$type\":\"location\",\"start\":[1347,3],\"end\":[1365,10]}"},{"L1_Recv_WbAck",::romp::location{{1371,1},{1382,8}},"{\"$type\":\"rule\",\"expr\":\"(Procs[p].UniMsg[dst].Cmd = WB_WbAck)\",\"label\":\"L1_Recv_WbAck\",\"loc\":{\"$type\":\"location\",\"start\":[1371,1],\"end\":[1382,8]}"},{"L2_SilentDrop",::romp::location{{1389,1},{1407,8}},"{\"$type\":\"rule\",\"expr\":\"((((((Procs[p].L2.State != Invld) & (Procs[p].L2.pending = false)) & forall n : NODE do (Procs[p].L2.ShrSet[n] = false) endforall) & (Procs[p].L2.Dirty = false)) & (Procs[p].L2.HeadPtr = L2)) & (Procs[p].RAC.State = Inval))\",\"label\":\"L2_SilentDrop\",\"loc\":{\"$type\":\"location\",\"start\":[1389,1],\"end\":[1407,8]}"},{"Dir_HomeGet_Put",::romp::location{{1414,1},{1439,8}},"{\"$type\":\"rule\",\"expr\":\"(((Procs[Home].RAC.State = WRDO) & (Dir.isBusy = false)) & ((Dir.State = Invld) | (Dir.State = Shrd)))\",\"label\":\"Dir_HomeGet_Put\",\"loc\":{\"$type\":\"location\",\"start\":[1414,1],\"end\":[1439,8]}"},{"Dir_HomeGet_RmtGet",::romp::location{{1443,1},{1456,8}},"{\"$type\":\"rule\",\"expr\":\"((((Procs[Home].RAC.State = WRDO) & (Dir.isBusy = false)) & (Dir.State = Excl)) & (Dir.isLocal = false))\",\"label\":\"Dir_HomeGet_RmtGet\",\"loc\":{\"$type\":\"location\",\"start\":[1443,1],\"end\":[1456,8]}"},{"Dir_HomeGet_isLocal_Put",::romp::location{{1460,1},{1489,8}},"{\"$type\":\"rule\",\"expr\":\"((((Procs[Home].RAC.State = WRDO) & (Dir.isBusy = false)) & (Dir.State = Excl)) & (Dir.isLocal = true))\",\"label\":\"Dir_HomeGet_isLocal_Put\",\"loc\":{\"$type\":\"location\",\"start\":[1460,1],\"end\":[1489,8]}"},{"Dir_HomeGetX_RmtGetX",::romp::location{{1493,1},{1507,8}},"{\"$type\":\"rule\",\"expr\":\"((((Procs[Home].RAC.State = WRDX) & (Dir.isBusy = false)) & (Dir.State = Excl)) & (Dir.isLocal = false))\",\"label\":\"Dir_HomeGetX_RmtGetX\",\"loc\":{\"$type\":\"location\",\"start\":[1493,1],\"end\":[1507,8]}"},{"Dir_HomeGetX_isLocal_PutX",::romp::location{{1511,1},{1547,8}},"{\"$type\":\"rule\",\"expr\":\"((((Procs[Home].RAC.State = WRDX) & (Dir.isBusy = false)) & (Dir.State = Excl)) & (Dir.isLocal = true))\",\"label\":\"Dir_HomeGetX_isLocal_PutX\",\"loc\":{\"$type\":\"location\",\"start\":[1511,1],\"end\":[1547,8]}"},{"Dir_HomeGetX_PutX",::romp::location{{1551,1},{1586,8}},"{\"$type\":\"rule\",\"expr\":\"(((Procs[Home].RAC.State = WRDX) & (Dir.isBusy = false)) & (Dir.State = Invld))\",\"label\":\"Dir_HomeGetX_PutX\",\"loc\":{\"$type\":\"location\",\"start\":[1551,1],\"end\":[1586,8]}"},{"Dir_Shrd_HomeGetX_PutX",::romp::location{{1590,1},{1649,8}},"{\"$type\":\"rule\",\"expr\":\"(((Procs[Home].RAC.State = WRDX) & (Dir.isBusy = false)) & (Dir.State = Shrd))\",\"label\":\"Dir_Shrd_HomeGetX_PutX\",\"loc\":{\"$type\":\"location\",\"start\":[1590,1],\"end\":[1649,8]}"},{"Home_Recv_InvAck",::romp::location{{1654,1},{1679,8}},"{\"$type\":\"rule\",\"expr\":\"((GInvMsg[src].Cmd = SACK) & (GInvMsg[src].Cluster = Home))\",\"label\":\"Home_Recv_InvAck\",\"loc\":{\"$type\":\"location\",\"start\":[1654,1],\"end\":[1679,8]}"},{"Home_Recv_IACK_X_",::romp::location{{1684,1},{1731,8}},"{\"$type\":\"rule\",\"expr\":\"((GUniMsg[Home].Cmd = IACK) | (GUniMsg[Home].Cmd = IACKX))\",\"label\":\"Home_Recv_IACK_X_\",\"loc\":{\"$type\":\"location\",\"start\":[1684,1],\"end\":[1731,8]}"},{"Home_Recv_Nak",::romp::location{{1736,1},{1772,8}},"{\"$type\":\"rule\",\"expr\":\"((GUniMsg[Home].Cmd = NAK) | (GUniMsg[Home].Cmd = NAK_Home))\",\"label\":\"Home_Recv_Nak\",\"loc\":{\"$type\":\"location\",\"start\":[1736,1],\"end\":[1772,8]}"},{"Dir_Recv_NAKC_DIR",::romp::location{{1776,1},{1794,8}},"{\"$type\":\"rule\",\"expr\":\"((GNakcMsg.Cmd = GNAKC_DIR) | (GNakcMsg.Cmd = GNAKC_Nakc))\",\"label\":\"Dir_Recv_NAKC_DIR\",\"loc\":{\"$type\":\"location\",\"start\":[1776,1],\"end\":[1794,8]}"},{"Home_Recv_ACK",::romp::location{{1798,1},{1871,8}},"{\"$type\":\"rule\",\"expr\":\"(GUniMsg[Home].Cmd = ACK)\",\"label\":\"Home_Recv_ACK\",\"loc\":{\"$type\":\"location\",\"start\":[1798,1],\"end\":[1871,8]}"},{"RmtCluster_Recv_Get",::romp::location{{1875,1},{1962,8}},"{\"$type\":\"rule\",\"expr\":\"((((GUniMsg[src].Cmd = RD_RAC) & (GUniMsg[src].Cluster = r)) & (Procs[r].L2.Gblock_WB = false)) & (Procs[r].L2.ifHoldMsg = false))\",\"label\":\"RmtCluster_Recv_Get\",\"loc\":{\"$type\":\"location\",\"start\":[1875,1],\"end\":[1962,8]}"},{"RmtCluster_Recv_GetX",::romp::location{{1968,1},{2086,8}},"{\"$type\":\"rule\",\"expr\":\"((((GUniMsg[src].Cmd = RDX_RAC) & (GUniMsg[src].Cluster = dst)) & (Procs[dst].L2.Gblock_WB = false)) & (Procs[dst].L2.ifHoldMsg = false))\",\"label\":\"RmtCluster_Recv_GetX\",\"loc\":{\"$type\":\"location\",\"start\":[1968,1],\"end\":[2086,8]}"},{"Dir_Recv_DXFER",::romp::location{{2091,1},{2102,8}},"{\"$type\":\"rule\",\"expr\":\"(GShWbMsg.Cmd = DXFER)\",\"label\":\"Dir_Recv_DXFER\",\"loc\":{\"$type\":\"location\",\"start\":[2091,1],\"end\":[2102,8]}"},{"Dir_Recv_ShWb",::romp::location{{2106,1},{2125,8}},"{\"$type\":\"rule\",\"expr\":\"(GShWbMsg.Cmd = SHWB)\",\"label\":\"Dir_Recv_ShWb\",\"loc\":{\"$type\":\"location\",\"start\":[2106,1],\"end\":[2125,8]}"},{"RmtCluster_Recv_ACK",::romp::location{{2130,1},{2208,8}},"{\"$type\":\"rule\",\"expr\":\"(GUniMsg[dst].Cmd = ACK)\",\"label\":\"RmtCluster_Recv_ACK\",\"loc\":{\"$type\":\"location\",\"start\":[2130,1],\"end\":[2208,8]}"},{"RmtCluster_Recv_Nak",::romp::location{{2214,1},{2241,8}},"{\"$type\":\"rule\",\"expr\":\"(GUniMsg[dst].Cmd = NAK)\",\"label\":\"RmtCluster_Recv_Nak\",\"loc\":{\"$type\":\"location\",\"start\":[2214,1],\"end\":[2241,8]}"},{"Cluster_Recv_Inv",::romp::location{{2247,1},{2320,8}},"{\"$type\":\"rule\",\"expr\":\"(GInvMsg[dst].Cmd = INV)\",\"label\":\"Cluster_Recv_Inv\",\"loc\":{\"$type\":\"location\",\"start\":[2247,1],\"end\":[2320,8]}"},{"RmtCluster_Recv_InvAck",::romp::location{{2326,1},{2354,8}},"{\"$type\":\"rule\",\"expr\":\"((GInvMsg[src].Cmd = SACK) & (GInvMsg[src].Cluster = dst))\",\"label\":\"RmtCluster_Recv_InvAck\",\"loc\":{\"$type\":\"location\",\"start\":[2326,1],\"end\":[2354,8]}"},{"RmtCluster_Recv_IACK_X_",::romp::location{{2360,1},{2405,8}},"{\"$type\":\"rule\",\"expr\":\"((GUniMsg[dst].Cmd = IACK) | (GUniMsg[dst].Cmd = IACKX))\",\"label\":\"RmtCluster_Recv_IACK_X_\",\"loc\":{\"$type\":\"location\",\"start\":[2360,1],\"end\":[2405,8]}"},{"Dir_Recv_RmtGet_Put",::romp::location{{2411,1},{2425,8}},"{\"$type\":\"rule\",\"expr\":\"((((Dir.State = Invld) | (Dir.State = Shrd)) & (Dir.isBusy = false)) & (GUniMsg[r].Cmd = RD_H))\",\"label\":\"Dir_Recv_RmtGet_Put\",\"loc\":{\"$type\":\"location\",\"start\":[2411,1],\"end\":[2425,8]}"},{"Dir_Recv_RmtGet__RmtGet_",::romp::location{{2449,1},{2473,8}},"{\"$type\":\"rule\",\"expr\":\"((((Dir.State = Excl) & (Dir.isBusy = false)) & (Dir.isLocal = false)) & (GUniMsg[r].Cmd = RD_H))\",\"label\":\"Dir_Recv_RmtGet__RmtGet_\",\"loc\":{\"$type\":\"location\",\"start\":[2449,1],\"end\":[2473,8]}"},{"Dir_Recv_RmtGetX__RmtGetX_",::romp::location{{2480,1},{2499,8}},"{\"$type\":\"rule\",\"expr\":\"((((Dir.State = Excl) & (Dir.isBusy = false)) & (Dir.isLocal = false)) & (GUniMsg[r].Cmd = RDX_H))\",\"label\":\"Dir_Recv_RmtGetX__RmtGetX_\",\"loc\":{\"$type\":\"location\",\"start\":[2480,1],\"end\":[2499,8]}"},{"Dir_Recv_RmtGetX_isLocal",::romp::location{{2506,1},{2604,8}},"{\"$type\":\"rule\",\"expr\":\"(((((Dir.State = Excl) & (Dir.isBusy = false)) & (Dir.isLocal = true)) & (GUniMsg[r].Cmd = RDX_H)) & (Procs[Home].L2.ifHoldMsg = false))\",\"label\":\"Dir_Recv_RmtGetX_isLocal\",\"loc\":{\"$type\":\"location\",\"start\":[2506,1],\"end\":[2604,8]}"},{"Dir_Recv_RmtGet_isLocal",::romp::location{{2610,1},{2683,8}},"{\"$type\":\"rule\",\"expr\":\"(((((Dir.State = Excl) & (Dir.isBusy = false)) & (Dir.isLocal = true)) & (GUniMsg[r].Cmd = RD_H)) & (Procs[Home].L2.ifHoldMsg = false))\",\"label\":\"Dir_Recv_RmtGet_isLocal\",\"loc\":{\"$type\":\"location\",\"start\":[2610,1],\"end\":[2683,8]}"},{"Dir_Recv_RmtGetX_PutX",::romp::location{{2689,1},{2703,8}},"{\"$type\":\"rule\",\"expr\":\"(((Dir.State = Invld) & (Dir.isBusy = false)) & (GUniMsg[r].Cmd = RDX_H))\",\"label\":\"Dir_Recv_RmtGetX_PutX\",\"loc\":{\"$type\":\"location\",\"start\":[2689,1],\"end\":[2703,8]}"},{"Cluster_WriteBack",::romp::location{{2709,1},{2741,8}},"{\"$type\":\"rule\",\"expr\":\"(((((Procs[p].L2.State = Excl) & (Procs[p].L2.Dirty = true)) & (Procs[p].RAC.State = Inval)) & (Procs[p].L2.HeadPtr = L2)) & (Procs[p].L2.pending = false))\",\"label\":\"Cluster_WriteBack\",\"loc\":{\"$type\":\"location\",\"start\":[2709,1],\"end\":[2741,8]}"},{"Dir_Recv_WB",::romp::location{{2745,1},{2777,8}},"{\"$type\":\"rule\",\"expr\":\"(GWbMsg.Cmd = WB)\",\"label\":\"Dir_Recv_WB\",\"loc\":{\"$type\":\"location\",\"start\":[2745,1],\"end\":[2777,8]}"},{"RmtCluster_Recv_WBAck",::romp::location{{2781,1},{2790,8}},"{\"$type\":\"rule\",\"expr\":\"(GUniMsg[r].Cmd = WB_Ack)\",\"label\":\"RmtCluster_Recv_WBAck\",\"loc\":{\"$type\":\"location\",\"start\":[2781,1],\"end\":[2790,8]}"},{"Dir_Shrd_RmtGetX_PutX",::romp::location{{2796,1},{2843,8}},"{\"$type\":\"rule\",\"expr\":\"(((GUniMsg[r].Cmd = RDX_H) & (Dir.State = Shrd)) & (Dir.isBusy = false))\",\"label\":\"Dir_Shrd_RmtGetX_PutX\",\"loc\":{\"$type\":\"location\",\"start\":[2796,1],\"end\":[2843,8]}"},};
  const ::romp::PropertyInfo PROPERTY_INFOS[] = {{"Funny pending receiving INV_InvAck.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.pending = true)",4294967295,::romp::location{{661,5},{661,78}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny pending receiving INV_InvAck.\",\"expr\":\"(Procs[p].L2.pending = true)\",\"loc\":{\"$type\":\"location\",\"start\":[661,5],\"end\":[661,78]}"},{"Funny forwarded req to itself.",::romp::PropertyType::ASSERTION,"(src != dst)",4294967295,::romp::location{{697,5},{697,57}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny forwarded req to itself.\",\"expr\":\"(src != dst)\",\"loc\":{\"$type\":\"location\",\"start\":[697,5],\"end\":[697,57]}"},{"Funny pending receiving NAKC_Nakc.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.pending = true)",4294967295,::romp::location{{744,5},{744,77}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny pending receiving NAKC_Nakc.\",\"expr\":\"(Procs[p].L2.pending = true)\",\"loc\":{\"$type\":\"location\",\"start\":[744,5],\"end\":[744,77]}"},{"Funny ReqCluster with NAKC_Nakc to L2.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[p].L2.ReqCluster))",4294967295,::romp::location{{748,7},{748,93}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny ReqCluster with NAKC_Nakc to L2.\",\"expr\":\"(!isundefined(Procs[p].L2.ReqCluster))\",\"loc\":{\"$type\":\"location\",\"start\":[748,7],\"end\":[748,93]}"},{"Funny Procs[p].L2.ifHoldMsg value.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.ifHoldMsg = true)",4294967295,::romp::location{{753,7},{753,81}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[p].L2.ifHoldMsg value.\",\"expr\":\"(Procs[p].L2.ifHoldMsg = true)\",\"loc\":{\"$type\":\"location\",\"start\":[753,7],\"end\":[753,81]}"},{"Funny GUniMsg[aux].Cmd value.",::romp::PropertyType::ASSERTION,"(GUniMsg[aux].Cmd = RD_H)",4294967295,::romp::location{{757,11},{757,75}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value.\",\"expr\":\"(GUniMsg[aux].Cmd = RD_H)\",\"loc\":{\"$type\":\"location\",\"start\":[757,11],\"end\":[757,75]}"},{"Funny GUniMsg[aux].Cmd value.",::romp::PropertyType::ASSERTION,"((GUniMsg[aux].Cmd = RD_RAC) & (GUniMsg[aux].Cluster = p))",4294967295,::romp::location{{759,11},{760,44}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value.\",\"expr\":\"((GUniMsg[aux].Cmd = RD_RAC) & (GUniMsg[aux].Cluster = p))\",\"loc\":{\"$type\":\"location\",\"start\":[759,11],\"end\":[760,44]}"},{"Funny GUniMsg[aux].Cmd value.",::romp::PropertyType::ASSERTION,"(GUniMsg[aux].Cmd = RDX_H)",4294967295,::romp::location{{765,11},{765,76}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value.\",\"expr\":\"(GUniMsg[aux].Cmd = RDX_H)\",\"loc\":{\"$type\":\"location\",\"start\":[765,11],\"end\":[765,76]}"},{"Funny GUniMsg[aux].Cmd value.",::romp::PropertyType::ASSERTION,"((GUniMsg[aux].Cmd = RDX_RAC) & (GUniMsg[aux].Cluster = p))",4294967295,::romp::location{{767,11},{768,44}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value.\",\"expr\":\"((GUniMsg[aux].Cmd = RDX_RAC) & (GUniMsg[aux].Cluster = p))\",\"loc\":{\"$type\":\"location\",\"start\":[767,11],\"end\":[768,44]}"},{"Funny pending receiving NAKC_Nakc.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.pending = true)",4294967295,::romp::location{{801,5},{801,77}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny pending receiving NAKC_Nakc.\",\"expr\":\"(Procs[p].L2.pending = true)\",\"loc\":{\"$type\":\"location\",\"start\":[801,5],\"end\":[801,77]}"},{"Funny ReqCluster with NAKC_Nakc to L2.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[p].L2.ReqCluster))",4294967295,::romp::location{{805,7},{805,93}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny ReqCluster with NAKC_Nakc to L2.\",\"expr\":\"(!isundefined(Procs[p].L2.ReqCluster))\",\"loc\":{\"$type\":\"location\",\"start\":[805,7],\"end\":[805,93]}"},{"Funny Procs[p].L2.ifHoldMsg value.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.ifHoldMsg = true)",4294967295,::romp::location{{813,7},{813,81}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[p].L2.ifHoldMsg value.\",\"expr\":\"(Procs[p].L2.ifHoldMsg = true)\",\"loc\":{\"$type\":\"location\",\"start\":[813,7],\"end\":[813,81]}"},{"Funny GUniMsg[aux].Cmd value.",::romp::PropertyType::ASSERTION,"((GUniMsg[aux].Cmd = RD_RAC) & (GUniMsg[aux].Cluster = p))",4294967295,::romp::location{{816,11},{817,44}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value.\",\"expr\":\"((GUniMsg[aux].Cmd = RD_RAC) & (GUniMsg[aux].Cluster = p))\",\"loc\":{\"$type\":\"location\",\"start\":[816,11],\"end\":[817,44]}"},{"Funny GUniMsg[aux].Cmd value.",::romp::PropertyType::ASSERTION,"((GUniMsg[aux].Cmd = RDX_RAC) & (GUniMsg[aux].Cluster = p))",4294967295,::romp::location{{819,11},{820,44}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value.\",\"expr\":\"((GUniMsg[aux].Cmd = RDX_RAC) & (GUniMsg[aux].Cluster = p))\",\"loc\":{\"$type\":\"location\",\"start\":[819,11],\"end\":[820,44]}"},{"Funny L2.State receiving NAKC_SD.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.State != Invld)",4294967295,::romp::location{{827,9},{827,80}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.State receiving NAKC_SD.\",\"expr\":\"(Procs[p].L2.State != Invld)\",\"loc\":{\"$type\":\"location\",\"start\":[827,9],\"end\":[827,80]}"},{"Impossible to this branch.",::romp::PropertyType::ASSERTION,"false",4294967295,::romp::location{{869,2},{869,45}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Impossible to this branch.\",\"expr\":\"false\",\"loc\":{\"$type\":\"location\",\"start\":[869,2],\"end\":[869,45]}"},{"Funny pending receiving NAKC_Nakc.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.pending = true)",4294967295,::romp::location{{903,5},{903,80}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny pending receiving NAKC_Nakc.\",\"expr\":\"(Procs[Home].L2.pending = true)\",\"loc\":{\"$type\":\"location\",\"start\":[903,5],\"end\":[903,80]}"},{"Funny ReqCluster with NAKC_Nakc to L2.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[Home].L2.ReqCluster))",4294967295,::romp::location{{907,7},{907,96}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny ReqCluster with NAKC_Nakc to L2.\",\"expr\":\"(!isundefined(Procs[Home].L2.ReqCluster))\",\"loc\":{\"$type\":\"location\",\"start\":[907,7],\"end\":[907,96]}"},{"Funny Procs[p].L2.ifHoldMsg value.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.ifHoldMsg = true)",4294967295,::romp::location{{915,7},{915,84}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[p].L2.ifHoldMsg value.\",\"expr\":\"(Procs[Home].L2.ifHoldMsg = true)\",\"loc\":{\"$type\":\"location\",\"start\":[915,7],\"end\":[915,84]}"},{"Funny GUniMsg[aux].Cmd value",::romp::PropertyType::ASSERTION,"(GUniMsg[aux].Cmd = RD_H)",4294967295,::romp::location{{918,9},{918,72}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value\",\"expr\":\"(GUniMsg[aux].Cmd = RD_H)\",\"loc\":{\"$type\":\"location\",\"start\":[918,9],\"end\":[918,72]}"},{"Funny GUniMsg[aux].Cmd value.",::romp::PropertyType::ASSERTION,"(GUniMsg[aux].Cmd = RDX_H)",4294967295,::romp::location{{920,11},{920,76}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value.\",\"expr\":\"(GUniMsg[aux].Cmd = RDX_H)\",\"loc\":{\"$type\":\"location\",\"start\":[920,11],\"end\":[920,76]}"},{"Funny L2.State receiving NAKC_SD.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.State != Invld)",4294967295,::romp::location{{927,9},{927,83}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.State receiving NAKC_SD.\",\"expr\":\"(Procs[Home].L2.State != Invld)\",\"loc\":{\"$type\":\"location\",\"start\":[927,9],\"end\":[927,83]}"},{"Impossible to this branch.",::romp::PropertyType::ASSERTION,"false",4294967295,::romp::location{{964,2},{964,45}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Impossible to this branch.\",\"expr\":\"false\",\"loc\":{\"$type\":\"location\",\"start\":[964,2],\"end\":[964,45]}"},{"Funny forwarded req to itself.",::romp::PropertyType::ASSERTION,"(src != dst)",4294967295,::romp::location{{995,5},{995,57}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny forwarded req to itself.\",\"expr\":\"(src != dst)\",\"loc\":{\"$type\":\"location\",\"start\":[995,5],\"end\":[995,57]}"},{"Funny pending receiving SHWB_ShWb.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.pending = true)",4294967295,::romp::location{{1030,5},{1030,77}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny pending receiving SHWB_ShWb.\",\"expr\":\"(Procs[p].L2.pending = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1030,5],\"end\":[1030,77]}"},{"Funny HeadPtr value.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.HeadPtr = dst)",4294967295,::romp::location{{1038,7},{1038,64}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny HeadPtr value.\",\"expr\":\"(Procs[p].L2.HeadPtr = dst)\",\"loc\":{\"$type\":\"location\",\"start\":[1038,7],\"end\":[1038,64]}"},{"Funny HeadPtr value.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.HeadPtr = dst)",4294967295,::romp::location{{1050,7},{1050,64}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny HeadPtr value.\",\"expr\":\"(Procs[p].L2.HeadPtr = dst)\",\"loc\":{\"$type\":\"location\",\"start\":[1050,7],\"end\":[1050,64]}"},{"Funny ReqCluster with SHWB_ShWb to L2.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[p].L2.ReqCluster))",4294967295,::romp::location{{1060,7},{1060,93}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny ReqCluster with SHWB_ShWb to L2.\",\"expr\":\"(!isundefined(Procs[p].L2.ReqCluster))\",\"loc\":{\"$type\":\"location\",\"start\":[1060,7],\"end\":[1060,93]}"},{"Funny ReqType value.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.ReqType = true)",4294967295,::romp::location{{1062,7},{1062,65}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny ReqType value.\",\"expr\":\"(Procs[p].L2.ReqType = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1062,7],\"end\":[1062,65]}"},{"Funny Procs[p].L2.ifHoldMsg value.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.ifHoldMsg = true)",4294967295,::romp::location{{1066,7},{1066,81}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[p].L2.ifHoldMsg value.\",\"expr\":\"(Procs[p].L2.ifHoldMsg = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1066,7],\"end\":[1066,81]}"},{"Funny GUniMsg[aux].Cmd value.",::romp::PropertyType::ASSERTION,"(GUniMsg[aux].Cmd = RD_H)",4294967295,::romp::location{{1069,11},{1069,75}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value.\",\"expr\":\"(GUniMsg[aux].Cmd = RD_H)\",\"loc\":{\"$type\":\"location\",\"start\":[1069,11],\"end\":[1069,75]}"},{"Funny GUniMsg[aux].Cmd value.",::romp::PropertyType::ASSERTION,"((GUniMsg[aux].Cmd = RD_RAC) & (GUniMsg[aux].Cluster = p))",4294967295,::romp::location{{1071,11},{1072,44}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value.\",\"expr\":\"((GUniMsg[aux].Cmd = RD_RAC) & (GUniMsg[aux].Cluster = p))\",\"loc\":{\"$type\":\"location\",\"start\":[1071,11],\"end\":[1072,44]}"},{"Funny pending receiving SHWB_FAck.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.pending = true)",4294967295,::romp::location{{1158,3},{1158,75}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny pending receiving SHWB_FAck.\",\"expr\":\"(Procs[p].L2.pending = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1158,3],\"end\":[1158,75]}"},{"Funny ReqCluster undefined with SHWB_FAck to L2.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[p].L2.ReqCluster))",4294967295,::romp::location{{1165,5},{1165,101}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny ReqCluster undefined with SHWB_FAck to L2.\",\"expr\":\"(!isundefined(Procs[p].L2.ReqCluster))\",\"loc\":{\"$type\":\"location\",\"start\":[1165,5],\"end\":[1165,101]}"},{"Funny SHWB_FAck with ReqType.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.ReqType = false)",4294967295,::romp::location{{1167,5},{1167,73}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny SHWB_FAck with ReqType.\",\"expr\":\"(Procs[p].L2.ReqType = false)\",\"loc\":{\"$type\":\"location\",\"start\":[1167,5],\"end\":[1167,73]}"},{"Funny Procs[p].L2.ifHoldMsg value.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.ifHoldMsg = true)",4294967295,::romp::location{{1172,7},{1172,81}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[p].L2.ifHoldMsg value.\",\"expr\":\"(Procs[p].L2.ifHoldMsg = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1172,7],\"end\":[1172,81]}"},{"Funny GUniMsg[aux].Cmd value.",::romp::PropertyType::ASSERTION,"(GUniMsg[aux].Cmd = RDX_H)",4294967295,::romp::location{{1175,11},{1175,76}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value.\",\"expr\":\"(GUniMsg[aux].Cmd = RDX_H)\",\"loc\":{\"$type\":\"location\",\"start\":[1175,11],\"end\":[1175,76]}"},{"Funny GUniMsg[aux].Cmd value.",::romp::PropertyType::ASSERTION,"((GUniMsg[aux].Cmd = RDX_RAC) & (GUniMsg[aux].Cluster = p))",4294967295,::romp::location{{1177,11},{1178,44}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg[aux].Cmd value.\",\"expr\":\"((GUniMsg[aux].Cmd = RDX_RAC) & (GUniMsg[aux].Cluster = p))\",\"loc\":{\"$type\":\"location\",\"start\":[1177,11],\"end\":[1178,44]}"},{"Funny ProcCmd receiving UNI_Put.",::romp::PropertyType::ASSERTION,"(Procs[p].Proc[dst].ProcCmd = NODE_Get)",4294967295,::romp::location{{1256,5},{1256,86}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny ProcCmd receiving UNI_Put.\",\"expr\":\"(Procs[p].Proc[dst].ProcCmd = NODE_Get)\",\"loc\":{\"$type\":\"location\",\"start\":[1256,5],\"end\":[1256,86]}"},{"PI req grant should have data.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[p].UniMsg[dst].Data))",4294967295,::romp::location{{1265,7},{1265,89}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"PI req grant should have data.\",\"expr\":\"(!isundefined(Procs[p].UniMsg[dst].Data))\",\"loc\":{\"$type\":\"location\",\"start\":[1265,7],\"end\":[1265,89]}"},{"Funny UNI_PutX received.",::romp::PropertyType::ASSERTION,"(Procs[p].Proc[dst].ProcCmd = NODE_GetX)",4294967295,::romp::location{{1281,5},{1281,79}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny UNI_PutX received.\",\"expr\":\"(Procs[p].Proc[dst].ProcCmd = NODE_GetX)\",\"loc\":{\"$type\":\"location\",\"start\":[1281,5],\"end\":[1281,79]}"},{"Excl grant should have data.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[p].UniMsg[dst].Data))",4294967295,::romp::location{{1284,5},{1284,85}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Excl grant should have data.\",\"expr\":\"(!isundefined(Procs[p].UniMsg[dst].Data))\",\"loc\":{\"$type\":\"location\",\"start\":[1284,5],\"end\":[1284,85]}"},{"Funny UNI_PutX received.",::romp::PropertyType::ASSERTION,"(Procs[p].Proc[dst].ProcCmd = NODE_GetX)",4294967295,::romp::location{{1300,5},{1300,79}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny UNI_PutX received.\",\"expr\":\"(Procs[p].Proc[dst].ProcCmd = NODE_GetX)\",\"loc\":{\"$type\":\"location\",\"start\":[1300,5],\"end\":[1300,79]}"},{"Excl grant should have data.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[p].UniMsg[dst].Data))",4294967295,::romp::location{{1303,5},{1303,85}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Excl grant should have data.\",\"expr\":\"(!isundefined(Procs[p].UniMsg[dst].Data))\",\"loc\":{\"$type\":\"location\",\"start\":[1303,5],\"end\":[1303,85]}"},{"Funny WB_Wb without being excl.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.State = Excl)",4294967295,::romp::location{{1352,5},{1352,72}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny WB_Wb without being excl.\",\"expr\":\"(Procs[p].L2.State = Excl)\",\"loc\":{\"$type\":\"location\",\"start\":[1352,5],\"end\":[1352,72]}"},{"Funny Proc[dst] state receiving WB_WbAck.",::romp::PropertyType::ASSERTION,"((Procs[p].Proc[dst].block_WB = true) & (Procs[p].Proc[dst].ProcCmd = NODE_None))",4294967295,::romp::location{{1375,3},{1377,49}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Proc[dst] state receiving WB_WbAck.\",\"expr\":\"((Procs[p].Proc[dst].block_WB = true) & (Procs[p].Proc[dst].ProcCmd = NODE_None))\",\"loc\":{\"$type\":\"location\",\"start\":[1375,3],\"end\":[1377,49]}"},{"Funny undefined ReqId.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[Home].L2.ReqId))",4294967295,::romp::location{{1427,3},{1427,71}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny undefined ReqId.\",\"expr\":\"(!isundefined(Procs[Home].L2.ReqId))\",\"loc\":{\"$type\":\"location\",\"start\":[1427,3],\"end\":[1427,71]}"},{"Funny L2.isRetired value in Dir_HomeGet_Put.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.isRetired = false)",4294967295,::romp::location{{1437,3},{1437,91}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.isRetired value in Dir_HomeGet_Put.\",\"expr\":\"(Procs[Home].L2.isRetired = false)\",\"loc\":{\"$type\":\"location\",\"start\":[1437,3],\"end\":[1437,91]}"},{"Remote excl without headptr1.",::romp::PropertyType::ASSERTION,"(!isundefined(Dir.HeadPtr))",4294967295,::romp::location{{1451,3},{1451,70}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Remote excl without headptr1.\",\"expr\":\"(!isundefined(Dir.HeadPtr))\",\"loc\":{\"$type\":\"location\",\"start\":[1451,3],\"end\":[1451,70]}"},{"Funny Dir.HeadPtr and isLocal.",::romp::PropertyType::ASSERTION,"isundefined(Dir.HeadPtr)",4294967295,::romp::location{{1468,3},{1468,69}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Dir.HeadPtr and isLocal.\",\"expr\":\"isundefined(Dir.HeadPtr)\",\"loc\":{\"$type\":\"location\",\"start\":[1468,3],\"end\":[1468,69]}"},{"Funny undefined ReqId.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[Home].L2.ReqId))",4294967295,::romp::location{{1476,3},{1476,71}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny undefined ReqId.\",\"expr\":\"(!isundefined(Procs[Home].L2.ReqId))\",\"loc\":{\"$type\":\"location\",\"start\":[1476,3],\"end\":[1476,71]}"},{"Funny L2.isRetired value in Dir_HomeGet_isLocal_Put.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.isRetired = false)",4294967295,::romp::location{{1487,3},{1487,99}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.isRetired value in Dir_HomeGet_isLocal_Put.\",\"expr\":\"(Procs[Home].L2.isRetired = false)\",\"loc\":{\"$type\":\"location\",\"start\":[1487,3],\"end\":[1487,99]}"},{"Remote excl without headptr3.",::romp::PropertyType::ASSERTION,"(!isundefined(Dir.HeadPtr))",4294967295,::romp::location{{1501,3},{1501,70}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Remote excl without headptr3.\",\"expr\":\"(!isundefined(Dir.HeadPtr))\",\"loc\":{\"$type\":\"location\",\"start\":[1501,3],\"end\":[1501,70]}"},{"Funny Dir.HeadPtr and isLocal both true.",::romp::PropertyType::ASSERTION,"isundefined(Dir.HeadPtr)",4294967295,::romp::location{{1519,3},{1519,79}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Dir.HeadPtr and isLocal both true.\",\"expr\":\"isundefined(Dir.HeadPtr)\",\"loc\":{\"$type\":\"location\",\"start\":[1519,3],\"end\":[1519,79]}"},{"Funny Procs[Home].L2 state with outside reply42.",::romp::PropertyType::ASSERTION,"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))",4294967295,::romp::location{{1526,3},{1527,56}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[Home].L2 state with outside reply42.\",\"expr\":\"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))\",\"loc\":{\"$type\":\"location\",\"start\":[1526,3],\"end\":[1527,56]}"},{"Funny Procs[Home].L2.ShrSet state.",::romp::PropertyType::ASSERTION,"(forall n : NODE do (Procs[Home].L2.ShrSet[n] = false) endforall & (Procs[Home].L2.InvCnt = 0))",4294967295,::romp::location{{1532,3},{1534,42}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[Home].L2.ShrSet state.\",\"expr\":\"(forall n : NODE do (Procs[Home].L2.ShrSet[n] = false) endforall & (Procs[Home].L2.InvCnt = 0))\",\"loc\":{\"$type\":\"location\",\"start\":[1532,3],\"end\":[1534,42]}"},{"Funny L2.isRetired value in Dir_HomeGetX_isLocal_PutX.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.isRetired = false)",4294967295,::romp::location{{1545,3},{1545,101}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.isRetired value in Dir_HomeGetX_isLocal_PutX.\",\"expr\":\"(Procs[Home].L2.isRetired = false)\",\"loc\":{\"$type\":\"location\",\"start\":[1545,3],\"end\":[1545,101]}"},{"Funny Dir Invld and isLocal/HeadPtr.",::romp::PropertyType::ASSERTION,"((Dir.isLocal = false) & isundefined(Dir.HeadPtr))",4294967295,::romp::location{{1558,3},{1559,44}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Dir Invld and isLocal/HeadPtr.\",\"expr\":\"((Dir.isLocal = false) & isundefined(Dir.HeadPtr))\",\"loc\":{\"$type\":\"location\",\"start\":[1558,3],\"end\":[1559,44]}"},{"Funny Procs[Home].L2 state with outside reply41.",::romp::PropertyType::ASSERTION,"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))",4294967295,::romp::location{{1568,3},{1569,56}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[Home].L2 state with outside reply41.\",\"expr\":\"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))\",\"loc\":{\"$type\":\"location\",\"start\":[1568,3],\"end\":[1569,56]}"},{"Funny L2.isRetired value in Dir_HomeGetX_PutX.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.isRetired = false)",4294967295,::romp::location{{1584,3},{1584,93}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.isRetired value in Dir_HomeGetX_PutX.\",\"expr\":\"(Procs[Home].L2.isRetired = false)\",\"loc\":{\"$type\":\"location\",\"start\":[1584,3],\"end\":[1584,93]}"},{"Funny dir shared with headptr.",::romp::PropertyType::ASSERTION,"isundefined(Dir.HeadPtr)",4294967295,::romp::location{{1599,3},{1599,69}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny dir shared with headptr.\",\"expr\":\"isundefined(Dir.HeadPtr)\",\"loc\":{\"$type\":\"location\",\"start\":[1599,3],\"end\":[1599,69]}"},{"Funny dir shared without any copy.",::romp::PropertyType::ASSERTION,"(Dir.isLocal = true)",4294967295,::romp::location{{1608,5},{1608,69}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny dir shared without any copy.\",\"expr\":\"(Dir.isLocal = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1608,5],\"end\":[1608,69]}"},{"Funny Procs[Home].L2 state with outside reply4.",::romp::PropertyType::ASSERTION,"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))",4294967295,::romp::location{{1631,3},{1632,54}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[Home].L2 state with outside reply4.\",\"expr\":\"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))\",\"loc\":{\"$type\":\"location\",\"start\":[1631,3],\"end\":[1632,54]}"},{"Funny L2.isRetired value in Dir_Shrd_HomeGetX_PutX.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.isRetired = false)",4294967295,::romp::location{{1647,3},{1647,98}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.isRetired value in Dir_Shrd_HomeGetX_PutX.\",\"expr\":\"(Procs[Home].L2.isRetired = false)\",\"loc\":{\"$type\":\"location\",\"start\":[1647,3],\"end\":[1647,98]}"},{"Funny Dir.isBusy state1.",::romp::PropertyType::ASSERTION,"(Dir.isBusy = true)",4294967295,::romp::location{{1691,3},{1691,56}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Dir.isBusy state1.\",\"expr\":\"(Dir.isBusy = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1691,3],\"end\":[1691,56]}"},{"Funny cluster state receive IACK(X).",::romp::PropertyType::ASSERTION,"(Procs[Home].RAC.State = WRDX)",4294967295,::romp::location{{1693,3},{1693,79}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny cluster state receive IACK(X).\",\"expr\":\"(Procs[Home].RAC.State = WRDX)\",\"loc\":{\"$type\":\"location\",\"start\":[1693,3],\"end\":[1693,79]}"},{"Funny Procs[Home].L2 state with outside reply.",::romp::PropertyType::ASSERTION,"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))",4294967295,::romp::location{{1706,3},{1707,54}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[Home].L2 state with outside reply.\",\"expr\":\"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))\",\"loc\":{\"$type\":\"location\",\"start\":[1706,3],\"end\":[1707,54]}"},{"Funny Dir state with home IACK.",::romp::PropertyType::ASSERTION,"(((Dir.State = Excl) & (!isundefined(GUniMsg[Home].Cluster))) & (Dir.HeadPtr = GUniMsg[Home].Cluster))",4294967295,::romp::location{{1718,3},{1720,39}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Dir state with home IACK.\",\"expr\":\"(((Dir.State = Excl) & (!isundefined(GUniMsg[Home].Cluster))) & (Dir.HeadPtr = GUniMsg[Home].Cluster))\",\"loc\":{\"$type\":\"location\",\"start\":[1718,3],\"end\":[1720,39]}"},{"Funny L2.isRetired value in Home_Recv_IACK(X).",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.isRetired = false)",4294967295,::romp::location{{1729,3},{1729,93}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.isRetired value in Home_Recv_IACK(X).\",\"expr\":\"(Procs[Home].L2.isRetired = false)\",\"loc\":{\"$type\":\"location\",\"start\":[1729,3],\"end\":[1729,93]}"},{"Funny Dir.isBusy state2.",::romp::PropertyType::ASSERTION,"(Dir.isBusy = true)",4294967295,::romp::location{{1742,3},{1742,56}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Dir.isBusy state2.\",\"expr\":\"(Dir.isBusy = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1742,3],\"end\":[1742,56]}"},{"Funny Procs[Home].L2 state with outside reply.",::romp::PropertyType::ASSERTION,"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))",4294967295,::romp::location{{1747,3},{1748,53}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[Home].L2 state with outside reply.\",\"expr\":\"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))\",\"loc\":{\"$type\":\"location\",\"start\":[1747,3],\"end\":[1748,53]}"},{"Funny GUniMsg without Cluster.",::romp::PropertyType::ASSERTION,"(!isundefined(GUniMsg[Home].Cluster))",4294967295,::romp::location{{1760,5},{1760,82}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GUniMsg without Cluster.\",\"expr\":\"(!isundefined(GUniMsg[Home].Cluster))\",\"loc\":{\"$type\":\"location\",\"start\":[1760,5],\"end\":[1760,82]}"},{"Funny L2.isRetired value in Home_Recv_Nak.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.isRetired = false)",4294967295,::romp::location{{1770,3},{1770,89}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.isRetired value in Home_Recv_Nak.\",\"expr\":\"(Procs[Home].L2.isRetired = false)\",\"loc\":{\"$type\":\"location\",\"start\":[1770,3],\"end\":[1770,89]}"},{"Funny Dir.isBusy state3.",::romp::PropertyType::ASSERTION,"(Dir.isBusy = true)",4294967295,::romp::location{{1781,3},{1781,56}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Dir.isBusy state3.\",\"expr\":\"(Dir.isBusy = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1781,3],\"end\":[1781,56]}"},{"Funny GNakc_Dir without Cluster.",::romp::PropertyType::ASSERTION,"(!isundefined(GNakcMsg.Cluster))",4294967295,::romp::location{{1785,5},{1785,79}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny GNakc_Dir without Cluster.\",\"expr\":\"(!isundefined(GNakcMsg.Cluster))\",\"loc\":{\"$type\":\"location\",\"start\":[1785,5],\"end\":[1785,79]}"},{"Funny Dir.isBusy state4.",::romp::PropertyType::ASSERTION,"(Dir.isBusy = true)",4294967295,::romp::location{{1803,3},{1803,56}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Dir.isBusy state4.\",\"expr\":\"(Dir.isBusy = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1803,3],\"end\":[1803,56]}"},{"Funny request without pending.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.pending = true)",4294967295,::romp::location{{1806,3},{1806,74}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny request without pending.\",\"expr\":\"(Procs[Home].L2.pending = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1806,3],\"end\":[1806,74]}"},{"Funny ACK in Inval RAC state.",::romp::PropertyType::ASSERTION,"(Procs[Home].RAC.State != Inval)",4294967295,::romp::location{{1807,3},{1807,74}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny ACK in Inval RAC state.\",\"expr\":\"(Procs[Home].RAC.State != Inval)\",\"loc\":{\"$type\":\"location\",\"start\":[1807,3],\"end\":[1807,74]}"},{"Funny dir state with home receiving ACK.",::romp::PropertyType::ASSERTION,"((Dir.State = Excl) & (Dir.HeadPtr = GUniMsg[Home].Cluster))",4294967295,::romp::location{{1820,5},{1821,48}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny dir state with home receiving ACK.\",\"expr\":\"((Dir.State = Excl) & (Dir.HeadPtr = GUniMsg[Home].Cluster))\",\"loc\":{\"$type\":\"location\",\"start\":[1820,5],\"end\":[1821,48]}"},{"Funny Procs[Home].L2 state with outside reply.",::romp::PropertyType::ASSERTION,"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))",4294967295,::romp::location{{1844,5},{1845,55}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[Home].L2 state with outside reply.\",\"expr\":\"((Procs[Home].L2.pending = true) & (!isundefined(Procs[Home].L2.ReqId)))\",\"loc\":{\"$type\":\"location\",\"start\":[1844,5],\"end\":[1845,55]}"},{"Funny dir state with home receiving ACK.",::romp::PropertyType::ASSERTION,"((Dir.State = Excl) & (Dir.HeadPtr = GUniMsg[Home].Cluster))",4294967295,::romp::location{{1848,5},{1849,48}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny dir state with home receiving ACK.\",\"expr\":\"((Dir.State = Excl) & (Dir.HeadPtr = GUniMsg[Home].Cluster))\",\"loc\":{\"$type\":\"location\",\"start\":[1848,5],\"end\":[1849,48]}"},{"Funny L2.isRetired value in Home_Recv_ACK.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.isRetired = false)",4294967295,::romp::location{{1869,3},{1869,89}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.isRetired value in Home_Recv_ACK.\",\"expr\":\"(Procs[Home].L2.isRetired = false)\",\"loc\":{\"$type\":\"location\",\"start\":[1869,3],\"end\":[1869,89]}"},{"Funny forwarded req to itself.",::romp::PropertyType::ASSERTION,"(src != r)",4294967295,::romp::location{{1884,3},{1884,53}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny forwarded req to itself.\",\"expr\":\"(src != r)\",\"loc\":{\"$type\":\"location\",\"start\":[1884,3],\"end\":[1884,53]}"},{"Funny OnlyCopy value.",::romp::PropertyType::ASSERTION,"(Procs[r].L2.OnlyCopy = true)",4294967295,::romp::location{{1919,7},{1919,67}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny OnlyCopy value.\",\"expr\":\"(Procs[r].L2.OnlyCopy = true)\",\"loc\":{\"$type\":\"location\",\"start\":[1919,7],\"end\":[1919,67]}"},{"Funny forwarded req to itself.",::romp::PropertyType::ASSERTION,"(src != dst)",4294967295,::romp::location{{1979,3},{1979,55}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny forwarded req to itself.\",\"expr\":\"(src != dst)\",\"loc\":{\"$type\":\"location\",\"start\":[1979,3],\"end\":[1979,55]}"},{"Funny Procs[dst].L2.OnlyCopy value.",::romp::PropertyType::ASSERTION,"(Procs[dst].L2.OnlyCopy = true)",4294967295,::romp::location{{2024,7},{2024,83}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Procs[dst].L2.OnlyCopy value.\",\"expr\":\"(Procs[dst].L2.OnlyCopy = true)\",\"loc\":{\"$type\":\"location\",\"start\":[2024,7],\"end\":[2024,83]}"},{"Funny Dir.isBusy state5.",::romp::PropertyType::ASSERTION,"(Dir.isBusy = true)",4294967295,::romp::location{{2095,3},{2095,56}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Dir.isBusy state5.\",\"expr\":\"(Dir.isBusy = true)\",\"loc\":{\"$type\":\"location\",\"start\":[2095,3],\"end\":[2095,56]}"},{"Funny Dir.isBusy state6.",::romp::PropertyType::ASSERTION,"(Dir.isBusy = true)",4294967295,::romp::location{{2110,3},{2110,56}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Dir.isBusy state6.\",\"expr\":\"(Dir.isBusy = true)\",\"loc\":{\"$type\":\"location\",\"start\":[2110,3],\"end\":[2110,56]}"},{"Funny ShWb without being excl.",::romp::PropertyType::ASSERTION,"(Dir.State = Excl)",4294967295,::romp::location{{2113,3},{2113,61}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny ShWb without being excl.\",\"expr\":\"(Dir.State = Excl)\",\"loc\":{\"$type\":\"location\",\"start\":[2113,3],\"end\":[2113,61]}"},{"Funny ShWb without remote being excl.",::romp::PropertyType::ASSERTION,"((!isundefined(Dir.HeadPtr)) & (Dir.isLocal = false))",4294967295,::romp::location{{2114,3},{2115,45}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny ShWb without remote being excl.\",\"expr\":\"((!isundefined(Dir.HeadPtr)) & (Dir.isLocal = false))\",\"loc\":{\"$type\":\"location\",\"start\":[2114,3],\"end\":[2115,45]}"},{"Funny ACK in Inval RAC state.",::romp::PropertyType::ASSERTION,"(Procs[dst].RAC.State != Inval)",4294967295,::romp::location{{2135,3},{2135,73}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny ACK in Inval RAC state.\",\"expr\":\"(Procs[dst].RAC.State != Inval)\",\"loc\":{\"$type\":\"location\",\"start\":[2135,3],\"end\":[2135,73]}"},{"Funny L2.ReqId value.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[dst].L2.ReqId))",4294967295,::romp::location{{2146,5},{2146,71}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.ReqId value.\",\"expr\":\"(!isundefined(Procs[dst].L2.ReqId))\",\"loc\":{\"$type\":\"location\",\"start\":[2146,5],\"end\":[2146,71]}"},{"Funny L2.pending value.",::romp::PropertyType::ASSERTION,"(Procs[dst].L2.pending = true)",4294967295,::romp::location{{2147,5},{2147,68}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.pending value.\",\"expr\":\"(Procs[dst].L2.pending = true)\",\"loc\":{\"$type\":\"location\",\"start\":[2147,5],\"end\":[2147,68]}"},{"Funny L2.ReqId value.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[dst].L2.ReqId))",4294967295,::romp::location{{2174,5},{2174,71}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.ReqId value.\",\"expr\":\"(!isundefined(Procs[dst].L2.ReqId))\",\"loc\":{\"$type\":\"location\",\"start\":[2174,5],\"end\":[2174,71]}"},{"Funny L2.pending value.",::romp::PropertyType::ASSERTION,"(Procs[dst].L2.pending = true)",4294967295,::romp::location{{2182,5},{2182,68}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.pending value.\",\"expr\":\"(Procs[dst].L2.pending = true)\",\"loc\":{\"$type\":\"location\",\"start\":[2182,5],\"end\":[2182,68]}"},{"Funny L2.ReqId value.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[dst].L2.ReqId))",4294967295,::romp::location{{2192,5},{2192,71}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.ReqId value.\",\"expr\":\"(!isundefined(Procs[dst].L2.ReqId))\",\"loc\":{\"$type\":\"location\",\"start\":[2192,5],\"end\":[2192,71]}"},{"Funny L2.pending value.",::romp::PropertyType::ASSERTION,"(Procs[dst].L2.pending = true)",4294967295,::romp::location{{2199,5},{2199,68}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.pending value.\",\"expr\":\"(Procs[dst].L2.pending = true)\",\"loc\":{\"$type\":\"location\",\"start\":[2199,5],\"end\":[2199,68]}"},{"Funny L2.isRetired value in RmtCluster_Recv_ACK.",::romp::PropertyType::ASSERTION,"(Procs[dst].L2.isRetired = false)",4294967295,::romp::location{{2206,3},{2206,94}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.isRetired value in RmtCluster_Recv_ACK.\",\"expr\":\"(Procs[dst].L2.isRetired = false)\",\"loc\":{\"$type\":\"location\",\"start\":[2206,3],\"end\":[2206,94]}"},{"Funny NAK in Inval/WINV RAC state2.",::romp::PropertyType::ASSERTION,"((Procs[dst].RAC.State != Inval) & (Procs[dst].RAC.State != WINV))",4294967295,::romp::location{{2219,3},{2220,43}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny NAK in Inval/WINV RAC state2.\",\"expr\":\"((Procs[dst].RAC.State != Inval) & (Procs[dst].RAC.State != WINV))\",\"loc\":{\"$type\":\"location\",\"start\":[2219,3],\"end\":[2220,43]}"},{"Funny L2.ReqId value.",::romp::PropertyType::ASSERTION,"(!isundefined(Procs[dst].L2.ReqId))",4294967295,::romp::location{{2224,3},{2224,69}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.ReqId value.\",\"expr\":\"(!isundefined(Procs[dst].L2.ReqId))\",\"loc\":{\"$type\":\"location\",\"start\":[2224,3],\"end\":[2224,69]}"},{"Funny L2.pending value.",::romp::PropertyType::ASSERTION,"(Procs[dst].L2.pending = true)",4294967295,::romp::location{{2231,3},{2231,66}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.pending value.\",\"expr\":\"(Procs[dst].L2.pending = true)\",\"loc\":{\"$type\":\"location\",\"start\":[2231,3],\"end\":[2231,66]}"},{"Funny L2.isRetired value in RmtCluster_Recv_Nak.",::romp::PropertyType::ASSERTION,"(Procs[dst].L2.isRetired = false)",4294967295,::romp::location{{2239,3},{2239,94}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.isRetired value in RmtCluster_Recv_Nak.\",\"expr\":\"(Procs[dst].L2.isRetired = false)\",\"loc\":{\"$type\":\"location\",\"start\":[2239,3],\"end\":[2239,94]}"},{"Funny L2.State value.",::romp::PropertyType::ASSERTION,"(Procs[dst].L2.OnlyCopy != true)",4294967295,::romp::location{{2257,5},{2257,68}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.State value.\",\"expr\":\"(Procs[dst].L2.OnlyCopy != true)\",\"loc\":{\"$type\":\"location\",\"start\":[2257,5],\"end\":[2257,68]}"},{"Funny InvAck to itself.",::romp::PropertyType::ASSERTION,"(src != dst)",4294967295,::romp::location{{2331,3},{2331,48}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny InvAck to itself.\",\"expr\":\"(src != dst)\",\"loc\":{\"$type\":\"location\",\"start\":[2331,3],\"end\":[2331,48]}"},{"Funny cluster state receive IACK.",::romp::PropertyType::ASSERTION,"(Procs[dst].RAC.State = WRDX)",4294967295,::romp::location{{2366,3},{2366,75}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny cluster state receive IACK.\",\"expr\":\"(Procs[dst].RAC.State = WRDX)\",\"loc\":{\"$type\":\"location\",\"start\":[2366,3],\"end\":[2366,75]}"},{"Funny L2.pending and ReqId values receiving IACK(X).",::romp::PropertyType::ASSERTION,"((Procs[dst].L2.pending = true) & (!isundefined(Procs[dst].L2.ReqId)))",4294967295,::romp::location{{2388,3},{2389,60}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.pending and ReqId values receiving IACK(X).\",\"expr\":\"((Procs[dst].L2.pending = true) & (!isundefined(Procs[dst].L2.ReqId)))\",\"loc\":{\"$type\":\"location\",\"start\":[2388,3],\"end\":[2389,60]}"},{"Funny L2.isRetired value in RmtCluster_Recv_IACK(X).",::romp::PropertyType::ASSERTION,"(Procs[dst].L2.isRetired = false)",4294967295,::romp::location{{2403,3},{2403,98}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.isRetired value in RmtCluster_Recv_IACK(X).\",\"expr\":\"(Procs[dst].L2.isRetired = false)\",\"loc\":{\"$type\":\"location\",\"start\":[2403,3],\"end\":[2403,98]}"},{"Remote excl without headptr2.",::romp::PropertyType::ASSERTION,"(!isundefined(Dir.HeadPtr))",4294967295,::romp::location{{2456,3},{2456,70}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Remote excl without headptr2.\",\"expr\":\"(!isundefined(Dir.HeadPtr))\",\"loc\":{\"$type\":\"location\",\"start\":[2456,3],\"end\":[2456,70]}"},{"Funny L2.OnlyCopy value.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.OnlyCopy = true)",4294967295,::romp::location{{2556,7},{2556,73}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny L2.OnlyCopy value.\",\"expr\":\"(Procs[Home].L2.OnlyCopy = true)\",\"loc\":{\"$type\":\"location\",\"start\":[2556,7],\"end\":[2556,73]}"},{"Funny Home.OnlyCopy value.",::romp::PropertyType::ASSERTION,"(Procs[Home].L2.OnlyCopy = true)",4294967295,::romp::location{{2652,7},{2652,75}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Home.OnlyCopy value.\",\"expr\":\"(Procs[Home].L2.OnlyCopy = true)\",\"loc\":{\"$type\":\"location\",\"start\":[2652,7],\"end\":[2652,75]}"},{"Funny Invld with home having valid copy.",::romp::PropertyType::ASSERTION,"(Dir.isLocal = false)",4294967295,::romp::location{{2697,3},{2697,74}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Invld with home having valid copy.\",\"expr\":\"(Dir.isLocal = false)\",\"loc\":{\"$type\":\"location\",\"start\":[2697,3],\"end\":[2697,74]}"},{"Funny sharer with Excl and dirty.",::romp::PropertyType::ASSERTION,"(Procs[p].L2.ShrSet[n] = false)",4294967295,::romp::location{{2718,5},{2718,79}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny sharer with Excl and dirty.\",\"expr\":\"(Procs[p].L2.ShrSet[n] = false)\",\"loc\":{\"$type\":\"location\",\"start\":[2718,5],\"end\":[2718,79]}"},{"Writeback with funny directory state.",::romp::PropertyType::ASSERTION,"(((Dir.State = Excl) & (!isundefined(Dir.HeadPtr))) & (Dir.isLocal = false))",4294967295,::romp::location{{2764,3},{2765,45}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Writeback with funny directory state.\",\"expr\":\"(((Dir.State = Excl) & (!isundefined(Dir.HeadPtr))) & (Dir.isLocal = false))\",\"loc\":{\"$type\":\"location\",\"start\":[2764,3],\"end\":[2765,45]}"},{"Funny Gblock_WB state receiving WB_Ack",::romp::PropertyType::ASSERTION,"((Procs[r].L2.Gblock_WB = true) & (Procs[r].RAC.State = Inval))",4294967295,::romp::location{{2785,3},{2786,46}},"{\"$type\":\"property\",\"type\":\"assert\",\"label\":\"Funny Gblock_WB state receiving WB_Ack\",\"expr\":\"((Procs[r].L2.Gblock_WB = true) & (Procs[r].RAC.State = Inval))\",\"loc\":{\"$type\":\"location\",\"start\":[2785,3],\"end\":[2786,46]}"},{"CacheStateProp",::romp::PropertyType::INVARIANT,"forall p : Procss do forall n1 : NODE do forall n2 : NODE do ((n1 != n2) -> (!(((Procs[p].Proc[n1].CacheState = CACHE_E) | (Procs[p].Proc[n1].CacheState = CACHE_M)) & ((Procs[p].Proc[n2].CacheState = CACHE_E) | (Procs[p].Proc[n2].CacheState = CACHE_M))))) endforall endforall endforall",4294967295,::romp::location{{2850,1},{2858,14}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do forall n1 : NODE do forall n2 : NODE do ((n1 != n2) -> (!(((Procs[p].Proc[n1].CacheState = CACHE_E) | (Procs[p].Proc[n1].CacheState = CACHE_M)) & ((Procs[p].Proc[n2].CacheState = CACHE_E) | (Procs[p].Proc[n2].CacheState = CACHE_M))))) endforall endforall endforall\",\"label\":\"CacheStateProp\",\"loc\":{\"$type\":\"location\",\"start\":[2850,1],\"end\":[2858,14]}"},{"CacheDataProp",::romp::PropertyType::INVARIANT,"forall p : Procss do forall n : NODE do ((((Procs[p].Proc[n].CacheState = CACHE_E) | (Procs[p].Proc[n].CacheState = CACHE_M)) -> (Procs[p].Proc[n].CacheData = Procs[p].CurrData)) & ((Procs[p].Proc[n].CacheState = CACHE_S) -> ((Procs[p].Collecting -> (Procs[p].Proc[n].CacheData = Procs[p].PrevData)) & ((!Procs[p].Collecting) -> (Procs[p].Proc[n].CacheData = Procs[p].CurrData))))) endforall endforall",4294967295,::romp::location{{2861,1},{2871,10}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do forall n : NODE do ((((Procs[p].Proc[n].CacheState = CACHE_E) | (Procs[p].Proc[n].CacheState = CACHE_M)) -> (Procs[p].Proc[n].CacheData = Procs[p].CurrData)) & ((Procs[p].Proc[n].CacheState = CACHE_S) -> ((Procs[p].Collecting -> (Procs[p].Proc[n].CacheData = Procs[p].PrevData)) & ((!Procs[p].Collecting) -> (Procs[p].Proc[n].CacheData = Procs[p].CurrData))))) endforall endforall\",\"label\":\"CacheDataProp\",\"loc\":{\"$type\":\"location\",\"start\":[2861,1],\"end\":[2871,10]}"},{"OnlyCopyProp",::romp::PropertyType::INVARIANT,"forall p : Procss do (((Procs[p].L2.Dirty = true) | (Procs[p].L2.State = Excl)) -> (Procs[p].L2.OnlyCopy = true)) endforall",4294967295,::romp::location{{2874,1},{2878,6}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do (((Procs[p].L2.Dirty = true) | (Procs[p].L2.State = Excl)) -> (Procs[p].L2.OnlyCopy = true)) endforall\",\"label\":\"OnlyCopyProp\",\"loc\":{\"$type\":\"location\",\"start\":[2874,1],\"end\":[2878,6]}"},{"CacheInvldDataProp",::romp::PropertyType::INVARIANT,"forall p : Procss do forall n : NODE do ((Procs[p].Proc[n].CacheState = CACHE_I) -> isundefined(Procs[p].Proc[n].CacheData)) endforall endforall",4294967295,::romp::location{{2880,1},{2884,10}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do forall n : NODE do ((Procs[p].Proc[n].CacheState = CACHE_I) -> isundefined(Procs[p].Proc[n].CacheData)) endforall endforall\",\"label\":\"CacheInvldDataProp\",\"loc\":{\"$type\":\"location\",\"start\":[2880,1],\"end\":[2884,10]}"},{"L2InvldDataProp",::romp::PropertyType::INVARIANT,"forall p : Procss do ((Procs[p].L2.State = Invld) -> ((isundefined(Procs[p].L2.Data) & (Procs[p].L2.OnlyCopy = false)) & (Procs[p].L2.Dirty = false))) endforall",4294967295,::romp::location{{2887,1},{2894,6}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do ((Procs[p].L2.State = Invld) -> ((isundefined(Procs[p].L2.Data) & (Procs[p].L2.OnlyCopy = false)) & (Procs[p].L2.Dirty = false))) endforall\",\"label\":\"L2InvldDataProp\",\"loc\":{\"$type\":\"location\",\"start\":[2887,1],\"end\":[2894,6]}"},{"Remote_cluster_cannot_be_WRDO_",::romp::PropertyType::INVARIANT,"forall r : Rmt do (Procs[r].RAC.State != WRDO) endforall",4294967295,::romp::location{{2899,1},{2902,6}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall r : Rmt do (Procs[r].RAC.State != WRDO) endforall\",\"label\":\"Remote_cluster_cannot_be_WRDO_\",\"loc\":{\"$type\":\"location\",\"start\":[2899,1],\"end\":[2902,6]}"},{"ClusterStateProp",::romp::PropertyType::INVARIANT,"forall p : Procss do forall q : Procss do (!((p != q) & ((Procs[p].L2.State = Excl) & (Procs[q].L2.State = Excl)))) endforall endforall",4294967295,::romp::location{{2905,1},{2910,10}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do forall q : Procss do (!((p != q) & ((Procs[p].L2.State = Excl) & (Procs[q].L2.State = Excl)))) endforall endforall\",\"label\":\"ClusterStateProp\",\"loc\":{\"$type\":\"location\",\"start\":[2905,1],\"end\":[2910,10]}"},{"InvldDataProp",::romp::PropertyType::INVARIANT,"forall p : Procss do ((Procs[p].L2.State = Invld) -> isundefined(Procs[p].L2.Data)) endforall",4294967295,::romp::location{{2913,1},{2917,6}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do ((Procs[p].L2.State = Invld) -> isundefined(Procs[p].L2.Data)) endforall\",\"label\":\"InvldDataProp\",\"loc\":{\"$type\":\"location\",\"start\":[2913,1],\"end\":[2917,6]}"},{"RACINvalProp",::romp::PropertyType::INVARIANT,"forall p : Procss do ((Procs[p].RAC.State = Inval) -> (Procs[p].RAC.InvCnt = 0)) endforall",4294967295,::romp::location{{2920,1},{2924,6}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do ((Procs[p].RAC.State = Inval) -> (Procs[p].RAC.InvCnt = 0)) endforall\",\"label\":\"RACINvalProp\",\"loc\":{\"$type\":\"location\",\"start\":[2920,1],\"end\":[2924,6]}"},{"InvStateProp",::romp::PropertyType::INVARIANT,"forall p : Procss do forall q : Procss do ((((p != q) & (Procs[p].RAC.State = WINV)) & (Procs[q].L2.State = Shrd)) -> (GInvMsg[q].Cmd = INV)) endforall endforall",4294967295,::romp::location{{2928,1},{2934,10}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do forall q : Procss do ((((p != q) & (Procs[p].RAC.State = WINV)) & (Procs[q].L2.State = Shrd)) -> (GInvMsg[q].Cmd = INV)) endforall endforall\",\"label\":\"InvStateProp\",\"loc\":{\"$type\":\"location\",\"start\":[2928,1],\"end\":[2934,10]}"},{"MemDataProp",::romp::PropertyType::INVARIANT,"((!(Dir.State = Excl)) -> (Dir.Mem = Dir.CurrData))",4294967295,::romp::location{{2963,1},{2964,52}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"((!(Dir.State = Excl)) -> (Dir.Mem = Dir.CurrData))\",\"label\":\"MemDataProp\",\"loc\":{\"$type\":\"location\",\"start\":[2963,1],\"end\":[2964,52]}"},{"tmpProp",::romp::PropertyType::INVARIANT,"forall p : Procss do forall src : NODE do ((Procs[p].InvMsg[src].Cmd = INV_InvAck) -> (Procs[p].L2.pending = true)) endforall endforall",4294967295,::romp::location{{2988,1},{2994,8}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do forall src : NODE do ((Procs[p].InvMsg[src].Cmd = INV_InvAck) -> (Procs[p].L2.pending = true)) endforall endforall\",\"label\":\"tmpProp\",\"loc\":{\"$type\":\"location\",\"start\":[2988,1],\"end\":[2994,8]}"},{"L2_InvCnt__0",::romp::PropertyType::INVARIANT,"forall p : Procss do forall src : NODE do ((Procs[p].InvMsg[src].Cmd = INV_InvAck) -> (Procs[p].L2.InvCnt > 0)) endforall endforall",4294967295,::romp::location{{2997,1},{3003,8}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do forall src : NODE do ((Procs[p].InvMsg[src].Cmd = INV_InvAck) -> (Procs[p].L2.InvCnt > 0)) endforall endforall\",\"label\":\"L2_InvCnt__0\",\"loc\":{\"$type\":\"location\",\"start\":[2997,1],\"end\":[3003,8]}"},{"Nak_Inval_WINV",::romp::PropertyType::INVARIANT,"forall p : Procss do ((GUniMsg[p].Cmd = NAK) -> ((Procs[p].RAC.State != Inval) & (Procs[p].RAC.State != WINV))) endforall",4294967295,::romp::location{{3006,1},{3011,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do ((GUniMsg[p].Cmd = NAK) -> ((Procs[p].RAC.State != Inval) & (Procs[p].RAC.State != WINV))) endforall\",\"label\":\"Nak_Inval_WINV\",\"loc\":{\"$type\":\"location\",\"start\":[3006,1],\"end\":[3011,4]}"},{"Uni_PutwithDataProp",::romp::PropertyType::INVARIANT,"forall p : Procss do forall n : NODE do ((Procs[p].UniMsg[n].Cmd = UNI_Put) -> (!isundefined(Procs[p].UniMsg[n].Data))) endforall endforall",4294967295,::romp::location{{3016,1},{3022,8}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do forall n : NODE do ((Procs[p].UniMsg[n].Cmd = UNI_Put) -> (!isundefined(Procs[p].UniMsg[n].Data))) endforall endforall\",\"label\":\"Uni_PutwithDataProp\",\"loc\":{\"$type\":\"location\",\"start\":[3016,1],\"end\":[3022,8]}"},{"HomeRecvIACK_X_Prop",::romp::PropertyType::INVARIANT,"(((GUniMsg[Home].Cmd = IACK) | (GUniMsg[Home].Cmd = IACKX)) -> (Dir.isBusy = true))",4294967295,::romp::location{{3024,1},{3028,20}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"(((GUniMsg[Home].Cmd = IACK) | (GUniMsg[Home].Cmd = IACKX)) -> (Dir.isBusy = true))\",\"label\":\"HomeRecvIACK_X_Prop\",\"loc\":{\"$type\":\"location\",\"start\":[3024,1],\"end\":[3028,20]}"},{"isRetiredProp1",::romp::PropertyType::INVARIANT,"forall p : Procss do ((Procs[p].L2.isRetired = true) -> (((Procs[p].RAC.State = Inval) | (Procs[p].RAC.State = WINV)) | (Procs[p].L2.OnlyCopy = true))) endforall",4294967295,::romp::location{{3031,1},{3038,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do ((Procs[p].L2.isRetired = true) -> (((Procs[p].RAC.State = Inval) | (Procs[p].RAC.State = WINV)) | (Procs[p].L2.OnlyCopy = true))) endforall\",\"label\":\"isRetiredProp1\",\"loc\":{\"$type\":\"location\",\"start\":[3031,1],\"end\":[3038,4]}"},{"isRetiredProp2",::romp::PropertyType::INVARIANT,"forall p : Procss do (((Procs[p].RAC.State = Inval) | (Procs[p].RAC.State = WINV)) -> (Procs[p].L2.isRetired = true)) endforall",4294967295,::romp::location{{3041,1},{3047,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do (((Procs[p].RAC.State = Inval) | (Procs[p].RAC.State = WINV)) -> (Procs[p].L2.isRetired = true)) endforall\",\"label\":\"isRetiredProp2\",\"loc\":{\"$type\":\"location\",\"start\":[3041,1],\"end\":[3047,4]}"},{"StateProp",::romp::PropertyType::INVARIANT,"((Dir.isLocal = false) -> (Procs[Home].L2.State != Excl))",4294967295,::romp::location{{3050,1},{3053,31}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"((Dir.isLocal = false) -> (Procs[Home].L2.State != Excl))\",\"label\":\"StateProp\",\"loc\":{\"$type\":\"location\",\"start\":[3050,1],\"end\":[3053,31]}"},{"HeadPtrProp",::romp::PropertyType::INVARIANT,"forall p : Procss do ((((Procs[p].L2.pending = false) & (!isundefined(Procs[p].L2.HeadPtr))) & (Procs[p].L2.HeadPtr = L2)) -> (Procs[p].L2.State != Invld)) endforall",4294967295,::romp::location{{3056,1},{3063,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do ((((Procs[p].L2.pending = false) & (!isundefined(Procs[p].L2.HeadPtr))) & (Procs[p].L2.HeadPtr = L2)) -> (Procs[p].L2.State != Invld)) endforall\",\"label\":\"HeadPtrProp\",\"loc\":{\"$type\":\"location\",\"start\":[3056,1],\"end\":[3063,4]}"},{"Excl__OnlyCopy",::romp::PropertyType::INVARIANT,"forall p : Procss do ((Procs[p].L2.State = Excl) -> (Procs[p].L2.OnlyCopy = true)) endforall",4294967295,::romp::location{{3066,1},{3071,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do ((Procs[p].L2.State = Excl) -> (Procs[p].L2.OnlyCopy = true)) endforall\",\"label\":\"Excl__OnlyCopy\",\"loc\":{\"$type\":\"location\",\"start\":[3066,1],\"end\":[3071,4]}"},{"HeadPtrL2__NoSharers",::romp::PropertyType::INVARIANT,"forall p : Procss do (((!isundefined(Procs[p].L2.HeadPtr)) & (Procs[p].L2.HeadPtr = L2)) -> forall n : NODE do (Procs[p].L2.ShrSet[n] = false) endforall) endforall",4294967295,::romp::location{{3074,1},{3082,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do (((!isundefined(Procs[p].L2.HeadPtr)) & (Procs[p].L2.HeadPtr = L2)) -> forall n : NODE do (Procs[p].L2.ShrSet[n] = false) endforall) endforall\",\"label\":\"HeadPtrL2__NoSharers\",\"loc\":{\"$type\":\"location\",\"start\":[3074,1],\"end\":[3082,4]}"},{"HeadPtrL2OnlyCopy__Excl",::romp::PropertyType::INVARIANT,"forall p : Procss do ((((!isundefined(Procs[p].L2.HeadPtr)) & (Procs[p].L2.HeadPtr = L2)) & (Procs[p].L2.OnlyCopy = true)) -> (Procs[p].L2.State = Excl)) endforall",4294967295,::romp::location{{3086,1},{3093,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do ((((!isundefined(Procs[p].L2.HeadPtr)) & (Procs[p].L2.HeadPtr = L2)) & (Procs[p].L2.OnlyCopy = true)) -> (Procs[p].L2.State = Excl)) endforall\",\"label\":\"HeadPtrL2OnlyCopy__Excl\",\"loc\":{\"$type\":\"location\",\"start\":[3086,1],\"end\":[3093,4]}"},{"HeadPtrL2_OnlyCopy__Shrd",::romp::PropertyType::INVARIANT,"forall p : Procss do ((((!isundefined(Procs[p].L2.HeadPtr)) & (Procs[p].L2.HeadPtr = L2)) & (Procs[p].L2.OnlyCopy = false)) -> (Procs[p].L2.State = Shrd)) endforall",4294967295,::romp::location{{3097,1},{3104,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do ((((!isundefined(Procs[p].L2.HeadPtr)) & (Procs[p].L2.HeadPtr = L2)) & (Procs[p].L2.OnlyCopy = false)) -> (Procs[p].L2.State = Shrd)) endforall\",\"label\":\"HeadPtrL2_OnlyCopy__Shrd\",\"loc\":{\"$type\":\"location\",\"start\":[3097,1],\"end\":[3104,4]}"},{"_Invld___Gblock_WB",::romp::PropertyType::INVARIANT,"forall p : Procss do ((Procs[p].L2.State != Invld) -> (Procs[p].L2.Gblock_WB = false)) endforall",4294967295,::romp::location{{3107,1},{3112,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do ((Procs[p].L2.State != Invld) -> (Procs[p].L2.Gblock_WB = false)) endforall\",\"label\":\"_Invld___Gblock_WB\",\"loc\":{\"$type\":\"location\",\"start\":[3107,1],\"end\":[3112,4]}"},{"NAKC_Nakc__Excl_Inval",::romp::PropertyType::INVARIANT,"forall p : Procss do (((Procs[p].NakcMsg.Cmd = NAKC_Nakc) & (Procs[p].NakcMsg.Aux = L2)) -> ((Procs[p].L2.State = Excl) & (Procs[p].RAC.State = Inval))) endforall",4294967295,::romp::location{{3115,1},{3122,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do (((Procs[p].NakcMsg.Cmd = NAKC_Nakc) & (Procs[p].NakcMsg.Aux = L2)) -> ((Procs[p].L2.State = Excl) & (Procs[p].RAC.State = Inval))) endforall\",\"label\":\"NAKC_Nakc__Excl_Inval\",\"loc\":{\"$type\":\"location\",\"start\":[3115,1],\"end\":[3122,4]}"},{"NAKC_SD__Excl_Inval__Gblock_WB",::romp::PropertyType::INVARIANT,"forall p : Procss do (((Procs[p].NakcMsg.Cmd = NAKC_SD) & (Procs[p].NakcMsg.Aux = L2)) -> (((Procs[p].L2.State = Excl) & (Procs[p].RAC.State = Inval)) & (Procs[p].L2.Gblock_WB = false))) endforall",4294967295,::romp::location{{3125,1},{3133,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do (((Procs[p].NakcMsg.Cmd = NAKC_SD) & (Procs[p].NakcMsg.Aux = L2)) -> (((Procs[p].L2.State = Excl) & (Procs[p].RAC.State = Inval)) & (Procs[p].L2.Gblock_WB = false))) endforall\",\"label\":\"NAKC_SD__Excl_Inval__Gblock_WB\",\"loc\":{\"$type\":\"location\",\"start\":[3125,1],\"end\":[3133,4]}"},{"SHWB_ShWb_L2__Excl_Inval",::romp::PropertyType::INVARIANT,"forall p : Procss do (((Procs[p].ShWbMsg.Cmd = SHWB_ShWb) & (Procs[p].ShWbMsg.Aux = L2)) -> ((Procs[p].L2.State = Excl) & (Procs[p].RAC.State = Inval))) endforall",4294967295,::romp::location{{3137,1},{3144,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do (((Procs[p].ShWbMsg.Cmd = SHWB_ShWb) & (Procs[p].ShWbMsg.Aux = L2)) -> ((Procs[p].L2.State = Excl) & (Procs[p].RAC.State = Inval))) endforall\",\"label\":\"SHWB_ShWb_L2__Excl_Inval\",\"loc\":{\"$type\":\"location\",\"start\":[3137,1],\"end\":[3144,4]}"},{"SHWB_ShWb__Excl",::romp::PropertyType::INVARIANT,"forall p : Procss do ((Procs[p].ShWbMsg.Cmd = SHWB_ShWb) -> (Procs[p].L2.State = Excl)) endforall",4294967295,::romp::location{{3148,1},{3153,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do ((Procs[p].ShWbMsg.Cmd = SHWB_ShWb) -> (Procs[p].L2.State = Excl)) endforall\",\"label\":\"SHWB_ShWb__Excl\",\"loc\":{\"$type\":\"location\",\"start\":[3148,1],\"end\":[3153,4]}"},{"SHWB_FAck_L2__Excl_Inval",::romp::PropertyType::INVARIANT,"forall p : Procss do (((Procs[p].ShWbMsg.Cmd = SHWB_FAck) & (Procs[p].ShWbMsg.Aux = L2)) -> ((Procs[p].L2.State = Excl) & (Procs[p].RAC.State = Inval))) endforall",4294967295,::romp::location{{3156,1},{3163,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do (((Procs[p].ShWbMsg.Cmd = SHWB_FAck) & (Procs[p].ShWbMsg.Aux = L2)) -> ((Procs[p].L2.State = Excl) & (Procs[p].RAC.State = Inval))) endforall\",\"label\":\"SHWB_FAck_L2__Excl_Inval\",\"loc\":{\"$type\":\"location\",\"start\":[3156,1],\"end\":[3163,4]}"},{"l2HeadPtr_RD_RAC__Excl",::romp::PropertyType::INVARIANT,"forall p : Procss do forall src : Procss do (((((((GUniMsg[src].Cmd = RD_RAC) | (GUniMsg[src].Cmd = RDX_RAC)) & (GUniMsg[src].Cluster = p)) & (Procs[p].RAC.State = Inval)) & (!isundefined(Procs[p].L2.HeadPtr))) & (Procs[p].L2.HeadPtr = L2)) -> (Procs[p].L2.State = Excl)) endforall endforall",4294967295,::romp::location{{3166,1},{3177,8}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall p : Procss do forall src : Procss do (((((((GUniMsg[src].Cmd = RD_RAC) | (GUniMsg[src].Cmd = RDX_RAC)) & (GUniMsg[src].Cluster = p)) & (Procs[p].RAC.State = Inval)) & (!isundefined(Procs[p].L2.HeadPtr))) & (Procs[p].L2.HeadPtr = L2)) -> (Procs[p].L2.State = Excl)) endforall endforall\",\"label\":\"l2HeadPtr_RD_RAC__Excl\",\"loc\":{\"$type\":\"location\",\"start\":[3166,1],\"end\":[3177,8]}"},};
/* the number of cover property statements & rules in the model */
#define _ROMP_COVER_PROP_COUNT (0ul)
/* the number of liveness property rules in the model */
#define _ROMP_LIVENESS_PROP_COUNT (0ul)

  const ::romp::PropertyInfo* LIVENESS_INFOS[_ROMP_LIVENESS_PROP_COUNT] = {};
  const ::romp::PropertyInfo* COVER_INFOS[_ROMP_COVER_PROP_COUNT] = {};

  const ::romp::StartStateInfo STARTSTATE_INFOS[] = {{"Init",::romp::location{{215,1},{283,14}},"{\"$type\":\"startstate\",\"label\":\"Init\",\"loc\":{\"$type\":\"location\",\"start\":[215,1],\"end\":[283,14]}"},};
  const ::romp::FunctInfo FUNCT_INFOS[] = {};
  const ::romp::MErrorInfo ERROR_INFOS[] = {{"Funny Home state receiving SACK.",::romp::location{{1674,5},{1674,45}},"{\"$type\":\"error-statement\",\"label\":\"Funny Home state receiving SACK.\",\"loc\":{\"$type\":\"location\",\"start\":[1674,5],\"end\":[1674,45]}"},{"Funny WRD/WRDX state in home.",::romp::location{{1863,5},{1863,42}},"{\"$type\":\"error-statement\",\"label\":\"Funny WRD/WRDX state in home.\",\"loc\":{\"$type\":\"location\",\"start\":[1863,5],\"end\":[1863,42]}"},{"No remote cluster can be WRDO.",::romp::location{{2161,5},{2161,43}},"{\"$type\":\"error-statement\",\"label\":\"No remote cluster can be WRDO.\",\"loc\":{\"$type\":\"location\",\"start\":[2161,5],\"end\":[2161,43]}"},{"Funny WINV receiving INV.",::romp::location{{2309,7},{2309,40}},"{\"$type\":\"error-statement\",\"label\":\"Funny WINV receiving INV.\",\"loc\":{\"$type\":\"location\",\"start\":[2309,7],\"end\":[2309,40]}"},{"Funny RAC.State value.",::romp::location{{2349,5},{2349,35}},"{\"$type\":\"error-statement\",\"label\":\"Funny RAC.State value.\",\"loc\":{\"$type\":\"location\",\"start\":[2349,5],\"end\":[2349,35]}"},};

} // namespace __info__


#pragma endregion metadata__generated_code



#pragma region rule_caller__generated_code

namespace __caller__ {

// << ==================================== Rule Expansions ===================================== >> 

/* --- Rules Generated by: `L1_Update_Data` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1_Update_Data__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(Home, _romp_NODE_2_1, _romp_Datas_2_1); }
 void __romp__Rule_action__L1_Update_Data__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(Home, _romp_NODE_2_1, _romp_Datas_2_1); }
 bool __romp__Rule_guard__L1_Update_Data__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(Home, _romp_NODE_2_1, _romp_Datas_2_2); }
 void __romp__Rule_action__L1_Update_Data__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(Home, _romp_NODE_2_1, _romp_Datas_2_2); }
 bool __romp__Rule_guard__L1_Update_Data__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(Home, _romp_NODE_2_2, _romp_Datas_2_1); }
 void __romp__Rule_action__L1_Update_Data__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(Home, _romp_NODE_2_2, _romp_Datas_2_1); }
 bool __romp__Rule_guard__L1_Update_Data__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(Home, _romp_NODE_2_2, _romp_Datas_2_2); }
 void __romp__Rule_action__L1_Update_Data__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(Home, _romp_NODE_2_2, _romp_Datas_2_2); }
 bool __romp__Rule_guard__L1_Update_Data__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_Datas_2_1); }
 void __romp__Rule_action__L1_Update_Data__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_Datas_2_1); }
 bool __romp__Rule_guard__L1_Update_Data__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_Datas_2_2); }
 void __romp__Rule_action__L1_Update_Data__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_Datas_2_2); }
 bool __romp__Rule_guard__L1_Update_Data__6(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_Datas_2_1); }
 void __romp__Rule_action__L1_Update_Data__6(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_Datas_2_1); }
 bool __romp__Rule_guard__L1_Update_Data__7(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_Datas_2_2); }
 void __romp__Rule_action__L1_Update_Data__7(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_Datas_2_2); }
 bool __romp__Rule_guard__L1_Update_Data__8(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_Datas_2_1); }
 void __romp__Rule_action__L1_Update_Data__8(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_Datas_2_1); }
 bool __romp__Rule_guard__L1_Update_Data__9(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_Datas_2_2); }
 void __romp__Rule_action__L1_Update_Data__9(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_Datas_2_2); }
 bool __romp__Rule_guard__L1_Update_Data__10(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_Datas_2_1); }
 void __romp__Rule_action__L1_Update_Data__10(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_Datas_2_1); }
 bool __romp__Rule_guard__L1_Update_Data__11(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Update_Data(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_Datas_2_2); }
 void __romp__Rule_action__L1_Update_Data__11(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Update_Data(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_Datas_2_2); }
/* --- Rules Generated by: `L1_Get` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1_Get__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Get(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Get__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Get(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Get__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Get(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Get__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Get(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Get__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Get(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Get__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Get(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Get__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Get(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Get__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Get(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Get__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Get(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Get__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Get(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Get__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Get(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Get__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Get(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L2_Recv_Get_Put` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2_Recv_Get_Put__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_Put(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_Get_Put__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_Put(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_Get_Put__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_Put(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_Get_Put__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_Put(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_Recv_Get_Put__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_Get_Put__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_Get_Put__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_Get_Put__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_Recv_Get_Put__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_Get_Put__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_Get_Put__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_Get_Put__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L2_busy_Recv_Get_X__Nak` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2_busy_Recv_Get_X__Nak__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_busy_Recv_Get_X__Nak(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_busy_Recv_Get_X__Nak__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_busy_Recv_Get_X__Nak(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_busy_Recv_Get_X__Nak__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_busy_Recv_Get_X__Nak(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_busy_Recv_Get_X__Nak__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_busy_Recv_Get_X__Nak(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_busy_Recv_Get_X__Nak__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_busy_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_busy_Recv_Get_X__Nak__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_busy_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_busy_Recv_Get_X__Nak__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_busy_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_busy_Recv_Get_X__Nak__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_busy_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_busy_Recv_Get_X__Nak__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_busy_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_busy_Recv_Get_X__Nak__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_busy_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_busy_Recv_Get_X__Nak__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_busy_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_busy_Recv_Get_X__Nak__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_busy_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L2HeadPtr_Recv_Get_Put` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2HeadPtr_Recv_Get_Put__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_Get_Put(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L2HeadPtr_Recv_Get_Put__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_Get_Put(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2HeadPtr_Recv_Get_Put__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_Get_Put(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L2HeadPtr_Recv_Get_Put__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_Get_Put(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2HeadPtr_Recv_Get_Put__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L2HeadPtr_Recv_Get_Put__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2HeadPtr_Recv_Get_Put__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L2HeadPtr_Recv_Get_Put__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2HeadPtr_Recv_Get_Put__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L2HeadPtr_Recv_Get_Put__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2HeadPtr_Recv_Get_Put__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L2HeadPtr_Recv_Get_Put__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L2_Fwd_Get_X_` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2_Fwd_Get_X___0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Fwd_Get_X_(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Fwd_Get_X___0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Fwd_Get_X_(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Fwd_Get_X___1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Fwd_Get_X_(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Fwd_Get_X___1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Fwd_Get_X_(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_Fwd_Get_X___2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Fwd_Get_X_(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Fwd_Get_X___2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Fwd_Get_X_(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Fwd_Get_X___3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Fwd_Get_X_(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Fwd_Get_X___3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Fwd_Get_X_(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_Fwd_Get_X___4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Fwd_Get_X_(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Fwd_Get_X___4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Fwd_Get_X_(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Fwd_Get_X___5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Fwd_Get_X_(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Fwd_Get_X___5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Fwd_Get_X_(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L2_Recv_Get_X__OutGet_X_` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2_Recv_Get_X__OutGet_X___0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_X__OutGet_X_(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_Get_X__OutGet_X___0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_X__OutGet_X_(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_Get_X__OutGet_X___1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_X__OutGet_X_(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_Get_X__OutGet_X___1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_X__OutGet_X_(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_Recv_Get_X__OutGet_X___2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_X__OutGet_X_(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_Get_X__OutGet_X___2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_X__OutGet_X_(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_Get_X__OutGet_X___3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_X__OutGet_X_(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_Get_X__OutGet_X___3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_X__OutGet_X_(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_Recv_Get_X__OutGet_X___4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_X__OutGet_X_(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_Get_X__OutGet_X___4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_X__OutGet_X_(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_Get_X__OutGet_X___5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_Get_X__OutGet_X_(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_Get_X__OutGet_X___5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_Get_X__OutGet_X_(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L1_GetX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1_GetX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_GetX(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_GetX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_GetX(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_GetX__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_GetX(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_GetX__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_GetX(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_GetX__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_GetX(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_GetX__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_GetX(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_GetX__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_GetX(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_GetX__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_GetX(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_GetX__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_GetX(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_GetX__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_GetX(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_GetX__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_GetX(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_GetX__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_GetX(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L2HeadPtr_Recv_GetX_PutX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L2Shrd_Recv_GetX__PutX_` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2Shrd_Recv_GetX__PutX___0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2Shrd_Recv_GetX__PutX_(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L2Shrd_Recv_GetX__PutX___0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2Shrd_Recv_GetX__PutX_(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2Shrd_Recv_GetX__PutX___1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2Shrd_Recv_GetX__PutX_(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L2Shrd_Recv_GetX__PutX___1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2Shrd_Recv_GetX__PutX_(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2Shrd_Recv_GetX__PutX___2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2Shrd_Recv_GetX__PutX_(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L2Shrd_Recv_GetX__PutX___2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2Shrd_Recv_GetX__PutX_(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2Shrd_Recv_GetX__PutX___3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2Shrd_Recv_GetX__PutX_(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L2Shrd_Recv_GetX__PutX___3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2Shrd_Recv_GetX__PutX_(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2Shrd_Recv_GetX__PutX___4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2Shrd_Recv_GetX__PutX_(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L2Shrd_Recv_GetX__PutX___4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2Shrd_Recv_GetX__PutX_(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2Shrd_Recv_GetX__PutX___5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2Shrd_Recv_GetX__PutX_(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L2Shrd_Recv_GetX__PutX___5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2Shrd_Recv_GetX__PutX_(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L1_Recv_Inv` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1_Recv_Inv__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Inv(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_Inv__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Inv(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_Inv__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Inv(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_Inv__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Inv(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_Inv__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Inv(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_Inv__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Inv(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_Inv__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Inv(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_Inv__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Inv(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_Inv__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Inv(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_Inv__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Inv(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_Inv__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Inv(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_Inv__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Inv(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L2_Recv_InvAck` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2_Recv_InvAck__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_InvAck(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_InvAck__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_InvAck(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_InvAck__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_InvAck(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_InvAck__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_InvAck(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_Recv_InvAck__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_InvAck(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_InvAck__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_InvAck(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_InvAck__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_InvAck(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_InvAck__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_InvAck(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_Recv_InvAck__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_InvAck(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_InvAck__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_InvAck(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_InvAck__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_InvAck(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_InvAck__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_InvAck(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L1Rmt_Recv_Get_X__Nak` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_1, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_1, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_2, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_2, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(Home, _romp_NODE_2_2, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__6(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__6(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__7(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__7(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__8(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_1, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__8(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_1, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__9(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__9(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__10(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__10(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__11(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_2, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__11(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_1, _romp_NODE_2_2, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__12(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__12(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__13(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__13(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__14(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_1, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__14(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_1, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__15(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__15(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__16(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__16(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__17(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_2, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_X__Nak__17(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_X__Nak(_romp_Rmt_2_2, _romp_NODE_2_2, L2); }
/* --- Rules Generated by: `L2_Recv_NAKC_Nakc` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2_Recv_NAKC_Nakc__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_NAKC_Nakc(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_NAKC_Nakc__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_NAKC_Nakc(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_NAKC_Nakc__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_NAKC_Nakc(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_NAKC_Nakc__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_NAKC_Nakc(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_Recv_NAKC_Nakc__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_NAKC_Nakc(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_NAKC_Nakc__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_NAKC_Nakc(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_NAKC_Nakc__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_NAKC_Nakc(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_NAKC_Nakc__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_NAKC_Nakc(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L2_Recv_NAKC_Nakc__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_NAKC_Nakc(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L2_Recv_NAKC_Nakc__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_NAKC_Nakc(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L2_Recv_NAKC_Nakc__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_NAKC_Nakc(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L2_Recv_NAKC_Nakc__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_NAKC_Nakc(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `RmtCluster_Recv_NAKC_SD` (RuleSet expansions) --- */
 bool __romp__Rule_guard__RmtCluster_Recv_NAKC_SD__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_NAKC_SD(_romp_Rmt_2_1); }
 void __romp__Rule_action__RmtCluster_Recv_NAKC_SD__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_NAKC_SD(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__RmtCluster_Recv_NAKC_SD__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_NAKC_SD(_romp_Rmt_2_2); }
 void __romp__Rule_action__RmtCluster_Recv_NAKC_SD__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_NAKC_SD(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Home_Recv_NAKC_SD` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Home_Recv_NAKC_SD__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Home_Recv_NAKC_SD(); }
 void __romp__Rule_action__Home_Recv_NAKC_SD__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Home_Recv_NAKC_SD(); }
/* --- Rules Generated by: `L1Rmt_Recv_Get_Put` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_1, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_1, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_2, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_2, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(Home, _romp_NODE_2_2, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__6(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__6(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__7(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__7(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__8(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_1, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__8(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_1, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__9(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__9(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__10(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__10(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__11(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_2, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__11(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_1, _romp_NODE_2_2, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__12(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__12(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__13(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__13(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__14(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_1, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__14(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_1, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__15(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__15(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__16(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__16(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_Get_Put__17(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_2, L2); }
 void __romp__Rule_action__L1Rmt_Recv_Get_Put__17(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_Get_Put(_romp_Rmt_2_2, _romp_NODE_2_2, L2); }
/* --- Rules Generated by: `L2_Recv_SHWB` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2_Recv_SHWB__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_SHWB(Home); }
 void __romp__Rule_action__L2_Recv_SHWB__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_SHWB(Home); }
 bool __romp__Rule_guard__L2_Recv_SHWB__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_SHWB(_romp_Rmt_2_1); }
 void __romp__Rule_action__L2_Recv_SHWB__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_SHWB(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__L2_Recv_SHWB__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_SHWB(_romp_Rmt_2_2); }
 void __romp__Rule_action__L2_Recv_SHWB__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_SHWB(_romp_Rmt_2_2); }
/* --- Rules Generated by: `L1Rmt_Recv_GetX_PutX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_1, L2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_1, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_2, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_2, L2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(Home, _romp_NODE_2_2, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__6(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__6(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__7(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__7(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__8(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_1, L2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__8(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_1, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__9(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__9(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__10(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__10(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_2, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__11(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_2, L2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__11(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_1, _romp_NODE_2_2, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__12(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__12(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__13(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__13(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__14(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_1, L2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__14(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_1, L2); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__15(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__15(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__16(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__16(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_2, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1Rmt_Recv_GetX_PutX__17(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_2, L2); }
 void __romp__Rule_action__L1Rmt_Recv_GetX_PutX__17(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1Rmt_Recv_GetX_PutX(_romp_Rmt_2_2, _romp_NODE_2_2, L2); }
/* --- Rules Generated by: `L2_Recv_SHWB_FAck` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2_Recv_SHWB_FAck__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_SHWB_FAck(Home); }
 void __romp__Rule_action__L2_Recv_SHWB_FAck__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_SHWB_FAck(Home); }
 bool __romp__Rule_guard__L2_Recv_SHWB_FAck__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_SHWB_FAck(_romp_Rmt_2_1); }
 void __romp__Rule_action__L2_Recv_SHWB_FAck__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_SHWB_FAck(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__L2_Recv_SHWB_FAck__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_SHWB_FAck(_romp_Rmt_2_2); }
 void __romp__Rule_action__L2_Recv_SHWB_FAck__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_SHWB_FAck(_romp_Rmt_2_2); }
/* --- Rules Generated by: `L1_Recv_Nak` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1_Recv_Nak__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Nak(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_Nak__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Nak(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_Nak__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Nak(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_Nak__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Nak(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_Nak__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Nak(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_Nak__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Nak(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_Nak__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Nak(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_Nak__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Nak(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_Nak__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Nak(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_Nak__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Nak(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_Nak__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Nak(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_Nak__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Nak(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L1_Recv_Put` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1_Recv_Put__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Put(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_Put__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Put(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_Put__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Put(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_Put__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Put(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_Put__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Put(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_Put__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Put(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_Put__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Put(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_Put__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Put(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_Put__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Put(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_Put__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Put(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_Put__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_Put(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_Put__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_Put(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L1_Recv_PutX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1_Recv_PutX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutX(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_PutX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutX(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_PutX__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutX(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_PutX__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutX(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_PutX__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutX(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_PutX__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutX(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_PutX__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutX(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_PutX__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutX(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_PutX__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutX(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_PutX__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutX(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_PutX__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutX(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_PutX__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutX(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L1_Recv_PutXX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1_Recv_PutXX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutXX(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_PutXX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutXX(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_PutXX__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutXX(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_PutXX__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutXX(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_PutXX__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutXX(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_PutXX__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutXX(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_PutXX__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutXX(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_PutXX__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutXX(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_PutXX__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutXX(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_PutXX__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutXX(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_PutXX__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_PutXX(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_PutXX__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_PutXX(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L1_SilentDrop` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1_SilentDrop__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_SilentDrop(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_SilentDrop__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_SilentDrop(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_SilentDrop__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_SilentDrop(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_SilentDrop__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_SilentDrop(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_SilentDrop__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_SilentDrop(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_SilentDrop__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_SilentDrop(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_SilentDrop__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_SilentDrop(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_SilentDrop__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_SilentDrop(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_SilentDrop__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_SilentDrop(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_SilentDrop__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_SilentDrop(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_SilentDrop__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_SilentDrop(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_SilentDrop__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_SilentDrop(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L1_WriteBack` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1_WriteBack__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_WriteBack(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_WriteBack__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_WriteBack(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_WriteBack__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_WriteBack(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_WriteBack__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_WriteBack(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_WriteBack__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_WriteBack(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_WriteBack__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_WriteBack(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_WriteBack__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_WriteBack(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_WriteBack__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_WriteBack(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_WriteBack__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_WriteBack(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_WriteBack__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_WriteBack(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_WriteBack__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_WriteBack(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_WriteBack__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_WriteBack(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L2_Recv_WB_Remain` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2_Recv_WB_Remain__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_WB_Remain(Home); }
 void __romp__Rule_action__L2_Recv_WB_Remain__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_WB_Remain(Home); }
 bool __romp__Rule_guard__L2_Recv_WB_Remain__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_WB_Remain(_romp_Rmt_2_1); }
 void __romp__Rule_action__L2_Recv_WB_Remain__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_WB_Remain(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__L2_Recv_WB_Remain__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_Recv_WB_Remain(_romp_Rmt_2_2); }
 void __romp__Rule_action__L2_Recv_WB_Remain__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_Recv_WB_Remain(_romp_Rmt_2_2); }
/* --- Rules Generated by: `L1_Recv_WbAck` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L1_Recv_WbAck__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_WbAck(Home, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_WbAck__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_WbAck(Home, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_WbAck__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_WbAck(Home, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_WbAck__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_WbAck(Home, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_WbAck__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_WbAck(_romp_Rmt_2_1, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_WbAck__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_WbAck(_romp_Rmt_2_1, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_WbAck__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_WbAck(_romp_Rmt_2_1, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_WbAck__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_WbAck(_romp_Rmt_2_1, _romp_NODE_2_2); }
 bool __romp__Rule_guard__L1_Recv_WbAck__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_WbAck(_romp_Rmt_2_2, _romp_NODE_2_1); }
 void __romp__Rule_action__L1_Recv_WbAck__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_WbAck(_romp_Rmt_2_2, _romp_NODE_2_1); }
 bool __romp__Rule_guard__L1_Recv_WbAck__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L1_Recv_WbAck(_romp_Rmt_2_2, _romp_NODE_2_2); }
 void __romp__Rule_action__L1_Recv_WbAck__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L1_Recv_WbAck(_romp_Rmt_2_2, _romp_NODE_2_2); }
/* --- Rules Generated by: `L2_SilentDrop` (RuleSet expansions) --- */
 bool __romp__Rule_guard__L2_SilentDrop__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_SilentDrop(Home); }
 void __romp__Rule_action__L2_SilentDrop__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_SilentDrop(Home); }
 bool __romp__Rule_guard__L2_SilentDrop__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_SilentDrop(_romp_Rmt_2_1); }
 void __romp__Rule_action__L2_SilentDrop__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_SilentDrop(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__L2_SilentDrop__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__L2_SilentDrop(_romp_Rmt_2_2); }
 void __romp__Rule_action__L2_SilentDrop__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__L2_SilentDrop(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Dir_HomeGet_Put` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_HomeGet_Put__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_HomeGet_Put(); }
 void __romp__Rule_action__Dir_HomeGet_Put__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_HomeGet_Put(); }
/* --- Rules Generated by: `Dir_HomeGet_RmtGet` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_HomeGet_RmtGet__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_HomeGet_RmtGet(); }
 void __romp__Rule_action__Dir_HomeGet_RmtGet__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_HomeGet_RmtGet(); }
/* --- Rules Generated by: `Dir_HomeGet_isLocal_Put` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_HomeGet_isLocal_Put__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_HomeGet_isLocal_Put(); }
 void __romp__Rule_action__Dir_HomeGet_isLocal_Put__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_HomeGet_isLocal_Put(); }
/* --- Rules Generated by: `Dir_HomeGetX_RmtGetX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_HomeGetX_RmtGetX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_HomeGetX_RmtGetX(); }
 void __romp__Rule_action__Dir_HomeGetX_RmtGetX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_HomeGetX_RmtGetX(); }
/* --- Rules Generated by: `Dir_HomeGetX_isLocal_PutX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_HomeGetX_isLocal_PutX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_HomeGetX_isLocal_PutX(); }
 void __romp__Rule_action__Dir_HomeGetX_isLocal_PutX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_HomeGetX_isLocal_PutX(); }
/* --- Rules Generated by: `Dir_HomeGetX_PutX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_HomeGetX_PutX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_HomeGetX_PutX(); }
 void __romp__Rule_action__Dir_HomeGetX_PutX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_HomeGetX_PutX(); }
/* --- Rules Generated by: `Dir_Shrd_HomeGetX_PutX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Shrd_HomeGetX_PutX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Shrd_HomeGetX_PutX(); }
 void __romp__Rule_action__Dir_Shrd_HomeGetX_PutX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Shrd_HomeGetX_PutX(); }
/* --- Rules Generated by: `Home_Recv_InvAck` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Home_Recv_InvAck__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Home_Recv_InvAck(Home); }
 void __romp__Rule_action__Home_Recv_InvAck__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Home_Recv_InvAck(Home); }
 bool __romp__Rule_guard__Home_Recv_InvAck__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Home_Recv_InvAck(_romp_Rmt_2_1); }
 void __romp__Rule_action__Home_Recv_InvAck__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Home_Recv_InvAck(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__Home_Recv_InvAck__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Home_Recv_InvAck(_romp_Rmt_2_2); }
 void __romp__Rule_action__Home_Recv_InvAck__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Home_Recv_InvAck(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Home_Recv_IACK_X_` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Home_Recv_IACK_X___0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Home_Recv_IACK_X_(); }
 void __romp__Rule_action__Home_Recv_IACK_X___0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Home_Recv_IACK_X_(); }
/* --- Rules Generated by: `Home_Recv_Nak` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Home_Recv_Nak__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Home_Recv_Nak(); }
 void __romp__Rule_action__Home_Recv_Nak__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Home_Recv_Nak(); }
/* --- Rules Generated by: `Dir_Recv_NAKC_DIR` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Recv_NAKC_DIR__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_NAKC_DIR(); }
 void __romp__Rule_action__Dir_Recv_NAKC_DIR__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_NAKC_DIR(); }
/* --- Rules Generated by: `Home_Recv_ACK` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Home_Recv_ACK__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Home_Recv_ACK(); }
 void __romp__Rule_action__Home_Recv_ACK__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Home_Recv_ACK(); }
/* --- Rules Generated by: `RmtCluster_Recv_Get` (RuleSet expansions) --- */
 bool __romp__Rule_guard__RmtCluster_Recv_Get__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_Get(_romp_Rmt_2_1, Home); }
 void __romp__Rule_action__RmtCluster_Recv_Get__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_Get(_romp_Rmt_2_1, Home); }
 bool __romp__Rule_guard__RmtCluster_Recv_Get__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_Get(_romp_Rmt_2_1, _romp_Rmt_2_1); }
 void __romp__Rule_action__RmtCluster_Recv_Get__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_Get(_romp_Rmt_2_1, _romp_Rmt_2_1); }
 bool __romp__Rule_guard__RmtCluster_Recv_Get__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_Get(_romp_Rmt_2_1, _romp_Rmt_2_2); }
 void __romp__Rule_action__RmtCluster_Recv_Get__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_Get(_romp_Rmt_2_1, _romp_Rmt_2_2); }
 bool __romp__Rule_guard__RmtCluster_Recv_Get__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_Get(_romp_Rmt_2_2, Home); }
 void __romp__Rule_action__RmtCluster_Recv_Get__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_Get(_romp_Rmt_2_2, Home); }
 bool __romp__Rule_guard__RmtCluster_Recv_Get__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_Get(_romp_Rmt_2_2, _romp_Rmt_2_1); }
 void __romp__Rule_action__RmtCluster_Recv_Get__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_Get(_romp_Rmt_2_2, _romp_Rmt_2_1); }
 bool __romp__Rule_guard__RmtCluster_Recv_Get__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_Get(_romp_Rmt_2_2, _romp_Rmt_2_2); }
 void __romp__Rule_action__RmtCluster_Recv_Get__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_Get(_romp_Rmt_2_2, _romp_Rmt_2_2); }
/* --- Rules Generated by: `RmtCluster_Recv_GetX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__RmtCluster_Recv_GetX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_GetX(_romp_Rmt_2_1, Home); }
 void __romp__Rule_action__RmtCluster_Recv_GetX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_GetX(_romp_Rmt_2_1, Home); }
 bool __romp__Rule_guard__RmtCluster_Recv_GetX__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_GetX(_romp_Rmt_2_1, _romp_Rmt_2_1); }
 void __romp__Rule_action__RmtCluster_Recv_GetX__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_GetX(_romp_Rmt_2_1, _romp_Rmt_2_1); }
 bool __romp__Rule_guard__RmtCluster_Recv_GetX__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_GetX(_romp_Rmt_2_1, _romp_Rmt_2_2); }
 void __romp__Rule_action__RmtCluster_Recv_GetX__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_GetX(_romp_Rmt_2_1, _romp_Rmt_2_2); }
 bool __romp__Rule_guard__RmtCluster_Recv_GetX__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_GetX(_romp_Rmt_2_2, Home); }
 void __romp__Rule_action__RmtCluster_Recv_GetX__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_GetX(_romp_Rmt_2_2, Home); }
 bool __romp__Rule_guard__RmtCluster_Recv_GetX__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_GetX(_romp_Rmt_2_2, _romp_Rmt_2_1); }
 void __romp__Rule_action__RmtCluster_Recv_GetX__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_GetX(_romp_Rmt_2_2, _romp_Rmt_2_1); }
 bool __romp__Rule_guard__RmtCluster_Recv_GetX__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_GetX(_romp_Rmt_2_2, _romp_Rmt_2_2); }
 void __romp__Rule_action__RmtCluster_Recv_GetX__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_GetX(_romp_Rmt_2_2, _romp_Rmt_2_2); }
/* --- Rules Generated by: `Dir_Recv_DXFER` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Recv_DXFER__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_DXFER(); }
 void __romp__Rule_action__Dir_Recv_DXFER__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_DXFER(); }
/* --- Rules Generated by: `Dir_Recv_ShWb` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Recv_ShWb__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_ShWb(); }
 void __romp__Rule_action__Dir_Recv_ShWb__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_ShWb(); }
/* --- Rules Generated by: `RmtCluster_Recv_ACK` (RuleSet expansions) --- */
 bool __romp__Rule_guard__RmtCluster_Recv_ACK__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_ACK(_romp_Rmt_2_1); }
 void __romp__Rule_action__RmtCluster_Recv_ACK__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_ACK(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__RmtCluster_Recv_ACK__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_ACK(_romp_Rmt_2_2); }
 void __romp__Rule_action__RmtCluster_Recv_ACK__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_ACK(_romp_Rmt_2_2); }
/* --- Rules Generated by: `RmtCluster_Recv_Nak` (RuleSet expansions) --- */
 bool __romp__Rule_guard__RmtCluster_Recv_Nak__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_Nak(_romp_Rmt_2_1); }
 void __romp__Rule_action__RmtCluster_Recv_Nak__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_Nak(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__RmtCluster_Recv_Nak__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_Nak(_romp_Rmt_2_2); }
 void __romp__Rule_action__RmtCluster_Recv_Nak__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_Nak(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Cluster_Recv_Inv` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Cluster_Recv_Inv__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Cluster_Recv_Inv(Home); }
 void __romp__Rule_action__Cluster_Recv_Inv__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Cluster_Recv_Inv(Home); }
 bool __romp__Rule_guard__Cluster_Recv_Inv__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Cluster_Recv_Inv(_romp_Rmt_2_1); }
 void __romp__Rule_action__Cluster_Recv_Inv__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Cluster_Recv_Inv(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__Cluster_Recv_Inv__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Cluster_Recv_Inv(_romp_Rmt_2_2); }
 void __romp__Rule_action__Cluster_Recv_Inv__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Cluster_Recv_Inv(_romp_Rmt_2_2); }
/* --- Rules Generated by: `RmtCluster_Recv_InvAck` (RuleSet expansions) --- */
 bool __romp__Rule_guard__RmtCluster_Recv_InvAck__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_InvAck(_romp_Rmt_2_1, Home); }
 void __romp__Rule_action__RmtCluster_Recv_InvAck__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_InvAck(_romp_Rmt_2_1, Home); }
 bool __romp__Rule_guard__RmtCluster_Recv_InvAck__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_InvAck(_romp_Rmt_2_1, _romp_Rmt_2_1); }
 void __romp__Rule_action__RmtCluster_Recv_InvAck__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_InvAck(_romp_Rmt_2_1, _romp_Rmt_2_1); }
 bool __romp__Rule_guard__RmtCluster_Recv_InvAck__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_InvAck(_romp_Rmt_2_1, _romp_Rmt_2_2); }
 void __romp__Rule_action__RmtCluster_Recv_InvAck__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_InvAck(_romp_Rmt_2_1, _romp_Rmt_2_2); }
 bool __romp__Rule_guard__RmtCluster_Recv_InvAck__3(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_InvAck(_romp_Rmt_2_2, Home); }
 void __romp__Rule_action__RmtCluster_Recv_InvAck__3(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_InvAck(_romp_Rmt_2_2, Home); }
 bool __romp__Rule_guard__RmtCluster_Recv_InvAck__4(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_InvAck(_romp_Rmt_2_2, _romp_Rmt_2_1); }
 void __romp__Rule_action__RmtCluster_Recv_InvAck__4(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_InvAck(_romp_Rmt_2_2, _romp_Rmt_2_1); }
 bool __romp__Rule_guard__RmtCluster_Recv_InvAck__5(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_InvAck(_romp_Rmt_2_2, _romp_Rmt_2_2); }
 void __romp__Rule_action__RmtCluster_Recv_InvAck__5(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_InvAck(_romp_Rmt_2_2, _romp_Rmt_2_2); }
/* --- Rules Generated by: `RmtCluster_Recv_IACK_X_` (RuleSet expansions) --- */
 bool __romp__Rule_guard__RmtCluster_Recv_IACK_X___0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_IACK_X_(_romp_Rmt_2_1); }
 void __romp__Rule_action__RmtCluster_Recv_IACK_X___0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_IACK_X_(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__RmtCluster_Recv_IACK_X___1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_IACK_X_(_romp_Rmt_2_2); }
 void __romp__Rule_action__RmtCluster_Recv_IACK_X___1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_IACK_X_(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Dir_Recv_RmtGet_Put` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Recv_RmtGet_Put__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGet_Put(_romp_Rmt_2_1); }
 void __romp__Rule_action__Dir_Recv_RmtGet_Put__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGet_Put(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__Dir_Recv_RmtGet_Put__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGet_Put(_romp_Rmt_2_2); }
 void __romp__Rule_action__Dir_Recv_RmtGet_Put__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGet_Put(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Dir_Recv_RmtGet__RmtGet_` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Recv_RmtGet__RmtGet___0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGet__RmtGet_(_romp_Rmt_2_1); }
 void __romp__Rule_action__Dir_Recv_RmtGet__RmtGet___0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGet__RmtGet_(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__Dir_Recv_RmtGet__RmtGet___1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGet__RmtGet_(_romp_Rmt_2_2); }
 void __romp__Rule_action__Dir_Recv_RmtGet__RmtGet___1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGet__RmtGet_(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Dir_Recv_RmtGetX__RmtGetX_` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Recv_RmtGetX__RmtGetX___0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGetX__RmtGetX_(_romp_Rmt_2_1); }
 void __romp__Rule_action__Dir_Recv_RmtGetX__RmtGetX___0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGetX__RmtGetX_(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__Dir_Recv_RmtGetX__RmtGetX___1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGetX__RmtGetX_(_romp_Rmt_2_2); }
 void __romp__Rule_action__Dir_Recv_RmtGetX__RmtGetX___1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGetX__RmtGetX_(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Dir_Recv_RmtGetX_isLocal` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Recv_RmtGetX_isLocal__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGetX_isLocal(_romp_Rmt_2_1); }
 void __romp__Rule_action__Dir_Recv_RmtGetX_isLocal__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGetX_isLocal(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__Dir_Recv_RmtGetX_isLocal__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGetX_isLocal(_romp_Rmt_2_2); }
 void __romp__Rule_action__Dir_Recv_RmtGetX_isLocal__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGetX_isLocal(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Dir_Recv_RmtGet_isLocal` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Recv_RmtGet_isLocal__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGet_isLocal(_romp_Rmt_2_1); }
 void __romp__Rule_action__Dir_Recv_RmtGet_isLocal__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGet_isLocal(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__Dir_Recv_RmtGet_isLocal__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGet_isLocal(_romp_Rmt_2_2); }
 void __romp__Rule_action__Dir_Recv_RmtGet_isLocal__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGet_isLocal(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Dir_Recv_RmtGetX_PutX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Recv_RmtGetX_PutX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGetX_PutX(_romp_Rmt_2_1); }
 void __romp__Rule_action__Dir_Recv_RmtGetX_PutX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGetX_PutX(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__Dir_Recv_RmtGetX_PutX__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_RmtGetX_PutX(_romp_Rmt_2_2); }
 void __romp__Rule_action__Dir_Recv_RmtGetX_PutX__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_RmtGetX_PutX(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Cluster_WriteBack` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Cluster_WriteBack__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Cluster_WriteBack(Home); }
 void __romp__Rule_action__Cluster_WriteBack__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Cluster_WriteBack(Home); }
 bool __romp__Rule_guard__Cluster_WriteBack__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Cluster_WriteBack(_romp_Rmt_2_1); }
 void __romp__Rule_action__Cluster_WriteBack__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Cluster_WriteBack(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__Cluster_WriteBack__2(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Cluster_WriteBack(_romp_Rmt_2_2); }
 void __romp__Rule_action__Cluster_WriteBack__2(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Cluster_WriteBack(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Dir_Recv_WB` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Recv_WB__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Recv_WB(); }
 void __romp__Rule_action__Dir_Recv_WB__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Recv_WB(); }
/* --- Rules Generated by: `RmtCluster_Recv_WBAck` (RuleSet expansions) --- */
 bool __romp__Rule_guard__RmtCluster_Recv_WBAck__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_WBAck(_romp_Rmt_2_1); }
 void __romp__Rule_action__RmtCluster_Recv_WBAck__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_WBAck(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__RmtCluster_Recv_WBAck__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__RmtCluster_Recv_WBAck(_romp_Rmt_2_2); }
 void __romp__Rule_action__RmtCluster_Recv_WBAck__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__RmtCluster_Recv_WBAck(_romp_Rmt_2_2); }
/* --- Rules Generated by: `Dir_Shrd_RmtGetX_PutX` (RuleSet expansions) --- */
 bool __romp__Rule_guard__Dir_Shrd_RmtGetX_PutX__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Shrd_RmtGetX_PutX(_romp_Rmt_2_1); }
 void __romp__Rule_action__Dir_Shrd_RmtGetX_PutX__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Shrd_RmtGetX_PutX(_romp_Rmt_2_1); }
 bool __romp__Rule_guard__Dir_Shrd_RmtGetX_PutX__1(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Rule_guard__Dir_Shrd_RmtGetX_PutX(_romp_Rmt_2_2); }
 void __romp__Rule_action__Dir_Shrd_RmtGetX_PutX__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__Rule_action__Dir_Shrd_RmtGetX_PutX(_romp_Rmt_2_2); }

#define _ROMP_RULE_COUNT (258ul)

#define _ROMP_RULESETS_LEN (60ul)
const ::romp::RuleSet RULESETS[] = {
		{::__info__::RULE_SET_INFOS[0],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1_Update_Data__0,__romp__Rule_action__L1_Update_Data__0,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_1\"}}}]","p:=Home; src:=NODE_1; data:=Datas_1"}, ::romp::Rule{__romp__Rule_guard__L1_Update_Data__1,__romp__Rule_action__L1_Update_Data__1,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_2\"}}}]","p:=Home; src:=NODE_1; data:=Datas_2"}, ::romp::Rule{__romp__Rule_guard__L1_Update_Data__2,__romp__Rule_action__L1_Update_Data__2,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_1\"}}}]","p:=Home; src:=NODE_2; data:=Datas_1"}, ::romp::Rule{__romp__Rule_guard__L1_Update_Data__3,__romp__Rule_action__L1_Update_Data__3,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_2\"}}}]","p:=Home; src:=NODE_2; data:=Datas_2"}, ::romp::Rule{__romp__Rule_guard__L1_Update_Data__4,__romp__Rule_action__L1_Update_Data__4,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_1\"}}}]","p:=Rmt_1; src:=NODE_1; data:=Datas_1"}, ::romp::Rule{__romp__Rule_guard__L1_Update_Data__5,__romp__Rule_action__L1_Update_Data__5,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_2\"}}}]","p:=Rmt_1; src:=NODE_1; data:=Datas_2"}, ::romp::Rule{__romp__Rule_guard__L1_Update_Data__6,__romp__Rule_action__L1_Update_Data__6,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_1\"}}}]","p:=Rmt_1; src:=NODE_2; data:=Datas_1"}, ::romp::Rule{__romp__Rule_guard__L1_Update_Data__7,__romp__Rule_action__L1_Update_Data__7,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_2\"}}}]","p:=Rmt_1; src:=NODE_2; data:=Datas_2"}, ::romp::Rule{__romp__Rule_guard__L1_Update_Data__8,__romp__Rule_action__L1_Update_Data__8,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_1\"}}}]","p:=Rmt_2; src:=NODE_1; data:=Datas_1"}, ::romp::Rule{__romp__Rule_guard__L1_Update_Data__9,__romp__Rule_action__L1_Update_Data__9,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_2\"}}}]","p:=Rmt_2; src:=NODE_1; data:=Datas_2"}, ::romp::Rule{__romp__Rule_guard__L1_Update_Data__10,__romp__Rule_action__L1_Update_Data__10,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_1\"}}}]","p:=Rmt_2; src:=NODE_2; data:=Datas_1"}, ::romp::Rule{__romp__Rule_guard__L1_Update_Data__11,__romp__Rule_action__L1_Update_Data__11,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"data\",\"value\":{\"$type\":\"quantifier\",\"id\":\"data\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_2\"}}}]","p:=Rmt_2; src:=NODE_2; data:=Datas_2"}	}},
		{::__info__::RULE_SET_INFOS[1],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1_Get__0,__romp__Rule_action__L1_Get__0,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Get__1,__romp__Rule_action__L1_Get__1,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Get__2,__romp__Rule_action__L1_Get__2,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Get__3,__romp__Rule_action__L1_Get__3,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Get__4,__romp__Rule_action__L1_Get__4,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Get__5,__romp__Rule_action__L1_Get__5,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[2],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2_Recv_Get_Put__0,__romp__Rule_action__L2_Recv_Get_Put__0,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_Get_Put__1,__romp__Rule_action__L2_Recv_Get_Put__1,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_Get_Put__2,__romp__Rule_action__L2_Recv_Get_Put__2,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_Get_Put__3,__romp__Rule_action__L2_Recv_Get_Put__3,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_Get_Put__4,__romp__Rule_action__L2_Recv_Get_Put__4,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_Get_Put__5,__romp__Rule_action__L2_Recv_Get_Put__5,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[3],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2_busy_Recv_Get_X__Nak__0,__romp__Rule_action__L2_busy_Recv_Get_X__Nak__0,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_busy_Recv_Get_X__Nak__1,__romp__Rule_action__L2_busy_Recv_Get_X__Nak__1,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_busy_Recv_Get_X__Nak__2,__romp__Rule_action__L2_busy_Recv_Get_X__Nak__2,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_busy_Recv_Get_X__Nak__3,__romp__Rule_action__L2_busy_Recv_Get_X__Nak__3,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_busy_Recv_Get_X__Nak__4,__romp__Rule_action__L2_busy_Recv_Get_X__Nak__4,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_busy_Recv_Get_X__Nak__5,__romp__Rule_action__L2_busy_Recv_Get_X__Nak__5,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[4],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_Get_Put__0,__romp__Rule_action__L2HeadPtr_Recv_Get_Put__0,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_Get_Put__1,__romp__Rule_action__L2HeadPtr_Recv_Get_Put__1,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_Get_Put__2,__romp__Rule_action__L2HeadPtr_Recv_Get_Put__2,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_Get_Put__3,__romp__Rule_action__L2HeadPtr_Recv_Get_Put__3,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_Get_Put__4,__romp__Rule_action__L2HeadPtr_Recv_Get_Put__4,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_Get_Put__5,__romp__Rule_action__L2HeadPtr_Recv_Get_Put__5,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[5],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2_Fwd_Get_X___0,__romp__Rule_action__L2_Fwd_Get_X___0,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Fwd_Get_X___1,__romp__Rule_action__L2_Fwd_Get_X___1,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_Fwd_Get_X___2,__romp__Rule_action__L2_Fwd_Get_X___2,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Fwd_Get_X___3,__romp__Rule_action__L2_Fwd_Get_X___3,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_Fwd_Get_X___4,__romp__Rule_action__L2_Fwd_Get_X___4,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Fwd_Get_X___5,__romp__Rule_action__L2_Fwd_Get_X___5,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[6],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2_Recv_Get_X__OutGet_X___0,__romp__Rule_action__L2_Recv_Get_X__OutGet_X___0,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_Get_X__OutGet_X___1,__romp__Rule_action__L2_Recv_Get_X__OutGet_X___1,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_Get_X__OutGet_X___2,__romp__Rule_action__L2_Recv_Get_X__OutGet_X___2,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_Get_X__OutGet_X___3,__romp__Rule_action__L2_Recv_Get_X__OutGet_X___3,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_Get_X__OutGet_X___4,__romp__Rule_action__L2_Recv_Get_X__OutGet_X___4,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_Get_X__OutGet_X___5,__romp__Rule_action__L2_Recv_Get_X__OutGet_X___5,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[7],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1_GetX__0,__romp__Rule_action__L1_GetX__0,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_GetX__1,__romp__Rule_action__L1_GetX__1,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_GetX__2,__romp__Rule_action__L1_GetX__2,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_GetX__3,__romp__Rule_action__L1_GetX__3,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_GetX__4,__romp__Rule_action__L1_GetX__4,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_GetX__5,__romp__Rule_action__L1_GetX__5,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[8],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__0,__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__0,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__1,__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__1,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__2,__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__2,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__3,__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__3,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__4,__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__4,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2HeadPtr_Recv_GetX_PutX__5,__romp__Rule_action__L2HeadPtr_Recv_GetX_PutX__5,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[9],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2Shrd_Recv_GetX__PutX___0,__romp__Rule_action__L2Shrd_Recv_GetX__PutX___0,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2Shrd_Recv_GetX__PutX___1,__romp__Rule_action__L2Shrd_Recv_GetX__PutX___1,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2Shrd_Recv_GetX__PutX___2,__romp__Rule_action__L2Shrd_Recv_GetX__PutX___2,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2Shrd_Recv_GetX__PutX___3,__romp__Rule_action__L2Shrd_Recv_GetX__PutX___3,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2Shrd_Recv_GetX__PutX___4,__romp__Rule_action__L2Shrd_Recv_GetX__PutX___4,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2Shrd_Recv_GetX__PutX___5,__romp__Rule_action__L2Shrd_Recv_GetX__PutX___5,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[10],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1_Recv_Inv__0,__romp__Rule_action__L1_Recv_Inv__0,::__info__::RULE_SET_INFOS[10],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Inv__1,__romp__Rule_action__L1_Recv_Inv__1,::__info__::RULE_SET_INFOS[10],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Inv__2,__romp__Rule_action__L1_Recv_Inv__2,::__info__::RULE_SET_INFOS[10],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Inv__3,__romp__Rule_action__L1_Recv_Inv__3,::__info__::RULE_SET_INFOS[10],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Inv__4,__romp__Rule_action__L1_Recv_Inv__4,::__info__::RULE_SET_INFOS[10],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Inv__5,__romp__Rule_action__L1_Recv_Inv__5,::__info__::RULE_SET_INFOS[10],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[11],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2_Recv_InvAck__0,__romp__Rule_action__L2_Recv_InvAck__0,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_InvAck__1,__romp__Rule_action__L2_Recv_InvAck__1,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_InvAck__2,__romp__Rule_action__L2_Recv_InvAck__2,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_InvAck__3,__romp__Rule_action__L2_Recv_InvAck__3,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_InvAck__4,__romp__Rule_action__L2_Recv_InvAck__4,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_InvAck__5,__romp__Rule_action__L2_Recv_InvAck__5,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[12],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__0,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__0,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__1,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__1,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__2,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__2,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Home; dst:=NODE_1; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__3,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__3,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__4,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__4,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_2; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__5,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__5,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Home; dst:=NODE_2; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__6,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__6,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__7,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__7,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__8,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__8,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_1; dst:=NODE_1; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__9,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__9,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__10,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__10,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_2; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__11,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__11,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_1; dst:=NODE_2; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__12,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__12,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__13,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__13,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__14,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__14,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_2; dst:=NODE_1; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__15,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__15,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__16,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__16,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_2; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_X__Nak__17,__romp__Rule_action__L1Rmt_Recv_Get_X__Nak__17,::__info__::RULE_SET_INFOS[12],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_2; dst:=NODE_2; src:=L2"}	}},
		{::__info__::RULE_SET_INFOS[13],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2_Recv_NAKC_Nakc__0,__romp__Rule_action__L2_Recv_NAKC_Nakc__0,::__info__::RULE_SET_INFOS[13],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_NAKC_Nakc__1,__romp__Rule_action__L2_Recv_NAKC_Nakc__1,::__info__::RULE_SET_INFOS[13],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_NAKC_Nakc__2,__romp__Rule_action__L2_Recv_NAKC_Nakc__2,::__info__::RULE_SET_INFOS[13],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_NAKC_Nakc__3,__romp__Rule_action__L2_Recv_NAKC_Nakc__3,::__info__::RULE_SET_INFOS[13],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_NAKC_Nakc__4,__romp__Rule_action__L2_Recv_NAKC_Nakc__4,::__info__::RULE_SET_INFOS[13],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_NAKC_Nakc__5,__romp__Rule_action__L2_Recv_NAKC_Nakc__5,::__info__::RULE_SET_INFOS[13],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[14],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_NAKC_SD__0,__romp__Rule_action__RmtCluster_Recv_NAKC_SD__0,::__info__::RULE_SET_INFOS[14],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","p:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_NAKC_SD__1,__romp__Rule_action__RmtCluster_Recv_NAKC_SD__1,::__info__::RULE_SET_INFOS[14],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","p:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[15],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Home_Recv_NAKC_SD__0,__romp__Rule_action__Home_Recv_NAKC_SD__0,::__info__::RULE_SET_INFOS[15],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[16],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__0,__romp__Rule_action__L1Rmt_Recv_Get_Put__0,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__1,__romp__Rule_action__L1Rmt_Recv_Get_Put__1,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__2,__romp__Rule_action__L1Rmt_Recv_Get_Put__2,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Home; dst:=NODE_1; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__3,__romp__Rule_action__L1Rmt_Recv_Get_Put__3,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__4,__romp__Rule_action__L1Rmt_Recv_Get_Put__4,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_2; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__5,__romp__Rule_action__L1Rmt_Recv_Get_Put__5,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Home; dst:=NODE_2; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__6,__romp__Rule_action__L1Rmt_Recv_Get_Put__6,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__7,__romp__Rule_action__L1Rmt_Recv_Get_Put__7,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__8,__romp__Rule_action__L1Rmt_Recv_Get_Put__8,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_1; dst:=NODE_1; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__9,__romp__Rule_action__L1Rmt_Recv_Get_Put__9,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__10,__romp__Rule_action__L1Rmt_Recv_Get_Put__10,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_2; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__11,__romp__Rule_action__L1Rmt_Recv_Get_Put__11,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_1; dst:=NODE_2; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__12,__romp__Rule_action__L1Rmt_Recv_Get_Put__12,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__13,__romp__Rule_action__L1Rmt_Recv_Get_Put__13,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__14,__romp__Rule_action__L1Rmt_Recv_Get_Put__14,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_2; dst:=NODE_1; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__15,__romp__Rule_action__L1Rmt_Recv_Get_Put__15,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__16,__romp__Rule_action__L1Rmt_Recv_Get_Put__16,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_2; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_Get_Put__17,__romp__Rule_action__L1Rmt_Recv_Get_Put__17,::__info__::RULE_SET_INFOS[16],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_2; dst:=NODE_2; src:=L2"}	}},
		{::__info__::RULE_SET_INFOS[17],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2_Recv_SHWB__0,__romp__Rule_action__L2_Recv_SHWB__0,::__info__::RULE_SET_INFOS[17],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","p:=Home"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_SHWB__1,__romp__Rule_action__L2_Recv_SHWB__1,::__info__::RULE_SET_INFOS[17],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","p:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_SHWB__2,__romp__Rule_action__L2_Recv_SHWB__2,::__info__::RULE_SET_INFOS[17],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","p:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[18],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__0,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__0,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__1,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__1,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__2,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__2,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Home; dst:=NODE_1; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__3,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__3,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__4,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__4,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_2; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__5,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__5,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Home; dst:=NODE_2; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__6,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__6,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__7,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__7,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__8,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__8,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_1; dst:=NODE_1; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__9,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__9,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__10,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__10,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_2; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__11,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__11,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_1; dst:=NODE_2; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__12,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__12,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__13,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__13,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__14,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__14,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_2; dst:=NODE_1; src:=L2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__15,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__15,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__16,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__16,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_2; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1Rmt_Recv_GetX_PutX__17,__romp__Rule_action__L1Rmt_Recv_GetX_PutX__17,::__info__::RULE_SET_INFOS[18],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE_L2\",\"value\":\"L2\"}}}]","p:=Rmt_2; dst:=NODE_2; src:=L2"}	}},
		{::__info__::RULE_SET_INFOS[19],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2_Recv_SHWB_FAck__0,__romp__Rule_action__L2_Recv_SHWB_FAck__0,::__info__::RULE_SET_INFOS[19],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","p:=Home"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_SHWB_FAck__1,__romp__Rule_action__L2_Recv_SHWB_FAck__1,::__info__::RULE_SET_INFOS[19],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","p:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_SHWB_FAck__2,__romp__Rule_action__L2_Recv_SHWB_FAck__2,::__info__::RULE_SET_INFOS[19],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","p:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[20],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1_Recv_Nak__0,__romp__Rule_action__L1_Recv_Nak__0,::__info__::RULE_SET_INFOS[20],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Nak__1,__romp__Rule_action__L1_Recv_Nak__1,::__info__::RULE_SET_INFOS[20],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Nak__2,__romp__Rule_action__L1_Recv_Nak__2,::__info__::RULE_SET_INFOS[20],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Nak__3,__romp__Rule_action__L1_Recv_Nak__3,::__info__::RULE_SET_INFOS[20],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Nak__4,__romp__Rule_action__L1_Recv_Nak__4,::__info__::RULE_SET_INFOS[20],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Nak__5,__romp__Rule_action__L1_Recv_Nak__5,::__info__::RULE_SET_INFOS[20],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[21],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1_Recv_Put__0,__romp__Rule_action__L1_Recv_Put__0,::__info__::RULE_SET_INFOS[21],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Put__1,__romp__Rule_action__L1_Recv_Put__1,::__info__::RULE_SET_INFOS[21],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Put__2,__romp__Rule_action__L1_Recv_Put__2,::__info__::RULE_SET_INFOS[21],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Put__3,__romp__Rule_action__L1_Recv_Put__3,::__info__::RULE_SET_INFOS[21],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Put__4,__romp__Rule_action__L1_Recv_Put__4,::__info__::RULE_SET_INFOS[21],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_Put__5,__romp__Rule_action__L1_Recv_Put__5,::__info__::RULE_SET_INFOS[21],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[22],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1_Recv_PutX__0,__romp__Rule_action__L1_Recv_PutX__0,::__info__::RULE_SET_INFOS[22],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_PutX__1,__romp__Rule_action__L1_Recv_PutX__1,::__info__::RULE_SET_INFOS[22],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_PutX__2,__romp__Rule_action__L1_Recv_PutX__2,::__info__::RULE_SET_INFOS[22],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_PutX__3,__romp__Rule_action__L1_Recv_PutX__3,::__info__::RULE_SET_INFOS[22],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_PutX__4,__romp__Rule_action__L1_Recv_PutX__4,::__info__::RULE_SET_INFOS[22],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_PutX__5,__romp__Rule_action__L1_Recv_PutX__5,::__info__::RULE_SET_INFOS[22],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[23],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1_Recv_PutXX__0,__romp__Rule_action__L1_Recv_PutXX__0,::__info__::RULE_SET_INFOS[23],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_PutXX__1,__romp__Rule_action__L1_Recv_PutXX__1,::__info__::RULE_SET_INFOS[23],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_PutXX__2,__romp__Rule_action__L1_Recv_PutXX__2,::__info__::RULE_SET_INFOS[23],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_PutXX__3,__romp__Rule_action__L1_Recv_PutXX__3,::__info__::RULE_SET_INFOS[23],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_PutXX__4,__romp__Rule_action__L1_Recv_PutXX__4,::__info__::RULE_SET_INFOS[23],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_PutXX__5,__romp__Rule_action__L1_Recv_PutXX__5,::__info__::RULE_SET_INFOS[23],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[24],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1_SilentDrop__0,__romp__Rule_action__L1_SilentDrop__0,::__info__::RULE_SET_INFOS[24],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_SilentDrop__1,__romp__Rule_action__L1_SilentDrop__1,::__info__::RULE_SET_INFOS[24],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_SilentDrop__2,__romp__Rule_action__L1_SilentDrop__2,::__info__::RULE_SET_INFOS[24],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_SilentDrop__3,__romp__Rule_action__L1_SilentDrop__3,::__info__::RULE_SET_INFOS[24],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_SilentDrop__4,__romp__Rule_action__L1_SilentDrop__4,::__info__::RULE_SET_INFOS[24],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_SilentDrop__5,__romp__Rule_action__L1_SilentDrop__5,::__info__::RULE_SET_INFOS[24],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[25],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1_WriteBack__0,__romp__Rule_action__L1_WriteBack__0,::__info__::RULE_SET_INFOS[25],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_WriteBack__1,__romp__Rule_action__L1_WriteBack__1,::__info__::RULE_SET_INFOS[25],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_WriteBack__2,__romp__Rule_action__L1_WriteBack__2,::__info__::RULE_SET_INFOS[25],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_WriteBack__3,__romp__Rule_action__L1_WriteBack__3,::__info__::RULE_SET_INFOS[25],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; src:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_WriteBack__4,__romp__Rule_action__L1_WriteBack__4,::__info__::RULE_SET_INFOS[25],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; src:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_WriteBack__5,__romp__Rule_action__L1_WriteBack__5,::__info__::RULE_SET_INFOS[25],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; src:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[26],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2_Recv_WB_Remain__0,__romp__Rule_action__L2_Recv_WB_Remain__0,::__info__::RULE_SET_INFOS[26],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","p:=Home"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_WB_Remain__1,__romp__Rule_action__L2_Recv_WB_Remain__1,::__info__::RULE_SET_INFOS[26],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","p:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__L2_Recv_WB_Remain__2,__romp__Rule_action__L2_Recv_WB_Remain__2,::__info__::RULE_SET_INFOS[26],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","p:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[27],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L1_Recv_WbAck__0,__romp__Rule_action__L1_Recv_WbAck__0,::__info__::RULE_SET_INFOS[27],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Home; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_WbAck__1,__romp__Rule_action__L1_Recv_WbAck__1,::__info__::RULE_SET_INFOS[27],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Home; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_WbAck__2,__romp__Rule_action__L1_Recv_WbAck__2,::__info__::RULE_SET_INFOS[27],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_1; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_WbAck__3,__romp__Rule_action__L1_Recv_WbAck__3,::__info__::RULE_SET_INFOS[27],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_1; dst:=NODE_2"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_WbAck__4,__romp__Rule_action__L1_Recv_WbAck__4,::__info__::RULE_SET_INFOS[27],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_1\"}}}]","p:=Rmt_2; dst:=NODE_1"}, ::romp::Rule{__romp__Rule_guard__L1_Recv_WbAck__5,__romp__Rule_action__L1_Recv_WbAck__5,::__info__::RULE_SET_INFOS[27],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"NODE\",\"value\":\"_romp_NODE_2_2\"}}}]","p:=Rmt_2; dst:=NODE_2"}	}},
		{::__info__::RULE_SET_INFOS[28],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__L2_SilentDrop__0,__romp__Rule_action__L2_SilentDrop__0,::__info__::RULE_SET_INFOS[28],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","p:=Home"}, ::romp::Rule{__romp__Rule_guard__L2_SilentDrop__1,__romp__Rule_action__L2_SilentDrop__1,::__info__::RULE_SET_INFOS[28],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","p:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__L2_SilentDrop__2,__romp__Rule_action__L2_SilentDrop__2,::__info__::RULE_SET_INFOS[28],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","p:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[29],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_HomeGet_Put__0,__romp__Rule_action__Dir_HomeGet_Put__0,::__info__::RULE_SET_INFOS[29],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[30],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_HomeGet_RmtGet__0,__romp__Rule_action__Dir_HomeGet_RmtGet__0,::__info__::RULE_SET_INFOS[30],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[31],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_HomeGet_isLocal_Put__0,__romp__Rule_action__Dir_HomeGet_isLocal_Put__0,::__info__::RULE_SET_INFOS[31],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[32],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_HomeGetX_RmtGetX__0,__romp__Rule_action__Dir_HomeGetX_RmtGetX__0,::__info__::RULE_SET_INFOS[32],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[33],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_HomeGetX_isLocal_PutX__0,__romp__Rule_action__Dir_HomeGetX_isLocal_PutX__0,::__info__::RULE_SET_INFOS[33],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[34],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_HomeGetX_PutX__0,__romp__Rule_action__Dir_HomeGetX_PutX__0,::__info__::RULE_SET_INFOS[34],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[35],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Shrd_HomeGetX_PutX__0,__romp__Rule_action__Dir_Shrd_HomeGetX_PutX__0,::__info__::RULE_SET_INFOS[35],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[36],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Home_Recv_InvAck__0,__romp__Rule_action__Home_Recv_InvAck__0,::__info__::RULE_SET_INFOS[36],"[{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","src:=Home"}, ::romp::Rule{__romp__Rule_guard__Home_Recv_InvAck__1,__romp__Rule_action__Home_Recv_InvAck__1,::__info__::RULE_SET_INFOS[36],"[{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","src:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__Home_Recv_InvAck__2,__romp__Rule_action__Home_Recv_InvAck__2,::__info__::RULE_SET_INFOS[36],"[{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","src:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[37],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Home_Recv_IACK_X___0,__romp__Rule_action__Home_Recv_IACK_X___0,::__info__::RULE_SET_INFOS[37],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[38],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Home_Recv_Nak__0,__romp__Rule_action__Home_Recv_Nak__0,::__info__::RULE_SET_INFOS[38],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[39],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Recv_NAKC_DIR__0,__romp__Rule_action__Dir_Recv_NAKC_DIR__0,::__info__::RULE_SET_INFOS[39],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[40],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Home_Recv_ACK__0,__romp__Rule_action__Home_Recv_ACK__0,::__info__::RULE_SET_INFOS[40],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[41],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_Get__0,__romp__Rule_action__RmtCluster_Recv_Get__0,::__info__::RULE_SET_INFOS[41],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","r:=Rmt_1; src:=Home"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_Get__1,__romp__Rule_action__RmtCluster_Recv_Get__1,::__info__::RULE_SET_INFOS[41],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","r:=Rmt_1; src:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_Get__2,__romp__Rule_action__RmtCluster_Recv_Get__2,::__info__::RULE_SET_INFOS[41],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","r:=Rmt_1; src:=Rmt_2"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_Get__3,__romp__Rule_action__RmtCluster_Recv_Get__3,::__info__::RULE_SET_INFOS[41],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","r:=Rmt_2; src:=Home"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_Get__4,__romp__Rule_action__RmtCluster_Recv_Get__4,::__info__::RULE_SET_INFOS[41],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","r:=Rmt_2; src:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_Get__5,__romp__Rule_action__RmtCluster_Recv_Get__5,::__info__::RULE_SET_INFOS[41],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","r:=Rmt_2; src:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[42],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_GetX__0,__romp__Rule_action__RmtCluster_Recv_GetX__0,::__info__::RULE_SET_INFOS[42],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","dst:=Rmt_1; src:=Home"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_GetX__1,__romp__Rule_action__RmtCluster_Recv_GetX__1,::__info__::RULE_SET_INFOS[42],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","dst:=Rmt_1; src:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_GetX__2,__romp__Rule_action__RmtCluster_Recv_GetX__2,::__info__::RULE_SET_INFOS[42],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","dst:=Rmt_1; src:=Rmt_2"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_GetX__3,__romp__Rule_action__RmtCluster_Recv_GetX__3,::__info__::RULE_SET_INFOS[42],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","dst:=Rmt_2; src:=Home"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_GetX__4,__romp__Rule_action__RmtCluster_Recv_GetX__4,::__info__::RULE_SET_INFOS[42],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","dst:=Rmt_2; src:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_GetX__5,__romp__Rule_action__RmtCluster_Recv_GetX__5,::__info__::RULE_SET_INFOS[42],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","dst:=Rmt_2; src:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[43],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Recv_DXFER__0,__romp__Rule_action__Dir_Recv_DXFER__0,::__info__::RULE_SET_INFOS[43],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[44],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Recv_ShWb__0,__romp__Rule_action__Dir_Recv_ShWb__0,::__info__::RULE_SET_INFOS[44],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[45],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_ACK__0,__romp__Rule_action__RmtCluster_Recv_ACK__0,::__info__::RULE_SET_INFOS[45],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","dst:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_ACK__1,__romp__Rule_action__RmtCluster_Recv_ACK__1,::__info__::RULE_SET_INFOS[45],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","dst:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[46],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_Nak__0,__romp__Rule_action__RmtCluster_Recv_Nak__0,::__info__::RULE_SET_INFOS[46],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","dst:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_Nak__1,__romp__Rule_action__RmtCluster_Recv_Nak__1,::__info__::RULE_SET_INFOS[46],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","dst:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[47],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Cluster_Recv_Inv__0,__romp__Rule_action__Cluster_Recv_Inv__0,::__info__::RULE_SET_INFOS[47],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","dst:=Home"}, ::romp::Rule{__romp__Rule_guard__Cluster_Recv_Inv__1,__romp__Rule_action__Cluster_Recv_Inv__1,::__info__::RULE_SET_INFOS[47],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","dst:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__Cluster_Recv_Inv__2,__romp__Rule_action__Cluster_Recv_Inv__2,::__info__::RULE_SET_INFOS[47],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","dst:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[48],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_InvAck__0,__romp__Rule_action__RmtCluster_Recv_InvAck__0,::__info__::RULE_SET_INFOS[48],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","dst:=Rmt_1; src:=Home"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_InvAck__1,__romp__Rule_action__RmtCluster_Recv_InvAck__1,::__info__::RULE_SET_INFOS[48],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","dst:=Rmt_1; src:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_InvAck__2,__romp__Rule_action__RmtCluster_Recv_InvAck__2,::__info__::RULE_SET_INFOS[48],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","dst:=Rmt_1; src:=Rmt_2"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_InvAck__3,__romp__Rule_action__RmtCluster_Recv_InvAck__3,::__info__::RULE_SET_INFOS[48],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","dst:=Rmt_2; src:=Home"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_InvAck__4,__romp__Rule_action__RmtCluster_Recv_InvAck__4,::__info__::RULE_SET_INFOS[48],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","dst:=Rmt_2; src:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_InvAck__5,__romp__Rule_action__RmtCluster_Recv_InvAck__5,::__info__::RULE_SET_INFOS[48],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}},{\"$type\":\"kv-pair\",\"key\":\"src\",\"value\":{\"$type\":\"quantifier\",\"id\":\"src\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","dst:=Rmt_2; src:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[49],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_IACK_X___0,__romp__Rule_action__RmtCluster_Recv_IACK_X___0,::__info__::RULE_SET_INFOS[49],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","dst:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_IACK_X___1,__romp__Rule_action__RmtCluster_Recv_IACK_X___1,::__info__::RULE_SET_INFOS[49],"[{\"$type\":\"kv-pair\",\"key\":\"dst\",\"value\":{\"$type\":\"quantifier\",\"id\":\"dst\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","dst:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[50],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGet_Put__0,__romp__Rule_action__Dir_Recv_RmtGet_Put__0,::__info__::RULE_SET_INFOS[50],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","r:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGet_Put__1,__romp__Rule_action__Dir_Recv_RmtGet_Put__1,::__info__::RULE_SET_INFOS[50],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","r:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[51],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGet__RmtGet___0,__romp__Rule_action__Dir_Recv_RmtGet__RmtGet___0,::__info__::RULE_SET_INFOS[51],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","r:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGet__RmtGet___1,__romp__Rule_action__Dir_Recv_RmtGet__RmtGet___1,::__info__::RULE_SET_INFOS[51],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","r:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[52],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGetX__RmtGetX___0,__romp__Rule_action__Dir_Recv_RmtGetX__RmtGetX___0,::__info__::RULE_SET_INFOS[52],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","r:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGetX__RmtGetX___1,__romp__Rule_action__Dir_Recv_RmtGetX__RmtGetX___1,::__info__::RULE_SET_INFOS[52],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","r:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[53],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGetX_isLocal__0,__romp__Rule_action__Dir_Recv_RmtGetX_isLocal__0,::__info__::RULE_SET_INFOS[53],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","r:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGetX_isLocal__1,__romp__Rule_action__Dir_Recv_RmtGetX_isLocal__1,::__info__::RULE_SET_INFOS[53],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","r:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[54],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGet_isLocal__0,__romp__Rule_action__Dir_Recv_RmtGet_isLocal__0,::__info__::RULE_SET_INFOS[54],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","r:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGet_isLocal__1,__romp__Rule_action__Dir_Recv_RmtGet_isLocal__1,::__info__::RULE_SET_INFOS[54],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","r:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[55],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGetX_PutX__0,__romp__Rule_action__Dir_Recv_RmtGetX_PutX__0,::__info__::RULE_SET_INFOS[55],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","r:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__Dir_Recv_RmtGetX_PutX__1,__romp__Rule_action__Dir_Recv_RmtGetX_PutX__1,::__info__::RULE_SET_INFOS[55],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","r:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[56],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Cluster_WriteBack__0,__romp__Rule_action__Cluster_WriteBack__0,::__info__::RULE_SET_INFOS[56],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"Home\"}}}]","p:=Home"}, ::romp::Rule{__romp__Rule_guard__Cluster_WriteBack__1,__romp__Rule_action__Cluster_WriteBack__1,::__info__::RULE_SET_INFOS[56],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_1\"}}}]","p:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__Cluster_WriteBack__2,__romp__Rule_action__Cluster_WriteBack__2,::__info__::RULE_SET_INFOS[56],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"quantifier\",\"id\":\"p\",\"type\":\"scalarset-union-quantifier\",\"index\":2,\"value\":{\"$type\":\"value\",\"display-type\":\"Procss\",\"value\":\"_romp_Rmt_2_2\"}}}]","p:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[57],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Recv_WB__0,__romp__Rule_action__Dir_Recv_WB__0,::__info__::RULE_SET_INFOS[57],"[]",""}	}},
		{::__info__::RULE_SET_INFOS[58],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_WBAck__0,__romp__Rule_action__RmtCluster_Recv_WBAck__0,::__info__::RULE_SET_INFOS[58],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","r:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__RmtCluster_Recv_WBAck__1,__romp__Rule_action__RmtCluster_Recv_WBAck__1,::__info__::RULE_SET_INFOS[58],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","r:=Rmt_2"}	}},
		{::__info__::RULE_SET_INFOS[59],std::vector<::romp::Rule>{::romp::Rule{__romp__Rule_guard__Dir_Shrd_RmtGetX_PutX__0,__romp__Rule_action__Dir_Shrd_RmtGetX_PutX__0,::__info__::RULE_SET_INFOS[59],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_1\"}}}]","r:=Rmt_1"}, ::romp::Rule{__romp__Rule_guard__Dir_Shrd_RmtGetX_PutX__1,__romp__Rule_action__Dir_Shrd_RmtGetX_PutX__1,::__info__::RULE_SET_INFOS[59],"[{\"$type\":\"kv-pair\",\"key\":\"r\",\"value\":{\"$type\":\"quantifier\",\"id\":\"r\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Rmt\",\"value\":\"_romp_Rmt_2_2\"}}}]","r:=Rmt_2"}	}}};


// << =============================== Property Rule Expansions ================================= >> 

/* --- Property Rule(s) generated by: `CacheStateProp` (RuleSet expansions) --- */
 bool __romp__Property__CacheStateProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__CacheStateProp(); }
/* --- Property Rule(s) generated by: `CacheDataProp` (RuleSet expansions) --- */
 bool __romp__Property__CacheDataProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__CacheDataProp(); }
/* --- Property Rule(s) generated by: `OnlyCopyProp` (RuleSet expansions) --- */
 bool __romp__Property__OnlyCopyProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__OnlyCopyProp(); }
/* --- Property Rule(s) generated by: `CacheInvldDataProp` (RuleSet expansions) --- */
 bool __romp__Property__CacheInvldDataProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__CacheInvldDataProp(); }
/* --- Property Rule(s) generated by: `L2InvldDataProp` (RuleSet expansions) --- */
 bool __romp__Property__L2InvldDataProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__L2InvldDataProp(); }
/* --- Property Rule(s) generated by: `Remote_cluster_cannot_be_WRDO_` (RuleSet expansions) --- */
 bool __romp__Property__Remote_cluster_cannot_be_WRDO___0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__Remote_cluster_cannot_be_WRDO_(); }
/* --- Property Rule(s) generated by: `ClusterStateProp` (RuleSet expansions) --- */
 bool __romp__Property__ClusterStateProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__ClusterStateProp(); }
/* --- Property Rule(s) generated by: `InvldDataProp` (RuleSet expansions) --- */
 bool __romp__Property__InvldDataProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__InvldDataProp(); }
/* --- Property Rule(s) generated by: `RACINvalProp` (RuleSet expansions) --- */
 bool __romp__Property__RACINvalProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__RACINvalProp(); }
/* --- Property Rule(s) generated by: `InvStateProp` (RuleSet expansions) --- */
 bool __romp__Property__InvStateProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__InvStateProp(); }
/* --- Property Rule(s) generated by: `MemDataProp` (RuleSet expansions) --- */
 bool __romp__Property__MemDataProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__MemDataProp(); }
/* --- Property Rule(s) generated by: `tmpProp` (RuleSet expansions) --- */
 bool __romp__Property__tmpProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__tmpProp(); }
/* --- Property Rule(s) generated by: `L2_InvCnt__0` (RuleSet expansions) --- */
 bool __romp__Property__L2_InvCnt__0__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__L2_InvCnt__0(); }
/* --- Property Rule(s) generated by: `Nak_Inval_WINV` (RuleSet expansions) --- */
 bool __romp__Property__Nak_Inval_WINV__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__Nak_Inval_WINV(); }
/* --- Property Rule(s) generated by: `Uni_PutwithDataProp` (RuleSet expansions) --- */
 bool __romp__Property__Uni_PutwithDataProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__Uni_PutwithDataProp(); }
/* --- Property Rule(s) generated by: `HomeRecvIACK_X_Prop` (RuleSet expansions) --- */
 bool __romp__Property__HomeRecvIACK_X_Prop__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__HomeRecvIACK_X_Prop(); }
/* --- Property Rule(s) generated by: `isRetiredProp1` (RuleSet expansions) --- */
 bool __romp__Property__isRetiredProp1__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__isRetiredProp1(); }
/* --- Property Rule(s) generated by: `isRetiredProp2` (RuleSet expansions) --- */
 bool __romp__Property__isRetiredProp2__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__isRetiredProp2(); }
/* --- Property Rule(s) generated by: `StateProp` (RuleSet expansions) --- */
 bool __romp__Property__StateProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__StateProp(); }
/* --- Property Rule(s) generated by: `HeadPtrProp` (RuleSet expansions) --- */
 bool __romp__Property__HeadPtrProp__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__HeadPtrProp(); }
/* --- Property Rule(s) generated by: `Excl__OnlyCopy` (RuleSet expansions) --- */
 bool __romp__Property__Excl__OnlyCopy__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__Excl__OnlyCopy(); }
/* --- Property Rule(s) generated by: `HeadPtrL2__NoSharers` (RuleSet expansions) --- */
 bool __romp__Property__HeadPtrL2__NoSharers__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__HeadPtrL2__NoSharers(); }
/* --- Property Rule(s) generated by: `HeadPtrL2OnlyCopy__Excl` (RuleSet expansions) --- */
 bool __romp__Property__HeadPtrL2OnlyCopy__Excl__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__HeadPtrL2OnlyCopy__Excl(); }
/* --- Property Rule(s) generated by: `HeadPtrL2_OnlyCopy__Shrd` (RuleSet expansions) --- */
 bool __romp__Property__HeadPtrL2_OnlyCopy__Shrd__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__HeadPtrL2_OnlyCopy__Shrd(); }
/* --- Property Rule(s) generated by: `_Invld___Gblock_WB` (RuleSet expansions) --- */
 bool __romp__Property___Invld___Gblock_WB__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property___Invld___Gblock_WB(); }
/* --- Property Rule(s) generated by: `NAKC_Nakc__Excl_Inval` (RuleSet expansions) --- */
 bool __romp__Property__NAKC_Nakc__Excl_Inval__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__NAKC_Nakc__Excl_Inval(); }
/* --- Property Rule(s) generated by: `NAKC_SD__Excl_Inval__Gblock_WB` (RuleSet expansions) --- */
 bool __romp__Property__NAKC_SD__Excl_Inval__Gblock_WB__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__NAKC_SD__Excl_Inval__Gblock_WB(); }
/* --- Property Rule(s) generated by: `SHWB_ShWb_L2__Excl_Inval` (RuleSet expansions) --- */
 bool __romp__Property__SHWB_ShWb_L2__Excl_Inval__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__SHWB_ShWb_L2__Excl_Inval(); }
/* --- Property Rule(s) generated by: `SHWB_ShWb__Excl` (RuleSet expansions) --- */
 bool __romp__Property__SHWB_ShWb__Excl__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__SHWB_ShWb__Excl(); }
/* --- Property Rule(s) generated by: `SHWB_FAck_L2__Excl_Inval` (RuleSet expansions) --- */
 bool __romp__Property__SHWB_FAck_L2__Excl_Inval__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__SHWB_FAck_L2__Excl_Inval(); }
/* --- Property Rule(s) generated by: `l2HeadPtr_RD_RAC__Excl` (RuleSet expansions) --- */
 bool __romp__Property__l2HeadPtr_RD_RAC__Excl__0(const ::__model__::__romp__Model__& s) { using namespace __model__; return s.__romp__Property__l2HeadPtr_RD_RAC__Excl(); }

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
#define _ROMP_PROPERTY_RULES_LEN ((31ul) + ___propRule_assume_count___ + ___propRule_cover_count___ + ___propRule_liveness_count___)

/* All of the property rules expanded in one place */
const ::romp::Property PROPERTIES[] = {
		{__romp__Property__CacheStateProp__0,::__info__::PROPERTY_INFOS[114],"[]",""},
		{__romp__Property__CacheDataProp__0,::__info__::PROPERTY_INFOS[115],"[]",""},
		{__romp__Property__OnlyCopyProp__0,::__info__::PROPERTY_INFOS[116],"[]",""},
		{__romp__Property__CacheInvldDataProp__0,::__info__::PROPERTY_INFOS[117],"[]",""},
		{__romp__Property__L2InvldDataProp__0,::__info__::PROPERTY_INFOS[118],"[]",""},
		{__romp__Property__Remote_cluster_cannot_be_WRDO___0,::__info__::PROPERTY_INFOS[119],"[]",""},
		{__romp__Property__ClusterStateProp__0,::__info__::PROPERTY_INFOS[120],"[]",""},
		{__romp__Property__InvldDataProp__0,::__info__::PROPERTY_INFOS[121],"[]",""},
		{__romp__Property__RACINvalProp__0,::__info__::PROPERTY_INFOS[122],"[]",""},
		{__romp__Property__InvStateProp__0,::__info__::PROPERTY_INFOS[123],"[]",""},
		{__romp__Property__MemDataProp__0,::__info__::PROPERTY_INFOS[124],"[]",""},
		{__romp__Property__tmpProp__0,::__info__::PROPERTY_INFOS[125],"[]",""},
		{__romp__Property__L2_InvCnt__0__0,::__info__::PROPERTY_INFOS[126],"[]",""},
		{__romp__Property__Nak_Inval_WINV__0,::__info__::PROPERTY_INFOS[127],"[]",""},
		{__romp__Property__Uni_PutwithDataProp__0,::__info__::PROPERTY_INFOS[128],"[]",""},
		{__romp__Property__HomeRecvIACK_X_Prop__0,::__info__::PROPERTY_INFOS[129],"[]",""},
		{__romp__Property__isRetiredProp1__0,::__info__::PROPERTY_INFOS[130],"[]",""},
		{__romp__Property__isRetiredProp2__0,::__info__::PROPERTY_INFOS[131],"[]",""},
		{__romp__Property__StateProp__0,::__info__::PROPERTY_INFOS[132],"[]",""},
		{__romp__Property__HeadPtrProp__0,::__info__::PROPERTY_INFOS[133],"[]",""},
		{__romp__Property__Excl__OnlyCopy__0,::__info__::PROPERTY_INFOS[134],"[]",""},
		{__romp__Property__HeadPtrL2__NoSharers__0,::__info__::PROPERTY_INFOS[135],"[]",""},
		{__romp__Property__HeadPtrL2OnlyCopy__Excl__0,::__info__::PROPERTY_INFOS[136],"[]",""},
		{__romp__Property__HeadPtrL2_OnlyCopy__Shrd__0,::__info__::PROPERTY_INFOS[137],"[]",""},
		{__romp__Property___Invld___Gblock_WB__0,::__info__::PROPERTY_INFOS[138],"[]",""},
		{__romp__Property__NAKC_Nakc__Excl_Inval__0,::__info__::PROPERTY_INFOS[139],"[]",""},
		{__romp__Property__NAKC_SD__Excl_Inval__Gblock_WB__0,::__info__::PROPERTY_INFOS[140],"[]",""},
		{__romp__Property__SHWB_ShWb_L2__Excl_Inval__0,::__info__::PROPERTY_INFOS[141],"[]",""},
		{__romp__Property__SHWB_ShWb__Excl__0,::__info__::PROPERTY_INFOS[142],"[]",""},
		{__romp__Property__SHWB_FAck_L2__Excl_Inval__0,::__info__::PROPERTY_INFOS[143],"[]",""},
		{__romp__Property__l2HeadPtr_RD_RAC__Excl__0,::__info__::PROPERTY_INFOS[144],"[]",""},
};


// << ================================= Startstate Expansions ================================== >> 

/* --- StartState Rule(s) generated by: `Init` (RuleSet expansions) --- */
 void __romp__StartState__Init__0(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__StartState__Init(_romp_Datas_2_1); }
 void __romp__StartState__Init__1(::__model__::__romp__Model__& s) { using namespace __model__; s.__romp__StartState__Init(_romp_Datas_2_2); }


#define _ROMP_STARTSTATES_LEN (2ul) // the number of property rules (after ruleset expansion) in the model
// all of the startstates in one place (post ruleset expansion)
const ::romp::StartState STARTSTATES[] = {{__romp__StartState__Init__0,::__info__::STARTSTATE_INFOS[0],0,"[{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"quantifier\",\"id\":\"d\",\"type\":\"scalarset-quantifier\",\"index\":0,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_1\"}}}]","d:=Datas_1"}, {__romp__StartState__Init__1,::__info__::STARTSTATE_INFOS[0],1,"[{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"quantifier\",\"id\":\"d\",\"type\":\"scalarset-quantifier\",\"index\":1,\"value\":{\"$type\":\"value\",\"display-type\":\"Datas\",\"value\":\"_romp_Datas_2_2\"}}}]","d:=Datas_2"}};


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
