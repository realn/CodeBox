#pragma once

#include "Defines.h"

namespace cb {
  namespace sdl {
    class CPerfTimer {
    private:
      u64 mFrequency;
      u64 mLastCount;
      float mDelta;
      
    public:
      CPerfTimer();

      void Update();

      float GetTimeDelta() const;

      u64 GetFrequency() const { return mFrequency; }
      u64 GetLastCount() const { return mLastCount; }
    };
  }
}