#include "stdafx.h"
#include <CBSDL/Timer.h>

namespace cb {
  namespace sdl {
    CPerfTimer::CPerfTimer()
      : mFrequency(0), mLastCount(0), mDelta(0)
    {
      mFrequency = SDL_GetPerformanceFrequency();
      CB_SDL_CHECKERRORS();
      mLastCount = SDL_GetPerformanceCounter();
      CB_SDL_CHECKERRORS();
    }

    void CPerfTimer::Update() {
      auto diff = SDL_GetPerformanceCounter() - mLastCount;
      auto delta = static_cast<double>(diff) / static_cast<double>(mFrequency);
      mDelta = static_cast<float>(delta);
    }

    float CPerfTimer::GetTimeDelta() const {
      return mDelta;
    }
  }
}