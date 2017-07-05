#ifndef __CB_XML_ATTRIBUTE_LIST_H__
#define __CB_XML_ATTRIBUTE_LIST_H__

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
    CXmlAttributeList(const CXmlAttributeList& other);
    CXmlAttributeList(CXmlAttributeList&& other);
    ~CXmlAttributeList();

    void SetValue(const string& name, const string& value = string());
    string GetValue(const string& name, const string& defValue = string()) const;

    size_t size() const { return mAttrList.size(); }
    bool empty() const { return mAttrList.empty(); }

    CXmlAttribute& Get(const size_t index) { return mAttrList[index]; }
    const CXmlAttribute& Get(const size_t index) const { return mAttrList[index]; }

    void clear();

    iterator begin() { return mAttrList.begin(); }
    const_iterator begin() const { return mAttrList.begin(); }

    iterator end() { return mAttrList.end(); }
    const_iterator end() const { return mAttrList.end(); }

    iterator find(const string& name);
    const_iterator find(const string& name) const;

    iterator erase(iterator it);

    size_t Parse(const string& text, const size_t offset = 0);
    string ToString() const;

    void operator=(const CXmlAttributeList& other);
    void operator=(CXmlAttributeList&& other);
    string operator[](const string& name) const;
  };
}

#endif // !__CB_XML_ATTRIBUTE_LIST_H__
