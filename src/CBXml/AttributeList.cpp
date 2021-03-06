#include "stdafx.h"
#include "Funcs.h"

#include <algorithm>

#include <CBCore/StringConvert.h>
#include <CBCore/StringFunctions.h>
#include <CBXml/AttributeList.h>

namespace cb {
  CXmlAttributeList::CXmlAttributeList() {}

  CXmlAttributeList::CXmlAttributeList(CXmlAttributeList const & other)
    : mAttrList(other.mAttrList) {}

  CXmlAttributeList::CXmlAttributeList(CXmlAttributeList && other)
    : mAttrList(std::move(other.mAttrList)) {}

  CXmlAttributeList::~CXmlAttributeList() {}

  void CXmlAttributeList::SetValue(string const & name, string const & value) {
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

  string CXmlAttributeList::GetValue(string const & name, string const & defValue) const {
    auto it = find(name);
    if(it == end()) {
      return defValue;
    }
    return it->GetValue();
  }

  inline void CXmlAttributeList::clear() { mAttrList.clear(); }

  CXmlAttributeList::iterator CXmlAttributeList::find(string const & name) {
    auto pred =
      [name](const CXmlAttribute& item) -> auto {return item.GetName() == name; };
    return std::find_if(begin(), end(), pred);
  }

  CXmlAttributeList::const_iterator CXmlAttributeList::find(string const & name) const {
    auto pred =
      [name](const CXmlAttribute& item) -> auto {return item.GetName() == name; };
    return std::find_if(begin(), end(), pred);
  }

  inline CXmlAttributeList::iterator CXmlAttributeList::erase(iterator it) { return mAttrList.erase(it); }

  size_t CXmlAttributeList::Parse(string const & text, size_t const offset, cb::ostream& err) {
    clear();
    auto pos = findNonWS(text, offset, XML_TAG_END_LIST);
    while(pos != string::npos && !subcmp(text, XML_TAG_END_LIST, pos)) {
      auto attr = CXmlAttribute();
      pos = attr.Parse(text, pos);

      if(pos != string::npos) {
        mAttrList.push_back(attr);
      }
      else {
        err << L"Failed to parse attribute list - some error on string." << std::endl;
        return string::npos;
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

  void CXmlAttributeList::operator=(CXmlAttributeList const& other) {
    mAttrList = other.mAttrList;
  }

  void CXmlAttributeList::operator=(CXmlAttributeList && other) {
    mAttrList = std::move(other.mAttrList);
  }

  CXmlAttribute& CXmlAttributeList::operator[](string const& name) { 
    auto it = find(name);
    if(it != end()) {
      return *it;
    }
    mAttrList.push_back(CXmlAttribute(name));
    return *mAttrList.rbegin(); 
  }

}