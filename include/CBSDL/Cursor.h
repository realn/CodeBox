#pragma once

#include "Defines.h"

namespace cb {
  namespace sdl {
    enum class SystemCursor;
    class CSurface;

    class CCursor {
    private:
      void* mCursor;

    public:
      using data8u = std::vector<cb::u8>;

      CCursor(const data8u& data, const data8u& mask, const glm::uvec2& size, const glm::uvec2& hotPos);
      CCursor(CSurface& surface, const glm::uvec2& hotPos);
      CCursor(const SystemCursor cursor);
      CCursor(const CCursor&) = delete;
      CCursor(CCursor&& other);
      explicit CCursor(void* cursor);
      ~CCursor();

      void* Get() const { return mCursor; }
    };

    extern void setCurrentCursor(const CCursor& cursor);
    extern CCursor getCurrentCursor();

    extern bool IsCursorVisible();
    extern void SetCursorVisible(bool const value);
  }
}