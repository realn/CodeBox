#include "stdafx.h"
#include <CBSDL/GLContext.h>
#include <CBSDL/Window.h>

#include <exception>

inline SDL_Window* get(cb::sdl::Window& obj) {
  return reinterpret_cast<SDL_Window*>(obj.get());
}

inline SDL_Window* get(cb::sdl::Window const& obj) {
  return reinterpret_cast<SDL_Window*>(obj.get());
}

namespace cb {
  namespace sdl {
    GLContext::GLContext(Window& window) {
      mContext = SDL_GL_CreateContext(::get(window));
      if (mContext == nullptr) {
        CB_SDL_CHECKERRORS();
      }
    }

    GLContext::~GLContext() {
      if (mContext) {
        SDL_GL_DeleteContext(reinterpret_cast<SDL_GLContext>(mContext));
        mContext = nullptr;
      }
    }

    void GLContext::makeCurrent(Window& window) {
      if (SDL_GL_MakeCurrent(::get(window), reinterpret_cast<SDL_GLContext>(mContext)) != 0) {
        CB_SDL_CHECKERRORS();
      }
    }

    void GLContext::swapWindow(Window& window) {
      SDL_GL_SwapWindow(::get(window));
      //CB_SDL_CHECKERRORS();
    }

    void setContextCreationAttributes(GLAttributeMapT const& attributes) {
      for (auto& attrib : attributes) {
        if (SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attrib.first), attrib.second) != 0) {
          CB_SDL_CHECKERRORS();
        }
      }
    }
  }
}