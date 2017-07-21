#pragma once

#include <glm/fwd.hpp>
#include <string>

namespace cb {
  using string = std::wstring;
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
