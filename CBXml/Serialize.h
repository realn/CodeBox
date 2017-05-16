#ifndef __CB_XML_SERIALIZE_H__
#define __CB_XML_SERIALIZE_H__

#include "Node.h"
#include "NodeList.h"

namespace cb {
  class CXmlSerializeBase {
  public:
    static const string ATTR_DEF_LIST_SEP;

  protected:
    CXmlNode& mNode;
    bool mWrite;

  public:
    CXmlSerializeBase(const CXmlNode& node, const bool write);
    virtual ~CXmlSerializeBase();

    static const strvector split(const string& text, const string& sep);
    static const string join(const strvector& list, const string& sep);
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

    const bool RWObj();
    const bool Read();
    const bool Write();

    template<typename _AttrType>
    const bool GetAttribute(const string& name, _AttrType& object) const;

    template<typename _AttrType>
    const bool GetAttribute(const string& name, 
                            std::vector<_AttrType>& objList, 
                            const string& sep = ATTR_DEF_LIST_SEP) const;

    template<typename _AttrNameType, typename _AttrType>
    const bool GetAttribute(std::map<_AttrNameType, std::vector<_AttrType>>& objMap,
                            const string& sep = ATTR_DEF_LIST_SEP) const;

    template<typename _AttrType>
    const bool SetAttribute(const string& name, const _AttrType& object);

    template<typename _AttrType>
    const bool SetAttribute(const string& name, 
                            const std::vector<_AttrType>& objList,
                            const string& sep = ATTR_DEF_LIST_SEP);
    
    template<typename _AttrNameType, typename _AttrType>
    const bool SetAttribute(const std::map<_AttrNameType, std::vector<_AttrType>>& objMap,
                            const string& sep = ATTR_DEF_LIST_SEP);

    template<typename _AttrType>
    const bool RWAttribute(const string& name, _AttrType& object);

    template<typename _AttrType>
    const bool RWAttribute(const string& name, 
                           std::vector<_AttrType>& objList,
                           const string& sep = ATTR_DEF_LIST_SEP);

    template<typename _AttrNameType, typename _AttrType>
    const bool RWAttribute(std::map<_AttrNameType, std::vector<_AttrType>>& objMap,
                           const string& sep = ATTR_DEF_LIST_SEP);

    template<typename _ObjType>
    const bool GetNode(const string& name, _ObjType& object) const;

    template<typename _ObjType>
    const bool SetNode(const string& name, const _ObjType& object);

    template<typename _ObjType>
    const bool RWNode(const string& name, _ObjType& object);

    template<typename _ObjType>
    const bool GetNodeList(std::vector<_ObjType>& list, const string& elemName) const;

    template<typename _ObjType>
    const bool SetNodeList(const std::vector<_ObjType>& list, const string& elemName);

    template<typename _ObjType>
    const bool RWNodeList(std::vector<_ObjType>& list, const string& elemName);

    template<typename _AttrType, typename _ObjType>
    const bool GetNodeMap(std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName) const;

    template<typename _AttrType, typename _ObjType>
    const bool SetNodeMap(const std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName);

    template<typename _AttrType, typename _ObjType>
    const bool RWNodeMap(std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName);

    template<typename _AttrType, typename _ObjType>
    const bool GetNodeMap(std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName, const string& valName) const;

    template<typename _AttrType, typename _ObjType>
    const bool SetNodeMap(const std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName, const string& valName);

    template<typename _AttrType, typename _ObjType>
    const bool RWNodeMap(std::map<_AttrType, _ObjType>& list, const string& elemName, const string& keyName, const string& valName);
  };



  template<typename _Type>
  const bool ReadXmlObject(const CXmlNode& node, _Type& object) {
    CXmlSerialize<_Type> xmlObj(node, object, false);
    return xmlObj.Read();
  }

