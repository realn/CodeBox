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

    ButtonFlags getMouseModState(glm::ivec2& outPos = glm::ivec2());
    ButtonFlags getGlobalMouseModSate(glm::ivec2& outPod = glm::ivec2());
  }
}