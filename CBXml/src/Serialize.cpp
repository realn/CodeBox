#include "stdafx.h"
#include "../Serialize.h"
#include "../../CBStr/StringEx.h"

namespace cb {
  CXmlSerializeBase::CXmlSerializeBase(const CXmlNode& node, 
                                       const bool write)
    : mNode(const_cast<CXmlNode&>(node)) 
    , mWrite(write) {}

  CXmlSerializeBase::~CXmlSerializeBase() {}
}
