#include "stdafx.h"
#include <CBGL/Rendering.h>

namespace cb {
  namespace gl {
    void clearColor(glm::vec4 const & color) {
      glClearColor(color.r, color.g, color.b, color.a);
      CB_GL_CHECKERRORS();
    }

    void clearDepth(float const & value) {
      glClearDepth(value);
      CB_GL_CHECKERRORS();
    }

    void clearStencil(int const & value) {
      glClearStencil(value);
      CB_GL_CHECKERRORS();
    }

    void clear(ClearBuffer const & flags) {
      glClear(static_cast<GLbitfield>(flags));
      CB_GL_CHECKERRORS();
    }

    void finish() {
      glFinish();
      CB_GL_CHECKERRORS();
    }

    void flush() {
      glFlush();
      CB_GL_CHECKERRORS();
    }


  }
}

