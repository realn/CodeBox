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
    CXmlNodeList(CXmlNodeList const & other);
    CXmlNodeList(CXmlNodeList&& other);
    ~CXmlNodeList();

    void AddNode(CXmlNode&& node);
    CXmlNode& AddNode(string const& name);
    CXmlNode& AddNode(XmlNodeType const type);

    size_t size() const { return mNodeList.size(); }
    bool empty() const { return mNodeList.empty(); }

    void clear();

    CXmlNode& Get(size_t const index) { return mNodeList[index]; }
    const CXmlNode& Get(size_t const index) const { return mNodeList[index]; }

    iterator begin() { return mNodeList.begin(); }
    const_iterator begin() const { return mNodeList.begin(); }

    CXmlNode& first() { return *begin(); }
    const CXmlNode& first() const { return *begin(); }

    iterator end() { return mNodeList.end(); }
    const_iterator end() const { return mNodeList.end(); }

    CXmlNode& last() { return *(end() - 1); }
    CXmlNode const & last() const { return *(end() - 1); }

    iterator erase(const_iterator it);
    iterator erase(const_iterator beg, const_iterator end);

    void Remove(string const& name);

    iterator find(string const& name);
    const_iterator find(string const& name) const;

    XmlNodePtrListT Search(string const& name);
    XmlNodeConstPtrListT Search(string const& name) const;

    size_t Parse(string const& text, size_t const offset = 0);

    string ToString(CXmlStringFormat const & fmt = CXmlStringFormat()) const;

    const CXmlNode& operator[](string const& name) const;
    CXmlNode& operator[](string const& name);

    void operator=(CXmlNodeList const & other);
    void operator=(CXmlNodeList&& other);
  };
}

#endif // !__CB_XML_NODE_LIST_H__

