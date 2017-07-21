#pragma once

#include <glm/fwd.hpp>
#include <string>

namespace cb {
  using string = std::wstring;

  namespace gl {
    using OGLObjId = unsigned;

    template<typename _Type>
    class CBindGuard {
    private:
      _Type const* mObj;

    public:
      CBindGuard(_Type const& obj) : mObj(&obj) { mObj->Bind(); }
      CBindGuard(CBindGuard<_Type> const&) = delete;
      CBindGuard(CBindGuard<_Type>&& other) : mObj(nullptr) { mObj = other.mObj; other.mObj = nullptr; }
      ~CBindGuard() { mObj->UnBind(); }
    };

    template<typename _Type>
    CBindGuard<_Type> bind(_Type const& obj) { return CBindGuard<_Type>(obj); }
  }
}

#ifndef ENUM_FLAG
#define ENUM_FLAG_OPERATOR(Type,Op) \
static Type const operator Op(Type const& arg1, Type const& arg2) { \
  return static_cast<Type const>(static_cast<unsigned const>(arg1) Op static_cast<unsigned const>(arg2)); \
};
#define ENUM_FLAG(Type) \
enum class Type; \
ENUM_FLAG_OPERATOR(Type, |) \
ENUM_FLAG_OPERATOR(Type, &) \
ENUM_FLAG_OPERATOR(Type, ^) \
static Type const operator ~(Type const& arg) { \
  return static_cast<Type const>(~static_cast<unsigned const>(arg)); \
}; \
enum class Type \

#endif
