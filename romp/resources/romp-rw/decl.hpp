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


#define _ROMP_TRACE_JSON_VERSION "0.0.3"
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
  extern const std::string SCALAR_IDS[];
  extern const std::string RECORD_MEMBER_LABELS[];
  extern const ::romp::TypeInfo TYPE_INFOS[];
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


  struct file_position {
    size_t row;
    size_t col;
  };

  struct location {
    // std::string model_obj;
    file_position start;
    file_position end;
  };

  enum TypeType { BOOLEAN, RANGE, ENUM, SCALARSET, SCALARSET_UNION, ARRAY, MULTISET, RECORD, RECORD_MEMBER, TYPE_EXPR_ID };

  struct TypeInfo {
    std::string label;
    TypeType type;
    std::string repr;
    location loc;
    std::vector<id_t> dependents;
  };


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
    bool isFunct;
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
     * @return \c size_t - the index in the multiset that has been choosen
     */
    virtual size_t choose_handler(size_t occupancy) = 0;
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
    ~Result() { if (tripped != nullptr) delete tripped; if (inside != nullptr) delete inside; }
  };



} // namespace romp

namespace __type__ {
  typedef bool boolean; // builtin type mask for Murphi's boolean
  template<class O> const ::romp::stream_void boolean_to_json(::romp::ojstream<O>& json, const ::__type__::boolean val) { 
#ifdef __ROMP__SIMPLE_TRACE
    json << ((bool)val);
#else
    json << "{\"$type\":\"boolean-value\",\"value\":" << ((bool)val) << "}"; 
#endif
    return ::romp::S_VOID; 
  }
  const ::romp::stream_void boolean_to_str(::romp::ostream_p& out, const ::__type__::boolean val) { out << (((bool)val) ? "true" : "false" ); return ::romp::S_VOID; }
} // namespace __type__
