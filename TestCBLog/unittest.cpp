#include "stdafx.h"
#include "CppUnitTest.h"

#include <CBStr/StringEx.h>
#include <CBLog/Log.h>
#include <CBLog/Logger.h>
#include <CBLog/PlainTextLogFormat.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::literals;

namespace TestCBLog {
  TEST_CLASS(LoggerUnitTest) {
  private:
    std::shared_ptr<cb::CLogger> mLogger;
    std::shared_ptr<cb::stringstream> mTextStream;

  public:
    TEST_METHOD_INITIALIZE(InitLog) { 
      mLogger = std::make_shared<cb::CLogger>();
      cb::CLogger::SetInstance(mLogger);

      mTextStream = std::make_shared<cb::stringstream>();
      mLogger->AddStream(mTextStream, std::make_unique<cb::CPlainTextLogFormat>());
    }

    TEST_METHOD_CLEANUP(CleanupLog) {
      mLogger.reset();
      mTextStream.reset();
    }

    TEST_METHOD(BasicLoggerTest) {
      cb::log(cb::LogLvl::Info, L"LOG"s);
      cb::log(cb::LogLvl::Info, L"LOG {0} {1} {2}"s, L"test"s, -5, 14.0f);
      cb::info(L"INFO");
      cb::info(L"INFO {1} {0}", -2, 12.0);
      cb::debug(L"DEBUG");
      cb::debug(L"DEBUG {1} {0}", -1, 4.0);
      cb::warn(L"WARNING");
      cb::warn(L"WARNING {1} {0}", -3, 2.0);
      cb::error(L"ERROR");
      cb::error(L"ERROR {1} {0}", -3, 2.0);
      cb::crit(L"CRITICAL");
      cb::crit(L"CRITICAL {1} {0}", -3, 2.0);
      Assert::IsFalse(mTextStream->str().empty(), L"cb::log did not generate output.", LINE_INFO());
      Logger::WriteMessage(mTextStream->str().c_str());
    }
  };
}