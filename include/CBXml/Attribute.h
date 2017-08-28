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
    CXmlAttribute(CXmlAttribute const& other);
    CXmlAttribute(CXmlAttribute&& other);
    explicit CXmlAttribute(string const name, string const value = string());
    ~CXmlAttribute();

    const string& GetName() const { return mName; }
    const string& GetValue() const { return mValue; }

    void SetValue(string const val) { mValue = val; }

    string ToString() const;

    size_t Parse(string const & text, size_t const offset = 0, cb::ostream& err = std::wcerr);

    void operator=(CXmlAttribute const& other);
    void operator=(CXmlAttribute&& other);
    void operator=(string const& value) { mValue = value; }

    operator const string&() const { return mValue; }
    operator string&() { return mValue; }
  };
}


#endif // !__CB_XML_ATTRIBUTE_H__
