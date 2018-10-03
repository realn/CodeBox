#pragma once

#ifndef ENUM_FLAG
#define ENUM_FLAG_OPERATOR(Type,Op) \
constexpr Type const operator Op(Type const& arg1, Type const& arg2) { \
  return static_cast<Type const>(static_cast<cb::u32 const>(arg1) Op static_cast<cb::u32 const>(arg2)); \
}
#define ENUM_FLAG_ASSIGN_OPERATOR(Type,OpAss,Op) \
constexpr Type const operator OpAss(Type& arg1, Type const& arg2) { \
  arg1 = arg1 Op arg2; \
  return arg1; \
}
#define ENUM_FLAG_DEFINE(Type) \
enum class Type; \
ENUM_FLAG_OPERATOR(Type, |) \
ENUM_FLAG_OPERATOR(Type, &) \
ENUM_FLAG_OPERATOR(Type, ^) \
ENUM_FLAG_ASSIGN_OPERATOR(Type, |=, |) \
ENUM_FLAG_ASSIGN_OPERATOR(Type, &=, & ) \
ENUM_FLAG_ASSIGN_OPERATOR(Type, ^=, ^ ) \
constexpr Type const operator ~(Type const& arg) { \
  return static_cast<Type const>(~static_cast<cb::u32 const>(arg)); \
} \
constexpr bool const isTrue(Type const& arg, Type const& bits) { \
  return static_cast<cb::u32 const>(arg & bits) > 0; \
} \
constexpr bool const isTrueAll(Type const& arg, Type const& bits) { \
  return static_cast<cb::u32 const>((~(arg & bits)) & bits) == 0; \
} \
constexpr Type const setBit(Type const& arg, Type const& bits, bool const value) { \
  return value ? (arg | bits) : (arg & ~bits); \
}

#define ENUM_FLAG(Type) \
ENUM_FLAG_DEFINE(Type) \
enum class Type 
#endif

