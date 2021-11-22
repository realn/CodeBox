#include "stdafx.h"

#include <CBSDL/Cursor.h>
#include <CBSDL/Surface.h>

inline SDL_Cursor* get(cb::sdl::Cursor& obj) {
  return reinterpret_cast<SDL_Cursor*>(obj.get());
}

inline SDL_Cursor* get(cb::sdl::Cursor const& obj) {
  return reinterpret_cast<SDL_Cursor*>(obj.get());
}


namespace cb {
  namespace sdl {
    Cursor::Cursor(const data8u & data, const data8u & mask, const glm::uvec2 & size, const glm::uvec2 & hotPos) {
      mCursor = SDL_CreateCursor(data.data(), mask.data(), size.x, size.y, hotPos.x, hotPos.y);
      CB_SDL_CHECKERRORS();
    }

    Cursor::Cursor(Surface & surface, const glm::uvec2 & hotPos) {
      mCursor = SDL_CreateColorCursor(reinterpret_cast<SDL_Surface*>(surface.get()), hotPos.x, hotPos.y);
      CB_SDL_CHECKERRORS();
    }

    Cursor::Cursor(const SystemCursor cursor) {
      mCursor = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursor));
      CB_SDL_CHECKERRORS();
    }

    Cursor::Cursor(Cursor && other) : mCursor(nullptr) {
      std::swap(mCursor, other.mCursor);
    }

    Cursor::Cursor(void * cursor) : mCursor(cursor) { }

    Cursor::~Cursor() {
      if (mCursor) {
        SDL_FreeCursor(::get(*this));
        mCursor = nullptr;
      }
    }

    void setCurrentCursor(const Cursor & cursor) {
      SDL_SetCursor(::get(cursor));
      CB_SDL_CHECKERRORS();
    }

    Cursor getCurrentCursor() {
      auto cursor = SDL_GetCursor();
      CB_SDL_CHECKERRORS();
      return Cursor(cursor);
    }

    bool isCursorVisible() {
      return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
    }

    void setCursorVisible(bool const value) {
      SDL_ShowCursor(value ? SDL_ENABLE : SDL_DISABLE);
      CB_SDL_CHECKERRORS();
    }
  }
}
