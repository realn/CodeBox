#pragma once

#include <chrono>

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    class CEvent;

    class CWindowEvent {
    private:
      WindowEventType mType;
      WindowID mWindowId;
      s32 mData1;
      s32 mData2;

    public:
      CWindowEvent() : mType(WindowEventType::NONE), mWindowId(0), mData1(0), mData2(0) {}
      explicit CWindowEvent(CEvent const& event);

      WindowEventType GetType() const { return mType; }
      WindowID GetWindowId() const { return mWindowId; }
      s32 GetData1() const { return mData1; }
      s32 GetData2() const { return mData2; }
    };

    class CKeyboardEvent {
    private:
      KeyState mType;
      WindowID mWindowId;
      ScanCode mScanCode;
      KeyMod mKeyMod;
      cb::string::value_type mKeySymbol;
      u32 mKeyRepeat;

    public:
      CKeyboardEvent() : mType(KeyState::PRESSED), mWindowId(0), mScanCode(ScanCode::UNKNOWN), mKeyMod(KeyMod::NONE), mKeySymbol(0), mKeyRepeat(0) {}
      explicit CKeyboardEvent(CEvent const& other);

      KeyState GetType() const { return mType; }
      WindowID GetWindowId() const { return mWindowId; }
      ScanCode GetScanCode() const { return mScanCode; }
      KeyMod GetKeyMod() const { return mKeyMod; }
      cb::string::value_type GetKeySymbol() const { return mKeySymbol; }
      u32 GetKeyRepeat() const { return mKeyRepeat; }
    };

    class CMouseButtonEvent {
    private:
      KeyState mType;
      Button mButton;
      u32 mClicks;
      MouseID mMouseId;
      WindowID mWindowId;

    public:
      CMouseButtonEvent() : mType(KeyState::PRESSED), mButton(Button::LEFT), mClicks(0), mMouseId(0), mWindowId(0) {}
      explicit CMouseButtonEvent(CEvent const& other);

      KeyState GetType() const { return mType; }
      Button GetButton() const { return mButton; }
      u32 GetClicks() const { return mClicks; }
      MouseID GetMouseId() const { return mMouseId; }
      WindowID GetWindowId() const { return mWindowId; }
    };

    class CMouseMotionEvent {
    private:
      glm::ivec2 mPosition;
      glm::ivec2 mRelative;
      MouseID mMouseId;
      WindowID mWindowId;

    public:
      CMouseMotionEvent() : mMouseId(0), mWindowId(0) {}
      explicit CMouseMotionEvent(CEvent const& other);

      glm::ivec2 GetPosition() const { return mPosition; }
      glm::ivec2 GetRelative() const { return mRelative; }
      MouseID GetMouseId() const { return mMouseId; }
      WindowID GetWindowId() const { return mWindowId; }
    };

    class CMouseWheelEvent {
    private:
      glm::ivec2 mScroll;
      bool mFlipped;
      MouseID mMouseId;
      WindowID mWindowId;

    public:
      CMouseWheelEvent() : mFlipped(false), mMouseId(0), mWindowId() {}
      explicit CMouseWheelEvent(CEvent const& other);

      glm::ivec2 GetScroll() const { return mScroll; }
      bool IsFlipped() const { return mFlipped; }
      MouseID GetMouseId() const { return mMouseId; }
      WindowID GetWindowId() const { return mWindowId; }
    };

    class CTextInputEvent {
    private:
      WindowID mWindowId;
      cb::string mText;

    public:
      CTextInputEvent() : mWindowId(0) {}
      explicit CTextInputEvent(CEvent const& other);
      
      WindowID GetWindowId() const { return mWindowId; }
      cb::string GetText() const { return mText; }
    };

    class CTextEditingEvent {
    private:
      WindowID mWindowId;
      u32 mEditPos;
      u32 mEditLen;
      cb::string mText;

    public:
      CTextEditingEvent() : mWindowId(0), mEditPos(0), mEditLen(0) {}
      explicit CTextEditingEvent(CEvent const& other);

      WindowID GetWindowId() const { return mWindowId; }
      u32 GetEditPos() const { return mEditPos; }
      u32 GetEditLen() const { return mEditLen; }
      cb::string GetText() const { return mText; }
    };

    class CEvent {
    private:
      static constexpr size_t DATA_SIZE = 56; // SDL_Event universal size
      byte mData[DATA_SIZE] = {0};

    public:
      EventType GetType() const;

      byte* Get() { return mData; }
      byte const* Get() const { return mData; }

      CWindowEvent Window() const { return CWindowEvent(*this); }
      CKeyboardEvent Key() const { return CKeyboardEvent(*this); }
      CMouseButtonEvent Button() const { return CMouseButtonEvent(*this); }
      CMouseMotionEvent Motion() const { return CMouseMotionEvent(*this); }
      CMouseWheelEvent Wheel() const { return CMouseWheelEvent(*this); }
      CTextEditingEvent Edit() const { return CTextEditingEvent(*this); }
      CTextInputEvent Text() const { return CTextInputEvent(*this); }

      static bool Poll(CEvent& outEvent);
      static CEvent WaitFor();
      static CEvent WaitFor(std::chrono::milliseconds const& timeout);
    };
  }
}