  template<typename _Type>
  const bool WriteXmlObject(CXmlNode& node, const _Type& object) {
    CXmlSerialize<_Type> xmlObj(node, object, true);
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
  const bool CXmlSerialize<_Type>::RWObj() { return false; }

  template<typename _Type>
  const bool CXmlSerialize<_Type>::Read() { 
    mWrite = false;
    return RWObj();
  }

  template<typename _Type>
  const bool CXmlSerialize<_Type>::Write() { 
    mWrite = true;
    return RWObj();
  }

  template<typename _Type>
  template<typename _AttrType>
  inline const bool CXmlSerialize<_Type>::GetAttribute(const string & name, _AttrType & object) const {
    string val = mNode.Attributes.GetValue(name);
    if(val.empty())
      return false;
    return fromStr(val, object);
  }

  template<typename _Type>
  template<typename _AttrType>
  inline const bool CXmlSerialize<_Type>::GetAttribute(const string & name, 
                                                       std::vector<_AttrType>& objList,
                                                       const string& sep) const {
    string value;
    if(!GetAttribute(name, value)) {
      return false;
    }
    strvector list = split(value, sep);
    return fromStr(list, objList);
  }

  template<typename _Type>
  template<typename _AttrNameType, typename _AttrType>
  inline const bool CXmlSerialize<_Type>::GetAttribute(std::map<_AttrNameType, std::vector<_AttrType>>& objMap,
                                                       const string& sep) const {
    for(typename std::map<_AttrNameType, std::vector<_AttrType>>::iterator it = objMap.begin();
        it != objMap.end(); it++) {
      if(!GetAttribute(toStr(it->first), it->second, sep)) {
        return false;
      }
    }
    return true;
  }

  template<typename _Type>
  template<typename _AttrType>
  inline const bool CXmlSerialize<_Type>::SetAttribute(const string & name, const _AttrType & object) {
    string val = toStr(object);
    mNode.Attributes.SetValue(name, val);
    return true;
  }

  template<typename _Type>
  template<typename _AttrType>
  inline const bool CXmlSerialize<_Type>::SetAttribute(const string & name, 
                                                       const std::vector<_AttrType>& objList,
                                                       const string& sep) {
    return SetAttribute(name, join(toStr(objList), sep));
  }

  template<typename _Type>
  template<typename _AttrNameType, typename _AttrType>
  inline const bool CXmlSerialize<_Type>::SetAttribute(const std::map<_AttrNameType, std::vector<_AttrType>>& objMap,
                                                       const string& sep) {
    for(typename std::map<_AttrNameType, std::vector<_AttrType>>::const_iterator it = objMap.begin();
        it != objMap.end(); it++) {
      if(SetAttribute(toStr(it->first), it->second, sep)) {
        return false;
      }
    }
    return true;
  }

  template<typename _Type>
  template<typename _AttrType>
  inline const bool CXmlSerialize<_Type>::RWAttribute(const string & name, _AttrType & object) {
    if(mWrite)
      return SetAttribute(name, object);
    return GetAttribute(name, object);
  }

  template<typename _Type>
  template<typename _AttrType>
  inline const bool CXmlSerialize<_Type>::RWAttribute(const string & name, 
                                                      std::vector<_AttrType>& objList,
                                                      const string& sep) {
    if(mWrite)
      return SetAttribute(name, objList, sep);
    return GetAttribute(name, objList, sep);
  }

  template<typename _Type>
  template<typename _AttrNameType, typename _AttrType>
  inline const bool CXmlSerialize<_Type>::RWAttribute(std::map<_AttrNameType, std::vector<_AttrType>>& objMap,
                                                      const string& sep) {
    if(mWrite)
      return SetAttribute(objMap, sep);
    return GetAttribute(objMap, sep);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline const bool CXmlSerialize<_Type>::GetNode(const string & name, _ObjType & object) const {
    CXmlNodeList::const_iterator it = mNode.Nodes.Find(name);
    if(it == mNode.Nodes.End()) {
      return false;
    }

    return ReadXmlObject(*it, object);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline const bool CXmlSerialize<_Type>::SetNode(const string & name, const _ObjType & object) {
    CXmlNodeList::iterator it = mNode.Nodes.Find(name);
    if(it != mNode.Nodes.End()) {
      return WriteXmlObject(*it, object);
    }
    CXmlNode& node = mNode.Nodes.AddNode(name);
    return WriteXmlObject(node, object);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline const bool CXmlSerialize<_Type>::RWNode(const string & name, _ObjType & object) {
    if(mWrite)
      return SetNode(name, object);
    return GetNode(name, object);
  }

  template<typename _Type>
  template<typename _ObjType>
  inline const bool CXmlSerialize<_Type>::GetNodeList(std::vector<_ObjType>& list, const string & elemName) const {
    list.clear();
    XmlNodePtrListT nodeList = mNode.Nodes.Search(elemName);

    for(XmlNodePtrListT::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
      _ObjType obj;

      if(!ReadXmlObject(**it, obj)) {
        return false;
      }

      list.push_back(obj);
    }

    return true;
  }

  template<typename _Type>
  template<typename _ObjType>
  inline const bool CXmlSerialize<_Type>::SetNodeList(const std::vector<_ObjType>& list, const string & elemName) {
    mNode.Nodes.Remove(elemName);

    for(typename std::vector<_ObjType>::const_iterator it = list.begin(); it != list.end(); it++) {
      CXmlNode& node = mNode.Nodes.AddNode(elemName);

      if(!WriteXmlObject(node, *it)) {
        return false;
      }
    }

    return true;
  }

  template<typename _Type>
  template<typename _ObjType>
  inline const bool CXmlSerialize<_Type>::RWNodeList(std::vector<_ObjType>& list, const string & elemName) {
    if(mWrite)
      return SetNodeList(list, elemName);
    return GetNodeList(list, elemName);
  }

  template<typename _Type>
  template<typename _AttrType, typename _ObjType>
  inline const bool CXmlSerialize<_Type>::GetNodeMap(std::map<_AttrType, _ObjType>& list, const string & elemName, const string & keyName) const {
    list.clear();
    XmlNodePtrListT nodeList = mNode.Nodes.Search(elemName);

    for(XmlNodePtrListT::const_iterator it = nodeList.begin(); it != nodeList.end(); it++) {
      const CXmlNode& node = **it;
      _ObjType obj;
      _AttrType key;

      CXmlSerialize<_ObjType> xml(node, obj);

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
  inline const bool CXmlSerialize<_Type>::SetNodeMap(const std::map<_AttrType, _ObjType>& list, const string & elemName, const string & keyName) {
    mNode.Nodes.Remove(elemName);

    for(typename std::map<_AttrType, _ObjType>::const_iterator it = list.begin(); it != list.end(); it++) {
      CXmlNode& node = mNode.Nodes.AddNode(elemName);

      CXmlSerialize<_ObjType> xml(node, it->second);

      if(!xml.SetAttribute(keyName, it->first)) {
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
  inline const bool CXmlSerialize<_Type>::RWNodeMap(std::map<_AttrType, _ObjType>& list, const string & elemName, const string & keyName) {
    if(mWrite)
      return SetNodeMap(list, elemName, keyName);
    return GetNodeMap(list, elemName, keyName);
  }

  template<typename _Type>
  template<typename _AttrType, typename _ObjType>
  inline const bool CXmlSerialize<_Type>::GetNodeMap(std::map<_AttrType, _ObjType>& list, const string & elemName, const string & keyName, const string & valName) const {
    list.clear();
    XmlNodePtrListT nodeList = mNode.Nodes.Search(elemName);

    for(XmlNodePtrListT::const_iterator it = nodeList.begin(); it != nodeList.end(); it++) {
      const CXmlNode& node = **it;
      _ObjType obj;
      _AttrType key;

      CXmlSerialize<_ObjType> xml(node, obj);

      if(!xml.GetAttribute(keyName, key)) {
        return false;
      }

      if(!xml.GetAttribute(valName, obj)) {
        return false;
      }

      list[key] = obj;
    }

    return true;
  }

  template<typename _Type>
  template<typename _AttrType, typename _ObjType>
  inline const bool CXmlSerialize<_Type>::SetNodeMap(const std::map<_AttrType, _ObjType>& list, const string & elemName, const string & keyName, const string & valName) {
    mNode.Nodes.Remove(elemName);

    for(typename std::map<_AttrType, _ObjType>::const_iterator it = list.begin(); it != list.end(); it++) {
      CXmlNode& node = mNode.Nodes.AddNode(elemName);

      CXmlSerialize<_ObjType> xml(node, it->second);

      if(!xml.SetAttribute(keyName, it->first)) {
        return false;
      }

      if(!xml.SetAttribute(valName, it->second)) {
        return false;
      }
    }

    return true;
  }

  template<typename _Type>
  template<typename _AttrType, typename _ObjType>
  inline const bool CXmlSerialize<_Type>::RWNodeMap(std::map<_AttrType, _ObjType>& list, const string & elemName, const string & keyName, const string & valName) {
    if(mWrite)
      return SetNodeMap(list, elemName, keyName, valName);
    return GetNodeMap(list, elemName, keyName, valName);
  }
}

#define CB_DEFINEXMLREAD(OBJ) template<> const bool cb::CXmlSerialize<OBJ>::Read() 
#define CB_DEFINEXMLWRITE(OBJ) template<> const bool cb::CXmlSerialize<OBJ>::Write() 
#define CB_DEFINEXMLRW(OBJ) template<> const bool cb::CXmlSerialize<OBJ>::RWObj() 

#endif // !__CB_XML_SERIALIZE_H__
