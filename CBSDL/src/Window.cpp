#include "stdafx.h"
#include "../Window.h"
#include "../DisplayMode.h"
#include "../Surface.h"
#include "../Consts.h"

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
      auto title = cb::toUtf8(name, true);
      mWindow = SDL_CreateWindow(title.data(),
                                 pos.x, pos.y,
                                 static_cast<int>(size.x), static_cast<int>(size.y),
                                 static_cast<Uint32>(flags));
      if(!mWindow) {
        throw std::exception("Failed to create SDL window.");
      }
    }

    CWindow::CWindow(CWindow && other) {
      std::swap(mWindow, other.mWindow);
    }

    CWindow::~CWindow() {
      if(mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
      }
    }

    bool CWindow::SetDisplayMode(CDisplayMode const & mode) {
      return SDL_SetWindowDisplayMode(mWindow, &mode.Get()) == 0;
    }

    void CWindow::SetTitle(string const & title) {
      auto winTitle = toUtf8(title);
      SDL_SetWindowTitle(mWindow, winTitle.data());
    }

    void CWindow::SetPosition(glm::ivec2 const & pos) {
      SDL_SetWindowPosition(mWindow, pos.x, pos.y);
    }

    void CWindow::SetSize(glm::uvec2 const & size) {
      SDL_SetWindowSize(mWindow, static_cast<int>(size.x), static_cast<int>(size.y));
    }

    void CWindow::SetMinimumSize(glm::uvec2 const & size) {
      SDL_SetWindowMinimumSize(mWindow, static_cast<int>(size.x), static_cast<int>(size.y));
    }

    void CWindow::SetMaximumSize(glm::uvec2 const & size) {
      SDL_SetWindowMaximumSize(mWindow, static_cast<int>(size.x), static_cast<int>(size.y));
    }

    void CWindow::SetBordered(bool const value) {
      SDL_SetWindowBordered(mWindow, value ? SDL_TRUE : SDL_FALSE);
    }

    void CWindow::SetResizeable(bool const value) {
      SDL_SetWindowResizable(mWindow, value ? SDL_TRUE : SDL_FALSE);
    }

    bool CWindow::SetFullscreen(bool const value) {
      auto res = SDL_SetWindowFullscreen(mWindow, value ? SDL_TRUE : SDL_FALSE);
      return res == 0;
    }

    void CWindow::SetGrab(bool const value) {
      SDL_SetWindowGrab(mWindow, value ? SDL_TRUE : SDL_FALSE);
    }

    bool CWindow::SetBrightness(float const value) {
      return false;
    }

    bool CWindow::SetOpacity(float const value) {
      return false;
    }

    int CWindow::GetDisplayIndex() const {
      return SDL_GetWindowDisplayIndex(mWindow);
    }

    CDisplayMode CWindow::GetDisplayMode() const {
      SDL_DisplayMode mode;
      if(SDL_GetWindowDisplayMode(mWindow, &mode) != 0) {
        throw std::exception("Failed to get window display mode.");
      }
      return CDisplayMode(mode);
    }

    PixelFormat CWindow::GetPixelFormat() const {
      return static_cast<PixelFormat>(SDL_GetWindowPixelFormat(mWindow));
    }

    WindowID CWindow::GetId() const {
      return SDL_GetWindowID(mWindow);
    }

    WindowFlag CWindow::GetFlags() const {
      return static_cast<WindowFlag>(SDL_GetWindowFlags(mWindow));
    }

    string CWindow::GetTitle() const {
      auto szTitle = SDL_GetWindowTitle(mWindow);
      return fromUtf8(cb::utf8vec(szTitle));
    }

    glm::ivec2 CWindow::GetPosition() const {
      auto result = glm::ivec2();
      SDL_GetWindowPosition(mWindow, &result.x, &result.y);
      return result;
    }

    glm::uvec2 CWindow::GetSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowSize(mWindow, &result.x, &result.y);
      return glm::uvec2(result);
    }

    glm::uvec2 CWindow::GetMinimumSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowMinimumSize(mWindow, &result.x, &result.y);
      return glm::uvec2(result);
    }

    glm::uvec2 CWindow::GetMaximumSize() const {
      auto result = glm::ivec2();
      SDL_GetWindowMaximumSize(mWindow, &result.x, &result.y);
      return glm::uvec2(result);
    }

    CSurface CWindow::GetSurface() {
      auto surface = SDL_GetWindowSurface(mWindow);
      if(surface == nullptr) {
        throw std::exception("Failed to get surface from window.");
      }
      return CSurface();
    }

    bool CWindow::GetGrab() const {
      return SDL_GetWindowGrab(mWindow) == SDL_TRUE;
    }

    float CWindow::GetBrightness() const {
      return SDL_GetWindowBrightness(mWindow);
    }

    float CWindow::GetOpacity() const {
      auto result = -1.0f;
      SDL_GetWindowOpacity(mWindow, &result);
      return result;
    }

    void CWindow::Show() {
      SDL_ShowWindow(mWindow);
    }

    void CWindow::Hide() {
      SDL_HideWindow(mWindow);
    }

    void CWindow::Raise() {
      SDL_RaiseWindow(mWindow);
    }

    void CWindow::Minimize() {
      SDL_MinimizeWindow(mWindow);
    }

    void CWindow::Maximize() {
      SDL_MaximizeWindow(mWindow);
    }

    void CWindow::Restore() {
      SDL_RestoreWindow(mWindow);
    }

    bool CWindow::UpdateSurface() {
      return SDL_UpdateWindowSurface(mWindow) == 0;
    }

    bool CWindow::UpdateSurfaceRects(const std::vector<SDL_Rect>& rects) {
      return SDL_UpdateWindowSurfaceRects(mWindow, rects.data(), rects.size());
    }

    bool CWindow::SetInputFocus() {
      return SDL_SetWindowInputFocus(mWindow) == 0;
    }

    bool CWindow::SetModalFor(CWindow & parent) {
      return SDL_SetWindowModalFor(mWindow, parent.mWindow) == 0;
    }

    CWindow CWindow::FromId(Uint32 const Id) {
      auto pWindow = SDL_GetWindowFromID(Id);
      if(!pWindow) {
        throw std::exception("Invalid id to convert to window.");
      }
      return CWindow(pWindow);
    }

    CWindow CWindow::FromGrabbed() {
      auto pWindow = SDL_GetGrabbedWindow();
      if(!pWindow) {
        throw std::exception("No window grabbed.");
      }
      return CWindow(pWindow);
    }

    CWindow::CWindow(SDL_Window * window) :
      mWindow(window) {}
  }
}
