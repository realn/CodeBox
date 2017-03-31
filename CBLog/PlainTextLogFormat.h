#ifndef __CB_LOG_PLAIN_TEXT_FORMAT_H__
#define __CB_LOG_PLAIN_TEXT_FORMAT_H__

#include "LogFormat.h"

namespace cb {
  class CPlainTextLogFormat :
    public ILogFormat {
  public:
    CPlainTextLogFormat();
    ~CPlainTextLogFormat();

    // Inherited via ILogFormat
    virtual void BeginLog(ostream & stream, const string & msg) override;
    virtual void EndLog(ostream & stream, const string & msg) override;
    virtual void LogMsg(ostream & stream, const LogLvl level, const string & msg) override;

  private:
    string GetTimeStamp() const;
  };
}

#endif // !__CB_LOG_PLAIN_TEXT_FORMAT_H__

