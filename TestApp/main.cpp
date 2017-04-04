
#include <iostream>

#include "../CBStr/StringEx.h"

#include "../CBLog/Logger.h"
#include "../CBLog/Log.h"

#include "../CBXml/Attribute.h"
#include "../CBXml/AttributeList.h"
#include "../CBXml/Node.h"
#include "../CBXml/NodeList.h"
#include "../CBXml/Document.h"
#include "../CBXml/Serialize.h"

#include "../CBIO/File.h"
#include "../CBIO/Path.h"

class CSubTest {
public:
  int OtherData;
  float SixData;
};

typedef std::vector<CSubTest> testList;
typedef std::map<cb::string, CSubTest> testMap;

class CTest {
public:
  cb::string mSomeData;
  CSubTest subData;
  testList someList;
  testMap someMap;
};

CB_DEFINEXMLREAD(testList) {
  return GetNodeList(mObject, L"Item");
}

CB_DEFINEXMLWRITE(testList) {
  return SetNodeList(mObject, L"Item");
}

CB_DEFINEXMLREAD(testMap) {
  return GetNodeMap(mObject, L"Item", L"Key");
}

CB_DEFINEXMLWRITE(testMap) {
  return SetNodeMap(mObject, L"Item", L"Key");
}

CB_DEFINEXMLREAD(CSubTest) {
  return
    GetAttribute(L"OtherData", mObject.OtherData) &&
    GetAttribute(L"SixData", mObject.SixData);
}

CB_DEFINEXMLWRITE(CSubTest) {
  return
    SetAttribute(L"OtherData", mObject.OtherData) &&
    SetAttribute(L"SixData", mObject.SixData);
}

CB_DEFINEXMLREAD(CTest) {
  return
    GetAttribute(L"someData", mObject.mSomeData) &&
    GetNode(L"subData", mObject.subData) &&
    GetNode(L"someList", mObject.someList) &&
    GetNode(L"someMap", mObject.someMap);
}

CB_DEFINEXMLWRITE(CTest) {
  return
    SetAttribute(L"someData", mObject.mSomeData) &&
    SetNode(L"subData", mObject.subData) &&
    SetNode(L"someList", mObject.someList) &&
    SetNode(L"someMap", mObject.someMap);
}

void main() {
  int num = 0;

  cb::CLogger log;
  log.AddStream(&std::wcout);
  cb::CLogger::SetInstance(&log);

  cb::string text = cb::replace(L"Wahahalataha", L"ha", cb::toStr(num));

  cb::info(text);

  cb::debug(cb::format(L"Number {0}, Float {1}", 1, 0.3));

  cb::CXmlAttribute attr(L"Test", L"Val");

  text = attr.ToString();
  cb::info(text);

  if(!attr.Parse(text)) {
    cb::error(L"Attribute parse failed.");
  }
  else {
    cb::info(L"AttrName: " + attr.GetName());
    cb::info(L"AttrValue: " + attr.GetValue());
  }

  cb::CXmlAttributeList attrList;
  attrList.SetValue(L"FirstVal", L"Some");
  attrList.SetValue(L"SecondVal", L"Thing");

  text = attrList.ToString();
  cb::info(text);

  attrList.Clear();
  attrList.Parse(text);
  cb::info(L"AttrVal: " + attrList.GetValue(L"SecondVal", L"Other"));

  cb::CXmlNode rootNode(L"Root");
  rootNode.Attributes.SetValue(L"First", L"Some");
  rootNode.Attributes.SetValue(L"Second", L"Here");
  {
    cb::CXmlNode& node = rootNode.Nodes.AddNode(L"OtherNode");
    node.SetValue(L"VIvi<><S<", true);
  }
  {
    cb::CXmlNode& node = rootNode.Nodes.AddNode(L"Sisi");
    node.SetValue(L"Seaskdjfsd");
  }

  text = rootNode.ToString(cb::CXmlStringFormat(true, true));
  cb::info(text);

  {
    cb::CXmlDocument xmlDoc(text);
    rootNode.Parse(text);
    cb::info(rootNode.Nodes[L"Sisi"].GetValue());
  }

  CTest test;
  test.mSomeData = L"Elo";
  test.someList.push_back(CSubTest());
  test.someMap[L"hoho"] = CSubTest();

  {
    cb::CXmlDocument xmlDoc;
    xmlDoc.RootNode.SetName(L"SomeData");
    cb::WriteXmlObject(xmlDoc.RootNode, test);

    cb::info(xmlDoc.ToString());

    cb::ReadXmlObject(xmlDoc.RootNode, test);

    cb::string tmp = xmlDoc.ToString();

    cb::writetextfileutf8(L"test.xml", tmp);
  }


  {
    cb::string tmp = cb::readtextfileutf8(L"test.xml");
    cb::info(tmp);

    cb::writetextfileutf16(L"test2.xml", tmp);
  }
  {
    cb::string tmp = cb::readtextfileutf16(L"test2.xml");

    cb::info(tmp);
  }

  std::cin.get();
}