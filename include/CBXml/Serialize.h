#pragma once

#include "Node.h"
#include "NodeList.h"

namespace cb {
  template<typename _Type> string toStr(const _Type& value);
  template<typename _Type> bool fromStr(const string& text, _Type& outValue);

  struct XmlUserData {
    virtual ~XmlUserData();
  };


  class XmlSerializeBase {
  protected:
    XmlNode& mNode;
    bool mWrite;
    std::shared_ptr<XmlUserData> mUserData;

  public:
    XmlSerializeBase(const XmlNode& node, const bool write, std::shared_ptr<XmlUserData> userData = {});
    virtual ~XmlSerializeBase();

    template<class _Type, class = std::enable_if_t<std::is_base_of_v<XmlUserData, _Type>>>
    std::shared_ptr<_Type> GetUserData() const {
      return std::dynamic_pointer_cast<_Type>(mUserData);
    }
  };

  template<typename _Type>
  class XmlSerialize
    : public XmlSerializeBase {
  private:
    _Type& mObject;

  public:
    XmlSerialize(const XmlNode& node,
                 const _Type& object,
                 const bool write = false,
                 std::shared_ptr<XmlUserData> userData = {});
    virtual ~XmlSerialize();

    bool process();
    bool read();
    bool write();

    template<typename _AttrType>
    bool getAttribute(const string& name, _AttrType& object) const;

    template<typename _AttrType>
    bool setAttribute(const string& name, const _AttrType& object);

    template<typename _AttrType>
    bool processAttribute(const string& name, _AttrType& object);

    template<typename _ObjType>
    bool getNode(const string& name, _ObjType& object) const;

    template<typename _ObjType>
    bool setNode(const string& name, const _ObjType& object);

    template<typename _ObjType>
    bool processNode(const string& name, _ObjType& object);

    template<typename _ObjType>
    bool addNode(const string& name, const _ObjType& object);

    template<typename _ObjType>
    bool getNodeList(std::vector<_ObjType>& list, const string& elemName) const;

    template<typename _ObjType>
    bool setNodeList(const std::vector<_ObjType>& list, const string& elemName);

    template<typename _ObjType>
    bool processNodeList(std::vector<_ObjType>& list, const string& elemName);

    template<typename _AttrType, typename _ObjType>
    bool getNodeMap(std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName) const;

    template<typename _AttrType, typename _ObjType>
    bool setNodeMap(const std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName);

    template<typename _AttrType, typename _ObjType>
    bool processNodeMap(std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName);
  };



  template<typename _Type>
  bool readXmlObject(const XmlNode& node, _Type& object, std::shared_ptr<XmlUserData> userData = {}) {
    auto xmlObj = XmlSerialize<_Type>(node, object, false, userData);
    return xmlObj.read();
  }

  template<typename _Type>
  bool writeXmlObject(XmlNode& node, const _Type& object, std::shared_ptr<XmlUserData> userData = {}) {
    auto xmlObj = XmlSerialize<_Type>(node, object, true, userData);
    return xmlObj.write();
  }



  template<typename _Type>
  inline XmlSerialize<_Type>::XmlSerialize(const XmlNode& node,
                                           const _Type& object,
                                           const bool write,
                                           std::shared_ptr<XmlUserData> userData)
    : XmlSerializeBase(node, write, userData)
    , mObject(const_cast<_Type&>(object)) {
  }

  template<typename _Type>
  inline XmlSerialize<_Type>::~XmlSerialize() {}

  template<typename _Type>
  bool XmlSerialize<_Type>::process() { return false; }

  template<typename _Type>
  bool XmlSerialize<_Type>::read() {
    return process();
  }

  template<typename _Type>
  bool XmlSerialize<_Type>::write() {
    return process();
  }

  template<typename _Type>
  template<typename _AttrType>
  inline bool XmlSerialize<_Type>::getAttribute(const string& name,
                                                _AttrType& object) const {
    auto val = mNode.Attributes.getValue(name);
    if (val.empty())
      return false;
    return fromStr(val, object);
  }

  template<typename _Type>
  template<typename _AttrType>
  inline bool XmlSerialize<_Type>::setAttribute(const string& name,
                                                const _AttrType& object) {
    auto val = toStr(object);
    mNode.Attributes.setValue(name, val);
    return true;
  }

