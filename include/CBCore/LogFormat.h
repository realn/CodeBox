#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  class ILogFormatter {
  public:
    virtual ~ILogFormatter() = default;

    virtual void beginLog(ostream& stream, string const& msg) = 0;
    virtual void endLog(ostream& stream, string const& msg) = 0;
    virtual void logMsg(ostream& stream, LogLvl const level, string const& msg) = 0;
  };
}
