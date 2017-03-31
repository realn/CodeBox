#ifndef __CB_XML_DOCUMENT_H__
#define __CB_XML_DOCUMENT_H__

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
    CXmlDocument(const string& text);

    void Clear();

    const bool IsValid() const;

    const bool Parse(const string& text);

    const string ToString() const;
  };
}

#endif // !__CB_XML_DOCUMENT_H__