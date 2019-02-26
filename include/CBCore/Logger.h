#pragma once

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

    void BeginLog(string const& msg = string());
    void LogMsg(LogLvl const level, string const& msg);
    void EndLog(string const& msg = string());

    static void SetInstance(std::shared_ptr<CLogger> logger);
    static std::shared_ptr<CLogger> GetInstance();
  };
}

