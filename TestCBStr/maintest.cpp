#include "stdafx.h"
#include "CppUnitTest.h"

#include <CBStr/Defines.h>
#include <CBStr/StringEx.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::literals;

namespace TestCBStr {
  TEST_CLASS(CBStrFunctionsTest) {
  public:
    TEST_METHOD(TestCount) {
      auto teststr = L"aaaaabb"s;
      Assert::AreEqual(2u, cb::count(teststr, L"aa"s), L"cb::count(aaaaabb, aa)", LINE_INFO());
      Assert::AreEqual(1u, cb::count(teststr, L"bb"s), L"cb::count(aaaaabb, bb)", LINE_INFO());
    }
    TEST_METHOD(TestSubStrPos) {
      auto teststr = L"Ala has a cat"s;
      Assert::AreEqual(teststr, cb::substrpos(teststr), L"Failed substrpos(text, 0, npos)", LINE_INFO());
      Assert::AreEqual(L"cat"s,
                       cb::substrpos(teststr, teststr.length() - 3),
                       L"Failed substrpos(text, text.len()-3, npos)", LINE_INFO());
      Assert::AreEqual(L"Ala"s,
                       cb::substrpos(teststr, 0, 3),
                       L"Failed substrpos(text, 0, 3)", LINE_INFO());
      Assert::AreEqual(L"has"s,
                       cb::substrpos(teststr, 4, 7),
                       L"Failed substrpos(text, 4, 7)", LINE_INFO());
    }
    TEST_METHOD(TestSubCmp) {
      auto teststr = L"alahasacat"s;
      Assert::AreEqual(true, cb::subcmp(teststr, L"lah"s, 1), L"Failed subcmp(text, what, 1)", LINE_INFO());
      Assert::AreEqual(false, cb::subcmp(teststr, L"has"s, 2), L"Failed subcmp(text, what, 2)", LINE_INFO());
      Assert::AreEqual(true, cb::subcmp(teststr, {L"lah"s, L"has"s}, 1), L"Failed subcmp(text, list, 1)", LINE_INFO());
      Assert::AreEqual(true, cb::subcmp(teststr, {L"lah"s, L"has"s}, 3), L"Failed subcmp(text, list, 3)", LINE_INFO());
    }
    TEST_METHOD(TestRSubCmp) {
      auto teststr = L"alahasacat"s;
      Assert::AreEqual(true, cb::rsubcmp(teststr, L"aca"s, 4), L"Failed subcmp(text, what, 1)", LINE_INFO());
      Assert::AreEqual(false, cb::rsubcmp(teststr, L"cat"s, 4), L"Failed subcmp(text, what, 2)", LINE_INFO());
    }
    TEST_METHOD(TestSubRCmp) {
      auto teststr = L"alahasacat"s;
      Assert::AreEqual(true, cb::subrcmp(teststr, L"ala"s, 3), L"Failed subcmp(text, what, 1)", LINE_INFO());
      Assert::AreEqual(false, cb::subrcmp(teststr, L"ala"s, 0), L"Failed subcmp(text, what, 2)", LINE_INFO());
    }
    TEST_METHOD(TestReplace) {
      auto teststr = L"test"s;
      Assert::AreEqual(L"tero"s, cb::replace(teststr, L"st"s, L"ro"s), L"Failed replace(text, what, with)", LINE_INFO());
      Assert::AreEqual(L"tero"s, cb::replace(teststr, L"st"s, L"ro"s), L"Failed replace(text, what, with)", LINE_INFO());
    }
  };
}