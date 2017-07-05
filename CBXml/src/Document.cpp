#include "stdafx.h"
#include "../Document.h"

namespace cb {
  CXmlDocument::CXmlDocument()
    : mValid(false)
    , StringFormat(true, true)
  {}

  CXmlDocument::CXmlDocument(const string & text) 
    : mValid(false)
    , StringFormat(true, true)
  {
    Parse(text);
  }

  void CXmlDocument::Clear() {
    RootNode.Attributes.clear();
    RootNode.Nodes.clear();
    mValid = false;
  }

  const bool CXmlDocument::IsValid() const {
    return mValid;
  }

  const bool CXmlDocument::Parse(const string & text) {
    Clear();
    mValid = RootNode.Parse(text) != string::npos;
    return mValid;
  }

  const string CXmlDocument::ToString() const {
    return RootNode.ToString(StringFormat);
  }
}