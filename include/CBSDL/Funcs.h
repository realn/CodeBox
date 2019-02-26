#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    enum class ScanCode;
    

    extern cb::string GetNameFromScanCode(ScanCode const code);
    extern ScanCode GetScanCodeFromName(cb::string const& name);

    extern bool HasClipboardText();
    extern void SetClipboardText(const cb::string& text);
    extern cb::string GetClipboardText();

    extern void SetModState(const KeyMods mods);
    extern KeyMods GetModState();
  }
}