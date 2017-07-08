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
    CXmlAttribute(CXmlAttribute&& other);
    explicit CXmlAttribute(const string name, const string value = string());
    ~CXmlAttribute();

    const string& GetName() const { return mName; }
    const string& GetValue() const { return mValue; }

    void SetValue(const string val) { mValue = val; }

    string ToString() const;

    size_t Parse(const string& text, const size_t offset = 0);

    void operator=(const CXmlAttribute& other);
    void operator=(CXmlAttribute&& other);
    void operator=(const string& value) { mValue = value; }

    operator const string&() const { return mValue; }
    operator string&() { return mValue; }
  };
}


#endif // !__CB_XML_ATTRIBUTE_H__
