#ifndef __CB_XML_SERIALIZE_H__
#define __CB_XML_SERIALIZE_H__

#include "Node.h"
#include "NodeList.h"

namespace cb {
  template<typename _Type> string toStr(const _Type& value);
  template<typename _Type> bool fromStr(const string& text, _Type& outValue);


  class CXmlSerializeBase {
  protected:
    CXmlNode& mNode;
    bool mWrite;

  public:
    CXmlSerializeBase(const CXmlNode& node, const bool write);
    virtual ~CXmlSerializeBase();
  };

  template<typename _Type>
  class CXmlSerialize
    : public CXmlSerializeBase {
  private:
    _Type& mObject;

  public:
    CXmlSerialize(const CXmlNode& node, 
                  const _Type& object, 
                  const bool write = false);
    virtual ~CXmlSerialize();

    bool RWObj();
    bool Read();
    bool Write();

    template<typename _AttrType>
    bool GetAttribute(const string& name, _AttrType& object) const;

    template<typename _AttrType>
    bool SetAttribute(const string& name, const _AttrType& object);

    template<typename _AttrType>
    bool RWAttribute(const string& name, _AttrType& object);

    template<typename _ObjType>
    bool GetNode(const string& name, _ObjType& object) const;

    template<typename _ObjType>
    bool SetNode(const string& name, const _ObjType& object);

    template<typename _ObjType>
    bool RWNode(const string& name, _ObjType& object);

    template<typename _ObjType>
    bool GetNodeList(std::vector<_ObjType>& list, const string& elemName) const;

    template<typename _ObjType>
    bool SetNodeList(const std::vector<_ObjType>& list, const string& elemName);

    template<typename _ObjType>
    bool RWNodeList(std::vector<_ObjType>& list, const string& elemName);

    template<typename _AttrType, typename _ObjType>
    bool GetNodeMap(std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName) const;

    template<typename _AttrType, typename _ObjType>
    bool SetNodeMap(const std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName);

    template<typename _AttrType, typename _ObjType>
    bool RWNodeMap(std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName);
  };



  template<typename _Type>
  bool ReadXmlObject(const CXmlNode& node, _Type& object) {
    auto xmlObj = CXmlSerialize<_Type>(node, object, false);
    return xmlObj.Read();
  }

  template<typename _Type>
  bool WriteXmlObject(CXmlNode& node, const _Type& object) {
    auto xmlObj = CXmlSerialize<_Type>(node, object, true);
    return xmlObj.Write();
  }



  template<typename _Type>
  inline CXmlSerialize<_Type>::CXmlSerialize(const CXmlNode & node, 
                                             const _Type & object, 
                                             const bool write)
    : CXmlSerializeBase(node, write)
    , mObject(const_cast<_Type&>(object)) {}

  template<typename _Type>
  inline CXmlSerialize<_Type>::~CXmlSerialize() {}

  template<typename _Type>
  bool CXmlSerialize<_Type>::RWObj() { return false; }

  template<typename _Type>
  bool CXmlSerialize<_Type>::Read() { 
    return RWObj();
  }

  template<typename _Type>
  bool CXmlSerialize<_Type>::Write() { 
    return RWObj();
  }

  template<typename _Type>
  template<typename _AttrType>
  inline bool CXmlSerialize<_Type>::GetAttribute(const string & name, 
                                                 _AttrType & object) const {
    auto val = mNode.Attributes.GetValue(name);
    if(val.empty())
      return false;
    return fromStr(val, object);
  }

  template<typename _Type>
  template<typename _AttrType>
  inline bool CXmlSerialize<_Type>::SetAttribute(const string & name, 
                                                 const _AttrType & object) {
    auto val = toStr(object);
    mNode.Attributes.SetValue(name, val);
    return true;
  }

