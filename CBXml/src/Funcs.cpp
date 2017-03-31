#include "stdafx.h"
#include "Funcs.h"

#include "../StringFormat.h"

#include <map>

#include <CBStr/StringEx.h>

namespace cb {
  const string g_quoteChar = L"\"";
  const string g_escapeChar = L"\\";
  const string g_quoteEscapeChar = g_escapeChar + g_quoteChar;
  const string g_cdataStartTag = L"<![CDATA[";
  const string g_cdataEndTag = L"]]/>";
  const string g_xmlTagStart = L"<";
  const string g_xmlTagCloseStart = L"</";
  const string g_xmlTagEnd = L">";
  const string g_xmlTagCloseEnd = L"/>";

  const strvector g_wsList = {L" ", L"\t", L"\n", L"\r"};
  const strvector g_xmlTagEndList = {g_xmlTagEnd, g_xmlTagCloseEnd};
  const strvector g_xmlTagStartList = {g_xmlTagStart, g_xmlTagCloseStart};

  const strmap g_xmlReplaceMap =
  {
    std::make_pair(L"<", L"&lt;"),
    std::make_pair(L">", L"&gt;")
  };



  const string escapeChars(const string & text) {
    return replace(text, g_quoteChar, g_quoteEscapeChar);
  }

  const string unescapeChars(const string & text) {
    return replace(text, g_quoteEscapeChar, g_quoteChar);
  }

  const string escapeXmlChars(const string & text) {
    return replace(text, g_xmlReplaceMap);
  }

  const string unescapeXmlChars(const string & text) {
    return replace(text, g_xmlReplaceMap, true);
  }

  const size_t findWS(const string & text, const size_t offset, const string& also) {
    strvector list = {also};
    return findWS(text, offset, list);
  }

  const size_t findWS(const string & text, const size_t offset, const strvector& also) {
    bool inQuote = false;
    for(size_t i = offset; i < text.length(); i++) {
      if(subcmp(text, g_escapeChar, i)) {
        i++;
        continue;
      }

      if(subcmp(text, g_quoteChar, i)) {
        inQuote = !inQuote;
      }

      if(inQuote) {
        continue;
      }

      if(subcmp(text, g_wsList, i)) {
        return i;
      }

      if(!also.empty() && subcmp(text, also, i)) {
        return i;
      }
    }
    return string::npos;
  }

  const size_t findNonWS(const string & text, const size_t offset, const string& also) {
    strvector list = {also};
    return findNonWS(text, offset, list);
  }

  const size_t findNonWS(const string & text, const size_t offset, const strvector& also) {
    //bool inQuote = false;
    for(size_t i = offset; i < text.length(); i++) {
      if(subcmp(text, g_escapeChar, i)) {
        i++;
        continue;
      }

      //if(subcmp(text, g_quoteChar, i)) {
      //  inQuote = !inQuote;
      //}

      //if(inQuote) {
      //  continue;
      //}

      if(!subcmp(text, g_wsList, i)) {
        return i;
      }
      
      if(!also.empty() && subcmp(text, also, i)) {
        return i;
      }
    }
    return string::npos;
  }

  const size_t findXml(const string & text, const string & what, const size_t offset) {
    bool inQuote = false;
    for(size_t i = offset; i < text.length(); i++) {
      if(subcmp(text, g_escapeChar, i)) {
        i++;
        continue;
      }

      if(subcmp(text, g_quoteChar, i)) {
        inQuote = !inQuote;
      }

      if(inQuote) {
        continue;
      }

      if(subcmp(text, what, i)) {
        return i;
      }
    }
    return string::npos;
  }

  const size_t findXml(const string & text, const strvector& what, const size_t offset) {
    bool inQuote = false;
    for(size_t i = offset; i < text.length(); i++) {
      if(subcmp(text, g_escapeChar, i)) {
        i++;
        continue;
      }

      if(subcmp(text, g_quoteChar, i)) {
        inQuote = !inQuote;
      }

      if(inQuote) {
        continue;
      }

      if(subcmp(text, what, i)) {
        return i;
      }
    }
    return string::npos;
  }

  const string inQuotes(const string & text) {
    return g_quoteChar + escapeChars(text) + g_quoteChar;
  }

  const string stripQuotes(const string & text) {
    if(text.empty())
      return string();

    string result = text;
    if(subcmp(result, g_quoteChar)) {
      result = substrpos(result, 1);
    }

    if(rsubcmp(result, g_quoteChar, 0) && !rsubcmp(result, g_quoteEscapeChar, 1)) {
      result = substrpos(result, 0, strlastpos(result));
    }
    
    return unescapeChars(result);
  }

  const string stripWS(const string & text) {
    string res;
    bool escape = false;
    bool quote = false;
    for(size_t i = 0; i < text.length(); i++) {
      if(subcmp(text, g_escapeChar, i)) {
        res += g_escapeChar;
        escape = true;
        continue;
      }

      if(!escape) {
        if(subcmp(text, g_quoteChar, i)) {
          quote = !quote;
        }

        if(!quote && subcmp(text, g_wsList, i)) {
          continue;
        }
      }

      res += text[i];
      escape = false;
    }
    return res;
  }

  const string genPadding(const CXmlStringFormat & fmt) {
    if(fmt.mNesting) {
      return repeat(fmt.mNestingStr, fmt.mNestingLevel);
    }
    return string();
  }

  const string genEnding(const CXmlStringFormat & fmt) {
    if(fmt.mNewLines) {
      return fmt.mNewLineStr;
    }
    return string();
  }


}
