#pragma once

#include "Defines.h"

//#ifndef ENUM_FLAG
//#define ENUM_FLAG_OPERATOR(Type,Op) \
//constexpr Type const operator Op(Type const& arg1, Type const& arg2) { \
//  return static_cast<Type const>(static_cast<cb::u32 const>(arg1) Op static_cast<cb::u32 const>(arg2)); \
//}
//#define ENUM_FLAG_ASSIGN_OPERATOR(Type,OpAss,Op) \
//constexpr Type const operator OpAss(Type& arg1, Type const& arg2) { \
//  arg1 = arg1 Op arg2; \
//  return arg1; \
//}
//#define ENUM_FLAG_DEFINE(Type) \
//enum class Type; \
//ENUM_FLAG_OPERATOR(Type, |) \
//ENUM_FLAG_OPERATOR(Type, &) \
//ENUM_FLAG_OPERATOR(Type, ^) \
//ENUM_FLAG_ASSIGN_OPERATOR(Type, |=, |) \
//ENUM_FLAG_ASSIGN_OPERATOR(Type, &=, & ) \
//ENUM_FLAG_ASSIGN_OPERATOR(Type, ^=, ^ ) \
//constexpr Type const operator ~(Type const& arg) { \
//  return static_cast<Type const>(~static_cast<cb::u32 const>(arg)); \
//} \
//constexpr bool const isTrue(Type const& arg, Type const& bits) { \
//  return static_cast<cb::u32 const>(arg & bits) > 0; \
//} \
//constexpr bool const isTrueAll(Type const& arg, Type const& bits) { \
//  return static_cast<cb::u32 const>((~(arg & bits)) & bits) == 0; \
//} \
//constexpr Type const setBit(Type const& arg, Type const& bits, bool const value) { \
//  return value ? (arg | bits) : (arg & ~bits); \
//}
//
//#define ENUM_FLAG(Type) \
//ENUM_FLAG_DEFINE(Type) \
//enum class Type 
//#endif
//


namespace cb {
  template<typename _Enum, typename _Type = uint32_t>
  class flags {
    _Type mValue;

  public:
    flags() : mValue(_Type(0)) {}
    flags(const _Enum flag)
      : mValue(static_cast<_Type>(flag)) {}

    inline void operator=(const _Enum flag) { mValue = static_cast<_Type>(flag); }

    inline flags<_Enum, _Type> operator|(const flags<_Enum, _Type>& value) const {
      return static_cast<_Enum>(mValue | value.mValue);
    }
    inline flags<_Enum, _Type> operator&(const flags<_Enum, _Type>& value) const {
      return static_cast<_Enum>(mValue & value.mValue);
    }

    inline void operator|=(const flags<_Enum, _Type>& value) {
      this->mValue |= value.mValue;
    }
    inline void operator&=(const flags<_Enum, _Type>& value) {
      this->mValue &= value.mValue;
    }

    inline operator bool() const {
      return mValue > _Type(0);
    }
    inline bool operator!() const {
      return mValue == _Type(0);
    }

    inline flags<_Enum, _Type> operator~() const {
      return static_cast<_Enum>(~mValue);
    }

    inline operator _Enum() const {
      return static_cast<_Enum>(mValue);
    }
  };
}

#define ENUM_FLAG(Type) \
enum class Type; \
using Type##s = cb::flags<Type>; \
enum class Type 

