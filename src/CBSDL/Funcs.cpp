#include "stdafx.h"
#include <CBSDL/Consts.h>
#include <CBSDL/Funcs.h>
#include <CBCore/StringConvert.h>

#include <SDL_mouse.h>

namespace cb {
  namespace sdl {
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