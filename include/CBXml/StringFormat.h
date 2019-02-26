#pragma once

#include "Defines.h"

namespace cb {
  class CXmlStringFormat {
  public:
    static string const DefaultNestingStr;
    static string const DefaultNewLineStr;

    bool mNewLines;
    bool mNesting;
    string mNewLineStr;
    size_t mNestingLevel;
    string mNestingStr;

    CXmlStringFormat(bool const newLines = false,
                     bool const nesting = false,
                     string const nestingStr = DefaultNestingStr,
                     string const newLineStr = DefaultNewLineStr);
    CXmlStringFormat(CXmlStringFormat const & other);
  };
}

