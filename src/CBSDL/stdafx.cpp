#include "stdafx.h"

#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

void CB_SDL_CHECKERRORS() {
  auto szError = SDL_GetError();
  if(szError == nullptr || strlen(szError) == 0) {
    return;
  }
  SDL_ClearError();
  throw std::exception(szError);
}

void CB_IMG_CHECKERRORS() {
  auto szError = IMG_GetError();
  if(szError == nullptr || strlen(szError) == 0) {
    return;
  }
  SDL_ClearError();
  throw std::exception(szError);
}

void CB_TTF_CHECKERRORS() {
  auto szError = TTF_GetError();
  if(szError == nullptr || strlen(szError) == 0) {
    return;
  }
  SDL_ClearError();
  throw std::exception(szError);
}
