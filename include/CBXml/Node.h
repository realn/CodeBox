#pragma once

#include "AttributeList.h"
#include "NodeList.h"
#include "StringFormat.h"

namespace cb {
  enum class XmlNodeType {
    Normal = 0,
    Text = 1,
    CData = 2
  };

  class CXmlNode {
  public:
    CXmlAttributeList Attributes;
    CXmlNodeList Nodes;

  private:
    string mName;
    XmlNodeType mType;

  public:
    CXmlNode(string const& name = string());
    CXmlNode(XmlNodeType const type, string const& value = string());
    CXmlNode(CXmlNode const& other);
    CXmlNode(CXmlNode&& other);
    ~CXmlNode();

    void SetType(XmlNodeType const type) { mType = type; }
    XmlNodeType GetType() const { return mType; }

    void SetName(string const& name) { mName = name; }
    string GetName() const { return mName; }

    void SetValue(string const& value, bool const cdata = false);
    string GetValue() const;

    void clear();

    size_t Parse(string const& text, size_t const offset = 0, cb::ostream& err = std::wcerr);

    string ToString(CXmlStringFormat const & fmt = CXmlStringFormat()) const;

    void operator=(CXmlNode const & other);
    void operator=(CXmlNode&& other);
    void operator=(string const& value);

    const CXmlNode& operator[](string const & name) const { return Nodes[name]; }
    CXmlNode& operator[](string const & name) { return Nodes[name]; };
  };
}
