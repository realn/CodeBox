#pragma once

#include "Node.h"
#include "StringFormat.h"

namespace cb {
  class CXmlDocument {
  private:
    bool mValid;

  public:
    CXmlNode RootNode;
    CXmlStringFormat StringFormat;

    CXmlDocument();
    CXmlDocument(string const & text);

    void clear();

    bool IsValid() const;

    bool Parse(string const& text);

    string ToString() const;
  };
}
