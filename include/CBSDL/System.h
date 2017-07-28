#pragma once

#include "Defines.h"
#include <SDL.h>

namespace cb {
  namespace sdl {
    ENUM_FLAG(System) {
      Audio = SDL_INIT_AUDIO,
      Events = SDL_INIT_EVENTS,
      GameController = SDL_INIT_GAMECONTROLLER,
      Haptic = SDL_INIT_HAPTIC,
      Joystick = SDL_INIT_JOYSTICK,
      Timer = SDL_INIT_TIMER,
      Video = SDL_INIT_VIDEO
    };

    class CSystem {
    private:
       System mFlags;
    public:
      CSystem(System const system);
      ~CSystem();
    };
  }
}
