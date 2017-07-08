#include "stdafx.h"
#include "../Log.h"
#include "../Logger.h"

#include <CBStr/StringEx.h>

namespace cb {
  void log(LogLvl const level, string const& msg) {
    auto pLog = CLogger::GetInstance();
    if(pLog) {
      pLog->LogMsg(level, msg);
    }
  }

  namespace detail {
    void log(LogLvl const level, string const & fmt, strvector & arglist) {
      cb::log(level, cb::varReplace(fmt, arglist));
    }
  }
}
