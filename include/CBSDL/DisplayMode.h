#pragma once

#include "Defines.h"
#include "Consts.h"

#include <SDL_video.h>

namespace cb {
  namespace sdl {
    class CDisplayMode;

    using DisplayIDVecT = std::vector<DisplayID>;
    using DisplayModeVecT = std::vector<CDisplayMode>;

    extern DisplayID DisplayIDDefault;

    class CDisplayMode {
    private:
      SDL_DisplayMode mMode;
    public:
      CDisplayMode(glm::uvec2 const& size = glm::uvec2(),
                   PixelFormat const format = PixelFormat::UNKNOWN,
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

      static DisplayModeVecT GetAll(DisplayID const& id = DisplayIDDefault);
      static CDisplayMode GetCurrent(DisplayID const& id = DisplayIDDefault);
      static CDisplayMode GetClosest(CDisplayMode const& mode, DisplayID const& id = DisplayIDDefault);
      static CDisplayMode GetFromDesktop(DisplayID const& id = DisplayIDDefault);
    };

    extern DisplayIDVecT GetAllDisplays();
  }
}