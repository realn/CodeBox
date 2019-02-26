#include "stdafx.h"
#include <CBXml/Serialize.h>

namespace cb {
  CXmlSerializeBase::CXmlSerializeBase(const CXmlNode& node, 
                                       const bool write)
    : mNode(const_cast<CXmlNode&>(node)) 
    , mWrite(write) {}

  CXmlSerializeBase::~CXmlSerializeBase() {}
}
