#ifndef __CB_LOG_LOGGER_H__
#define __CB_LOG_LOGGER_H__

#include "Defines.h"
#include "Consts.h"

#include <sstream>
#include <map>

namespace cb {
  class ILogFormat;

  class CLogger {
  private:
    typedef std::map<ostream*, ILogFormat*> streammap;

    streammap mStreamMap;

    static CLogger* mInstance;

  public:
    CLogger();
    ~CLogger();

    void AddStream(ostream* stream, ILogFormat* format = nullptr);
    void RemoveStream(ostream* stream);

    void BeginLog(const string& msg = string());
    void LogMsg(const LogLvl level, const string& msg);
    void EndLog(const string& msg = string());

    static void SetInstance(CLogger* logger);
    static CLogger* GetInstance();
  };
}

#endif // !__CB_LOG_LOGGER_H__

