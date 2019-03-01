#pragma once

#include <CBCore/Flags.h>

#include "Defines.h"

namespace cb {
  namespace sdl {
    ENUM_FLAG(WindowFlag) {
      None = 0,
        FULLSCREEN = 0x00000001,         /**< fullscreen window */
        OPENGL = 0x00000002,             /**< window usable with OpenGL context */
        SHOWN = 0x00000004,              /**< window is visible */
        HIDDEN = 0x00000008,             /**< window is not visible */
        BORDERLESS = 0x00000010,         /**< no window decoration */
        RESIZABLE = 0x00000020,          /**< window can be resized */
        MINIMIZED = 0x00000040,          /**< window is minimized */
        MAXIMIZED = 0x00000080,          /**< window is maximized */
        INPUT_GRABBED = 0x00000100,      /**< window has grabbed input focus */
        INPUT_FOCUS = 0x00000200,        /**< window has input focus */
        MOUSE_FOCUS = 0x00000400,        /**< window has mouse focus */
        FULLSCREEN_DESKTOP = (FULLSCREEN | 0x00001000),
        FOREIGN = 0x00000800,            /**< window not created by SDL */
        ALLOW_HIGHDPI = 0x00002000,      /**< window should be created in high-DPI mode if supported */
        MOUSE_CAPTURE = 0x00004000,      /**< window has mouse captured (unrelated to INPUT_GRABBED) */
        ALWAYS_ON_TOP = 0x00008000,      /**< window should always be above others */
        SKIP_TASKBAR = 0x00010000,      /**< window should not be added to the taskbar */
        UTILITY = 0x00020000,      /**< window should be treated as a utility window */
        TOOLTIP = 0x00040000,      /**< window should be treated as a tooltip */
        POPUP_MENU = 0x00080000,      /**< window should be treated as a popup menu */
        VULKAN = 0x00100000,       /**< window usable for Vulkan surface */
    };


    namespace helper {
      enum class PIXELTYPE {
        UNKNOWN,
        INDEX1,
        INDEX4,
        INDEX8,
        PACKED8,
        PACKED16,
        PACKED32,
        ARRAYU8,
        ARRAYU16,
        ARRAYU32,
        ARRAYF16,
        ARRAYF32
      };

      enum class BITMAPORDER {
        NONE,
        B4321,
        B1234
      };

      enum class PACKEDORDER {
        NONE,
        XRGB,
        RGBX,
        ARGB,
        RGBA,
        XBGR,
        BGRX,
        ABGR,
        BGRA
      };

      enum class ARRAYORDER {
        NONE,
        RGB,
        RGBA,
        ARGB,
        BGR,
        BGRA,
        ABGR
      };

      enum class PACKEDLAYOUT {
        NONE,
        L332,
        L4444,
        L1555,
        L5551,
        L565,
        L8888,
        L2101010,
        L1010102
      };

      constexpr u32 DEFINE_PIXELFOURCC(s8 A, s8 B, s8 C, s8 D) {
        return
          (static_cast<u32>(static_cast<u8>(A)) << 0) |
          (static_cast<u32>(static_cast<u8>(B)) << 0) |
          (static_cast<u32>(static_cast<u8>(C)) << 0) |
          (static_cast<u32>(static_cast<u8>(D)) << 0);
      }

      constexpr u32 DEFINE_PIXELFORMAT(PIXELTYPE type, u32 order, u32 layout, u32 bits, u32 bytes) {
        return (1 << 28) | (static_cast<u32>(type) << 24) | (order << 20) | (layout << 16) | (bits << 8) | (bytes << 0);
      }

      constexpr u32 DEFINE_PIXELFORMAT(PIXELTYPE type, BITMAPORDER order, u32 layout, u32 bits, u32 bytes) {
        return DEFINE_PIXELFORMAT(type, static_cast<u32>(order), layout, bits, bytes);
      }

