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

  CXmlNode::~CXmlNode() {}

  void CXmlNode::SetType(const XmlNodeType type) {
    mType = type;
  }

  const XmlNodeType CXmlNode::GetType() const {
    return mType;
  }

  void CXmlNode::SetName(const string & name) {
    mName = name;
  }

  const string CXmlNode::GetName() const {
    return mName;
  }

  void CXmlNode::SetValue(const string & value, const bool cdata) {
    if(Nodes.GetSize() != 1) {
      Nodes.Clear();
      Nodes.AddNode(XmlNodeType::Text);
    }
    CXmlNode& node = Nodes.Get(0);

    node.SetType(cdata ? XmlNodeType::CData : XmlNodeType::Text);
    node.SetName(value);
  }

  const string CXmlNode::GetValue() const {
    if(Nodes.GetSize() != 1)
      return string();
    const CXmlNode& node = Nodes.Get(0);
    if(node.GetType() != XmlNodeType::Text && node.GetType() != XmlNodeType::CData)
      return string();
    return node.GetName();
  }

  const size_t CXmlNode::Parse(const string & text, const size_t offset) {
    size_t pos = findNonWS(text, offset);
    size_t endpos = 0;

    // check for starting tag
    if(!subcmp(text, g_xmlTagStart, pos)) {
      // if there is no starting tag, then it's a text node
      mType = XmlNodeType::Text;

      // find begining of new node - this will mark the end of the text node
      endpos = text.find(g_xmlTagStart, pos);

      mName = unescapeXmlChars(substrpos(text, pos, endpos));
      return endpos;
    }

    if(subcmp(text, g_cdataStartTag, pos)) {
      // it's an cdata node
      pos += g_cdataStartTag.length();
      size_t endpos = text.find(g_cdataEndTag, pos);

      if(endpos == string::npos) {
        // it's an invaid node
        return string::npos;
      }

      mType = XmlNodeType::CData;
      mName = substrpos(text, pos, endpos);
      return endpos + g_cdataEndTag.length();
    }

    if(subcmp(text, g_xmlTagCloseStart, pos)) {
      // invalid end tag 
      return string::npos;
    }

    // it must be a normal xml tag
    mType = XmlNodeType::Normal;
    
    // find name begining
    pos = findNonWS(text, pos + g_xmlTagStart.length());

    // find name ending
    endpos = findWS(text, pos, g_xmlTagEndList);

    if(pos == endpos || pos == string::npos || endpos == string::npos) {
      return string::npos;
    }

    // found tag name
    mName = substrpos(text, pos, endpos);

    // parse possible attributes
    pos = Attributes.Parse(text, endpos);

    // find tag ending
    pos = findXml(text, g_xmlTagEndList, pos);
    if(pos == string::npos) {
      return string::npos;
    }

    if(subcmp(text, g_xmlTagCloseEnd, pos)) {
      // tag is self closed - finished parsing
      return pos + g_xmlTagCloseEnd.length();
    }

    // tag has possible sub nodes;
    pos = Nodes.Parse(text, pos + g_xmlTagEnd.length());

    if(!subcmp(text, g_xmlTagCloseStart, pos)) {
      // missing close tag start
      return string::npos;
    }

    pos = findNonWS(text, pos + g_xmlTagCloseStart.length());
    endpos = findWS(text, pos, g_xmlTagEndList);

    if(mName != substrpos(text, pos, endpos)) {
      // invalid closing tag name
      return string::npos;
    }

    pos = findNonWS(text, endpos);

    if(!subcmp(text, g_xmlTagEnd, pos)) {
      // invalid closing tag ending
      return string::npos;
    }

    return pos + g_xmlTagEnd.length();
  }

  const string CXmlNode::ToString(const CXmlStringFormat& fmt) const {
    string padding = genPadding(fmt);
    string ending = genEnding(fmt);

    if(mType == XmlNodeType::Text) {
      return padding + escapeXmlChars(mName);
    }
    if(mType == XmlNodeType::CData) {
      return padding + g_cdataStartTag + mName + g_cdataEndTag;
    }

    string result = padding + L"<" + mName;
    if(!Attributes.IsEmpty()) {
      result += L" " + Attributes.ToString();
    }

    if(Nodes.IsEmpty()) {
      result += L" />";
    }
    else {
      CXmlStringFormat format(fmt);
      format.mNestingLevel++;

      result += L">" + ending;
      result += Nodes.ToString(format) + ending;
      result += padding + L"</" + mName + L">";
    }
    return result;
  }

  void CXmlNode::operator=(const CXmlNode & other) {
    mType = other.mType;
    mName = other.mName;
    Attributes = other.Attributes;
    Nodes = other.Nodes;
  }

}
