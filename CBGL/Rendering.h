#pragma once

#include "Defines.h"

namespace cb {
  namespace gl {
    ENUM_FLAG(ClearBuffer) {
      COLOR = 0x00004000,
        DEPTH = 0x00000100,
        STENCIL = 0x00000400,
    };

    extern void clearColor(glm::vec4 const& value);
    extern void clearDepth(float const& value);
    extern void clearStencil(int const& value);
    extern void clear(ClearBuffer const& flags);
    extern void finish();
    extern void flush();
  }
}