#include "stdafx.h"
#include <CBSDL/Events.h>
#include <CBSDL/Consts.h>
#include <CBCore/StringConvert.h>

#include <SDL_events.h>

inline SDL_Event& Get(cb::sdl::CEvent& event) {
  return reinterpret_cast<SDL_Event&>(*event.Get());
}

inline SDL_Event const& Get(cb::sdl::CEvent const& event) {
  return reinterpret_cast<SDL_Event const&>(*event.Get());
}

namespace cb {
  namespace sdl {
    EventType CEvent::GetType() const {
      return static_cast<EventType>(::Get(*this).type);
    }

    bool CEvent::Poll(CEvent & outEvent) {
      return SDL_PollEvent(&::Get(outEvent)) == SDL_TRUE;
    }

    CEvent CEvent::WaitFor() {
      CEvent result;
      SDL_WaitEvent(&::Get(result));
      CB_SDL_CHECKERRORS();
      return result;
    }

    CEvent CEvent::WaitFor(std::chrono::milliseconds const & timeout) {
      CEvent result;
      SDL_WaitEventTimeout(&::Get(result), static_cast<int>(timeout.count()));
      CB_SDL_CHECKERRORS();
      return result;
    }

    CWindowEvent::CWindowEvent(CEvent const & event) 
      : CWindowEvent()
    {
      mType = static_cast<WindowEventType>(::Get(event).window.event);
      mWindowId = static_cast<WindowID>(::Get(event).window.windowID);
      mData1 = static_cast<s32>(::Get(event).window.data1);
      mData2 = static_cast<s32>(::Get(event).window.data2);
    }

    CKeyboardEvent::CKeyboardEvent(CEvent const & other) 
      : CKeyboardEvent()
    {
      mType = static_cast<KeyState>(::Get(other).key.state);
      mWindowId = static_cast<WindowID>(::Get(other).key.windowID);
      mScanCode = static_cast<ScanCode>(::Get(other).key.keysym.scancode);
      mKeyMod = static_cast<KeyMod>(::Get(other).key.keysym.mod);
      mKeySymbol = static_cast<string::value_type>(::Get(other).key.keysym.sym);
      mKeyRepeat = static_cast<u32>(::Get(other).key.repeat);
    }

    CMouseButtonEvent::CMouseButtonEvent(CEvent const & other) 
      : CMouseButtonEvent()
    {
      mType = static_cast<KeyState>(::Get(other).button.state);
      mButton = static_cast<Button>(::Get(other).button.button);
      mClicks = static_cast<u32>(::Get(other).button.clicks);
      mMouseId = static_cast<MouseID>(::Get(other).button.which);
      mWindowId = static_cast<WindowID>(::Get(other).button.windowID);
    }

    CMouseMotionEvent::CMouseMotionEvent(CEvent const & other) 
      : CMouseMotionEvent()
    {
      mPosition = {::Get(other).motion.x, ::Get(other).motion.y};
      mRelative = {::Get(other).motion.xrel, ::Get(other).motion.yrel};
      mMouseId = static_cast<MouseID>(::Get(other).motion.which);
      mWindowId = static_cast<WindowID>(::Get(other).motion.windowID);
    }

    CMouseWheelEvent::CMouseWheelEvent(CEvent const & other) 
      : CMouseWheelEvent()
    {
      mScroll = {::Get(other).wheel.x, ::Get(other).wheel.y};
      mFlipped = ::Get(other).wheel.direction == SDL_MOUSEWHEEL_FLIPPED;
      mMouseId = static_cast<MouseID>(::Get(other).wheel.which);
      mWindowId = static_cast<WindowID>(::Get(other).wheel.windowID);
    }

    CTextInputEvent::CTextInputEvent(CEvent const & other) 
      : CTextInputEvent()
    {
      mWindowId = static_cast<WindowID>(::Get(other).text.windowID);
      mText = cb::fromUtf8(::Get(other).text.text);
    }

    CTextEditingEvent::CTextEditingEvent(CEvent const & other) 
      : CTextEditingEvent()
    {
      mWindowId = static_cast<WindowID>(::Get(other).edit.windowID);
      mEditPos = ::Get(other).edit.start;
      mEditLen = ::Get(other).edit.length;
      mText = fromUtf8(::Get(other).edit.text);
    }
  }
}