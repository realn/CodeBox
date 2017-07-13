#pragma once

#include "Defines.h"
#include <SDL.h>

namespace cb {
  namespace sdl {
    enum class SubSystemFlag {
      Audio = SDL_INIT_AUDIO,
      Events = SDL_INIT_EVENTS,
      GameController = SDL_INIT_GAMECONTROLLER,
      Haptic = SDL_INIT_HAPTIC,
      Joystick = SDL_INIT_JOYSTICK,
      Timer = SDL_INIT_TIMER,
      Video = SDL_INIT_VIDEO
    };

    class CLibrary {
    public:
      CLibrary(std::initializer_list<SubSystemFlag> const& subsystems = {});
      ~CLibrary();
    };

    class CSubSystem {
    private:
      Uint32 mFlags = 0;
    public:
      CSubSystem(SubSystemFlag const subsystem);
      CSubSystem(std::initializer_list<SubSystemFlag> const& subsystems);
      ~CSubSystem();
    };
  }
}
