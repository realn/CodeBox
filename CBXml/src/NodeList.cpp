#include "stdafx.h"
#include "../NodeList.h"
#include "../Node.h"
#include "Funcs.h"

#include <CBStr/StringEx.h>

#include <algorithm>

namespace cb {
  CXmlNodeList::CXmlNodeList() {}

  CXmlNodeList::CXmlNodeList(const CXmlNodeList & other)
    : mNodeList(other.mNodeList) {}

  CXmlNodeList::CXmlNodeList(CXmlNodeList && other)
    : mNodeList(std::move(other.mNodeList))
  {}

  CXmlNodeList::~CXmlNodeList() {}

  void CXmlNodeList::AddNode(CXmlNode && node) {
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

  inline void CXmlNodeList::clear() {
    return mNodeList.clear();
  }

  CXmlNodeList::iterator CXmlNodeList::erase(const_iterator it) {
    return mNodeList.erase(it);
  }

  CXmlNodeList::iterator CXmlNodeList::erase(const_iterator beg, const_iterator end) {
    return mNodeList.erase(beg, end);
  }

  void CXmlNodeList::Remove(const string & name) {
    auto pred =
      [name](const CXmlNode& node)->auto{return node.GetName() == name; };
    erase(std::remove_if(begin(), end(), pred), end());
  }

  CXmlNodeList::iterator CXmlNodeList::find(const string & name) {
    auto pred =
      [name](const CXmlNode& node)->auto{return node.GetName() == name; };
    return std::find_if(begin(), end(), pred);
  }

  CXmlNodeList::const_iterator CXmlNodeList::find(const string & name) const {
    auto pred =
      [name](const CXmlNode& node)->auto{return node.GetName() == name; };
    return std::find_if(begin(), end(), pred);
  }

  XmlNodePtrListT CXmlNodeList::Search(const string & name) {
    auto result = XmlNodePtrListT();
    for(auto& node : *this) {
      if(node.GetName() == name) {
        result.push_back(&node);
      }
    }
    return result;
  }

  XmlNodeConstPtrListT CXmlNodeList::Search(const string & name) const {
    auto result = XmlNodeConstPtrListT();
    for(auto& node : *this) {
      if(node.GetName() == name) {
        result.push_back(&node);
      }
    }
    return result;
  }

  size_t CXmlNodeList::Parse(const string & text, const size_t offset) {
    clear();

    size_t pos = findNonWS(text, offset, XML_TAG_START);
    while(pos != string::npos && !subcmp(text, XML_TAG_CLOSE_START, pos)) {
      CXmlNode node;
      pos = node.Parse(text, pos);

      if(pos != string::npos) {
        mNodeList.push_back(node);
      }
      else {
        return string::npos;
      }

      pos = findNonWS(text, pos, XML_TAG_START);
    }

    return pos;
  }

  string CXmlNodeList::ToString(const CXmlStringFormat& fmt) const {
    auto list = strvector();
    for(auto& node : *this) {
      list.push_back(node.ToString(fmt));
    }
    return join(list, genEnding(fmt));
  }

  const CXmlNode & CXmlNodeList::operator[](const string & name) const {
    return *find(name);
  }

  CXmlNode & CXmlNodeList::operator[](const string & name) {
    return *find(name);
  }

  void CXmlNodeList::operator=(const CXmlNodeList & other) {
    mNodeList = other.mNodeList;
  }

  void CXmlNodeList::operator=(CXmlNodeList && other) {
    mNodeList = std::move(other.mNodeList);
  }
}