  template<typename _Type>
  template<typename _AttrType>
  inline bool XmlSerialize<_Type>::processAttribute(const string& name,
                                                    _AttrType& object) {
    if (mWrite)
      return setAttribute(name, object);
    return getAttribute(name, object);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool XmlSerialize<_Type>::getNode(const string& name,
                                           _ObjType& object) const {
    auto it = mNode.Nodes.find(name);
    if (it == mNode.Nodes.end()) {
      return false;
    }
    return readXmlObject(*it, object, mUserData);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool XmlSerialize<_Type>::setNode(const string& name,
                                           const _ObjType& object) {
    auto it = mNode.Nodes.find(name);
    if (it != mNode.Nodes.end()) {
      return writeXmlObject(*it, object, mUserData);
    }
    auto& node = mNode.Nodes.addNode(name);
    return writeXmlObject(node, object, mUserData);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool XmlSerialize<_Type>::processNode(const string& name,
                                               _ObjType& object) {
    if (mWrite)
      return setNode(name, object);
    return getNode(name, object);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool XmlSerialize<_Type>::addNode(const string& name,
                                           const _ObjType& object) {
    auto& node = mNode.Nodes.addNode(name);
    return writeXmlObject(node, object, mUserData);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool XmlSerialize<_Type>::getNodeList(std::vector<_ObjType>& list,
                                               const string& elemName) const {
    list.clear();
    auto nodeList = mNode.Nodes.search(elemName);
    for (auto& pNode : nodeList) {
      auto obj = _ObjType();
      if (!readXmlObject(*pNode, obj, mUserData)) {
        return false;
      }
      list.push_back(std::move(obj));
    }
    return true;
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool XmlSerialize<_Type>::setNodeList(const std::vector<_ObjType>& list,
                                               const string& elemName) {
    mNode.Nodes.Remove(elemName);
    for (auto& item : list) {
      auto& node = mNode.Nodes.addNode(elemName);
      if (!writeXmlObject(node, item, mUserData)) {
        return false;
      }
    }
    return true;
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool XmlSerialize<_Type>::processNodeList(std::vector<_ObjType>& list,
                                                   const string& elemName) {
    if (mWrite)
      return setNodeList(list, elemName);
    return getNodeList(list, elemName);
  }

  template<typename _Type>
  template<typename _AttrType, typename _ObjType>
  inline bool XmlSerialize<_Type>::getNodeMap(std::map<_AttrType, _ObjType>& list,
                                              const string& elemName,
                                              const string& keyName) const {
    list.clear();
    auto nodeList = mNode.Nodes.search(elemName);
    for (auto& pNode : nodeList) {
      auto obj = _ObjType();
      auto key = _AttrType();
      auto xml = XmlSerialize<_ObjType>(*pNode, obj, mWrite);
      if (!xml.getAttribute(keyName, key)) {
        return false;
      }
      if (!xml.read()) {
        return false;
      }
      list[key] = std::move(obj);
    }
    return true;
  }

  template<typename _Type>
  template<typename _AttrType, typename _ObjType>
  inline bool XmlSerialize<_Type>::setNodeMap(const std::map<_AttrType, _ObjType>& list,
                                              const string& elemName,
                                              const string& keyName) {
    mNode.Nodes.Remove(elemName);
    for (auto& item : list) {
      auto node = XmlNode(elemName);
      auto xml = XmlSerialize<_ObjType>(node, item.second, mWrite);
      if (!xml.setAttribute(keyName, item.first)) {
        return false;
      }
      if (!xml.write()) {
        return false;
      }
      mNode.Nodes.addNode(std::move(node));
    }
    return true;
  }

  template<typename _Type>
  template<typename _AttrType, typename _ObjType>
  inline bool XmlSerialize<_Type>::processNodeMap(std::map<_AttrType, _ObjType>& list,
                                                  const string& elemName,
                                                  const string& keyName) {
    if (mWrite)
      return setNodeMap(list, elemName, keyName);
    return getNodeMap(list, elemName, keyName);
  }
}

#define CB_DEFINEXMLREAD(OBJ) template<> bool cb::XmlSerialize<OBJ>::read() 
#define CB_DEFINEXMLWRITE(OBJ) template<> bool cb::XmlSerialize<OBJ>::write() 
#define CB_DEFINEXMLRW(OBJ) template<> bool cb::XmlSerialize<OBJ>::RWObj() 
