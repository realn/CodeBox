#include "stdafx.h"
#include <CBSDL/Window.h>
#include <CBSDL/DisplayMode.h>
#include <CBSDL/Surface.h>
#include <CBSDL/Consts.h>

#include <algorithm>
#include <exception>

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

    CWindow::CWindow(SDL_Window * window) :
      mWindow(window) {}

    CWindow::~CWindow() {
      if(mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
      }
    }

    bool CWindow::SetDisplayMode(CDisplayMode const & mode) {
      auto res = SDL_SetWindowDisplayMode(mWindow, &mode.Get());
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    void CWindow::SetTitle(string const & title) {
      auto winTitle = toUtf8(title);
      SDL_SetWindowTitle(mWindow, winTitle.data());
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetPosition(glm::ivec2 const & pos) {
      SDL_SetWindowPosition(mWindow, pos.x, pos.y);
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetSize(glm::uvec2 const & size) {
      SDL_SetWindowSize(mWindow, static_cast<int>(size.x), static_cast<int>(size.y));
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetMinimumSize(glm::uvec2 const & size) {
      SDL_SetWindowMinimumSize(mWindow, static_cast<int>(size.x), static_cast<int>(size.y));
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetMaximumSize(glm::uvec2 const & size) {
      SDL_SetWindowMaximumSize(mWindow, static_cast<int>(size.x), static_cast<int>(size.y));
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetBordered(bool const value) {
      SDL_SetWindowBordered(mWindow, value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
    }

    void CWindow::SetResizeable(bool const value) {
      SDL_SetWindowResizable(mWindow, value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
    }

    bool CWindow::SetFullscreen(bool const value) {
      auto res = SDL_SetWindowFullscreen(mWindow, value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    void CWindow::SetGrab(bool const value) {
      SDL_SetWindowGrab(mWindow, value ? SDL_TRUE : SDL_FALSE);
      CB_SDL_CHECKERRORS();
    }

    bool CWindow::SetBrightness(float const value) {
      auto res = SDL_SetWindowBrightness(mWindow, value);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool CWindow::SetOpacity(float const value) {
      auto res = SDL_SetWindowOpacity(mWindow, value);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    int CWindow::GetDisplayIndex() const {
      auto res = SDL_GetWindowDisplayIndex(mWindow);
      CB_SDL_CHECKERRORS();
      return res;
    }

    CDisplayMode CWindow::GetDisplayMode() const {
      auto mode = SDL_DisplayMode();
      SDL_GetWindowDisplayMode(mWindow, &mode);
      CB_SDL_CHECKERRORS();
      return CDisplayMode(mode);
    }

    PixelFormat CWindow::GetPixelFormat() const {
      auto format = SDL_GetWindowPixelFormat(mWindow);
      CB_SDL_CHECKERRORS();
      return static_cast<PixelFormat>(format);
    }

    WindowID CWindow::GetId() const {
      auto res = SDL_GetWindowID(mWindow);
      CB_SDL_CHECKERRORS();
      return res;
    }

    WindowFlag CWindow::GetFlags() const {
      auto flags = SDL_GetWindowFlags(mWindow);
      CB_SDL_CHECKERRORS();
      return static_cast<WindowFlag>(flags);
    }

    string CWindow::GetTitle() const {
      auto szTitle = SDL_GetWindowTitle(mWindow);
      CB_SDL_CHECKERRORS();
      return fromUtf8(cb::utf8string(szTitle));
    }

    glm::ivec2 CWindow::GetPosition() const {
      auto result = glm::ivec2();
      SDL_GetWindowPosition(mWindow, &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return result;
    }

    glm::uvec2 CWindow::GetSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowSize(mWindow, &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return glm::uvec2(result);
    }

    glm::uvec2 CWindow::GetMinimumSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowMinimumSize(mWindow, &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return glm::uvec2(result);
    }

    glm::uvec2 CWindow::GetMaximumSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowMaximumSize(mWindow, &result.x, &result.y);
      CB_SDL_CHECKERRORS();
      return glm::uvec2(result);
    }

    CSurface CWindow::GetSurface() {
      auto surface = SDL_GetWindowSurface(mWindow);
      CB_SDL_CHECKERRORS();
      return CSurface(surface);
    }

    bool CWindow::GetGrab() const {
      auto res = SDL_GetWindowGrab(mWindow);
      CB_SDL_CHECKERRORS();
      return res == SDL_TRUE;
    }

    float CWindow::GetBrightness() const {
      auto res = SDL_GetWindowBrightness(mWindow);
      CB_SDL_CHECKERRORS();
      return res;
    }

    float CWindow::GetOpacity() const {
      auto result = -1.0f;
      SDL_GetWindowOpacity(mWindow, &result);
      CB_SDL_CHECKERRORS();
      return result;
    }

    void CWindow::Show() {
      SDL_ShowWindow(mWindow);
      CB_SDL_CHECKERRORS();
    }

    void CWindow::Hide() {
      SDL_HideWindow(mWindow);
      CB_SDL_CHECKERRORS();
    }

    void CWindow::Raise() {
      SDL_RaiseWindow(mWindow);
      CB_SDL_CHECKERRORS();
    }

    void CWindow::Minimize() {
      SDL_MinimizeWindow(mWindow);
      CB_SDL_CHECKERRORS();
    }

    void CWindow::Maximize() {
      SDL_MaximizeWindow(mWindow);
      CB_SDL_CHECKERRORS();
    }

    void CWindow::Restore() {
      SDL_RestoreWindow(mWindow);
      CB_SDL_CHECKERRORS();
    }

    bool CWindow::UpdateSurface() {
      auto res = SDL_UpdateWindowSurface(mWindow);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool CWindow::UpdateSurfaceRects(const std::vector<SDL_Rect>& rects) {
      auto res = SDL_UpdateWindowSurfaceRects(mWindow, rects.data(), rects.size());
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool CWindow::SetInputFocus() {
      auto res = SDL_SetWindowInputFocus(mWindow);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    bool CWindow::SetModalFor(CWindow & parent) {
      auto res = SDL_SetWindowModalFor(mWindow, parent.mWindow);
      CB_SDL_CHECKERRORS();
      return res == 0;
    }

    CWindow CWindow::FromId(Uint32 const Id) {
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
