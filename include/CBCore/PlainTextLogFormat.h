#pragma once

#include "LogFormat.h"

namespace cb {
  class CPlainTextLogFormat :
    public ILogFormat {
  public:
    CPlainTextLogFormat();
    virtual ~CPlainTextLogFormat();

    // Inherited via ILogFormat
    virtual void BeginLog(ostream & stream, string const & msg) override;
    virtual void EndLog(ostream & stream, string const & msg) override;
    virtual void LogMsg(ostream & stream, LogLvl const level, string const & msg) override;

  private:
    string GetTimeStamp() const;
  };
}

