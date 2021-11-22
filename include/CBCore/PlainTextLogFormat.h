#pragma once

#include "LogFormat.h"

namespace cb {
  class PlainTextLogFormatter :
    public ILogFormatter {
  public:
    PlainTextLogFormatter() = default;

    // Inherited via ILogFormat
    void beginLog(ostream& stream, string const& msg) override;
    void endLog(ostream& stream, string const& msg) override;
    void logMsg(ostream& stream, LogLvl const level, string const& msg) override;
  };
}

