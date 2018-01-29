#ifndef __CB_XML_FUNCS_H__
#define __CB_XML_FUNCS_H__

#include <CBXml/Defines.h>

namespace cb {
  class CXmlStringFormat;

  extern const string XML_SPACE;
  extern const string XML_QUOTE_CHAR;
  extern const string XML_AMP_CHAR;
  extern const string XML_CDATA_TAG_START;
  extern const string XML_CDATA_TAG_END;

  extern const string XML_TAG_START;
  extern const string XML_TAG_END;
  extern const string XML_TAG_CLOSE_START;
  extern const string XML_TAG_CLOSE_END;

  extern const string XML_ESCAPE_CHAR;
  extern const string XML_ESCAPE_QUOTE_CHAR;
  extern const string XML_ESCAPE_TAG_START;
  extern const string XML_ESCAPE_TAG_END;
  extern const string XML_ESCAPE_AMP_CHAR;

  extern const strvector XML_WHITESPACE_LIST;
  extern const strvector XML_TAG_END_LIST;
  extern const strvector XML_TAG_START_LIST;

  extern string escapeAttrChars(const string& text);
  extern string unescapeAttrChars(const string& text);

  extern string escapeTagChars(const string& text);
  extern string unescapeTagChars(const string& text);

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

