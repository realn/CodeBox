#include "stdafx.h"
#include "../System.h"

namespace cb {
  namespace gl {
    void initextensions() {
      auto error = glewInit();
      if(error != GLEW_OK) {
        auto szError = reinterpret_cast<const char*>(glewGetErrorString(error));
        throw std::exception(szError);
      }
    }
  }
}