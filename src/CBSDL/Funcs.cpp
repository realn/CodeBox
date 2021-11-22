#include "stdafx.h"
#include <CBSDL/Consts.h>
#include <CBSDL/Funcs.h>
#include <CBCore/StringConvert.h>

#include <SDL_mouse.h>

namespace cb {
  namespace sdl {
    cb::string getNameFromScanCode(ScanCode const code) {
      auto szName = SDL_GetScancodeName(static_cast<SDL_Scancode>(code));
      CB_SDL_CHECKERRORS();
      return cb::fromUtf8(cb::utf8string(szName));
    }

    ScanCode getScanCodeFromName(cb::string const & name) {
      auto code = SDL_GetScancodeFromName(cb::toUtf8(name).c_str());
      CB_SDL_CHECKERRORS();
      return static_cast<cb::sdl::ScanCode>(code);
    }

    bool hasClipboardText() {
      return SDL_HasClipboardText() == SDL_TRUE;
    }

    void setClipboardText(const cb::string & text) {
      auto utf8text = cb::toUtf8(text);
      SDL_SetClipboardText(utf8text.c_str());
      CB_SDL_CHECKERRORS();
    }

    cb::string getClipboardText() {
      auto utf8text = SDL_GetClipboardText();
      CB_SDL_CHECKERRORS();
      return cb::fromUtf8(utf8text);
    }

    void setModState(const KeyMods mods) {
      SDL_SetModState(static_cast<SDL_Keymod>(mods.get()));
      CB_SDL_CHECKERRORS();
    }

    KeyMods getModState() {
      auto mods = static_cast<KeyMod>(SDL_GetModState());
      CB_SDL_CHECKERRORS();
      return KeyMods(mods);
    }

    ButtonFlags getMouseModState(glm::ivec2 & outPos) {
      auto state = SDL_GetMouseState(&outPos.x, &outPos.y);
      CB_SDL_CHECKERRORS();
      return static_cast<ButtonFlag>(state);
    }

    ButtonFlags getGlobalMouseModSate(glm::ivec2 & outPod) {
      auto state = SDL_GetGlobalMouseState(&outPod.x, &outPod.y);
      CB_SDL_CHECKERRORS();
      return static_cast<ButtonFlag>(state);
    }
  }
}