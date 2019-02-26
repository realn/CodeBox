#pragma once

#include "Attribute.h"

#include <vector>

namespace cb {
  class CXmlAttributeList {
  public:
    using AttributeListT = std::vector<CXmlAttribute>;
    using iterator = AttributeListT::iterator;
    using const_iterator = AttributeListT::const_iterator;

  private:
    AttributeListT mAttrList;

  public:
    CXmlAttributeList();
    CXmlAttributeList(CXmlAttributeList const& other);
    CXmlAttributeList(CXmlAttributeList&& other);
    ~CXmlAttributeList();

    void SetValue(string const& name, string const& value = string());
    string GetValue(string const& name, string const& defValue = string()) const;

    size_t size() const { return mAttrList.size(); }
    bool empty() const { return mAttrList.empty(); }

    CXmlAttribute& Get(size_t const index) { return mAttrList[index]; }
    const CXmlAttribute& Get(size_t const index) const { return mAttrList[index]; }

    void clear();

    iterator begin() { return mAttrList.begin(); }
    const_iterator begin() const { return mAttrList.begin(); }

    iterator end() { return mAttrList.end(); }
    const_iterator end() const { return mAttrList.end(); }

    iterator find(string const& name);
    const_iterator find(string const& name) const;

    iterator erase(iterator it);

    size_t Parse(string const& text, size_t const offset = 0, cb::ostream& err = std::wcerr);
    string ToString() const;

    void operator=(CXmlAttributeList const& other);
    void operator=(CXmlAttributeList&& other);

    const CXmlAttribute& operator[](string const& name) const { return *find(name); }
    CXmlAttribute& operator[](string const& name);
  };
}
