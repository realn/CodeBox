#pragma once

#include <chrono>
#include <SDL_events.h>

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    class CEvent {
    private:
      SDL_Event mEvent = {0};

    public:
      CEvent() = default;
      explicit CEvent(SDL_Event const& event) : mEvent(event) {}

      EventType GetType() const;

      SDL_Event& Get() { return mEvent; }
      const SDL_Event& Get() const { return mEvent; }

      static bool Poll(CEvent& outEvent);
      static CEvent WaitFor();
      static CEvent WaitFor(std::chrono::milliseconds const& timeout);
    };

    class CWindowEvent {
    private:
      SDL_WindowEvent mEvent = {0};

    public:
      CWindowEvent() = default;
      explicit CWindowEvent(CEvent const& event) : mEvent(event.Get().window) {}

      WindowEventType GetType() const { return static_cast<WindowEventType>(mEvent.event); }
      WindowID GetWindowId() const { return mEvent.windowID; }
      Sint32 GetData1() const { return mEvent.data1; }
      Sint32 GetData2() const { return mEvent.data2; }
    };

    class CKeyboardEvent {
    private:
      SDL_KeyboardEvent mEvent = {0};

    public:
      CKeyboardEvent() = default;
      explicit CKeyboardEvent(CEvent const& other) : mEvent(other.Get().key) {}

      KeyState GetType() const { return static_cast<KeyState>(mEvent.state); }
      WindowID GetWindowId() const { return static_cast<WindowID>(mEvent.windowID); }
      ScanCode GetScanCode() const { return static_cast<ScanCode>(mEvent.keysym.scancode); }
      KeyMod GetKeyMod() const { return static_cast<KeyMod>(mEvent.keysym.mod); }
      cb::string::value_type GetKeySymbol() const {
        return static_cast<cb::string::value_type>(mEvent.keysym.sym);
      }
      Uint32 GetKeyRepeat() const { return static_cast<Uint32>(mEvent.repeat); }
    };

    class CMouseButtonEvent {
    private:
      SDL_MouseButtonEvent mEvent = {0};

    public:
      CMouseButtonEvent() = default;
      explicit  CMouseButtonEvent(CEvent const& other) : mEvent(other.Get().button) {}

      KeyState GetType() const { return static_cast<KeyState>(mEvent.state); }
      Button GetButton() const { return static_cast<Button>(mEvent.button); }
      Uint32 GetClicks() const { return static_cast<Uint32>(mEvent.clicks); }
      MouseID GetMouseId() const { return static_cast<MouseID>(mEvent.which); }
      WindowID GetWindowId() const { return static_cast<WindowID>(mEvent.windowID); }
    };

    class CMouseMotionEvent {
    private:
      SDL_MouseMotionEvent mEvent = {0};

    public:
      CMouseMotionEvent() = default;
      explicit CMouseMotionEvent(CEvent const& other) : mEvent(other.Get().motion) {}

      glm::ivec2 GetPosition() const { return glm::ivec2(mEvent.x, mEvent.y); }
      glm::ivec2 GetRelative() const { return glm::ivec2(mEvent.xrel, mEvent.yrel); }
      MouseID GetMouseId() const { return static_cast<MouseID>(mEvent.which); }
      WindowID GetWindowId() const { return static_cast<WindowID>(mEvent.windowID); }
    };

    class CMouseWheelEvent {
    private:
      SDL_MouseWheelEvent mEvent = {0};

    public:
      CMouseWheelEvent() = default;
      explicit CMouseWheelEvent(CEvent const& other) : mEvent(other.Get().wheel) {}

      glm::ivec2 GetScroll() const { return glm::ivec2(mEvent.x, mEvent.y); }
      bool IsFlipped() const { return mEvent.direction == SDL_MOUSEWHEEL_FLIPPED; }
      MouseID GetMouseId() const { return static_cast<MouseID>(mEvent.which); }
      WindowID GetWindowId() const { return static_cast<WindowID>(mEvent.windowID); }
    };

    class CTextInputEvent {
    private:
      SDL_TextInputEvent mEvent = {0};

    public:
      CTextInputEvent() = default;
      explicit CTextInputEvent(CEvent const& other) : mEvent(other.Get().text) {}
      
      WindowID GetWindowId() const { return static_cast<WindowID>(mEvent.windowID); }
      cb::string GetText() const;
    };

    class CTextEditingEvent {
    private:
      SDL_TextEditingEvent mEvent = {0};

    public:
      CTextEditingEvent() = default;
      explicit CTextEditingEvent(CEvent const& other) : mEvent(other.Get().edit) {}

      WindowID GetWindowId() const { return static_cast<WindowID>(mEvent.windowID); }
      Uint32 GetEditPos() const { return static_cast<Uint32>(mEvent.start); }
      Uint32 GetEditLen() const { return static_cast<Uint32>(mEvent.length); }
      cb::string GetText() const;
    };
  }
}