#include "stdafx.h"
#include <CBGL/Rendering.h>

namespace cb {
  namespace gl {
    void clearColor(glm::vec4 const& color) {
      glClearColor(color.r, color.g, color.b, color.a);
      CB_GL_CHECKERRORS();
    }

    void clearDepth(float const& value) {
      glClearDepth(value);
      CB_GL_CHECKERRORS();
    }

    void clearStencil(int const& value) {
      glClearStencil(value);
      CB_GL_CHECKERRORS();
    }

    void clear(ClearBuffer const& flags) {
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

    void setViewport(const Viewport& viewport) {
      glViewport(viewport.Pos.x, viewport.Pos.y, viewport.Size.x, viewport.Size.y);
      CB_GL_CHECKERRORS();
    }

    Viewport getViewport() {
      GLint viewport[4];
      glGetIntegerv(GL_VIEWPORT, viewport);
      CB_GL_CHECKERRORS();
      return Viewport{
        {viewport[0], viewport[1]},
        {static_cast<cb::u32>(viewport[2]), static_cast<cb::u32>(viewport[3]) }
      };
    }

    void setScissorRect(const Viewport& rect) {
      glScissor(rect.Pos.x, rect.Pos.y, rect.Size.x, rect.Size.y);
    }

    Viewport getScissorRect() {
      GLint viewport[4];
      glGetIntegerv(GL_SCISSOR_BOX, viewport);
      CB_GL_CHECKERRORS();
      return Viewport{
        {viewport[0], viewport[1]},
        {static_cast<cb::u32>(viewport[2]), static_cast<cb::u32>(viewport[3]) }
      };
    }

    void setScissorTest(bool enabled) {
      if (enabled) {
        glEnable(GL_SCISSOR_TEST);
      }
      else {
        glDisable(GL_SCISSOR_TEST);
      }
      CB_GL_CHECKERRORS();
    }

    bool isScissorTestEnabled() {
      GLint result;
      glGetIntegerv(GL_SCISSOR_TEST, &result);
      CB_GL_CHECKERRORS();
      return result == GL_TRUE;
    }


  }
}

