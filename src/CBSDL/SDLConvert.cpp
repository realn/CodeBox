#include "stdafx.h"
#include "SDLConvert.h"
#include <CBSDL/DisplayMode.h>

SDL_DisplayMode convert(cb::sdl::DisplayMode const & value) {
  return {
    static_cast<Uint32>(value.getPixelFormat()),
    static_cast<int>(value.getSize().x),
    static_cast<int>(value.getSize().y),
    static_cast<int>(value.getRefreshRate()),
    nullptr
  };
}

cb::sdl::DisplayMode convert(SDL_DisplayMode const & value) {
  return cb::sdl::DisplayMode(
    {static_cast<cb::u32>(value.w), static_cast<cb::u32>(value.h)}, 
    static_cast<cb::sdl::PixelFormat>(value.format),
    static_cast<cb::sdl::RefreshRate>(value.refresh_rate)
  );
}
