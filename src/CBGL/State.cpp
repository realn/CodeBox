#include "stdafx.h"
#include <CBGL/State.h>

namespace cb {
  namespace gl {
    namespace {
      constexpr GLboolean toGLBool(bool value) {
        return value ? GL_TRUE : GL_FALSE;
      }
    }
    void setStateEnabled(State const state, bool enabled) {
      if(enabled) {
        glEnable(static_cast<GLenum>(state));
        CB_GL_CHECKERRORS();
      }
      else {
        glDisable(static_cast<GLenum>(state));
        CB_GL_CHECKERRORS();
      }
    }

    void setState(BlendState const & state) {
      glBlendFunc(
        static_cast<GLenum>(state.SrcFactor),
        static_cast<GLenum>(state.DstFactor)
      );
      CB_GL_CHECKERRORS();
      glBlendEquationSeparate(
        static_cast<GLenum>(state.ColorFunc),
        static_cast<GLenum>(state.AlphaFunc)
      );
      CB_GL_CHECKERRORS();
      glBlendColor(state.ConstColor.r,
                   state.ConstColor.g,
                   state.ConstColor.b,
                   state.ConstColor.a);
      CB_GL_CHECKERRORS();
      glColorMask(toGLBool(state.ColorMask.r),
                  toGLBool(state.ColorMask.g),
                  toGLBool(state.ColorMask.b),
                  toGLBool(state.ColorMask.a));
      CB_GL_CHECKERRORS();
    }

    void setState(CullState const & state) {
      glCullFace(static_cast<GLenum>(state.Face));
      CB_GL_CHECKERRORS();
      glFrontFace(static_cast<GLenum>(state.Front));
      CB_GL_CHECKERRORS();
    }

    void setState(DepthState const & state) {
      glDepthFunc(static_cast<GLenum>(state.Func));
      CB_GL_CHECKERRORS();
      glDepthMask(toGLBool(state.Mask));
      CB_GL_CHECKERRORS();
      glDepthRange(state.RangeNear, state.RangeFar);
      CB_GL_CHECKERRORS();
    }

    bool isStateEnabled(State const state) {
      auto result = glIsEnabled(static_cast<GLenum>(state));
      CB_GL_CHECKERRORS();
      return result == GL_TRUE;
    }

    BlendState getBlendState() {
      GLint src, dst, rgb, alp;
      glm::vec4 color;
      glm::tvec4<GLboolean> mask;

      glGetIntegerv(GL_BLEND_SRC, &src);
      CB_GL_CHECKERRORS();
      glGetIntegerv(GL_BLEND_DST, &dst);
      CB_GL_CHECKERRORS();
      glGetIntegerv(GL_BLEND_EQUATION_RGB, &rgb);
      CB_GL_CHECKERRORS();
      glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &alp);
      CB_GL_CHECKERRORS();
      glGetFloatv(GL_BLEND_COLOR, glm::value_ptr(color));
      CB_GL_CHECKERRORS();
      glGetBooleanv(GL_COLOR_WRITEMASK, glm::value_ptr(mask));
      CB_GL_CHECKERRORS();

      return BlendState{
        static_cast<BlendFactor>(src),
        static_cast<BlendFactor>(dst),
        static_cast<BlendFunc>(rgb),
        static_cast<BlendFunc>(alp),
        color, 
        glm::bvec4(
          mask.r == GL_TRUE, 
          mask.g == GL_TRUE, 
          mask.b == GL_TRUE,
          mask.a == GL_TRUE)
      };
    }

    CullState getCullState() {
      GLint face, front;

      glGetIntegerv(GL_CULL_FACE_MODE, &face);
      CB_GL_CHECKERRORS();
      glGetIntegerv(GL_FRONT_FACE, &front);
      CB_GL_CHECKERRORS();

      return CullState{
        static_cast<CullFace>(face),
        static_cast<FrontFace>(front)
      };
    }

    DepthState getDepthState() {
      GLint func;
      GLboolean mask;
      glm::vec2 range;

      glGetIntegerv(GL_DEPTH_FUNC, &func);
      CB_GL_CHECKERRORS();
      glGetBooleanv(GL_DEPTH_WRITEMASK, &mask);
      CB_GL_CHECKERRORS();
      glGetFloatv(GL_DEPTH_RANGE, glm::value_ptr(range));
      CB_GL_CHECKERRORS();

      return DepthState{
        static_cast<DepthFunc>(func),
        mask == GL_TRUE,
        range.x, range.y
      };
    }
  }
}