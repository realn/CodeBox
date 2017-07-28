#include "stdafx.h"
#include "CppUnitTest.h"

#include <CBStr/StringEx.h>
#include <CBIO/Path.h>
#include <CBIO/File.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::literals;

template<typename _FuncT, typename _ExpectedT, typename _LineInfoT, typename ..._ArgsT>
void Test(_FuncT& func, const _ExpectedT& expected, const cb::string& msg, _LineInfoT lineInfo, _ArgsT... args) {
  Assert::AreEqual(expected, func(args...), msg.c_str(), lineInfo);
}

namespace Microsoft {
  namespace VisualStudio {
    namespace CppUnitTestFramework {
      template<>
      static std::wstring ToString<cb::bytevector>(const cb::bytevector& q) {
        auto result = cb::string();
        for(auto& item : q) {
          result += L"[" + cb::toStr(item) + L"]";
        }
        return result;
      }
      template<>
      static std::wstring ToString<std::streamsize>(const std::streamsize& q) {
        return cb::toStr(q);
      }
    }
  }
}


namespace TestCBIO {
  TEST_CLASS(CBIOUnitTest) {
  public:
    TEST_METHOD(PathToolsTest) {
      Test(cb::filenameextpos, 5u, L"cb::filenameextpos failed."s, LINE_INFO(), L"test.ext");
      Test(cb::filenameext, L"ext"s, L"cb::filenameext"s, LINE_INFO(), L"test.ext");
      Test(cb::makefilename, L"test.ext"s, L"cb::makefilename failed."s, LINE_INFO(), L"test", L"ext");
      Test(cb::clearpath, L"C:/test/tset"s, L"cb::clearpath failed."s, LINE_INFO(), L"C:\\test///tset");
      Test(cb::pathnamepos, 8u, L"cb::pathnamepos"s, LINE_INFO(), L"C:/test/tset");
      Test(cb::pathname, L"tset"s, L"cb::pathname failed."s, LINE_INFO(), L"C:/test/tset");
      Test(cb::pathbase, L"C:/test"s, L"cb::pathbase failed."s, LINE_INFO(), L"C:/test/tset");
      Test(cb::makepath, L"C:/test/tset"s, L"cb::makepath failed."s, LINE_INFO(), L"C:/test/", L"/tset");
    }
    TEST_METHOD(FileToolsTest) {
      auto data = cb::bytevector({0, 1, 2});
      auto text = L"Wójcik"s;

      Assert::IsTrue(cb::writefile(L"test1.dat", data), L"cb::writefile failed.", LINE_INFO());
      Assert::IsTrue(cb::writetextfileutf16(L"test2.txt", text), L"cb::writetextfileutf16 failed.", LINE_INFO());
      Assert::IsTrue(cb::writetextfileutf8(L"test3.txt", text), L"cb::writetextfileutf8 failed.", LINE_INFO());
      Assert::IsTrue(cb::fileexists(L"test1.dat"), L"cb::fileexists failed.", LINE_INFO());
      Assert::AreEqual(3ll, cb::filesize(L"test1.dat"), L"cb::filesize failed.", LINE_INFO());
      Assert::AreEqual(data, cb::readfile(L"test1.dat"), L"cb::readfile failed.", LINE_INFO());
      Assert::AreEqual(text, cb::readtextfileutf16(L"test2.txt"), L"cb::readtextfileutf16 failed.", LINE_INFO());
      Assert::AreEqual(text, cb::readtextfileutf8(L"test3.txt"), L"cb::readtextfileutf8 failed.", LINE_INFO());
    }
  };
}