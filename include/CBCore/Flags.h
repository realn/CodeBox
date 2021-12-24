#pragma once

#include "Defines.h"

namespace cb {
  template<typename _Enum, typename _Type = uint32_t, typename = std::is_enum<_Enum>>
  class flags {
    _Type mValue = _Type(0);

  public:
    flags() = default;
    flags(const _Enum flag)
      : mValue(static_cast<_Type>(flag)) {
    }
    flags(const std::initializer_list<_Type>& list) {
      for (const auto& item : list)
        *this |= item;
    }

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

    inline operator _Type() const {
      return mValue;
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

    inline _Enum get() const {
      return static_cast<_Enum>(mValue);
    }
  };
}

#define ENUM_FLAG(Type) \
enum class Type; \
using Type##s = cb::flags<Type>; \
enum class Type 

