#include "stdafx.h"
#include "../Rendering.h"

namespace cb {
  namespace gl {
    void clearColor(glm::vec4 const & color) {
      glClearColor(color.r, color.g, color.b, color.a);
    }

    void clearDepth(float const & value) {
      glClearDepth(value);
    }

    void clearStencil(int const & value) {
      glClearStencil(value);
    }

    void clear(ClearBuffer const & flags) {
      glClear(static_cast<GLbitfield>(flags));
    }

    void finish() {}

    void flush() {}


  }
}

