#pragma once

#include "Attribute.h"

#include <vector>

namespace cb {
  class XmlAttributeList {
  public:
    using AttributeListT = std::vector<XmlAttribute>;
    using iterator = AttributeListT::iterator;
    using const_iterator = AttributeListT::const_iterator;

  private:
    AttributeListT mAttrList;

  public:
    XmlAttributeList();
    XmlAttributeList(XmlAttributeList const& other);
    XmlAttributeList(XmlAttributeList&& other);
    ~XmlAttributeList();

    void setValue(string const& name, string const& value = string());
    string getValue(string const& name, string const& defValue = string()) const;

    size_t size() const { return mAttrList.size(); }
    bool empty() const { return mAttrList.empty(); }

    XmlAttribute& get(size_t const index) { return mAttrList[index]; }
    const XmlAttribute& get(size_t const index) const { return mAttrList[index]; }

    void clear();

    iterator begin() { return mAttrList.begin(); }
    const_iterator begin() const { return mAttrList.begin(); }

    iterator end() { return mAttrList.end(); }
    const_iterator end() const { return mAttrList.end(); }

    iterator find(string const& name);
    const_iterator find(string const& name) const;

    iterator erase(iterator it);

    size_t parse(string const& text, size_t const offset = 0, cb::ostream& err = std::wcerr);
    string toString() const;

    void operator=(XmlAttributeList const& other);
    void operator=(XmlAttributeList&& other);

    const XmlAttribute& operator[](string const& name) const { return *find(name); }
    XmlAttribute& operator[](string const& name);
  };
}
