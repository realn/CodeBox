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
    GLContext::GLContext(Window& window, GLAttributeMapT const & attributes) {
      for(auto& attrib : attributes) {
        SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attrib.first), attrib.second);
        CB_SDL_CHECKERRORS();
      }
      mContext = SDL_GL_CreateContext(::get(window));
      CB_SDL_CHECKERRORS();
    }

    GLContext::~GLContext() {
      if(mContext) {
        SDL_GL_DeleteContext(reinterpret_cast<SDL_GLContext>(mContext));
        mContext = nullptr;
      }
    }

    void GLContext::makeCurrent(Window & window) {
      SDL_GL_MakeCurrent(::get(window), reinterpret_cast<SDL_GLContext>(mContext));
      CB_SDL_CHECKERRORS();
    }

    void GLContext::swapWindow(Window & window) {
      SDL_GL_SwapWindow(::get(window));
      CB_SDL_CHECKERRORS();
    }
  }
}