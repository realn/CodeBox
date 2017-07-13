#pragma once

#include <string>

#include <SDL_types.h>
#include <glm/fwd.hpp>

namespace cb {
  using string = std::wstring;

  namespace sdl {
    using RefreshRate = Uint32;
  }
}