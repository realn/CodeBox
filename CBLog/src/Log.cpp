#include "stdafx.h"
#include "../Log.h"
#include "../Logger.h"

#include <CBStr/StringEx.h>

namespace cb {
  void log(const LogLvl level, const string& msg) {
    auto pLog = CLogger::GetInstance();
    if(pLog) {
      pLog->LogMsg(level, msg);
    }
  }

  namespace detail {
    void log(const LogLvl level, const string & fmt, strvector & arglist) {
      cb::log(level, cb::varReplace(fmt, arglist));
    }
  }
}
