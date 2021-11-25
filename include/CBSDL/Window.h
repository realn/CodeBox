#pragma once

#include "Defines.h"
#include "Consts.h"

#include <glm/vec2.hpp>
#include <vector>

namespace cb {
  namespace sdl {
    class DisplayMode;
    class Surface;

    struct CRect {
      glm::ivec2 pos;
      glm::ivec2 size;
    };

    class Window {
    private:
      void* mWindow = nullptr;

    public:
      Window(const string& title,
             const glm::ivec2& pos = PosUndefined,
             const glm::uvec2& size = glm::uvec2(100),
             const WindowFlag& flags = WindowFlag::None);
      Window(Window const&) = delete;
      Window(Window&& other) = default;
      explicit Window(void* window) : mWindow(window) {}
      ~Window();

      void* get() const { return mWindow; };

      bool setDisplayMode(DisplayMode const& mode);
      void setTitle(string const& title);
      void setPosition(glm::ivec2 const& pos);
      void setSize(glm::uvec2 const& size);
      void setMinimumSize(glm::uvec2 const& size);
      void setMaximumSize(glm::uvec2 const& size);
      void setBordered(bool const value);
      void setResizeable(bool const value);
      bool setFullscreen(bool const value);
      void setGrab(bool const value);
      bool setBrightness(float const value);
      bool setOpacity(float const value);

      int getDisplayIndex() const;
      DisplayMode getDisplayMode() const;
      PixelFormat getPixelFormat() const;
      WindowID getId() const;
      WindowFlags getFlags() const;
      string getTitle() const;
      glm::ivec2 getPosition() const;
      glm::uvec2 getSize() const;
      glm::uvec2 getDrawableSize() const;
      glm::uvec2 getMinimumSize() const;
      glm::uvec2 getMaximumSize() const;
      Surface getSurface();
      bool getGrab() const;
      float getBrightness() const;
      float getOpacity() const;

      void show();
      void hide();
      void raise();
      void minimize();
      void maximize();
      void restore();
      bool updateSurface();
      bool updateSurfaceRects(const std::vector<CRect>& rects);
      bool setInputFocus();
      bool setModalFor(Window& parent);
      void warpMouse(glm::ivec2 pos);

      Window& operator=(Window const& other) = delete;
      Window& operator=(Window&&) = default;

      void* getWindowNativeHandle() const;

      static glm::ivec2 const PosUndefined;
      static glm::ivec2 const PosCentered;

      static Window fromId(WindowID const Id);
      static Window fromGrabbed();
    };
  }
}