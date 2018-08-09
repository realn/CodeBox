#include "stdafx.h"
#include "CppUnitTest.h"

#include <CBStr/Defines.h>
#include <CBStr/StringEx.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::literals;

template<typename _FuncT, typename _ExpectedT, typename _LineInfoT, typename ..._ArgsT>
void Test(_FuncT& func, const _ExpectedT& expected, cb::string const & msg, _LineInfoT lineInfo, _ArgsT... args) {
  Assert::AreEqual(expected, func(args...), msg.c_str(), lineInfo);
}

namespace Microsoft {
  namespace VisualStudio {
    namespace CppUnitTestFramework {
      template<>
      static std::wstring ToString<cb::strvector>(const cb::strvector& q) {
        auto result = cb::string();
        for(auto& item : q) {
          result += item + L",";
        }
        return result;
      }
      //template<>
      //static std::wstring ToString<cb::charvector>(const cb::charvector& q) {
      //  auto result = cb::string();
      //  for(auto& item : q) {
      //    result += item + L",";
      //  }
      //  return result;
      //}
    }
  }
}

namespace TestCBStr {
  TEST_CLASS(CBStrFunctionsTest) {
public:
  TEST_METHOD(StringCheckFuncsTest) {
    using subcmp1T = bool(const cb::string&, const cb::string&, const size_t);
    using subcmp2T = bool(const cb::string&, const cb::strvector&, const size_t);
    auto val = size_t(2);

    Test(cb::count, val, L"cb::count failed."s, LINE_INFO(), L"baabaabab"s, L"aa"s);
    Test<subcmp1T>(cb::subcmp, true, L"cb::subcmp failed."s, LINE_INFO(), L"zstestzgg"s, L"test"s, 2u);
    Test<subcmp2T>(cb::subcmp, true, L"cb::subcmp list variant failed"s, LINE_INFO(),
                   L"sdfstestsdfs"s, cb::strvector({ L"sets"s, L"test"s }), 4u);
    Test(cb::rsubcmp, true, L"cb::rsubcmp failed"s, LINE_INFO(), L"sdtstesta"s, L"test"s, 5);
    Test(cb::subrcmp, true, L"cb::subrcmp failed"s, LINE_INFO(), L"stestasd"s, L"test"s, 5);
    Test(cb::strposrev, val, L"cb::strposrev failed."s, LINE_INFO(), L"test"s, 1u);
    Test(cb::ends_with, true, L"cb::ends_with failed."s, LINE_INFO(), L"alamasnieg"s, L"snieg"s);
  }
  TEST_METHOD(StringManipFuncsTest) {
    using replace1T = cb::string(const cb::string&, const cb::string&, const cb::string&);
    using replace2T = cb::string(const cb::string&, const cb::strmap&);
    using split1T = cb::strvector(const cb::string&, const cb::string&, const bool);

    Test(cb::substrpos, L"test"s, L"cb::substrpos failed.", LINE_INFO(), L"sdftest", 3, 7);
    Test<replace1T>(cb::replace, L"mokaamokaa"s, L"cb::replace failed."s, LINE_INFO(), L"testatesta"s, L"test"s, L"moka"s);
    Test<replace2T>(cb::replace, L"mokaazulua"s, L"cb::replace map variant failed."s, LINE_INFO(),
                    L"testabawaa"s, cb::strmap({ {L"test"s, L"moka"s}, {L"bawa"s, L"zulu"s} }));
    Test(cb::join, L"somethinginhere"s, L"cb::join failed."s, LINE_INFO(),
         cb::strvector({ L"some"s, L"thing"s, L"in"s, L"here"s }), cb::string());
    Test<split1T>(cb::split, cb::strvector({ L"some"s, L"thing"s, L"in"s, L"here"s }),
                  L"cb::split failed."s, LINE_INFO(), L"someathingaainahere"s, L"a"s, true);
    Test(cb::varReplace, L"someatest"s, L"cb::varReplace failed."s, LINE_INFO(), L"{1}a{0}"s,
         cb::strvector({ L"test"s, L"some"s }));
    Test(cb::repeat, L"isisis"s, L"cb::repeat failed."s, LINE_INFO(), L"is"s, 3);
  }
  TEST_METHOD(StringConvertFuncsTest) {
    Test(cb::toStr<bool>, L"true"s, L"toStr<bool> failed."s, LINE_INFO(), true);
    Test(cb::toStr<int>, L"-1"s, L"toStr<int> failed."s, LINE_INFO(), -1);
    Test(cb::toStr<unsigned>, L"5"s, L"toStr<unsigned> failed."s, LINE_INFO(), 5u);
    Test(cb::toStr<cb::string>, L"test"s, L"toStr<string> failed."s, LINE_INFO(), L"test"s);

    Test(cb::fromStr<bool>, true, L"fromStr<bool> failed."s, LINE_INFO(), L"true"s, bool());
    Test(cb::fromStr<int>, true, L"fromStr<int> failed."s, LINE_INFO(), L"-1"s, int());
    Test(cb::fromStr<unsigned>, true, L"fromStr<unsigned> failed."s, LINE_INFO(), L"5"s, unsigned());
    Test(cb::fromStr<cb::string>, true, L"fromStr<string> failed."s, LINE_INFO(), L"test"s, cb::string());

    Test(cb::toUtf8, "a"s, L"toUtf8 failed.", LINE_INFO(), L"a"s);
    Test(cb::fromUtf8, L"a"s, L"toUtf8 failed.", LINE_INFO(), "a"s);
  }

  TEST_METHOD(StringFormattingTest) {
    auto result = cb::format(L"Some {1} in {0} or {2}"s, L"here"s, 15, -3.f);
    Assert::AreEqual(L"Some 15 in here or -3"s, result, L"cb::format failed.", LINE_INFO());
  }
  };
}