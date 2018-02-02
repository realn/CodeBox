#include "stdafx.h"
#include "../../include/CBSDL/Funcs.h"

#include <SDL_mouse.h>

namespace cb {
  namespace sdl {
    bool IsCursorVisible() {
      return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
    }

    void SetCursorVisible(bool const value) {
      SDL_ShowCursor(value ? SDL_ENABLE : SDL_DISABLE);
    }
  }
}