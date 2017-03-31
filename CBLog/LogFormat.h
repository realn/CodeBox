#ifndef __CB_LOG_FORMAT_H__
#define __CB_LOG_FORMAT_H__

#include "Defines.h"
#include "Consts.h"

namespace cb {
  class ILogFormat {
  public:
    virtual ~ILogFormat() {}

    virtual void BeginLog(ostream& stream, const string& msg) = 0;
    virtual void EndLog(ostream& stream, const string& msg) = 0;
    virtual void LogMsg(ostream& stream, const LogLvl level, const string& msg) = 0;
  };
}

#endif // !__CB_LOG_FORMAT_H__
