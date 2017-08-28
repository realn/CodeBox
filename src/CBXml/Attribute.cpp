#include "stdafx.h"
#include <CBXml/Attribute.h>

#include "Funcs.h"

#include <CBStr/StringEx.h>

namespace cb {
  using namespace std::string_literals;

  const auto XML_EQUAL = L"="s;
  const auto XML_ATTR_FMT = L"{0}{1}{2}";

  CXmlAttribute::CXmlAttribute() {}

  CXmlAttribute::CXmlAttribute(CXmlAttribute const& other)
    : mName(other.mName)
    , mValue(other.mValue) {}

  CXmlAttribute::CXmlAttribute(CXmlAttribute && other) 
    : mName(std::move(other.mName))
    , mValue(std::move(other.mValue))
  {}

  CXmlAttribute::CXmlAttribute(string const name, string const value)
    : mName(name)
    , mValue(value)
  {}

  CXmlAttribute::~CXmlAttribute() {}
  
  string CXmlAttribute::ToString() const {
    return format(XML_ATTR_FMT, mName, XML_EQUAL, inQuotes(escapeAttrChars(mValue)));
  }

  size_t CXmlAttribute::Parse(string const& text, size_t const offset, cb::ostream& err) {
    // find begining of atrribute name, stop on tag end.
    auto pos = findNonWS(text, offset, XML_TAG_END_LIST);
    if(pos == string::npos) {
      err << L"Attribute name not found while parsing - unexpected end of string." << std::endl;
      return string::npos;
    }
    if(subcmp(text, XML_TAG_END_LIST, pos)) {
      // found tag ending = there are no attributes on this string
      return pos;
    }

    // find the equal sign that should be right after attribute name
    auto endpos = findWS(text, pos, XML_EQUAL);
    if(endpos == string::npos || pos == endpos) {
      err << L"Attribute name ending not found (or any equal sign), unexpected end of string." << std::endl;
      return string::npos;
    }

    mName = substrpos(text, pos, endpos);
    if(mName.empty()) {
      err << L"Empty attribute name, invalid attribute." << std::endl;
    }

    // find the first non whitespace - this should be the attribute value
    pos = findNonWS(text, endpos);
    if(!subcmp(text, XML_EQUAL, pos)) {
      err << L"Cannot find equal sign for attribute " << mName << " value, incomplete attribute." << std::endl;
      return string::npos;
    }

    // find end of attribute value - this should be whitespace (for multiple
    // attributes) or tag ending
    pos = findNonWS(text, pos + XML_EQUAL.length(), XML_TAG_END_LIST);
    if(subcmp(text, XML_TAG_END_LIST, pos)) {
      err << L"Cannot find value begging for attribute " << mName << ", unexpected end of string." << std::endl;
      return string::npos;
    }
    
    endpos = findWS(text, pos, XML_TAG_END_LIST);
    if(endpos == string::npos) {
      err << L"Cannot find value ending for attribute " << mName << ", unexpected end of string." << std::endl;
      return string::npos;
    }

    mValue = unescapeAttrChars(stripQuotes(stripWS(substrpos(text, pos, endpos))));
    return endpos;
  }

  void CXmlAttribute::operator=(CXmlAttribute const& other) {
    mName = other.mName;
    mValue = other.mValue;
  }

  void CXmlAttribute::operator=(CXmlAttribute && other) {
    mName = std::move(other.mName);
    mValue = std::move(other.mValue);
  }
}
