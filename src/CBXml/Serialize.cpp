#include "stdafx.h"
#include <CBXml/Serialize.h>

namespace cb {
  CXmlUserData::~CXmlUserData() {}

  CXmlSerializeBase::CXmlSerializeBase(const CXmlNode& node,
                                       const bool write,
                                       std::shared_ptr<CXmlUserData> userData)
    : mNode(const_cast<CXmlNode&>(node))
    , mWrite(write)
    , mUserData(userData) {}

  CXmlSerializeBase::~CXmlSerializeBase() {}
}
