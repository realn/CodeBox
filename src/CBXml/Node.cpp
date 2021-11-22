#include "stdafx.h"
#include "Funcs.h"

#include <CBCore/StringFunctions.h>
#include <CBXml/NodeList.h>

#include <CBXml/Node.h>

namespace cb {
  XmlNode::XmlNode(string const& name)
    : mType(XmlNodeType::Normal)
    , mName(name) {
  }

  XmlNode::XmlNode(XmlNodeType const type, string const& value)
    : mType(type)
    , mName(value) {
  }

  XmlNode::XmlNode(XmlNode const& other)
    : Attributes(other.Attributes)
    , Nodes(other.Nodes)
    , mType(other.mType)
    , mName(other.mName) {
  }

  XmlNode::XmlNode(XmlNode&& other)
    : Attributes(std::move(other.Attributes))
    , Nodes(std::move(other.Nodes))
    , mType(other.mType)
    , mName(std::move(other.mName)) {
  }

  XmlNode::~XmlNode() {}

  void XmlNode::setValue(string const& value, bool const cdata) {
    if (Nodes.size() != 1) {
      Nodes.clear();
      Nodes.addNode(XmlNodeType::text);
    }
    auto& node = Nodes.first();

    node.SetType(cdata ? XmlNodeType::CData : XmlNodeType::text);
    node.SetName(value);
  }

  string XmlNode::getValue() const {
    if (Nodes.size() != 1)
      return string();
    auto& node = Nodes.first();
    if (node.getType() != XmlNodeType::text && node.getType() != XmlNodeType::CData)
      return string();
    return node.getName();
  }

  void XmlNode::clear() {
    Nodes.clear();
    Attributes.clear();
  }

  size_t XmlNode::parse(string const& text, size_t const offset, cb::ostream& err) {
    auto pos = findNonWS(text, offset);
    if (pos == string::npos) {
      err << L"Unexpected end of string." << std::endl;
      return string::npos;
    }

    // check for starting tag
    if (!subcmp(text, XML_TAG_START, pos)) {
      // if there is no starting tag, then it's a text node
      mType = XmlNodeType::text;

      // find begining of new node - this will mark the end of the text node
      auto endpos = text.find(XML_TAG_START, pos);
      if (endpos == string::npos) {
        err << L"Invalid tag end, node is incompleted." << std::endl;
        return string::npos;
      }

      mName = unescapeTagChars(substrpos(text, pos, endpos));
      return endpos;
    }

    if (subcmp(text, XML_CDATA_TAG_START, pos)) {
      // it's an cdata node
      pos += XML_CDATA_TAG_START.length();
      auto endpos = text.find(XML_CDATA_TAG_END, pos);
      if (endpos == string::npos) {
        err << L"Failed to find tag ending, inalid node." << std::endl;
        return string::npos;
      }

      mType = XmlNodeType::CData;
      mName = substrpos(text, pos, endpos);
      return endpos + XML_CDATA_TAG_END.length();
    }

    if (subcmp(text, XML_TAG_CLOSE_START, pos)) {
      err << L"Invalid tag closing, invalid node." << std::endl;
      return string::npos;
    }

    // it must be a normal xml tag
    mType = XmlNodeType::Normal;

    // find name begining
    pos = findNonWS(text, pos + XML_TAG_START.length());
    if (pos == string::npos) {
      err << L"Failed to find tag name begining." << std::endl;
      return string::npos;
    }

    // find name ending
    auto endpos = findWS(text, pos, XML_TAG_END_LIST);
    if (endpos == string::npos) {
      err << L"Failed to find tag name ending." << std::endl;
      return string::npos;
    }

    // found tag name
    mName = substrpos(text, pos, endpos);
    if (mName.empty()) {
      err << L"Empty node name, invalid node." << std::endl;
      return string::npos;
    }

    // parse possible attributes
    pos = Attributes.parse(text, endpos, err);
    if (pos == string::npos) {
      err << L"Error while parsing node " << mName << L" attributes, invalid node." << std::endl;
      return string::npos;
    }

    // find tag ending
    pos = findXml(text, XML_TAG_END_LIST, pos);
    if (pos == string::npos) {
      err << L"Failed tag ending of node " << mName << L", invalid node." << std::endl;
      return string::npos;
    }

    if (subcmp(text, XML_TAG_CLOSE_END, pos)) {
      // tag is self closed - finished parsing
      return pos + XML_TAG_CLOSE_END.length();
    }

    // tag has possible sub nodes;
    pos = Nodes.parse(text, pos + XML_TAG_END.length());
    if (pos == string::npos) {
      err << L"Error while parsing sub nodes of node " << mName << std::endl;
      return string::npos;
    }

    if (!subcmp(text, XML_TAG_CLOSE_START, pos)) {
      err << L"Missing closing tag start for node " << mName << std::endl;
      return string::npos;
    }

    pos = findNonWS(text, pos + XML_TAG_CLOSE_START.length());
    if (pos == string::npos) {
      err << L"Failed to find ending tag name for node " << mName << L", unexpected end of string." << std::endl;
      return string::npos;
    }
    endpos = findWS(text, pos, XML_TAG_END_LIST);
    if (endpos == string::npos) {
      err << L"Failed to find ending tag name ending for node " << mName << L", unexpected end of string." << std::endl;
      return string::npos;
    }

    auto endName = substrpos(text, pos, endpos);
    if (mName != endName) {
      err << mName << L" and its ending tag " << endName << L" does not match." << std::endl;
      return string::npos;
    }

    pos = findNonWS(text, endpos);
    if (pos == string::npos) {
      err << L"Could not find ending of closing tag for node " << mName << ", unexpected end of string." << std::endl;
      return string::npos;
    }

    if (!subcmp(text, XML_TAG_END, pos)) {
      err << L"Invalid enging for closing tag for node " << mName << std::endl;
      return string::npos;
    }

    return pos + XML_TAG_END.length();
  }

  string XmlNode::toString(XmlStringFormat const& fmt) const {
    auto padding = genPadding(fmt);
    auto ending = genEnding(fmt);

    if (mType == XmlNodeType::text) {
      return padding + escapeTagChars(mName);
    }
    if (mType == XmlNodeType::CData) {
      return padding + XML_CDATA_TAG_START + mName + XML_CDATA_TAG_END;
    }

    string result = padding + XML_TAG_START + mName;
    if (!Attributes.empty()) {
      result += XML_SPACE + Attributes.toString();
    }

    if (Nodes.empty()) {
      result += XML_SPACE + XML_TAG_CLOSE_END;
    }
    else {
      auto format = XmlStringFormat(fmt);
      format.mNestingLevel++;

      result += XML_TAG_END + ending;
      result += Nodes.toString(format) + ending;
      result += padding + XML_TAG_CLOSE_START + mName + XML_TAG_END;
    }
    return result;
  }

  void XmlNode::operator=(XmlNode const& other) {
    mType = other.mType;
    mName = other.mName;
    Attributes = other.Attributes;
    Nodes = other.Nodes;
  }

  void XmlNode::operator=(XmlNode&& other) {
    mType = other.mType;
    mName = std::move(other.mName);
    Attributes = std::move(other.Attributes);
    Nodes = std::move(other.Nodes);
  }

  void XmlNode::operator=(string const& value) {
    setValue(value);
  }
}
