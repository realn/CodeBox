#include "stdafx.h"
#include <CBCore/Log.h>
#include <CBCore/Logger.h>
#include <CBCore/StringConvert.h>

namespace cb {
  void log(LogLvl const level, string const& msg) {
    auto pLog = Logger::getInstance();
    if (pLog) {
      pLog->logMsg(level, msg);
    }
  }

  namespace detail {
    void log(LogLvl const level, string const& fmt, strvector& arglist) {
      cb::log(level, cb::varReplace(fmt, arglist));
    }
  }
}
