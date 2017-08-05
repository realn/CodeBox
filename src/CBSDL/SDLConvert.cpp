#include "stdafx.h"
#include "SDLConvert.h"
#include <CBSDL/DisplayMode.h>

SDL_DisplayMode convert(cb::sdl::CDisplayMode const & value) {
  return {
    static_cast<Uint32>(value.GetPixelFormat()),
    static_cast<int>(value.GetSize().x),
    static_cast<int>(value.GetSize().y),
    static_cast<int>(value.GetRefreshRate()),
    nullptr
  };
}

cb::sdl::CDisplayMode convert(SDL_DisplayMode const & value) {
  return cb::sdl::CDisplayMode(
    {static_cast<cb::u32>(value.w), static_cast<cb::u32>(value.h)}, 
    static_cast<cb::sdl::PixelFormat>(value.format),
    static_cast<cb::sdl::RefreshRate>(value.refresh_rate)
  );
}
