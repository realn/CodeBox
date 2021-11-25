#include "stdafx.h"
#include <CBSDL/Window.h>
#include <CBSDL/DisplayMode.h>
#include <CBSDL/Surface.h>
#include <CBSDL/Consts.h>
#include <CBCore/StringConvert.h>

#include "SDLConvert.h"
#include <SDL_video.h>
#include <SDL_syswm.h>
#include <algorithm>
#include <exception>

inline SDL_Window* get(cb::sdl::Window& obj) {
  return reinterpret_cast<SDL_Window*>(obj.get());
}

inline SDL_Window* get(cb::sdl::Window const& obj) {
  return reinterpret_cast<SDL_Window*>(obj.get());
}

namespace cb {
  namespace sdl {
    glm::ivec2 const Window::PosUndefined = glm::ivec2(SDL_WINDOWPOS_UNDEFINED);
    glm::ivec2 const Window::PosCentered = glm::ivec2(SDL_WINDOWPOS_CENTERED);

    Window::Window(cb::string const & name,
                     glm::ivec2 const & pos,
                     glm::uvec2 const & size,
                     WindowFlag const & flags) {
      auto title = cb::toUtf8(name);
      mWindow = SDL_CreateWindow(title.data(),
                                 pos.x, pos.y,
                                 static_cast<int>(size.x), static_cast<int>(size.y),
                                 static_cast<Uint32>(flags));
      CB_SDL_CHECKERRORS();
    }

    Window::~Window() {
      if(mWindow) {
        SDL_DestroyWindow(::get(*this));
        mWindow = nullptr;
      }
    }

