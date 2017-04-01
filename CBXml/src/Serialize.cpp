#include "stdafx.h"
#include "../Serialize.h"

namespace cb {
  CXmlSerializeBase::CXmlSerializeBase(const CXmlNode& node)
    : mNode(const_cast<CXmlNode&>(node)) {}

  CXmlSerializeBase::~CXmlSerializeBase() {}
}
