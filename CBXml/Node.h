#ifndef __CB_XML_NODE_H__
#define __CB_XML_NODE_H__

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
    CXmlNode(const string name = string());
    CXmlNode(const XmlNodeType type, const string value = string());
    CXmlNode(const CXmlNode& other);
    ~CXmlNode();

    void SetType(const XmlNodeType type);
    const XmlNodeType GetType() const;

    void SetName(const string& name);
    const string GetName() const;

    void SetValue(const string& value, const bool cdata = false);
    const string GetValue() const;

    const size_t Parse(const string& text, const size_t offset = 0);

    const string ToString(const CXmlStringFormat& fmt = CXmlStringFormat()) const;

    void operator=(const CXmlNode& other);
  };
}

#endif // !__CB_XML_NODE_H__
