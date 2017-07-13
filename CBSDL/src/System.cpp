#include "stdafx.h"
#include "../System.h"

namespace cb {
  namespace sdl {
    CLibrary::CLibrary(std::initializer_list<SubSystemFlag> const& subsystems) {
      auto flags = genflags(subsystems);
      if(SDL_Init(flags) != 0) {
        throw std::exception("Failed to initialize SDL.");
      }
    }
    CLibrary::~CLibrary() {
      SDL_Quit();
    }

    CSubSystem::CSubSystem(SubSystemFlag const subsystem) 
      : CSubSystem({subsystem})
    {}

    CSubSystem::CSubSystem(std::initializer_list<SubSystemFlag> const & subsystems) {
      mFlags = genflags(subsystems);
      if(SDL_InitSubSystem(mFlags) != 0) {
        throw std::exception("Failed to initialize SDL subsystem.");
      }
    }
    CSubSystem::~CSubSystem() {
      SDL_QuitSubSystem(mFlags);
    }
  }
}