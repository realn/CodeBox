#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    enum class ScanCode;
    
    cb::string getNameFromScanCode(ScanCode const code);
    ScanCode getScanCodeFromName(cb::string const& name);

    bool hasClipboardText();
    void setClipboardText(const cb::string& text);
    cb::string getClipboardText();

    void setModState(const KeyMods mods);
    KeyMods getModState();

    ButtonFlags getMouseState(glm::ivec2& outRelFocusPos = glm::ivec2());
    ButtonFlags getGlobalMouseState(glm::ivec2& outGlobalPos = glm::ivec2());
    ButtonFlags getRelativeMouseState(glm::ivec2& outRelativePos = glm::ivec2());
  }
}