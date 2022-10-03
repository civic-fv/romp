/*
	Generated code for a romp "parallel random walker" verification tool based off of the Murphi Model described in:
		Original Murphi Model: dek.m
	Please build with the following command(s):
		<not-implemented-yet>
*/


#define __romp__GENERATED_CODE


#define _ROMP_STATE_TYPE ::__model__::__Model__


#define _ROMP_STATE_HISTORY_LEN (4ul)


#define _ROMP_THREAD_TO_RW_RATIO (8ul)


#define __model__filepath "/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m"


#define __model__filepath_contains_space (true)


#define __model__filename "dek.m"

#define __model__filename_contains_space (false)


#define __romp__ENABLE_liveness_property

#define __romp__ENABLE_cover_property

#define __romp__ENABLE_assume_property

#define __ROMP__DO_MEASURE

#define __ROMP__SIMPLE_TRACE

#define _ROMP_HIST_LEN (4ul)

#define __romp__ENABLE_symmetry

#pragma region inline_library_includes


#pragma endregion inline_library_includes

namespace __model__ { struct __Model__; } // helpful pre-definition


#pragma region model_prefixes

#include "/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/resources/c_prefix.cpp"

#pragma endregion model_prefixes



#pragma region generated_code


/* ======= Header Comments ====== */


/* ======= Model Type & Const Definitions ====== */

