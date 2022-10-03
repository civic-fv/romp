/*
	Generated code for a romp "parallel random walker" verification tool based off of the Murphi Model described in:
		Original Murphi Model: german.m
	Please build with the following command(s):
		<not-implemented-yet>
*/


#define __romp__GENERATED_CODE


#define _ROMP_STATE_TYPE ::__model__::__Model__


#define _ROMP_STATE_HISTORY_LEN (4ul)


#define _ROMP_THREAD_TO_RW_RATIO (8ul)


#define __model__filepath "/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m"


#define __model__filepath_contains_space (true)


#define __model__filename "german.m"

#define __model__filename_contains_space (false)


#define __ROMP__SIMPLE_TRACE

#define __ROMP__DO_MEASURE

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
  const __typeof__(((int)(4))) NODE_NUM = ((int)(4));
  const __typeof__(((int)(2))) DATA_NUM = ((int)(2));
  typedef scalarset_t NODE;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& NODE_to_json(::romp::ojstream<O>& json, const NODE& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& NODE_to_json(::romp::ojstream<O>& json, const NODE& val) noexcept { json << "{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"bound\":4,\"value\":" << ((scalarset_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& NODE_to_str(::romp::ostream_p& out, const NODE& val) noexcept { out << ((scalarset_t)val); return ::romp::S_VOID;}

  typedef scalarset_t DATA;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& DATA_to_json(::romp::ojstream<O>& json, const DATA& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& DATA_to_json(::romp::ojstream<O>& json, const DATA& val) noexcept { json << "{\"$type\":\"scalarset-value\",\"type\":\"DATA\",\"bound\":2,\"value\":" << ((scalarset_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& DATA_to_str(::romp::ostream_p& out, const DATA& val) noexcept { out << ((scalarset_t)val); return ::romp::S_VOID;}

  typedef enum { I, S, E, } CACHE_STATE;
  std::string to_string(const CACHE_STATE val) { switch (val) { case I: return "I"; case S: return "S"; case E: return "E"; default: break; } return "CACHE_STATE::__UNKNOWN_ENUM_VALUE__"; }
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& CACHE_STATE_to_json(::romp::ojstream<O>& json, const CACHE_STATE& val) noexcept { json << '"' << to_string(val) << '"'; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& CACHE_STATE_to_json(::romp::ojstream<O>& json, const CACHE_STATE& val) noexcept { json << "{\"$type\":\"enum-value\",\"type\":\"CACHE_STATE\",\"value\":\"" << to_string(val) <<"\"}"; return ::romp::S_VOID; }
#endif
  const ::romp::stream_void& CACHE_STATE_to_str(::romp::ostream_p& out, const CACHE_STATE& val) noexcept { out << to_string(val); return ::romp::S_VOID; }

  typedef struct {
      // configuration parameters --
      // type decl --
      ::__type__::CACHE_STATE State;
      ::__type__::DATA Data;
    } CACHE;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& CACHE_to_json(::romp::ojstream<O>& json, const CACHE& val) noexcept { using namespace ::__type__; json  << CACHE_STATE_to_json(json,val.State) << ',' << DATA_to_json(json,val.Data); return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& CACHE_to_json(::romp::ojstream<O>& json, const CACHE& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"CACHE\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"State\",\"value\":" << CACHE_STATE_to_json(json,val.State) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Data\",\"value\":" << DATA_to_json(json,val.Data)<< "}]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& CACHE_to_str(::romp::ostream_p& out, const CACHE& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "State " << ((::romp::OPTIONS.result_show_type) ? ": CACHE_STATE =" : ":=") << ' ' << CACHE_STATE_to_str(out,val.State) << '\n' << out.indentation() << "Data " << ((::romp::OPTIONS.result_show_type) ? ": DATA =" : ":=") << ' ' << DATA_to_str(out,val.Data) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}

  typedef enum { Empty, ReqS, ReqE, Inv, InvAck, GntS, GntE, } MSG_CMD;
  std::string to_string(const MSG_CMD val) { switch (val) { case Empty: return "Empty"; case ReqS: return "ReqS"; case ReqE: return "ReqE"; case Inv: return "Inv"; case InvAck: return "InvAck"; case GntS: return "GntS"; case GntE: return "GntE"; default: break; } return "MSG_CMD::__UNKNOWN_ENUM_VALUE__"; }
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& MSG_CMD_to_json(::romp::ojstream<O>& json, const MSG_CMD& val) noexcept { json << '"' << to_string(val) << '"'; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& MSG_CMD_to_json(::romp::ojstream<O>& json, const MSG_CMD& val) noexcept { json << "{\"$type\":\"enum-value\",\"type\":\"MSG_CMD\",\"value\":\"" << to_string(val) <<"\"}"; return ::romp::S_VOID; }
#endif
  const ::romp::stream_void& MSG_CMD_to_str(::romp::ostream_p& out, const MSG_CMD& val) noexcept { out << to_string(val); return ::romp::S_VOID; }

  typedef struct {
      ::__type__::MSG_CMD Cmd;
      ::__type__::DATA Data;
    } MSG;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& MSG_to_json(::romp::ojstream<O>& json, const MSG& val) noexcept { using namespace ::__type__; json  << MSG_CMD_to_json(json,val.Cmd) << ',' << DATA_to_json(json,val.Data); return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& MSG_to_json(::romp::ojstream<O>& json, const MSG& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"MSG\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"Cmd\",\"value\":" << MSG_CMD_to_json(json,val.Cmd) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Data\",\"value\":" << DATA_to_json(json,val.Data)<< "}]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& MSG_to_str(::romp::ostream_p& out, const MSG& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "Cmd " << ((::romp::OPTIONS.result_show_type) ? ": MSG_CMD =" : ":=") << ' ' << MSG_CMD_to_str(out,val.Cmd) << '\n' << out.indentation() << "Data " << ((::romp::OPTIONS.result_show_type) ? ": DATA =" : ":=") << ' ' << DATA_to_str(out,val.Data) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}

  typedef struct { ::__type__::CACHE data[4]; size_t size() const {return (4ul);} } anon0x0_t; // Caches
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x0_t_to_json(::romp::ojstream<O>& json, const anon0x0_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << CACHE_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x0_t_to_json(::romp::ojstream<O>& json, const anon0x0_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[NODE] of CACHE\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(3) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << CACHE_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x0_t_to_str(::romp::ostream_p& out, const anon0x0_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< CACHE_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct { ::__type__::MSG data[4]; size_t size() const {return (4ul);} } anon0x1_t; // Channels for Req*
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x1_t_to_json(::romp::ojstream<O>& json, const anon0x1_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << MSG_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x1_t_to_json(::romp::ojstream<O>& json, const anon0x1_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[NODE] of MSG\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(3) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << MSG_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x1_t_to_str(::romp::ostream_p& out, const anon0x1_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< MSG_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct { ::__type__::MSG data[4]; size_t size() const {return (4ul);} } anon0x2_t; // Channels for Gnt* and Inv
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x2_t_to_json(::romp::ojstream<O>& json, const anon0x2_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << MSG_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x2_t_to_json(::romp::ojstream<O>& json, const anon0x2_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[NODE] of MSG\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(3) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << MSG_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x2_t_to_str(::romp::ostream_p& out, const anon0x2_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< MSG_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct { ::__type__::MSG data[4]; size_t size() const {return (4ul);} } anon0x3_t; // Channels for InvAck
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x3_t_to_json(::romp::ojstream<O>& json, const anon0x3_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << MSG_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x3_t_to_json(::romp::ojstream<O>& json, const anon0x3_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[NODE] of MSG\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(3) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << MSG_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x3_t_to_str(::romp::ostream_p& out, const anon0x3_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< MSG_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct { ::__type__::boolean data[4]; size_t size() const {return (4ul);} } anon0x4_t; // Nodes to be invalidated
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x4_t_to_json(::romp::ojstream<O>& json, const anon0x4_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << boolean_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x4_t_to_json(::romp::ojstream<O>& json, const anon0x4_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[NODE] of boolean\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(3) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << boolean_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x4_t_to_str(::romp::ostream_p& out, const anon0x4_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< boolean_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct { ::__type__::boolean data[4]; size_t size() const {return (4ul);} } anon0x5_t; // Nodes having S or E copies
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x5_t_to_json(::romp::ojstream<O>& json, const anon0x5_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << boolean_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x5_t_to_json(::romp::ojstream<O>& json, const anon0x5_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[NODE] of boolean\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(3) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << boolean_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x5_t_to_str(::romp::ostream_p& out, const anon0x5_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< boolean_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}


}



/* ======= Generated Model & State ====== */

namespace __model__ {

  struct __Model__ {
    ::romp::IRandWalker* __rw__; // reference to associated romp rand walker


    /* ======= Model State Variables ====== */

    ::__type__::anon0x0_t Cache;

    ::__type__::anon0x1_t Chan1;

    ::__type__::anon0x2_t Chan2;

    ::__type__::anon0x3_t Chan3;

    ::__type__::anon0x4_t InvSet;

    ::__type__::anon0x5_t ShrSet;

    ::__type__::boolean ExGntd; // E copy has been granted

    ::__type__::MSG_CMD CurCmd; // Current request command

    ::__type__::NODE CurPtr; // Current request node

    ::__type__::DATA MemData; // Memory data

    ::__type__::DATA AuxData; // Latest value of cache line


    /* ======= Murphi Model Functions ====== */


    /* ======= Murphi Model StartStates, Rules & Global Properties ====== */

     void __StartState__init(const ::__type__::DATA d){
      using namespace ::__type__;
      try {
        // state variables --
        // Initial States --
        //
        // All nodes: init all cmd channels to be empty, Cache States I, 
        // the set of nodes to be invalidated is empty
        // and nodes having S or E copies empty
        // 
        do {
          for (int i = 0; i < (NODE_NUM); i++) {
            (((Chan1).data[((i)) - int_VALUE_C(0)]).Cmd) = (Empty);
            (((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) = (Empty);
            (((Chan3).data[((i)) - int_VALUE_C(0)]).Cmd) = (Empty);
            (((Cache).data[((i)) - int_VALUE_C(0)]).State) = (I);
            ((InvSet).data[((i)) - int_VALUE_C(0)]) = (false);
            ((ShrSet).data[((i)) - int_VALUE_C(0)]) = (false);
          }
        } while (0);
        (ExGntd) = (false);
        (CurCmd) = (Empty);
        (MemData) = (d);
        (AuxData) = (d);
      } catch (...) { ::std::throw_with_nested( ::romp::ModelStartStateError(0) ); }
    }



    
    bool __Rule_guard__SendReqS(const ::__type__::NODE i) const {
      using namespace ::__type__;
      try {
        return (((((Chan1).data[((i)) - int_VALUE_C(0)]).Cmd) == (Empty)) && ((((Cache).data[((i)) - int_VALUE_C(0)]).State) == (I)));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(0,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__SendReqS(const ::__type__::NODE i) {
      using namespace ::__type__;
      try {
        // State Transitions --
        //------------------------------------------
        // Any node with cmd req channel empty and cache I can request ReqS
        (((Chan1).data[((i)) - int_VALUE_C(0)]).Cmd) = (ReqS); // raises "ReqS" semaphore
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(0,::romp::ModelRuleError::ACTION) ); }
    }

    
    bool __Rule_guard__SendReqE(const ::__type__::NODE i) const {
      using namespace ::__type__;
      try {
        return (((((Chan1).data[((i)) - int_VALUE_C(0)]).Cmd) == (Empty)) && (((((Cache).data[((i)) - int_VALUE_C(0)]).State) == (I)) || ((((Cache).data[((i)) - int_VALUE_C(0)]).State) == (S))));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(1,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__SendReqE(const ::__type__::NODE i) {
      using namespace ::__type__;
      try {
        //--------------------
        // Any node with cmd req channel empty and cache I/S can request ReqE
        (((Chan1).data[((i)) - int_VALUE_C(0)]).Cmd) = (ReqE); // raises "ReqE" semaphore
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(1,::romp::ModelRuleError::ACTION) ); }
    }

    
    bool __Rule_guard__RecvReqS(const ::__type__::NODE i) const {
      using namespace ::__type__;
      try {
        return (((CurCmd) == (Empty)) && ((((Chan1).data[((i)) - int_VALUE_C(0)]).Cmd) == (ReqS)));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(2,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__RecvReqS(const ::__type__::NODE i) {
      using namespace ::__type__;
      try {
        //------------------------------------------
        // For any node that is waiting with ReqS requested, with CurCmd Empty 
        // we set CurCmd to ReqS on behalf of node i (setting CurPtr to point to it).
        // Then void Chan1 empty.
        // Now Set the nodes to be invalidated to the nodes having S or E copies.
        // prep action of dir ctrlr
        (CurCmd) = (ReqS);
        (CurPtr) = (i); // who sent me ReqS
        (((Chan1).data[((i)) - int_VALUE_C(0)]).Cmd) = (Empty); // drain its cmd
        do {
          for (int j = 0; j < (NODE_NUM); j++) {
            ((InvSet).data[((j)) - int_VALUE_C(0)]) = ((ShrSet).data[((j)) - int_VALUE_C(0)]); // inv = nodes with S/E
          }
        } while (0);
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(2,::romp::ModelRuleError::ACTION) ); }
    }

    
    bool __Rule_guard__RecvReqE(const ::__type__::NODE i) const {
      using namespace ::__type__;
      try {
        return (((CurCmd) == (Empty)) && ((((Chan1).data[((i)) - int_VALUE_C(0)]).Cmd) == (ReqE)));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(3,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__RecvReqE(const ::__type__::NODE i) {
      using namespace ::__type__;
      try {
        //--------------------
        // For any node that is waiting with ReqE requested, with CurCmd Empty 
        // we set CurCmd to ReqE on behalf of node i (setting CurPtr to point to it).
        // Then void Chan1 empty.
        // Now Set the nodes to be invalidated to the nodes having S or E copies.
        (CurCmd) = (ReqE);
        (CurPtr) = (i); // who sent me ReqE
        (((Chan1).data[((i)) - int_VALUE_C(0)]).Cmd) = (Empty); // drain its cmd
        do {
          for (int j = 0; j < (NODE_NUM); j++) {
            ((InvSet).data[((j)) - int_VALUE_C(0)]) = ((ShrSet).data[((j)) - int_VALUE_C(0)]); // inv = nodes with S/E
          }
        } while (0);
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(3,::romp::ModelRuleError::ACTION) ); }
    }

    
    bool __Rule_guard__SendInv(const ::__type__::NODE i) const {
      using namespace ::__type__;
      try {
        return ((((((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) == (Empty)) && (((InvSet).data[((i)) - int_VALUE_C(0)]) == (true))) && (((CurCmd) == (ReqE)) || (((CurCmd) == (ReqS)) && ((ExGntd) == (true)))));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(4,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__SendInv(const ::__type__::NODE i) {
      using namespace ::__type__;
      try {
        //------------------------------------------
        // For every node with Chan2 Cmd empty and InvSet true (node to be invalidated)
        // and if CurCmd is ReqE or (ReqS with ExGnt true), then
        // void Chan2 Cmd to Inv, and remove node i from InvSet (invalidation already set out)
        // Gnt* and Inv channel
        // DC: curcmd = E
        // DC: curcmd = S & ExGntd
        (((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) = (Inv); // fill Chan2 with Inv
        ((InvSet).data[((i)) - int_VALUE_C(0)]) = (false);
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(4,::romp::ModelRuleError::ACTION) ); }
    }

    
    bool __Rule_guard__SendInvAck(const ::__type__::NODE i) const {
      using namespace ::__type__;
      try {
        return (((((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) == (Inv)) && ((((Chan3).data[((i)) - int_VALUE_C(0)]).Cmd) == (Empty)));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(5,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__SendInvAck(const ::__type__::NODE i) {
      using namespace ::__type__;
      try {
        //--------------------
        //
        // When a node gets invalidated, it acks, and when it was E
        // then the node (i) coughs up its cache data into Chan3
        // Then cache state is I and undefine Cache Data
        // 
        (((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) = (Empty);
        (((Chan3).data[((i)) - int_VALUE_C(0)]).Cmd) = (InvAck);
        if ((((Cache).data[((i)) - int_VALUE_C(0)]).State) == (E)) {
          (((Chan3).data[((i)) - int_VALUE_C(0)]).Data) = (((Cache).data[((i)) - int_VALUE_C(0)]).Data);
        }
        (((Cache).data[((i)) - int_VALUE_C(0)]).State) = (I);
        memset(&(((Cache).data[((i)) - int_VALUE_C(0)]).Data), 0, sizeof((((Cache).data[((i)) - int_VALUE_C(0)]).Data)));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(5,::romp::ModelRuleError::ACTION) ); }
    }

    
    bool __Rule_guard__RecvInvAck(const ::__type__::NODE i) const {
      using namespace ::__type__;
      try {
        return (((((Chan3).data[((i)) - int_VALUE_C(0)]).Cmd) == (InvAck)) && ((CurCmd) != (Empty)));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(6,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__RecvInvAck(const ::__type__::NODE i) {
      using namespace ::__type__;
      try {
        //--------------------
        (((Chan3).data[((i)) - int_VALUE_C(0)]).Cmd) = (Empty);
        ((ShrSet).data[((i)) - int_VALUE_C(0)]) = (false);
        if ((ExGntd) == (true)) {
          (ExGntd) = (false);
          (MemData) = (((Chan3).data[((i)) - int_VALUE_C(0)]).Data);
          memset(&(((Chan3).data[((i)) - int_VALUE_C(0)]).Data), 0, sizeof((((Chan3).data[((i)) - int_VALUE_C(0)]).Data)));
        }
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(6,::romp::ModelRuleError::ACTION) ); }
    }

    
    bool __Rule_guard__SendGntS(const ::__type__::NODE i) const {
      using namespace ::__type__;
      try {
        return (((((CurCmd) == (ReqS)) && ((CurPtr) == (i))) && ((((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) == (Empty))) && ((ExGntd) == (false)));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(7,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__SendGntS(const ::__type__::NODE i) {
      using namespace ::__type__;
      try {
        //------------------------------------------
        (((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) = (GntS);
        (((Chan2).data[((i)) - int_VALUE_C(0)]).Data) = (MemData);
        ((ShrSet).data[((i)) - int_VALUE_C(0)]) = (true);
        (CurCmd) = (Empty);
        memset(&(CurPtr), 0, sizeof((CurPtr)));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(7,::romp::ModelRuleError::ACTION) ); }
    }

    
    bool __Rule_guard__SendGntE(const ::__type__::NODE i) const {
      using namespace ::__type__;
      try {
        return ((((((CurCmd) == (ReqE)) && ((CurPtr) == (i))) && ((((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) == (Empty))) && ((ExGntd) == (false))) && ({ bool res_0 = true; for (int j = 0; j < (NODE_NUM); j++) { res_0&= (((ShrSet).data[((j)) - int_VALUE_C(0)]) == (false)); } res_0; }));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(8,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__SendGntE(const ::__type__::NODE i) {
      using namespace ::__type__;
      try {
        //--------------------
        // nodes having S or E status
        (((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) = (GntE);
        (((Chan2).data[((i)) - int_VALUE_C(0)]).Data) = (MemData);
        ((ShrSet).data[((i)) - int_VALUE_C(0)]) = (true);
        (ExGntd) = (true);
        (CurCmd) = (Empty);
        memset(&(CurPtr), 0, sizeof((CurPtr)));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(8,::romp::ModelRuleError::ACTION) ); }
    }

    
    bool __Rule_guard__RecvGntS(const ::__type__::NODE i) const {
      using namespace ::__type__;
      try {
        return ((((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) == (GntS));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(9,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__RecvGntS(const ::__type__::NODE i) {
      using namespace ::__type__;
      try {
        //--------------------
        (((Cache).data[((i)) - int_VALUE_C(0)]).State) = (S);
        (((Cache).data[((i)) - int_VALUE_C(0)]).Data) = (((Chan2).data[((i)) - int_VALUE_C(0)]).Data);
        (((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) = (Empty);
        memset(&(((Chan2).data[((i)) - int_VALUE_C(0)]).Data), 0, sizeof((((Chan2).data[((i)) - int_VALUE_C(0)]).Data)));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(9,::romp::ModelRuleError::ACTION) ); }
    }

    
    bool __Rule_guard__RecvGntE(const ::__type__::NODE i) const {
      using namespace ::__type__;
      try {
        return ((((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) == (GntE));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(10,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__RecvGntE(const ::__type__::NODE i) {
      using namespace ::__type__;
      try {
        //--------------------
        (((Cache).data[((i)) - int_VALUE_C(0)]).State) = (E);
        (((Cache).data[((i)) - int_VALUE_C(0)]).Data) = (((Chan2).data[((i)) - int_VALUE_C(0)]).Data);
        (((Chan2).data[((i)) - int_VALUE_C(0)]).Cmd) = (Empty);
        memset(&(((Chan2).data[((i)) - int_VALUE_C(0)]).Data), 0, sizeof((((Chan2).data[((i)) - int_VALUE_C(0)]).Data)));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(10,::romp::ModelRuleError::ACTION) ); }
    }

    
    bool __Rule_guard__Store(const ::__type__::NODE i, const ::__type__::DATA d) const {
      using namespace ::__type__;
      try {
        return ((((Cache).data[((i)) - int_VALUE_C(0)]).State) == (E));
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(11,::romp::ModelRuleError::GUARD) ); }
    }

    
    void __Rule_action__Store(const ::__type__::NODE i, const ::__type__::DATA d) {
      using namespace ::__type__;
      try {
        //--------------------
        // for every node i
        // for every data d
        // if node is in E
        (((Cache).data[((i)) - int_VALUE_C(0)]).Data) = (d); // store d into Cache[i].Data
        (AuxData) = (d); // Also update latest cache line value
      } catch (...) { ::std::throw_with_nested( ::romp::ModelRuleError(11,::romp::ModelRuleError::ACTION) ); }
    }


    
    bool __Property__CtrlProp(void) const {
      using namespace ::__type__;
      try {
        return this->__rw__->invariant_handler(({ bool res_1 = true; for (int i = 0; i < (NODE_NUM); i++) { res_1&= ({ bool res_2 = true; for (int j = 0; j < (NODE_NUM); j++) { res_2&= (!((i) != (j)) || ((!((((Cache).data[((i)) - int_VALUE_C(0)]).State) == (E)) || ((((Cache).data[((j)) - int_VALUE_C(0)]).State) == (I))) && (!((((Cache).data[((i)) - int_VALUE_C(0)]).State) == (S)) || (((((Cache).data[((j)) - int_VALUE_C(0)]).State) == (I)) || ((((Cache).data[((j)) - int_VALUE_C(0)]).State) == (S)))))); } res_2; }); } res_1; }),0u);
      } catch (...) { ::std::throw_with_nested( ::romp::ModelPropertyError(0) ); }
    }

    
    bool __Property__DataProp(void) const {
      using namespace ::__type__;
      try {
        return this->__rw__->invariant_handler(((!((ExGntd) == (false)) || ((MemData) == (AuxData))) && ({ bool res_3 = true; for (int i = 0; i < (NODE_NUM); i++) { res_3&= (!((((Cache).data[((i)) - int_VALUE_C(0)]).State) != (I)) || ((((Cache).data[((i)) - int_VALUE_C(0)]).Data) == (AuxData))); } res_3; })),1u);
      } catch (...) { ::std::throw_with_nested( ::romp::ModelPropertyError(1) ); }
    }


  };

  /* ======= Murphi Model Output Functions ====== */
#ifdef __ROMP__SIMPLE_TRACE
template<class O> const ::romp::stream_void& __Model___to_json(::romp::ojstream<O>& json, const __Model__& val) noexcept { using namespace ::__type__; json  << anon0x0_t_to_json(json,val.Cache) << ',' << anon0x1_t_to_json(json,val.Chan1) << ',' << anon0x2_t_to_json(json,val.Chan2) << ',' << anon0x3_t_to_json(json,val.Chan3) << ',' << anon0x4_t_to_json(json,val.InvSet) << ',' << anon0x5_t_to_json(json,val.ShrSet) << ',' << boolean_to_json(json,val.ExGntd) << ',' << MSG_CMD_to_json(json,val.CurCmd) << ',' << NODE_to_json(json,val.CurPtr) << ',' << DATA_to_json(json,val.MemData) << ',' << DATA_to_json(json,val.AuxData); return ::romp::S_VOID; }
#else
template<class O> const ::romp::stream_void& __Model___to_json(::romp::ojstream<O>& json, const __Model__& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"__Model__\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"Cache\",\"value\":" << anon0x0_t_to_json(json,val.Cache) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Chan1\",\"value\":" << anon0x1_t_to_json(json,val.Chan1) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Chan2\",\"value\":" << anon0x2_t_to_json(json,val.Chan2) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Chan3\",\"value\":" << anon0x3_t_to_json(json,val.Chan3) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"InvSet\",\"value\":" << anon0x4_t_to_json(json,val.InvSet) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"ShrSet\",\"value\":" << anon0x5_t_to_json(json,val.ShrSet) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"ExGntd\",\"value\":" << boolean_to_json(json,val.ExGntd) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"CurCmd\",\"value\":" << MSG_CMD_to_json(json,val.CurCmd) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"CurPtr\",\"value\":" << NODE_to_json(json,val.CurPtr) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"MemData\",\"value\":" << DATA_to_json(json,val.MemData) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"AuxData\",\"value\":" << DATA_to_json(json,val.AuxData)<< "}]}"; return ::romp::S_VOID;}
#endif
const ::romp::stream_void& __Model___to_str(::romp::ostream_p& out, const __Model__& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "Cache " << ((::romp::OPTIONS.result_show_type) ? ": Array[NODE] of CACHE =" : ":=") << ' ' << anon0x0_t_to_str(out,val.Cache) << '\n' << out.indentation() << "Chan1 " << ((::romp::OPTIONS.result_show_type) ? ": Array[NODE] of MSG =" : ":=") << ' ' << anon0x1_t_to_str(out,val.Chan1) << '\n' << out.indentation() << "Chan2 " << ((::romp::OPTIONS.result_show_type) ? ": Array[NODE] of MSG =" : ":=") << ' ' << anon0x2_t_to_str(out,val.Chan2) << '\n' << out.indentation() << "Chan3 " << ((::romp::OPTIONS.result_show_type) ? ": Array[NODE] of MSG =" : ":=") << ' ' << anon0x3_t_to_str(out,val.Chan3) << '\n' << out.indentation() << "InvSet " << ((::romp::OPTIONS.result_show_type) ? ": Array[NODE] of boolean =" : ":=") << ' ' << anon0x4_t_to_str(out,val.InvSet) << '\n' << out.indentation() << "ShrSet " << ((::romp::OPTIONS.result_show_type) ? ": Array[NODE] of boolean =" : ":=") << ' ' << anon0x5_t_to_str(out,val.ShrSet) << '\n' << out.indentation() << "ExGntd " << ((::romp::OPTIONS.result_show_type) ? ": __Model__ =" : ":=") << ' ' << boolean_to_str(out,val.ExGntd) << '\n' << out.indentation() << "CurCmd " << ((::romp::OPTIONS.result_show_type) ? ": MSG_CMD =" : ":=") << ' ' << MSG_CMD_to_str(out,val.CurCmd) << '\n' << out.indentation() << "CurPtr " << ((::romp::OPTIONS.result_show_type) ? ": NODE =" : ":=") << ' ' << NODE_to_str(out,val.CurPtr) << '\n' << out.indentation() << "MemData " << ((::romp::OPTIONS.result_show_type) ? ": DATA =" : ":=") << ' ' << DATA_to_str(out,val.MemData) << '\n' << out.indentation() << "AuxData " << ((::romp::OPTIONS.result_show_type) ? ": DATA =" : ":=") << ' ' << DATA_to_str(out,val.AuxData) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}
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
#define _ROMP_STATESPACE_COUNT_str "8011450590742230963602072335810560"
/* the number of functions & procedures in the model */
#define _ROMP_FUNCTS_LEN (0ul)
  /* the info/metadata about the functions/procedures in the model */
  const ::romp::FunctInfo FUNCT_INFOS[_ROMP_FUNCTS_LEN] = {};
/* the number of error statements in the model */
#define _ROMP_ERRORS_LEN (0ul)
  /* the info/metadata about the murphi error statements in the model */
  const ::romp::MErrorInfo ERROR_INFOS[_ROMP_ERRORS_LEN] = {};
/* the number of property statements & rules in the model */
#define _ROMP_PROPERTIES_LEN (2ul)
/* the number of cover property statements & rules in the model */
#define _ROMP_COVER_PROP_COUNT (0ul) // the number of property rules (after ruleset expansion) in the model
/* the number of liveness property rules in the model */
#define _ROMP_LIVENESS_PROP_COUNT (0ul) // the number of property rules (after ruleset expansion) in the model
  /* the info/metadata about the murphi properties in the model */
  const ::romp::PropertyInfo PROPERTY_INFOS[_ROMP_PROPERTIES_LEN] = {{"CtrlProp",::romp::PropertyType::INVARIANT,"forall i : NODE do forall j : NODE do ((i != j) -> (((Cache[i].State = E) -> (Cache[j].State = I)) & ((Cache[i].State = S) -> ((Cache[j].State = I) | (Cache[j].State = S))))) endforall endforall",0,{{235,1},{243,4}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall i : NODE do forall j : NODE do ((i != j) -> (((Cache[i].State = E) -> (Cache[j].State = I)) & ((Cache[i].State = S) -> ((Cache[j].State = I) | (Cache[j].State = S))))) endforall endforall\",\"label\":\"CtrlProp\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[235,1],\"end\":[243,4]}"},{"DataProp",::romp::PropertyType::INVARIANT,"(((ExGntd = false) -> (MemData = AuxData)) & forall i : NODE do ((Cache[i].State != I) -> (Cache[i].Data = AuxData)) endforall)",1,{{245,1},{250,5}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"(((ExGntd = false) -> (MemData = AuxData)) & forall i : NODE do ((Cache[i].State != I) -> (Cache[i].Data = AuxData)) endforall)\",\"label\":\"DataProp\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[245,1],\"end\":[250,5]}"},};
/* the number of start state rules (before ruleset expansions) in the model */
#define _ROMP_STARTSTATE_INFO_LEN (1ul)
  /* the info/metadata about the startstate rules in the model */
  const ::romp::StartStateInfo STARTSTATE_INFOS[_ROMP_STARTSTATE_INFO_LEN] = {{"init",{{34,21},{52,4}},"{\"$type\":\"startstate\",\"label\":\"init\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[34,21],\"end\":[52,4]}"},};
/* the number of rules in the model, BEFORE ruleset expansion */
#define _ROMP_RULESETS_LEN (12ul)
  /* the info/metadata about the rules in the model */
  const ::romp::RuleInfo RULE_SET_INFOS[_ROMP_RULESETS_LEN] = {{"SendReqS",{{59,3},{64,6}},"{\"$type\":\"rule\",\"expr\":\"((Chan1[i].Cmd = Empty) & (Cache[i].State = I))\",\"label\":\"SendReqS\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[59,3],\"end\":[64,6]}"},{"SendReqE",{{70,3},{76,6}},"{\"$type\":\"rule\",\"expr\":\"((Chan1[i].Cmd = Empty) & ((Cache[i].State = I) | (Cache[i].State = S)))\",\"label\":\"SendReqE\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[70,3],\"end\":[76,6]}"},{"RecvReqS",{{85,3},{93,6}},"{\"$type\":\"rule\",\"expr\":\"((CurCmd = Empty) & (Chan1[i].Cmd = ReqS))\",\"label\":\"RecvReqS\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[85,3],\"end\":[93,6]}"},{"RecvReqE",{{102,3},{110,6}},"{\"$type\":\"rule\",\"expr\":\"((CurCmd = Empty) & (Chan1[i].Cmd = ReqE))\",\"label\":\"RecvReqE\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[102,3],\"end\":[110,6]}"},{"SendInv",{{118,3},{126,6}},"{\"$type\":\"rule\",\"expr\":\"(((Chan2[i].Cmd = Empty) & (InvSet[i] = true)) & ((CurCmd = ReqE) | ((CurCmd = ReqS) & (ExGntd = true))))\",\"label\":\"SendInv\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[118,3],\"end\":[126,6]}"},{"SendInvAck",{{136,3},{144,6}},"{\"$type\":\"rule\",\"expr\":\"((Chan2[i].Cmd = Inv) & (Chan3[i].Cmd = Empty))\",\"label\":\"SendInvAck\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[136,3],\"end\":[144,6]}"},{"RecvInvAck",{{149,3},{158,6}},"{\"$type\":\"rule\",\"expr\":\"((Chan3[i].Cmd = InvAck) & (CurCmd != Empty))\",\"label\":\"RecvInvAck\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[149,3],\"end\":[158,6]}"},{"SendGntS",{{163,3},{174,6}},"{\"$type\":\"rule\",\"expr\":\"((((CurCmd = ReqS) & (CurPtr = i)) & (Chan2[i].Cmd = Empty)) & (ExGntd = false))\",\"label\":\"SendGntS\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[163,3],\"end\":[174,6]}"},{"SendGntE",{{179,3},{192,6}},"{\"$type\":\"rule\",\"expr\":\"(((((CurCmd = ReqE) & (CurPtr = i)) & (Chan2[i].Cmd = Empty)) & (ExGntd = false)) & forall j : NODE do (ShrSet[j] = false) endforall)\",\"label\":\"SendGntE\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[179,3],\"end\":[192,6]}"},{"RecvGntS",{{197,3},{204,6}},"{\"$type\":\"rule\",\"expr\":\"(Chan2[i].Cmd = GntS)\",\"label\":\"RecvGntS\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[197,3],\"end\":[204,6]}"},{"RecvGntE",{{209,3},{216,6}},"{\"$type\":\"rule\",\"expr\":\"(Chan2[i].Cmd = GntE)\",\"label\":\"RecvGntE\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[209,3],\"end\":[216,6]}"},{"Store",{{223,5},{228,8}},"{\"$type\":\"rule\",\"expr\":\"(Cache[i].State = E)\",\"label\":\"Store\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/german.m\",\"start\":[223,5],\"end\":[228,8]}"},};

}

/* ======= Romp CALLER Lists ====== */
namespace __caller__ {
  typedef ::__model__::__Model__ State_t; // type mask for the generated state object
  /* --- Rules Generated by: `SendReqS` (RuleSet expansions) --- */
   bool __Rule_guard__SendReqS__0(const State_t& s){return s.__Rule_guard__SendReqS((::__type__::NODE) 0); }
   void __Rule_action__SendReqS__0(State_t& s){s.__Rule_action__SendReqS((::__type__::NODE) 0); }
   bool __Rule_guard__SendReqS__1(const State_t& s){return s.__Rule_guard__SendReqS((::__type__::NODE) 1); }
   void __Rule_action__SendReqS__1(State_t& s){s.__Rule_action__SendReqS((::__type__::NODE) 1); }
   bool __Rule_guard__SendReqS__2(const State_t& s){return s.__Rule_guard__SendReqS((::__type__::NODE) 2); }
   void __Rule_action__SendReqS__2(State_t& s){s.__Rule_action__SendReqS((::__type__::NODE) 2); }
   bool __Rule_guard__SendReqS__3(const State_t& s){return s.__Rule_guard__SendReqS((::__type__::NODE) 3); }
   void __Rule_action__SendReqS__3(State_t& s){s.__Rule_action__SendReqS((::__type__::NODE) 3); }
  /* --- Rules Generated by: `SendReqE` (RuleSet expansions) --- */
   bool __Rule_guard__SendReqE__0(const State_t& s){return s.__Rule_guard__SendReqE((::__type__::NODE) 0); }
   void __Rule_action__SendReqE__0(State_t& s){s.__Rule_action__SendReqE((::__type__::NODE) 0); }
   bool __Rule_guard__SendReqE__1(const State_t& s){return s.__Rule_guard__SendReqE((::__type__::NODE) 1); }
   void __Rule_action__SendReqE__1(State_t& s){s.__Rule_action__SendReqE((::__type__::NODE) 1); }
   bool __Rule_guard__SendReqE__2(const State_t& s){return s.__Rule_guard__SendReqE((::__type__::NODE) 2); }
   void __Rule_action__SendReqE__2(State_t& s){s.__Rule_action__SendReqE((::__type__::NODE) 2); }
   bool __Rule_guard__SendReqE__3(const State_t& s){return s.__Rule_guard__SendReqE((::__type__::NODE) 3); }
   void __Rule_action__SendReqE__3(State_t& s){s.__Rule_action__SendReqE((::__type__::NODE) 3); }
  /* --- Rules Generated by: `RecvReqS` (RuleSet expansions) --- */
   bool __Rule_guard__RecvReqS__0(const State_t& s){return s.__Rule_guard__RecvReqS((::__type__::NODE) 0); }
   void __Rule_action__RecvReqS__0(State_t& s){s.__Rule_action__RecvReqS((::__type__::NODE) 0); }
   bool __Rule_guard__RecvReqS__1(const State_t& s){return s.__Rule_guard__RecvReqS((::__type__::NODE) 1); }
   void __Rule_action__RecvReqS__1(State_t& s){s.__Rule_action__RecvReqS((::__type__::NODE) 1); }
   bool __Rule_guard__RecvReqS__2(const State_t& s){return s.__Rule_guard__RecvReqS((::__type__::NODE) 2); }
   void __Rule_action__RecvReqS__2(State_t& s){s.__Rule_action__RecvReqS((::__type__::NODE) 2); }
   bool __Rule_guard__RecvReqS__3(const State_t& s){return s.__Rule_guard__RecvReqS((::__type__::NODE) 3); }
   void __Rule_action__RecvReqS__3(State_t& s){s.__Rule_action__RecvReqS((::__type__::NODE) 3); }
  /* --- Rules Generated by: `RecvReqE` (RuleSet expansions) --- */
   bool __Rule_guard__RecvReqE__0(const State_t& s){return s.__Rule_guard__RecvReqE((::__type__::NODE) 0); }
   void __Rule_action__RecvReqE__0(State_t& s){s.__Rule_action__RecvReqE((::__type__::NODE) 0); }
   bool __Rule_guard__RecvReqE__1(const State_t& s){return s.__Rule_guard__RecvReqE((::__type__::NODE) 1); }
   void __Rule_action__RecvReqE__1(State_t& s){s.__Rule_action__RecvReqE((::__type__::NODE) 1); }
   bool __Rule_guard__RecvReqE__2(const State_t& s){return s.__Rule_guard__RecvReqE((::__type__::NODE) 2); }
   void __Rule_action__RecvReqE__2(State_t& s){s.__Rule_action__RecvReqE((::__type__::NODE) 2); }
   bool __Rule_guard__RecvReqE__3(const State_t& s){return s.__Rule_guard__RecvReqE((::__type__::NODE) 3); }
   void __Rule_action__RecvReqE__3(State_t& s){s.__Rule_action__RecvReqE((::__type__::NODE) 3); }
  /* --- Rules Generated by: `SendInv` (RuleSet expansions) --- */
   bool __Rule_guard__SendInv__0(const State_t& s){return s.__Rule_guard__SendInv((::__type__::NODE) 0); }
   void __Rule_action__SendInv__0(State_t& s){s.__Rule_action__SendInv((::__type__::NODE) 0); }
   bool __Rule_guard__SendInv__1(const State_t& s){return s.__Rule_guard__SendInv((::__type__::NODE) 1); }
   void __Rule_action__SendInv__1(State_t& s){s.__Rule_action__SendInv((::__type__::NODE) 1); }
   bool __Rule_guard__SendInv__2(const State_t& s){return s.__Rule_guard__SendInv((::__type__::NODE) 2); }
   void __Rule_action__SendInv__2(State_t& s){s.__Rule_action__SendInv((::__type__::NODE) 2); }
   bool __Rule_guard__SendInv__3(const State_t& s){return s.__Rule_guard__SendInv((::__type__::NODE) 3); }
   void __Rule_action__SendInv__3(State_t& s){s.__Rule_action__SendInv((::__type__::NODE) 3); }
  /* --- Rules Generated by: `SendInvAck` (RuleSet expansions) --- */
   bool __Rule_guard__SendInvAck__0(const State_t& s){return s.__Rule_guard__SendInvAck((::__type__::NODE) 0); }
   void __Rule_action__SendInvAck__0(State_t& s){s.__Rule_action__SendInvAck((::__type__::NODE) 0); }
   bool __Rule_guard__SendInvAck__1(const State_t& s){return s.__Rule_guard__SendInvAck((::__type__::NODE) 1); }
   void __Rule_action__SendInvAck__1(State_t& s){s.__Rule_action__SendInvAck((::__type__::NODE) 1); }
   bool __Rule_guard__SendInvAck__2(const State_t& s){return s.__Rule_guard__SendInvAck((::__type__::NODE) 2); }
   void __Rule_action__SendInvAck__2(State_t& s){s.__Rule_action__SendInvAck((::__type__::NODE) 2); }
   bool __Rule_guard__SendInvAck__3(const State_t& s){return s.__Rule_guard__SendInvAck((::__type__::NODE) 3); }
   void __Rule_action__SendInvAck__3(State_t& s){s.__Rule_action__SendInvAck((::__type__::NODE) 3); }
  /* --- Rules Generated by: `RecvInvAck` (RuleSet expansions) --- */
   bool __Rule_guard__RecvInvAck__0(const State_t& s){return s.__Rule_guard__RecvInvAck((::__type__::NODE) 0); }
   void __Rule_action__RecvInvAck__0(State_t& s){s.__Rule_action__RecvInvAck((::__type__::NODE) 0); }
   bool __Rule_guard__RecvInvAck__1(const State_t& s){return s.__Rule_guard__RecvInvAck((::__type__::NODE) 1); }
   void __Rule_action__RecvInvAck__1(State_t& s){s.__Rule_action__RecvInvAck((::__type__::NODE) 1); }
   bool __Rule_guard__RecvInvAck__2(const State_t& s){return s.__Rule_guard__RecvInvAck((::__type__::NODE) 2); }
   void __Rule_action__RecvInvAck__2(State_t& s){s.__Rule_action__RecvInvAck((::__type__::NODE) 2); }
   bool __Rule_guard__RecvInvAck__3(const State_t& s){return s.__Rule_guard__RecvInvAck((::__type__::NODE) 3); }
   void __Rule_action__RecvInvAck__3(State_t& s){s.__Rule_action__RecvInvAck((::__type__::NODE) 3); }
  /* --- Rules Generated by: `SendGntS` (RuleSet expansions) --- */
   bool __Rule_guard__SendGntS__0(const State_t& s){return s.__Rule_guard__SendGntS((::__type__::NODE) 0); }
   void __Rule_action__SendGntS__0(State_t& s){s.__Rule_action__SendGntS((::__type__::NODE) 0); }
   bool __Rule_guard__SendGntS__1(const State_t& s){return s.__Rule_guard__SendGntS((::__type__::NODE) 1); }
   void __Rule_action__SendGntS__1(State_t& s){s.__Rule_action__SendGntS((::__type__::NODE) 1); }
   bool __Rule_guard__SendGntS__2(const State_t& s){return s.__Rule_guard__SendGntS((::__type__::NODE) 2); }
   void __Rule_action__SendGntS__2(State_t& s){s.__Rule_action__SendGntS((::__type__::NODE) 2); }
   bool __Rule_guard__SendGntS__3(const State_t& s){return s.__Rule_guard__SendGntS((::__type__::NODE) 3); }
   void __Rule_action__SendGntS__3(State_t& s){s.__Rule_action__SendGntS((::__type__::NODE) 3); }
  /* --- Rules Generated by: `SendGntE` (RuleSet expansions) --- */
   bool __Rule_guard__SendGntE__0(const State_t& s){return s.__Rule_guard__SendGntE((::__type__::NODE) 0); }
   void __Rule_action__SendGntE__0(State_t& s){s.__Rule_action__SendGntE((::__type__::NODE) 0); }
   bool __Rule_guard__SendGntE__1(const State_t& s){return s.__Rule_guard__SendGntE((::__type__::NODE) 1); }
   void __Rule_action__SendGntE__1(State_t& s){s.__Rule_action__SendGntE((::__type__::NODE) 1); }
   bool __Rule_guard__SendGntE__2(const State_t& s){return s.__Rule_guard__SendGntE((::__type__::NODE) 2); }
   void __Rule_action__SendGntE__2(State_t& s){s.__Rule_action__SendGntE((::__type__::NODE) 2); }
   bool __Rule_guard__SendGntE__3(const State_t& s){return s.__Rule_guard__SendGntE((::__type__::NODE) 3); }
   void __Rule_action__SendGntE__3(State_t& s){s.__Rule_action__SendGntE((::__type__::NODE) 3); }
  /* --- Rules Generated by: `RecvGntS` (RuleSet expansions) --- */
   bool __Rule_guard__RecvGntS__0(const State_t& s){return s.__Rule_guard__RecvGntS((::__type__::NODE) 0); }
   void __Rule_action__RecvGntS__0(State_t& s){s.__Rule_action__RecvGntS((::__type__::NODE) 0); }
   bool __Rule_guard__RecvGntS__1(const State_t& s){return s.__Rule_guard__RecvGntS((::__type__::NODE) 1); }
   void __Rule_action__RecvGntS__1(State_t& s){s.__Rule_action__RecvGntS((::__type__::NODE) 1); }
   bool __Rule_guard__RecvGntS__2(const State_t& s){return s.__Rule_guard__RecvGntS((::__type__::NODE) 2); }
   void __Rule_action__RecvGntS__2(State_t& s){s.__Rule_action__RecvGntS((::__type__::NODE) 2); }
   bool __Rule_guard__RecvGntS__3(const State_t& s){return s.__Rule_guard__RecvGntS((::__type__::NODE) 3); }
   void __Rule_action__RecvGntS__3(State_t& s){s.__Rule_action__RecvGntS((::__type__::NODE) 3); }
  /* --- Rules Generated by: `RecvGntE` (RuleSet expansions) --- */
   bool __Rule_guard__RecvGntE__0(const State_t& s){return s.__Rule_guard__RecvGntE((::__type__::NODE) 0); }
   void __Rule_action__RecvGntE__0(State_t& s){s.__Rule_action__RecvGntE((::__type__::NODE) 0); }
   bool __Rule_guard__RecvGntE__1(const State_t& s){return s.__Rule_guard__RecvGntE((::__type__::NODE) 1); }
   void __Rule_action__RecvGntE__1(State_t& s){s.__Rule_action__RecvGntE((::__type__::NODE) 1); }
   bool __Rule_guard__RecvGntE__2(const State_t& s){return s.__Rule_guard__RecvGntE((::__type__::NODE) 2); }
   void __Rule_action__RecvGntE__2(State_t& s){s.__Rule_action__RecvGntE((::__type__::NODE) 2); }
   bool __Rule_guard__RecvGntE__3(const State_t& s){return s.__Rule_guard__RecvGntE((::__type__::NODE) 3); }
   void __Rule_action__RecvGntE__3(State_t& s){s.__Rule_action__RecvGntE((::__type__::NODE) 3); }
  /* --- Rules Generated by: `Store` (RuleSet expansions) --- */
   bool __Rule_guard__Store__0(const State_t& s){return s.__Rule_guard__Store((::__type__::NODE) 0, (::__type__::DATA) 0); }
   void __Rule_action__Store__0(State_t& s){s.__Rule_action__Store((::__type__::NODE) 0, (::__type__::DATA) 0); }
   bool __Rule_guard__Store__1(const State_t& s){return s.__Rule_guard__Store((::__type__::NODE) 0, (::__type__::DATA) 1); }
   void __Rule_action__Store__1(State_t& s){s.__Rule_action__Store((::__type__::NODE) 0, (::__type__::DATA) 1); }
   bool __Rule_guard__Store__2(const State_t& s){return s.__Rule_guard__Store((::__type__::NODE) 1, (::__type__::DATA) 0); }
   void __Rule_action__Store__2(State_t& s){s.__Rule_action__Store((::__type__::NODE) 1, (::__type__::DATA) 0); }
   bool __Rule_guard__Store__3(const State_t& s){return s.__Rule_guard__Store((::__type__::NODE) 1, (::__type__::DATA) 1); }
   void __Rule_action__Store__3(State_t& s){s.__Rule_action__Store((::__type__::NODE) 1, (::__type__::DATA) 1); }
   bool __Rule_guard__Store__4(const State_t& s){return s.__Rule_guard__Store((::__type__::NODE) 2, (::__type__::DATA) 0); }
   void __Rule_action__Store__4(State_t& s){s.__Rule_action__Store((::__type__::NODE) 2, (::__type__::DATA) 0); }
   bool __Rule_guard__Store__5(const State_t& s){return s.__Rule_guard__Store((::__type__::NODE) 2, (::__type__::DATA) 1); }
   void __Rule_action__Store__5(State_t& s){s.__Rule_action__Store((::__type__::NODE) 2, (::__type__::DATA) 1); }
   bool __Rule_guard__Store__6(const State_t& s){return s.__Rule_guard__Store((::__type__::NODE) 3, (::__type__::DATA) 0); }
   void __Rule_action__Store__6(State_t& s){s.__Rule_action__Store((::__type__::NODE) 3, (::__type__::DATA) 0); }
   bool __Rule_guard__Store__7(const State_t& s){return s.__Rule_guard__Store((::__type__::NODE) 3, (::__type__::DATA) 1); }
   void __Rule_action__Store__7(State_t& s){s.__Rule_action__Store((::__type__::NODE) 3, (::__type__::DATA) 1); }

/* the number of rules in the model, AFTER ruleset expansion */
#define _ROMP_RULE_COUNT (52ul)


  // All of the rule sets in one place
  const ::romp::RuleSet RULESETS[_ROMP_RULESETS_LEN] = {
		{::__info__::RULE_SET_INFOS[0],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__SendReqS__0,__Rule_action__SendReqS__0,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}}]","i:=0"}, ::romp::Rule{__Rule_guard__SendReqS__1,__Rule_action__SendReqS__1,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}}]","i:=1"}, ::romp::Rule{__Rule_guard__SendReqS__2,__Rule_action__SendReqS__2,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}}]","i:=2"}, ::romp::Rule{__Rule_guard__SendReqS__3,__Rule_action__SendReqS__3,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}}]","i:=3"}  	}},
		{::__info__::RULE_SET_INFOS[1],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__SendReqE__0,__Rule_action__SendReqE__0,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}}]","i:=0"}, ::romp::Rule{__Rule_guard__SendReqE__1,__Rule_action__SendReqE__1,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}}]","i:=1"}, ::romp::Rule{__Rule_guard__SendReqE__2,__Rule_action__SendReqE__2,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}}]","i:=2"}, ::romp::Rule{__Rule_guard__SendReqE__3,__Rule_action__SendReqE__3,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}}]","i:=3"}  	}},
		{::__info__::RULE_SET_INFOS[2],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__RecvReqS__0,__Rule_action__RecvReqS__0,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}}]","i:=0"}, ::romp::Rule{__Rule_guard__RecvReqS__1,__Rule_action__RecvReqS__1,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}}]","i:=1"}, ::romp::Rule{__Rule_guard__RecvReqS__2,__Rule_action__RecvReqS__2,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}}]","i:=2"}, ::romp::Rule{__Rule_guard__RecvReqS__3,__Rule_action__RecvReqS__3,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}}]","i:=3"}  	}},
		{::__info__::RULE_SET_INFOS[3],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__RecvReqE__0,__Rule_action__RecvReqE__0,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}}]","i:=0"}, ::romp::Rule{__Rule_guard__RecvReqE__1,__Rule_action__RecvReqE__1,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}}]","i:=1"}, ::romp::Rule{__Rule_guard__RecvReqE__2,__Rule_action__RecvReqE__2,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}}]","i:=2"}, ::romp::Rule{__Rule_guard__RecvReqE__3,__Rule_action__RecvReqE__3,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}}]","i:=3"}  	}},
		{::__info__::RULE_SET_INFOS[4],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__SendInv__0,__Rule_action__SendInv__0,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}}]","i:=0"}, ::romp::Rule{__Rule_guard__SendInv__1,__Rule_action__SendInv__1,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}}]","i:=1"}, ::romp::Rule{__Rule_guard__SendInv__2,__Rule_action__SendInv__2,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}}]","i:=2"}, ::romp::Rule{__Rule_guard__SendInv__3,__Rule_action__SendInv__3,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}}]","i:=3"}  	}},
		{::__info__::RULE_SET_INFOS[5],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__SendInvAck__0,__Rule_action__SendInvAck__0,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}}]","i:=0"}, ::romp::Rule{__Rule_guard__SendInvAck__1,__Rule_action__SendInvAck__1,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}}]","i:=1"}, ::romp::Rule{__Rule_guard__SendInvAck__2,__Rule_action__SendInvAck__2,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}}]","i:=2"}, ::romp::Rule{__Rule_guard__SendInvAck__3,__Rule_action__SendInvAck__3,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}}]","i:=3"}  	}},
		{::__info__::RULE_SET_INFOS[6],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__RecvInvAck__0,__Rule_action__RecvInvAck__0,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}}]","i:=0"}, ::romp::Rule{__Rule_guard__RecvInvAck__1,__Rule_action__RecvInvAck__1,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}}]","i:=1"}, ::romp::Rule{__Rule_guard__RecvInvAck__2,__Rule_action__RecvInvAck__2,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}}]","i:=2"}, ::romp::Rule{__Rule_guard__RecvInvAck__3,__Rule_action__RecvInvAck__3,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}}]","i:=3"}  	}},
		{::__info__::RULE_SET_INFOS[7],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__SendGntS__0,__Rule_action__SendGntS__0,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}}]","i:=0"}, ::romp::Rule{__Rule_guard__SendGntS__1,__Rule_action__SendGntS__1,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}}]","i:=1"}, ::romp::Rule{__Rule_guard__SendGntS__2,__Rule_action__SendGntS__2,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}}]","i:=2"}, ::romp::Rule{__Rule_guard__SendGntS__3,__Rule_action__SendGntS__3,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}}]","i:=3"}  	}},
		{::__info__::RULE_SET_INFOS[8],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__SendGntE__0,__Rule_action__SendGntE__0,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}}]","i:=0"}, ::romp::Rule{__Rule_guard__SendGntE__1,__Rule_action__SendGntE__1,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}}]","i:=1"}, ::romp::Rule{__Rule_guard__SendGntE__2,__Rule_action__SendGntE__2,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}}]","i:=2"}, ::romp::Rule{__Rule_guard__SendGntE__3,__Rule_action__SendGntE__3,::__info__::RULE_SET_INFOS[8],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}}]","i:=3"}  	}},
		{::__info__::RULE_SET_INFOS[9],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__RecvGntS__0,__Rule_action__RecvGntS__0,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}}]","i:=0"}, ::romp::Rule{__Rule_guard__RecvGntS__1,__Rule_action__RecvGntS__1,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}}]","i:=1"}, ::romp::Rule{__Rule_guard__RecvGntS__2,__Rule_action__RecvGntS__2,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}}]","i:=2"}, ::romp::Rule{__Rule_guard__RecvGntS__3,__Rule_action__RecvGntS__3,::__info__::RULE_SET_INFOS[9],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}}]","i:=3"}  	}},
		{::__info__::RULE_SET_INFOS[10],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__RecvGntE__0,__Rule_action__RecvGntE__0,::__info__::RULE_SET_INFOS[10],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}}]","i:=0"}, ::romp::Rule{__Rule_guard__RecvGntE__1,__Rule_action__RecvGntE__1,::__info__::RULE_SET_INFOS[10],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}}]","i:=1"}, ::romp::Rule{__Rule_guard__RecvGntE__2,__Rule_action__RecvGntE__2,::__info__::RULE_SET_INFOS[10],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}}]","i:=2"}, ::romp::Rule{__Rule_guard__RecvGntE__3,__Rule_action__RecvGntE__3,::__info__::RULE_SET_INFOS[10],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}}]","i:=3"}  	}},
		{::__info__::RULE_SET_INFOS[11],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__Store__0,__Rule_action__Store__0,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"DATA\",\"value\":0}}]","i:=0; d:=0"}, ::romp::Rule{__Rule_guard__Store__1,__Rule_action__Store__1,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"DATA\",\"value\":1}}]","i:=0; d:=1"}, ::romp::Rule{__Rule_guard__Store__2,__Rule_action__Store__2,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}},{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"DATA\",\"value\":0}}]","i:=1; d:=0"}, ::romp::Rule{__Rule_guard__Store__3,__Rule_action__Store__3,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":1}},{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"DATA\",\"value\":1}}]","i:=1; d:=1"}, ::romp::Rule{__Rule_guard__Store__4,__Rule_action__Store__4,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}},{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"DATA\",\"value\":0}}]","i:=2; d:=0"}, ::romp::Rule{__Rule_guard__Store__5,__Rule_action__Store__5,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":2}},{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"DATA\",\"value\":1}}]","i:=2; d:=1"}, ::romp::Rule{__Rule_guard__Store__6,__Rule_action__Store__6,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}},{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"DATA\",\"value\":0}}]","i:=3; d:=0"}, ::romp::Rule{__Rule_guard__Store__7,__Rule_action__Store__7,::__info__::RULE_SET_INFOS[11],"[{\"$type\":\"kv-pair\",\"key\":\"i\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"NODE\",\"value\":3}},{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"DATA\",\"value\":1}}]","i:=3; d:=1"}  	}}};

  /* --- Property Rule(s) generated by: `CtrlProp` (RuleSet expansions) --- */
   bool __Property__CtrlProp__0(const State_t& s) {return s.__Property__CtrlProp(); }
  /* --- Property Rule(s) generated by: `DataProp` (RuleSet expansions) --- */
   bool __Property__DataProp__0(const State_t& s) {return s.__Property__DataProp(); }

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
#define _ROMP_PROPERTY_RULES_LEN ((2ul) + ___propRule_assume_count___ + ___propRule_cover_count___ + ___propRule_liveness_count___)

  /* All of the property rules expanded in one place */
const ::romp::Property PROPERTIES[_ROMP_PROPERTY_RULES_LEN] = {
		{__Property__CtrlProp__0,::__info__::PROPERTY_INFOS[0],"[]",""},
		{__Property__DataProp__0,::__info__::PROPERTY_INFOS[1],"[]",""},
};

  /* --- StartState Rule(s) generated by: `init` (RuleSet expansions) --- */
   void __StartState__init__0(State_t& s){ s.__StartState__init((::__type__::DATA) 0); }
   void __StartState__init__1(State_t& s){ s.__StartState__init((::__type__::DATA) 1); }


#define _ROMP_STARTSTATES_LEN (2ul) // the number of property rules (after ruleset expansion) in the model

  // All of the rule sets in one place
const ::romp::StartState STARTSTATES[_ROMP_STARTSTATES_LEN] = {{__StartState__init__0,::__info__::STARTSTATE_INFOS[0],0,"[{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"DATA\",\"value\":0}}]","d:=0"}, {__StartState__init__1,::__info__::STARTSTATE_INFOS[0],1,"[{\"$type\":\"kv-pair\",\"key\":\"d\",\"value\":{\"$type\":\"scalarset-value\",\"type\":\"DATA\",\"value\":1}}]","d:=1"}};


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
