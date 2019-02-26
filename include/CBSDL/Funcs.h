#pragma once

#include "Defines.h"

namespace cb {
  namespace sdl {
    enum class ScanCode;

    extern cb::string GetNameFromScanCode(ScanCode const code);
    extern ScanCode GetScanCodeFromName(cb::string const& name);
  }
}