#include "stdafx.h"
#include <CBSDL/Events.h>
#include <CBSDL/Consts.h>

namespace cb {
  namespace sdl {
    EventType CEvent::GetType() const {
      return static_cast<EventType>(mEvent.type);
    }

    bool CEvent::Poll(CEvent & outEvent) {
      return SDL_PollEvent(&outEvent.Get()) == SDL_TRUE;
    }

    CEvent CEvent::WaitFor() {
      SDL_Event event = {0};
      SDL_WaitEvent(&event);
      CB_SDL_CHECKERRORS();
      return CEvent(event);
    }

    CEvent CEvent::WaitFor(std::chrono::milliseconds const & timeout) {
      SDL_Event event = {0};
      SDL_WaitEventTimeout(&event, static_cast<int>(timeout.count()));
      CB_SDL_CHECKERRORS();
      return CEvent(event);
    }

    cb::string CTextInputEvent::GetText() const {
      return cb::fromUtf8(cb::utf8string(mEvent.text));
    }

    cb::string CTextEditingEvent::GetText() const {
      return cb::fromUtf8(cb::utf8string(mEvent.text));
    }
  }
}