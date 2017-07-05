#ifndef __CB_LOG_FORMAT_H__
#define __CB_LOG_FORMAT_H__

#include "Defines.h"
#include "Consts.h"

namespace cb {
  class ILogFormat {
  public:
    ILogFormat() = default;
    virtual ~ILogFormat() = default;

    virtual void BeginLog(ostream& stream, const string& msg) = 0;
    virtual void EndLog(ostream& stream, const string& msg) = 0;
    virtual void LogMsg(ostream& stream, const LogLvl level, const string& msg) = 0;

    ILogFormat(const ILogFormat&) = delete;
    void operator=(const ILogFormat&) = delete;
  };
}

#endif // !__CB_LOG_FORMAT_H__
