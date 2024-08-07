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
 * @version 0.3
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

  const RandSeed_t INIT_SEED = ([]() -> RandSeed_t {
                                  // struct timeval tp; // from mimicing cmurphi random
                                  // struct timezone tzp;
                                  // // select a "random" seed
                                  // gettimeofday(&tp, &tzp);
                                  // size_t value = ((unsigned long) (tp.tv_sec ^ tp.tv_usec) * 2654435769ul) >> 1;
                                  // if (value == 0)
                                  //   value = 46831694;
                                  // return value;
                                  std::random_device rd;
                                  std::mt19937 mt(rd());
                                  std::uniform_real_distribution<double> dist(0,UINT32_MAX); //TODO examine this for issues in randomness
                                  return dist(mt);
                                })();

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
        DEADLOCK,
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

  // constexpr size_t MAX_RULESET_SIZE();

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
