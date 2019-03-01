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

    extern ButtonFlags GetMouseModState(glm::ivec2& outPos = glm::ivec2());
    extern ButtonFlags GetGlobalMouseModSate(glm::ivec2& outPod = glm::ivec2());
  }
}