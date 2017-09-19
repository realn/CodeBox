#pragma once

#include <string>
#include <vector>

#include <glm/fwd.hpp>

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

  using byte = unsigned char;
  using bytevector = std::vector<byte>;

  namespace sdl {
    using RefreshRate = u32;
    using WindowID = u32;
    using DisplayID = u32;
    using MouseID = u32;
  }
}

#ifndef ENUM_FLAG
#define ENUM_FLAG_OPERATOR(Type,Op) \
constexpr Type const operator Op(Type const& arg1, Type const& arg2) { \
  return static_cast<Type const>(static_cast<cb::u32 const>(arg1) Op static_cast<cb::u32 const>(arg2)); \
};
#define ENUM_FLAG_ASSIGN_OPERATOR(Type,OpAss,Op) \
constexpr Type const operator OpAss(Type& arg1, Type const& arg2) { \
  arg1 = arg1 Op arg2; \
  return arg1; \
};
#define ENUM_FLAG(Type) \
enum class Type; \
ENUM_FLAG_OPERATOR(Type, |) \
ENUM_FLAG_OPERATOR(Type, &) \
ENUM_FLAG_OPERATOR(Type, ^) \
ENUM_FLAG_ASSIGN_OPERATOR(Type, |=, |) \
ENUM_FLAG_ASSIGN_OPERATOR(Type, &=, & ) \
ENUM_FLAG_ASSIGN_OPERATOR(Type, ^=, ^ ) \
constexpr Type const operator ~(Type const& arg) { \
  return static_cast<Type const>(~static_cast<cb::u32 const>(arg)); \
}; \
constexpr bool const isTrueOr(Type const& arg) { \
  return static_cast<cb::u32 const>(arg) > 0; \
} \
constexpr bool const isTrueAnd(Type const& arg) { \
  return static_cast<cb::u32 const>(~arg) == 0; \
} \
enum class Type \

#endif
