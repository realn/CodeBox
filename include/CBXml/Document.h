#pragma once

#include "Node.h"
#include "StringFormat.h"

namespace cb {
  class XmlDocument {
  private:
    bool mValid;

  public:
    XmlNode RootNode;
    XmlStringFormat StringFormat;

    XmlDocument();
    XmlDocument(string const& text);

    void clear();

    bool isValid() const;

    bool parse(string const& text);

    string toString() const;
  };
}