namespace __type__ {
  typedef int range_t;
  typedef unsigned int scalarset_t;
  typedef int enum_backend_t;
  typedef range_t ind_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& ind_t_to_json(::romp::ojstream<O>& json, const ind_t& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& ind_t_to_json(::romp::ojstream<O>& json, const ind_t& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"ind_t\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(1)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& ind_t_to_str(::romp::ostream_p& out, const ind_t& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef enum { init, whileOtherLocked, checkTurn, unlock, waitForTurn, lockAndRetry, crit, exitCrit, } label_t;
  std::string to_string(const label_t val) { switch (val) { case init: return "init"; case whileOtherLocked: return "whileOtherLocked"; case checkTurn: return "checkTurn"; case unlock: return "unlock"; case waitForTurn: return "waitForTurn"; case lockAndRetry: return "lockAndRetry"; case crit: return "crit"; case exitCrit: return "exitCrit"; default: break; } return "label_t::__UNKNOWN_ENUM_VALUE__"; }
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& label_t_to_json(::romp::ojstream<O>& json, const label_t& val) noexcept { json << '"' << to_string(val) << '"'; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& label_t_to_json(::romp::ojstream<O>& json, const label_t& val) noexcept { json << "{\"$type\":\"enum-value\",\"type\":\"label_t\",\"value\":\"" << to_string(val) <<"\"}"; return ::romp::S_VOID; }
#endif
  const ::romp::stream_void& label_t_to_str(::romp::ostream_p& out, const label_t& val) noexcept { out << to_string(val); return ::romp::S_VOID; }

  typedef enum { locked, unlocked, } lock_t;
  std::string to_string(const lock_t val) { switch (val) { case locked: return "locked"; case unlocked: return "unlocked"; default: break; } return "lock_t::__UNKNOWN_ENUM_VALUE__"; }
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& lock_t_to_json(::romp::ojstream<O>& json, const lock_t& val) noexcept { json << '"' << to_string(val) << '"'; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& lock_t_to_json(::romp::ojstream<O>& json, const lock_t& val) noexcept { json << "{\"$type\":\"enum-value\",\"type\":\"lock_t\",\"value\":\"" << to_string(val) <<"\"}"; return ::romp::S_VOID; }
#endif
  const ::romp::stream_void& lock_t_to_str(::romp::ostream_p& out, const lock_t& val) noexcept { out << to_string(val); return ::romp::S_VOID; }

  typedef struct { ::__type__::label_t data[2]; constexpr const size_t size() const {return (2ul);} } anon0x0_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x0_t_to_json(::romp::ojstream<O>& json, const anon0x0_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << label_t_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x0_t_to_json(::romp::ojstream<O>& json, const anon0x0_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[ind_t] of label_t\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(1) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << label_t_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x0_t_to_str(::romp::ostream_p& out, const anon0x0_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< label_t_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct { ::__type__::lock_t data[2]; constexpr const size_t size() const {return (2ul);} } anon0x1_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x1_t_to_json(::romp::ojstream<O>& json, const anon0x1_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << lock_t_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x1_t_to_json(::romp::ojstream<O>& json, const anon0x1_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[ind_t] of lock_t\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(1) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << lock_t_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x1_t_to_str(::romp::ostream_p& out, const anon0x1_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< lock_t_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef range_t anon0x2_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x2_t_to_json(::romp::ojstream<O>& json, const anon0x2_t& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x2_t_to_json(::romp::ojstream<O>& json, const anon0x2_t& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"0..1\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(1)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x2_t_to_str(::romp::ostream_p& out, const anon0x2_t& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}


}



/* ======= Generated Model & State ====== */

namespace __model__ {

  struct __Model__ {
    ::romp::IRandWalker* __rw__; // reference to associated romp rand walker


    /* ======= Model State Variables ====== */

    ::__type__::anon0x0_t s;

    ::__type__::anon0x1_t c;

    ::__type__::anon0x2_t turn;


    /* ======= Murphi Model Functions ====== */

    
    void Goto(const ::__type__::ind_t p, const ::__type__::label_t label)  {
      using namespace ::__type__;
      try {
        //----------------------------------------------------------------------
        // Copyright (C) 1992, 1993 by the Board of Trustees of 		 
        // Leland Stanford Junior University.					 
        //									 
        // This description is provided to serve as an example of the use	 
        // of the Murphi description language and verifier, and as a benchmark	 
        // example for other verification efforts.				 
        //									 
        // License to use, copy, modify, sell and/or distribute this description 
        // and its documentation any purpose is hereby granted without royalty,  
        // subject to the following terms and conditions, provided		 
        //									 
        // 1.  The above copyright notice and this permission notice must	 
        // appear in all copies of this description.				 
        // 									 
        // 2.  The Murphi group at Stanford University must be acknowledged	 
        // in any publication describing work that makes use of this example. 	 
        // 									 
        // Nobody vouches for the accuracy or usefulness of this description	 
        // for any purpose.							 
        //-----------------------------------------------------------------------
        //--------------------------------------------------------------------
        // Filename:	dek.m
        // Version:	Murphi 2.3
        // Content: 	Dekker's algorithm for mutual exclusion.
        //		Satisfies all conditions for a correct solution.
        // Last modification:
        //              modified 8/25/92 by Ralph Melton for Murphi 2.3
        //--------------------------------------------------------------------
        ((s).data[((p)) - int_VALUE_C(0)]) = (label);
      } catch (...) { throw ::romp::ModelFunctError(0); }
}


    /* ======= Murphi Model StartStates, Rules & Global Properties ====== */

     void __StartState__startstate1(void){
      using namespace ::__type__;
      try {
        // While c[1-p]=locked
        // Repeat until turn=p
        do {
          for (int p = ((int)(0)); p <= ((int)(1)); p++) {
            ::__model__::__Model__::Goto((p), (init));
            ((c).data[((p)) - int_VALUE_C(0)]) = (unlocked);
          }
        } while (0);
        (turn) = ((int)(0));
      } catch (...) { throw ::romp::ModelStartStateError(0); }
    }



    
    bool __Rule_guard__Init(const ::__type__::ind_t p) const {
      using namespace ::__type__;
      try {
        return (((s).data[((p)) - int_VALUE_C(0)]) == (init));
      } catch (...) { throw ::romp::ModelRuleError(0,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__Init(const ::__type__::ind_t p) {
      using namespace ::__type__;
      try {
        ((c).data[((p)) - int_VALUE_C(0)]) = (locked);
        ::__model__::__Model__::Goto((p), (whileOtherLocked));
      } catch (...) { throw ::romp::ModelRuleError(0,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__WhileOtherLocked(const ::__type__::ind_t p) const {
      using namespace ::__type__;
      try {
        return (((s).data[((p)) - int_VALUE_C(0)]) == (whileOtherLocked));
      } catch (...) { throw ::romp::ModelRuleError(1,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__WhileOtherLocked(const ::__type__::ind_t p) {
      using namespace ::__type__;
      try {
        if (((c).data[((((int)(1)) - (p))) - int_VALUE_C(0)]) == (unlocked)) {
          ::__model__::__Model__::Goto((p), (crit));
        } else {
          ::__model__::__Model__::Goto((p), (checkTurn));
        }
      } catch (...) { throw ::romp::ModelRuleError(1,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__CheckTurn(const ::__type__::ind_t p) const {
      using namespace ::__type__;
      try {
        return (((s).data[((p)) - int_VALUE_C(0)]) == (checkTurn));
      } catch (...) { throw ::romp::ModelRuleError(2,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__CheckTurn(const ::__type__::ind_t p) {
      using namespace ::__type__;
      try {
        if ((turn) == (((int)(1)) - (p))) {
          ::__model__::__Model__::Goto((p), (unlock));
        } else {
          ::__model__::__Model__::Goto((p), (whileOtherLocked));
        }
      } catch (...) { throw ::romp::ModelRuleError(2,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__Unlock(const ::__type__::ind_t p) const {
      using namespace ::__type__;
      try {
        return (((s).data[((p)) - int_VALUE_C(0)]) == (unlock));
      } catch (...) { throw ::romp::ModelRuleError(3,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__Unlock(const ::__type__::ind_t p) {
      using namespace ::__type__;
      try {
        ((c).data[((p)) - int_VALUE_C(0)]) = (unlocked);
        ::__model__::__Model__::Goto((p), (waitForTurn));
      } catch (...) { throw ::romp::ModelRuleError(3,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__WaitForTurn(const ::__type__::ind_t p) const {
      using namespace ::__type__;
      try {
        return (((s).data[((p)) - int_VALUE_C(0)]) == (waitForTurn));
      } catch (...) { throw ::romp::ModelRuleError(4,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__WaitForTurn(const ::__type__::ind_t p) {
      using namespace ::__type__;
      try {
        if ((turn) != (p)) {
          ::__model__::__Model__::Goto((p), (lockAndRetry));
        }
      } catch (...) { throw ::romp::ModelRuleError(4,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__LockAndRetry(const ::__type__::ind_t p) const {
      using namespace ::__type__;
      try {
        return (((s).data[((p)) - int_VALUE_C(0)]) == (lockAndRetry));
      } catch (...) { throw ::romp::ModelRuleError(5,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__LockAndRetry(const ::__type__::ind_t p) {
      using namespace ::__type__;
      try {
        ((c).data[((p)) - int_VALUE_C(0)]) = (locked);
        ::__model__::__Model__::Goto((p), (whileOtherLocked));
      } catch (...) { throw ::romp::ModelRuleError(5,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__Crit(const ::__type__::ind_t p) const {
      using namespace ::__type__;
      try {
        return (((s).data[((p)) - int_VALUE_C(0)]) == (crit));
      } catch (...) { throw ::romp::ModelRuleError(6,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__Crit(const ::__type__::ind_t p) {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Goto((p), (exitCrit));
      } catch (...) { throw ::romp::ModelRuleError(6,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__ExitCrit(const ::__type__::ind_t p) const {
      using namespace ::__type__;
      try {
        return (((s).data[((p)) - int_VALUE_C(0)]) == (exitCrit));
      } catch (...) { throw ::romp::ModelRuleError(7,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__ExitCrit(const ::__type__::ind_t p) {
      using namespace ::__type__;
      try {
        ((c).data[((p)) - int_VALUE_C(0)]) = (unlocked);
        (turn) = (((int)(1)) - (p));
        ::__model__::__Model__::Goto((p), (init));
      } catch (...) { throw ::romp::ModelRuleError(7,::romp::ModelRuleError::ACTION); }
    }


    
    bool __Property__property2(void) const {
      using namespace ::__type__;
      try {
        return this->__rw__->invariant_handler((!((((s).data[(((int)(0))) - int_VALUE_C(0)]) == (crit)) && (((s).data[(((int)(1))) - int_VALUE_C(0)]) == (crit)))),0u);
      } catch (...) { throw ::romp::ModelPropertyError(0); }
    }


  };

  /* ======= Murphi Model Output Functions ====== */
#ifdef __ROMP__SIMPLE_TRACE
template<class O> const ::romp::stream_void& __Model___to_json(::romp::ojstream<O>& json, const __Model__& val) noexcept { using namespace ::__type__; json  << anon0x0_t_to_json(json,val.s) << ',' << anon0x1_t_to_json(json,val.c) << ',' << anon0x2_t_to_json(json,val.turn); return ::romp::S_VOID; }
#else
template<class O> const ::romp::stream_void& __Model___to_json(::romp::ojstream<O>& json, const __Model__& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"__Model__\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"s\",\"value\":" << anon0x0_t_to_json(json,val.s) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"c\",\"value\":" << anon0x1_t_to_json(json,val.c) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"turn\",\"value\":" << anon0x2_t_to_json(json,val.turn)<< "}]}"; return ::romp::S_VOID;}
#endif
const ::romp::stream_void& __Model___to_str(::romp::ostream_p& out, const __Model__& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "s " << ((::romp::OPTIONS.report_show_type) ? ": Array[ind_t] of label_t =" : ":=") << ' ' << anon0x0_t_to_str(out,val.s) << '\n' << out.indentation() << "c " << ((::romp::OPTIONS.report_show_type) ? ": Array[ind_t] of lock_t =" : ":=") << ' ' << anon0x1_t_to_str(out,val.c) << '\n' << out.indentation() << "turn " << ((::romp::OPTIONS.report_show_type) ? ": 0..1 =" : ":=") << ' ' << anon0x2_t_to_str(out,val.turn) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}
}
namespace romp {
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> ::romp::ojstream<O>& operator << (::romp::ojstream<O>& json, const ::__model__::__Model__& s) { json << '[' << ::__model__::__Model___to_json(json,s) << ']'; return json; }
#else
  template<class O> ::romp::ojstream<O>& operator << (::romp::ojstream<O>& json, const ::__model__::__Model__& s) { (void) ::__model__::__Model___to_json(json,s); return json; }
#endif
  ::romp::ostream_p& operator << (::romp::ostream_p& out, const ::__model__::__Model__& s) { (void) ::__model__::__Model___to_str(out,s); return out; }
  ::std::ostream& operator << (::std::ostream& out_, const ::__model__::__Model__& s) { ::romp::ostream_p out(out_,2); (void) ::__model__::__Model___to_str(out,s); return out_; }
}



/* ======= Murphi Model Infos & MetaData ====== */
namespace __info__ {

/* the number possible variations in the state (# of permutations of the state-space) */
#define _ROMP_STATESPACE_COUNT_str "59049"
/* the number of functions & procedures in the model */
#define _ROMP_FUNCTS_LEN (1ul)
  /* the info/metadata about the functions/procedures in the model */
  const ::romp::FunctInfo FUNCT_INFOS[_ROMP_FUNCTS_LEN] = {{"Goto",{{43,1},{46,5}},"{\"$type\":\"procedure\",\"label\":\"Goto\",\"params\":[{\"$type\":\"param\",\"id\":\"p\",\"type\":\"ind_t\"},{\"$type\":\"param\",\"id\":\"label\",\"type\":\"label_t\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m\",\"start\":[43,1],\"end\":[46,5]}}","procedure Goto(var p: ind_t; var label: label_t);"},};
/* the number of error statements in the model */
#define _ROMP_ERRORS_LEN (0ul)
  /* the info/metadata about the murphi error statements in the model */
  const ::romp::MErrorInfo ERROR_INFOS[_ROMP_ERRORS_LEN] = {};
/* the number of property statements & rules in the model */
#define _ROMP_PROPERTIES_LEN (1ul)
/* the number of cover property statements & rules in the model */
#define _ROMP_COVER_PROP_COUNT (0ul) // the number of property rules (after ruleset expansion) in the model
/* the number of liveness property rules in the model */
#define _ROMP_LIVENESS_PROP_COUNT (0ul) // the number of property rules (after ruleset expansion) in the model
  /* the info/metadata about the murphi properties in the model */
  const ::romp::PropertyInfo PROPERTY_INFOS[_ROMP_PROPERTIES_LEN] = {{"property2",::romp::PropertyType::INVARIANT,"(!((s[0] = crit) & (s[1] = crit)))",0,{{134,1},{135,32}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"(!((s[0] = crit) & (s[1] = crit)))\",\"label\":\"property2\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m\",\"start\":[134,1],\"end\":[135,32]}"},};
/* the number of start state rules (before ruleset expansions) in the model */
#define _ROMP_STARTSTATE_INFO_LEN (1ul)
  /* the info/metadata about the startstate rules in the model */
  const ::romp::StartStateInfo STARTSTATE_INFOS[_ROMP_STARTSTATE_INFO_LEN] = {{"startstate1",{{125,1},{132,4}},"{\"$type\":\"startstate\",\"label\":\"startstate1\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m\",\"start\":[125,1],\"end\":[132,4]}"},};
/* the number of rules in the model, BEFORE ruleset expansion */
#define _ROMP_RULESETS_LEN (8ul)
  /* the info/metadata about the rules in the model */
  const ::romp::RuleInfo RULE_SET_INFOS[_ROMP_RULESETS_LEN] = {{"Init",{{50,2},{56,5}},"{\"$type\":\"rule\",\"expr\":\"(s[p] = init)\",\"label\":\"Init\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m\",\"start\":[50,2],\"end\":[56,5]}"},{"WhileOtherLocked",{{58,2},{67,5}},"{\"$type\":\"rule\",\"expr\":\"(s[p] = whileOtherLocked)\",\"label\":\"WhileOtherLocked\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m\",\"start\":[58,2],\"end\":[67,5]}"},{"CheckTurn",{{69,2},{78,5}},"{\"$type\":\"rule\",\"expr\":\"(s[p] = checkTurn)\",\"label\":\"CheckTurn\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m\",\"start\":[69,2],\"end\":[78,5]}"},{"Unlock",{{80,2},{86,5}},"{\"$type\":\"rule\",\"expr\":\"(s[p] = unlock)\",\"label\":\"Unlock\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m\",\"start\":[80,2],\"end\":[86,5]}"},{"WaitForTurn",{{88,2},{95,5}},"{\"$type\":\"rule\",\"expr\":\"(s[p] = waitForTurn)\",\"label\":\"WaitForTurn\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m\",\"start\":[88,2],\"end\":[95,5]}"},{"LockAndRetry",{{97,2},{103,5}},"{\"$type\":\"rule\",\"expr\":\"(s[p] = lockAndRetry)\",\"label\":\"LockAndRetry\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m\",\"start\":[97,2],\"end\":[103,5]}"},{"Crit",{{105,2},{110,5}},"{\"$type\":\"rule\",\"expr\":\"(s[p] = crit)\",\"label\":\"Crit\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m\",\"start\":[105,2],\"end\":[110,5]}"},{"ExitCrit",{{112,2},{119,5}},"{\"$type\":\"rule\",\"expr\":\"(s[p] = exitCrit)\",\"label\":\"ExitCrit\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/dek.m\",\"start\":[112,2],\"end\":[119,5]}"},};

}

/* ======= Romp CALLER Lists ====== */
namespace __caller__ {
  typedef ::__model__::__Model__ State_t; // type mask for the generated state object
  /* --- Rules Generated by: `Init` (RuleSet expansions) --- */
   bool __Rule_guard__Init__0(const State_t& s){return s.__Rule_guard__Init((::__type__::ind_t) 0); }
   void __Rule_action__Init__0(State_t& s){s.__Rule_action__Init((::__type__::ind_t) 0); }
   bool __Rule_guard__Init__1(const State_t& s){return s.__Rule_guard__Init((::__type__::ind_t) 1); }
   void __Rule_action__Init__1(State_t& s){s.__Rule_action__Init((::__type__::ind_t) 1); }
  /* --- Rules Generated by: `WhileOtherLocked` (RuleSet expansions) --- */
   bool __Rule_guard__WhileOtherLocked__0(const State_t& s){return s.__Rule_guard__WhileOtherLocked((::__type__::ind_t) 0); }
   void __Rule_action__WhileOtherLocked__0(State_t& s){s.__Rule_action__WhileOtherLocked((::__type__::ind_t) 0); }
   bool __Rule_guard__WhileOtherLocked__1(const State_t& s){return s.__Rule_guard__WhileOtherLocked((::__type__::ind_t) 1); }
   void __Rule_action__WhileOtherLocked__1(State_t& s){s.__Rule_action__WhileOtherLocked((::__type__::ind_t) 1); }
  /* --- Rules Generated by: `CheckTurn` (RuleSet expansions) --- */
   bool __Rule_guard__CheckTurn__0(const State_t& s){return s.__Rule_guard__CheckTurn((::__type__::ind_t) 0); }
   void __Rule_action__CheckTurn__0(State_t& s){s.__Rule_action__CheckTurn((::__type__::ind_t) 0); }
   bool __Rule_guard__CheckTurn__1(const State_t& s){return s.__Rule_guard__CheckTurn((::__type__::ind_t) 1); }
   void __Rule_action__CheckTurn__1(State_t& s){s.__Rule_action__CheckTurn((::__type__::ind_t) 1); }
  /* --- Rules Generated by: `Unlock` (RuleSet expansions) --- */
   bool __Rule_guard__Unlock__0(const State_t& s){return s.__Rule_guard__Unlock((::__type__::ind_t) 0); }
   void __Rule_action__Unlock__0(State_t& s){s.__Rule_action__Unlock((::__type__::ind_t) 0); }
   bool __Rule_guard__Unlock__1(const State_t& s){return s.__Rule_guard__Unlock((::__type__::ind_t) 1); }
   void __Rule_action__Unlock__1(State_t& s){s.__Rule_action__Unlock((::__type__::ind_t) 1); }
  /* --- Rules Generated by: `WaitForTurn` (RuleSet expansions) --- */
   bool __Rule_guard__WaitForTurn__0(const State_t& s){return s.__Rule_guard__WaitForTurn((::__type__::ind_t) 0); }
   void __Rule_action__WaitForTurn__0(State_t& s){s.__Rule_action__WaitForTurn((::__type__::ind_t) 0); }
   bool __Rule_guard__WaitForTurn__1(const State_t& s){return s.__Rule_guard__WaitForTurn((::__type__::ind_t) 1); }
   void __Rule_action__WaitForTurn__1(State_t& s){s.__Rule_action__WaitForTurn((::__type__::ind_t) 1); }
  /* --- Rules Generated by: `LockAndRetry` (RuleSet expansions) --- */
   bool __Rule_guard__LockAndRetry__0(const State_t& s){return s.__Rule_guard__LockAndRetry((::__type__::ind_t) 0); }
   void __Rule_action__LockAndRetry__0(State_t& s){s.__Rule_action__LockAndRetry((::__type__::ind_t) 0); }
   bool __Rule_guard__LockAndRetry__1(const State_t& s){return s.__Rule_guard__LockAndRetry((::__type__::ind_t) 1); }
   void __Rule_action__LockAndRetry__1(State_t& s){s.__Rule_action__LockAndRetry((::__type__::ind_t) 1); }
  /* --- Rules Generated by: `Crit` (RuleSet expansions) --- */
   bool __Rule_guard__Crit__0(const State_t& s){return s.__Rule_guard__Crit((::__type__::ind_t) 0); }
   void __Rule_action__Crit__0(State_t& s){s.__Rule_action__Crit((::__type__::ind_t) 0); }
   bool __Rule_guard__Crit__1(const State_t& s){return s.__Rule_guard__Crit((::__type__::ind_t) 1); }
   void __Rule_action__Crit__1(State_t& s){s.__Rule_action__Crit((::__type__::ind_t) 1); }
  /* --- Rules Generated by: `ExitCrit` (RuleSet expansions) --- */
   bool __Rule_guard__ExitCrit__0(const State_t& s){return s.__Rule_guard__ExitCrit((::__type__::ind_t) 0); }
   void __Rule_action__ExitCrit__0(State_t& s){s.__Rule_action__ExitCrit((::__type__::ind_t) 0); }
   bool __Rule_guard__ExitCrit__1(const State_t& s){return s.__Rule_guard__ExitCrit((::__type__::ind_t) 1); }
   void __Rule_action__ExitCrit__1(State_t& s){s.__Rule_action__ExitCrit((::__type__::ind_t) 1); }

/* the number of rules in the model, AFTER ruleset expansion */
#define _ROMP_RULE_COUNT (16ul)


  // All of the rule sets in one place
  const ::romp::RuleSet RULESETS[_ROMP_RULESETS_LEN] = {
		{::__info__::RULE_SET_INFOS[0],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__Init__0,__Rule_action__Init__0,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":0}}]","p:=0"}, ::romp::Rule{__Rule_guard__Init__1,__Rule_action__Init__1,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":1}}]","p:=1"}  	}},
		{::__info__::RULE_SET_INFOS[1],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__WhileOtherLocked__0,__Rule_action__WhileOtherLocked__0,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":0}}]","p:=0"}, ::romp::Rule{__Rule_guard__WhileOtherLocked__1,__Rule_action__WhileOtherLocked__1,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":1}}]","p:=1"}  	}},
		{::__info__::RULE_SET_INFOS[2],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__CheckTurn__0,__Rule_action__CheckTurn__0,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":0}}]","p:=0"}, ::romp::Rule{__Rule_guard__CheckTurn__1,__Rule_action__CheckTurn__1,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":1}}]","p:=1"}  	}},
		{::__info__::RULE_SET_INFOS[3],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__Unlock__0,__Rule_action__Unlock__0,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":0}}]","p:=0"}, ::romp::Rule{__Rule_guard__Unlock__1,__Rule_action__Unlock__1,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":1}}]","p:=1"}  	}},
		{::__info__::RULE_SET_INFOS[4],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__WaitForTurn__0,__Rule_action__WaitForTurn__0,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":0}}]","p:=0"}, ::romp::Rule{__Rule_guard__WaitForTurn__1,__Rule_action__WaitForTurn__1,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":1}}]","p:=1"}  	}},
		{::__info__::RULE_SET_INFOS[5],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__LockAndRetry__0,__Rule_action__LockAndRetry__0,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":0}}]","p:=0"}, ::romp::Rule{__Rule_guard__LockAndRetry__1,__Rule_action__LockAndRetry__1,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":1}}]","p:=1"}  	}},
		{::__info__::RULE_SET_INFOS[6],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__Crit__0,__Rule_action__Crit__0,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":0}}]","p:=0"}, ::romp::Rule{__Rule_guard__Crit__1,__Rule_action__Crit__1,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":1}}]","p:=1"}  	}},
		{::__info__::RULE_SET_INFOS[7],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__ExitCrit__0,__Rule_action__ExitCrit__0,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":0}}]","p:=0"}, ::romp::Rule{__Rule_guard__ExitCrit__1,__Rule_action__ExitCrit__1,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"p\",\"value\":{\"$type\":\"range-value\",\"type\":\"ind_t\",\"value\":1}}]","p:=1"}  	}}};

  /* --- Property Rule(s) generated by: `property2` (RuleSet expansions) --- */
   bool __Property__property2__0(const State_t& s) {return s.__Property__property2(); }

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
const ::romp::Property PROPERTIES[_ROMP_PROPERTY_RULES_LEN] = {
		{__Property__property2__0,::__info__::PROPERTY_INFOS[0],"[]",""},
};

  /* --- StartState Rule(s) generated by: `startstate1` (RuleSet expansions) --- */
   void __StartState__startstate1__0(State_t& s){ s.__StartState__startstate1(); }


#define _ROMP_STARTSTATES_LEN (1ul) // the number of property rules (after ruleset expansion) in the model

  // All of the rule sets in one place
const ::romp::StartState STARTSTATES[_ROMP_STARTSTATES_LEN] = {{__StartState__startstate1__0,::__info__::STARTSTATE_INFOS[0],0,"[]",""}};


}



#pragma endregion generated_code


#pragma region romp_rw

#include "/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/resources/romp-rw.hpp"

#pragma endregion romp_rw


#pragma region romp_rw_options

#include "/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/resources/romp-rw-options.hpp"

#pragma endregion romp_rw_options


#pragma region romp_rw_main

#include "/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/resources/romp-rw-main.hpp"

#pragma endregion romp_rw_main
