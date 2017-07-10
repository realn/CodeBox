#include "stdafx.h"
#include "../Document.h"

namespace cb {
  CXmlDocument::CXmlDocument()
    : mValid(false)
    , StringFormat(true, true)
  {}

  CXmlDocument::CXmlDocument(string const & text)
    : mValid(false)
    , StringFormat(true, true)
  {
    Parse(text);
  }

  void CXmlDocument::clear() {
    RootNode.clear();
    mValid = false;
  }

  bool CXmlDocument::IsValid() const {
    return mValid;
  }

  bool CXmlDocument::Parse(string const& text) {
    clear();
    mValid = RootNode.Parse(text) != string::npos;
    return mValid;
  }

  string CXmlDocument::ToString() const {
    return RootNode.ToString(StringFormat);
  }
}