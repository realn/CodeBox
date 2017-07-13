#include "stdafx.h"
#include "../Events.h"
#include "../Consts.h"

namespace cb {
  namespace sdl {
    CEvent::CEvent()
      : mEvent({0}) {}

    CEvent::CEvent(CEvent const & other)
      : mEvent(other.mEvent) {}

    CEvent::CEvent(SDL_Event const & event) 
      : mEvent(event) {}

    CEvent::~CEvent() {}

    EventType CEvent::GetType() const {
      return static_cast<EventType>(mEvent.type);
    }

    bool CEvent::Poll(CEvent & outEvent) {
      return SDL_PollEvent(&outEvent.Get()) == SDL_TRUE;
    }

    CEvent CEvent::WaitFor() {
      SDL_Event event = {0};
      SDL_WaitEvent(&event);
      return CEvent(event);
    }

    CEvent CEvent::WaitFor(std::chrono::milliseconds const & timeout) {
      SDL_Event event = {0};
      SDL_WaitEventTimeout(&event, static_cast<int>(timeout.count()));
      return CEvent(event);
    }
  }
}