#include "stdafx.h"
#include <CBSDL/Timer.h>

namespace cb {
  namespace sdl {
    PerformanceTimer::PerformanceTimer()
      : mFrequency(0), mLastCount(0), mDelta(0)
    {
      mFrequency = SDL_GetPerformanceFrequency();
      CB_SDL_CHECKERRORS();
      mLastCount = SDL_GetPerformanceCounter();
      CB_SDL_CHECKERRORS();
    }

    void PerformanceTimer::update() {
      auto thisCount = SDL_GetPerformanceCounter();
      auto diff = thisCount - mLastCount;
      auto delta = static_cast<double>(diff) / static_cast<double>(mFrequency);
      mDelta = static_cast<float>(delta);
      mLastCount = thisCount;
    }

    float PerformanceTimer::getTimeDelta() const {
      return mDelta;
    }
  }
}