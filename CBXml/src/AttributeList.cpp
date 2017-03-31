#include "stdafx.h"
#include "../AttributeList.h"

#include "Funcs.h"

#include <CBStr/StringEx.h>

namespace cb {
  CXmlAttributeList::CXmlAttributeList() {}

  CXmlAttributeList::CXmlAttributeList(const CXmlAttributeList & other) 
    : mAttrList(other.mAttrList)
  {}

  CXmlAttributeList::~CXmlAttributeList() {}

  void CXmlAttributeList::SetValue(const string & name, const string & value) {
    iterator it = Find(name);
    if(it == End()) {
      if(!value.empty()) {
        mAttrList.push_back(CXmlAttribute(name, value));
      }
      return;
    }
    if(value.empty()) {
      Erase(it);
      return;
    }
    it->SetValue(value);
  }

  const string CXmlAttributeList::GetValue(const string & name, const string & defValue) const {
    const_iterator it = Find(name);
    if(it == End()) {
      return defValue;
    }
    return it->GetValue();
  }

  const size_t CXmlAttributeList::GetSize() const {
    return mAttrList.size();
  }

  const bool CXmlAttributeList::IsEmpty() const {
    return mAttrList.empty();
  }

  CXmlAttribute & CXmlAttributeList::Get(const size_t index) {
    return mAttrList[index];
  }

  const CXmlAttribute & CXmlAttributeList::Get(const size_t index) const {
    return mAttrList[index];
  }

  void CXmlAttributeList::Clear() {
    mAttrList.clear();
  }

  CXmlAttributeList::iterator CXmlAttributeList::Begin() {
    return mAttrList.begin();
  }

  CXmlAttributeList::const_iterator CXmlAttributeList::Begin() const {
    return mAttrList.begin();
  }

  CXmlAttributeList::iterator CXmlAttributeList::End() {
    return mAttrList.end();
  }

  CXmlAttributeList::const_iterator CXmlAttributeList::End() const {
    return mAttrList.end();
  }

  CXmlAttributeList::iterator CXmlAttributeList::Find(const string & name) {
    for(iterator it = Begin(); it != End(); it++) {
      if(it->GetName() == name) {
        return it;
      }
    }
    return End();
  }

  CXmlAttributeList::const_iterator CXmlAttributeList::Find(const string & name) const {
    for(const_iterator it = Begin(); it != End(); it++) {
      if(it->GetName() == name) {
        return it;
      }
    }
    return End();
  }

  CXmlAttributeList::iterator CXmlAttributeList::Erase(iterator it) {
    return mAttrList.erase(it);
  }

  const size_t CXmlAttributeList::Parse(const string & text, const size_t offset) {
    Clear();
    size_t pos = findNonWS(text, offset, g_xmlTagEndList);

    while(pos != string::npos && !subcmp(text, g_xmlTagEndList, pos)) {
      CXmlAttribute attr;
      pos = attr.Parse(text, pos);
      
      if(pos != string::npos) {
        mAttrList.push_back(attr);
      }
      else {
        return false;
      }

      pos = findNonWS(text, pos, g_xmlTagEndList);
    }

    return pos;
  }

  const string CXmlAttributeList::ToString() const {
    strvector list;
    for(const_iterator it = Begin(); it != End(); it++) {
      list.push_back(it->ToString());
    }
    return join(list, L" ");
  }

  void CXmlAttributeList::operator=(const CXmlAttributeList & other) {
    mAttrList = other.mAttrList;
  }

  const string CXmlAttributeList::operator[](const string & name) const {
    return Find(name)->GetValue();
  }
}