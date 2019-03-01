#include "stdafx.h"

#include <CBSDL/Cursor.h>
#include <CBSDL/Surface.h>

inline SDL_Cursor* Get(cb::sdl::CCursor& obj) {
  return reinterpret_cast<SDL_Cursor*>(obj.Get());
}

inline SDL_Cursor* Get(cb::sdl::CCursor const& obj) {
  return reinterpret_cast<SDL_Cursor*>(obj.Get());
}


namespace cb {
  namespace sdl {
    CCursor::CCursor(const data8u & data, const data8u & mask, const glm::uvec2 & size, const glm::uvec2 & hotPos) {
      mCursor = SDL_CreateCursor(data.data(), mask.data(), size.x, size.y, hotPos.x, hotPos.y);
      CB_SDL_CHECKERRORS();
    }

    CCursor::CCursor(CSurface & surface, const glm::uvec2 & hotPos) {
      mCursor = SDL_CreateColorCursor(reinterpret_cast<SDL_Surface*>(surface.Get()), hotPos.x, hotPos.y);
      CB_SDL_CHECKERRORS();
    }

    CCursor::CCursor(const SystemCursor cursor) {
      mCursor = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursor));
      CB_SDL_CHECKERRORS();
    }

    CCursor::CCursor(CCursor && other) : mCursor(nullptr) {
      std::swap(mCursor, other.mCursor);
    }

    CCursor::CCursor(void * cursor) : mCursor(cursor) { }

    CCursor::~CCursor() {
      if (mCursor) {
        SDL_FreeCursor(::Get(*this));
        mCursor = nullptr;
      }
    }

    void setCurrentCursor(const CCursor & cursor) {
      SDL_SetCursor(::Get(cursor));
      CB_SDL_CHECKERRORS();
    }

    CCursor getCurrentCursor() {
      auto cursor = SDL_GetCursor();
      CB_SDL_CHECKERRORS();
      return CCursor(cursor);
    }

    bool IsCursorVisible() {
      return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
    }

    void SetCursorVisible(bool const value) {
      SDL_ShowCursor(value ? SDL_ENABLE : SDL_DISABLE);
      CB_SDL_CHECKERRORS();
    }
  }
}
