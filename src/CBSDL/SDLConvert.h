#pragma once

#include <SDL.h>

namespace cb {
  namespace sdl {
    class DisplayMode;
  }
}

extern SDL_DisplayMode convert(cb::sdl::DisplayMode const& value);
extern cb::sdl::DisplayMode convert(SDL_DisplayMode const& value);


