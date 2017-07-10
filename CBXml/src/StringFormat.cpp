#include "stdafx.h"
#include "../StringFormat.h"

namespace cb {
  string const CXmlStringFormat::DefaultNestingStr = L"  ";
  string const CXmlStringFormat::DefaultNewLineStr = L"\n";

  CXmlStringFormat::CXmlStringFormat(bool const newLines,
                                     bool const nesting, 
                                     string const nestingStr,
                                     string const newLineStr)
    : mNewLines(newLines)
    , mNesting(nesting)
    , mNewLineStr(newLineStr)
    , mNestingLevel(0)
    , mNestingStr(nestingStr)
  {}

  CXmlStringFormat::CXmlStringFormat(CXmlStringFormat const & other)
    : mNewLines(other.mNewLines)
    , mNesting(other.mNesting)
    , mNewLineStr(other.mNewLineStr)
    , mNestingLevel(other.mNestingLevel)
    , mNestingStr(other.mNestingStr)
  {}
}