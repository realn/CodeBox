#include "stdafx.h"
#include <CBXml/Attribute.h>

#include "Funcs.h"

#include <CBStr/StringEx.h>

namespace cb {
  using namespace std::string_literals;

  const auto XML_EQUAL = L"="s;

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
    return mName + XML_EQUAL + inQuotes(mValue);
  }

  size_t CXmlAttribute::Parse(string const& text, size_t const offset) {
    auto pos = findNonWS(text, offset, XML_TAG_END_LIST);
    if(subcmp(text, XML_TAG_END_LIST, pos)) {
      return pos;
    }

    auto endpos = findWS(text, pos, XML_EQUAL);
    if(endpos == string::npos || pos == endpos) {
      return string::npos;
    }

    mName = substrpos(text, pos, endpos);

    pos = findNonWS(text, endpos);
    if(!subcmp(text, XML_EQUAL, pos)) {
      return string::npos;
    }

    pos = findNonWS(text, pos + XML_EQUAL.length(), XML_TAG_END_LIST);
    if(subcmp(text, XML_TAG_END_LIST, pos)) {
      return string::npos;
    }
    
    endpos = findWS(text, pos, XML_TAG_END_LIST);
    if(endpos == string::npos) {
      return string::npos;
    }

    mValue = stripQuotes(stripWS(substrpos(text, pos, endpos)));
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