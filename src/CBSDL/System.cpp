#include "stdafx.h"
#include <CBSDL/System.h>

#include <SDL_image.h>
#include <SDL_ttf.h>

namespace cb {
  namespace sdl {
    CSystem::CSystem(System const system) : mFlags(system) {
      SDL_InitSubSystem(static_cast<Uint32>(mFlags));
      CB_SDL_CHECKERRORS();
      IMG_Init(0);
      CB_IMG_CHECKERRORS();
      TTF_Init();
      CB_TTF_CHECKERRORS();
    }

    CSystem::~CSystem() {
      TTF_Quit();
      IMG_Quit();
      SDL_QuitSubSystem(static_cast<Uint32>(mFlags));
    }
  }
}