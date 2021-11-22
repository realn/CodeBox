#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    class DisplayMode;

    using DisplayIDVecT = std::vector<DisplayID>;
    using DisplayModeVecT = std::vector<DisplayMode>;

    DisplayID getDefaultDisplayID();
    DisplayIDVecT getAllDisplays();

    class DisplayMode {
    private:
      PixelFormat mFormat;              /**< pixel format */
      glm::uvec2 mSize;
      RefreshRate mRefreshRate;
      void * mDriverData;           /**< driver-specific data, initialize to 0 */
    public:
      DisplayMode(glm::uvec2 const& size = glm::uvec2(),
                   PixelFormat const format = PixelFormat::UNKNOWN,
                   RefreshRate const refreshRate = 0);
      ~DisplayMode();

      void setSize(glm::uvec2 const & size) { mSize = size; }
      void setPixelFormat(PixelFormat const value) { mFormat = value; }
      void setRefreshRate(RefreshRate const value) { mRefreshRate = value; }

      glm::uvec2 getSize() const { return mSize; }
      PixelFormat getPixelFormat() const { return mFormat; }
      RefreshRate getRefreshRate() const { return mRefreshRate; }

      static DisplayModeVecT getAll(DisplayID const& id = getDefaultDisplayID());
      static DisplayMode getCurrent(DisplayID const& id = getDefaultDisplayID());
      static DisplayMode getClosest(DisplayMode const& mode, DisplayID const& id = getDefaultDisplayID());
      static DisplayMode getFromDesktop(DisplayID const& id = getDefaultDisplayID());
    };
  }
}