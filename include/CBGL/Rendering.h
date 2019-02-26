#pragma once

#include <glm/vec2.hpp>

#include <CBCore/Flags.h>

#include "Defines.h"

namespace cb {
  namespace gl {
    ENUM_FLAG(ClearBuffer) {
      COLOR = 0x00004000,
        DEPTH = 0x00000100,
        STENCIL = 0x00000400,
    };

    struct CViewport {
      glm::ivec2 Pos;
      glm::uvec2 Size;
    };

    extern void clearColor(glm::vec4 const& value);
    extern void clearDepth(float const& value);
    extern void clearStencil(int const& value);
    extern void clear(ClearBuffer const& flags);
    extern void finish();
    extern void flush();

    extern void setViewport(const CViewport& viewport);
    extern CViewport getViewport();

    extern void setScissorRect(const CViewport& rect);
    extern CViewport getScissorRect();
    extern void setScissorTest(bool enabled);
    extern bool isScissorTestEnabled();
  }
}