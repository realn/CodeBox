#pragma once

#include "Defines.h"
#include "StringFormat.h"

#include <vector>
#include <map>

namespace cb {
  class XmlNode;
  enum class XmlNodeType;

  using XmlNodePtrT = XmlNode*;
  using XmlNodeConstPtrT = XmlNode const*;
  using XmlNodePtrListT = std::vector<XmlNodePtrT>;
  using XmlNodeConstPtrListT = std::vector<XmlNodeConstPtrT>;

  class CXmlNodeList {
  public:
    using NodeListT = std::vector<XmlNode>;
    using iterator = NodeListT::iterator;
    using const_iterator = NodeListT::const_iterator;

  private:
    NodeListT mNodeList;

  public:
    CXmlNodeList();
    CXmlNodeList(CXmlNodeList const& other);
    CXmlNodeList(CXmlNodeList&& other);
    ~CXmlNodeList();

    void addNode(XmlNode&& node);
    XmlNode& addNode(string const& name);
    XmlNode& addNode(XmlNodeType const type);

    size_t size() const { return mNodeList.size(); }
    bool empty() const { return mNodeList.empty(); }

    void clear();

    XmlNode& get(size_t const index) { return mNodeList[index]; }
    const XmlNode& get(size_t const index) const { return mNodeList[index]; }

    iterator begin() { return mNodeList.begin(); }
    const_iterator begin() const { return mNodeList.begin(); }

    XmlNode& first() { return *begin(); }
    const XmlNode& first() const { return *begin(); }

    iterator end() { return mNodeList.end(); }
    const_iterator end() const { return mNodeList.end(); }

    XmlNode& last() { return *(end() - 1); }
    XmlNode const& last() const { return *(end() - 1); }

    iterator erase(const_iterator it);
    iterator erase(const_iterator beg, const_iterator end);

    void Remove(string const& name);

    iterator find(string const& name);
    const_iterator find(string const& name) const;

    XmlNodePtrListT search(string const& name);
    XmlNodeConstPtrListT search(string const& name) const;

    size_t parse(string const& text, size_t const offset = 0, cb::ostream& err = std::wcerr);

    string toString(XmlStringFormat const& fmt = XmlStringFormat()) const;

    const XmlNode& operator[](string const& name) const;
    XmlNode& operator[](string const& name);

    void operator=(CXmlNodeList const& other);
    void operator=(CXmlNodeList&& other);
  };
}

