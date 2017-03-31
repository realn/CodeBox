#ifndef __CB_XML_ATTRIBUTE_LIST_H__
#define __CB_XML_ATTRIBUTE_LIST_H__

#include "Attribute.h"

#include <vector>

namespace cb {
  class CXmlAttributeList {
  public:
    typedef std::vector<CXmlAttribute> vector;
    typedef vector::iterator iterator;
    typedef vector::const_iterator const_iterator;

  private:
    vector mAttrList;

  public:
    CXmlAttributeList();
    CXmlAttributeList(const CXmlAttributeList& other);
    ~CXmlAttributeList();

    void SetValue(const string& name, const string& value = string());
    const string GetValue(const string& name, const string& defValue = string()) const;

    const size_t GetSize() const;
    const bool IsEmpty() const;

    CXmlAttribute& Get(const size_t index);
    const CXmlAttribute& Get(const size_t index) const;

    void Clear();

    iterator Begin();
    const_iterator Begin() const;

    iterator End();
    const_iterator End() const;

    iterator Find(const string& name);
    const_iterator Find(const string& name) const;

    iterator Erase(iterator it);

    const size_t Parse(const string& text, const size_t offset = 0);
    const string ToString() const;

    void operator=(const CXmlAttributeList& other);
    const string operator[](const string& name) const;
  };
}

#endif // !__CB_XML_ATTRIBUTE_LIST_H__
