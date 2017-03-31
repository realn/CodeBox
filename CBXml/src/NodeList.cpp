#include "stdafx.h"
#include "../NodeList.h"
#include "../Node.h"
#include "Funcs.h"

#include <CBStr/StringEx.h>

namespace cb {
  CXmlNodeList::CXmlNodeList() {}
  CXmlNodeList::CXmlNodeList(const CXmlNodeList & other) 
    : mNodeList(other.mNodeList)
  {}
  CXmlNodeList::~CXmlNodeList() {}

  void CXmlNodeList::AddNode(const CXmlNode & node) {
    mNodeList.push_back(node);
  }

  CXmlNode & CXmlNodeList::AddNode(const string & name) {
    mNodeList.push_back(CXmlNode(name));
    return *mNodeList.rbegin();
  }

  CXmlNode & CXmlNodeList::AddNode(const XmlNodeType type) {
    mNodeList.push_back(CXmlNode(type));
    return *mNodeList.rbegin();
  }

  const size_t CXmlNodeList::GetSize() const {
    return mNodeList.size();
  }

  const bool CXmlNodeList::IsEmpty() const {
    return mNodeList.empty();
  }

  void CXmlNodeList::Clear() {
    return mNodeList.clear();
  }

  CXmlNode & CXmlNodeList::Get(const size_t index) {
    return mNodeList[index];
  }

  const CXmlNode & CXmlNodeList::Get(const size_t index) const {
    return mNodeList[index];
  }

  CXmlNodeList::iterator CXmlNodeList::Begin() {
    return mNodeList.begin();
  }

  CXmlNodeList::const_iterator CXmlNodeList::Begin() const {
    return mNodeList.begin();
  }

  CXmlNodeList::iterator CXmlNodeList::End() {
    return mNodeList.end();
  }

  CXmlNodeList::const_iterator CXmlNodeList::End() const {
    return mNodeList.end();
  }

  CXmlNodeList::iterator CXmlNodeList::Erase(const_iterator it) {
    return mNodeList.erase(it);
  }

  CXmlNodeList::iterator CXmlNodeList::Find(const string & name) {
    for(iterator it = Begin(); it != End(); it++) {
      if(it->GetName() == name) {
        return it;
      }
    }
    return End();
  }

  CXmlNodeList::const_iterator CXmlNodeList::Find(const string & name) const {
    for(const_iterator it = Begin(); it != End(); it++) {
      if(it->GetName() == name) {
        return it;
      }
    }
    return End();
  }

  const size_t CXmlNodeList::Parse(const string & text, const size_t offset) {
    Clear();

    size_t pos = findNonWS(text, offset, g_xmlTagStart);
    while(pos != string::npos && !subcmp(text, g_xmlTagCloseStart, pos)) {
      CXmlNode node;
      pos = node.Parse(text, pos);

      if(pos != string::npos) {
        mNodeList.push_back(node);
      }
      else {
        return string::npos;
      }

      pos = findNonWS(text, pos, g_xmlTagStart);
    }

    return pos;
  }

  const string CXmlNodeList::ToString(const CXmlStringFormat& fmt) const {
    strvector list;
    for(const_iterator it = Begin(); it != End(); it++) {
      list.push_back(it->ToString(fmt));
    }
    return join(list, genEnding(fmt));
  }
 
  const CXmlNode & CXmlNodeList::operator[](const string & name) const {
    return *Find(name);
  }

  CXmlNode & CXmlNodeList::operator[](const string & name) {
    return *Find(name);
  }

  void CXmlNodeList::operator=(const CXmlNodeList & other) {
    mNodeList = other.mNodeList;
  }
}