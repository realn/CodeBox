#include "stdafx.h"
#include <CBSDL/DisplayMode.h>

#include "SDLConvert.h"
#include <numeric>

namespace cb {
  namespace sdl {
    DisplayID DisplayIDDefault = 0;

    DisplayMode::DisplayMode(glm::uvec2 const & size,
                               PixelFormat const format,
                               RefreshRate const refreshRate)
      : mFormat(format)
      , mSize(size)
      , mRefreshRate(refreshRate)
      , mDriverData(nullptr) {}

    DisplayMode::~DisplayMode() {}


    DisplayModeVecT DisplayMode::getAll(DisplayID const & id) {
      auto num = SDL_GetNumDisplayModes(id);
      CB_SDL_CHECKERRORS();
      auto result = DisplayModeVecT(size_t(num));
      for(auto i = 0u; result.size(); i++) {
        SDL_DisplayMode mode;
        SDL_GetDisplayMode(int(id), int(i), &mode);
        result[i] = convert(mode);
        CB_SDL_CHECKERRORS();
      }
      return result;
    }

    DisplayMode DisplayMode::getCurrent(DisplayID const & id) {
      auto result = SDL_DisplayMode();
      SDL_GetCurrentDisplayMode(static_cast<int>(id), &result);
      CB_SDL_CHECKERRORS();
      return convert(result);
    }

    DisplayMode DisplayMode::getClosest(DisplayMode const & mode, DisplayID const & id) {
      auto result = SDL_DisplayMode();
      auto sdlmode = convert(mode);
      SDL_GetClosestDisplayMode(static_cast<int>(id), &sdlmode, &result);
      CB_SDL_CHECKERRORS();
      return convert(result);
    }

    DisplayMode DisplayMode::getFromDesktop(DisplayID const & id) {
      auto result = SDL_DisplayMode();
      SDL_GetDesktopDisplayMode(static_cast<int>(id), &result);
      CB_SDL_CHECKERRORS();
      return convert(result);
    }

    DisplayID getDefaultDisplayID() {
      return DisplayIDDefault;
    }

    DisplayIDVecT getAllDisplays() {
      auto num = SDL_GetNumVideoDisplays();
      CB_SDL_CHECKERRORS();
      auto result = DisplayIDVecT(size_t(num));
      std::iota(result.begin(), result.end(), DisplayIDDefault);
      return result;
    }
  }
}