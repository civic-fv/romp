/*
	Generated code for a romp "parallel random walker" verification tool based off of the Murphi Model described in:
		Original Murphi Model: cache3.m
	Please build with the following command(s):
		<not-implemented-yet>
*/


#define __romp__GENERATED_CODE


#define _ROMP_STATE_TYPE ::__model__::__Model__


#define _ROMP_STATE_HISTORY_LEN (4ul)


#define _ROMP_THREAD_TO_RW_RATIO (8ul)


#define __model__filepath "/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m"


#define __model__filepath_contains_space (true)


#define __model__filename "cache3.m"

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

/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file c_prefix.cpp
 * 
 * @brief The header for romp generated C code (prefixes the generated code)
 * 
 * @date 2022/07/06
 * @version 0.1
 */

// #include <assert.h>
// #include <stdbool.h>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <iomanip>
// #include <stdlib.h>
#include <string>
#include <string.h>  // required for memset
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
#include <queue>
#include <memory>
#include <utility>
#include <functional>
#include <type_traits>
#include <thread>
#include <unordered_map>
#include <chrono>
#include <ctime>



// << =============================== Preprocessor Declarations ================================ >>

#ifndef __romp__GENERATED_CODE
#include "romp-rw_pregen-fix.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
// #include "romp-json.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
#endif


#define _ROMP_TRACE_JSON_VERSION "0.0.3"
#ifdef DEBUG
#define _ROMP_FLUSH_FREQ (32ul)
#else
#define _ROMP_FLUSH_FREQ (64ul)
#endif

#ifdef __clang__
using nullptr_t=std::nullptr_t;
#endif

// various printf wrappers to deal with the user having passed --value-type
// static __attribute__((unused)) void print_int     (int v)      { printf("%d",          v); }
// static __attribute__((unused)) void print_unsigned(unsigned v) { printf("%u",          v); }
// static __attribute__((unused)) void print_short   (short v)    { printf("%hd",         v); }
// static __attribute__((unused)) void print_long    (long v)     { printf("%ld",         v); }
// static __attribute__((unused)) void print_int8_t  (int8_t v)   { printf("%" PRId8 , v); }
// static __attribute__((unused)) void print_uint8_t (uint8_t v)  { printf("%" PRIu8 , v); }
// static __attribute__((unused)) void print_int16_t (int16_t v)  { printf("%" PRId16, v); }
// static __attribute__((unused)) void print_uint16_t(uint16_t v) { printf("%" PRIu16, v); }
// static __attribute__((unused)) void print_int32_t (int32_t v)  { printf("%" PRId32, v); }
// static __attribute__((unused)) void print_uint32_t(uint32_t v) { printf("%" PRIu32, v); }
// static __attribute__((unused)) void print_int64_t (int64_t v)  { printf("%" PRId64, v); }
// static __attribute__((unused)) void print_uint64_t(uint64_t v) { printf("%" PRIu64, v); }

// wrappers for producing literal expressions of value type
#define int_VALUE_C(v)      (v)
#define unsigned_VALUE_C(v) (v ## u)
#define short_VALUE_C(v)    ((short)(v))
#define long_VALUE_C(v)     (v ## l)
#define int8_t_VALUE_C(v)   INT8_C(v)
#define uint8_t_VALUE_C(v)  UINT8_C(v)
#define int16_t_VALUE_C(v)  INT16_C(v)
#define uint16_t_VALUE_C(v) UINT16_C(v)
#define int32_t_VALUE_C(v)  INT32_C(v)
#define uint32_t_VALUE_C(v) UINT32_C(v)
#define int64_t_VALUE_C(v)  INT64_C(v)
#define uint64_t_VALUE_C(v) UINT64_C(v)
#define VALUE_C(v) int_VALUE_C((v))


namespace romp {
  struct RuleInfo; struct PropertyInfo; struct StartStateInfo; struct MErrorInfo; struct FunctInfo;
  struct RuleSet; struct StartState; struct Property;
  class stream_void { nullptr_t none = nullptr; };
  const stream_void S_VOID;
  std::ostream& operator << (std::ostream& out, const stream_void& val) { return out; }
  class ostream_p;
  template <class O> class ojstream;
}

namespace __caller__ {
  extern const ::romp::RuleSet RULESETS[];
  extern const ::romp::StartState STARTSTATES[];
  extern const ::romp::Property PROPERTIES[];
}

namespace __info__ { // LANGUAGE SERVER SUPPORT ONLY!!
  extern const ::romp::RuleInfo RULE_SET_INFOS[];
  extern const ::romp::PropertyInfo PROPERTY_INFOS[]; 
  extern const ::romp::StartStateInfo STARTSTATE_INFOS[]; 
  extern const ::romp::MErrorInfo ERROR_INFOS[]; 
  extern const ::romp::FunctInfo FUNCT_INFOS[]; 
}

namespace romp {

