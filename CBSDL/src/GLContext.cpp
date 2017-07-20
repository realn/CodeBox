#include "stdafx.h"
#include "../GLContext.h"
#include "../Window.h"

#include <exception>

namespace cb {
  namespace sdl {
    CGLContext::CGLContext(CWindow& window, GLAttributeMapT const & attributes) {
      for(auto& attrib : attributes) {
        if(SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attrib.first), 
                               attrib.second) != 0) {
          throw std::exception(SDL_GetError());
        }
      }

      mContext = SDL_GL_CreateContext(window.Get());
      if(mContext == nullptr) {
        throw std::exception(SDL_GetError());
      }
    }

    CGLContext::~CGLContext() {
      if(mContext) {
        SDL_GL_DeleteContext(mContext);
        mContext = nullptr;
      }
    }

    void CGLContext::MakeCurrent(CWindow & window) {
      if(SDL_GL_MakeCurrent(window.Get(), mContext) != 0) {
        throw std::exception(SDL_GetError());
      }
    }

    void CGLContext::SwapWindow(CWindow & window) {
      SDL_GL_SwapWindow(window.Get());
    }
  }
}