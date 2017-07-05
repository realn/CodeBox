#ifndef __CB_XML_FUNCS_H__
#define __CB_XML_FUNCS_H__

#include "../Defines.h"

namespace cb {
  class CXmlStringFormat;

  extern const string XML_SPACE;
  extern const string XML_QUOTE_CHAR;
  extern const string XML_ESCAPE_CHAR;
  extern const string XML_QUOTE_ESCAPE_CHAR;
  extern const string XML_CDATA_TAG_START;
  extern const string XML_CDATA_TAG_END;
  extern const string XML_TAG_START;
  extern const string XML_TAG_END;
  extern const string XML_TAG_CLOSE_START;
  extern const string XML_TAG_CLOSE_END;

  extern const strvector XML_WHITESPACE_LIST;
  extern const strvector XML_TAG_END_LIST;
  extern const strvector XML_TAG_START_LIST;

  extern const strmap XML_REPLACE_MAP;

  extern string escapeChars(const string& text);
  extern string unescapeChars(const string& text);

  extern string escapeXmlChars(const string& text);
  extern string unescapeXmlChars(const string& text);

  extern size_t findWS(const string& text, const size_t offset = 0, const string& also = string());
  extern size_t findWS(const string& text, const size_t offset, const strvector& also);
  extern size_t findNonWS(const string& text, const size_t offset = 0, const string& also = string());
  extern size_t findNonWS(const string& text, const size_t offset, const strvector& also);

  extern size_t findXml(const string& text, const string& what, const size_t offset = 0);
  extern size_t findXml(const string& text, const strvector& list, const size_t offset = 0);

  extern string inQuotes(const string& text);
  extern string stripQuotes(const string& text);

  extern string stripWS(const string& text);

  extern string genPadding(const CXmlStringFormat& fmt);
  extern string genEnding(const CXmlStringFormat& fmt);
}

#endif // !__CB_XML_FUNCS_H__