  const std::string EMPTY_STR = "";
  const time_t ROMP_ID = std::time(nullptr);
  const auto INIT_TIME = *std::localtime(&ROMP_ID);
  const auto INIT_TIME_STAMP = std::put_time(&INIT_TIME, "%F_%T");
  namespace options {

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
      bool result_show_type = false;
      bool result_emit_state = true;
      unsigned int tab_size = 2;
      char tab_char = ' ';
      void parse_args(int, char **);
      const stream_void write_config(ostream_p& out) const noexcept;
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
    };
  }
  options::Options OPTIONS;

  template<class O>
  ojstream<O>& operator << (ojstream<O>& json, const options::Options& opts) noexcept;
  
  typedef _ROMP_STATE_TYPE State_t;

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

  struct IModelError;
  template <class O> struct ojstream;
  template<class O> void __jprint_exception(ojstream<O>& json, const std::exception& ex) noexcept;
  template<class O> void __jprint_exception(ojstream<O>& json, const IModelError& ex) noexcept;

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

  class ostream_p {
    unsigned int _width;
    std::string _indentation;
  public:
    std::ostream& out;
    ostream_p(std::ostream& out_, unsigned int level_=0) 
        : out(out_), _width(level_*OPTIONS.tab_size) 
      { _indentation = std::string(_width,OPTIONS.tab_char); }
    inline int width() { return _width; }
    inline const stream_void indent() { _indentation = std::string((_width+=OPTIONS.tab_size),OPTIONS.tab_char); return S_VOID; }
    inline const std::string _indent() { indent(); return indentation(); }
    inline const stream_void dedent() { _indentation = std::string((_width-=OPTIONS.tab_size),OPTIONS.tab_char); return S_VOID; }
    inline const std::string _dedent() { dedent(); return indentation(); }
    inline const std::string indentation() { return _indentation; }
    inline const stream_void new_line() { out << '\n' << indentation(); return S_VOID; }
    inline const stream_void nl() { return new_line(); }
    template <typename T>
    inline ostream_p& operator << (const T val);  
  };
  template <typename T>
  inline ostream_p& ostream_p::operator << (const T val) { out << val; return *this; }  
  // template <>
  // inline ostream_p& ostream_p::operator << <std::_Setw>(const std::_Setw val) { _width = val._M_n; return *this; } 
  template <>
  inline ostream_p& ostream_p::operator << <stream_void>(const stream_void val) { return *this; }
  template <>
  inline ostream_p& ostream_p::operator << <bool>(const bool val) { return (*this << ((val) ? "YES" : "NO")); }
  inline std::ostream& operator << (std::ostream& out, const options::Options& opts) {
    ostream_p _out(out,0); opts.write_config(_out); return out;
  }
  ostream_p& operator << (ostream_p& out, const options::Options& opts) noexcept { opts.write_config(out); return out; }

  template<typename T, class R> 
  const std::string _pre0(const std::chrono::duration<T,R> dur) { return ((dur.count()<10) ? "0" : ""); }
  template<typename T, class R>
  ostream_p& operator << (ostream_p& out, const std::chrono::duration<T,R> _dur) noexcept {
    using namespace std::chrono;
    using day_t = duration<T, std::ratio<3600 * 24>>;
    enum TimeUnit {_ms,_s,_min,_hr,_d};
    std::chrono::duration<T,R> dur(_dur);
    day_t d(0);
    hours h(0);
    minutes m(0);
    seconds s(0);
    milliseconds ms(0);
    TimeUnit msu = _ms;
    if (dur > day_t(3)) {
      d = duration_cast<day_t>(dur);
      dur -= d; msu = _d;
    }
    if (msu > _ms || dur > hours(3)) {
      h = duration_cast<hours>(dur);
      dur -= h; msu = ((msu > _hr) ? msu : _hr);
    }
    if (msu > _ms || dur > minutes(3)) {
      m = duration_cast<minutes>(dur);
      dur -= m; msu = ((msu > _min) ? msu : _min);
    }
    if (msu > _ms || dur >= seconds(10)) {
      s = duration_cast<seconds>(dur);
      dur -= m; msu = ((msu > _s) ? msu : _s);
    }
    ms = duration_cast<milliseconds>(dur);
    
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
        return (out << ms.count() << "ms");
      default:
        return (out << "<ERROR_PARSING_DURATION>");
    }
    return out;
  }

  // template<> char* json_str_t::str() { return out.str(); }

  struct file_position {
    size_t row;
    size_t col;
  };
  template<class O>
  ojstream<O>& operator << (ojstream<O>& json, const file_position& fp) { 
    return (json << '[' << fp.row << ',' << fp.col << ']'); 
  }
  std::ostream& operator << (std::ostream& out, const file_position& fp) { return (out << fp.row << ',' << fp.col); }

  struct location {
    // std::string model_obj;
    file_position start;
    file_position end;
  };
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

  struct IModelError :  /* public std::logic_error, */ public std::nested_exception {
    IModelError() 
      : std::nested_exception() 
        // ,std::logic_error("IModelError :: THIS SHOULD NEVER BE SEEN") 
    {}
    // const char* what() const noexcept {
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
    // if (ex_level++ == 0) out << "],\"error-trace\":["
    me.to_json(*this);
    if (me.nested_ptr() != nullptr)
      __jprint_exception(*this,me);
    // if (--ex_level == 0) out << ']';
    return *this; 
  }

  // struct IInfo {
  //   virtual void to_json(json_file_t& json) { this->to_json(json.out); }
  //   virtual void to_json(json_str_t& json) { this->to_json(json.out); }
  //   virtual void to_string(std::ostream& out) = 0;
  // protected:
  //   virtual void to_json(std::ostream& json) = 0;
  // };

  typedef enum { INVARIANT, ASSERTION, ASSUMPTION, COVER, LIVENESS } PropertyType;
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

  std::ostream& operator << (std::ostream& out, const PropertyInfo& pi) noexcept { return (out << pi.type << " \"" << pi.label << "\" " /* << pi.expr */ << " @(" << pi.loc << ")"); }
  template<class O> ojstream<O>& operator << (ojstream<O>& json, const PropertyInfo& pi) noexcept {
// #ifdef __ROMP__SIMPLE_TRACE
//     json.out << "\"" << pi.type << " \\\"" << pi.label << "\\\" " << pi.expr << " @(" << pi.loc << ")\"";
// #else
    json << pi.json_h << '}';
// #endif
    return json;
  }

   struct Property {
    bool (*check)(const State_t&) ;
    const PropertyInfo& info;
    const std::string quant_json;
    const std::string quant_str;
    IModelError* make_error() const;
  };

  std::ostream& operator << (std::ostream& out, const Property& p) noexcept { 
    out << p.info.type << " \"" << p.info.label << "\" ";
    if (p.quant_str.size() > 0)
      out << " Quantifiers(" << p.quant_str << ") ";
    return (out << "@(" << p.info.loc << ')'); 
  }
  template<class O> ojstream<O>& operator << (ojstream<O>& json, const Property& p) noexcept {
// #ifdef __ROMP__SIMPLE_TRACE
//     json.out << '"' << p.info.type << " \\\"" << p.info.label << "\\\" ";
//     if (p.quant_str.size() > 0)
//       json.out << " Quantifiers(" << p.quant_str << ") ";
//     // json.out << "@(" << p.info.loc << "(\"";
//     json.out << '"';
// #else
    json << p.info.json_h << ",\"quantifiers\":" << p.quant_json << '}';
// #endif
    return json;
  }

  struct ModelPropertyError : public IModelError {
    ModelPropertyError(const Property& prop_) : isProp(true) { data.prop = &prop_; }
    ModelPropertyError(const PropertyInfo& info_) : isProp(false) { data.info = &info_; }
    ModelPropertyError(id_t id) : isProp(false) { data.info = &(::__info__::PROPERTY_INFOS[id]); }
    void what(std::ostream& out) const noexcept { if (isProp) out << *data.prop; else out << *data.info; }
    virtual void to_json(json_file_t& json) const noexcept { _to_json(json); }
    virtual void to_json(json_str_t& json) const noexcept { _to_json(json); }
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
  

  struct RuleInfo {
    std::string label;
    location loc;
    std::string json_h;
    IModelError* make_error() const;
  };

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
  std::ostream& operator << (std::ostream& out, const RuleInfo& ri) noexcept { return (out << "rule \""<< ri.label << "\" @(" << ri.loc << ")"); }

  struct Rule {
    bool (*guard)(const State_t&) ;
    void (*action)(State_t&) ;
    const RuleInfo& info;
    const std::string quant_json;
    const std::string quant_str;
    IModelError* make_error() const;
  };

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

  struct RuleSet {
    const RuleInfo& info;
    std::vector<Rule> rules;
    IModelError* make_error() const;
  }; 

  template<class O> ojstream<O>& operator << (ojstream<O>& json, const RuleSet& rs) noexcept { return (json << rs.info); }
  std::ostream& operator << (std::ostream& out, const RuleSet& rs) noexcept { return (out << rs.info); }

  struct ModelRuleError : public IModelError {
    enum Where {UNKNOWN,GUARD,ACTION};
    ModelRuleError(const Rule& rule_) : isRule(true), where(UNKNOWN) { data.rule = &rule_; }
    ModelRuleError(const RuleInfo& info_) : isRule(false), where(UNKNOWN) { data.info = &info_; }
    ModelRuleError(const RuleSet& rule_set_) : isRule(false), where(UNKNOWN) { data.info = &(rule_set_.info); }
    ModelRuleError(id_t id) : isRule(false), where(UNKNOWN) { data.info = &(::__info__::RULE_SET_INFOS[id]); }
    ModelRuleError(id_t id, Where where_) : isRule(false), where(where_) { data.info = &(::__info__::RULE_SET_INFOS[id]); }
    void what(std::ostream& out) const noexcept { if (isRule) out << *data.rule; else out << *data.info; }
    virtual void to_json(json_file_t& json) const noexcept { _to_json(json); }
    virtual void to_json(json_str_t& json) const noexcept { _to_json(json); }
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
  
  struct StartStateInfo {
    const std::string label;
    const location loc;
    const std::string json_h;
    IModelError* make_error() const;
  };

  template<class O> ojstream<O>& operator << (ojstream<O>& json, const StartStateInfo& si) noexcept {
// #ifdef __ROMP__SIMPLE_TRACE
//     json.out << "\"startstate \\\""<< si.label << "\\\""
//                 // " @(" << si.loc << ")\"";
//              << '"';
// #else
    json << si.json_h << '}';
// #endif
    return json;
  }
  std::ostream& operator << (std::ostream& out, const StartStateInfo& si) noexcept { return (out << "startstate \""<< si.label << "\" @(" << si.loc << ")"); }

  struct StartState {
    void (*initialize)(State_t&) ;
    const StartStateInfo& info;
    const id_t id;
    const std::string quant_json;
    const std::string quant_str;
    IModelError* make_error() const;
  };

  template<class O> ojstream<O>& operator << (ojstream<O>& json, const StartState& s) noexcept {
// #ifdef __ROMP__SIMPLE_TRACE
//     json.out << "\"startstate \\\"" << s.info.label << "\\\" ";
//     if (s.quant_str.size() > 0)
//       json.out << " id: " << s.id 
//                << " Quantifiers(" << s.quant_str << ") ";
//     // json.out << "@(" << s.info.loc << ')';
//     json.out << '"';
// #else
    json << s.info.json_h 
         << ",\"id\":" << s.id
         << ",\"quantifiers\":" << s.quant_json << '}';
// #endif
    return json;
  }
  std::ostream& operator << (std::ostream& out, const StartState& s) noexcept {
    out << "startstate \"" << s.info.label << "\" ";
    if (s.quant_str.size() > 0)
      out << "-- id: " << s.id 
          << " -- Quantifiers(" << s.quant_str << ") ";
    return (out << "@(" << s.info.loc << ')');
  }

  struct ModelStartStateError : public IModelError {
    ModelStartStateError(const StartState& rule_) : isStartState(true) { data.rule = &rule_; }
    ModelStartStateError(const StartStateInfo& info_) : isStartState(false) { data.info = &info_; }
    ModelStartStateError(id_t id) : isStartState(false) { data.info = &(::__info__::STARTSTATE_INFOS[id]); }
    void what(std::ostream& out) const noexcept { if (isStartState) out << *data.rule; else out << *data.info; }
    virtual void to_json(json_file_t& json) const noexcept { _to_json(json); }
    virtual void to_json(json_str_t& json) const noexcept { _to_json(json); }
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

  struct MErrorInfo {
    const std::string label;
    location loc;
    bool isFunct;
    const std::string json;
  };

  template<class O> ojstream<O>& operator << (ojstream<O>& json, const MErrorInfo& ei) noexcept { return (json << ei.json); }
  std::ostream& operator << (std::ostream& out, const MErrorInfo& ei) noexcept { return (out << "error \""<< ei.label << "\" @(" << ei.loc << ")"); }
  
  struct ModelMErrorError : public IModelError {
    ModelMErrorError(const MErrorInfo& info_) : _info(info_) {}
    ModelMErrorError(id_t id) : _info(::__info__::ERROR_INFOS[id]) {}
    void what(std::ostream& out) const noexcept { out << _info; }
    virtual void to_json(json_file_t& json) const noexcept { _to_json(json); }
    virtual void to_json(json_str_t& json) const noexcept { _to_json(json); }
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

  struct FunctInfo {
    const std::string label;
    location loc;
    const std::string json;
    const std::string signature;
  };

  template<class O> ojstream<O>& operator << (ojstream<O>& json, const FunctInfo& fi) noexcept { return (json << fi.json); }
  std::ostream& operator << (std::ostream& out, const FunctInfo& fi) noexcept { return (out << fi.signature << " @(" << fi.loc << ")"); }
  
  struct ModelFunctError : public IModelError {
    ModelFunctError(const FunctInfo& info_) : _info(info_) {}
    ModelFunctError(id_t id) : _info(::__info__::FUNCT_INFOS[id]) {}
    void what(std::ostream& out) const noexcept { out << _info; }
    virtual void to_json(json_file_t& json) const noexcept { _to_json(json); }
    virtual void to_json(json_str_t& json) const noexcept { _to_json(json); }
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
  std::ostream& operator << (std::ostream& out, const IModelError& ex) noexcept { ostream_p _out(out,0); _out << ex;  return out; }

  ostream_p& operator << (ostream_p& out, const std::exception& ex) noexcept {
    out << "{exception ``";
    out << ex.what(); // << out.nl();
    out << "``";
    __fprint_exception(out, ex);
    out << '}';
    return out;
  }
  std::ostream& operator << (std::ostream& out, const std::exception& ex) noexcept { ostream_p _out(out,0); _out << ex;  return out; }

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

  class IRandWalker {
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
    friend State_t;
  };

  struct Result {
    using duration_ms_t = std::chrono::duration<long long,std::milli>;
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
    duration_ms_t active_time;
    duration_ms_t total_time;
#endif
    // Result(Result& old) 
    //   : id(old.id), root_seed(old.root_seed), start_id(old.start_id),
    //     cause(old.cause), depth(old.depth), 
    //     tripped(old.tripped), inside(old.inside)
    // { old.tripped = nullptr; old.inside = nullptr; }
    ~Result() { if (tripped != nullptr) delete tripped; if (inside != nullptr) delete inside; }
  };

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
}
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
  template<>
  class hash<romp::IModelError> {
    public: size_t operator () (const romp::IModelError& me) const { return me.hash(); }
  };
  template<>
  class equal_to<romp::IModelError> {
    public: size_t operator () (const romp::IModelError& l, const romp::IModelError& r) const { return l.hash() == r.hash(); }
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
}

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
}

#pragma endregion model_prefixes



#pragma region generated_code


/* ======= Header Comments ====== */


/* ======= Model Type & Const Definitions ====== */

namespace __type__ {
  typedef int range_t;
  typedef unsigned int scalarset_t;
  typedef int enum_backend_t;
  const __typeof__(((int)(1))) HomeCount = ((int)(1)); // number of homes.
  const __typeof__(((int)(2))) ProcCount = ((int)(2)); // number of processors.
  const __typeof__(((int)(1))) AddressCount = ((int)(1)); // number of addresses
  const __typeof__(((int)(1))) ValueCount = ((int)(1)); // number of data values
  const __typeof__((ProcCount)) DirMax = (ProcCount); // Maximum number of dir
  const __typeof__(((DirMax) + ((int)(3)))) NetMax = ((DirMax) + ((int)(3))); // Network capacity.  Must be at least DirMax to
  typedef range_t Home;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& Home_to_json(::romp::ojstream<O>& json, const Home& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& Home_to_json(::romp::ojstream<O>& json, const Home& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"Home\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(0)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& Home_to_str(::romp::ostream_p& out, const Home& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef range_t Proc;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& Proc_to_json(::romp::ojstream<O>& json, const Proc& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& Proc_to_json(::romp::ojstream<O>& json, const Proc& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"Proc\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(1)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& Proc_to_str(::romp::ostream_p& out, const Proc& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef range_t Node;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& Node_to_json(::romp::ojstream<O>& json, const Node& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& Node_to_json(::romp::ojstream<O>& json, const Node& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"Node\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(1)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& Node_to_str(::romp::ostream_p& out, const Node& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef range_t Address;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& Address_to_json(::romp::ojstream<O>& json, const Address& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& Address_to_json(::romp::ojstream<O>& json, const Address& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"Address\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(0)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& Address_to_str(::romp::ostream_p& out, const Address& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef range_t Value;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& Value_to_json(::romp::ojstream<O>& json, const Value& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& Value_to_json(::romp::ojstream<O>& json, const Value& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"Value\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(0)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& Value_to_str(::romp::ostream_p& out, const Value& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef enum { Cache_Read, Cache_Read_Ex, Cache_Promote, Uncache, Write_Back, Update, Data, Invalidate, Uncache_Ack, Write_Back_Ack, Inv_Ack, Fw_Cache_R, Fw_Cache_R_Ex, Ack_Fw_Cache_Ex, Cache_Promote_Ack, } Message_Type;
  std::string to_string(const Message_Type val) { switch (val) { case Cache_Read: return "Cache_Read"; case Cache_Read_Ex: return "Cache_Read_Ex"; case Cache_Promote: return "Cache_Promote"; case Uncache: return "Uncache"; case Write_Back: return "Write_Back"; case Update: return "Update"; case Data: return "Data"; case Invalidate: return "Invalidate"; case Uncache_Ack: return "Uncache_Ack"; case Write_Back_Ack: return "Write_Back_Ack"; case Inv_Ack: return "Inv_Ack"; case Fw_Cache_R: return "Fw_Cache_R"; case Fw_Cache_R_Ex: return "Fw_Cache_R_Ex"; case Ack_Fw_Cache_Ex: return "Ack_Fw_Cache_Ex"; case Cache_Promote_Ack: return "Cache_Promote_Ack"; default: break; } return "Message_Type::__UNKNOWN_ENUM_VALUE__"; }
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& Message_Type_to_json(::romp::ojstream<O>& json, const Message_Type& val) noexcept { json << '"' << to_string(val) << '"'; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& Message_Type_to_json(::romp::ojstream<O>& json, const Message_Type& val) noexcept { json << "{\"$type\":\"enum-value\",\"type\":\"Message_Type\",\"value\":\"" << to_string(val) <<"\"}"; return ::romp::S_VOID; }
#endif
  const ::romp::stream_void& Message_Type_to_str(::romp::ostream_p& out, const Message_Type& val) noexcept { out << to_string(val); return ::romp::S_VOID; }

  typedef struct {
      //---------------------------------------------------------------------
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
      //-----------------------------------------------------------------------
      //
      // File : cache3.m
      //
      // Cache Coherence Protocol on a General Network (message order
      // is NOT preserved).
      //
      // David L. Dill at Stanford University.   Initial protocol design
      //  by Andreas Nowatzyk, and the initial description was derived
      //  from a description by Ken McMillan.  Modified by Norris Ip
      //
      // Note from Dill: If I had to do it over again, I would model the
      // network as a 2D array indexed by source and destination instead
      // of a single array with all the messages in arbitrary order.
      //
      //  The invariant is also an unnecessarily complicated mess!
      //
      //-----------------------------------------------------------------------
      //
      // Status:  No violations of verification conditions, but it does
      // not necessarily implement an appropriate memory model.
      //
      //------------------------------------------------------------------------
      // 
      // Note:
      //
      // For verification, it is convenient to split nodes into two
      // parts: "homes", which have the Memory, Directory and Remote Access
      // System (RAS) and "procs" (processors), which have the Cache and
      // Pending Message Module (PMM).
      //
      //--------------------------------------------- March 4, 1993 ------------
      // number of homes.
      // number of processors.
      // number of addresses
      // number of data values
      // Maximum number of dir
      // entries that can be kept
      // Network capacity.  Must be at least DirMax to
      // allow for invalidations on Cache_Promote,
      // Cache_Read_Ex.
      // Kludge! so I don't have to redo all message field types.
      // request for shared copy
      // request for master copy
      // request for changing shared copy
      // to master copy
      // request for removing shared copy
      // request for removing master copy
      // update data memory w/ new value
      // reply with data
      // request invalidate data at cache
      // acknowledge for uncache data
      // acknowledge for write back
      // acknowledge for invalidate
      // forwarded shared copy request
      // to remote
      // forwarded master copy request
      // to remote
      // acknowledge for forwarded
      // master copy
      // grant permission to change to
      // master copy
      ::__type__::Message_Type MType;
      ::__type__::Node Source;
      ::__type__::Node Destination;
      ::__type__::Node Aux; // Local in Fw_Cache_R, Fw_Cache_R_Ex, Home in Data.
      ::__type__::Address Address;
      ::__type__::Value Value;
    } Message;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& Message_to_json(::romp::ojstream<O>& json, const Message& val) noexcept { using namespace ::__type__; json  << Message_Type_to_json(json,val.MType) << ',' << Node_to_json(json,val.Source) << ',' << Node_to_json(json,val.Destination) << ',' << Node_to_json(json,val.Aux) << ',' << Address_to_json(json,val.Address) << ',' << Value_to_json(json,val.Value); return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& Message_to_json(::romp::ojstream<O>& json, const Message& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"Message\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"MType\",\"value\":" << Message_Type_to_json(json,val.MType) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Source\",\"value\":" << Node_to_json(json,val.Source) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Destination\",\"value\":" << Node_to_json(json,val.Destination) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Aux\",\"value\":" << Node_to_json(json,val.Aux) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Address\",\"value\":" << Address_to_json(json,val.Address) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Value\",\"value\":" << Value_to_json(json,val.Value)<< "}]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& Message_to_str(::romp::ostream_p& out, const Message& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "MType " << ((::romp::OPTIONS.result_show_type) ? ": Message_Type =" : ":=") << ' ' << Message_Type_to_str(out,val.MType) << '\n' << out.indentation() << "Source " << ((::romp::OPTIONS.result_show_type) ? ": Node =" : ":=") << ' ' << Node_to_str(out,val.Source) << '\n' << out.indentation() << "Destination " << ((::romp::OPTIONS.result_show_type) ? ": Node =" : ":=") << ' ' << Node_to_str(out,val.Destination) << '\n' << out.indentation() << "Aux " << ((::romp::OPTIONS.result_show_type) ? ": Node =" : ":=") << ' ' << Node_to_str(out,val.Aux) << '\n' << out.indentation() << "Address " << ((::romp::OPTIONS.result_show_type) ? ": Address =" : ":=") << ' ' << Address_to_str(out,val.Address) << '\n' << out.indentation() << "Value " << ((::romp::OPTIONS.result_show_type) ? ": Value =" : ":=") << ' ' << Value_to_str(out,val.Value) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}

  typedef struct { ::__type__::Value data[1]; constexpr const size_t size() const {return (1ul);} } anon0x0_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x0_t_to_json(::romp::ojstream<O>& json, const anon0x0_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << Value_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x0_t_to_json(::romp::ojstream<O>& json, const anon0x0_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[Address] of Value\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(0) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << Value_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x0_t_to_str(::romp::ostream_p& out, const anon0x0_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< Value_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef enum { Inv, Shared_Remote, Master_Remote, Wait_Inv, Wait_Update, Wait_WB, } anon0x1_t;
  std::string to_string(const anon0x1_t val) { switch (val) { case Inv: return "Inv"; case Shared_Remote: return "Shared_Remote"; case Master_Remote: return "Master_Remote"; case Wait_Inv: return "Wait_Inv"; case Wait_Update: return "Wait_Update"; case Wait_WB: return "Wait_WB"; default: break; } return "anon0x1_t::__UNKNOWN_ENUM_VALUE__"; }
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x1_t_to_json(::romp::ojstream<O>& json, const anon0x1_t& val) noexcept { json << '"' << to_string(val) << '"'; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x1_t_to_json(::romp::ojstream<O>& json, const anon0x1_t& val) noexcept { json << "{\"$type\":\"enum-value\",\"type\":\"Enum {Inv..Wait_WB}\",\"value\":\"" << to_string(val) <<"\"}"; return ::romp::S_VOID; }
#endif
  const ::romp::stream_void& anon0x1_t_to_str(::romp::ostream_p& out, const anon0x1_t& val) noexcept { out << to_string(val); return ::romp::S_VOID; }

  typedef range_t anon0x2_t; // "DirMax" means "DirMax or more".
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x2_t_to_json(::romp::ojstream<O>& json, const anon0x2_t& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x2_t_to_json(::romp::ojstream<O>& json, const anon0x2_t& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"0..DirMax\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(2)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x2_t_to_str(::romp::ostream_p& out, const anon0x2_t& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef range_t anon0x3_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x3_t_to_json(::romp::ojstream<O>& json, const anon0x3_t& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x3_t_to_json(::romp::ojstream<O>& json, const anon0x3_t& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"0..(DirMax - 1)\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(1)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x3_t_to_str(::romp::ostream_p& out, const anon0x3_t& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef struct { ::__type__::Proc data[2]; constexpr const size_t size() const {return (2ul);} } anon0x4_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x4_t_to_json(::romp::ojstream<O>& json, const anon0x4_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << Proc_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x4_t_to_json(::romp::ojstream<O>& json, const anon0x4_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[0..(DirMax - 1)] of Proc\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(1) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << Proc_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x4_t_to_str(::romp::ostream_p& out, const anon0x4_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< Proc_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct {
      // "Address" is node-relative.  A physical address is a pair consisting
      // of a node and address.
      ::__type__::anon0x1_t State;
      // Invalid
      // Shared by remote clusters
      // Owned by a remote cluster
      // Waiting for Invalidate 
      // Acknowledge
      // Waiting for Update to home
      // Waiting for ack for the
      // transfer of ownership or
      // write back of master copy
      ::__type__::anon0x2_t Shared_Count;
      ::__type__::anon0x4_t Entries;
      ::__type__::Proc Inv_Count; // number of pending invalidates.
    } anon0x5_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x5_t_to_json(::romp::ojstream<O>& json, const anon0x5_t& val) noexcept { using namespace ::__type__; json  << anon0x1_t_to_json(json,val.State) << ',' << anon0x2_t_to_json(json,val.Shared_Count) << ',' << anon0x4_t_to_json(json,val.Entries) << ',' << Proc_to_json(json,val.Inv_Count); return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x5_t_to_json(::romp::ojstream<O>& json, const anon0x5_t& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"anon_record_t\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"State\",\"value\":" << anon0x1_t_to_json(json,val.State) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Shared_Count\",\"value\":" << anon0x2_t_to_json(json,val.Shared_Count) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Entries\",\"value\":" << anon0x4_t_to_json(json,val.Entries) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Inv_Count\",\"value\":" << Proc_to_json(json,val.Inv_Count)<< "}]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x5_t_to_str(::romp::ostream_p& out, const anon0x5_t& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "State " << ((::romp::OPTIONS.result_show_type) ? ": Enum {Inv..Wait_WB} =" : ":=") << ' ' << anon0x1_t_to_str(out,val.State) << '\n' << out.indentation() << "Shared_Count " << ((::romp::OPTIONS.result_show_type) ? ": 0..DirMax =" : ":=") << ' ' << anon0x2_t_to_str(out,val.Shared_Count) << '\n' << out.indentation() << "Entries " << ((::romp::OPTIONS.result_show_type) ? ": Array[0..(DirMax - 1)] of Proc =" : ":=") << ' ' << anon0x4_t_to_str(out,val.Entries) << '\n' << out.indentation() << "Inv_Count " << ((::romp::OPTIONS.result_show_type) ? ": Proc =" : ":=") << ' ' << Proc_to_str(out,val.Inv_Count) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}

  typedef struct { ::__type__::anon0x5_t data[1]; constexpr const size_t size() const {return (1ul);} } anon0x6_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x6_t_to_json(::romp::ojstream<O>& json, const anon0x6_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << anon0x5_t_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x6_t_to_json(::romp::ojstream<O>& json, const anon0x6_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[Address] of anon_record_t\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(0) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << anon0x5_t_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x6_t_to_str(::romp::ostream_p& out, const anon0x6_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< anon0x5_t_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct {
      ::__type__::anon0x0_t Mem;
      ::__type__::anon0x6_t Dir;
    } HomeState;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& HomeState_to_json(::romp::ojstream<O>& json, const HomeState& val) noexcept { using namespace ::__type__; json  << anon0x0_t_to_json(json,val.Mem) << ',' << anon0x6_t_to_json(json,val.Dir); return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& HomeState_to_json(::romp::ojstream<O>& json, const HomeState& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"HomeState\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"Mem\",\"value\":" << anon0x0_t_to_json(json,val.Mem) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Dir\",\"value\":" << anon0x6_t_to_json(json,val.Dir)<< "}]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& HomeState_to_str(::romp::ostream_p& out, const HomeState& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "Mem " << ((::romp::OPTIONS.result_show_type) ? ": Array[Address] of Value =" : ":=") << ' ' << anon0x0_t_to_str(out,val.Mem) << '\n' << out.indentation() << "Dir " << ((::romp::OPTIONS.result_show_type) ? ": Array[Address] of anon_record_t =" : ":=") << ' ' << anon0x6_t_to_str(out,val.Dir) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}

  typedef enum { I, S, M, } anon0x7_t; // Invalid, Shared, or Master
  std::string to_string(const anon0x7_t val) { switch (val) { case I: return "I"; case S: return "S"; case M: return "M"; default: break; } return "anon0x7_t::__UNKNOWN_ENUM_VALUE__"; }
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x7_t_to_json(::romp::ojstream<O>& json, const anon0x7_t& val) noexcept { json << '"' << to_string(val) << '"'; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x7_t_to_json(::romp::ojstream<O>& json, const anon0x7_t& val) noexcept { json << "{\"$type\":\"enum-value\",\"type\":\"Enum {I..M}\",\"value\":\"" << to_string(val) <<"\"}"; return ::romp::S_VOID; }
#endif
  const ::romp::stream_void& anon0x7_t_to_str(::romp::ostream_p& out, const anon0x7_t& val) noexcept { out << to_string(val); return ::romp::S_VOID; }

  typedef struct {
      // Cache and Pending Message Module (PMM)
      // must keep track of physical addresses.
      ::__type__::anon0x7_t State;
      ::__type__::Value Value;
    } anon0x8_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x8_t_to_json(::romp::ojstream<O>& json, const anon0x8_t& val) noexcept { using namespace ::__type__; json  << anon0x7_t_to_json(json,val.State) << ',' << Value_to_json(json,val.Value); return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x8_t_to_json(::romp::ojstream<O>& json, const anon0x8_t& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"anon_record_t\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"State\",\"value\":" << anon0x7_t_to_json(json,val.State) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Value\",\"value\":" << Value_to_json(json,val.Value)<< "}]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x8_t_to_str(::romp::ostream_p& out, const anon0x8_t& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "State " << ((::romp::OPTIONS.result_show_type) ? ": Enum {I..M} =" : ":=") << ' ' << anon0x7_t_to_str(out,val.State) << '\n' << out.indentation() << "Value " << ((::romp::OPTIONS.result_show_type) ? ": Value =" : ":=") << ' ' << Value_to_str(out,val.Value) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}

  typedef struct { ::__type__::anon0x8_t data[1]; constexpr const size_t size() const {return (1ul);} } anon0x9_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x9_t_to_json(::romp::ojstream<O>& json, const anon0x9_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << anon0x8_t_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x9_t_to_json(::romp::ojstream<O>& json, const anon0x9_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[Address] of anon_record_t\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(0) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << anon0x8_t_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x9_t_to_str(::romp::ostream_p& out, const anon0x9_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< anon0x8_t_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct { ::__type__::anon0x9_t data[1]; constexpr const size_t size() const {return (1ul);} } anon0xa_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0xa_t_to_json(::romp::ojstream<O>& json, const anon0xa_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << anon0x9_t_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0xa_t_to_json(::romp::ojstream<O>& json, const anon0xa_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[Home] of anon_array_t\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(0) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << anon0x9_t_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0xa_t_to_str(::romp::ostream_p& out, const anon0xa_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< anon0x9_t_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef enum { NOP, CR_Pend, CRE_Pend, CP_Pend, WB_Pend, Uncache_Pend, } anon0xb_t;
  std::string to_string(const anon0xb_t val) { switch (val) { case NOP: return "NOP"; case CR_Pend: return "CR_Pend"; case CRE_Pend: return "CRE_Pend"; case CP_Pend: return "CP_Pend"; case WB_Pend: return "WB_Pend"; case Uncache_Pend: return "Uncache_Pend"; default: break; } return "anon0xb_t::__UNKNOWN_ENUM_VALUE__"; }
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0xb_t_to_json(::romp::ojstream<O>& json, const anon0xb_t& val) noexcept { json << '"' << to_string(val) << '"'; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0xb_t_to_json(::romp::ojstream<O>& json, const anon0xb_t& val) noexcept { json << "{\"$type\":\"enum-value\",\"type\":\"Enum {NOP..Uncache_Pend}\",\"value\":\"" << to_string(val) <<"\"}"; return ::romp::S_VOID; }
#endif
  const ::romp::stream_void& anon0xb_t_to_str(::romp::ostream_p& out, const anon0xb_t& val) noexcept { out << to_string(val); return ::romp::S_VOID; }

  typedef struct { ::__type__::anon0xb_t data[1]; constexpr const size_t size() const {return (1ul);} } anon0xc_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0xc_t_to_json(::romp::ojstream<O>& json, const anon0xc_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << anon0xb_t_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0xc_t_to_json(::romp::ojstream<O>& json, const anon0xc_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[Address] of NOP..Uncache_Pend\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(0) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << anon0xb_t_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0xc_t_to_str(::romp::ostream_p& out, const anon0xc_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< anon0xb_t_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct { ::__type__::anon0xc_t data[1]; constexpr const size_t size() const {return (1ul);} } anon0xd_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0xd_t_to_json(::romp::ojstream<O>& json, const anon0xd_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << anon0xc_t_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0xd_t_to_json(::romp::ojstream<O>& json, const anon0xd_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[Home] of anon_array_t\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(0) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << anon0xc_t_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0xd_t_to_str(::romp::ostream_p& out, const anon0xd_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< anon0xc_t_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct {
      ::__type__::anon0xa_t Cache;
      ::__type__::anon0xd_t PMMState;
    } ProcState;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& ProcState_to_json(::romp::ojstream<O>& json, const ProcState& val) noexcept { using namespace ::__type__; json  << anon0xa_t_to_json(json,val.Cache) << ',' << anon0xd_t_to_json(json,val.PMMState); return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& ProcState_to_json(::romp::ojstream<O>& json, const ProcState& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"ProcState\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"Cache\",\"value\":" << anon0xa_t_to_json(json,val.Cache) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"PMMState\",\"value\":" << anon0xd_t_to_json(json,val.PMMState)<< "}]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& ProcState_to_str(::romp::ostream_p& out, const ProcState& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "Cache " << ((::romp::OPTIONS.result_show_type) ? ": Array[Home] of anon_array_t =" : ":=") << ' ' << anon0xa_t_to_str(out,val.Cache) << '\n' << out.indentation() << "PMMState " << ((::romp::OPTIONS.result_show_type) ? ": Array[Home] of anon_array_t =" : ":=") << ' ' << anon0xd_t_to_str(out,val.PMMState) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}

  typedef struct { ::__type__::HomeState data[1]; constexpr const size_t size() const {return (1ul);} } anon0xe_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0xe_t_to_json(::romp::ojstream<O>& json, const anon0xe_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << HomeState_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0xe_t_to_json(::romp::ojstream<O>& json, const anon0xe_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[Home] of HomeState\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(0) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << HomeState_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0xe_t_to_str(::romp::ostream_p& out, const anon0xe_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< HomeState_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct { ::__type__::ProcState data[2]; constexpr const size_t size() const {return (2ul);} } anon0xf_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0xf_t_to_json(::romp::ojstream<O>& json, const anon0xf_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << ProcState_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0xf_t_to_json(::romp::ojstream<O>& json, const anon0xf_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[Proc] of ProcState\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(1) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << ProcState_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0xf_t_to_str(::romp::ostream_p& out, const anon0xf_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< ProcState_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef range_t anon0x10_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x10_t_to_json(::romp::ojstream<O>& json, const anon0x10_t& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x10_t_to_json(::romp::ojstream<O>& json, const anon0x10_t& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"0..NetMax\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(5)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x10_t_to_str(::romp::ostream_p& out, const anon0x10_t& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef range_t anon0x11_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x11_t_to_json(::romp::ojstream<O>& json, const anon0x11_t& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x11_t_to_json(::romp::ojstream<O>& json, const anon0x11_t& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(4)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x11_t_to_str(::romp::ostream_p& out, const anon0x11_t& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef struct { ::__type__::Message data[5]; constexpr const size_t size() const {return (5ul);} } anon0x12_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x12_t_to_json(::romp::ojstream<O>& json, const anon0x12_t& val) noexcept {std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << Message_to_json(json,val.data[i]); sep = ","; } return ::romp::S_VOID;}
#else
  template<class O> const ::romp::stream_void& anon0x12_t_to_json(::romp::ojstream<O>& json, const anon0x12_t& val) noexcept {json << "{\"$type\":\"array-value\",\"type\":\"Array[0..(NetMax - 1)] of Message\",\"size\":" << val.size() << ",\"lower-bound\":" << VALUE_C(0) << ",\"upper-bound\":" << VALUE_C(4) << ",\"elements\":["; std::string sep; for (size_t i=(0ul); i<val.size(); ++i) { json << sep << Message_to_json(json,val.data[i]); sep = ","; } json << "]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x12_t_to_str(::romp::ostream_p& out, const anon0x12_t& val) noexcept { out << "[\n" << out.indent(); for (size_t i=0; i<val.size(); ++i) { out << out.indentation() << "[" << (i + (VALUE_C(0))) << "]: "<< Message_to_str(out,val.data[i]) << '\n'; } out << out.dedent() << out.indentation() << ']'; return ::romp::S_VOID;}

  typedef struct {
      // invalid
      // waiting for Cache_Read reply
      // waiting for Cache_Read_Ex reply
      // waiting for Cache_Promote reply
      // waiting for Write_Back_Ack
      // waitign for Uncache_ack
      // The Net is, abstractly, a bounded set of NetMax or
      // fewer messages.  It is implemented as an unsorted array,
      // along with a count of the number of elements in the set.
      // The array entries from 0..Count-1 are all valid messages.
      // The entries from Count..MaxNet-1 are all invalid, and are
      // set to a fixed default value to reduce state space blowup.
      ::__type__::anon0x10_t Count;
      ::__type__::anon0x12_t Ar;
    } anon0x13_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x13_t_to_json(::romp::ojstream<O>& json, const anon0x13_t& val) noexcept { using namespace ::__type__; json  << anon0x10_t_to_json(json,val.Count) << ',' << anon0x12_t_to_json(json,val.Ar); return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x13_t_to_json(::romp::ojstream<O>& json, const anon0x13_t& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"anon_record_t\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"Count\",\"value\":" << anon0x10_t_to_json(json,val.Count) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Ar\",\"value\":" << anon0x12_t_to_json(json,val.Ar)<< "}]}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x13_t_to_str(::romp::ostream_p& out, const anon0x13_t& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "Count " << ((::romp::OPTIONS.result_show_type) ? ": 0..NetMax =" : ":=") << ' ' << anon0x10_t_to_str(out,val.Count) << '\n' << out.indentation() << "Ar " << ((::romp::OPTIONS.result_show_type) ? ": Array[0..(NetMax - 1)] of Message =" : ":=") << ' ' << anon0x12_t_to_str(out,val.Ar) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}

  typedef range_t anon0x14_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x14_t_to_json(::romp::ojstream<O>& json, const anon0x14_t& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x14_t_to_json(::romp::ojstream<O>& json, const anon0x14_t& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(4)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x14_t_to_str(::romp::ostream_p& out, const anon0x14_t& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef range_t anon0x15_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x15_t_to_json(::romp::ojstream<O>& json, const anon0x15_t& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x15_t_to_json(::romp::ojstream<O>& json, const anon0x15_t& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(4)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x15_t_to_str(::romp::ostream_p& out, const anon0x15_t& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}

  typedef range_t anon0x16_t;
#ifdef __ROMP__SIMPLE_TRACE
  template<class O> const ::romp::stream_void& anon0x16_t_to_json(::romp::ojstream<O>& json, const anon0x16_t& val) noexcept { json << val; return ::romp::S_VOID; }
#else
  template<class O> const ::romp::stream_void& anon0x16_t_to_json(::romp::ojstream<O>& json, const anon0x16_t& val) noexcept { json << "{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"min\":" << (VALUE_C(0)) << ",\"max\":" << (VALUE_C(4)) << ",\"value\":" << ((range_t)val) << "}"; return ::romp::S_VOID;}
#endif
  const ::romp::stream_void& anon0x16_t_to_str(::romp::ostream_p& out, const anon0x16_t& val) noexcept { out << ((range_t)val); return ::romp::S_VOID;}


}



/* ======= Generated Model & State ====== */

namespace __model__ {

  struct __Model__ {
    ::romp::IRandWalker* __rw__; // reference to associated romp rand walker


    /* ======= Model State Variables ====== */

    ::__type__::anon0xe_t Homes;

    ::__type__::anon0xf_t Procs;

    ::__type__::anon0x13_t Net;


    /* ======= Murphi Model Functions ====== */

    
    void Send(const ::__type__::Message_Type t, const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Node Loc, const ::__type__::Address Addr, const ::__type__::Value Val)  {
      using namespace ::__type__;
      try {
        // Network functions
        if (((Net).Count) == (NetMax)) {
          if (this->__rw__->error_handler(0u))
            throw ::romp::ModelMErrorError(0);

        } else {
          ((((Net).Ar).data[(((Net).Count)) - int_VALUE_C(0)]).MType) = (t);
          ((((Net).Ar).data[(((Net).Count)) - int_VALUE_C(0)]).Source) = (Src);
          ((((Net).Ar).data[(((Net).Count)) - int_VALUE_C(0)]).Destination) = (Dst);
          ((((Net).Ar).data[(((Net).Count)) - int_VALUE_C(0)]).Aux) = (Loc);
          ((((Net).Ar).data[(((Net).Count)) - int_VALUE_C(0)]).Address) = (Addr);
          ((((Net).Ar).data[(((Net).Count)) - int_VALUE_C(0)]).Value) = (Val);
          ((Net).Count) = (((Net).Count) + ((int)(1)));
        }
      } catch (...) { throw ::romp::ModelFunctError(0); }
}

    
    void Consume_Message(const ::__type__::anon0x14_t M_Index)  {
      using namespace ::__type__;
      try {
        if ((M_Index) >= ((Net).Count)) {
          if (this->__rw__->error_handler(1u))
            throw ::romp::ModelMErrorError(1);

        } else {
          do {
            for (int i = ((int)(0)); i <= ((NetMax) - ((int)(2))); i++) {
              if ((i) >= (M_Index)) {
                (((Net).Ar).data[((i)) - int_VALUE_C(0)]) = (((Net).Ar).data[(((i) + ((int)(1)))) - int_VALUE_C(0)]);
              }
            }
          } while (0);
          // Clear last entry.
          ((((Net).Ar).data[((((Net).Count) - ((int)(1)))) - int_VALUE_C(0)]).MType) = (Cache_Read);
          ((((Net).Ar).data[((((Net).Count) - ((int)(1)))) - int_VALUE_C(0)]).Source) = ((int)(0));
          ((((Net).Ar).data[((((Net).Count) - ((int)(1)))) - int_VALUE_C(0)]).Destination) = ((int)(0));
          ((((Net).Ar).data[((((Net).Count) - ((int)(1)))) - int_VALUE_C(0)]).Aux) = ((int)(0));
          ((((Net).Ar).data[((((Net).Count) - ((int)(1)))) - int_VALUE_C(0)]).Address) = ((int)(0));
          ((((Net).Ar).data[((((Net).Count) - ((int)(1)))) - int_VALUE_C(0)]).Value) = ((int)(0));
        }
        ((Net).Count) = (((Net).Count) - ((int)(1)));
      } catch (...) { throw ::romp::ModelFunctError(1); }
}

    
    void Send_Cache_Read(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        // Special send functions
        ::__model__::__Model__::Send((Cache_Read), (Dst), (Src), ((int)(0)), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(2); }
}

    
    void Send_Cache_Read_Ex(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Cache_Read_Ex), (Dst), (Src), ((int)(0)), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(3); }
}

    
    void Send_Uncache(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Uncache), (Dst), (Src), ((int)(0)), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(4); }
}

    
    void Send_Uncache_Ack(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Uncache_Ack), (Dst), (Src), ((int)(0)), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(5); }
}

    
    void Send_Data(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Node Home, const ::__type__::Address addr, const ::__type__::Value val)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Data), (Dst), (Src), (Home), (addr), (val));
      } catch (...) { throw ::romp::ModelFunctError(6); }
}

    
    void Send_Fw_Cache_R(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Node Loc, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Fw_Cache_R), (Dst), (Src), (Loc), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(7); }
}

    
    void Send_Fw_Cache_R_Ex(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Node Loc, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Fw_Cache_R_Ex), (Dst), (Src), (Loc), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(8); }
}

    
    void Send_Ack_Fw_Cache_Ex(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Ack_Fw_Cache_Ex), (Dst), (Src), ((int)(0)), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(9); }
}

    
    void Send_Invalidate(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Invalidate), (Dst), (Src), ((int)(0)), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(10); }
}

    
    void Send_Inv_Ack(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Inv_Ack), (Dst), (Src), ((int)(0)), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(11); }
}

    
    void Send_Write_Back(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr, const ::__type__::Value Data)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Write_Back), (Dst), (Src), ((int)(0)), (Addr), (Data));
      } catch (...) { throw ::romp::ModelFunctError(12); }
}

    
    void Send_Update(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr, const ::__type__::Value Data)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Update), (Dst), (Src), ((int)(0)), (Addr), (Data));
      } catch (...) { throw ::romp::ModelFunctError(13); }
}

    
    void Send_Cache_Promote(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Cache_Promote), (Dst), (Src), ((int)(0)), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(14); }
}

    
    void Send_Cache_Promote_Ack(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Cache_Promote_Ack), (Dst), (Src), ((int)(0)), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(15); }
}

    
    void Send_Write_Back_Ack(const ::__type__::Node Dst, const ::__type__::Node Src, const ::__type__::Address Addr)  {
      using namespace ::__type__;
      try {
        ::__model__::__Model__::Send((Write_Back_Ack), (Dst), (Src), ((int)(0)), (Addr), ((int)(0)));
      } catch (...) { throw ::romp::ModelFunctError(16); }
}

    
    void add_dir_entry(const ::__type__::Node h, const ::__type__::Address a, const ::__type__::Node n)  {
      using namespace ::__type__;
      try {
        // Directory support functions
        // h = home node, a = address, n = node to be added.
        if ((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count) == (DirMax)) {
          if (this->__rw__->error_handler(2u))
            throw ::romp::ModelMErrorError(2);

        }
        ((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Entries).data[((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count)) - int_VALUE_C(0)]) = (n);
        (((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count) = ((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count) + ((int)(1)));
      } catch (...) { throw ::romp::ModelFunctError(17); }
}

    
    void remove_dir_entry(const ::__type__::Node h, const ::__type__::Address a, const ::__type__::Node n)  {
      using namespace ::__type__;
      try {
        // kludged a bit to avoid needing a local variable.
        // WARNING! Calling this rearranges the directory, so
        // indices of directory entries will change!
        if ((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count) == ((int)(0))) {
          if (this->__rw__->error_handler(3u))
            throw ::romp::ModelMErrorError(3);

        }
        // h = home node, a = address, n = node to be added.
        do {
          for (int i = ((int)(0)); i <= ((DirMax) - ((int)(1))); i++) {
            if (((i) < (((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count)) && (((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Entries).data[((i)) - int_VALUE_C(0)]) == (n))) {
              // overwrite this entry with last entry.
              ((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Entries).data[((i)) - int_VALUE_C(0)]) = ((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Entries).data[(((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count) - ((int)(1)))) - int_VALUE_C(0)]);
              // clear last entry	
              ((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Entries).data[(((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count) - ((int)(1)))) - int_VALUE_C(0)]) = ((int)(0));
              (((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count) = ((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count) - ((int)(1)));
            }
          }
        } while (0);
        // if we removed last entry, go to Inv state.
        if ((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count) == ((int)(0))) {
          (((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).State) = (Inv);
        }
      } catch (...) { throw ::romp::ModelFunctError(18); }
}

    
    void Handle_Inv_Ack(const ::__type__::Node n, const ::__type__::Address addr)  {
      using namespace ::__type__;
      try {
        // Procedures for operations that are repeated in several places.
        // This procedure is called when an Inv_Ack message is received,
        // or when we would like to pretend that that has happened.
        if ((((((Homes).data[((n)) - int_VALUE_C(0)]).Dir).data[((addr)) - int_VALUE_C(0)]).Inv_Count) == ((int)(0))) {
          if (this->__rw__->error_handler(4u))
            throw ::romp::ModelMErrorError(4);

        }
        (((((Homes).data[((n)) - int_VALUE_C(0)]).Dir).data[((addr)) - int_VALUE_C(0)]).Inv_Count) = ((((((Homes).data[((n)) - int_VALUE_C(0)]).Dir).data[((addr)) - int_VALUE_C(0)]).Inv_Count) - ((int)(1)));
        if ((((((Homes).data[((n)) - int_VALUE_C(0)]).Dir).data[((addr)) - int_VALUE_C(0)]).Inv_Count) == ((int)(0))) {
          if ((((((Homes).data[((n)) - int_VALUE_C(0)]).Dir).data[((addr)) - int_VALUE_C(0)]).State) != (Wait_Inv)) {
            if (this->__rw__->error_handler(5u))
              throw ::romp::ModelMErrorError(5);

          }
          (((((Homes).data[((n)) - int_VALUE_C(0)]).Dir).data[((addr)) - int_VALUE_C(0)]).State) = (Master_Remote);
        }
      } catch (...) { throw ::romp::ModelFunctError(19); }
}

    
    void Handle_Uncache_Ack(const ::__type__::Node n, const ::__type__::Node home, const ::__type__::Address addr)  {
      using namespace ::__type__;
      try {
        if ((((((Procs).data[((n)) - int_VALUE_C(0)]).PMMState).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]) != (Uncache_Pend)) {
          if (this->__rw__->error_handler(6u))
            throw ::romp::ModelMErrorError(6);

        }
        (((((Procs).data[((n)) - int_VALUE_C(0)]).PMMState).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]) = (NOP);
        ((((((Procs).data[((n)) - int_VALUE_C(0)]).Cache).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]).State) = (I);
        ((((((Procs).data[((n)) - int_VALUE_C(0)]).Cache).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]).Value) = ((int)(0));
      } catch (...) { throw ::romp::ModelFunctError(20); }
}

    
    void Handle_Write_Back_Ack(const ::__type__::Node n, const ::__type__::Node home, const ::__type__::Address addr)  {
      using namespace ::__type__;
      try {
        if ((((((Procs).data[((n)) - int_VALUE_C(0)]).PMMState).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]) != (WB_Pend)) {
          if (this->__rw__->error_handler(7u))
            throw ::romp::ModelMErrorError(7);

        }
        (((((Procs).data[((n)) - int_VALUE_C(0)]).PMMState).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]) = (NOP);
        ((((((Procs).data[((n)) - int_VALUE_C(0)]).Cache).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]).State) = (I);
        ((((((Procs).data[((n)) - int_VALUE_C(0)]).Cache).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]).Value) = ((int)(0));
      } catch (...) { throw ::romp::ModelFunctError(21); }
}


    /* ======= Murphi Model StartStates, Rules & Global Properties ====== */

     void __StartState__startstate21(const ::__type__::Value v){
      using namespace ::__type__;
      try {
        // PMM rules
        // Transaction initiation ("send" part of PMM).
        // All of these messages must leave lots of room in the network
        // to avoid overfilling it with invalidate messages if there
        // is pending Cache_Promote or Cache_Read_Ex message.
        // spontaneously generate a Coherent Read
        // avoid deadlock
        // rule
        // spontaneously generate a Coherent Read Invalidate
        // avoid deadlock
        // rule
        // spontaneously generate a Coherent Invalidate
        // avoid deadlock
        // rule
        // PMM rules, cont.
        // uncache
        // avoid deadlock
        // rule
        // writeback due to replacement.
        // avoid deadlock
        // rule
        // When an address is cached and writable, we can
        // change its value arbitrarily.
        // rule
        // ruleset
        // ruleset
        // ruleset
        // alias
        // ruleset
        // Receive part of PMM.  Note: "n" and "me" are bound in enclosing
        // ruleset and alias.
        // This rule set nondeterministically chooses a candidate
        // message from the Net.
        // is it a valid message?
        // home is msg.Aux.
        // switch
        // !! Block.  Wait for the data.
        // Abort.  Cache_Read_Ex will be treated as Inv_Ack
        // by home.
        // Abort.  Cache_Promote will be treated as Inv_Ack
        // by home.
        // Invalidate and Uncache passed in the network.
        // Treat invalidate like an Uncache_Ack.
        // switch
        // if
        // PMM rules, cont.
        // We have an M copy.  Someone else wants an S copy.
        // Normal case.  Change Cache state to S.  Update
        // home, forward data to local.
        // home.
        // Block.
        // !! This case is tricky.  Home sent data, then
        // got a Cache_Read from someone else and sent a Fw_Cache_R.
        // But the Fw_Cache_R got here first.
        // We have to block, because we don't have the
        // data to forward.
        // The data is definitely on its way, so we won't
        // deadlock.	
        // Let the Fw_Cache_R sit in the queue.
        // !! Block. 
        // We did a Cache_Promote successfully, but Cache_Read from
        //  someone else caused a Fw_Cache_R, which got here before
        // the Cache_Promote_Ack.
        // There may be some way to abort this guy.
        // We're already writing it back.  Treat this as
        // a Write_Back_Ack, but forward data to local.
        // switch
        // PMM rules, cont.
        // We have an M copy. Someone else wants one,
        // so we have to write ours back, convert to I.
        // Normal case.
        // Forward the data immediately.  Send Ack_Fw_Cache_Ex to home.
        // clear Cache entry.
        // We are already in the middle of a writeback.
        // Treat Fw_Cache_R_Ex like a Write_Back_Ack, but forward data to 
        // local.
        // !! Note that in the next two cases, data can get
        // snatched away from a node before the processor
        // has a chance to write to it (Fw_Cache_R_Ex is waiting for
        // data to arrive).  I hope it's not a problem.
        // We don't have the data yet, so block
        // these messages until we do.
        // switch
        // PMM rules, cont.
        // Our Cache_Promote has succeeded.  Make the copy writeable.
        // if
        // Home has seen the uncache.  Invalidate the entry.
        // if
        // do nothing.  Message wasn't for us.
        // switch
        // rule 
        // alias
        // alias
        // alias
        // alias
        // RAS< rules. "n" and "me" still bound
        // is it a valid message?
        // is it for home	
        // Case on message type
        // Someone wants an S copy.
        // Easy case: send him the data, update Dir.
        // Others already have S copies.  Send him the data,
        // Add him to the directory list.
        // Someone has an M copy.  Ask him to update by
        // sending Fw_Cache_R, then go into Wait_Update state to wait
        // for the update to come back.
        // Tell remote cache to update modified entry.
        // remote owner
        // !! Block. Wait for the Inv_Ack
        // !! Block. Wait for the Ack_Fw_Cache_Ex or Write_Back.
        // !! Block. Wait for the Update.
        // switch
        // RAS rules, cont.
        // add local to the directory in Master_Remote state.
        // send data back to local
        // Send invalidate messages to remotes.
        // Set counter so we know when all Inv_Ack's are in.
        // empty the directory.
        // Add local to Dir.  Wait_Inv = waiting for Inv_Acks.
        // remote will forward the data.
        // Add local to Dir.  Wait_WB = wait for Ack_Fw_Cache_Ex
        // Block. Wait for the Inv_Ack
        // Block. Wait for writeback
        // Block. Wait for update
        /*	      Case Master_Remote:	
         -- Treat like Inv_Ack (someone else got entry in M state).
         Handle_Inv_Ack(n, msg.Address);
         Consume_Message(M_Index);	
         */
        // switch
        // RAS rules, cont.
        // Only entry is the local doing the Cache_Promote.
        // No invalidations necessary.
        // Send invalidate messages to remotes.
        // But not to the local that originated the Cache_Promote!
        // Set counter so we know when we have all Inv_Acks back.
        // Empty out the directory.
        // Add local to directory. 
        // Wait_Inv = Waiting for Inv_Acks.
        // Acknowledge the Cache_Promote
        // Treat Cache_Promote as Inv_Ack, because it was or will be
        // aborted (home is handling a Cache_Read_Ex).
        // In this case, Cache_Promote is treated as an Inv_Ack
        // because a competitor has gotten an exclusive
        // copy (via Cache_Promote or Cache_Read_Ex).
        // Block.  Wait for the update.
        // switch
        // RAS rules, cont.
        // Write back happens when local invalidates
        // a writable copy (in response to Invalidate
        // or Fw_Cache_R_Ex message).  Or spontaneously.
        // Normal case.  Remove the writeback node from
        // the directory, acknowledge the write_back.
        // writeback arrived while awaiting an Ack_Fw_Cache_Ex.
        // !! Except you have to make sure it's from
        // the OLD node, not the new one.
        // Writeback from OLD owner.  Pretend it's the Ack_Fw_Cache_Ex.
        // write_back from new owner.  Block it.
        // Waiting for an update (because of Fw_Cache_R), but
        // got a writeback instead.
        // Update memory, remove local from dir, go into
        // shared state.
        // The Fw_Cache_R we already sent is the Write_Back_Ack
        // Similar to Wait_WB case.
        // Writeback and invalidate passed each other
        // Treat Write_Back like Inv_Ack
        //  !! Data goes to local, which then decides
        //  to write_back, before inv_ack has returned
        //  from remote.  Block the writeback.
        // switch	
        // RAS rules, cont.
        // This happens when remote wants to update the main memory
        // while keeping a shared copy (in response to Fw_Cache_R).	
        // waiting for update in response to our Fw_Cache_R.
        // update memory.
        // swtich
        // Message sent by node in S state to indicate that
        // entry is no longer cached.
        // Home just sent an invalidate to everyone
        // including local because of a Cache_Read_Ex on another
        // node.  Treat the uncache like an Inv_Ack.
        // Local should treat the invalidate like an
        // Uncache_Ack.
        // Block.
        // We are waiting for an update.
        // Normal case.
        // Written this way because we can't have multiple
        // expressions in a Case.
        // switch
        // RAS rules, cont.
        // Acknowledge from Fw_Cache_R_Ex
        // switch
        // otherwise, it's a message we don't care about. Do nothing.
        // switch
        // alias
        // rule
        // alias
        // alias
        // ruleset
        // Initialization
        do {
          for (int h = ((int)(0)); h <= ((HomeCount) - ((int)(1))); h++) {
            do {
              for (int a = ((int)(0)); a <= ((AddressCount) - ((int)(1))); a++) {
                ((((Homes).data[((h)) - int_VALUE_C(0)]).Mem).data[((a)) - int_VALUE_C(0)]) = (v);
                (((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).State) = (Inv);
                (((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count) = ((int)(0));
                do {
                  for (int i = ((int)(0)); i <= ((DirMax) - ((int)(1))); i++) {
                    ((((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Entries).data[((i)) - int_VALUE_C(0)]) = ((int)(0));
                  }
                } while (0);
                (((((Homes).data[((h)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Inv_Count) = ((int)(0));
              }
            } while (0);
          }
        } while (0);
        do {
          for (int l = ((int)(0)); l <= ((ProcCount) - ((int)(1))); l++) {
            do {
              for (int h = ((int)(0)); h <= ((HomeCount) - ((int)(1))); h++) {
                do {
                  for (int a = ((int)(0)); a <= ((AddressCount) - ((int)(1))); a++) {
                    ((((((Procs).data[((l)) - int_VALUE_C(0)]).Cache).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]).State) = (I);
                    ((((((Procs).data[((l)) - int_VALUE_C(0)]).Cache).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]).Value) = (v);
                    (((((Procs).data[((l)) - int_VALUE_C(0)]).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) = (NOP);
                  }
                } while (0);
              }
            } while (0);
          }
        } while (0);
        ((Net).Count) = ((int)(0));
        do {
          for (int i = ((int)(0)); i <= ((NetMax) - ((int)(1))); i++) {
            memset(&((Net).Ar), 0, sizeof(((Net).Ar)));
          }
        } while (0);
      } catch (...) { throw ::romp::ModelStartStateError(0); }
    }



    
    bool __Rule_guard__rule4(const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) const {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        return ((((((((me()).Cache).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]).State) == (I)) && (((((me()).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) == (NOP))) && (((Net).Count) <= (((NetMax) - (ProcCount)) - ((int)(1)))));
#undef me
      } catch (...) { throw ::romp::ModelRuleError(0,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__rule4(const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        ((((me()).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) = (CR_Pend);
        ::__model__::__Model__::Send_Cache_Read((h), (n), (a));
#undef me
      } catch (...) { throw ::romp::ModelRuleError(0,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__rule5(const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) const {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        return ((((((((me()).Cache).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]).State) == (I)) && (((((me()).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) == (NOP))) && (((Net).Count) <= (((NetMax) - (ProcCount)) - ((int)(1)))));
#undef me
      } catch (...) { throw ::romp::ModelRuleError(1,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__rule5(const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        ((((me()).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) = (CRE_Pend);
        ::__model__::__Model__::Send_Cache_Read_Ex((h), (n), (a));
#undef me
      } catch (...) { throw ::romp::ModelRuleError(1,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__rule6(const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) const {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        return ((((((((me()).Cache).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]).State) == (S)) && (((((me()).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) == (NOP))) && (((Net).Count) <= (((NetMax) - (ProcCount)) - ((int)(1)))));
#undef me
      } catch (...) { throw ::romp::ModelRuleError(2,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__rule6(const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        ((((me()).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) = (CP_Pend);
        ::__model__::__Model__::Send_Cache_Promote((h), (n), (a));
#undef me
      } catch (...) { throw ::romp::ModelRuleError(2,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__rule7(const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) const {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        return ((((((((me()).Cache).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]).State) == (S)) && (((((me()).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) == (NOP))) && (((Net).Count) <= (((NetMax) - (ProcCount)) - ((int)(1)))));
#undef me
      } catch (...) { throw ::romp::ModelRuleError(3,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__rule7(const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        ((((me()).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) = (Uncache_Pend);
        ::__model__::__Model__::Send_Uncache((h), (n), (a));
#undef me
      } catch (...) { throw ::romp::ModelRuleError(3,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__rule8(const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) const {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        return ((((((((me()).Cache).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]).State) == (M)) && (((((me()).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) == (NOP))) && (((Net).Count) <= (((NetMax) - (ProcCount)) - ((int)(1)))));
#undef me
      } catch (...) { throw ::romp::ModelRuleError(4,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__rule8(const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        ((((me()).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) = (WB_Pend);
        ::__model__::__Model__::Send_Write_Back((h), (n), (a), (((((me()).Cache).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]).Value));
#undef me
      } catch (...) { throw ::romp::ModelRuleError(4,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__rule10(const ::__type__::Value v, const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) const {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        return (((((((me()).Cache).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]).State) == (M)) && (((((me()).PMMState).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]) == (NOP)));
#undef me
      } catch (...) { throw ::romp::ModelRuleError(5,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__rule10(const ::__type__::Value v, const ::__type__::Address a, const ::__type__::Home h, const ::__type__::Proc n) {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n)) - int_VALUE_C(0)])
        (((((me()).Cache).data[((h)) - int_VALUE_C(0)]).data[((a)) - int_VALUE_C(0)]).Value) = (v);
#undef me
      } catch (...) { throw ::romp::ModelRuleError(5,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__rule15(const ::__type__::anon0x15_t M_Index) const {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n())) - int_VALUE_C(0)])
#define n() ((msg()).Destination)
#define msg() (((Net).Ar).data[((M_Index)) - int_VALUE_C(0)])
        return ((M_Index) < ((Net).Count));
#undef me
#undef n
#undef msg
      } catch (...) { throw ::romp::ModelRuleError(6,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__rule15(const ::__type__::anon0x15_t M_Index) {
      using namespace ::__type__;
      try {
#define me() ((Procs).data[((n())) - int_VALUE_C(0)])
#define n() ((msg()).Destination)
#define msg() (((Net).Ar).data[((M_Index)) - int_VALUE_C(0)])
        do {
          __typeof__(((msg()).MType)) res_ = ((msg()).MType);
          if (res_ == (Data)) {
            do {
              __typeof__(((((me()).PMMState).data[(((msg()).Aux)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)])) res_ = ((((me()).PMMState).data[(((msg()).Aux)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]);
              if (res_ == (CR_Pend)) {
                ((((me()).PMMState).data[(((msg()).Aux)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]) = (NOP);
                (((((me()).Cache).data[(((msg()).Aux)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (S);
                (((((me()).Cache).data[(((msg()).Aux)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).Value) = ((msg()).Value);
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (CRE_Pend)) {
                ((((me()).PMMState).data[(((msg()).Aux)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]) = (NOP);
                (((((me()).Cache).data[(((msg()).Aux)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (M);
                (((((me()).Cache).data[(((msg()).Aux)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).Value) = ((msg()).Value);
                ::__model__::__Model__::Consume_Message((M_Index));
              } else {
                if (this->__rw__->error_handler(8u))
                  throw ::romp::ModelMErrorError(8);

              }
            } while (0);
          } else if (res_ == (Invalidate)) {
            if (((((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).State) == (S)) || ((((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).State) == (I))) {
              (((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (I);
              (((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).Value) = ((int)(0));
              do {
                __typeof__(((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)])) res_ = ((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]);
                if (res_ == (NOP)) {
                  ::__model__::__Model__::Send_Inv_Ack(((msg()).Source), (n()), ((msg()).Address));
                  ::__model__::__Model__::Consume_Message((M_Index));
                } else if (res_ == (CR_Pend)) {
                } else if (res_ == (CRE_Pend)) {
                  ((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]) = (NOP);
                  ::__model__::__Model__::Consume_Message((M_Index));
                } else if (res_ == (CP_Pend)) {
                  ((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]) = (NOP);
                  ::__model__::__Model__::Consume_Message((M_Index));
                } else if (res_ == (Uncache_Pend)) {
                  ::__model__::__Model__::Handle_Uncache_Ack((n()), ((msg()).Source), ((msg()).Address));
                  ::__model__::__Model__::Consume_Message((M_Index));
                } else {
                  if (this->__rw__->error_handler(9u))
                    throw ::romp::ModelMErrorError(9);

                }
              } while (0);
            } else {
              if (this->__rw__->error_handler(10u))
                throw ::romp::ModelMErrorError(10);

            }
          } else if (res_ == (Fw_Cache_R)) {
            do {
              __typeof__(((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)])) res_ = ((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]);
              if (res_ == (NOP)) {
                (((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (S);
                ::__model__::__Model__::Send_Data(((msg()).Aux), (n()), ((msg()).Source), ((msg()).Address), (((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).Value));
                ::__model__::__Model__::Send_Update(((msg()).Source), (n()), ((msg()).Address), (((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).Value));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (CRE_Pend)) {
              } else if (res_ == (CP_Pend)) {
              } else if (res_ == (WB_Pend)) {
                ::__model__::__Model__::Send_Data(((msg()).Aux), (n()), ((msg()).Source), ((msg()).Address), (((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).Value));
                ::__model__::__Model__::Handle_Write_Back_Ack((n()), ((msg()).Source), ((msg()).Address));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else {
                if (this->__rw__->error_handler(11u))
                  throw ::romp::ModelMErrorError(11);

              }
            } while (0);
          } else if (res_ == (Fw_Cache_R_Ex)) {
            do {
              __typeof__(((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)])) res_ = ((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]);
              if (res_ == (NOP)) {
                if ((((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).State) != (M)) {
                  if (this->__rw__->error_handler(12u))
                    throw ::romp::ModelMErrorError(12);

                }
                ::__model__::__Model__::Send_Data(((msg()).Aux), (n()), ((msg()).Source), ((msg()).Address), (((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).Value));
                (((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (I);
                (((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).Value) = ((int)(0));
                ::__model__::__Model__::Send_Ack_Fw_Cache_Ex(((msg()).Source), (n()), ((msg()).Address));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (WB_Pend)) {
                ::__model__::__Model__::Send_Data(((msg()).Aux), (n()), ((msg()).Source), ((msg()).Address), (((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).Value));
                ::__model__::__Model__::Handle_Write_Back_Ack((n()), ((msg()).Source), ((msg()).Address));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (CP_Pend)) {
              } else if (res_ == (CRE_Pend)) {
              } else {
                if (this->__rw__->error_handler(13u))
                  throw ::romp::ModelMErrorError(13);

              }
            } while (0);
          } else if (res_ == (Cache_Promote_Ack)) {
            if (((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]) == (CP_Pend)) {
              ((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]) = (NOP);
              (((((me()).Cache).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (M);
              ::__model__::__Model__::Consume_Message((M_Index));
            } else {
              if (this->__rw__->error_handler(14u))
                throw ::romp::ModelMErrorError(14);

            }
          } else if (res_ == (Uncache_Ack)) {
            if (((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]) == (Uncache_Pend)) {
              ::__model__::__Model__::Handle_Uncache_Ack((n()), ((msg()).Source), ((msg()).Address));
              ::__model__::__Model__::Consume_Message((M_Index));
            } else {
              if (this->__rw__->error_handler(15u))
                throw ::romp::ModelMErrorError(15);

            }
          } else if (res_ == (Write_Back_Ack)) {
            if (((((me()).PMMState).data[(((msg()).Source)) - int_VALUE_C(0)]).data[(((msg()).Address)) - int_VALUE_C(0)]) == (WB_Pend)) {
              ::__model__::__Model__::Handle_Write_Back_Ack((n()), ((msg()).Source), ((msg()).Address));
              ::__model__::__Model__::Consume_Message((M_Index));
            } else {
              if (this->__rw__->error_handler(16u))
                throw ::romp::ModelMErrorError(16);

            }
          } else {
          }
        } while (0);
#undef me
#undef n
#undef msg
      } catch (...) { throw ::romp::ModelRuleError(6,::romp::ModelRuleError::ACTION); }
    }

    
    bool __Rule_guard__rule19(const ::__type__::anon0x16_t M_Index) const {
      using namespace ::__type__;
      try {
#define n() ((msg()).Destination)
#define msg() (((Net).Ar).data[((M_Index)) - int_VALUE_C(0)])
        return (((M_Index) < ((Net).Count)) && ((((((((((msg()).MType) == (Cache_Read)) || (((msg()).MType) == (Cache_Read_Ex))) || (((msg()).MType) == (Cache_Promote))) || (((msg()).MType) == (Write_Back))) || (((msg()).MType) == (Update))) || (((msg()).MType) == (Uncache))) || (((msg()).MType) == (Ack_Fw_Cache_Ex))) || (((msg()).MType) == (Inv_Ack))));
#undef n
#undef msg
      } catch (...) { throw ::romp::ModelRuleError(7,::romp::ModelRuleError::GUARD); }
    }

    
    void __Rule_action__rule19(const ::__type__::anon0x16_t M_Index) {
      using namespace ::__type__;
      try {
#define n() ((msg()).Destination)
#define msg() (((Net).Ar).data[((M_Index)) - int_VALUE_C(0)])
#define me() ((Homes).data[((n())) - int_VALUE_C(0)])
        do {
          __typeof__(((msg()).MType)) res_ = ((msg()).MType);
          if (res_ == (Cache_Read)) {
            do {
              __typeof__(((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State)) res_ = ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State);
              if (res_ == (Inv)) {
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Shared_Remote);
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Shared_Count) = ((int)(1));
                (((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries).data[(((int)(0))) - int_VALUE_C(0)]) = ((msg()).Source);
                ::__model__::__Model__::Send_Data(((msg()).Source), (n()), (n()), ((msg()).Address), (((me()).Mem).data[(((msg()).Address)) - int_VALUE_C(0)]));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Shared_Remote)) {
                ::__model__::__Model__::add_dir_entry((n()), ((msg()).Address), ((msg()).Source));
                ::__model__::__Model__::Send_Data(((msg()).Source), (n()), (n()), ((msg()).Address), (((me()).Mem).data[(((msg()).Address)) - int_VALUE_C(0)]));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Master_Remote)) {
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Wait_Update);
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Shared_Count) = ((int)(1));
                ::__model__::__Model__::Send_Fw_Cache_R((((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries).data[(((int)(0))) - int_VALUE_C(0)]), (n()), ((msg()).Source), ((msg()).Address));
                ::__model__::__Model__::add_dir_entry((n()), ((msg()).Address), ((msg()).Source));
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Wait_Update);
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Wait_Inv)) {
              } else if (res_ == (Wait_WB)) {
              } else if (res_ == (Wait_Update)) {
              } else {
                if (this->__rw__->error_handler(17u))
                  throw ::romp::ModelMErrorError(17);

              }
            } while (0);
          } else if (res_ == (Cache_Read_Ex)) {
            do {
              __typeof__(((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State)) res_ = ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State);
              if (res_ == (Inv)) {
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Master_Remote);
                ::__model__::__Model__::add_dir_entry((n()), ((msg()).Address), ((msg()).Source));
                ::__model__::__Model__::Send_Data(((msg()).Source), (n()), (n()), ((msg()).Address), (((me()).Mem).data[(((msg()).Address)) - int_VALUE_C(0)]));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Shared_Remote)) {
                do {
                  for (int i = ((int)(0)); i <= ((DirMax) - ((int)(1))); i++) {
                    if ((i) < ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Shared_Count)) {
                      ::__model__::__Model__::Send_Invalidate((((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries).data[((i)) - int_VALUE_C(0)]), (n()), ((msg()).Address));
                    }
                  }
                } while (0);
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Inv_Count) = ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Shared_Count);
                ::__model__::__Model__::Send_Data(((msg()).Source), (n()), (n()), ((msg()).Address), (((me()).Mem).data[(((msg()).Address)) - int_VALUE_C(0)]));
                memset(&((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries), 0, sizeof(((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries)));
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Shared_Count) = ((int)(0));
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Wait_Inv);
                ::__model__::__Model__::add_dir_entry((n()), ((msg()).Address), ((msg()).Source));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Master_Remote)) {
                ::__model__::__Model__::Send_Fw_Cache_R_Ex((((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries).data[(((int)(0))) - int_VALUE_C(0)]), (n()), ((msg()).Source), ((msg()).Address));
                memset(&((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries), 0, sizeof(((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries)));
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Shared_Count) = ((int)(0));
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Wait_WB);
                ::__model__::__Model__::add_dir_entry((n()), ((msg()).Address), ((msg()).Source));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Wait_Inv)) {
              } else if (res_ == (Wait_WB)) {
              } else if (res_ == (Wait_Update)) {
              } else {
                if (this->__rw__->error_handler(18u))
                  throw ::romp::ModelMErrorError(18);

              }
            } while (0);
          } else if (res_ == (Cache_Promote)) {
            do {
              __typeof__(((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State)) res_ = ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State);
              if (res_ == (Inv)) {
                if (this->__rw__->error_handler(19u))
                  throw ::romp::ModelMErrorError(19);

              } else if (res_ == (Shared_Remote)) {
                if (((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Shared_Count) == ((int)(1))) {
                  ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Master_Remote);
                } else {
                  do {
                    for (int i = ((int)(0)); i <= ((DirMax) - ((int)(1))); i++) {
                      if (((i) < ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Shared_Count)) && ((((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries).data[((i)) - int_VALUE_C(0)]) != ((msg()).Source))) {
                        ::__model__::__Model__::Send_Invalidate((((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries).data[((i)) - int_VALUE_C(0)]), (n()), ((msg()).Address));
                      }
                    }
                  } while (0);
                  ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Inv_Count) = (((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Shared_Count) - ((int)(1)));
                  memset(&((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries), 0, sizeof(((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries)));
                  ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Shared_Count) = ((int)(0));
                  ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Wait_Inv);
                  ::__model__::__Model__::add_dir_entry((n()), ((msg()).Address), ((msg()).Source));
                }
                ::__model__::__Model__::Send_Cache_Promote_Ack(((msg()).Source), (n()), ((msg()).Address));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Wait_Inv)) {
                ::__model__::__Model__::Handle_Inv_Ack((n()), ((msg()).Address));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Master_Remote)) {
                ::__model__::__Model__::Handle_Inv_Ack((n()), ((msg()).Address));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Wait_Update)) {
              } else {
                if (this->__rw__->error_handler(20u))
                  throw ::romp::ModelMErrorError(20);

              }
            } while (0);
          } else if (res_ == (Write_Back)) {
            do {
              __typeof__(((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State)) res_ = ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State);
              if (res_ == (Master_Remote)) {
                (((me()).Mem).data[(((msg()).Address)) - int_VALUE_C(0)]) = ((msg()).Value);
                ::__model__::__Model__::remove_dir_entry((n()), ((msg()).Address), ((msg()).Source));
                ::__model__::__Model__::Send_Write_Back_Ack(((msg()).Source), (n()), ((msg()).Address));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Wait_WB)) {
                if ((((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries).data[(((int)(0))) - int_VALUE_C(0)]) != ((msg()).Source)) {
                  (((me()).Mem).data[(((msg()).Address)) - int_VALUE_C(0)]) = ((msg()).Value);
                  ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Master_Remote);
                  ::__model__::__Model__::Consume_Message((M_Index));
                } else {
                }
              } else if (res_ == (Wait_Update)) {
                (((me()).Mem).data[(((msg()).Address)) - int_VALUE_C(0)]) = ((msg()).Value);
                ::__model__::__Model__::remove_dir_entry((n()), ((msg()).Address), ((msg()).Source));
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Shared_Remote);
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Wait_Inv)) {
                if ((((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).Entries).data[(((int)(0))) - int_VALUE_C(0)]) != ((msg()).Source)) {
                  ::__model__::__Model__::Handle_Inv_Ack((n()), ((msg()).Address));
                  ::__model__::__Model__::Consume_Message((M_Index));
                } else {
                }
              } else {
                if (this->__rw__->error_handler(21u))
                  throw ::romp::ModelMErrorError(21);

              }
            } while (0);
          } else if (res_ == (Update)) {
            do {
              __typeof__(((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State)) res_ = ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State);
              if (res_ == (Wait_Update)) {
                (((me()).Mem).data[(((msg()).Address)) - int_VALUE_C(0)]) = ((msg()).Value);
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Shared_Remote);
                ::__model__::__Model__::Consume_Message((M_Index));
              } else {
                if (this->__rw__->error_handler(22u))
                  throw ::romp::ModelMErrorError(22);

              }
            } while (0);
          } else if (res_ == (Uncache)) {
            do {
              __typeof__(((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State)) res_ = ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State);
              if (res_ == (Wait_Inv)) {
                ::__model__::__Model__::Handle_Inv_Ack((n()), ((msg()).Address));
                ::__model__::__Model__::Consume_Message((M_Index));
              } else if (res_ == (Wait_Update)) {
              } else {
                if ((((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) == (Shared_Remote)) || (((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) == (Wait_Update))) {
                  ::__model__::__Model__::remove_dir_entry((n()), ((msg()).Address), ((msg()).Source));
                  ::__model__::__Model__::Send_Uncache_Ack(((msg()).Source), (n()), ((msg()).Address));
                  ::__model__::__Model__::Consume_Message((M_Index));
                } else {
                  if (this->__rw__->error_handler(23u))
                    throw ::romp::ModelMErrorError(23);

                }
              }
            } while (0);
          } else if (res_ == (Ack_Fw_Cache_Ex)) {
            do {
              __typeof__(((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State)) res_ = ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State);
              if (res_ == (Wait_WB)) {
                ((((me()).Dir).data[(((msg()).Address)) - int_VALUE_C(0)]).State) = (Master_Remote);
                ::__model__::__Model__::Consume_Message((M_Index));
              } else {
                if (this->__rw__->error_handler(24u))
                  throw ::romp::ModelMErrorError(24);

              }
            } while (0);
          } else if (res_ == (Inv_Ack)) {
            ::__model__::__Model__::Handle_Inv_Ack((n()), ((msg()).Address));
            ::__model__::__Model__::Consume_Message((M_Index));
          } else {
          }
        } while (0);
#undef me
#undef n
#undef msg
      } catch (...) { throw ::romp::ModelRuleError(7,::romp::ModelRuleError::ACTION); }
    }


    
    bool __Property__property22(void) const {
      using namespace ::__type__;
      try {
        return this->__rw__->invariant_handler(({ bool res_0 = true; for (int n = ((int)(0)); n <= ((HomeCount) - ((int)(1))); n++) { res_0&= ({ bool res_1 = true; for (int a = ((int)(0)); a <= ((AddressCount) - ((int)(1))); a++) { res_1&= (((!((((((Homes).data[((n)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).State) == (Inv))) || ((((((Homes).data[((n)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count) == ((int)(0)))) && ({ bool res_2 = true; for (int i = ((int)(0)); i <= ((DirMax) - ((int)(1))); i++) { res_2&= (!((i) >= (((((Homes).data[((n)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Shared_Count)) || (((((((Homes).data[((n)) - int_VALUE_C(0)]).Dir).data[((a)) - int_VALUE_C(0)]).Entries).data[((i)) - int_VALUE_C(0)]) == ((int)(0)))); } res_2; })); } res_1; }); } res_0; }),0u);
      } catch (...) { throw ::romp::ModelPropertyError(0); }
    }

    
    bool __Property__property23(void) const {
      using namespace ::__type__;
      try {
        return this->__rw__->invariant_handler(({ bool res_3 = true; for (int n1 = ((int)(0)); n1 <= ((ProcCount) - ((int)(1))); n1++) { res_3&= ({ bool res_4 = true; for (int n2 = ((int)(0)); n2 <= ((ProcCount) - ((int)(1))); n2++) { res_4&= ({ bool res_5 = true; for (int home = ((int)(0)); home <= ((HomeCount) - ((int)(1))); home++) { res_5&= ({ bool res_6 = true; for (int addr = ((int)(0)); addr <= ((AddressCount) - ((int)(1))); addr++) { res_6&= ((!((n1) != (n2))) || (!(((((((((Procs).data[((n1)) - int_VALUE_C(0)]).Cache).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]).State) == (M)) && ((((((Procs).data[((n1)) - int_VALUE_C(0)]).PMMState).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]) != (WB_Pend))) && (((((((((Procs).data[((n2)) - int_VALUE_C(0)]).Cache).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]).State) == (M)) && ((((((Procs).data[((n2)) - int_VALUE_C(0)]).PMMState).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]) != (WB_Pend))) || (((((((((Procs).data[((n2)) - int_VALUE_C(0)]).Cache).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]).State) == (S)) && ((((((Procs).data[((n2)) - int_VALUE_C(0)]).PMMState).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]) != (Uncache_Pend))) && (!({ bool res_7 = false; for (int i = ((int)(0)); i <= ((NetMax) - ((int)(1))); i++) { res_7 |= (((((i) < ((Net).Count)) && (((((Net).Ar).data[((i)) - int_VALUE_C(0)]).MType) == (Invalidate))) && (((((Net).Ar).data[((i)) - int_VALUE_C(0)]).Source) == (home))) && (((((Net).Ar).data[((i)) - int_VALUE_C(0)]).Destination) == (n2))); } res_7; }))))))); } res_6; }); } res_5; }); } res_4; }); } res_3; }),1u);
      } catch (...) { throw ::romp::ModelPropertyError(1); }
    }

    
    bool __Property__property24(void) const {
      using namespace ::__type__;
      try {
        return this->__rw__->invariant_handler(({ bool res_8 = true; for (int n1 = ((int)(0)); n1 <= ((ProcCount) - ((int)(1))); n1++) { res_8&= ({ bool res_9 = true; for (int home = ((int)(0)); home <= ((HomeCount) - ((int)(1))); home++) { res_9&= ({ bool res_10 = true; for (int addr = ((int)(0)); addr <= ((AddressCount) - ((int)(1))); addr++) { res_10&= (!((((((((((Procs).data[((n1)) - int_VALUE_C(0)]).Cache).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]).State) == (S)) && (((((((Procs).data[((n1)) - int_VALUE_C(0)]).Cache).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]).Value) != ((((Homes).data[((home)) - int_VALUE_C(0)]).Mem).data[((addr)) - int_VALUE_C(0)]))) && ((((((Procs).data[((n1)) - int_VALUE_C(0)]).PMMState).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]) != (Uncache_Pend))) && (!({ bool res_11 = false; for (int i = ((int)(0)); i <= ((NetMax) - ((int)(1))); i++) { res_11 |= (((i) < ((Net).Count)) && (((((((((Net).Ar).data[((i)) - int_VALUE_C(0)]).MType) == (Invalidate)) && (((((Net).Ar).data[((i)) - int_VALUE_C(0)]).Source) == (home))) && (((((Net).Ar).data[((i)) - int_VALUE_C(0)]).Destination) == (n1))) || (((((((Net).Ar).data[((i)) - int_VALUE_C(0)]).MType) == (Update)) && (((((Net).Ar).data[((i)) - int_VALUE_C(0)]).Destination) == (home))) && (((((Net).Ar).data[((i)) - int_VALUE_C(0)]).Value) == ((((((Procs).data[((n1)) - int_VALUE_C(0)]).Cache).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]).Value)))) || (((((((Net).Ar).data[((i)) - int_VALUE_C(0)]).MType) == (Write_Back)) && (((((Net).Ar).data[((i)) - int_VALUE_C(0)]).Destination) == (home))) && (((((Net).Ar).data[((i)) - int_VALUE_C(0)]).Value) == ((((((Procs).data[((n1)) - int_VALUE_C(0)]).Cache).data[((home)) - int_VALUE_C(0)]).data[((addr)) - int_VALUE_C(0)]).Value))))); } res_11; })))); } res_10; }); } res_9; }); } res_8; }),2u);
      } catch (...) { throw ::romp::ModelPropertyError(2); }
    }


  };

  /* ======= Murphi Model Output Functions ====== */
#ifdef __ROMP__SIMPLE_TRACE
template<class O> const ::romp::stream_void& __Model___to_json(::romp::ojstream<O>& json, const __Model__& val) noexcept { using namespace ::__type__; json  << anon0xe_t_to_json(json,val.Homes) << ',' << anon0xf_t_to_json(json,val.Procs) << ',' << anon0x13_t_to_json(json,val.Net); return ::romp::S_VOID; }
#else
template<class O> const ::romp::stream_void& __Model___to_json(::romp::ojstream<O>& json, const __Model__& val) noexcept { using namespace ::__type__; json << "{\"$type\":\"record-value\",\"type\":\"__Model__\",\"fields\":[" << "{\"$type\":\"kv-pair\",\"key\":\"Homes\",\"value\":" << anon0xe_t_to_json(json,val.Homes) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Procs\",\"value\":" << anon0xf_t_to_json(json,val.Procs) << "}," << "{\"$type\":\"kv-pair\",\"key\":\"Net\",\"value\":" << anon0x13_t_to_json(json,val.Net)<< "}]}"; return ::romp::S_VOID;}
#endif
const ::romp::stream_void& __Model___to_str(::romp::ostream_p& out, const __Model__& val) noexcept { using namespace ::__type__; out << "{\n" << out.indent() << out.indentation() << "Homes " << ((::romp::OPTIONS.result_show_type) ? ": Array[Home] of HomeState =" : ":=") << ' ' << anon0xe_t_to_str(out,val.Homes) << '\n' << out.indentation() << "Procs " << ((::romp::OPTIONS.result_show_type) ? ": Array[Proc] of ProcState =" : ":=") << ' ' << anon0xf_t_to_str(out,val.Procs) << '\n' << out.indentation() << "Net " << ((::romp::OPTIONS.result_show_type) ? ": anon_record_t =" : ":=") << ' ' << anon0x13_t_to_str(out,val.Net) << '\n' << out.dedent()<< out.indentation() << '}'; return ::romp::S_VOID;}
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
#define _ROMP_STATESPACE_COUNT_str "75042790738092011948526420046573267250132093949525884928"
/* the number of functions & procedures in the model */
#define _ROMP_FUNCTS_LEN (22ul)
  /* the info/metadata about the functions/procedures in the model */
  const ::romp::FunctInfo FUNCT_INFOS[_ROMP_FUNCTS_LEN] = {{"Send",{{170,1},{189,5}},"{\"$type\":\"procedure\",\"label\":\"Send\",\"params\":[{\"$type\":\"param\",\"id\":\"t\",\"type\":\"Message_Type\"},{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Loc\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"},{\"$type\":\"param\",\"id\":\"Val\",\"type\":\"Value\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[170,1],\"end\":[189,5]}}","procedure Send(var t: Message_Type; var Dst: Node; var Src: Node; var Loc: Node; var Addr: Address; var Val: Value);"},{"Consume_Message",{{191,1},{211,5}},"{\"$type\":\"procedure\",\"label\":\"Consume_Message\",\"params\":[{\"$type\":\"param\",\"id\":\"M_Index\",\"type\":\"0..(NetMax - 1)\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[191,1],\"end\":[211,5]}}","procedure Consume_Message(var M_Index: 0..(NetMax - 1));"},{"Send_Cache_Read",{{214,1},{216,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Cache_Read\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[214,1],\"end\":[216,5]}}","procedure Send_Cache_Read(var Dst: Node; var Src: Node; var Addr: Address);"},{"Send_Cache_Read_Ex",{{218,1},{220,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Cache_Read_Ex\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[218,1],\"end\":[220,5]}}","procedure Send_Cache_Read_Ex(var Dst: Node; var Src: Node; var Addr: Address);"},{"Send_Uncache",{{222,1},{224,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Uncache\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[222,1],\"end\":[224,5]}}","procedure Send_Uncache(var Dst: Node; var Src: Node; var Addr: Address);"},{"Send_Uncache_Ack",{{226,1},{228,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Uncache_Ack\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[226,1],\"end\":[228,5]}}","procedure Send_Uncache_Ack(var Dst: Node; var Src: Node; var Addr: Address);"},{"Send_Data",{{230,1},{233,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Data\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Home\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"addr\",\"type\":\"Address\"},{\"$type\":\"param\",\"id\":\"val\",\"type\":\"Value\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[230,1],\"end\":[233,5]}}","procedure Send_Data(var Dst: Node; var Src: Node; var Home: Node; var addr: Address; var val: Value);"},{"Send_Fw_Cache_R",{{235,1},{238,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Fw_Cache_R\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Loc\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[235,1],\"end\":[238,5]}}","procedure Send_Fw_Cache_R(var Dst: Node; var Src: Node; var Loc: Node; var Addr: Address);"},{"Send_Fw_Cache_R_Ex",{{240,1},{243,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Fw_Cache_R_Ex\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Loc\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[240,1],\"end\":[243,5]}}","procedure Send_Fw_Cache_R_Ex(var Dst: Node; var Src: Node; var Loc: Node; var Addr: Address);"},{"Send_Ack_Fw_Cache_Ex",{{245,1},{247,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Ack_Fw_Cache_Ex\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[245,1],\"end\":[247,5]}}","procedure Send_Ack_Fw_Cache_Ex(var Dst: Node; var Src: Node; var Addr: Address);"},{"Send_Invalidate",{{249,1},{251,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Invalidate\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[249,1],\"end\":[251,5]}}","procedure Send_Invalidate(var Dst: Node; var Src: Node; var Addr: Address);"},{"Send_Inv_Ack",{{253,1},{255,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Inv_Ack\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[253,1],\"end\":[255,5]}}","procedure Send_Inv_Ack(var Dst: Node; var Src: Node; var Addr: Address);"},{"Send_Write_Back",{{257,1},{260,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Write_Back\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"},{\"$type\":\"param\",\"id\":\"Data\",\"type\":\"Value\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[257,1],\"end\":[260,5]}}","procedure Send_Write_Back(var Dst: Node; var Src: Node; var Addr: Address; var Data: Value);"},{"Send_Update",{{262,1},{265,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Update\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"},{\"$type\":\"param\",\"id\":\"Data\",\"type\":\"Value\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[262,1],\"end\":[265,5]}}","procedure Send_Update(var Dst: Node; var Src: Node; var Addr: Address; var Data: Value);"},{"Send_Cache_Promote",{{267,1},{269,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Cache_Promote\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[267,1],\"end\":[269,5]}}","procedure Send_Cache_Promote(var Dst: Node; var Src: Node; var Addr: Address);"},{"Send_Cache_Promote_Ack",{{271,1},{273,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Cache_Promote_Ack\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[271,1],\"end\":[273,5]}}","procedure Send_Cache_Promote_Ack(var Dst: Node; var Src: Node; var Addr: Address);"},{"Send_Write_Back_Ack",{{275,1},{278,5}},"{\"$type\":\"procedure\",\"label\":\"Send_Write_Back_Ack\",\"params\":[{\"$type\":\"param\",\"id\":\"Dst\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Src\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"Addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[275,1],\"end\":[278,5]}}","procedure Send_Write_Back_Ack(var Dst: Node; var Src: Node; var Addr: Address);"},{"add_dir_entry",{{282,1},{290,5}},"{\"$type\":\"procedure\",\"label\":\"add_dir_entry\",\"params\":[{\"$type\":\"param\",\"id\":\"h\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"a\",\"type\":\"Address\"},{\"$type\":\"param\",\"id\":\"n\",\"type\":\"Node\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[282,1],\"end\":[290,5]}}","procedure add_dir_entry(var h: Node; var a: Address; var n: Node);"},{"remove_dir_entry",{{295,1},{318,5}},"{\"$type\":\"procedure\",\"label\":\"remove_dir_entry\",\"params\":[{\"$type\":\"param\",\"id\":\"h\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"a\",\"type\":\"Address\"},{\"$type\":\"param\",\"id\":\"n\",\"type\":\"Node\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[295,1],\"end\":[318,5]}}","procedure remove_dir_entry(var h: Node; var a: Address; var n: Node);"},{"Handle_Inv_Ack",{{324,1},{338,5}},"{\"$type\":\"procedure\",\"label\":\"Handle_Inv_Ack\",\"params\":[{\"$type\":\"param\",\"id\":\"n\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[324,1],\"end\":[338,5]}}","procedure Handle_Inv_Ack(var n: Node; var addr: Address);"},{"Handle_Uncache_Ack",{{340,1},{349,5}},"{\"$type\":\"procedure\",\"label\":\"Handle_Uncache_Ack\",\"params\":[{\"$type\":\"param\",\"id\":\"n\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"home\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[340,1],\"end\":[349,5]}}","procedure Handle_Uncache_Ack(var n: Node; var home: Node; var addr: Address);"},{"Handle_Write_Back_Ack",{{351,1},{360,5}},"{\"$type\":\"procedure\",\"label\":\"Handle_Write_Back_Ack\",\"params\":[{\"$type\":\"param\",\"id\":\"n\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"home\",\"type\":\"Node\"},{\"$type\":\"param\",\"id\":\"addr\",\"type\":\"Address\"}],\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[351,1],\"end\":[360,5]}}","procedure Handle_Write_Back_Ack(var n: Node; var home: Node; var addr: Address);"},};
/* the number of error statements in the model */
#define _ROMP_ERRORS_LEN (25ul)
  /* the info/metadata about the murphi error statements in the model */
  const ::romp::MErrorInfo ERROR_INFOS[_ROMP_ERRORS_LEN] = {{"Network is full",{{179,5},{179,28}},1,"{\"$type\":\"error-statement\",\"label\":\"Network is full\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[179,5],\"end\":[179,28]}"},{"Invalid Message Index",{{194,5},{194,34}},1,"{\"$type\":\"error-statement\",\"label\":\"Invalid Message Index\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[194,5],\"end\":[194,34]}"},{"Directory overflow",{{286,5},{286,31}},1,"{\"$type\":\"error-statement\",\"label\":\"Directory overflow\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[286,5],\"end\":[286,31]}"},{"Cannot remove from empty directory",{{298,5},{298,47}},1,"{\"$type\":\"error-statement\",\"label\":\"Cannot remove from empty directory\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[298,5],\"end\":[298,47]}"},{"Bad invalidation count",{{327,5},{327,35}},1,"{\"$type\":\"error-statement\",\"label\":\"Bad invalidation count\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[327,5],\"end\":[327,35]}"},{"Should be in RE state",{{334,7},{334,36}},1,"{\"$type\":\"error-statement\",\"label\":\"Should be in RE state\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[334,7],\"end\":[334,36]}"},{"PMM state not Uncache_Pend",{{344,5},{344,39}},1,"{\"$type\":\"error-statement\",\"label\":\"PMM state not Uncache_Pend\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[344,5],\"end\":[344,39]}"},{"PMM state not WB_Pend",{{355,5},{355,34}},1,"{\"$type\":\"error-statement\",\"label\":\"PMM state not WB_Pend\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[355,5],\"end\":[355,34]}"},{"Data received in funny PMMState",{{468,8},{468,47}},0,"{\"$type\":\"error-statement\",\"label\":\"Data received in funny PMMState\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[468,8],\"end\":[468,47]}"},{"Got Invalidate with funny PMM state",{{498,12},{498,55}},0,"{\"$type\":\"error-statement\",\"label\":\"Got Invalidate with funny PMM state\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[498,12],\"end\":[498,55]}"},{"Invalidate message when in M state",{{501,8},{501,50}},0,"{\"$type\":\"error-statement\",\"label\":\"Invalidate message when in M state\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[501,8],\"end\":[501,50]}"},{"Fw_Cache_R received with funny PMMState",{{541,8},{541,55}},0,"{\"$type\":\"error-statement\",\"label\":\"Fw_Cache_R received with funny PMMState\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[541,8],\"end\":[541,55]}"},{"Fw_Cache_R_Ex received, but Cache not M",{{553,10},{553,57}},0,"{\"$type\":\"error-statement\",\"label\":\"Fw_Cache_R_Ex received, but Cache not M\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[553,10],\"end\":[553,57]}"},{"Fw_Cache_R_Ex received in funny PMMState",{{581,8},{581,56}},0,"{\"$type\":\"error-statement\",\"label\":\"Fw_Cache_R_Ex received in funny PMMState\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[581,8],\"end\":[581,56]}"},{"Cache_Promote_Ack when PMMstate not CP_Pend",{{593,15},{593,66}},0,"{\"$type\":\"error-statement\",\"label\":\"Cache_Promote_Ack when PMMstate not CP_Pend\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[593,15],\"end\":[593,66]}"},{"Uncache_Ack received in funny PMMState",{{603,8},{603,54}},0,"{\"$type\":\"error-statement\",\"label\":\"Uncache_Ack received in funny PMMState\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[603,8],\"end\":[603,54]}"},{"Write_Back_Ack when PMMState not WB_Pend",{{612,8},{612,56}},0,"{\"$type\":\"error-statement\",\"label\":\"Write_Back_Ack when PMMState not WB_Pend\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[612,8],\"end\":[612,56]}"},{"Cache_Read received in funny Dir state",{{680,3},{680,49}},0,"{\"$type\":\"error-statement\",\"label\":\"Cache_Read received in funny Dir state\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[680,3],\"end\":[680,49]}"},{"Cache_Read_Ex received in funny Dir state",{{733,10},{733,59}},0,"{\"$type\":\"error-statement\",\"label\":\"Cache_Read_Ex received in funny Dir state\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[733,10],\"end\":[733,59]}"},{"Home in Inv state on Cache_Promote",{{740,3},{740,45}},0,"{\"$type\":\"error-statement\",\"label\":\"Home in Inv state on Cache_Promote\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[740,3],\"end\":[740,45]}"},{"Cache_Promote received in funny Dir state",{{783,10},{783,59}},0,"{\"$type\":\"error-statement\",\"label\":\"Cache_Promote received in funny Dir state\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[783,10],\"end\":[783,59]}"},{"Writeback received in funny Dir state",{{836,3},{836,48}},0,"{\"$type\":\"error-statement\",\"label\":\"Writeback received in funny Dir state\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[836,3],\"end\":[836,48]}"},{"Update received in funny Dir state",{{851,3},{851,45}},0,"{\"$type\":\"error-statement\",\"label\":\"Update received in funny Dir state\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[851,3],\"end\":[851,45]}"},{"Uncache received in funny Dir state",{{879,12},{879,55}},0,"{\"$type\":\"error-statement\",\"label\":\"Uncache received in funny Dir state\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[879,12],\"end\":[879,55]}"},{"Ack_Fw_Cache_Ex received in funny Dir state",{{891,10},{891,61}},0,"{\"$type\":\"error-statement\",\"label\":\"Ack_Fw_Cache_Ex received in funny Dir state\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[891,10],\"end\":[891,61]}"},};
/* the number of property statements & rules in the model */
#define _ROMP_PROPERTIES_LEN (3ul)
/* the number of cover property statements & rules in the model */
#define _ROMP_COVER_PROP_COUNT (0ul) // the number of property rules (after ruleset expansion) in the model
/* the number of liveness property rules in the model */
#define _ROMP_LIVENESS_PROP_COUNT (0ul) // the number of property rules (after ruleset expansion) in the model
  /* the info/metadata about the murphi properties in the model */
  const ::romp::PropertyInfo PROPERTY_INFOS[_ROMP_PROPERTIES_LEN] = {{"property22",::romp::PropertyType::INVARIANT,"forall n : Home do forall a : Address do (((!(Homes[n].Dir[a].State = Inv)) | (Homes[n].Dir[a].Shared_Count = 0)) & forall i : 0..(DirMax - 1) do ((i >= Homes[n].Dir[a].Shared_Count) -> (Homes[n].Dir[a].Entries[i] = 0)) endforall) endforall endforall",0,{{941,3},{950,8}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall n : Home do forall a : Address do (((!(Homes[n].Dir[a].State = Inv)) | (Homes[n].Dir[a].Shared_Count = 0)) & forall i : 0..(DirMax - 1) do ((i >= Homes[n].Dir[a].Shared_Count) -> (Homes[n].Dir[a].Entries[i] = 0)) endforall) endforall endforall\",\"label\":\"property22\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[941,3],\"end\":[950,8]}"},{"property23",::romp::PropertyType::INVARIANT,"forall n1 : Proc do forall n2 : Proc do forall home : Home do forall addr : Address do ((!(n1 != n2)) | (!(((Procs[n1].Cache[home][addr].State = M) & (Procs[n1].PMMState[home][addr] != WB_Pend)) & (((Procs[n2].Cache[home][addr].State = M) & (Procs[n2].PMMState[home][addr] != WB_Pend)) | (((Procs[n2].Cache[home][addr].State = S) & (Procs[n2].PMMState[home][addr] != Uncache_Pend)) & (!exists i : 0..(NetMax - 1) do ((((i < Net.Count) & (Net.Ar[i].MType = Invalidate)) & (Net.Ar[i].Source = home)) & (Net.Ar[i].Destination = n2)) endexists)))))) endforall endforall endforall endforall",1,{{952,3},{974,8}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall n1 : Proc do forall n2 : Proc do forall home : Home do forall addr : Address do ((!(n1 != n2)) | (!(((Procs[n1].Cache[home][addr].State = M) & (Procs[n1].PMMState[home][addr] != WB_Pend)) & (((Procs[n2].Cache[home][addr].State = M) & (Procs[n2].PMMState[home][addr] != WB_Pend)) | (((Procs[n2].Cache[home][addr].State = S) & (Procs[n2].PMMState[home][addr] != Uncache_Pend)) & (!exists i : 0..(NetMax - 1) do ((((i < Net.Count) & (Net.Ar[i].MType = Invalidate)) & (Net.Ar[i].Source = home)) & (Net.Ar[i].Destination = n2)) endexists)))))) endforall endforall endforall endforall\",\"label\":\"property23\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[952,3],\"end\":[974,8]}"},{"property24",::romp::PropertyType::INVARIANT,"forall n1 : Proc do forall home : Home do forall addr : Address do (!((((Procs[n1].Cache[home][addr].State = S) & (Procs[n1].Cache[home][addr].Value != Homes[home].Mem[addr])) & (Procs[n1].PMMState[home][addr] != Uncache_Pend)) & (!exists i : 0..(NetMax - 1) do ((i < Net.Count) & (((((Net.Ar[i].MType = Invalidate) & (Net.Ar[i].Source = home)) & (Net.Ar[i].Destination = n1)) | (((Net.Ar[i].MType = Update) & (Net.Ar[i].Destination = home)) & (Net.Ar[i].Value = Procs[n1].Cache[home][addr].Value))) | (((Net.Ar[i].MType = Write_Back) & (Net.Ar[i].Destination = home)) & (Net.Ar[i].Value = Procs[n1].Cache[home][addr].Value)))) endexists))) endforall endforall endforall",2,{{976,3},{997,8}},"{\"$type\":\"property\",\"type\":\"invariant\",\"expr\":\"forall n1 : Proc do forall home : Home do forall addr : Address do (!((((Procs[n1].Cache[home][addr].State = S) & (Procs[n1].Cache[home][addr].Value != Homes[home].Mem[addr])) & (Procs[n1].PMMState[home][addr] != Uncache_Pend)) & (!exists i : 0..(NetMax - 1) do ((i < Net.Count) & (((((Net.Ar[i].MType = Invalidate) & (Net.Ar[i].Source = home)) & (Net.Ar[i].Destination = n1)) | (((Net.Ar[i].MType = Update) & (Net.Ar[i].Destination = home)) & (Net.Ar[i].Value = Procs[n1].Cache[home][addr].Value))) | (((Net.Ar[i].MType = Write_Back) & (Net.Ar[i].Destination = home)) & (Net.Ar[i].Value = Procs[n1].Cache[home][addr].Value)))) endexists))) endforall endforall endforall\",\"label\":\"property24\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[976,3],\"end\":[997,8]}"},};
/* the number of start state rules (before ruleset expansions) in the model */
#define _ROMP_STARTSTATE_INFO_LEN (1ul)
  /* the info/metadata about the startstate rules in the model */
  const ::romp::StartStateInfo STARTSTATE_INFOS[_ROMP_STARTSTATE_INFO_LEN] = {{"startstate21",{{908,1},{935,4}},"{\"$type\":\"startstate\",\"label\":\"startstate21\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[908,1],\"end\":[935,4]}"},};
/* the number of rules in the model, BEFORE ruleset expansion */
#define _ROMP_RULESETS_LEN (8ul)
  /* the info/metadata about the rules in the model */
  const ::romp::RuleInfo RULE_SET_INFOS[_ROMP_RULESETS_LEN] = {{"rule4",{{372,9},{380,5}},"{\"$type\":\"rule\",\"expr\":\"(((me.Cache[h][a].State = I) & (me.PMMState[h][a] = NOP)) & (Net.Count <= ((NetMax - ProcCount) - 1)))\",\"label\":\"rule4\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[372,9],\"end\":[380,5]}"},{"rule5",{{382,9},{390,5}},"{\"$type\":\"rule\",\"expr\":\"(((me.Cache[h][a].State = I) & (me.PMMState[h][a] = NOP)) & (Net.Count <= ((NetMax - ProcCount) - 1)))\",\"label\":\"rule5\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[382,9],\"end\":[390,5]}"},{"rule6",{{392,9},{400,5}},"{\"$type\":\"rule\",\"expr\":\"(((me.Cache[h][a].State = S) & (me.PMMState[h][a] = NOP)) & (Net.Count <= ((NetMax - ProcCount) - 1)))\",\"label\":\"rule6\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[392,9],\"end\":[400,5]}"},{"rule7",{{403,2},{411,5}},"{\"$type\":\"rule\",\"expr\":\"(((me.Cache[h][a].State = S) & (me.PMMState[h][a] = NOP)) & (Net.Count <= ((NetMax - ProcCount) - 1)))\",\"label\":\"rule7\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[403,2],\"end\":[411,5]}"},{"rule8",{{413,2},{421,5}},"{\"$type\":\"rule\",\"expr\":\"(((me.Cache[h][a].State = M) & (me.PMMState[h][a] = NOP)) & (Net.Count <= ((NetMax - ProcCount) - 1)))\",\"label\":\"rule8\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[413,2],\"end\":[421,5]}"},{"rule10",{{426,4},{431,7}},"{\"$type\":\"rule\",\"expr\":\"((me.Cache[h][a].State = M) & (me.PMMState[h][a] = NOP))\",\"label\":\"rule10\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[426,4],\"end\":[431,7]}"},{"rule15",{{448,9},{618,12}},"{\"$type\":\"rule\",\"expr\":\"(M_Index < Net.Count)\",\"label\":\"rule15\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[448,9],\"end\":[618,12]}"},{"rule19",{{629,11},{901,14}},"{\"$type\":\"rule\",\"expr\":\"((M_Index < Net.Count) & ((((((((msg.MType = Cache_Read) | (msg.MType = Cache_Read_Ex)) | (msg.MType = Cache_Promote)) | (msg.MType = Write_Back)) | (msg.MType = Update)) | (msg.MType = Uncache)) | (msg.MType = Ack_Fw_Cache_Ex)) | (msg.MType = Inv_Ack)))\",\"label\":\"rule19\",\"loc\":{\"$type\":\"location\",\"file\":\"/mnt/g/My Drive/School/UofU/proj/romp/rumur-romp/romp/tests/cache3.m\",\"start\":[629,11],\"end\":[901,14]}"},};

}

/* ======= Romp CALLER Lists ====== */
namespace __caller__ {
  typedef ::__model__::__Model__ State_t; // type mask for the generated state object
  /* --- Rules Generated by: `rule4` (RuleSet expansions) --- */
   bool __Rule_guard__rule4__0(const State_t& s){return s.__Rule_guard__rule4((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   void __Rule_action__rule4__0(State_t& s){s.__Rule_action__rule4((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   bool __Rule_guard__rule4__1(const State_t& s){return s.__Rule_guard__rule4((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
   void __Rule_action__rule4__1(State_t& s){s.__Rule_action__rule4((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
  /* --- Rules Generated by: `rule5` (RuleSet expansions) --- */
   bool __Rule_guard__rule5__0(const State_t& s){return s.__Rule_guard__rule5((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   void __Rule_action__rule5__0(State_t& s){s.__Rule_action__rule5((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   bool __Rule_guard__rule5__1(const State_t& s){return s.__Rule_guard__rule5((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
   void __Rule_action__rule5__1(State_t& s){s.__Rule_action__rule5((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
  /* --- Rules Generated by: `rule6` (RuleSet expansions) --- */
   bool __Rule_guard__rule6__0(const State_t& s){return s.__Rule_guard__rule6((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   void __Rule_action__rule6__0(State_t& s){s.__Rule_action__rule6((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   bool __Rule_guard__rule6__1(const State_t& s){return s.__Rule_guard__rule6((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
   void __Rule_action__rule6__1(State_t& s){s.__Rule_action__rule6((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
  /* --- Rules Generated by: `rule7` (RuleSet expansions) --- */
   bool __Rule_guard__rule7__0(const State_t& s){return s.__Rule_guard__rule7((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   void __Rule_action__rule7__0(State_t& s){s.__Rule_action__rule7((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   bool __Rule_guard__rule7__1(const State_t& s){return s.__Rule_guard__rule7((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
   void __Rule_action__rule7__1(State_t& s){s.__Rule_action__rule7((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
  /* --- Rules Generated by: `rule8` (RuleSet expansions) --- */
   bool __Rule_guard__rule8__0(const State_t& s){return s.__Rule_guard__rule8((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   void __Rule_action__rule8__0(State_t& s){s.__Rule_action__rule8((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   bool __Rule_guard__rule8__1(const State_t& s){return s.__Rule_guard__rule8((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
   void __Rule_action__rule8__1(State_t& s){s.__Rule_action__rule8((::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
  /* --- Rules Generated by: `rule10` (RuleSet expansions) --- */
   bool __Rule_guard__rule10__0(const State_t& s){return s.__Rule_guard__rule10((::__type__::Value) 0, (::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   void __Rule_action__rule10__0(State_t& s){s.__Rule_action__rule10((::__type__::Value) 0, (::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 0); }
   bool __Rule_guard__rule10__1(const State_t& s){return s.__Rule_guard__rule10((::__type__::Value) 0, (::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
   void __Rule_action__rule10__1(State_t& s){s.__Rule_action__rule10((::__type__::Value) 0, (::__type__::Address) 0, (::__type__::Home) 0, (::__type__::Proc) 1); }
  /* --- Rules Generated by: `rule15` (RuleSet expansions) --- */
   bool __Rule_guard__rule15__0(const State_t& s){return s.__Rule_guard__rule15((::__type__::anon0x15_t) 0); }
   void __Rule_action__rule15__0(State_t& s){s.__Rule_action__rule15((::__type__::anon0x15_t) 0); }
   bool __Rule_guard__rule15__1(const State_t& s){return s.__Rule_guard__rule15((::__type__::anon0x15_t) 1); }
   void __Rule_action__rule15__1(State_t& s){s.__Rule_action__rule15((::__type__::anon0x15_t) 1); }
   bool __Rule_guard__rule15__2(const State_t& s){return s.__Rule_guard__rule15((::__type__::anon0x15_t) 2); }
   void __Rule_action__rule15__2(State_t& s){s.__Rule_action__rule15((::__type__::anon0x15_t) 2); }
   bool __Rule_guard__rule15__3(const State_t& s){return s.__Rule_guard__rule15((::__type__::anon0x15_t) 3); }
   void __Rule_action__rule15__3(State_t& s){s.__Rule_action__rule15((::__type__::anon0x15_t) 3); }
   bool __Rule_guard__rule15__4(const State_t& s){return s.__Rule_guard__rule15((::__type__::anon0x15_t) 4); }
   void __Rule_action__rule15__4(State_t& s){s.__Rule_action__rule15((::__type__::anon0x15_t) 4); }
  /* --- Rules Generated by: `rule19` (RuleSet expansions) --- */
   bool __Rule_guard__rule19__0(const State_t& s){return s.__Rule_guard__rule19((::__type__::anon0x16_t) 0); }
   void __Rule_action__rule19__0(State_t& s){s.__Rule_action__rule19((::__type__::anon0x16_t) 0); }
   bool __Rule_guard__rule19__1(const State_t& s){return s.__Rule_guard__rule19((::__type__::anon0x16_t) 1); }
   void __Rule_action__rule19__1(State_t& s){s.__Rule_action__rule19((::__type__::anon0x16_t) 1); }
   bool __Rule_guard__rule19__2(const State_t& s){return s.__Rule_guard__rule19((::__type__::anon0x16_t) 2); }
   void __Rule_action__rule19__2(State_t& s){s.__Rule_action__rule19((::__type__::anon0x16_t) 2); }
   bool __Rule_guard__rule19__3(const State_t& s){return s.__Rule_guard__rule19((::__type__::anon0x16_t) 3); }
   void __Rule_action__rule19__3(State_t& s){s.__Rule_action__rule19((::__type__::anon0x16_t) 3); }
   bool __Rule_guard__rule19__4(const State_t& s){return s.__Rule_guard__rule19((::__type__::anon0x16_t) 4); }
   void __Rule_action__rule19__4(State_t& s){s.__Rule_action__rule19((::__type__::anon0x16_t) 4); }

/* the number of rules in the model, AFTER ruleset expansion */
#define _ROMP_RULE_COUNT (22ul)


  // All of the rule sets in one place
  const ::romp::RuleSet RULESETS[_ROMP_RULESETS_LEN] = {
		{::__info__::RULE_SET_INFOS[0],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__rule4__0,__Rule_action__rule4__0,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":0}}]","a:=0; h:=0; n:=0"}, ::romp::Rule{__Rule_guard__rule4__1,__Rule_action__rule4__1,::__info__::RULE_SET_INFOS[0],"[{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":1}}]","a:=0; h:=0; n:=1"}  	}},
		{::__info__::RULE_SET_INFOS[1],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__rule5__0,__Rule_action__rule5__0,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":0}}]","a:=0; h:=0; n:=0"}, ::romp::Rule{__Rule_guard__rule5__1,__Rule_action__rule5__1,::__info__::RULE_SET_INFOS[1],"[{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":1}}]","a:=0; h:=0; n:=1"}  	}},
		{::__info__::RULE_SET_INFOS[2],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__rule6__0,__Rule_action__rule6__0,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":0}}]","a:=0; h:=0; n:=0"}, ::romp::Rule{__Rule_guard__rule6__1,__Rule_action__rule6__1,::__info__::RULE_SET_INFOS[2],"[{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":1}}]","a:=0; h:=0; n:=1"}  	}},
		{::__info__::RULE_SET_INFOS[3],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__rule7__0,__Rule_action__rule7__0,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":0}}]","a:=0; h:=0; n:=0"}, ::romp::Rule{__Rule_guard__rule7__1,__Rule_action__rule7__1,::__info__::RULE_SET_INFOS[3],"[{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":1}}]","a:=0; h:=0; n:=1"}  	}},
		{::__info__::RULE_SET_INFOS[4],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__rule8__0,__Rule_action__rule8__0,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":0}}]","a:=0; h:=0; n:=0"}, ::romp::Rule{__Rule_guard__rule8__1,__Rule_action__rule8__1,::__info__::RULE_SET_INFOS[4],"[{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":1}}]","a:=0; h:=0; n:=1"}  	}},
		{::__info__::RULE_SET_INFOS[5],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__rule10__0,__Rule_action__rule10__0,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"v\",\"value\":{\"$type\":\"range-value\",\"type\":\"Value\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":0}}]","v:=0; a:=0; h:=0; n:=0"}, ::romp::Rule{__Rule_guard__rule10__1,__Rule_action__rule10__1,::__info__::RULE_SET_INFOS[5],"[{\"$type\":\"kv-pair\",\"key\":\"v\",\"value\":{\"$type\":\"range-value\",\"type\":\"Value\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"a\",\"value\":{\"$type\":\"range-value\",\"type\":\"Address\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"h\",\"value\":{\"$type\":\"range-value\",\"type\":\"Home\",\"value\":0}},{\"$type\":\"kv-pair\",\"key\":\"n\",\"value\":{\"$type\":\"range-value\",\"type\":\"Proc\",\"value\":1}}]","v:=0; a:=0; h:=0; n:=1"}  	}},
		{::__info__::RULE_SET_INFOS[6],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__rule15__0,__Rule_action__rule15__0,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"M_Index\",\"value\":{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"value\":0}}]","M_Index:=0"}, ::romp::Rule{__Rule_guard__rule15__1,__Rule_action__rule15__1,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"M_Index\",\"value\":{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"value\":1}}]","M_Index:=1"}, ::romp::Rule{__Rule_guard__rule15__2,__Rule_action__rule15__2,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"M_Index\",\"value\":{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"value\":2}}]","M_Index:=2"}, ::romp::Rule{__Rule_guard__rule15__3,__Rule_action__rule15__3,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"M_Index\",\"value\":{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"value\":3}}]","M_Index:=3"}, ::romp::Rule{__Rule_guard__rule15__4,__Rule_action__rule15__4,::__info__::RULE_SET_INFOS[6],"[{\"$type\":\"kv-pair\",\"key\":\"M_Index\",\"value\":{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"value\":4}}]","M_Index:=4"}  	}},
		{::__info__::RULE_SET_INFOS[7],std::vector<::romp::Rule>{::romp::Rule{__Rule_guard__rule19__0,__Rule_action__rule19__0,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"M_Index\",\"value\":{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"value\":0}}]","M_Index:=0"}, ::romp::Rule{__Rule_guard__rule19__1,__Rule_action__rule19__1,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"M_Index\",\"value\":{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"value\":1}}]","M_Index:=1"}, ::romp::Rule{__Rule_guard__rule19__2,__Rule_action__rule19__2,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"M_Index\",\"value\":{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"value\":2}}]","M_Index:=2"}, ::romp::Rule{__Rule_guard__rule19__3,__Rule_action__rule19__3,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"M_Index\",\"value\":{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"value\":3}}]","M_Index:=3"}, ::romp::Rule{__Rule_guard__rule19__4,__Rule_action__rule19__4,::__info__::RULE_SET_INFOS[7],"[{\"$type\":\"kv-pair\",\"key\":\"M_Index\",\"value\":{\"$type\":\"range-value\",\"type\":\"0..(NetMax - 1)\",\"value\":4}}]","M_Index:=4"}  	}}};

  /* --- Property Rule(s) generated by: `property22` (RuleSet expansions) --- */
   bool __Property__property22__0(const State_t& s) {return s.__Property__property22(); }
  /* --- Property Rule(s) generated by: `property23` (RuleSet expansions) --- */
   bool __Property__property23__0(const State_t& s) {return s.__Property__property23(); }
  /* --- Property Rule(s) generated by: `property24` (RuleSet expansions) --- */
   bool __Property__property24__0(const State_t& s) {return s.__Property__property24(); }

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
#define _ROMP_PROPERTY_RULES_LEN ((3ul) + ___propRule_assume_count___ + ___propRule_cover_count___ + ___propRule_liveness_count___)

  /* All of the property rules expanded in one place */
const ::romp::Property PROPERTIES[_ROMP_PROPERTY_RULES_LEN] = {
		{__Property__property22__0,::__info__::PROPERTY_INFOS[0],"[]",""},
		{__Property__property23__0,::__info__::PROPERTY_INFOS[1],"[]",""},
		{__Property__property24__0,::__info__::PROPERTY_INFOS[2],"[]",""},
};

  /* --- StartState Rule(s) generated by: `startstate21` (RuleSet expansions) --- */
   void __StartState__startstate21__0(State_t& s){ s.__StartState__startstate21((::__type__::Value) 0); }


#define _ROMP_STARTSTATES_LEN (1ul) // the number of property rules (after ruleset expansion) in the model

  // All of the rule sets in one place
const ::romp::StartState STARTSTATES[_ROMP_STARTSTATES_LEN] = {{__StartState__startstate21__0,::__info__::STARTSTATE_INFOS[0],0,"[{\"$type\":\"kv-pair\",\"key\":\"v\",\"value\":{\"$type\":\"range-value\",\"type\":\"Value\",\"value\":0}}]","v:=0"}};


}



#pragma endregion generated_code


#pragma region romp_rw

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
 * @version 0.1
 */
#include <thread>
#include <mutex>
#ifndef __romp__GENERATED_CODE
#include "c_prefix.cpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif

// << =================================== Type Declarations ==================================== >>

namespace romp {
  using duration_ms_t = std::chrono::duration<long long,std::milli>;
  using time_ms_t = std::chrono::time_point<std::chrono::high_resolution_clock,std::chrono::duration<long long,std::milli>>;

  time_ms_t time_ms() {
    return std::chrono::time_point_cast<duration_ms_t>(std::chrono::high_resolution_clock::now());
  }

/**
 * @brief helper function rand_choice 
 * 
 */
template<typename T>
T rand_choice(unsigned int &seed, T min, T max) {
    //not done fully
    seed = (((seed ^ (seed >> 3)) >> 12) & 0xffff) | ((seed & 0x7fff) << 16); // modifies the seed
    int choice = seed % (max-min) + min;  // generates the random number
    return choice;
}

class RandWalker : public ::romp::IRandWalker {
private:
  static id_t next_id;
  const id_t id;
  id_t start_id;
  const unsigned int init_rand_seed;
  unsigned int rand_seed;
  State_t state;
  size_t _fuel = OPTIONS.depth;
  bool _valid = true;  // legacy 
  bool _is_error = false; // legacy
  Result::Cause status = Result::RUNNING;
  json_file_t* json;
  // tripped thing
  IModelError* tripped = nullptr;
  IModelError* tripped_inside = nullptr;
  size_t _attempt_limit = OPTIONS.attempt_limit;
  const size_t init_attempt_limit = OPTIONS.attempt_limit;
  struct History {
    const Rule* rule;
  };
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
  time_ms_t start_time;
  duration_ms_t active_time = duration_ms_t(0l);
  duration_ms_t total_time = duration_ms_t(0l);
#endif
  
  void init_state() noexcept {    
    const StartState& startstate = ::__caller__::STARTSTATES[start_id];
#ifdef __ROMP__DO_MEASURE
    start_time = time_ms();
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
    active_time += time_ms() - start_time;
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

  RandWalker(unsigned int rand_seed_) 
    : rand_seed(rand_seed_),
      init_rand_seed(rand_seed_),
      sim1Step(((OPTIONS.do_trace) 
                  ? std::function<void()>([this](){sim1Step_trace();}) 
                  : std::function<void()>([this](){sim1Step_no_trace();}))),
      id(RandWalker::next_id++) 
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
    if (OPTIONS.do_trace) {
      init_trace();
    }
    for (int i=0; i<history_size(); ++i) history[i] = History{nullptr};
#ifdef __romp__ENABLE_symmetry
    for (int i=0; i<_ROMP_RULESETS_LEN; ++i) next_rule[i] = 0;
#endif
#ifdef __romp__ENABLE_cover_property
    for (int i=0; i<_ROMP_COVER_PROP_COUNT; ++i) cover_counts[i] = 0;
#endif
#ifdef __romp__ENABLE_liveness_property
    for (int i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i) lcounts[i] = init_lcount;
#endif
  } 

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
    start_time = time_ms();
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
    active_time += time_ms() - start_time;
#endif
    if (_fuel % _ROMP_FLUSH_FREQ == 0)
      json->out.flush();
  }

  void sim1Step_no_trace() noexcept {
#ifdef __ROMP__DO_MEASURE
    start_time = time_ms();
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
    active_time += time_ms() - start_time;
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

  void trace_result_out() const {
    *json << "]"; // close trace
    // if (_valid && tripped == nullptr) // if it didn't end in an error we need to: 
    if (tripped_inside == nullptr) // if it didn't end in an error we need to: 
      *json << ",\"error-trace\":[]"; // output empty error-trace
    *json << ",\"results\":{\"depth\":"<< OPTIONS.depth-_fuel <<",\"valid\":null,\"is-error\":null"
          << ",\"result\":\"" << std::to_string(status) << "\"" 
#ifdef __ROMP__DO_MEASURE
                                << ",\"active-time\":" << active_time.count() 
                                << ",\"total-time\":" << total_time.count()
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
        << "      Depth: " << OPTIONS.depth - rw._fuel                              << out.nl()
        << "   Start ID: " << rw.start_id                                           << out.nl()
        << " StartState: " << ::__caller__::STARTSTATES[rw.start_id]                << out.nl()
        << "     Result: " << res_color << std::to_string(rw.status) << "\033[0m"   << out.nl()
        << out.dedent()                                                             << out.nl()
        << "TRACE LITE:"                                            << out.indent() << out.nl()
        << "NOTE - " << ((OPTIONS.do_trace) 
                          ? "see \"" + OPTIONS.trace_dir + std::to_string(rw.init_rand_seed) + ".json\" for full trace." 
                          : "use the --trace/-t option to generate a full & detailed trace." ) << out.nl()
        << "History: ["                                             << out.indent() << out.nl()
        << "-(0) " << ::__caller__::STARTSTATES[rw.start_id] << '\n';
      if (rw.history_start > 0)
        out << out.indentation() << "-(..) ... forgotten past ...\n";
      for (size_t i=rw.history_start; i<rw.history_level; ++i)
        out << out.indentation() << "-(" << i+1 <<") " << *(rw.history[i%rw.history_size()].rule) << "\n";
    out << out.dedent() << "]"                                                      << out.nl();
    if (OPTIONS.result_emit_state)
      out << "  State: " <<  out.indent() << rw.state << out.dedent()               ;// << out.nl();
    if (rw.tripped != nullptr || rw.tripped_inside != nullptr) {
      out << out.dedent()                                                           << out.nl()
          << "ISSUE REPORT:"                                        << out.indent() << out.nl();
      if (rw.tripped != nullptr)
        out << "Tripped: \033[31m" << *rw.tripped << "\033[0m"                      << out.nl();
      if (rw.tripped_inside != nullptr)
        out << "  Trace: "                                          << out.indent() << out.nl()
            << *rw.tripped_inside                                   << out.dedent() << out.nl();
            // << '}'                                                                  << out.nl(); 
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
  { ostream_p _out(out,0); _out << rw; return out; }

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
    status = Result::MERROR_REACHED;
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
  const bool enable_cover = OPTIONS.complete_on_cover;
  const id_t goal_cover_count = OPTIONS.cover_count;
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
#ifdef __romp__ENABLE_liveness_property
private:
  const bool enable_liveness = OPTIONS.liveness;
  const size_t init_lcount = OPTIONS.lcount;
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
    return true;  // TODO actually handle this as described in the help page
  }
#else
  bool liveness_handler(bool expr, id_t liveness_id, id_t prop_id) {
    return false;  // never throw anything if cover is not enabled by romp generator
  }
#endif
}; //? END class RandomWalker

id_t RandWalker::next_id = 0u;


/**
 * @brief A class that indexes and groups the various results a RandWalker can produce,
 *        and provides a helpful operator for writing a nice summary of the results 
 *        to a \c std::ostream as well.
 */
class ResultTree {
  time_ms_t start_time = time_ms();
  time_ms_t end_time;
  size_t rules_fired = 0;
  size_t size = 0;
#ifdef __ROMP__DO_MEASURE
  duration_ms_t total_walk_active_time = duration_ms_t(0);
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
  ~ResultTree() {
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
  ResultTree() {}
  void insert(const Result* res) {
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
  void start_timer() { start_time = time_ms(); }
  void reset_timer() { start_time = time_ms(); }
  void stop_timer() { end_time = time_ms(); }
  duration_ms_t get_time() const { return end_time - start_time; }
  friend std::ostream& operator << (std::ostream& out, const ResultTree& results) {
    ostream_p _out(out);
    _out << results;
    return out;
  }
  friend ostream_p& operator << (ostream_p& out, const ResultTree& r) {
    int i = 1; // int j = 1;
    size_t issues = 0; size_t abs_issues = 0;
#ifdef __romp__ENABLE_assume_property
    if (OPTIONS.r_assume && r.n_assumptions_violated > 0) {
      issues += r.assumptions_violated.size();
      abs_issues += r.n_assumptions_violated;
      out << out.indentation() << "\033[1;4mASSUMPTION(S) VIOLATED (n="<< r.assumptions_violated.size() 
          << " |n|=" << r.n_assumptions_violated << "):\033[0m\n";
      out.indent(); i = 1;
      for (const auto& _a : r.assumptions_violated) {  
        out << out.indentation()
            << "\033[1m-(" << (i++) << ") assume \"" << _a.first.label() << "\":\033[0m\n";
        out.indent();
        for (const auto& a : _a.second) {
          out << out.indentation()
              << "-[w#" << a->id << "] seed=" << a->root_seed << " start-id=" << a->start_id <<" depth=" << a->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << a->active_time << " (|t|=" << a->total_time << ')';
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
    if ((OPTIONS.attempt_limit != _ROMP_ATTEMPT_LIMIT_DEFAULT && OPTIONS.deadlock) 
          && r.attempt_limits_reached.size() > 0) {
        out << out.indentation() << "\033[1;4mATTEMPT LIMIT(S) REACHED (n=" 
                << r.attempt_limits_reached.size() << "):\033[0m\n";
        out.indent();
        i = 1;
        for (const auto& _al : r.attempt_limits_reached) {
          out << out.indentation()
              << "-(" << i << ") [w#" << _al->id << "] seed=" << _al->root_seed << " start-id=" << _al->start_id <<" depth=" << _al->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << _al->active_time << " (|t|=" << _al->total_time << ')';
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
     if (OPTIONS.r_cover && r.completed_covers.size() > 0) {
      out << out.indentation() << "\033[1;4mCOVER(S) COMPLETED (n=" 
                << r.completed_covers.size() << "):\033[0m\n";
        out.indent();
        i = 1;
        for (const auto& _c : r.completed_covers) {
          out << out.indentation()
              << "-(" << i << ") [w#" << _c->id << "] seed=" << _c->root_seed << " start-id=" << _c->start_id <<" depth=" << _c->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << _c->active_time << " (|t|=" << _c->total_time << ')';
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
    if (OPTIONS.report_all && r.max_depths_reached.size() > 0) {
      out << out.indentation() << "\033[1;4mMAX DEPTH(S) REACHED (n=" 
                << r.max_depths_reached.size() << "):\033[0m";
        out.indent();
        i = 1;
        for (const auto& _r : r.max_depths_reached) {
          out << out.nl()
              << "-(" << i++ << ") [w#" << _r->id << "] seed=" << _r->root_seed << " start-id=" << _r->start_id;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << _r->active_time << " (|t|=" << _r->total_time << ')';
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
        for (const auto& a : _a.second) {
          out << out.indentation()
              << "-[w#" << a->id << "] seed=" << a->root_seed << " start-id=" << a->start_id <<" depth=" << a->depth
#ifdef __ROMP__DO_MEASURE
              << " t=" << a->active_time << " (|t|={" << a->total_time << ')'
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
            << "\033[1m-(" << (i++) << ") " << _info.type << " \"" << _info.label << "\":\033[0m "
                "(x"<< _a.second.size() <<")\n";
        out.indent();
        int j = 0;
        for (const auto& a : _a.second) {
          if (j > 2 && not (OPTIONS.report_all || OPTIONS.report_error)) { 
            out << out.indentation() << "-[..] ... " << _a.second.size()-j << " more ...\n"; 
            break;
          }
          out << out.indentation()
              << "-[w#" << a->id << "] seed=" << a->root_seed << " start-id=" << a->start_id <<" depth=" << a->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << a->active_time << " (|t|=" << a->total_time << ')';
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
    if (OPTIONS.report_all && r.unknown_causes.size() > 0) {
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
              << " t=" << _r->active_time << " (|t|=" << _r->total_time << ")\n"
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
        << out.nl() << "\033[1;4mSUMMARY:\033[0m" << out.indent()
        << out.nl() << "       issues found: n=" << color << issues << "\033[0m"
                                          << "  (|n|=" << color << abs_issues << "\033[0m)"
        << out.nl() << "total rules applied: " << r.rules_fired
        << out.nl() << "  avg rules applied: " << std::setprecision(1) << (r.rules_fired/r.size)
#ifndef __ROMP__DO_MEASURE
        << out.nl() << "            runtime: " << r.get_time();
#else
        << out.nl() << "    total walk time: t=" << r.total_walk_active_time << " "
                                          "(|t|=" << r.total_walk_time << ")" 
        << out.nl() << "     mean walk time: mean(t)=" << (r.total_walk_active_time/r.size) << " "
                                           "(mean(|t|)=" << (r.total_walk_time/r.size) << ')' 
        << out.nl() << "     actual runtime: " << r.get_time();
#endif
    out.out << "\n\n" << std::flush;
    return out;
  }
};

/**
 * @brief to generate random seeds for the no of random-walkers
 * rand is generated using UNIX timestamp 
 * @param root_seed the parent seed for generating the random seeds.
 */
unsigned int gen_random_seed(unsigned int &root_seed) {
  return rand_choice(root_seed, 1u, UINT32_MAX);
}

/**
 * @brief generate all startstates of the model. 
 * To do - how to get the size of startstate
 * 
 */
std::vector<RandWalker*> gen_random_walkers(unsigned int root_seed)   {
  std::vector<RandWalker*> rws;
  for(int i=0; i<OPTIONS.walks; i++) {
    rws.push_back(new RandWalker(gen_random_seed(root_seed)));
  }
  return rws;
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
void launch_OpenMP(unsigned int root_seed) {
  std::cout << "\n\t!! NOT YET IMPLEMENTED !!\n" << std::endl; return; //!! temp, remove when finished !! 
  
  // std::vector<RandWalker> rws;
  // try {
  //   rws = gen_random_walkers(rw_count, root_seed, fuel);
  // } catch (const IModelError& ex) {
  //   std::cerr << "\nModel raised an error when initializing our start state(s)!! (message below)\n"
  //             << ex << std::endl;
  // }
  //TODO: launch the random walkers !!
}

/**
 * @brief implementing \c rw_count parallel \c RandWalker "simulations" which has the threads 
 *        and no of random-walkers specified by the user options .
 * @param rw_count the number of \c RandWalker 's to use.
 * @param rand_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 * @param thread_count the max number of threads to use to accomplish all said random walks.
 */
void launch_threads(unsigned int rand_seed) {
  auto rws = gen_random_walkers(rand_seed);
  std::queue<RandWalker*> in_rws(std::deque<RandWalker*>(rws.begin(),rws.end()));
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
    do {
      RandWalker *rw = in_rws.front();
      in_rws.pop(); 
      in_queue.unlock();

      if (rw == nullptr) {
        break;  //DEBUG catch bad data in queue
        // in_queue.lock();  
        // continue;
      };  // just in case might not need (if so remove)

      rw->init();
      while (not rw->is_done())
        rw->sim1Step();
      rw->finalize();

      out_queue.lock();
      out_rws.push(rw);
      ++walks_done;
      out_queue.unlock();

      in_queue.lock();
    } while (in_rws.size() > 0);
    in_queue.unlock();
  };

  ostream_p out(std::cout,0);
  std::vector<std::thread> threads;
  ResultTree summary;
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
}
  

/**
 * @brief (NOT YET IMPLEMENTED) \n
 *        Implementing \c rw_count parallel \c RandWalker "simulations" which has the threads 
 *        and no of random-walkers specified by the user options .
 * @param root_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 */
void launch_CUDA(unsigned int root_seed);


/**
 * @brief (NOT YET IMPLEMENTED) \n
 *        Implementing \c rw_count parallel \c RandWalker "simulations" which has the threads 
 *        and no of random-walkers specified by the user options .
 * @param root_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 */
void launch_SYCL(unsigned int root_seed);


/**
 * @brief (NOT YET IMPLEMENTED) \n
 *        Implementing \c rw_count parallel \c RandWalker "simulations" which has the threads 
 *        and no of random-walkers specified by the user options .
 * @param root_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 */
void launch_OpenMPI(unsigned int root_seed);


/**
 * @brief Launches a single RandWalker (basically jst a simulation).
 * @param rand_seed the random seed
 * @param fuel the max number of rules to try to apply
 */
void launch_single(unsigned int rand_seed) {
  RandWalker* rw = new RandWalker(rand_seed);
  rw->init();
  ResultTree summary;
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


// void Sim1Step(RandWalker::State state, Rule rule, size_t state_count) {
//   for (int s = 0; s < state_count; s++)
//     if (rule.Guard(states[s])) {
//       rule.Run(states[s]);
//       states[i].rule_applied(
//           rule.id); // this keeps track of history and other overhead
//       // These could possibly be parallelized even better for GPU using
//       // shared memory. (not implemented here, could introduce data races)
//       for (int i = 0; i < _ROMP_INVARIANTS_LEN; i++)
//         states[s].valid |= State::INVARIANTS[i](
//             states[i]); // this will need to change after we figure shit out
//       for (int a = 0; a < _ROMP_ASSERTIONS_LEN; a++)
//         states[s].valid |= State::ASSERTIONS[a](
//             states[i]); // this will need to change after we figure shit out
//     }
// }


// << ========================================================================================== >> 
// <<                                         ROMP CODE                                          >> 
// << ========================================================================================== >> 
}
// template<class S, class R>

#pragma endregion romp_rw


#pragma region romp_rw_options

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
 * @brief
 *
 * @date 2022/07/12
 * @version 0.1
 */

#ifndef __romp__GENERATED_CODE
#pragma once
#include "c_prefix.cpp"
#include <functional>
#include <iostream>
#include <string>
#endif

namespace romp {
namespace options {

// input model's path
// extern std::string input_filename;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void print_help() {
  using namespace std;
  Options default_opts;
  // clang-format off
  std::cout << "This is a murphi model checker generated from the romp random walker tool.\n"
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
      result_show_type = true;
    } else if ("-ros" == std::string(argv[i]) || "--omit-state" == std::string(argv[i]) || "--r-omit-state" == std::string(argv[i])) {
      result_emit_state = false;
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
    }
  }
    // modifying values to match complex default values
    if (tab_char == '\t') {
      tab_size = 1;
    }
    
    // check for inconsistent or contradictory options here
    // TODO (OPTIONAL) check OPTIONS to make sure config is valid and output
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
      << "history len: " << _ROMP_HIST_LEN << " \t(config when generating with romp)"<< out.nl()
      << "     report: " << pw_report_str                                           << out.nl()
#ifdef __ROMP__DO_MEASURE
      << " report time: YES \t(config when generating with romp)"
#else
      << " report time: NO  \t(config when generating with romp)"
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

} // namespace options

template<class O>
ojstream<O>& operator << (ojstream<O>& json, const options::Options& opts) noexcept {
  json << "{"
            "\"model\":\"" __model__filepath "\","
            "\"romp-id\":" << ROMP_ID << ","
            "\"root-seed\":\"" << opts.seed_str << "\","
            "\"walks\":" << opts.walks << ","
            "\"threads\":" << opts.threads << ","
            "\"do-single\":" << opts.do_single << ","
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

} // namespace romp

#pragma endregion romp_rw_options


#pragma region romp_rw_main

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
 * @version 0.1
 */


#ifndef __romp__GENERATED_CODE
#include "romp-rw.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "romp-rw-options.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#endif

// #include <unistd.h>
namespace romp { 
  void init_trace_dir() {
    std::string args = "mkdir -p \"" + OPTIONS.get_trace_dir() + "\"";
    int err = system(args.c_str());
    if (err) {
      std::cerr << "\nERROR :: trace directory ``" << OPTIONS.get_trace_dir() << "`` does not exists and could not be created !!\n\n" 
                << std::flush;
      exit(EXIT_FAILURE);
    }
  }
  
  void launch_prompt() {
    ostream_p out(std::cout,0);
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

  ::romp::OPTIONS.parse_args(argc, argv);

  if (not (::romp::OPTIONS.skip_launch_prompt))
    ::romp::launch_prompt();

  if (::romp::OPTIONS.do_trace)
    ::romp::init_trace_dir();

  if (::romp::OPTIONS.do_single)
    ::romp::launch_single(::romp::OPTIONS.rand_seed);

  else
    ::romp::launch_threads(::romp::OPTIONS.rand_seed);
    // ::romp::launch_OpenMP(::romp::OPTIONS.rand_seed);


  return EXIT_SUCCESS;
}

//TODO add in signal intercept for kill/Ctrl-C to gracefully kill threads & output traces etc.

#pragma endregion romp_rw_main
