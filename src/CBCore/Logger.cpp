#include "stdafx.h"
#include <CBCore/Logger.h>
#include <CBCore/LogFormat.h>
#include <CBCore/PlainTextLogFormat.h>

namespace cb {
  std::weak_ptr<Logger> Logger::instance;

  Logger::~Logger() = default;

  void Logger::addStream(std::shared_ptr<ostream> pStream) {
    if (pStream) {
      streamMap[pStream] = std::make_unique<PlainTextLogFormatter>();
    }
  }

  void Logger::addStream(std::shared_ptr<ostream> pStream,
    std::unique_ptr<ILogFormatter> pFormat) {
    if (pStream) {
      if (pFormat) {
        streamMap[pStream] = std::move(pFormat);
      }
      else {
        streamMap[pStream] = std::make_unique<PlainTextLogFormatter>();
      }
    }
  }

  void Logger::clearStreams() {
    streamMap.clear();
  }

  void Logger::beginLog(string const& msg) {
    for (auto& item : streamMap) {
      item.second->beginLog(*item.first, msg);
    }
  }

  void Logger::logMsg(LogLvl const level, string const& msg) {
    for (auto& item : streamMap) {
      item.second->logMsg(*item.first, level, msg);
    }
  }

  void Logger::endLog(string const& msg) {
    for (auto& item : streamMap) {
      item.second->endLog(*item.first, msg);
    }
  }

  void Logger::setInstance(std::shared_ptr<Logger> logger) {
    instance = logger;
  }

  std::shared_ptr<Logger> Logger::getInstance() {
    auto logger = instance.lock();
    if (!logger) {
      logger = std::make_shared<Logger>();
      instance = logger;
    }
    return logger;
  }
}