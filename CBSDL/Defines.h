#pragma once

#include <string>
#include <vector>

#include <SDL_types.h>
#include <glm/fwd.hpp>

namespace cb {
  using string = std::wstring;

  namespace sdl {
    using RefreshRate = Uint32;
    using WindowID = Uint32;
    using DisplayID = Uint32;
    using MouseID = Uint32;
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
