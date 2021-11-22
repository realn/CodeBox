#include "stdafx.h"
#include "Funcs.h"

#include <algorithm>

#include <CBCore/StringConvert.h>
#include <CBCore/StringFunctions.h>
#include <CBXml/AttributeList.h>

namespace cb {
  XmlAttributeList::XmlAttributeList() {}

  XmlAttributeList::XmlAttributeList(XmlAttributeList const& other)
    : mAttrList(other.mAttrList) {
  }

  XmlAttributeList::XmlAttributeList(XmlAttributeList&& other)
    : mAttrList(std::move(other.mAttrList)) {
  }

  XmlAttributeList::~XmlAttributeList() {}

  void XmlAttributeList::setValue(string const& name, string const& value) {
    auto it = find(name);
    if (it == end()) {
      if (!value.empty()) {
        mAttrList.push_back(XmlAttribute(name, value));
      }
      return;
    }
    if (value.empty()) {
      erase(it);
      return;
    }
    it->setValue(value);
  }

  string XmlAttributeList::getValue(string const& name, string const& defValue) const {
    auto it = find(name);
    if (it == end()) {
      return defValue;
    }
    return it->getValue();
  }

  inline void XmlAttributeList::clear() { mAttrList.clear(); }

  XmlAttributeList::iterator XmlAttributeList::find(string const& name) {
    auto pred =
      [name](const XmlAttribute& item) -> auto {return item.getName() == name; };
    return std::find_if(begin(), end(), pred);
  }

  XmlAttributeList::const_iterator XmlAttributeList::find(string const& name) const {
    auto pred =
      [name](const XmlAttribute& item) -> auto {return item.getName() == name; };
    return std::find_if(begin(), end(), pred);
  }

  inline XmlAttributeList::iterator XmlAttributeList::erase(iterator it) { return mAttrList.erase(it); }

  size_t XmlAttributeList::parse(string const& text, size_t const offset, cb::ostream& err) {
    clear();
    auto pos = findNonWS(text, offset, XML_TAG_END_LIST);
    while (pos != string::npos && !subcmp(text, XML_TAG_END_LIST, pos)) {
      auto attr = XmlAttribute();
      pos = attr.parse(text, pos);

      if (pos != string::npos) {
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

  string XmlAttributeList::toString() const {
    auto list = strvector();
    for (auto& item : *this) {
      list.push_back(item.toString());
    }
    return join(list, XML_SPACE);
  }

  void XmlAttributeList::operator=(XmlAttributeList const& other) {
    mAttrList = other.mAttrList;
  }

  void XmlAttributeList::operator=(XmlAttributeList&& other) {
    mAttrList = std::move(other.mAttrList);
  }

  XmlAttribute& XmlAttributeList::operator[](string const& name) {
    auto it = find(name);
    if (it != end()) {
      return *it;
    }
    mAttrList.push_back(XmlAttribute(name));
    return *mAttrList.rbegin();
  }

}