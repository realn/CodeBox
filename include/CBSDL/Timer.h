#pragma once

#include "Defines.h"

namespace cb {
  namespace sdl {
    class PerformanceTimer {
    private:
      u64 mFrequency;
      u64 mLastCount;
      float mDelta;
      
    public:
      PerformanceTimer();

      void update();

      float getTimeDelta() const;

      u64 getFrequency() const { return mFrequency; }
      u64 getLastCount() const { return mLastCount; }
    };
  }
}