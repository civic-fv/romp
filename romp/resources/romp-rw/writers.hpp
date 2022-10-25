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
    inline const stream_void nl() { return new_line(); }
    template <typename T>
    inline ostream_p& operator << (const T val);
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
  // template <typename T>
  // inline ostream_p& operator << (ostream_p& out, const T val) { out.out << val; return *this; }  
  template <typename T>
  inline ostream_p& ostream_p::operator << (const T val) { out << val; return *this; }  
  template <>
  inline ostream_p& ostream_p::operator << <std::_Setw>(const std::_Setw val) { _width = val._M_n; return *this; } 
  template <>
  inline ostream_p& ostream_p::operator << <stream_void>(const stream_void val) { return *this; }
  template <>
  inline ostream_p& ostream_p::operator << <bool>(const bool val) { return (*this << ((val) ? "YES" : "NO")); }
  


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
        dur -= m; msu = ((msu > _s) ? msu : _s);
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