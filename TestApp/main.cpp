
#include <iostream>

#include "../CBStr/StringEx.h"

#include "../CBLog/Logger.h"
#include "../CBLog/Log.h"

#include "../CBXml/Attribute.h"
#include "../CBXml/AttributeList.h"
#include "../CBXml/Node.h"
#include "../CBXml/NodeList.h"
#include "../CBXml/Document.h"

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

  cb::CXmlDocument xmlDoc(text);
  rootNode.Parse(text);
  cb::info(rootNode.Nodes[L"Sisi"].GetValue());

  std::cin.get();
}