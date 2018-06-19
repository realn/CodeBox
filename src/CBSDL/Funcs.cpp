#include "stdafx.h"
#include "../../include/CBSDL/Funcs.h"
#include "../../include/CBSDL/Consts.h"

#include <SDL_mouse.h>

namespace cb {
  namespace sdl {
    bool IsCursorVisible() {
      return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
    }

    void SetCursorVisible(bool const value) {
      SDL_ShowCursor(value ? SDL_ENABLE : SDL_DISABLE);
      CB_SDL_CHECKERRORS();
    }

    cb::string GetNameFromScanCode(ScanCode const code) {
      auto szName = SDL_GetScancodeName(static_cast<SDL_Scancode>(code));
      CB_SDL_CHECKERRORS();
      return cb::fromUtf8(cb::utf8string(szName));
    }

    ScanCode GetScanCodeFromName(cb::string const & name) {
      auto code = SDL_GetScancodeFromName(cb::toUtf8(name).c_str());
      CB_SDL_CHECKERRORS();
      return static_cast<cb::sdl::ScanCode>(code);
    }
  }
}