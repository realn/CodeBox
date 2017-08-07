#pragma once

#include <map>

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    class CWindow;

    using GLAttributeMapT = std::map<GLAttribute, Sint32>;

    class CGLContext {
    private:
      void* mContext = nullptr;

    public:
      CGLContext(CWindow& window, GLAttributeMapT const & attributes);
      ~CGLContext();

      void MakeCurrent(CWindow& window);
      void SwapWindow(CWindow& window);
    };
  }
}