#pragma once

#include <map>

#include <SDL_video.h>

#include "Defines.h"

namespace cb {
  namespace sdl {
    class CWindow;

    using GLAttributeMapT = std::map<SDL_GLattr, int>;

    class CGLContext {
    private:
      SDL_GLContext mContext = nullptr;

    public:
      CGLContext(CWindow& window, GLAttributeMapT const & attributes);
      ~CGLContext();

      void MakeCurrent(CWindow& window);
      void SwapWindow(CWindow& window);
    };
  }
}