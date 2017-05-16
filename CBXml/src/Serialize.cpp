#include "stdafx.h"
#include "../Serialize.h"
#include "../../CBStr/StringEx.h"

const cb::string cb::CXmlSerializeBase::ATTR_DEF_LIST_SEP = L",";

namespace cb {
  CXmlSerializeBase::CXmlSerializeBase(const CXmlNode& node, 
                                       const bool write)
    : mNode(const_cast<CXmlNode&>(node)) 
    , mWrite(write) {}

  CXmlSerializeBase::~CXmlSerializeBase() {}

  const strvector CXmlSerializeBase::split(const string & text, const string & sep) {
    return cb::split(text, sep, true);
  }
  const string CXmlSerializeBase::join(const strvector & list, const string & sep) {
    return cb::join(list, sep);
  }
}
