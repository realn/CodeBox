#pragma once

#include "Defines.h"
#include "Consts.h"

#include <glm/vec2.hpp>
#include <vector>

namespace cb {
  namespace sdl {
    class CDisplayMode;
    class CSurface;

    struct CRect {
      glm::ivec2 pos;
      glm::ivec2 size;
    };

    class CWindow {
    private:
      void* mWindow = nullptr;

    public:
      CWindow(const string& title,
              const glm::ivec2& pos = PosUndefined,
              const glm::uvec2& size = glm::uvec2(100),
              const WindowFlag& flags = WindowFlag::None);
      CWindow(CWindow const&) = delete;
      CWindow(CWindow&& other);
      explicit CWindow(void* window) : mWindow(window) {}
      ~CWindow();

      void* Get() const { return mWindow; };

      bool SetDisplayMode(CDisplayMode const& mode);
      void SetTitle(string const& title);
      void SetPosition(glm::ivec2 const& pos);
      void SetSize(glm::uvec2 const& size);
      void SetMinimumSize(glm::uvec2 const& size);
      void SetMaximumSize(glm::uvec2 const& size);
      void SetBordered(bool const value);
      void SetResizeable(bool const value);
      bool SetFullscreen(bool const value);
      void SetGrab(bool const value);
      bool SetBrightness(float const value);
      bool SetOpacity(float const value);
      
      int GetDisplayIndex() const;
      CDisplayMode GetDisplayMode() const;
      PixelFormat GetPixelFormat() const;
      WindowID GetId() const;
      WindowFlag GetFlags() const;
      string GetTitle() const;
      glm::ivec2 GetPosition() const;
      glm::uvec2 GetSize() const;
      glm::uvec2 GetMinimumSize() const;
      glm::uvec2 GetMaximumSize() const;
      CSurface GetSurface();
      bool GetGrab() const;
      float GetBrightness() const;
      float GetOpacity() const;

      void Show();
      void Hide();
      void Raise();
      void Minimize();
      void Maximize();
      void Restore();
      bool UpdateSurface();
      bool UpdateSurfaceRects(const std::vector<CRect>& rects);
      bool SetInputFocus();
      bool SetModalFor(CWindow& parent);

      void operator=(CWindow const & other) = delete;

      static glm::ivec2 const PosUndefined;
      static glm::ivec2 const PosCentered;

      static CWindow FromId(WindowID const Id);
      static CWindow FromGrabbed();
    };
  }
}