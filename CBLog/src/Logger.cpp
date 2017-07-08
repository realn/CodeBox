#include "stdafx.h"
#include "../Logger.h"
#include "../LogFormat.h"
#include "../PlainTextLogFormat.h"

namespace cb {
  std::weak_ptr<CLogger> CLogger::mInstance;

  CLogger::CLogger() {}

  CLogger::~CLogger() {}

  void CLogger::AddStream(std::shared_ptr<ostream> pStream) {
    if(pStream) {
      mStreamMap[pStream] = std::make_unique<CPlainTextLogFormat>();
    }
  }

  void CLogger::AddStream(std::shared_ptr<ostream> pStream, 
                          std::unique_ptr<ILogFormat> pFormat) {
    if(pStream) {
      if(pFormat) {
        mStreamMap[pStream] = std::move(pFormat);
      }
      else {
        mStreamMap[pStream] = std::make_unique<CPlainTextLogFormat>();
      }
    }
  }

  void CLogger::ClearStreams() {
    mStreamMap.clear();
  }

  void CLogger::BeginLog(string const & msg) {
    for(auto& item : mStreamMap) {
      item.second->BeginLog(*item.first, msg);
    }
  }

  void CLogger::LogMsg(LogLvl const level, string const & msg) {
    for(auto& item : mStreamMap) {
      item.second->LogMsg(*item.first, level, msg);
    }
  }

  void CLogger::EndLog(string const & msg) {
    for(auto& item : mStreamMap) {
      item.second->EndLog(*item.first, msg);
    }
  }

  void CLogger::SetInstance(std::shared_ptr<CLogger> logger) {
    mInstance = logger;
  }

  std::shared_ptr<CLogger> CLogger::GetInstance() {
    return mInstance.lock();
  }
}