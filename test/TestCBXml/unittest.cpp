#include "stdafx.h"
#include "CppUnitTest.h"

#include <CBStr/StringEx.h>
#include <CBXml/Attribute.h>
#include <CBXml/AttributeList.h>
#include <CBXml/Node.h>
#include <CBXml/NodeList.h>
#include <CBXml/Document.h>
#include <CBXml/Serialize.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::literals;

class DummySubClass {
public:
  cb::string mVal0 = L"Test";
  cb::string mName = L"Test1";

  DummySubClass() = default;
  DummySubClass(cb::string const &name) : mName(name) {}
};

class DummyClass {
public:
  unsigned mVal0 = 1;
  double mVal1 = 2;
  DummySubClass mSubClass = DummySubClass(L"SomeTest");
  std::vector<DummySubClass> mVector = {DummySubClass(L"Test0"), DummySubClass(L"Test1")};
  std::map<cb::string, DummySubClass> mMap = {{L"key0"s, DummySubClass(L"value0")},{L"key1"s, DummySubClass(L"value1")}};
};

template<>
bool cb::CXmlSerialize<DummySubClass>::RWObj() {
  return
    RWAttribute(L"mVal0", mObject.mVal0) &&
    RWAttribute(L"mName", mObject.mName);
}

template<>
bool cb::CXmlSerialize<DummyClass>::RWObj() {
  return
    RWAttribute(L"mVal0", mObject.mVal0) &&
    RWAttribute(L"mVal1", mObject.mVal1) &&
    RWNode(L"mSubClass", mObject.mSubClass) &&
    RWNodeList(mObject.mVector, L"mVectorItem") &&
    RWNodeMap(mObject.mMap, L"mMapItem", L"Key");
}

namespace TestCBXml {
  TEST_CLASS(CBXmlUnitTest) {
  public:
    TEST_METHOD(BasicXmlManipulationTest) {
      auto attrib = cb::CXmlAttribute(L"TestAttrib", L"TestValue");
      Assert::AreEqual(L"TestAttrib=\"TestValue\""s, attrib.ToString(), L"Attribute::ToString failed.", LINE_INFO());

      auto attribList = cb::CXmlAttributeList();
      attribList.SetValue(L"test1", L"o");
      attribList.SetValue(L"test2", L"value");
      Assert::AreEqual(L"test1=\"o\" test2=\"value\""s, attribList.ToString(), L"AttributeList::Tostring failed.", LINE_INFO());
      Assert::AreEqual(L"value"s, attribList.GetValue(L"test2"), L"AttribList::GetValue failed.", LINE_INFO());
      Assert::AreEqual(L"none"s, attribList.GetValue(L"test3", L"none"), L"AttrbList::GetValueDef failed.", LINE_INFO());

      auto fmt = cb::CXmlStringFormat(false, false);
      auto node = cb::CXmlNode(L"TestNode");
      node.Attributes.SetValue(L"test", L"value");
      Assert::AreEqual(L"<TestNode test=\"value\" />"s, node.ToString(fmt), L"Node::ToString failed.", LINE_INFO());

      node.Nodes.AddNode(L"SubNode");
      {
        auto otherNode = cb::CXmlNode(L"OtherNode");
        otherNode.SetValue(L"SOMEDATA");
        node.Nodes.AddNode(std::move(otherNode));
      }
      Assert::AreEqual(L"<TestNode test=\"value\"><SubNode /><OtherNode>SOMEDATA</OtherNode></TestNode>"s, node.ToString(fmt), L"Node::ToString (1) failed.", LINE_INFO());

      node[L"OtherNode"].SetValue(L"SOMEDATA", true);
      Assert::AreEqual(L"<TestNode test=\"value\"><SubNode /><OtherNode><![CDATA[SOMEDATA]]/></OtherNode></TestNode>"s, node.ToString(fmt), L"Node::ToString (1) failed.", LINE_INFO());
    }

    TEST_METHOD(XmlSerializationTest) {
      auto test = DummyClass();
      auto node = cb::CXmlNode();

      Assert::IsTrue(cb::WriteXmlObject(node, test), L"Serialization failed.", LINE_INFO());
      Assert::AreEqual(L"Test"s, cb::string(node[L"mSubClass"].Attributes[L"mVal0"]), L"Serialized value get failed.", LINE_INFO());

      node[L"mSubClass"].Attributes[L"mVal0"] = L"Other";
      Assert::IsTrue(cb::ReadXmlObject(node, test), L"Deserialization failed.", LINE_INFO());
      Assert::AreEqual(L"Other"s, test.mSubClass.mVal0, L"Object value check failed.", LINE_INFO());
    }

    TEST_METHOD(NonStandardCharsTest) {
      auto rootName = L"Root"s;
      auto attrName = L"Attr"s;
      auto subNodeName1 = L"SubNode1"s;
      auto subNodeName2 = L"SubNode2"s;
      auto subNodeName3 = L"SubNode3"s;;
      auto attrValue = L"\"\\"s;
      auto tagValue = L"<><>\"\\"s;

      auto node = cb::CXmlNode();
      node.SetName(rootName);
      node.Nodes.AddNode(subNodeName1);
      node.Nodes.AddNode(subNodeName2);
      node.Nodes.AddNode(subNodeName3);
      node[subNodeName1].Attributes.SetValue(attrName, attrValue);
      node[subNodeName2].SetValue(tagValue);
      node[subNodeName3].SetValue(tagValue, true);

      auto nodeText = node.ToString();
      node.clear();
      Assert::IsFalse(node.Parse(nodeText) == cb::string::npos, L"XML Node parsing failed.", LINE_INFO());

      Assert::AreEqual(rootName, node.GetName(), L"Root name not equal.", LINE_INFO());
      Assert::AreEqual(attrValue, node[subNodeName1].Attributes[attrName].GetValue(), L"Attribute name not equal.", LINE_INFO());
      Assert::AreEqual(tagValue, node[subNodeName2].GetValue(), L"Text value not equal.", LINE_INFO());
      Assert::AreEqual(tagValue, node[subNodeName3].GetValue(), L"CData value data node equal.", LINE_INFO());
    }
  };
}