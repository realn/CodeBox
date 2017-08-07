#include "stdafx.h"
#include <CBSDL/Window.h>
#include <CBSDL/DisplayMode.h>
#include <CBSDL/Surface.h>
#include <CBSDL/Consts.h>

#include <SDL_video.h>
#include "SDLConvert.h"
#include <algorithm>
#include <exception>

inline SDL_Window* Get(cb::sdl::CWindow& obj) {
  return reinterpret_cast<SDL_Window*>(obj.Get());
}

inline SDL_Window* Get(cb::sdl::CWindow const& obj) {
  return reinterpret_cast<SDL_Window*>(obj.Get());
}

namespace cb {
  namespace sdl {
    glm::ivec2 const CWindow::PosUndefined = glm::ivec2(SDL_WINDOWPOS_UNDEFINED);
    glm::ivec2 const CWindow::PosCentered = glm::ivec2(SDL_WINDOWPOS_CENTERED);

    CWindow::CWindow(cb::string const & name,
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

    CWindow::CWindow(CWindow && other) {
      std::swap(mWindow, other.mWindow);
    }

    CWindow::~CWindow() {
      if(mWindow) {
        SDL_DestroyWindow(::Get(*this));
        mWindow = nullptr;
      }
    }

    bool CWindow::SetDisplayMode(CDisplayMode const & mode) {
      auto sdlmode = convert(mode);
      auto res = SDL_SetWindowDisplayMode(::Get(*this), &sdlmode);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    void CWindow::SetTitle(string const & title) {
      auto winTitle = toUtf8(title);
      SDL_SetWindowTitle(::Get(*this), winTitle.data());
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetPosition(glm::ivec2 const & pos) {
      SDL_SetWindowPosition(::Get(*this), pos.x, pos.y);
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetSize(glm::uvec2 const & size) {
      SDL_SetWindowSize(::Get(*this), static_cast<int>(size.x), static_cast<int>(size.y));
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetMinimumSize(glm::uvec2 const & size) {
      SDL_SetWindowMinimumSize(::Get(*this), static_cast<int>(size.x), static_cast<int>(size.y));
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetMaximumSize(glm::uvec2 const & size) {
      SDL_SetWindowMaximumSize(::Get(*this), static_cast<int>(size.x), static_cast<int>(size.y));
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetBordered(bool const value) {
      SDL_SetWindowBordered(::Get(*this), value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetResizeable(bool const value) {
      SDL_SetWindowResizable(::Get(*this), value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
    }

    bool CWindow::SetFullscreen(bool const value) {
      auto res = SDL_SetWindowFullscreen(::Get(*this), value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    void CWindow::SetGrab(bool const value) {
      SDL_SetWindowGrab(::Get(*this), value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
    }

    bool CWindow::SetBrightness(float const value) {
      auto res = SDL_SetWindowBrightness(::Get(*this), value);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool CWindow::SetOpacity(float const value) {
      auto res = SDL_SetWindowOpacity(::Get(*this), value);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    int CWindow::GetDisplayIndex() const {
      auto res = SDL_GetWindowDisplayIndex(::Get(*this));
      CB_SDL_CHECKERRORS();
      return res;
    }

    CDisplayMode CWindow::GetDisplayMode() const {
      auto mode = SDL_DisplayMode();
      SDL_GetWindowDisplayMode(::Get(*this), &mode);
      CB_SDL_CHECKERRORS();
      return convert(mode);
    }

    PixelFormat CWindow::GetPixelFormat() const {
      auto format = SDL_GetWindowPixelFormat(::Get(*this));
      CB_SDL_CHECKERRORS();
      return static_cast<PixelFormat>(format);
    }

    WindowID CWindow::GetId() const {
      auto res = SDL_GetWindowID(::Get(*this));
      CB_SDL_CHECKERRORS();
      return res;
    }

    WindowFlag CWindow::GetFlags() const {
      auto flags = SDL_GetWindowFlags(::Get(*this));
      CB_SDL_CHECKERRORS();
      return static_cast<WindowFlag>(flags);
    }

    string CWindow::GetTitle() const {
      auto szTitle = SDL_GetWindowTitle(::Get(*this));
      CB_SDL_CHECKERRORS();
      return fromUtf8(cb::utf8string(szTitle));
    }

    glm::ivec2 CWindow::GetPosition() const {
      auto result = glm::ivec2();
      SDL_GetWindowPosition(::Get(*this), &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return result;
    }

    glm::uvec2 CWindow::GetSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowSize(::Get(*this), &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return glm::uvec2(result);
    }

    glm::uvec2 CWindow::GetMinimumSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowMinimumSize(::Get(*this), &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return glm::uvec2(result);
    }

    glm::uvec2 CWindow::GetMaximumSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowMaximumSize(::Get(*this), &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return glm::uvec2(result);
    }

    CSurface CWindow::GetSurface() {
      auto surface = SDL_GetWindowSurface(::Get(*this));
      CB_SDL_CHECKERRORS();
      return CSurface(surface);
    }

    bool CWindow::GetGrab() const {
      auto res = SDL_GetWindowGrab(::Get(*this));
      CB_SDL_CHECKERRORS();
      return res == SDL_TRUE;
    }

    float CWindow::GetBrightness() const {
      auto res = SDL_GetWindowBrightness(::Get(*this));
      CB_SDL_CHECKERRORS();
      return res;
    }

    float CWindow::GetOpacity() const {
      auto result = -1.0f;
      SDL_GetWindowOpacity(::Get(*this), &result);
      CB_SDL_CHECKERRORS();
      return result;
    }

    void CWindow::Show() {
      SDL_ShowWindow(::Get(*this));
      CB_SDL_CHECKERRORS();
    }

    void CWindow::Hide() {
      SDL_HideWindow(::Get(*this));
      CB_SDL_CHECKERRORS();
    }

    void CWindow::Raise() {
      SDL_RaiseWindow(::Get(*this));
      CB_SDL_CHECKERRORS();
    }

    void CWindow::Minimize() {
      SDL_MinimizeWindow(::Get(*this));
      CB_SDL_CHECKERRORS();
    }

    void CWindow::Maximize() {
      SDL_MaximizeWindow(::Get(*this));
      CB_SDL_CHECKERRORS();
    }

    void CWindow::Restore() {
      SDL_RestoreWindow(::Get(*this));
      CB_SDL_CHECKERRORS();
    }

    bool CWindow::UpdateSurface() {
      auto res = SDL_UpdateWindowSurface(::Get(*this));
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool CWindow::UpdateSurfaceRects(const std::vector<CRect>& rects) {
      auto res = SDL_UpdateWindowSurfaceRects(::Get(*this), 
                                              reinterpret_cast<const SDL_Rect*>(rects.data()), 
                                              static_cast<int>(rects.size()));
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool CWindow::SetInputFocus() {
      auto res = SDL_SetWindowInputFocus(::Get(*this));
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool CWindow::SetModalFor(CWindow & parent) {
      auto res = SDL_SetWindowModalFor(::Get(*this), ::Get(parent));
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    CWindow CWindow::FromId(WindowID const Id) {
      auto pWindow = SDL_GetWindowFromID(Id);
      CB_SDL_CHECKERRORS();
      return CWindow(pWindow);
    }

    CWindow CWindow::FromGrabbed() {
      auto pWindow = SDL_GetGrabbedWindow();
      CB_SDL_CHECKERRORS();
      return CWindow(pWindow);
    }

  }
}
