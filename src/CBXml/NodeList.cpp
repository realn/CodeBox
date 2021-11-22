#include "stdafx.h"
#include "Funcs.h"

#include <algorithm>
#include <CBCore/StringFunctions.h>
#include <CBXml/Node.h>
#include <CBXml/NodeList.h>

namespace cb {
  CXmlNodeList::CXmlNodeList() = default;

  CXmlNodeList::CXmlNodeList(const CXmlNodeList& other) = default;

  CXmlNodeList::CXmlNodeList(CXmlNodeList&& other) = default;

  CXmlNodeList::~CXmlNodeList() = default;

  void CXmlNodeList::addNode(XmlNode&& node) {
    mNodeList.push_back(node);
  }

  XmlNode& CXmlNodeList::addNode(string const& name) {
    mNodeList.push_back(XmlNode(name));
    return *mNodeList.rbegin();
  }

  XmlNode& CXmlNodeList::addNode(XmlNodeType const type) {
    mNodeList.push_back(XmlNode(type));
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

  void CXmlNodeList::Remove(string const& name) {
    auto pred =
      [name](const XmlNode& node)->auto{return node.getName() == name; };
    erase(std::remove_if(begin(), end(), pred), end());
  }

  CXmlNodeList::iterator CXmlNodeList::find(string const& name) {
    auto pred =
      [name](const XmlNode& node)->auto{return node.getName() == name; };
    return std::find_if(begin(), end(), pred);
  }

  CXmlNodeList::const_iterator CXmlNodeList::find(string const& name) const {
    auto pred =
      [name](const XmlNode& node)->auto{return node.getName() == name; };
    return std::find_if(begin(), end(), pred);
  }

  XmlNodePtrListT CXmlNodeList::search(string const& name) {
    auto result = XmlNodePtrListT();
    for (auto& node : *this) {
      if (node.getName() == name) {
        result.push_back(&node);
      }
    }
    return result;
  }

  XmlNodeConstPtrListT CXmlNodeList::search(string const& name) const {
    auto result = XmlNodeConstPtrListT();
    for (auto& node : *this) {
      if (node.getName() == name) {
        result.push_back(&node);
      }
    }
    return result;
  }

  size_t CXmlNodeList::parse(string const& text, size_t const offset, cb::ostream& err) {
    clear();

    size_t pos = findNonWS(text, offset, XML_TAG_START);
    while (pos != string::npos && !subcmp(text, XML_TAG_CLOSE_START, pos)) {
      auto node = XmlNode();
      pos = node.parse(text, pos, err);

      if (pos != string::npos) {
        mNodeList.push_back(node);
      }
      else {
        return string::npos;
      }

      pos = findNonWS(text, pos, XML_TAG_START);
    }

    return pos;
  }

  string CXmlNodeList::toString(XmlStringFormat const& fmt) const {
    auto list = strvector();
    for (auto& node : *this) {
      list.push_back(node.toString(fmt));
    }
    return join(list, genEnding(fmt));
  }

  const XmlNode& CXmlNodeList::operator[](string const& name) const {
    return *find(name);
  }

  XmlNode& CXmlNodeList::operator[](string const& name) {
    auto it = find(name);
    if (it != end()) {
      return *it;
    }
    mNodeList.push_back(XmlNode(name));
    return *mNodeList.rbegin();
  }

  void CXmlNodeList::operator=(CXmlNodeList const& other) {
    mNodeList = other.mNodeList;
  }

  void CXmlNodeList::operator=(CXmlNodeList&& other) {
    mNodeList = std::move(other.mNodeList);
  }
}