#pragma once

#include <SDL.h>

namespace cb {
  namespace sdl {
    class CDisplayMode;
  }
}

extern SDL_DisplayMode convert(cb::sdl::CDisplayMode const& value);
extern cb::sdl::CDisplayMode convert(SDL_DisplayMode const& value);


