#pragma once

#include "Defines.h"
#include "Consts.h"

#include <sstream>
#include <map>
#include <memory>

namespace cb {
  class ILogFormatter;

  class Logger {
  private:
    using StreamItem = std::shared_ptr<ostream>;
    using StreamFormatter = std::unique_ptr<ILogFormatter>;
    using StreamMap = std::map<StreamItem, StreamFormatter>;

    StreamMap streamMap;

    static std::shared_ptr<Logger> instance;

  public:
    Logger();
    ~Logger();

    void addStream(std::shared_ptr<ostream> stream);
    void addStream(std::shared_ptr<ostream> stream, std::unique_ptr<ILogFormatter> formatter);
    void clearStreams();

    void beginLog(string const& msg = string());
    void logMsg(LogLvl const level, string const& msg);
    void endLog(string const& msg = string());

    static std::shared_ptr<Logger> getInstance();
    static void destroyInstance();
  };
}

