#include "stdafx.h"
#include "../StringFormat.h"

namespace cb {
  const string CXmlStringFormat::DefaultNestingStr = L"  ";
  const string CXmlStringFormat::DefaultNewLineStr = L"\n";

  CXmlStringFormat::CXmlStringFormat(const bool newLines, const bool nesting, const string nestingStr, const string newLineStr) 
    : mNewLines(newLines)
    , mNesting(nesting)
    , mNewLineStr(newLineStr)
    , mNestingLevel(0)
    , mNestingStr(nestingStr)
  {}

  CXmlStringFormat::CXmlStringFormat(const CXmlStringFormat & other)
    : mNewLines(other.mNewLines)
    , mNesting(other.mNesting)
    , mNewLineStr(other.mNewLineStr)
    , mNestingLevel(other.mNestingLevel)
    , mNestingStr(other.mNestingStr)
  {}
}