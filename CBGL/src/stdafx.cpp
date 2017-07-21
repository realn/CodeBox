#include "stdafx.h"

#include <map>
#include <exception>

#define DEF_ERRCODE(A) {A, #A}

static const auto glErrorMap = std::map<GLenum, std::string>{
  DEF_ERRCODE(GL_NO_ERROR),
  DEF_ERRCODE(GL_INVALID_ENUM),
  DEF_ERRCODE(GL_INVALID_VALUE),
  DEF_ERRCODE(GL_INVALID_OPERATION),
  DEF_ERRCODE(GL_INVALID_FRAMEBUFFER_OPERATION),
  DEF_ERRCODE(GL_OUT_OF_MEMORY),
};

void checkGLErrors() {
  auto const error = glGetError();
  if(error == GL_NO_ERROR) {
    return;
  }

  auto it = glErrorMap.find(error);
  throw std::exception(it->second.c_str());
}
