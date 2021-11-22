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

    void clearColor(glm::vec4 const& value);
    void clearDepth(float const& value);
    void clearStencil(int const& value);
    void clear(ClearBuffer const& flags);
    void finish();
    void flush();

    void setViewport(const CViewport& viewport);
    CViewport getViewport();

    void setScissorRect(const CViewport& rect);
    CViewport getScissorRect();
    void setScissorTest(bool enabled);
    bool isScissorTestEnabled();
  }
}