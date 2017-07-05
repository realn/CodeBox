#ifndef __CB_XML_NODE_LIST_H__
#define __CB_XML_NODE_LIST_H__

#include "Defines.h"
#include "StringFormat.h"

#include <vector>
#include <map>

namespace cb {
  class CXmlNode;
  enum class XmlNodeType;

  using XmlNodePtrT = CXmlNode*;
  using XmlNodeConstPtrT = CXmlNode const*;
  using XmlNodePtrListT = std::vector<XmlNodePtrT>;
  using XmlNodeConstPtrListT = std::vector<XmlNodeConstPtrT>;

  class CXmlNodeList {
  public:
    using NodeListT = std::vector<CXmlNode>;
    using iterator = NodeListT::iterator;
    using const_iterator = NodeListT::const_iterator;

  private:
    NodeListT mNodeList;

  public:
    CXmlNodeList();
    CXmlNodeList(const CXmlNodeList& other);
    CXmlNodeList(CXmlNodeList&& other);
    ~CXmlNodeList();

    void AddNode(const CXmlNode& node);
    CXmlNode& AddNode(const string& name);
    CXmlNode& AddNode(const XmlNodeType type);

    size_t size() const { return mNodeList.size(); }
    bool empty() const { return mNodeList.empty(); }

    void clear();

    CXmlNode& Get(const size_t index) { return mNodeList[index]; }
    const CXmlNode& Get(const size_t index) const { return mNodeList[index]; }

    iterator begin() { return mNodeList.begin(); }
    const_iterator begin() const { return mNodeList.begin(); }

    iterator end() { return mNodeList.end(); }
    const_iterator end() const { return mNodeList.end(); }

    iterator erase(const_iterator it);
    iterator erase(const_iterator beg, const_iterator end);

    void Remove(const string& name);

    iterator find(const string& name);
    const_iterator find(const string& name) const;

    XmlNodePtrListT Search(const string& name);
    XmlNodeConstPtrListT Search(const string& name) const;

    size_t Parse(const string& text, const size_t offset = 0);

    string ToString(const CXmlStringFormat& fmt = CXmlStringFormat()) const;

    const CXmlNode& operator[](const string& name) const;
    CXmlNode& operator[](const string& name);

    void operator=(const CXmlNodeList& other);
    void operator=(CXmlNodeList&& other);
  };
}

#endif // !__CB_XML_NODE_LIST_H__

