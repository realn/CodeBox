#include "stdafx.h"
#include "../PlainTextLogFormat.h"

#include <ctime>
#include <iomanip>

namespace cb {
  const string toStr(const LogLvl level) {
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
    std::time_t t = std::time(nullptr);
    std::tm lt;
    if(localtime_s(&lt, &t) != 0) {
      return L"0000.00.00|00:00:00";
    }

    cb::stringstream ss;
    ss
      << std::setfill(L'0') 
      << std::setw(4) << (1900 + lt.tm_year)
      << L"." << std::setw(2) << (lt.tm_mon + 1)
      << L"." << std::setw(2) << lt.tm_mday
      << L"|" << std::setw(2) << lt.tm_hour
      << L":" << std::setw(2) << lt.tm_min
      << L":" << std::setw(2) << lt.tm_sec;

    return ss.str();
  }

}
