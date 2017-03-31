#ifndef __CB_XML_STRINGFORMAT_H__
#define __CB_XML_STRINGFORMAT_H__

#include "Defines.h"

namespace cb {
  class CXmlStringFormat {
  public:
    static const string DefaultNestingStr;
    static const string DefaultNewLineStr;

    bool mNewLines;
    bool mNesting;
    string mNewLineStr;
    size_t mNestingLevel;
    string mNestingStr;

    CXmlStringFormat(const bool newLines = false, const bool nesting = false, const string nestingStr = DefaultNestingStr, const string newLineStr = DefaultNewLineStr);
    CXmlStringFormat(const CXmlStringFormat& other);
  };
}

#endif // !__CB_XML_STRINGFORMAT_H__

