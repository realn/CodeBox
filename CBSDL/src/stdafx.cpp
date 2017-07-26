#include "stdafx.h"

#include <SDL_error.h>

void CB_SDL_CHECKERRORS() {
  auto szError = SDL_GetError();
  if(szError == nullptr || strlen(szError) == 0) {
    return;
  }
  SDL_ClearError();
  throw std::exception(szError);
}
