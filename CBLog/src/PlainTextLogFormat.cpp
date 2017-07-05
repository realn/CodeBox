#include "stdafx.h"
#include "../PlainTextLogFormat.h"
#include <CBStr/Defines.h>

#include <iomanip>
#include <chrono>

using namespace std::chrono_literals;

namespace cb {
  template<>
  string toStr<LogLvl>(const LogLvl& level) {
    switch(level) {
    case LogLvl::Debug: return L"DBG";
    case LogLvl::Info:  return L"INF";
    case LogLvl::Warning: return L"WRN";
    case LogLvl::Error: return L"ERR";
    case LogLvl::Critical:  return L"CRI";
    default:
      return L"???";
    }
  }

  CPlainTextLogFormat::CPlainTextLogFormat() {}

  CPlainTextLogFormat::~CPlainTextLogFormat() {}

  void CPlainTextLogFormat::BeginLog(ostream & stream, const string & msg) {
    stream << GetTimeStamp() << L" LOG START" << std::endl;
  }

  void CPlainTextLogFormat::EndLog(ostream & stream, const string & msg) {
    stream << GetTimeStamp() << L" LOG END" << std::endl;
  }

  void CPlainTextLogFormat::LogMsg(ostream & stream, const LogLvl level, const string & msg) {
    stream << GetTimeStamp() << L" " << toStr(level) << L" " << msg << std::endl;
  }

  string CPlainTextLogFormat::GetTimeStamp() const {
    auto timet = 
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto ltimet = std::tm();
    if(localtime_s(&ltimet, &timet) != 0) {
      return L"[TIME ERROR]";
    }
    auto timestr = std::put_time(&ltimet, L"%Y.%m.%d|%H:%M:%S");

    return toStr(timestr);
  }
}
