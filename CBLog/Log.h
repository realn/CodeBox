#ifndef __CB_LOG_H__
#define __CB_LOG_H__

#include "Consts.h"
#include "Defines.h"

namespace cb {
  template<typename _Type> cb::string toStr(const _Type& value);

  extern void log(const LogLvl level, const string& msg);

  inline void debug(const string& msg) { log(LogLvl::Debug, msg); }
  inline void info(const string& msg) { log(LogLvl::Info, msg); }
  inline void warn(const string& msg) { log(LogLvl::Warning, msg); }
  inline void error(const string& msg) { log(LogLvl::Error, msg); }
  inline void crit(const string& msg) { log(LogLvl::Critical, msg); }

  namespace detail {
    extern void log(const LogLvl level, const string& fmt, strvector& arglist);

    template<typename _Type, typename ..._Args>
    inline void log(const LogLvl level, 
             const string& fmt, 
             strvector& arglist, 
             _Type& arg0, 
             _Args ... args) {
      arglist.push_back(toStr(arg0));
      log(level, fmt, arglist, args...);
    }
  }

  template<typename ..._Args>
  inline void log(const LogLvl level, const string& fmt, _Args ... args) {
    detail::log(level, fmt, strvector(), args...);
  }

  template<typename ..._Args>
  inline void debug(const string& fmt, _Args ... args) {
    detail::log(LogLvl::Debug, fmt, strvector(), args...);
  }

  template<typename ..._Args>
  inline void info(const string& fmt, _Args ... args) {
    detail::log(LogLvl::Info, fmt, strvector(), args...);
  }

  template<typename ..._Args>
  inline void warn(const string& fmt, _Args ... args) {
    detail::log(LogLvl::Warning, fmt, strvector(), args...);
  }

  template<typename ..._Args>
  inline void error(const string& fmt, _Args ... args) {
    detail::log(LogLvl::Error, fmt, strvector(), args...);
  }

  template<typename ..._Args>
  inline void crit(const string& fmt, _Args ... args) {
    detail::log(LogLvl::Critical, fmt, strvector(), args...);
  }
}

#endif // !__CB_LOG_H__

