#pragma once

#include <map>

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    class Window;

    using GLAttributeMapT = std::map<GLAttribute, s32>;

    // use BEFORE WINDOW CREATION
    void setContextCreationAttributes(GLAttributeMapT const& attributes);

    class GLContext {
    private:
      void* mContext = nullptr;

    public:
      GLContext(Window& window);
      ~GLContext();

      void makeCurrent(Window& window);
      void swapWindow(Window& window);
    };
  }
}