#include "stdafx.h"
#include "../Logger.h"
#include "../LogFormat.h"
#include "../PlainTextLogFormat.h"

namespace cb {
  CLogger* CLogger::mInstance = nullptr;

  CLogger::CLogger() {

  }

  CLogger::~CLogger() {
    for(streammap::iterator it = mStreamMap.begin(); it != mStreamMap.end(); it++) {
      delete it->second;
    }
    mStreamMap.clear();

    if(GetInstance() == this) {
      SetInstance(nullptr);
    }
  }

  void CLogger::AddStream(ostream* stream, ILogFormat* format) {
    if(mStreamMap.count(stream) != 0) {
      delete mStreamMap[stream];
    }
    if(format == nullptr) {
      mStreamMap[stream] = new CPlainTextLogFormat();
    }
    else {
      mStreamMap[stream] = format;
    }
  }

  void CLogger::RemoveStream(ostream* stream) {
    streammap::iterator it = mStreamMap.find(stream);
    if(it == mStreamMap.end())
      return;

    delete it->second;
    mStreamMap.erase(it);
  }

  void CLogger::BeginLog(const string & msg) {
    for(streammap::iterator it = mStreamMap.begin(); it != mStreamMap.end(); it++) {
      it->second->BeginLog(*it->first, msg);
    }
  }

  void CLogger::LogMsg(const LogLvl level, const string & msg) {
    for(streammap::iterator it = mStreamMap.begin(); it != mStreamMap.end(); it++) {
      it->second->LogMsg(*it->first, level, msg);
    }
  }

  void CLogger::EndLog(const string & msg) {
    for(streammap::iterator it = mStreamMap.begin(); it != mStreamMap.end(); it++) {
      it->second->EndLog(*it->first, msg);
    }
  }

  void CLogger::SetInstance(CLogger * logger) {
    mInstance = logger;
  }

  CLogger * CLogger::GetInstance() {
    return mInstance;
  }
}