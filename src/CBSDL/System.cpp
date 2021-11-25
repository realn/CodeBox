#include "stdafx.h"
#include <CBSDL/System.h>

#include <SDL_image.h>
#include <SDL_ttf.h>

namespace cb {
  namespace sdl {
    System::System(SystemFlags const system) : mFlags(system) {
      setMainReady();

      if (SDL_InitSubSystem(static_cast<Uint32>(mFlags)) != 0) {
        CB_SDL_CHECKERRORS();
        throw std::exception("Failed to initialize sdl subsystem.");
      }
      if (!IMG_Init(0) == 0) {
        CB_IMG_CHECKERRORS();
        throw std::exception("Failed to initialize sdl img subsystem.");
      }
      if (TTF_Init() != 0) {
        CB_TTF_CHECKERRORS();
        throw std::exception("Failed to initialize sdl ttf subsystem.");
      }
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