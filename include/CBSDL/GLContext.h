#pragma once

#include <map>

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    class Window;

    using GLAttributeMapT = std::map<GLAttribute, s32>;

    class GLContext {
    private:
      void* mContext = nullptr;

    public:
      GLContext(Window& window, GLAttributeMapT const & attributes);
      ~GLContext();

      void makeCurrent(Window& window);
      void swapWindow(Window& window);
    };
  }
}