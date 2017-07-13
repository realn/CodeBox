#pragma once

#include "Defines.h"
#include <SDL_video.h>

namespace cb {
  namespace sdl {
    enum class PixelFormat;

    class CDisplayMode {
    private:
      SDL_DisplayMode mMode;
    public:
      CDisplayMode(glm::uvec2 const& size,
                   PixelFormat const format,
                   RefreshRate const refreshRate = 0);
      CDisplayMode(CDisplayMode const &) = delete;
      CDisplayMode(CDisplayMode && other);
      explicit CDisplayMode(SDL_DisplayMode const& mode);
      ~CDisplayMode();

      void SetSize(glm::uvec2 const & size);
      void SetPixelFormat(PixelFormat const value);
      void SetRefreshRate(RefreshRate const value);

      glm::uvec2 GetSize() const;
      PixelFormat GetPixelFormat() const;
      RefreshRate GetRefreshRate() const;

      SDL_DisplayMode& Get() { return mMode; }
      const SDL_DisplayMode& Get() const { return mMode; }

      void operator=(CDisplayMode const & other) = delete;
    };
  }
}