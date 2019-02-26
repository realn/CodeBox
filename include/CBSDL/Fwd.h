#pragma once

namespace cb {
  namespace sdl {
    enum class WindowFlag;
    enum class PixelFormat;
    enum class EventType;
    enum class WindowEventType;
    enum class KeyState;
    enum class ScanCode;
    enum class KeyMod;
    enum class Button;
    enum class GLAttribute;
    enum class FontStyle;
    enum class SeekPos;
    enum class FileMode;
    enum class FlipDir;
    enum class System;

    class CCursor;
    class CWindow;
    class CSystem;
    class CDisplayMode;
    class CSurface;
    class CRWObj;
    class CGLContext;
    class CEvent;
    class CWindowEvent;
    class CKeyboardEvent;
    class CMouseButtonEvent;
    class CMouseMotionEvent;
    class CMouseWheelEvent;
    class CTextInputEvent;
    class CTextEditingEvent;
    struct CGlyph;
    class CFont;
    class CPerfTimer;
  }
}