#include "stdafx.h"
#include <CBSDL/System.h>

#include <SDL_image.h>
#include <SDL_ttf.h>

namespace cb {
  namespace sdl {
    System::System(SystemFlags const system) : mFlags(system) {
      setMainReady();

      SDL_InitSubSystem(static_cast<Uint32>(mFlags));
      CB_SDL_CHECKERRORS();
      IMG_Init(0);
      CB_IMG_CHECKERRORS();
      TTF_Init();
      CB_TTF_CHECKERRORS();
    }

    System::~System() {
      TTF_Quit();
      IMG_Quit();
      SDL_QuitSubSystem(static_cast<Uint32>(mFlags));
    }

    void System::setMainReady()
    {
      SDL_SetMainReady();
    }
  }
}