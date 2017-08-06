#include "stdafx.h"
#include <CBSDL/GLContext.h>
#include <CBSDL/Window.h>

#include <exception>

namespace cb {
  namespace sdl {
    CGLContext::CGLContext(CWindow& window, GLAttributeMapT const & attributes) {
      for(auto& attrib : attributes) {
        SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attrib.first), attrib.second);
        CB_SDL_CHECKERRORS();
      }
      mContext = SDL_GL_CreateContext(window.Get());
      CB_SDL_CHECKERRORS();
    }

    CGLContext::~CGLContext() {
      if(mContext) {
        SDL_GL_DeleteContext(reinterpret_cast<SDL_GLContext>(mContext));
        mContext = nullptr;
      }
    }

    void CGLContext::MakeCurrent(CWindow & window) {
      SDL_GL_MakeCurrent(window.Get(), reinterpret_cast<SDL_GLContext>(mContext));
      CB_SDL_CHECKERRORS();
    }

    void CGLContext::SwapWindow(CWindow & window) {
      SDL_GL_SwapWindow(window.Get());
      CB_SDL_CHECKERRORS();
    }
  }
}