#pragma once

#include "AttributeList.h"
#include "NodeList.h"
#include "StringFormat.h"

namespace cb {
  enum class XmlNodeType {
    Normal = 0,
    text = 1,
    CData = 2
  };

  class XmlNode {
  public:
    XmlAttributeList Attributes;
    CXmlNodeList Nodes;

  private:
    string mName;
    XmlNodeType mType;

  public:
    XmlNode(string const& name = string());
    XmlNode(XmlNodeType const type, string const& value = string());
    XmlNode(XmlNode const& other);
    XmlNode(XmlNode&& other);
    ~XmlNode();

    void SetType(XmlNodeType const type) { mType = type; }
    XmlNodeType getType() const { return mType; }

    void SetName(string const& name) { mName = name; }
    string getName() const { return mName; }

    void setValue(string const& value, bool const cdata = false);
    string getValue() const;

    void clear();

    size_t parse(string const& text, size_t const offset = 0, cb::ostream& err = std::wcerr);

    string toString(XmlStringFormat const& fmt = XmlStringFormat()) const;

    void operator=(XmlNode const& other);
    void operator=(XmlNode&& other);
    void operator=(string const& value);

    const XmlNode& operator[](string const& name) const { return Nodes[name]; }
    XmlNode& operator[](string const& name) { return Nodes[name]; };
  };
}
