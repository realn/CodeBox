#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  class ILogFormat {
  public:
    ILogFormat() = default;
    virtual ~ILogFormat() = default;

    virtual void BeginLog(ostream& stream, string const& msg) = 0;
    virtual void EndLog(ostream& stream, string const& msg) = 0;
    virtual void LogMsg(ostream& stream, LogLvl const level, string const& msg) = 0;

    ILogFormat(ILogFormat const&) = delete;
    void operator=(ILogFormat const&) = delete;
  };
}
