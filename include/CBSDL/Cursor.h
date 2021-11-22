#pragma once

#include "Defines.h"

namespace cb {
  namespace sdl {
    enum class SystemCursor;
    class Surface;

    class Cursor {
    private:
      void* mCursor;

    public:
      using data8u = std::vector<cb::u8>;

      Cursor(const data8u& data, const data8u& mask, const glm::uvec2& size, const glm::uvec2& hotPos);
      Cursor(Surface& surface, const glm::uvec2& hotPos);
      Cursor(const SystemCursor cursor);
      Cursor(const Cursor&) = delete;
      Cursor(Cursor&& other);
      explicit Cursor(void* cursor);
      ~Cursor();

      void* get() const { return mCursor; }
    };

    void setCurrentCursor(const Cursor& cursor);
    Cursor getCurrentCursor();

    bool isCursorVisible();
    void setCursorVisible(bool const value);
  }
}