  template<typename _Type>
  template<typename _AttrType>
  inline bool CXmlSerialize<_Type>::RWAttribute(const string & name, 
                                                _AttrType & object) {
    if(mWrite)
      return SetAttribute(name, object);
    return GetAttribute(name, object);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool CXmlSerialize<_Type>::GetNode(const string & name, 
                                            _ObjType & object) const {
    auto it = mNode.Nodes.find(name);
    if(it == mNode.Nodes.end()) {
      return false;
    }
    return ReadXmlObject(*it, object);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool CXmlSerialize<_Type>::SetNode(const string & name, 
                                            const _ObjType & object) {
    auto it = mNode.Nodes.find(name);
    if(it != mNode.Nodes.end()) {
      return WriteXmlObject(*it, object);
    }
    auto& node = mNode.Nodes.AddNode(name);
    return WriteXmlObject(node, object);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool CXmlSerialize<_Type>::RWNode(const string & name, 
                                           _ObjType & object) {
    if(mWrite)
      return SetNode(name, object);
    return GetNode(name, object);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool CXmlSerialize<_Type>::GetNodeList(std::vector<_ObjType>& list, 
                                                const string & elemName) const {
    list.clear();
    auto nodeList = mNode.Nodes.Search(elemName);
    for(auto& pNode : nodeList) {
      auto obj = _ObjType();
      if(!ReadXmlObject(*pNode, obj)) {
        return false;
      }
      list.push_back(obj);
    }
    return true;
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool CXmlSerialize<_Type>::SetNodeList(const std::vector<_ObjType>& list, 
                                                const string & elemName) {
    mNode.Nodes.Remove(elemName);
    for(auto& item : list) {
      auto& node = mNode.Nodes.AddNode(elemName);
      if(!WriteXmlObject(node, item)) {
        return false;
      }
    }
    return true;
  }

  template<typename _Type>
  template<typename _ObjType>
  inline bool CXmlSerialize<_Type>::RWNodeList(std::vector<_ObjType>& list, 
                                               const string & elemName) {
    if(mWrite)
      return SetNodeList(list, elemName);
    return GetNodeList(list, elemName);
  }

  template<typename _Type>
  template<typename _AttrType, typename _ObjType>
  inline bool CXmlSerialize<_Type>::GetNodeMap(std::map<_AttrType, _ObjType>& list, 
                                               const string & elemName, 
                                               const string & keyName) const {
    list.clear();
    auto nodeList = mNode.Nodes.Search(elemName);
    for(auto& pNode, : nodeList) {
      auto obj = _ObjType();
      auto key = _AttrType();
      auto xml = CXmlSerialize<_ObjType>(*pNode, obj);
      if(!xml.GetAttribute(keyName, key)) {
        return false;
      }
      if(!xml.Read()) {
        return false;
      }
      list[key] = obj;
    }
    return true;
  }

  template<typename _Type>
  template<typename _AttrType, typename _ObjType>
  inline bool CXmlSerialize<_Type>::SetNodeMap(const std::map<_AttrType, _ObjType>& list, 
                                               const string & elemName, 
                                               const string & keyName) {
    mNode.Nodes.Remove(elemName);
    for(auto& item : list) {
      auto& node = mNode.Nodes.AddNode(elemName);
      auto xml = CXmlSerialize<_ObjType>(node, item.second);
      if(!xml.SetAttribute(keyName, it.first)) {
        return false;
      }
      if(!xml.Write()) {
        return false;
      }
    }
    return true;
  }

  template<typename _Type>
  template<typename _AttrType, typename _ObjType>
  inline bool CXmlSerialize<_Type>::RWNodeMap(std::map<_AttrType, _ObjType>& list, 
                                              const string & elemName, 
                                              const string & keyName) {
    if(mWrite)
      return SetNodeMap(list, elemName, keyName);
    return GetNodeMap(list, elemName, keyName);
  }
}

#define CB_DEFINEXMLREAD(OBJ) template<> const bool cb::CXmlSerialize<OBJ>::Read() 
#define CB_DEFINEXMLWRITE(OBJ) template<> const bool cb::CXmlSerialize<OBJ>::Write() 
#define CB_DEFINEXMLRW(OBJ) template<> const bool cb::CXmlSerialize<OBJ>::RWObj() 

#endif // !__CB_XML_SERIALIZE_H__
