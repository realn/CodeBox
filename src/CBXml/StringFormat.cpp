#include "stdafx.h"
#include <CBXml/StringFormat.h>

namespace cb {
  string const XmlStringFormat::DefaultNestingStr = L"  ";
  string const XmlStringFormat::DefaultNewLineStr = L"\n";

  XmlStringFormat::XmlStringFormat(bool const newLines,
                                   bool const nesting,
                                   string const nestingStr,
                                   string const newLineStr)
    : mNewLines(newLines)
    , mNesting(nesting)
    , mNewLineStr(newLineStr)
    , mNestingLevel(0)
    , mNestingStr(nestingStr) {
  }

  XmlStringFormat::XmlStringFormat(XmlStringFormat const& other)
    : mNewLines(other.mNewLines)
    , mNesting(other.mNesting)
    , mNewLineStr(other.mNewLineStr)
    , mNestingLevel(other.mNestingLevel)
    , mNestingStr(other.mNestingStr) {
  }
}