#include "stdafx.h"
#include "../System.h"

namespace cb {
  namespace sdl {
    CSystem::CSystem(System const system) : mFlags(system) {
      if(SDL_InitSubSystem(static_cast<Uint32>(mFlags)) != 0) {
        throw std::exception(SDL_GetError());
      }
    }
    CSystem::~CSystem() {
      SDL_QuitSubSystem(static_cast<Uint32>(mFlags));
    }
  }
}