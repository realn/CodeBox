#pragma once

#include <CBCore/Flags.h>

#include "Defines.h"

namespace cb {
  namespace sdl {
    ENUM_FLAG(SystemFlag) {
        TIMER = 0x00000001u,
        AUDIO = 0x00000010u,
        VIDEO = 0x00000020u,  /**< SDL_INIT_VIDEO implies SDL_INIT_EVENTS */
        JOYSTICK = 0x00000200u,  /**< SDL_INIT_JOYSTICK implies SDL_INIT_EVENTS */
        HAPTIC = 0x00001000u,
        GAMECONTROLLER = 0x00002000u,  /**< SDL_INIT_GAMECONTROLLER implies SDL_INIT_JOYSTICK */
        EVENTS = 0x00004000u,
        NOPARACHUTE = 0x00100000u,  /**< compatibility; this flag is ignored. */
        EVERYTHING = (TIMER | AUDIO | VIDEO | EVENTS | \
                      JOYSTICK | HAPTIC | GAMECONTROLLER )
    };

    class System {
    private:
      SystemFlags mFlags;
    public:
      System(SystemFlags const system);
      ~System();

      void setMainReady();
    };
  }
}
