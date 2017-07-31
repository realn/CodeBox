#pragma once

#include "Defines.h"

namespace cb {
  namespace sdl {
    class CPerfTimer {
    private:
      Uint64 mFrequency;
      Uint64 mLastCount;
      float mDelta;
      
    public:
      CPerfTimer();

      void Update();

      float GetTimeDelta() const;
    };
  }
}