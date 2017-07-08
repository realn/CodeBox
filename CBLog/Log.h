#ifndef __CB_LOG_H__
#define __CB_LOG_H__

#include "Consts.h"
#include "Defines.h"

namespace cb {
  template<typename _Type> cb::string toStr(const _Type& value);

  extern void log(LogLvl const level, string const& msg);

  inline void debug(string const& msg) { log(LogLvl::Debug, msg); }
  inline void info(string const& msg) { log(LogLvl::Info, msg); }
  inline void warn(string const& msg) { log(LogLvl::Warning, msg); }
  inline void error(string const& msg) { log(LogLvl::Error, msg); }
  inline void crit(string const& msg) { log(LogLvl::Critical, msg); }

  namespace detail {
    extern void log(LogLvl const level, string const& fmt, strvector& arglist);

    template<typename _Type, typename ..._Args>
    inline void log(LogLvl const level, 
             string const& fmt, 
             strvector& arglist, 
             _Type& arg0, 
             _Args ... args) {
      arglist.push_back(toStr(arg0));
      log(level, fmt, arglist, args...);
    }
  }

  template<typename ..._Args>
  inline void log(LogLvl const level, string const& fmt, _Args ... args) {
    detail::log(level, fmt, strvector(), args...);
  }

  template<typename ..._Args>
  inline void debug(string const& fmt, _Args ... args) {
    detail::log(LogLvl::Debug, fmt, strvector(), args...);
  }

  template<typename ..._Args>
  inline void info(string const& fmt, _Args ... args) {
    detail::log(LogLvl::Info, fmt, strvector(), args...);
  }

  template<typename ..._Args>
  inline void warn(string const& fmt, _Args ... args) {
    detail::log(LogLvl::Warning, fmt, strvector(), args...);
  }

  template<typename ..._Args>
  inline void error(string const& fmt, _Args ... args) {
    detail::log(LogLvl::Error, fmt, strvector(), args...);
  }

  template<typename ..._Args>
  inline void crit(string const& fmt, _Args ... args) {
    detail::log(LogLvl::Critical, fmt, strvector(), args...);
  }
}

#endif // !__CB_LOG_H__

