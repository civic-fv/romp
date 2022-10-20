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
    void what(std::ostream& out) const noexcept { 
      out << loc << " :: " << msg;
    }
    void to_json(json_file_t& json) const noexcept {  }
    void to_json(json_str_t& json) const noexcept {}
    size_t hash() const noexcept { return reinterpret_cast<size_t>(&(*this)); }
    const std::string& label() const noexcept {  }
    virtual const std::string& quants() const noexcept { return EMPTY_STR; }
    virtual bool is_generic() const noexcept { return true; }
    virtual std::string get_type() const noexcept { return "type"; }
  }


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
  class hash<romp::IModelError> {
    public: size_t operator () (const romp::IModelError& me) const { return me.hash(); }
  };
  template<>
  class equal_to<romp::IModelError> {
    public: size_t operator () (const romp::IModelError& l, const romp::IModelError& r) const { return l.hash() == r.hash(); }
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
