#ifndef __CB_XML_NODE_LIST_H__
#define __CB_XML_NODE_LIST_H__

#include "Defines.h"
#include "StringFormat.h"

#include <vector>

namespace cb {
  class CXmlNode;
  enum class XmlNodeType;

  class CXmlNodeList {
  public:
    typedef std::vector<CXmlNode> vector;
    typedef vector::iterator iterator;
    typedef vector::const_iterator const_iterator;

  private:
    vector mNodeList;

  public:
    CXmlNodeList();
    CXmlNodeList(const CXmlNodeList& other);
    ~CXmlNodeList();

    void AddNode(const CXmlNode& node);
    CXmlNode& AddNode(const string& name);
    CXmlNode& AddNode(const XmlNodeType type);

    const size_t GetSize() const;
    const bool IsEmpty() const;

    void Clear();

    CXmlNode& Get(const size_t index);
    const CXmlNode& Get(const size_t index) const;

    iterator Begin();
    const_iterator Begin() const;

    iterator End();
    const_iterator End() const;

    iterator Erase(const_iterator it);

    iterator Find(const string& name);
    const_iterator Find(const string& name) const;

    const size_t Parse(const string& text, const size_t offset = 0);

    const string ToString(const CXmlStringFormat& fmt = CXmlStringFormat()) const;

    const CXmlNode& operator[](const string& name) const;
    CXmlNode& operator[](const string& name);

    void operator=(const CXmlNodeList& other);
  };
}

#endif // !__CB_XML_NODE_LIST_H__

