#include "stdafx.h"
#include "Funcs.h"

#include <CBXml/StringFormat.h>

#include <map>

#include <CBStr/StringEx.h>

namespace cb {
  const string XML_SPACE = L" ";
  const string XML_QUOTE_CHAR = L"\"";
  const string XML_ESCAPE_CHAR = L"\\";
  const string XML_QUOTE_ESCAPE_CHAR = XML_ESCAPE_CHAR + XML_QUOTE_CHAR;
  const string XML_CDATA_TAG_START = L"<![CDATA[";
  const string XML_CDATA_TAG_END = L"]]/>";
  const string XML_TAG_START = L"<";
  const string XML_TAG_CLOSE_START = L"</";
  const string XML_TAG_END = L">";
  const string XML_TAG_CLOSE_END = L"/>";

  const strvector XML_WHITESPACE_LIST = {L" ", L"\t", L"\n", L"\r"};
  const strvector XML_TAG_END_LIST = {XML_TAG_END, XML_TAG_CLOSE_END};
  const strvector XML_TAG_START_LIST = {XML_TAG_START, XML_TAG_CLOSE_START};

  const strmap XML_REPLACE_MAP =
  {
    {L"<", L"&lt;"},
    {L">", L"&gt;"}
  };



  string escapeChars(const string & text) {
    return replace(text, XML_QUOTE_CHAR, XML_QUOTE_ESCAPE_CHAR);
  }

  string unescapeChars(const string & text) {
    return replace(text, XML_QUOTE_ESCAPE_CHAR, XML_QUOTE_CHAR);
  }

  string escapeXmlChars(const string & text) {
    return replace(text, XML_REPLACE_MAP);
  }

  string unescapeXmlChars(const string & text) {
    return replace(text, XML_REPLACE_MAP, true);
  }

  size_t findWS(const string & text, const size_t offset, const string& also) {
    auto list = {also};
    return findWS(text, offset, list);
  }

  size_t findWS(const string & text, const size_t offset, const strvector& also) {
    auto inQuote = false;
    for(auto i = offset; i < text.length(); i++) {
      if(subcmp(text, XML_ESCAPE_CHAR, i)) {
        i++;
        continue;
      }

      if(subcmp(text, XML_QUOTE_CHAR, i)) {
        inQuote = !inQuote;
      }

      if(inQuote) {
        continue;
      }

      if(subcmp(text, XML_WHITESPACE_LIST, i)) {
        return i;
      }

      if(!also.empty() && subcmp(text, also, i)) {
        return i;
      }
    }
    return string::npos;
  }

  size_t findNonWS(const string & text, const size_t offset, const string& also) {
    auto list = {also};
    return findNonWS(text, offset, list);
  }

  size_t findNonWS(const string & text, const size_t offset, const strvector& also) {
    for(auto i = offset; i < text.length(); i++) {
      if(subcmp(text, XML_ESCAPE_CHAR, i)) {
        i++;
        continue;
      }

      if(!subcmp(text, XML_WHITESPACE_LIST, i)) {
        return i;
      }
      
      if(!also.empty() && subcmp(text, also, i)) {
        return i;
      }
    }
    return string::npos;
  }

  size_t findXml(const string & text, const string & what, const size_t offset) {
    auto inQuote = false;
    for(auto i = offset; i < text.length(); i++) {
      if(subcmp(text, XML_ESCAPE_CHAR, i)) {
        i++;
        continue;
      }

      if(subcmp(text, XML_QUOTE_CHAR, i)) {
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

  size_t findXml(const string & text, const strvector& what, const size_t offset) {
    auto inQuote = false;
    for(auto i = offset; i < text.length(); i++) {
      if(subcmp(text, XML_ESCAPE_CHAR, i)) {
        i++;
        continue;
      }

      if(subcmp(text, XML_QUOTE_CHAR, i)) {
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

  string inQuotes(const string & text) {
    return XML_QUOTE_CHAR + escapeChars(text) + XML_QUOTE_CHAR;
  }

  string stripQuotes(const string & text) {
    if(text.empty())
      return string();

    auto result = text;
    if(subcmp(result, XML_QUOTE_CHAR)) {
      result = substrpos(result, 1);
    }

    if(rsubcmp(result, XML_QUOTE_CHAR, 0) && !rsubcmp(result, XML_QUOTE_ESCAPE_CHAR, 1)) {
      result = substrpos(result, 0, strposrev(result));
    }
    
    return unescapeChars(result);
  }

  string stripWS(const string & text) {
    auto res = string();
    auto escape = false;
    auto quote = false;
    for(auto i = 0u; i < text.length(); i++) {
      if(subcmp(text, XML_ESCAPE_CHAR, i)) {
        res += XML_ESCAPE_CHAR;
        escape = true;
        continue;
      }

      if(!escape) {
        if(subcmp(text, XML_QUOTE_CHAR, i)) {
          quote = !quote;
        }

        if(!quote && subcmp(text, XML_WHITESPACE_LIST, i)) {
          continue;
        }
      }

      res += text[i];
      escape = false;
    }
    return res;
  }

  string genPadding(const CXmlStringFormat & fmt) {
    if(fmt.mNesting) {
      return repeat(fmt.mNestingStr, fmt.mNestingLevel);
    }
    return string();
  }

  string genEnding(const CXmlStringFormat & fmt) {
    if(fmt.mNewLines) {
      return fmt.mNewLineStr;
    }
    return string();
  }
}
