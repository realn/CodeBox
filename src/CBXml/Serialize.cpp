#include "stdafx.h"
#include <CBXml/Serialize.h>

namespace cb {
  XmlUserData::~XmlUserData() {}

  XmlSerializeBase::XmlSerializeBase(const XmlNode& node,
                                     const bool write,
                                     std::shared_ptr<XmlUserData> userData)
    : mNode(const_cast<XmlNode&>(node))
    , mWrite(write)
    , mUserData(userData) {
  }

  XmlSerializeBase::~XmlSerializeBase() {}
}
