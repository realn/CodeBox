#ifndef __CB_LOG_LOGGER_H__
#define __CB_LOG_LOGGER_H__

#include "Defines.h"
#include "Consts.h"

#include <sstream>
#include <map>
#include <memory>

namespace cb {
  class ILogFormat;

  class CLogger {
  private:
    using StreamItem = std::shared_ptr<ostream>;
    using StreamFormat = std::unique_ptr<ILogFormat>;
    using StreamMap = std::map<StreamItem, StreamFormat>;

    StreamMap mStreamMap;

    static std::weak_ptr<CLogger> mInstance;

  public:
    CLogger();
    ~CLogger();

    void AddStream(std::shared_ptr<ostream> pStream);
    void AddStream(std::shared_ptr<ostream> pStream, std::unique_ptr<ILogFormat> pFormat);
    void ClearStreams();

    void BeginLog(const string& msg = string());
    void LogMsg(const LogLvl level, const string& msg);
    void EndLog(const string& msg = string());

    static void SetInstance(std::shared_ptr<CLogger> logger);
    static std::shared_ptr<CLogger> GetInstance();
  };
}

#endif // !__CB_LOG_LOGGER_H__

