
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

enum class SomeEnum {
  some = 0,
};
typedef std::vector<SomeEnum> SomeEnumVecT;
typedef std::map<SomeEnum, SomeEnumVecT> SomeEnumMapT;

const cb::string toStr(const SomeEnum val) {
  return L"Some";
}
const bool fromStr(const cb::string& text, SomeEnum& outVal) {
  outVal = SomeEnum::some;
  return true;
}

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
  SomeEnumVecT someEnumVec;
  SomeEnumMapT someEnumMap;
};

CB_DEFINEXMLRW(testList) {
  return RWNodeList(mObject, L"Item");
}

CB_DEFINEXMLRW(testMap) {
  return RWNodeMap(mObject, L"Item", L"Key");
}

CB_DEFINEXMLRW(CSubTest) {
  return
    RWAttribute(L"OtherData", mObject.OtherData) &&
    RWAttribute(L"SixData", mObject.SixData);
}

CB_DEFINEXMLRW(CTest) {
  return
    RWAttribute(L"someData", mObject.mSomeData) &&
    RWNode(L"subData", mObject.subData) &&
    RWNode(L"someList", mObject.someList) &&
    RWNode(L"someMap", mObject.someMap) &&
    RWAttribute(L"someEnumVec", mObject.someEnumVec) &&
    RWAttribute(mObject.someEnumMap);
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
  test.someEnumVec = {SomeEnum::some};
  test.someEnumMap[SomeEnum::some] = {SomeEnum::some, SomeEnum::some};

  {
    cb::CXmlDocument xmlDoc;
    xmlDoc.RootNode.SetName(L"SomeData");
    cb::WriteXmlObject(xmlDoc.RootNode, test);

    cb::info(xmlDoc.ToString());
    test.someMap.clear();

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