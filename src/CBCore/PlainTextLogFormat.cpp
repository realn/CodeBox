#include "stdafx.h"
#include <CBCore/PlainTextLogFormat.h>
#include <CBCore/StringConvert.h>

#include <iomanip>
#include <chrono>

using namespace std::chrono_literals;

namespace cb {
  namespace {
    string getTimeStamp() {
      auto timet =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
      auto ltimet = std::tm();
      if (localtime_s(&ltimet, &timet) != 0) {
        return L"[TIME ERROR]";
      }
      auto timestr = std::put_time(&ltimet, L"%Y.%m.%d|%H:%M:%S");

      return toStr(timestr);
    }
  }

  template<>
  string toStr<LogLvl>(LogLvl const& level) {
    switch (level) {
    case LogLvl::Debug: return L"DBG";
    case LogLvl::Info:  return L"INF";
    case LogLvl::Warning: return L"WRN";
    case LogLvl::Error: return L"ERR";
    case LogLvl::Critical:  return L"CRI";
    default:
      return L"???";
    }
  }

  void PlainTextLogFormatter::beginLog(ostream& stream, string const& msg) {
    stream << getTimeStamp() << L" LOG START: " << msg << std::endl;
  }

  void PlainTextLogFormatter::endLog(ostream& stream, string const& msg) {
    stream << getTimeStamp() << L" LOG END" << msg << std::endl;
  }

  void PlainTextLogFormatter::logMsg(ostream& stream, LogLvl const level, string const& msg) {
    stream << getTimeStamp() << L" " << toStr(level) << L" " << msg << std::endl;
  }

}
