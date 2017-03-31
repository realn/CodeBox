#ifndef __CB_XML_FUNCS_H__
#define __CB_XML_FUNCS_H__

#include "../Defines.h"

namespace cb {
  class CXmlStringFormat;

  extern const string g_quoteChar;
  extern const string g_escapeChar;
  extern const string g_quoteEscapeChar;
  extern const string g_cdataStartTag;
  extern const string g_cdataEndTag;
  extern const string g_xmlTagStart;
  extern const string g_xmlTagCloseStart;
  extern const string g_xmlTagEnd;
  extern const string g_xmlTagCloseEnd;

  extern const strvector g_wsList;
  extern const strvector g_xmlTagEndList;
  extern const strvector g_xmlTagStartList;

  extern const strmap g_xmlReplaceMap;


  extern const string escapeChars(const string& text);
  extern const string unescapeChars(const string& text);

  extern const string escapeXmlChars(const string& text);
  extern const string unescapeXmlChars(const string& text);

  extern const size_t findWS(const string& text, const size_t offset = 0, const string& also = string());
  extern const size_t findWS(const string& text, const size_t offset, const strvector& also);
  extern const size_t findNonWS(const string& text, const size_t offset = 0, const string& also = string());
  extern const size_t findNonWS(const string& text, const size_t offset, const strvector& also);

  extern const size_t findXml(const string& text, const string& what, const size_t offset = 0);
  extern const size_t findXml(const string& text, const strvector& list, const size_t offset = 0);

  extern const string inQuotes(const string& text);
  extern const string stripQuotes(const string& text);

  extern const string stripWS(const string& text);

  extern const string genPadding(const CXmlStringFormat& fmt);
  extern const string genEnding(const CXmlStringFormat& fmt);
}

#endif // !__CB_XML_FUNCS_H__

