#include "stdafx.h"
#include "../Node.h"
#include "../NodeList.h"

#include "Funcs.h"

#include <CBStr/StringEx.h>

namespace cb {
  CXmlNode::CXmlNode(const string name)
    : mType(XmlNodeType::Normal)
    , mName(name)
  {
  }

  CXmlNode::CXmlNode(const XmlNodeType type, const string value)
    : mType(type)
    , mName(value)
  {}

  CXmlNode::CXmlNode(const CXmlNode & other) 
    : Attributes(other.Attributes)
    , Nodes(other.Nodes)
    , mType(other.mType)
    , mName(other.mName)
  {}

  CXmlNode::CXmlNode(CXmlNode && other) 
    : Attributes(std::move(other.Attributes))
    , Nodes(std::move(other.Nodes))
    , mType(other.mType)
    , mName(std::move(other.mName))
  {}

  CXmlNode::~CXmlNode() {}

  void CXmlNode::SetValue(const string & value, const bool cdata) {
    if(Nodes.size() != 1) {
      Nodes.clear();
      Nodes.AddNode(XmlNodeType::Text);
    }
    auto& node = Nodes.first();

    node.SetType(cdata ? XmlNodeType::CData : XmlNodeType::Text);
    node.SetName(value);
  }

  string CXmlNode::GetValue() const {
    if(Nodes.size() != 1)
      return string();
    auto& node = Nodes.first();
    if(node.GetType() != XmlNodeType::Text && node.GetType() != XmlNodeType::CData)
      return string();
    return node.GetName();
  }

  size_t CXmlNode::Parse(const string & text, const size_t offset) {
    auto pos = findNonWS(text, offset);

    // check for starting tag
    if(!subcmp(text, XML_TAG_START, pos)) {
      // if there is no starting tag, then it's a text node
      mType = XmlNodeType::Text;

      // find begining of new node - this will mark the end of the text node
      auto endpos = text.find(XML_TAG_START, pos);

      mName = unescapeXmlChars(substrpos(text, pos, endpos));
      return endpos;
    }

    if(subcmp(text, XML_CDATA_TAG_START, pos)) {
      // it's an cdata node
      pos += XML_CDATA_TAG_START.length();
      auto endpos = text.find(XML_CDATA_TAG_END, pos);

      if(endpos == string::npos) {
        // it's an invaid node
        return string::npos;
      }

      mType = XmlNodeType::CData;
      mName = substrpos(text, pos, endpos);
      return endpos + XML_CDATA_TAG_END.length();
    }

    if(subcmp(text, XML_TAG_CLOSE_START, pos)) {
      // invalid end tag 
      return string::npos;
    }

    // it must be a normal xml tag
    mType = XmlNodeType::Normal;
    
    // find name begining
    pos = findNonWS(text, pos + XML_TAG_START.length());

    // find name ending
    auto endpos = findWS(text, pos, XML_TAG_END_LIST);

    if(pos == endpos || pos == string::npos || endpos == string::npos) {
      return string::npos;
    }

    // found tag name
    mName = substrpos(text, pos, endpos);

    // parse possible attributes
    pos = Attributes.Parse(text, endpos);

    // find tag ending
    pos = findXml(text, XML_TAG_END_LIST, pos);
    if(pos == string::npos) {
      return string::npos;
    }

    if(subcmp(text, XML_TAG_CLOSE_END, pos)) {
      // tag is self closed - finished parsing
      return pos + XML_TAG_CLOSE_END.length();
    }

    // tag has possible sub nodes;
    pos = Nodes.Parse(text, pos + XML_TAG_END.length());

    if(!subcmp(text, XML_TAG_CLOSE_START, pos)) {
      // missing close tag start
      return string::npos;
    }

    pos = findNonWS(text, pos + XML_TAG_CLOSE_START.length());
    endpos = findWS(text, pos, XML_TAG_END_LIST);

    if(mName != substrpos(text, pos, endpos)) {
      // invalid closing tag name
      return string::npos;
    }

    pos = findNonWS(text, endpos);

    if(!subcmp(text, XML_TAG_END, pos)) {
      // invalid closing tag ending
      return string::npos;
    }

    return pos + XML_TAG_END.length();
  }

  string CXmlNode::ToString(const CXmlStringFormat& fmt) const {
    auto padding = genPadding(fmt);
    auto ending = genEnding(fmt);

    if(mType == XmlNodeType::Text) {
      return padding + escapeXmlChars(mName);
    }
    if(mType == XmlNodeType::CData) {
      return padding + XML_CDATA_TAG_START + mName + XML_CDATA_TAG_END;
    }

    string result = padding + XML_TAG_START + mName;
    if(!Attributes.empty()) {
      result += XML_SPACE + Attributes.ToString();
    }

    if(Nodes.empty()) {
      result += XML_SPACE + XML_TAG_CLOSE_END;
    }
    else {
      auto format = CXmlStringFormat(fmt);
      format.mNestingLevel++;

      result += XML_TAG_END + ending;
      result += Nodes.ToString(format) + ending;
      result += padding + XML_TAG_CLOSE_START + mName + XML_TAG_END;
    }
    return result;
  }

  void CXmlNode::operator=(const CXmlNode & other) {
    mType = other.mType;
    mName = other.mName;
    Attributes = other.Attributes;
    Nodes = other.Nodes;
  }

  void CXmlNode::operator=(CXmlNode && other) {
    mType = other.mType;
    mName = std::move(other.mName);
    Attributes = std::move(other.Attributes);
    Nodes = std::move(other.Nodes);
  }
}
