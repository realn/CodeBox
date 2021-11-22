#include "stdafx.h"
#include "Funcs.h"

#include <map>
#include <CBCore/StringFunctions.h>
#include <CBXml/StringFormat.h>

namespace cb {
  const string XML_SPACE = L" ";
  const string XML_QUOTE_CHAR = L"\"";
  const string XML_AMP_CHAR = L"&"s;
  const string XML_CDATA_TAG_START = L"<![CDATA[";
  const string XML_CDATA_TAG_END = L"]]/>";
  const string XML_TAG_START = L"<";
  const string XML_TAG_CLOSE_START = L"</";
  const string XML_TAG_END = L">";
  const string XML_TAG_CLOSE_END = L"/>";

  const string XML_ESCAPE_CHAR = L"\\";
  const string XML_ESCAPE_QUOTE_CHAR = L"&quot;"s;
  const string XML_ESCAPE_TAG_START = L"&lt;"s;
  const string XML_ESCAPE_TAG_END = L"&gt;"s;
  const string XML_ESCAPE_AMP_CHAR = L"&amp;"s;

  const strvector XML_WHITESPACE_LIST = { L" ", L"\t", L"\n", L"\r" };
  const strvector XML_TAG_END_LIST = { XML_TAG_END, XML_TAG_CLOSE_END };
  const strvector XML_TAG_START_LIST = { XML_TAG_START, XML_TAG_CLOSE_START };

  auto const XML_ESCAPE_CHAR_MAP = strmap{
    {XML_TAG_START, XML_ESCAPE_TAG_START},
    {XML_TAG_END, XML_ESCAPE_TAG_END},
    {XML_QUOTE_CHAR, XML_ESCAPE_QUOTE_CHAR},
    {XML_AMP_CHAR, XML_ESCAPE_AMP_CHAR},
    {XML_ESCAPE_CHAR, XML_ESCAPE_CHAR + XML_ESCAPE_CHAR}
  };

  auto const XML_ESCAPE_CHAR_MAP_FLIP = mapflip(XML_ESCAPE_CHAR_MAP);

  string escapeAttrChars(const string& text) {
    return replace_by_char(text, XML_ESCAPE_CHAR_MAP);
  }

  string unescapeAttrChars(const string& text) {
    return replace_by_char(text, XML_ESCAPE_CHAR_MAP_FLIP);
  }

  string escapeTagChars(const string& text) {
    return replace_by_char(text, XML_ESCAPE_CHAR_MAP);
  }

  string unescapeTagChars(const string& text) {
    return replace_by_char(text, XML_ESCAPE_CHAR_MAP_FLIP);
  }

  size_t findWS(const string& text, const size_t offset, const string& also) {
    auto list = { also };
    return findWS(text, offset, list);
  }

  size_t findWS(const string& text, const size_t offset, const strvector& also) {
    auto inQuote = false;
    for (auto i = offset; i < text.length(); i++) {
      if (subcmp(text, XML_ESCAPE_CHAR, i)) {
        i++;
        continue;
      }

      if (subcmp(text, XML_QUOTE_CHAR, i)) {
        inQuote = !inQuote;
      }

      if (inQuote) {
        continue;
      }

      if (subcmp(text, XML_WHITESPACE_LIST, i)) {
        return i;
      }

      if (!also.empty() && subcmp(text, also, i)) {
        return i;
      }
    }
    return string::npos;
  }

  size_t findNonWS(const string& text, const size_t offset, const string& also) {
    auto list = { also };
    return findNonWS(text, offset, list);
  }

  size_t findNonWS(const string& text, const size_t offset, const strvector& also) {
    for (auto i = offset; i < text.length(); i++) {
      if (subcmp(text, XML_ESCAPE_CHAR, i)) {
        i++;
        continue;
      }

      if (!subcmp(text, XML_WHITESPACE_LIST, i)) {
        return i;
      }

      if (!also.empty() && subcmp(text, also, i)) {
        return i;
      }
    }
    return string::npos;
  }

  size_t findXml(const string& text, const string& what, const size_t offset) {
    auto inQuote = false;
    for (auto i = offset; i < text.length(); i++) {
      if (subcmp(text, XML_ESCAPE_CHAR, i)) {
        i++;
        continue;
      }

      if (subcmp(text, XML_QUOTE_CHAR, i)) {
        inQuote = !inQuote;
      }

      if (inQuote) {
        continue;
      }

      if (subcmp(text, what, i)) {
        return i;
      }
    }
    return string::npos;
  }

  size_t findXml(const string& text, const strvector& what, const size_t offset) {
    auto inQuote = false;
    for (auto i = offset; i < text.length(); i++) {
      if (subcmp(text, XML_ESCAPE_CHAR, i)) {
        i++;
        continue;
      }

      if (subcmp(text, XML_QUOTE_CHAR, i)) {
        inQuote = !inQuote;
      }

      if (inQuote) {
        continue;
      }

      if (subcmp(text, what, i)) {
        return i;
      }
    }
    return string::npos;
  }

  string inQuotes(const string& text) {
    return XML_QUOTE_CHAR + text + XML_QUOTE_CHAR;
  }

  string stripQuotes(const string& text) {
    if (text.empty())
      return string();

    auto result = string();
    auto pos = size_t(0);
    while (pos < text.length()) {
      if (subcmp(text, XML_ESCAPE_CHAR, pos)) {
        result += text.substr(pos, 2);
        pos += 2;
        continue;
      }
      if (subcmp(text, XML_QUOTE_CHAR, pos)) {
        pos++;
        continue;
      }

      result += text[pos];
      pos++;
    }
    return result;
  }

  string stripWS(const string& text) {
    auto res = string();
    auto escape = false;
    auto quote = false;
    for (auto i = 0u; i < text.length(); i++) {
      if (subcmp(text, XML_ESCAPE_CHAR, i)) {
        res += XML_ESCAPE_CHAR;
        escape = true;
        continue;
      }

      if (!escape) {
        if (subcmp(text, XML_QUOTE_CHAR, i)) {
          quote = !quote;
        }

        if (!quote && subcmp(text, XML_WHITESPACE_LIST, i)) {
          continue;
        }
      }

      res += text[i];
      escape = false;
    }
    return res;
  }

  string genPadding(const XmlStringFormat& fmt) {
    if (fmt.mNesting) {
      return repeat(fmt.mNestingStr, fmt.mNestingLevel);
    }
    return string();
  }

  string genEnding(const XmlStringFormat& fmt) {
    if (fmt.mNewLines) {
      return fmt.mNewLineStr;
    }
    return string();
  }
}
