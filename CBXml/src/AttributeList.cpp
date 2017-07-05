#include "stdafx.h"
#include "../AttributeList.h"

#include "Funcs.h"

#include <algorithm>
#include <CBStr/StringEx.h>

namespace cb {
  CXmlAttributeList::CXmlAttributeList() {}

  CXmlAttributeList::CXmlAttributeList(const CXmlAttributeList & other)
    : mAttrList(other.mAttrList) {}

  CXmlAttributeList::CXmlAttributeList(CXmlAttributeList && other)
    : mAttrList(std::move(other.mAttrList)) {}

  CXmlAttributeList::~CXmlAttributeList() {}

  void CXmlAttributeList::SetValue(const string & name, const string & value) {
    auto it = find(name);
    if(it == end()) {
      if(!value.empty()) {
        mAttrList.push_back(CXmlAttribute(name, value));
      }
      return;
    }
    if(value.empty()) {
      erase(it);
      return;
    }
    it->SetValue(value);
  }

  string CXmlAttributeList::GetValue(const string & name, const string & defValue) const {
    auto it = find(name);
    if(it == end()) {
      return defValue;
    }
    return it->GetValue();
  }

  inline void CXmlAttributeList::clear() { mAttrList.clear(); }

  CXmlAttributeList::iterator CXmlAttributeList::find(const string & name) {
    auto pred =
      [name](const CXmlAttribute& item) -> auto {return item.GetName() == name; };
    return std::find_if(begin(), end(), pred);
  }

  CXmlAttributeList::const_iterator CXmlAttributeList::find(const string & name) const {
    auto pred =
      [name](const CXmlAttribute& item) -> auto {return item.GetName() == name; };
    return std::find_if(begin(), end(), pred);
  }

  inline CXmlAttributeList::iterator CXmlAttributeList::erase(iterator it) { return mAttrList.erase(it); }

  size_t CXmlAttributeList::Parse(const string & text, const size_t offset) {
    clear();
    auto pos = findNonWS(text, offset, XML_TAG_END_LIST);

    auto attr = CXmlAttribute();
    while(pos != string::npos && !subcmp(text, XML_TAG_END_LIST, pos)) {
      pos = attr.Parse(text, pos);

      if(pos != string::npos) {
        mAttrList.push_back(attr);
      }
      else {
        return false;
      }

      pos = findNonWS(text, pos, XML_TAG_END_LIST);
    }

    return pos;
  }

  string CXmlAttributeList::ToString() const {
    auto list = strvector();
    for(auto& item : *this) {
      list.push_back(item.ToString());
    }
    return join(list, XML_SPACE);
  }

  void CXmlAttributeList::operator=(const CXmlAttributeList & other) {
    mAttrList = other.mAttrList;
  }

  void CXmlAttributeList::operator=(CXmlAttributeList && other) {
    mAttrList = std::move(other.mAttrList);
  }

  string CXmlAttributeList::operator[](const string & name) const {
    auto it = find(name);
    if(it != end()) {
      return it->GetValue();
    }
    throw std::invalid_argument("Invalid index argument for name in xml attribute list.");
  }
}