#ifndef __CB_XML_ATTRIBUTE_H__
#define __CB_XML_ATTRIBUTE_H__

#include "Defines.h"

namespace cb {
  class CXmlAttribute {
  private:
    string  mName;
    string  mValue;

  public:
    CXmlAttribute();
    CXmlAttribute(const CXmlAttribute& other);
    explicit CXmlAttribute(const string name, const string value = string());
    ~CXmlAttribute();

    const string GetName() const;
    const string GetValue() const;

    void SetValue(const string val);

    const string ToString() const;

    const size_t Parse(const string& text, const size_t offset = 0);

    void operator=(const CXmlAttribute& other);
    void operator=(const string& value);
  };
}


#endif // !__CB_XML_ATTRIBUTE_H__
