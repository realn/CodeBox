#pragma once

#include <chrono>

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    class Event;

    class WindowEvent {
    private:
      WindowEventType mType;
      WindowID mWindowId;
      s32 mData1;
      s32 mData2;

    public:
      WindowEvent() : mType(WindowEventType::NONE), mWindowId(0), mData1(0), mData2(0) {}
      explicit WindowEvent(Event const& event);

      WindowEventType getType() const { return mType; }
      WindowID getWindowId() const { return mWindowId; }
      s32 getData1() const { return mData1; }
      s32 getData2() const { return mData2; }
    };

    class KeyboardEvent {
    private:
      KeyState mType;
      WindowID mWindowId;
      ScanCode mScanCode;
      KeyMod mKeyMod;
      cb::string::value_type mKeySymbol;
      u32 mKeyRepeat;

    public:
      KeyboardEvent() : mType(KeyState::PRESSED), mWindowId(0), mScanCode(ScanCode::UNKNOWN), mKeyMod(KeyMod::NONE), mKeySymbol(0), mKeyRepeat(0) {}
      explicit KeyboardEvent(Event const& other);

      KeyState getType() const { return mType; }
      WindowID getWindowId() const { return mWindowId; }
      ScanCode getScanCode() const { return mScanCode; }
      KeyMod getKeyMod() const { return mKeyMod; }
      cb::string::value_type getKeySymbol() const { return mKeySymbol; }
      u32 getKeyRepeat() const { return mKeyRepeat; }
    };

    class MouseButtonEvent {
    private:
      KeyState mType;
      button mButton;
      u32 mClicks;
      MouseID mMouseId;
      WindowID mWindowId;

    public:
      MouseButtonEvent() : mType(KeyState::PRESSED), mButton(button::LEFT), mClicks(0), mMouseId(0), mWindowId(0) {}
      explicit MouseButtonEvent(Event const& other);

      KeyState getType() const { return mType; }
      button getButton() const { return mButton; }
      u32 getClicks() const { return mClicks; }
      MouseID getMouseId() const { return mMouseId; }
      WindowID getWindowId() const { return mWindowId; }
    };

    class MouseMotionEvent {
    private:
      glm::ivec2 mPosition;
      glm::ivec2 mRelative;
      MouseID mMouseId;
      WindowID mWindowId;

    public:
      MouseMotionEvent() : mMouseId(0), mWindowId(0) {}
      explicit MouseMotionEvent(Event const& other);

      glm::ivec2 getPosition() const { return mPosition; }
      glm::ivec2 getRelative() const { return mRelative; }
      MouseID getMouseId() const { return mMouseId; }
      WindowID getWindowId() const { return mWindowId; }
    };

    class MouseWheelEvent {
    private:
      glm::ivec2 mScroll;
      bool mFlipped;
      MouseID mMouseId;
      WindowID mWindowId;

    public:
      MouseWheelEvent() : mFlipped(false), mMouseId(0), mWindowId() {}
      explicit MouseWheelEvent(Event const& other);

      glm::ivec2 getScroll() const { return mScroll; }
      bool isFlipped() const { return mFlipped; }
      MouseID getMouseId() const { return mMouseId; }
      WindowID getWindowId() const { return mWindowId; }
    };

    class TextInputEvent {
    private:
      WindowID mWindowId;
      cb::string mText;

    public:
      TextInputEvent() : mWindowId(0) {}
      explicit TextInputEvent(Event const& other);
      
      WindowID getWindowId() const { return mWindowId; }
      cb::string getText() const { return mText; }
    };

    class TextEditingEvent {
    private:
      WindowID mWindowId;
      u32 mEditPos;
      u32 mEditLen;
      cb::string mText;

    public:
      TextEditingEvent() : mWindowId(0), mEditPos(0), mEditLen(0) {}
      explicit TextEditingEvent(Event const& other);

      WindowID getWindowId() const { return mWindowId; }
      u32 getEditPos() const { return mEditPos; }
      u32 getEditLen() const { return mEditLen; }
      cb::string getText() const { return mText; }
    };

    class Event {
    private:
      static constexpr size_t DATA_SIZE = 56; // SDL_Event universal size
      byte mData[DATA_SIZE] = {0};

    public:
      EventType getType() const;

      byte* get() { return mData; }
      byte const* get() const { return mData; }

      WindowEvent window() const { return WindowEvent(*this); }
      KeyboardEvent key() const { return KeyboardEvent(*this); }
      MouseButtonEvent button() const { return MouseButtonEvent(*this); }
      MouseMotionEvent motion() const { return MouseMotionEvent(*this); }
      MouseWheelEvent wheel() const { return MouseWheelEvent(*this); }
      TextEditingEvent edit() const { return TextEditingEvent(*this); }
      TextInputEvent text() const { return TextInputEvent(*this); }

      // Returns true if there is a pending event or false if there are none available.
      static bool poll(Event& outEvent);
      // Waits for any event
      static Event waitFor();
      // Waits for any event for 'timeout' time
      static Event waitFor(std::chrono::milliseconds const& timeout);
    };
  }
}