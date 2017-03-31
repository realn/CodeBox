#include "stdafx.h"
#include "../Log.h"
#include "../Logger.h"

namespace cb {
  void log(const LogLvl level, const string& msg) {
    CLogger* pLog = CLogger::GetInstance();
    if(pLog) {
      pLog->LogMsg(level, msg);
    }
  }

  void debug(const string& msg) {
    log(LogLvl::Debug, msg);
  }

  void info(const string& msg) {
    log(LogLvl::Info, msg);
  }

  void warn(const string& msg) {
    log(LogLvl::Warning, msg);
  }

  void error(const string& msg) {
    log(LogLvl::Error, msg);
  }

  void crit(const string& msg) {
    log(LogLvl::Critical, msg);
  }
}