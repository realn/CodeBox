#include "stdafx.h"

#include <map>
#include <exception>


enum class GLERRCODE {
  NO_ERROR = GL_NO_ERROR,
  INVALID_ENUM = GL_INVALID_ENUM,
  INVALID_VALUE = GL_INVALID_VALUE,
  INVALID_OPERATION = GL_INVALID_OPERATION,
  INVALID_FRAMEBUFFER_OPERATION = GL_INVALID_FRAMEBUFFER_OPERATION,
  OUT_OF_MEMORY = GL_OUT_OF_MEMORY,
};

#define DEF_ERRCODE(A) {GLERRCODE::A, #A}
static const auto glErrorMap = std::map<GLERRCODE, std::string>{
  DEF_ERRCODE(NO_ERROR),
  DEF_ERRCODE(INVALID_ENUM),
  DEF_ERRCODE(INVALID_VALUE),
  DEF_ERRCODE(INVALID_OPERATION),
  DEF_ERRCODE(INVALID_FRAMEBUFFER_OPERATION),
  DEF_ERRCODE(OUT_OF_MEMORY),
};

void checkGLErrors() {
  auto const error = static_cast<GLERRCODE>(glGetError());
  if(error == GLERRCODE::NO_ERROR) {
    return;
  }

  auto it = glErrorMap.find(error);
  throw std::exception(it->second.c_str());
}
