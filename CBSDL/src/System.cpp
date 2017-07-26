#include "stdafx.h"
#include "../System.h"

namespace cb {
  namespace sdl {
    CSystem::CSystem(System const system) : mFlags(system) {
      SDL_InitSubSystem(static_cast<Uint32>(mFlags));
      CB_SDL_CHECKERRORS();
    }
    CSystem::~CSystem() {
      SDL_QuitSubSystem(static_cast<Uint32>(mFlags));
    }
  }
}