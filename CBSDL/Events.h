#pragma once

#include <chrono>
#include <SDL_events.h>

#include "Defines.h"

namespace cb {
  namespace sdl {
    enum class EventType;

    class CEvent {
    private:
      SDL_Event mEvent;

    public:
      CEvent();
      CEvent(CEvent const & other);
      explicit CEvent(SDL_Event const& event);
      ~CEvent();

      EventType GetType() const;

      SDL_Event& Get() { return mEvent; }
      const SDL_Event& Get() const { return mEvent; }

      static bool Poll(CEvent& outEvent);
      static CEvent WaitFor();
      static CEvent WaitFor(std::chrono::milliseconds const& timeout);
    };
  }
}