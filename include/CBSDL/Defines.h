#pragma once

#include <glm/fwd.hpp>

#include <CBCore/Defines.h>

namespace cb {
  namespace sdl {
    using RefreshRate = u32;
    using WindowID = u32;
    using DisplayID = u32;
    using MouseID = u32;

    template<typename _Type>
    constexpr int shiftBit(_Type value, int shiftAdj = -1) {
      return 1 << (static_cast<int>(value) + shiftAdj);
    }
  }
}
