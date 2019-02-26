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

    bool HasClipboardText() {
      return SDL_HasClipboardText() == SDL_TRUE;
    }

    void SetClipboardText(const cb::string & text) {
      auto utf8text = cb::toUtf8(text);
      SDL_SetClipboardText(utf8text.c_str());
      CB_SDL_CHECKERRORS();
    }

    cb::string GetClipboardText() {
      auto utf8text = SDL_GetClipboardText();
      CB_SDL_CHECKERRORS();
      return cb::fromUtf8(utf8text);
    }

    void SetModState(const KeyMods mods) {
      SDL_SetModState(static_cast<SDL_Keymod>(mods.Get()));
      CB_SDL_CHECKERRORS();
    }

    KeyMods GetModState() {
      auto mods = static_cast<KeyMod>(SDL_GetModState());
      CB_SDL_CHECKERRORS();
      return KeyMods(mods);
    }
  }
}