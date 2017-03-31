#ifndef __CB_LOG_H__
#define __CB_LOG_H__

#include "Consts.h"
#include "Defines.h"

namespace cb {
  extern void log(const LogLvl level, const string& msg);

  extern void debug(const string& msg);
  extern void info(const string& msg);
  extern void warn(const string& msg);
  extern void error(const string& msg);
  extern void crit(const string& msg);
}

#endif // !__CB_LOG_H__