    bool Window::setDisplayMode(DisplayMode const & mode) {
      auto sdlmode = convert(mode);
      auto res = SDL_SetWindowDisplayMode(::get(*this), &sdlmode);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    void Window::setTitle(string const & title) {
      auto winTitle = toUtf8(title);
      SDL_SetWindowTitle(::get(*this), winTitle.data());
      CB_SDL_CHECKERRORS();
    }

    void Window::setPosition(glm::ivec2 const & pos) {
      SDL_SetWindowPosition(::get(*this), pos.x, pos.y);
      CB_SDL_CHECKERRORS();
    }

    void Window::setSize(glm::uvec2 const & size) {
      SDL_SetWindowSize(::get(*this), static_cast<int>(size.x), static_cast<int>(size.y));
      CB_SDL_CHECKERRORS();
    }

    void Window::setMinimumSize(glm::uvec2 const & size) {
      SDL_SetWindowMinimumSize(::get(*this), static_cast<int>(size.x), static_cast<int>(size.y));
      CB_SDL_CHECKERRORS();
    }

    void Window::setMaximumSize(glm::uvec2 const & size) {
      SDL_SetWindowMaximumSize(::get(*this), static_cast<int>(size.x), static_cast<int>(size.y));
      CB_SDL_CHECKERRORS();
    }

    void Window::setBordered(bool const value) {
      SDL_SetWindowBordered(::get(*this), value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
    }

    void Window::setResizeable(bool const value) {
      SDL_SetWindowResizable(::get(*this), value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
    }

    bool Window::setFullscreen(bool const value) {
      auto res = SDL_SetWindowFullscreen(::get(*this), value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    void Window::setGrab(bool const value) {
      SDL_SetWindowGrab(::get(*this), value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
    }

    bool Window::setBrightness(float const value) {
      auto res = SDL_SetWindowBrightness(::get(*this), value);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool Window::setOpacity(float const value) {
      auto res = SDL_SetWindowOpacity(::get(*this), value);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    int Window::getDisplayIndex() const {
      auto res = SDL_GetWindowDisplayIndex(::get(*this));
      CB_SDL_CHECKERRORS();
      return res;
    }

    DisplayMode Window::getDisplayMode() const {
      auto mode = SDL_DisplayMode();
      SDL_GetWindowDisplayMode(::get(*this), &mode);
      CB_SDL_CHECKERRORS();
      return convert(mode);
    }

    PixelFormat Window::getPixelFormat() const {
      auto format = SDL_GetWindowPixelFormat(::get(*this));
      CB_SDL_CHECKERRORS();
      return static_cast<PixelFormat>(format);
    }

    WindowID Window::getId() const {
      auto res = SDL_GetWindowID(::get(*this));
      CB_SDL_CHECKERRORS();
      return res;
    }

    WindowFlags Window::getFlags() const {
      auto flags = SDL_GetWindowFlags(::get(*this));
      CB_SDL_CHECKERRORS();
      return static_cast<WindowFlag>(flags);
    }

    string Window::getTitle() const {
      auto szTitle = SDL_GetWindowTitle(::get(*this));
      CB_SDL_CHECKERRORS();
      return fromUtf8(cb::utf8string(szTitle));
    }

    glm::ivec2 Window::getPosition() const {
      auto result = glm::ivec2();
      SDL_GetWindowPosition(::get(*this), &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return result;
    }

    glm::uvec2 Window::getSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowSize(::get(*this), &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return glm::uvec2(result);
    }

    glm::uvec2 Window::getDrawableSize() const {
      auto result = glm::ivec2();
      SDL_GL_GetDrawableSize(::get(*this), &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return glm::uvec2(result);
    }

    glm::uvec2 Window::getMinimumSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowMinimumSize(::get(*this), &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return glm::uvec2(result);
    }

    glm::uvec2 Window::getMaximumSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowMaximumSize(::get(*this), &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return glm::uvec2(result);
    }

    Surface Window::getSurface() {
      auto surface = SDL_GetWindowSurface(::get(*this));
      CB_SDL_CHECKERRORS();
      return Surface(surface);
    }

    bool Window::getGrab() const {
      auto res = SDL_GetWindowGrab(::get(*this));
      CB_SDL_CHECKERRORS();
      return res == SDL_TRUE;
    }

    float Window::getBrightness() const {
      auto res = SDL_GetWindowBrightness(::get(*this));
      CB_SDL_CHECKERRORS();
      return res;
    }

    float Window::getOpacity() const {
      auto result = -1.0f;
      SDL_GetWindowOpacity(::get(*this), &result);
      CB_SDL_CHECKERRORS();
      return result;
    }

    void Window::show() {
      SDL_ShowWindow(::get(*this));
      CB_SDL_CHECKERRORS();
    }

    void Window::hide() {
      SDL_HideWindow(::get(*this));
      CB_SDL_CHECKERRORS();
    }

    void Window::raise() {
      SDL_RaiseWindow(::get(*this));
      CB_SDL_CHECKERRORS();
    }

    void Window::minimize() {
      SDL_MinimizeWindow(::get(*this));
      CB_SDL_CHECKERRORS();
    }

    void Window::maximize() {
      SDL_MaximizeWindow(::get(*this));
      CB_SDL_CHECKERRORS();
    }

    void Window::restore() {
      SDL_RestoreWindow(::get(*this));
      CB_SDL_CHECKERRORS();
    }

    bool Window::updateSurface() {
      auto res = SDL_UpdateWindowSurface(::get(*this));
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool Window::updateSurfaceRects(const std::vector<CRect>& rects) {
      auto res = SDL_UpdateWindowSurfaceRects(::get(*this), 
                                              reinterpret_cast<const SDL_Rect*>(rects.data()), 
                                              static_cast<int>(rects.size()));
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool Window::setInputFocus() {
      auto res = SDL_SetWindowInputFocus(::get(*this));
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool Window::setModalFor(Window & parent) {
      auto res = SDL_SetWindowModalFor(::get(*this), ::get(parent));
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    void Window::warpMouse(glm::ivec2 pos) {
      SDL_WarpMouseInWindow(::get(*this), pos.x, pos.y);
      CB_SDL_CHECKERRORS();
    }

    void * Window::getWindowNativeHandle() const {
#ifdef _WIN32
      SDL_SysWMinfo wmInfo;
      SDL_VERSION(&wmInfo.version);
      SDL_GetWindowWMInfo(::get(*this), &wmInfo);
      return wmInfo.info.win.window;
#else
      return nullptr;
#endif
    }

    Window Window::fromId(WindowID const Id) {
      auto pWindow = SDL_GetWindowFromID(Id);
      CB_SDL_CHECKERRORS();
      return Window(pWindow);
    }

    Window Window::fromGrabbed() {
      auto pWindow = SDL_GetGrabbedWindow();
      CB_SDL_CHECKERRORS();
      return Window(pWindow);
    }

  }
}
