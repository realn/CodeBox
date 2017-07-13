#include "stdafx.h"
#include "../DisplayMode.h"

namespace cb {
  namespace sdl {
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
      mMode.refresh_rate = value;
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
  }
}