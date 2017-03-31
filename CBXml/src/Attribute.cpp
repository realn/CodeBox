#include "stdafx.h"
#include "../Attribute.h"

#include "Funcs.h"

#include <CBStr/StringEx.h>

namespace cb {
  static const string g_equal = L"=";

  CXmlAttribute::CXmlAttribute(const string name, const string value) 
    : mName(name)
    , mValue(value)
  {}

  CXmlAttribute::CXmlAttribute() {}

  CXmlAttribute::CXmlAttribute(const CXmlAttribute & other)
    : mName(other.mName)
    , mValue(other.mValue)
  {}

  CXmlAttribute::~CXmlAttribute() {}
  
  const string CXmlAttribute::GetName() const {
    return mName;
  }

  const string CXmlAttribute::GetValue() const {
    return mValue;
  }

  void CXmlAttribute::SetValue(const string val) {
    mValue = val;
  }

  const string CXmlAttribute::ToString() const {
    return mName + g_equal + inQuotes(mValue);
  }

  const size_t CXmlAttribute::Parse(const string & text, const size_t offset) {
    size_t pos = findNonWS(text, offset, g_xmlTagEndList);
    if(subcmp(text, g_xmlTagEndList, pos)) {
      return pos;
    }

    size_t endpos = findWS(text, pos, g_equal);
    if(endpos == string::npos || pos == endpos) {
      return string::npos;
    }

    mName = substrpos(text, pos, endpos);

    pos = findNonWS(text, endpos);
    if(!subcmp(text, g_equal, pos)) {
      return string::npos;
    }

    pos = findNonWS(text, pos + g_equal.length(), g_xmlTagEndList);
    if(subcmp(text, g_xmlTagEndList, pos)) {
      return string::npos;
    }
    
    endpos = findWS(text, pos, g_xmlTagEndList);
    if(endpos == string::npos) {
      return string::npos;
    }

    mValue = stripQuotes(stripWS(substrpos(text, pos, endpos)));
    return endpos;
  }

  void CXmlAttribute::operator=(const CXmlAttribute & other) {
    mName = other.mName;
    mValue = other.mValue;
  }

  void CXmlAttribute::operator=(const string & value) {
    mValue = value;
  }
}