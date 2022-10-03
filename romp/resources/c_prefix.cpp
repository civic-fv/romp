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
      bool report_show_type = false;
      bool report_emit_state = true;
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

  template<typename ratio1, typename ratio2>
  struct CompareRatios { 
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
    if (CompareRatios<R,std::milli>::dif() > 0.0l // case: lower precision clock
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
        dur -= m; msu = ((msu > _s) ? msu : _s);
      } 
      if (msu > _ms || dur >= microseconds(1)) {
        ms = duration_cast<milliseconds>(dur);
      } else msu = __ms;  // case: measured essentially 0 time ms
    } else /* if (CompareRatios<R,std::milli>::dif() < 0.0l) */ { // case: higher precision clock
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