      constexpr u32 DEFINE_PIXELFORMAT(PIXELTYPE type, PACKEDORDER order, PACKEDLAYOUT layout, u32 bits, u32 bytes) {
        return DEFINE_PIXELFORMAT(type, static_cast<u32>(order), static_cast<u32>(layout), bits, bytes);
      }

      constexpr u32 DEFINE_PIXELFORMAT(PIXELTYPE type, ARRAYORDER order, u32 layout, u32 bits, u32 bytes) {
        return DEFINE_PIXELFORMAT(type, static_cast<u32>(order), layout, bits, bytes);
      }
    }

    enum class PixelFormat {
      UNKNOWN,
      INDEX1LSB = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::INDEX1, helper::BITMAPORDER::B4321, 0, 1, 0),
      INDEX1MSB = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::INDEX1, helper::BITMAPORDER::B1234, 0, 1, 0),
      INDEX4LSB = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::INDEX4, helper::BITMAPORDER::B4321, 0, 4, 0),
      INDEX4MSB = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::INDEX4, helper::BITMAPORDER::B1234, 0, 4, 0),
      INDEX8 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::INDEX8, 0, 0, 8, 1),
      RGB332 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED8, helper::PACKEDORDER::XRGB, helper::PACKEDLAYOUT::L332, 8, 1),
      RGB444 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::XRGB, helper::PACKEDLAYOUT::L4444, 12, 2),
      RGB555 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::XRGB, helper::PACKEDLAYOUT::L1555, 15, 2),
      BGR555 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::XBGR, helper::PACKEDLAYOUT::L1555, 15, 2),
      ARGB4444 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::ARGB, helper::PACKEDLAYOUT::L4444, 16, 2),
      RGBA4444 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::RGBA, helper::PACKEDLAYOUT::L4444, 16, 2),
      ABGR4444 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::ABGR, helper::PACKEDLAYOUT::L4444, 16, 2),
      BGRA4444 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::BGRA, helper::PACKEDLAYOUT::L4444, 16, 2),
      ARGB1555 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::ARGB, helper::PACKEDLAYOUT::L1555, 16, 2),
      RGBA5551 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::RGBA, helper::PACKEDLAYOUT::L5551, 16, 2),
      ABGR1555 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::ABGR, helper::PACKEDLAYOUT::L1555, 16, 2),
      BGRA5551 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::BGRA, helper::PACKEDLAYOUT::L5551, 16, 2),
      RGB565 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::XRGB, helper::PACKEDLAYOUT::L565, 16, 2),
      BGR565 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED16, helper::PACKEDORDER::XBGR, helper::PACKEDLAYOUT::L565, 16, 2),
      RGB24 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::ARRAYU8, helper::ARRAYORDER::RGB, 0, 24, 3),
      BGR24 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::ARRAYU8, helper::ARRAYORDER::BGR, 0, 24, 3),
      RGB888 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED32, helper::PACKEDORDER::XRGB, helper::PACKEDLAYOUT::L8888, 24, 4),
      RGBX8888 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED32, helper::PACKEDORDER::RGBX, helper::PACKEDLAYOUT::L8888, 24, 4),
      BGR888 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED32, helper::PACKEDORDER::XBGR, helper::PACKEDLAYOUT::L8888, 24, 4),
      BGRX8888 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED32, helper::PACKEDORDER::BGRX, helper::PACKEDLAYOUT::L8888, 24, 4),
      ARGB8888 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED32, helper::PACKEDORDER::ARGB, helper::PACKEDLAYOUT::L8888, 32, 4),
      RGBA8888 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED32, helper::PACKEDORDER::RGBA, helper::PACKEDLAYOUT::L8888, 32, 4),
      ABGR8888 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED32, helper::PACKEDORDER::ABGR, helper::PACKEDLAYOUT::L8888, 32, 4),
      BGRA8888 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED32, helper::PACKEDORDER::BGRA, helper::PACKEDLAYOUT::L8888, 32, 4),
      ARGB2101010 = helper::DEFINE_PIXELFORMAT(helper::PIXELTYPE::PACKED32, helper::PACKEDORDER::ARGB, helper::PACKEDLAYOUT::L2101010, 32, 4),

      /* Aliases for RGBA byte arrays of color data, for the current platform */
      //#if SDL_BYTEORDER == SDL_BIG_ENDIAN
      //RGBA32 = RGBA8888,
      //ARGB32 = ARGB8888,
      //BGRA32 = BGRA8888,
      //ABGR32 = ABGR8888,
      //#else
      RGBA32 = ABGR8888,
      ARGB32 = BGRA8888,
      BGRA32 = ARGB8888,
      ABGR32 = RGBA8888,
      //#endif

      YV12 = helper::DEFINE_PIXELFOURCC('Y', 'V', '1', '2'),
      IYUV = helper::DEFINE_PIXELFOURCC('I', 'Y', 'U', 'V'),
      YUY2 = helper::DEFINE_PIXELFOURCC('Y', 'U', 'Y', '2'),
      UYVY = helper::DEFINE_PIXELFOURCC('U', 'Y', 'V', 'Y'),
      YVYU = helper::DEFINE_PIXELFOURCC('Y', 'V', 'Y', 'U'),
      NV12 = helper::DEFINE_PIXELFOURCC('N', 'V', '1', '2'),
      NV21 = helper::DEFINE_PIXELFOURCC('N', 'V', '2', '1')
    };

    enum class EventType {
      FIRSTEVENT = 0,
      QUIT = 0x100,
      APP_TERMINATING,
      APP_LOWMEMORY,
      APP_WILLENTERBACKGROUND,
      APP_DIDENTERBACKGROUND,
      APP_WILLENTERFOREGROUND,
      APP_DIDENTERFOREGROUND,
      WINDOWEVENT = 0x200,
      SYSWMEVENT,
      KEYDOWN = 0x300,
      KEYUP,
      TEXTEDITING,
      TEXTINPUT,
      KEYMAPCHANGED,
      MOUSEMOTION = 0x400,
      MOUSEBUTTONDOWN,
      MOUSEBUTTONUP,
      MOUSEWHEEL,
      JOYAXISMOTION = 0x600, /**< Joystick axis motion */
      JOYBALLMOTION,          /**< Joystick trackball motion */
      JOYHATMOTION,           /**< Joystick hat position change */
      JOYBUTTONDOWN,          /**< Joystick button pressed */
      JOYBUTTONUP,            /**< Joystick button released */
      JOYDEVICEADDED,         /**< A new joystick has been inserted into the system */
      JOYDEVICEREMOVED,
      CONTROLLERAXISMOTION = 0x650, /**< Game controller axis motion */
      CONTROLLERBUTTONDOWN,          /**< Game controller button pressed */
      CONTROLLERBUTTONUP,            /**< Game controller button released */
      CONTROLLERDEVICEADDED,         /**< A new Game controller has been inserted into the system */
      CONTROLLERDEVICEREMOVED,       /**< An opened Game controller has been removed */
      CONTROLLERDEVICEREMAPPED,      /**< The controller mapping was updated */
      FINGERDOWN = 0x700,
      FINGERUP,
      FINGERMOTION,
      DOLLARGESTURE = 0x800,
      DOLLARRECORD,
      MULTIGESTURE,
      CLIPBOARDUPDATE = 0x900,
      DROPFILE = 0x1000, /**< The system requests a file open */
      DROPTEXT,                 /**< text/plain drag-and-drop event */
      DROPBEGIN,                /**< A new set of drops is beginning (NULL filename) */
      DROPCOMPLETE,
      AUDIODEVICEADDED = 0x1100, /**< A new audio device is available */
      AUDIODEVICEREMOVED,
      RENDER_TARGETS_RESET = 0x2000, /**< The render targets have been reset and their contents need to be updated */
      RENDER_DEVICE_RESET, /**< The device has been reset and all textures need to be recreated */
      USEREVENT = 0x8000,
      LASTEVENT = 0xFFFF
    };

    enum class WindowEventType {
      NONE,           /**< Never used */
      SHOWN,          /**< Window has been shown */
      HIDDEN,         /**< Window has been hidden */
      EXPOSED,        /**< Window has been exposed and should be redrawn */
      MOVED,          /**< Window has been moved to data1, data2 */
      RESIZED,        /**< Window has been resized to data1xdata2 */
      SIZE_CHANGED,   /**< The window size has changed, either as a result of an API call or through the system or user changing the window size. */
      MINIMIZED,      /**< Window has been minimized */
      MAXIMIZED,      /**< Window has been maximized */
      RESTORED,       /**< Window has been restored to normal size and position */
      ENTER,          /**< Window has gained mouse focus */
      LEAVE,          /**< Window has lost mouse focus */
      FOCUS_GAINED,   /**< Window has gained keyboard focus */
      FOCUS_LOST,     /**< Window has lost keyboard focus */
      CLOSE,          /**< The window manager requests that the window be closed */
      TAKE_FOCUS,     /**< Window is being offered a focus (should SetWindowInputFocus() on itself or a subwindow, or ignore) */
      HIT_TEST        /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
    };

    enum class KeyState {
      PRESSED = 1,
      RELEASED = 0,
    };

    enum class ScanCode {
      UNKNOWN = 0,
      A = 4,
      B = 5,
      C = 6,
      D = 7,
      E = 8,
      F = 9,
      G = 10,
      H = 11,
      I = 12,
      J = 13,
      K = 14,
      L = 15,
      M = 16,
      N = 17,
      O = 18,
      P = 19,
      Q = 20,
      R = 21,
      S = 22,
      T = 23,
      U = 24,
      V = 25,
      W = 26,
      X = 27,
      Y = 28,
      Z = 29,
      K1 = 30,
      K2 = 31,
      K3 = 32,
      K4 = 33,
      K5 = 34,
      K6 = 35,
      K7 = 36,
      K8 = 37,
      K9 = 38,
      K0 = 39,
      RETURN = 40,
      ESCAPE = 41,
      BACKSPACE = 42,
      TAB = 43,
      SPACE = 44,
      MINUS = 45,
      EQUALS = 46,
      LEFTBRACKET = 47,
      RIGHTBRACKET = 48,
      BACKSLASH = 49,
      NONUSHASH = 50,
      SEMICOLON = 51,
      APOSTROPHE = 52,
      GRAVE = 53,
      COMMA = 54,
      PERIOD = 55,
      SLASH = 56,
      CAPSLOCK = 57,
      F1 = 58,
      F2 = 59,
      F3 = 60,
      F4 = 61,
      F5 = 62,
      F6 = 63,
      F7 = 64,
      F8 = 65,
      F9 = 66,
      F10 = 67,
      F11 = 68,
      F12 = 69,
      PRINTSCREEN = 70,
      SCROLLLOCK = 71,
      PAUSE = 72,
      INSERT = 73,
      HOME = 74,
      PAGEUP = 75,
      DELETE = 76,
      END = 77,
      PAGEDOWN = 78,
      RIGHT = 79,
      LEFT = 80,
      DOWN = 81,
      UP = 82,
      NUMLOCKCLEAR = 83,
      KP_DIVIDE = 84,
      KP_MULTIPLY = 85,
      KP_MINUS = 86,
      KP_PLUS = 87,
      KP_ENTER = 88,
      KP_1 = 89,
      KP_2 = 90,
      KP_3 = 91,
      KP_4 = 92,
      KP_5 = 93,
      KP_6 = 94,
      KP_7 = 95,
      KP_8 = 96,
      KP_9 = 97,
      KP_0 = 98,
      KP_PERIOD = 99,
      NONUSBACKSLASH = 100,
      APPLICATION = 101,
      POWER = 102,
      KP_EQUALS = 103,
      F13 = 104,
      F14 = 105,
      F15 = 106,
      F16 = 107,
      F17 = 108,
      F18 = 109,
      F19 = 110,
      F20 = 111,
      F21 = 112,
      F22 = 113,
      F23 = 114,
      F24 = 115,
      EXECUTE = 116,
      HELP = 117,
      MENU = 118,
      SELECT = 119,
      STOP = 120,
      AGAIN = 121,
      UNDO = 122,
      CUT = 123,
      COPY = 124,
      PASTE = 125,
      FIND = 126,
      MUTE = 127,
      VOLUMEUP = 128,
      VOLUMEDOWN = 129,
      KP_COMMA = 133,
      KP_EQUALSAS400 = 134,
      INTERNATIONAL1 = 135,
      INTERNATIONAL2 = 136,
      INTERNATIONAL3 = 137,
      INTERNATIONAL4 = 138,
      INTERNATIONAL5 = 139,
      INTERNATIONAL6 = 140,
      INTERNATIONAL7 = 141,
      INTERNATIONAL8 = 142,
      INTERNATIONAL9 = 143,
      LANG1 = 144, /**< Hangul/English toggle */
      LANG2 = 145, /**< Hanja conversion */
      LANG3 = 146, /**< Katakana */
      LANG4 = 147, /**< Hiragana */
      LANG5 = 148, /**< Zenkaku/Hankaku */
      LANG6 = 149, /**< reserved */
      LANG7 = 150, /**< reserved */
      LANG8 = 151, /**< reserved */
      LANG9 = 152, /**< reserved */
      ALTERASE = 153, /**< Erase-Eaze */
      SYSREQ = 154,
      CANCEL = 155,
      CLEAR = 156,
      PRIOR = 157,
      RETURN2 = 158,
      SEPARATOR = 159,
      OUT = 160,
      OPER = 161,
      CLEARAGAIN = 162,
      CRSEL = 163,
      EXSEL = 164,
      KP_00 = 176,
      KP_000 = 177,
      THOUSANDSSEPARATOR = 178,
      DECIMALSEPARATOR = 179,
      CURRENCYUNIT = 180,
      CURRENCYSUBUNIT = 181,
      KP_LEFTPAREN = 182,
      KP_RIGHTPAREN = 183,
      KP_LEFTBRACE = 184,
      KP_RIGHTBRACE = 185,
      KP_TAB = 186,
      KP_BACKSPACE = 187,
      KP_A = 188,
      KP_B = 189,
      KP_C = 190,
      KP_D = 191,
      KP_E = 192,
      KP_F = 193,
      KP_XOR = 194,
      KP_POWER = 195,
      KP_PERCENT = 196,
      KP_LESS = 197,
      KP_GREATER = 198,
      KP_AMPERSAND = 199,
      KP_DBLAMPERSAND = 200,
      KP_VERTICALBAR = 201,
      KP_DBLVERTICALBAR = 202,
      KP_COLON = 203,
      KP_HASH = 204,
      KP_SPACE = 205,
      KP_AT = 206,
      KP_EXCLAM = 207,
      KP_MEMSTORE = 208,
      KP_MEMRECALL = 209,
      KP_MEMCLEAR = 210,
      KP_MEMADD = 211,
      KP_MEMSUBTRACT = 212,
      KP_MEMMULTIPLY = 213,
      KP_MEMDIVIDE = 214,
      KP_PLUSMINUS = 215,
      KP_CLEAR = 216,
      KP_CLEARENTRY = 217,
      KP_BINARY = 218,
      KP_OCTAL = 219,
      KP_DECIMAL = 220,
      KP_HEXADECIMAL = 221,
      LCTRL = 224,
      LSHIFT = 225,
      LALT = 226, /**< alt, option */
      LGUI = 227, /**< windows, command (apple), meta */
      RCTRL = 228,
      RSHIFT = 229,
      RALT = 230, /**< alt gr, option */
      RGUI = 231, /**< windows, command (apple), meta */
      MODE = 257,
      AUDIONEXT = 258,
      AUDIOPREV = 259,
      AUDIOSTOP = 260,
      AUDIOPLAY = 261,
      AUDIOMUTE = 262,
      MEDIASELECT = 263,
      WWW = 264,
      MAIL = 265,
      CALCULATOR = 266,
      COMPUTER = 267,
      AC_SEARCH = 268,
      AC_HOME = 269,
      AC_BACK = 270,
      AC_FORWARD = 271,
      AC_STOP = 272,
      AC_REFRESH = 273,
      AC_BOOKMARKS = 274,
      BRIGHTNESSDOWN = 275,
      BRIGHTNESSUP = 276,
      DISPLAYSWITCH = 277, 
      KBDILLUMTOGGLE = 278,
      KBDILLUMDOWN = 279,
      KBDILLUMUP = 280,
      EJECT = 281,
      SLEEP = 282,
      APP1 = 283,
      APP2 = 284,
      AUDIOREWIND = 285,
      AUDIOFASTFORWARD = 286,
      SDL_NUM_SCANCODES = 512
    };

    ENUM_FLAG(KeyMod) {
      NONE = 0x0000,
        LSHIFT = 0x0001,
        RSHIFT = 0x0002,
        SHIFT = 0x0003,
        LCTRL = 0x0040,
        RCTRL = 0x0080,
        CTRL = 0x00B0,
        LALT = 0x0100,
        RALT = 0x0200,
        ALT = 0x0300,
        LGUI = 0x0400,
        RGUI = 0x0800,
        GUI = 0x0B00,
        NUM = 0x1000,
        CAPS = 0x2000,
        MODE = 0x4000,
        RESERVED = 0x8000
    };

    enum class Button {
      LEFT = 1,
      MIDDLE = 2,
      RIGHT = 3,
      X1 = 4,
      X2 = 5,
    };

    ENUM_FLAG(ButtonFlag) {
      LEFT = ShiftBit(Button::LEFT),
      MIDDLE = ShiftBit(Button::MIDDLE),
      RIGHT = ShiftBit(Button::RIGHT),
      X1 = ShiftBit(Button::X1),
      X2 = ShiftBit(Button::X2)
    };

    enum class GLAttribute {
      RED_SIZE,
      GREEN_SIZE,
      BLUE_SIZE,
      ALPHA_SIZE,
      BUFFER_SIZE,
      DOUBLEBUFFER,
      DEPTH_SIZE,
      STENCIL_SIZE,
      ACCUM_RED_SIZE,
      ACCUM_GREEN_SIZE,
      ACCUM_BLUE_SIZE,
      ACCUM_ALPHA_SIZE,
      STEREO,
      MULTISAMPLEBUFFERS,
      MULTISAMPLESAMPLES,
      ACCELERATED_VISUAL,
      RETAINED_BACKING,
      CONTEXT_MAJOR_VERSION,
      CONTEXT_MINOR_VERSION,
      CONTEXT_EGL,
      CONTEXT_FLAGS,
      CONTEXT_PROFILE_MASK,
      SHARE_WITH_CURRENT_CONTEXT,
      FRAMEBUFFER_SRGB_CAPABLE,
      CONTEXT_RELEASE_BEHAVIOR
    };

    enum class SystemCursor {
      ARROW,     /**< Arrow */
      IBEAM,     /**< I-beam */
      WAIT,      /**< Wait */
      CROSSHAIR, /**< Crosshair */
      WAITARROW, /**< Small wait cursor (or Wait if not available) */
      SIZENWSE,  /**< Double arrow pointing northwest and southeast */
      SIZENESW,  /**< Double arrow pointing northeast and southwest */
      SIZEWE,    /**< Double arrow pointing west and east */
      SIZENS,    /**< Double arrow pointing north and south */
      SIZEALL,   /**< Four pointed arrow pointing north, south, east, and west */
      NO,        /**< Slashed circle or crossbones */
      HAND,      /**< Hand */
      NUM_SYSTEM_CURSORS
    };
  }
}
