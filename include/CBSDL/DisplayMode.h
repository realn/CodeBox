#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    class CDisplayMode;

    using DisplayIDVecT = std::vector<DisplayID>;
    using DisplayModeVecT = std::vector<CDisplayMode>;

    extern DisplayID DisplayIDDefault;

    class CDisplayMode {
    private:
      PixelFormat mFormat;              /**< pixel format */
      glm::uvec2 mSize;
      RefreshRate mRefreshRate;
      void * mDriverData;           /**< driver-specific data, initialize to 0 */
    public:
      CDisplayMode(glm::uvec2 const& size = glm::uvec2(),
                   PixelFormat const format = PixelFormat::UNKNOWN,
                   RefreshRate const refreshRate = 0);
      ~CDisplayMode();

      void SetSize(glm::uvec2 const & size) { mSize = size; }
      void SetPixelFormat(PixelFormat const value) { mFormat = value; }
      void SetRefreshRate(RefreshRate const value) { mRefreshRate = value; }

      glm::uvec2 GetSize() const { return mSize; }
      PixelFormat GetPixelFormat() const { return mFormat; }
      RefreshRate GetRefreshRate() const { return mRefreshRate; }

      static DisplayModeVecT GetAll(DisplayID const& id = DisplayIDDefault);
      static CDisplayMode GetCurrent(DisplayID const& id = DisplayIDDefault);
      static CDisplayMode GetClosest(CDisplayMode const& mode, DisplayID const& id = DisplayIDDefault);
      static CDisplayMode GetFromDesktop(DisplayID const& id = DisplayIDDefault);
    };

    extern DisplayIDVecT GetAllDisplays();
  }
}