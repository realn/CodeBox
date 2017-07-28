#include "stdafx.h"
#include <CBSDL/System.h>

#include <SDL_image.h>

namespace cb {
  namespace sdl {
    CSystem::CSystem(System const system) : mFlags(system) {
      SDL_InitSubSystem(static_cast<Uint32>(mFlags));
      CB_SDL_CHECKERRORS();
      IMG_Init(0);
      CB_IMG_CHECKERRORS();
    }

    CSystem::~CSystem() {
      SDL_QuitSubSystem(static_cast<Uint32>(mFlags));
      IMG_Quit();
    }
  }
}