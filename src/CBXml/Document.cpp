#include "stdafx.h"
#include <CBXml/Document.h>

namespace cb {
  XmlDocument::XmlDocument()
    : mValid(false)
    , StringFormat(true, true) {
  }

  XmlDocument::XmlDocument(string const& text)
    : mValid(false)
    , StringFormat(true, true) {
    parse(text);
  }

  void XmlDocument::clear() {
    RootNode.clear();
    mValid = false;
  }

  bool XmlDocument::isValid() const {
    return mValid;
  }

  bool XmlDocument::parse(string const& text) {
    clear();
    mValid = RootNode.parse(text) != string::npos;
    return mValid;
  }

  string XmlDocument::toString() const {
    return RootNode.toString(StringFormat);
  }
}