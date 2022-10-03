/*
	Generated code for a romp "parallel random walker" verification tool based off of the Murphi Model described in:
		Original Murphi Model: sort5.m
	Please build with the following command(s):
		<not-implemented-yet>
*/


#define __romp__GENERATED_CODE


#define _ROMP_STATE_TYPE ::__model__::__Model__


#define _ROMP_STATE_HISTORY_LEN (4ul)


#define _ROMP_THREAD_TO_RW_RATIO (8ul)


#define __model__filepath "/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/sort5.m"


#define __model__filepath_contains_space (true)


#define __model__filename "sort5.m"

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
  const __typeof__(((int)(5))) N = ((int)(5));
  typedef range_t ind_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& ind_t_to_json(::romp::ojstream<O>& json, const ind_t& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& ind_t_to_json(::romp::ojstream<O>& json, const ind_t& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"ind_t\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(4)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& ind_t_to_str(::romp::ostream_p& out, const ind_t& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef range_t val_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& val_t_to_json(::romp::ojstream<O>& json, const val_t& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& val_t_to_json(::romp::ojstream<O>& json, const val_t& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"val_t\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(4)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& val_t_to_str(::romp::ostream_p& out, const val_t& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef struct { ::__type__::val_t data[5]; constexpr const size_t size() const {return (5ul);} } arr_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& arr_t_to_json(::romp::ojstream<O>& json, const arr_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << val_t_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& arr_t_to_json(::romp::ojstream<O>& json, const arr_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"arr_t\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(4) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << val_t_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& arr_t_to_str(::romp::ostream_p& out, const arr_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< val_t_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef ::__type__::boolean bool_t;
  template<class O> const ::romp::stream_void& bool_t_to_json(::romp::ojstream<O>& json, const bool_t& val) noexcept{ json << boolean_to_json(json,((boolean)val)); return ::romp::S_VOID;}
  const ::romp::stream_void& bool_t_to_str(::romp::ostream_p& out, const bool_t& val) noexcept { out << boolean_to_str(out,((boolean)val)); return ::romp::S_VOID;}


}



/* ======= Generated Model & State ====== */

namespace __model__ {

  struct __Model__ {
    ::romp::IRandWalker* __rw__; // reference to associated romp rand walker


    /* ======= Model State Variables ====== */

    ::__type__::ind_t i;

    ::__type__::ind_t j;

    ::__type__::arr_t a;


    /* ======= Murphi Model Functions ====== */

    
    void IncrementMod(::__type__::ind_t& v, const ::__type__::ind_t m)  {
      using namespace ::__type__;
      try {
        //------------------------------------------------------------------------------
        // Copyright (C) 1992, 1993 by the Board of Trustees of 		      --	
        // Leland Stanford Junior University.					      --	
        //									      --
        // This description is provided to serve as an example of the use	      --
        // of the Murphi description language and verifier, and as a benchmark	      --
        // example for other verification efforts.				      --	
        //									      --	
        // License to use, copy, modify, sell and/or distribute this description      --
        // and its documentation any purpose is hereby granted without royalty,       --
        // subject to the following terms and conditions, provided		      --	
        //									      --	
        // 1.  The above copyright notice and this permission notice must	      --	
        // appear in all copies of this description.				      --
        // 									      --
        // 2.  The Murphi group at Stanford University must be acknowledged	      --
        // in any publication describing work that makes use of this example. 	      --
        // 									      --	
        // Nobody vouches for the accuracy or usefulness of this description	      --
        // for any purpose.							      --
        //------------------------------------------------------------------------------
        //--------------------------------------------------------------------
        // Filename: 	sort5.m
        // Content:	sorting by random swaping
        // Version:	Murphi 2.3
        // Engineer:	Update to Murphi 2.3 by Ralph Melton, 1993.
        // Result:	The program violates invariant when the data is sorted
        //--------------------------------------------------------------------
        if ((v) == (m)) {
          (v) = ((int)(0));
        } else {
          (v) = ((v) + ((int)(1)));
        }
      } catch (...) { throw ::romp::ModelFunctError(0); }
}

    
    void Increment(::__type__::ind_t& v)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::IncrementMod((v), ((N) - ((int)(1))));
      } catch (...) { throw ::romp::ModelFunctError(1); }
}

    
    void Swap(::__type__::arr_t& a)  {
      using namespace ::__type__;
      try {
        ::__type__::val_t tmp;
        (tmp) = ((a).data[((i)) - int_VALUE_C(0)]);
        ((a).data[((i)) - int_VALUE_C(0)]) = ((a).data[((j)) - int_VALUE_C(0)]);
        ((a).data[((j)) - int_VALUE_C(0)]) = (tmp);
        (tmp) = ((int)(0));
      } catch (...) { throw ::romp::ModelFunctError(2); }
}


    /* ======= Murphi Model StartStates, Rules & Global Properties ====== */

     void __StartState__startstate0(void){
      using namespace ::__type__;
      try {
        memset(&(i), 0, sizeof((i)));
        memset(&(j), 0, sizeof((j)));
        do {
          for (int f = ((int)(0)); f <= ((N) - ((int)(1))); f++) {
            ((a).data[((f)) - int_VALUE_C(0)]) = (((N) - ((int)(1))) - (f));
          }
        } while (0);
      } catch (...) { throw ::romp::ModelStartStateError(0); }
    }



    
    bool __Rule_guard__i(void) const {
      using namespace ::__type__;
      try {
        return (true);
      } catch (...) { throw ::romp::ModelRuleError(0,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__i(void) {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::IncrementMod((i), ((N) - ((int)(1))));
      } catch (...) { throw ::romp::ModelRuleError(0,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__j(void) const {
      using namespace ::__type__;
      try {
        return (true);
      } catch (...) { throw ::romp::ModelRuleError(1,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__j(void) {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Increment((j));
      } catch (...) { throw ::romp::ModelRuleError(1,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__swap(void) const {
      using namespace ::__type__;
      try {
        return (((i) < (j)) && (((a).data[((i)) - int_VALUE_C(0)]) > ((a).data[((j)) - int_VALUE_C(0)])));
      } catch (...) { throw ::romp::ModelRuleError(2,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__swap(void) {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Swap((a));
      } catch (...) { throw ::romp::ModelRuleError(2,::romp::ModelRuleError::ACTION); }
    }


    
    bool __Property__property1(void) const {
      using namespace ::__type__;
      try {
        return this->__rw__->invariant_handler(({ bool res_0 = false; for (int i = ((int)(0)); i <= ((N) - ((int)(2))); i++) { res_0 |= (((a).data[((i)) - int_VALUE_C(0)]) > ((a).data[(((i) + ((int)(1)))) - int_VALUE_C(0)])); } res_0; }),0u);
      } catch (...) { throw ::romp::ModelPropertyError(0); }
    }


  };

  /* ======= Murphi Model Output Functions ====== */
#ifdef __ROMP__SIMPLE_TRACE
template<class O> const ::romp::stream_void& __Model___to_json(::romp::ojstream<O>& json, const __Model__& val) noexcept { using namespace ::__type__; json  << ind_t_to_json(json,val.i) << ',' << ind_t_to_json(json,val.j) << ',' << arr_t_to_json(json,val.a); return ::romp::S_VOID; }
#else
template<class O> const ::romp::stream_void& __Model___to_json(::romp::ojstream<O>& json, const __Model__& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"__Model__\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":" << ind_t_to_json(json,val.i) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"j\",\"value\":" << ind_t_to_json(json,val.j) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":" << arr_t_to_json(json,val.a)<< "}]}"; return ::romp::S_VOID;}
#endif
const ::romp::stream_void& __Model___to_str(::romp::ostream_p& out, const __Model__& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "i " << ((::romp::OPTIONS.report_show_type) ? ": ind_t =" : ":=") << ' ' << ind_t_to_str(out,val.i) << '\n' << out.indentation() << "j " << ((::romp::OPTIONS.report_show_type) ? ": ind_t =" : ":=") << ' ' << ind_t_to_str(out,val.j) << '\n' << out.indentation() << "a " << ((::romp::OPTIONS.report_show_type) ? ": arr_t =" : ":=") << ' ' << arr_t_to_str(out,val.a) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}
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
#define _ROMP_STATESPACE_COUNT_str "1679616"
/* the number of functions & procedures in the model */
#define _ROMP_FUNCTS_LEN (3ul)
  /* the info/metadata about the functions/procedures in the model */
  const ::romp::FunctInfo FUNCT_INFOS[_ROMP_FUNCTS_LEN] = {{"IncrementMod",{{45,1},{52,5}},"{\"$type\":\"procedure\",\"label\":\"IncrementMod\",\"params\":[{\"$type\":\"param\",\"id\":\"v\",\"type\":\"ind_t\"},{\"$type\":\"param\",\"id\":\"m\",\"type\":\"ind_t\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/sort5.m\",\"start\":[45,1],\"end\":[52,5]}}","procedure IncrementMod(v: ind_t; var m: ind_t);"},{"Increment",{{54,1},{57,5}},"{\"$type\":\"procedure\",\"label\":\"Increment\",\"params\":[{\"$type\":\"param\",\"id\":\"v\",\"type\":\"ind_t\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/sort5.m\",\"start\":[54,1],\"end\":[57,5]}}","procedure Increment(v: ind_t);"},{"Swap",{{59,1},{66,5}},"{\"$type\":\"procedure\",\"label\":\"Swap\",\"params\":[{\"$type\":\"param\",\"id\":\"a\",\"type\":\"arr_t\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/sort5.m\",\"start\":[59,1],\"end\":[66,5]}}","procedure Swap(a: arr_t);"},};
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
  const ::romp::PropertyInfo PROPERTY_INFOS[_ROMP_PROPERTIES_LEN] = {{"property1",::romp::PropertyType::INVARIANT,"exists i : 0..(N - 2) do (a[i] > a[(i + 1)]) endexists",0,{{100,1},{101,40}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"exists i : 0..(N - 2) do (a[i] > a[(i + 1)]) endexists\",\"label\":\"property1\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/sort5.m\",\"start\":[100,1],\"end\":[101,40]}"},};
/* the number of start state rules (before ruleset expansions) in the model */
#define _ROMP_STARTSTATE_INFO_LEN (1ul)
  /* the info/metadata about the startstate rules in the model */
  const ::romp::StartStateInfo STARTSTATE_INFOS[_ROMP_STARTSTATE_INFO_LEN] = {{"startstate0",{{91,1},{98,4}},"{\"$type\":\"startstate\",\"label\":\"startstate0\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/sort5.m\",\"start\":[91,1],\"end\":[98,4]}"},};
/* the number of rules in the model, BEFORE ruleset expansion */
#define _ROMP_RULESETS_LEN (3ul)
  /* the info/metadata about the rules in the model */
  const ::romp::RuleInfo RULE_SET_INFOS[_ROMP_RULESETS_LEN] = {{"i",{{69,1},{74,4}},"{\"$type\":\"rule\",\"expr\":\"true\",\"label\":\"i\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/sort5.m\",\"start\":[69,1],\"end\":[74,4]}"},{"j",{{76,1},{81,4}},"{\"$type\":\"rule\",\"expr\":\"true\",\"label\":\"j\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/sort5.m\",\"start\":[76,1],\"end\":[81,4]}"},{"swap",{{83,1},{88,4}},"{\"$type\":\"rule\",\"expr\":\"((i < j) & (a[i] > a[j]))\",\"label\":\"swap\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/sort5.m\",\"start\":[83,1],\"end\":[88,4]}"},};

}

/* ======= Romp CALLER Lists ====== */
namespace __caller__ {
  typedef ::__model__::__Model__ State_t; // type mask for the generated state object
  /* --- Rules Generated by: `i` (RuleSet expansions) --- */
   bool __Rule_guard__i__0(const State_t& s){return s.__Rule_guard__i(); }
   void __Rule_action__i__0(State_t& s){s.__Rule_action__i(); }
  /* --- Rules Generated by: `j` (RuleSet expansions) --- */
   bool __Rule_guard__j__0(const State_t& s){return s.__Rule_guard__j(); }
   void __Rule_action__j__0(State_t& s){s.__Rule_action__j(); }
  /* --- Rules Generated by: `swap` (RuleSet expansions) --- */
   bool __Rule_guard__swap__0(const State_t& s){return s.__Rule_guard__swap(); }
   void __Rule_action__swap__0(State_t& s){s.__Rule_action__swap(); }

/* the number of rules in the model, AFTER ruleset expansion */
#define _ROMP_RULE_COUNT (3ul)


  // All of the rule sets in one place
  const ::romp::RuleSet RULESETS[_ROMP_RULESETS_LEN] = {
		{::__info__::RULE_SET_INFOS[0],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__i__0,__Rule_action__i__0,::__info__::RULE_SET_INFOS[0],"[]",""}  	}},
		{::__info__::RULE_SET_INFOS[1],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__j__0,__Rule_action__j__0,::__info__::RULE_SET_INFOS[1],"[]",""}  	}},
		{::__info__::RULE_SET_INFOS[2],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__swap__0,__Rule_action__swap__0,::__info__::RULE_SET_INFOS[2],"[]",""}  	}}};

  /* --- Property Rule(s) generated by: `property1` (RuleSet expansions) --- */
   bool __Property__property1__0(const State_t& s) {return s.__Property__property1(); }

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
		{__Property__property1__0,::__info__::PROPERTY_INFOS[0],"[]",""},
};

  /* --- StartState Rule(s) generated by: `startstate0` (RuleSet expansions) --- */
   void __StartState__startstate0__0(State_t& s){ s.__StartState__startstate0(); }


#define _ROMP_STARTSTATES_LEN (1ul) // the number of property rules (after ruleset expansion) in the model

  // All of the rule sets in one place
const ::romp::StartState STARTSTATES[_ROMP_STARTSTATES_LEN] = {{__StartState__startstate0__0,::__info__::STARTSTATE_INFOS[0],0,"[]",""}};


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
