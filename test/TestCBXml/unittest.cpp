#include "stdafx.h"
#include "CppUnitTest.h"

#include <CBCore/StringConvert.h>
#include <CBCore/StringFunctions.h>
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
bool cb::XmlSerialize<DummySubClass>::process() {
  return
    processAttribute(L"mVal0", mObject.mVal0) &&
    processAttribute(L"mName", mObject.mName);
}

template<>
bool cb::XmlSerialize<DummyClass>::process() {
  return
    processAttribute(L"mVal0", mObject.mVal0) &&
    processAttribute(L"mVal1", mObject.mVal1) &&
    processNode(L"mSubClass", mObject.mSubClass) &&
    processNodeList(mObject.mVector, L"mVectorItem") &&
    processNodeMap(mObject.mMap, L"mMapItem", L"Key");
}

namespace TestCBXml {
  TEST_CLASS(CBXmlUnitTest) {
  public:
    TEST_METHOD(BasicXmlManipulationTest) {
      auto attrib = cb::XmlAttribute(L"TestAttrib", L"TestValue");
      Assert::AreEqual(L"TestAttrib=\"TestValue\""s, attrib.toString(), L"Attribute::ToString failed.", LINE_INFO());

      auto attribList = cb::XmlAttributeList();
      attribList.setValue(L"test1", L"o");
      attribList.setValue(L"test2", L"value");
      Assert::AreEqual(L"test1=\"o\" test2=\"value\""s, attribList.toString(), L"AttributeList::Tostring failed.", LINE_INFO());
      Assert::AreEqual(L"value"s, attribList.getValue(L"test2"), L"AttribList::GetValue failed.", LINE_INFO());
      Assert::AreEqual(L"none"s, attribList.getValue(L"test3", L"none"), L"AttrbList::GetValueDef failed.", LINE_INFO());

      auto fmt = cb::XmlStringFormat(false, false);
      auto node = cb::XmlNode(L"TestNode");
      node.Attributes.setValue(L"test", L"value");
      Assert::AreEqual(L"<TestNode test=\"value\" />"s, node.toString(fmt), L"Node::ToString failed.", LINE_INFO());

      node.Nodes.addNode(L"SubNode");
      {
        auto otherNode = cb::XmlNode(L"OtherNode");
        otherNode.setValue(L"SOMEDATA");
        node.Nodes.addNode(std::move(otherNode));
      }
      Assert::AreEqual(L"<TestNode test=\"value\"><SubNode /><OtherNode>SOMEDATA</OtherNode></TestNode>"s, node.toString(fmt), L"Node::ToString (1) failed.", LINE_INFO());

      node[L"OtherNode"].setValue(L"SOMEDATA", true);
      Assert::AreEqual(L"<TestNode test=\"value\"><SubNode /><OtherNode><![CDATA[SOMEDATA]]/></OtherNode></TestNode>"s, node.toString(fmt), L"Node::ToString (1) failed.", LINE_INFO());
    }

    TEST_METHOD(XmlSerializationTest) {
      auto test = DummyClass();
      auto node = cb::XmlNode();

      Assert::IsTrue(cb::writeXmlObject(node, test), L"Serialization failed.", LINE_INFO());
      Assert::AreEqual(L"Test"s, cb::string(node[L"mSubClass"].Attributes[L"mVal0"]), L"Serialized value get failed.", LINE_INFO());

      node[L"mSubClass"].Attributes[L"mVal0"] = L"Other";
      Assert::IsTrue(cb::readXmlObject(node, test), L"Deserialization failed.", LINE_INFO());
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

      auto node = cb::XmlNode(rootName);
      node[subNodeName1].Attributes[attrName] = attrValue;
      node[subNodeName2] = tagValue;
      node[subNodeName3].setValue(tagValue, true);

      auto nodeText = node.toString();
      node.clear();
      Assert::IsFalse(node.parse(nodeText) == cb::string::npos, L"XML Node parsing failed.", LINE_INFO());

      Assert::AreEqual(rootName, node.getName(), L"Root name not equal.", LINE_INFO());
      Assert::AreEqual(attrValue, node[subNodeName1].Attributes[attrName].getValue(), L"Attribute name not equal.", LINE_INFO());
      Assert::AreEqual(tagValue, node[subNodeName2].getValue(), L"Text value not equal.", LINE_INFO());
      Assert::AreEqual(tagValue, node[subNodeName3].getValue(), L"CData value data node equal.", LINE_INFO());
    }
  };
}