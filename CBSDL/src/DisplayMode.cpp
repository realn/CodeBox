#include "stdafx.h"
#include "../DisplayMode.h"

#include <numeric>

namespace cb {
  namespace sdl {
    DisplayID DisplayIDDefault = 0;

    CDisplayMode::CDisplayMode(glm::uvec2 const & size,
                               PixelFormat const format,
                               RefreshRate const refreshRate) {
      mMode.w = static_cast<int>(size.x);
      mMode.h = static_cast<int>(size.y);
      mMode.format = static_cast<Uint32>(format);
      mMode.refresh_rate = refreshRate;
      mMode.driverdata = nullptr;
    }
    CDisplayMode::CDisplayMode(CDisplayMode && other) {
      mMode = std::move(other.mMode);
    }
    CDisplayMode::CDisplayMode(SDL_DisplayMode const & mode)
      : mMode(mode) {}

    CDisplayMode::~CDisplayMode() {}

    void CDisplayMode::SetSize(glm::uvec2 const & size) {
      mMode.w = static_cast<int>(size.x);
      mMode.h = static_cast<int>(size.y);
    }

    void CDisplayMode::SetPixelFormat(PixelFormat const value) {
      mMode.format = static_cast<Uint32>(value);
    }

    void CDisplayMode::SetRefreshRate(RefreshRate const value) {
      mMode.refresh_rate = static_cast<int>(value);
    }

    glm::uvec2 CDisplayMode::GetSize() const {
      return glm::uvec2(static_cast<Uint32>(mMode.w), 
                        static_cast<Uint32>(mMode.h));
    }

    PixelFormat CDisplayMode::GetPixelFormat() const {
      return static_cast<PixelFormat>(mMode.format);
    }

    RefreshRate CDisplayMode::GetRefreshRate() const {
      return static_cast<RefreshRate>(mMode.refresh_rate);
    }

    DisplayModeVecT CDisplayMode::GetAll(DisplayID const & id) {
      auto num = SDL_GetNumDisplayModes(id);
      CB_SDL_CHECKERRORS();
      auto result = DisplayModeVecT(size_t(num));
      for(auto i = 0u; result.size(); i++) {
        SDL_GetDisplayMode(int(id), int(i), &result[i].Get());
        CB_SDL_CHECKERRORS();
      }
      return result;
    }

    CDisplayMode CDisplayMode::GetCurrent(DisplayID const & id) {
      auto result = SDL_DisplayMode();
      SDL_GetCurrentDisplayMode(static_cast<int>(id), &result);
      CB_SDL_CHECKERRORS();
      return CDisplayMode(result);
    }

    CDisplayMode CDisplayMode::GetClosest(CDisplayMode const & mode, DisplayID const & id) {
      auto result = SDL_DisplayMode();
      SDL_GetClosestDisplayMode(static_cast<int>(id), &mode.Get(), &result);
      CB_SDL_CHECKERRORS();
      return CDisplayMode(result);
    }

    CDisplayMode CDisplayMode::GetFromDesktop(DisplayID const & id) {
      auto result = SDL_DisplayMode();
      SDL_GetDesktopDisplayMode(static_cast<int>(id), &result);
      CB_SDL_CHECKERRORS();
      return CDisplayMode(result);
    }

    DisplayIDVecT GetAllDisplays() {
      auto num = SDL_GetNumVideoDisplays();
      CB_SDL_CHECKERRORS();
      auto result = DisplayIDVecT(size_t(num));
      std::iota(result.begin(), result.end(), DisplayIDDefault);
      return result;
    }
  }
}