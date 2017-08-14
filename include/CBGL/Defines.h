#pragma once

#include <glm/fwd.hpp>
#include <string>

namespace cb {
  using s8 = signed char;
  using s16 = signed short;
  using s32 = signed int;
  using s64 = signed __int64;

  using u8 = unsigned char;
  using u16 = unsigned short;
  using u32 = unsigned int;
  using u64 = unsigned __int64;

  using string = std::wstring;

  namespace gl {
    using OGLObjId = unsigned;
    using AttributeId = unsigned;
    using UniformId = unsigned;

    template<typename _Type, typename _BindFunc, typename _UnBindFunc>
    class CBindGuard {
    private:
      _Type const* mObj;
      _BindFunc mBind;
      _UnBindFunc mUnBind;

    public:
      CBindGuard(_Type const& obj, _BindFunc bindFunc, _UnBindFunc unBindFunc)
        : mObj(&obj), mBind(bindFunc), mUnBind(unBindFunc) {
        mBind(mObj);
      }
      CBindGuard(CBindGuard<_Type, _BindFunc, _UnBindFunc> const&) = delete;
      CBindGuard(CBindGuard<_Type, _BindFunc, _UnBindFunc>&& other)
        : mObj(other.mObj), mBind(other.mBind), mUnBind(other.mUnBind) {
        other.mObj = nullptr;
      }
      ~CBindGuard() {
        if(mObj) mUnBind(mObj);
      }
    };

    template<typename _Type, typename ... _Args>
    auto bind(_Type const& obj, _Args ... args) {
      auto bindFunc = [args...](_Type const* obj)->void{ obj->Bind(args...); };
      auto unBindFunc = [args...](_Type const* obj)->void{ obj->UnBind(args...); };
      return CBindGuard<_Type, decltype(bindFunc), decltype(unBindFunc)>(obj, bindFunc, unBindFunc);
    }
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
