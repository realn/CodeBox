#include "stdafx.h"
#include <CBSDL/Events.h>
#include <CBSDL/Consts.h>
#include <CBCore/StringConvert.h>

#include <SDL_events.h>

inline SDL_Event& get(cb::sdl::Event& event) {
  return reinterpret_cast<SDL_Event&>(*event.get());
}

inline SDL_Event const& get(cb::sdl::Event const& event) {
  return reinterpret_cast<SDL_Event const&>(*event.get());
}

namespace cb {
  namespace sdl {
    EventType Event::getType() const {
      return static_cast<EventType>(::get(*this).type);
    }

    bool Event::poll(Event & outEvent) {
      return SDL_PollEvent(&::get(outEvent)) == SDL_TRUE;
    }

    Event Event::waitFor() {
      Event result;
      SDL_WaitEvent(&::get(result));
      CB_SDL_CHECKERRORS();
      return result;
    }

    Event Event::waitFor(std::chrono::milliseconds const & timeout) {
      Event result;
      SDL_WaitEventTimeout(&::get(result), static_cast<int>(timeout.count()));
      CB_SDL_CHECKERRORS();
      return result;
    }

    WindowEvent::WindowEvent(Event const & event) 
      : WindowEvent()
    {
      mType = static_cast<WindowEventType>(::get(event).window.event);
      mWindowId = static_cast<WindowID>(::get(event).window.windowID);
      mData1 = static_cast<s32>(::get(event).window.data1);
      mData2 = static_cast<s32>(::get(event).window.data2);
    }

    KeyboardEvent::KeyboardEvent(Event const & other) 
      : KeyboardEvent()
    {
      mType = static_cast<KeyState>(::get(other).key.state);
      mWindowId = static_cast<WindowID>(::get(other).key.windowID);
      mScanCode = static_cast<ScanCode>(::get(other).key.keysym.scancode);
      mKeyMod = static_cast<KeyMod>(::get(other).key.keysym.mod);
      mKeySymbol = static_cast<string::value_type>(::get(other).key.keysym.sym);
      mKeyRepeat = static_cast<u32>(::get(other).key.repeat);
    }

    MouseButtonEvent::MouseButtonEvent(Event const & other) 
      : MouseButtonEvent()
    {
      mType = static_cast<KeyState>(::get(other).button.state);
      mButton = static_cast<button>(::get(other).button.button);
      mClicks = static_cast<u32>(::get(other).button.clicks);
      mMouseId = static_cast<MouseID>(::get(other).button.which);
      mWindowId = static_cast<WindowID>(::get(other).button.windowID);
    }

    MouseMotionEvent::MouseMotionEvent(Event const & other) 
      : MouseMotionEvent()
    {
      mPosition = {::get(other).motion.x, ::get(other).motion.y};
      mRelative = {::get(other).motion.xrel, ::get(other).motion.yrel};
      mMouseId = static_cast<MouseID>(::get(other).motion.which);
      mWindowId = static_cast<WindowID>(::get(other).motion.windowID);
    }

    MouseWheelEvent::MouseWheelEvent(Event const & other) 
      : MouseWheelEvent()
    {
      mScroll = {::get(other).wheel.x, ::get(other).wheel.y};
      mFlipped = ::get(other).wheel.direction == SDL_MOUSEWHEEL_FLIPPED;
      mMouseId = static_cast<MouseID>(::get(other).wheel.which);
      mWindowId = static_cast<WindowID>(::get(other).wheel.windowID);
    }

    TextInputEvent::TextInputEvent(Event const & other) 
      : TextInputEvent()
    {
      mWindowId = static_cast<WindowID>(::get(other).text.windowID);
      mText = cb::fromUtf8(::get(other).text.text);
    }

    TextEditingEvent::TextEditingEvent(Event const & other) 
      : TextEditingEvent()
    {
      mWindowId = static_cast<WindowID>(::get(other).edit.windowID);
      mEditPos = ::get(other).edit.start;
      mEditLen = ::get(other).edit.length;
      mText = fromUtf8(::get(other).edit.text);
    }
  }
}