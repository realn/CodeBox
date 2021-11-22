#pragma once

#include "Defines.h"

namespace cb {
  class XmlAttribute {
  private:
    string  mName;
    string  mValue;

  public:
    XmlAttribute();
    XmlAttribute(XmlAttribute const& other);
    XmlAttribute(XmlAttribute&& other);
    explicit XmlAttribute(string const name, string const value = string());
    ~XmlAttribute();

    const string& getName() const { return mName; }
    const string& getValue() const { return mValue; }

    void setValue(string const val) { mValue = val; }

    string toString() const;

    size_t parse(string const& text, size_t const offset = 0, cb::ostream& err = std::wcerr);

    void operator=(XmlAttribute const& other);
    void operator=(XmlAttribute&& other);
    void operator=(string const& value) { mValue = value; }

    operator const string& () const { return mValue; }
    operator string& () { return mValue; }
  };
}
