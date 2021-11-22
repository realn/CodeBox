#include "stdafx.h"
#include <CBSDL/Surface.h>
#include <CBSDL/RWObj.h>

#include <SDL_surface.h>
#include <SDL_image.h>

inline SDL_RWops* get(cb::sdl::RWObj& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.get());
}

inline SDL_RWops* get(cb::sdl::RWObj const& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.get());
}

inline SDL_Surface* get(cb::sdl::Surface& surface) {
  return reinterpret_cast<SDL_Surface*>(surface.get());
}

inline SDL_Surface* get(cb::sdl::Surface const& surface) {
  return reinterpret_cast<SDL_Surface*>(surface.get());
}

namespace cb {
  namespace sdl {
    namespace {
      SDL_Rect toSdlRect(glm::uvec2 const& pos, glm::uvec2 const& size) {
        return SDL_Rect{
          static_cast<int>(pos.x), static_cast<int>(pos.y),
          static_cast<int>(size.x), static_cast<int>(size.y)
        };
      }
    }

    Surface::Surface(glm::uvec2 const size, unsigned const depth, PixelFormat const format)
      : mSurface(nullptr) {
      mSurface = SDL_CreateRGBSurfaceWithFormat(0, size.x, size.y, depth,
                                                static_cast<unsigned>(format));
      CB_SDL_CHECKERRORS();
    }

    Surface::Surface(Surface && other) : mSurface(nullptr) {
      std::swap(mSurface, other.mSurface);
    }

    Surface::~Surface() {
      if(mSurface) {
        SDL_FreeSurface(::get(*this));
        mSurface = nullptr;
      }
    }

    void Surface::operator=(Surface && other) {
      std::swap(mSurface, other.mSurface);
    }

    void Surface::setPixels(std::vector<cb::byte> const & data) {
      if(data.size() != ::get(*this)->w * ::get(*this)->h * ::get(*this)->format->BytesPerPixel) {
        throw std::exception("Invalid data size to set to sdl surface.");
      }

      SDL_LockSurface(::get(*this));
      auto pData = reinterpret_cast<cb::byte*>(::get(*this)->pixels);
      std::memcpy(::get(*this)->pixels, data.data(), data.size());
      SDL_UnlockSurface(::get(*this));
    }

    glm::uvec2 Surface::getSize() const {
      return glm::uvec2(static_cast<unsigned>(::get(*this)->w),
                        static_cast<unsigned>(::get(*this)->h));
    }

    unsigned Surface::getDepth() const {
      return ::get(*this)->format->BitsPerPixel;
    }

    PixelFormat Surface::getFormat() const {
      return static_cast<PixelFormat>(::get(*this)->format->format);
    }

    cb::bytevector Surface::getPixels() const {
      auto len = ::get(*this)->w * ::get(*this)->h * ::get(*this)->format->BytesPerPixel;
      auto result = cb::bytevector(len);
      SDL_LockSurface(::get(*this));
      std::memcpy(result.data(), ::get(*this)->pixels, len);
      SDL_UnlockSurface(::get(*this));
      return result;
    }

    Surface Surface::copy() const {
      SDL_LockSurface(::get(*this));
      CB_SDL_CHECKERRORS();
      auto surface =
        SDL_CreateRGBSurfaceWithFormatFrom(::get(*this)->pixels,
                                           ::get(*this)->w,
                                           ::get(*this)->h,
                                           ::get(*this)->format->BitsPerPixel,
                                           ::get(*this)->pitch,
                                           ::get(*this)->format->format);
      SDL_UnlockSurface(::get(*this));
      CB_SDL_CHECKERRORS();
      return Surface(surface);
    }

    Surface Surface::convert(PixelFormat const format) const {
      auto surface = SDL_ConvertSurfaceFormat(::get(*this), static_cast<Uint32>(format), 0);
      CB_SDL_CHECKERRORS();
      return Surface(surface);
    }

    void Surface::paste(glm::uvec2 const & dstPos, Surface const & source) {
      auto dstRect = toSdlRect(dstPos, glm::uvec2());
      SDL_BlitSurface(::get(source), nullptr, ::get(*this), &dstRect);
      CB_SDL_CHECKERRORS();
    }

    void Surface::paste(glm::uvec2 const & dstPos, Surface const & source, 
                         glm::uvec2 const & srcPos, glm::uvec2 const & srcSize) {
      auto dstRect = toSdlRect(dstPos, glm::uvec2());
      auto srcRect = toSdlRect(srcPos, srcSize);
      SDL_BlitSurface(::get(source), &srcRect, ::get(*this), &dstRect);
      CB_SDL_CHECKERRORS();
    }

    void Surface::pasteScaled(glm::uvec2 const & dstPos, glm::uvec2 const & dstSize, 
                               Surface const & source) {
      auto dstRect = toSdlRect(dstPos, dstSize);
      SDL_BlitScaled(::get(source), nullptr, ::get(*this), &dstRect);
      CB_SDL_CHECKERRORS();
    }

    void Surface::pasteScaled(glm::uvec2 const & dstPos, glm::uvec2 const & dstSize, 
                               Surface const & source, 
                               glm::uvec2 const & srcPos, glm::uvec2 const & srcSize) {
      auto dstRect = toSdlRect(dstPos, dstSize);
      auto srcRect = toSdlRect(srcPos, srcSize);
      SDL_BlitScaled(::get(source), &srcRect, ::get(*this), &dstRect);
      CB_SDL_CHECKERRORS();
    }

    void Surface::flip(FlipDir const dir) {
      switch(dir) {
      case FlipDir::Horizontal: flipHorizontal(); break;
      case FlipDir::Vertical:   flipVertical(); break;
      default:
        throw std::exception("Unknown sdl surface flip direction.");
      }
    }

    void Surface::fill(glm::vec4 const & color) {
      fill(glm::u8vec4(color * 255.0f));
    }

    void Surface::fill(glm::u8vec4 const & color) {
      auto surf = ::get(*this);
      auto col = SDL_MapRGBA(surf->format, color.r, color.g, color.b, color.a);
      SDL_FillRect(surf, nullptr, col);
      CB_SDL_CHECKERRORS();
    }

    void Surface::fill(glm::vec4 const & color, glm::uvec2 const & pos, glm::uvec2 const & size) {
      fill(glm::u8vec4(color * 255.0f), pos, size);
    }

    void Surface::fill(glm::u8vec4 const & color, glm::uvec2 const & pos, glm::uvec2 const & size) {
      auto surf = ::get(*this);
      auto col = SDL_MapRGBA(surf->format, color.r, color.g, color.b, color.a);
      auto rect = SDL_Rect{
        static_cast<int>(pos.x), static_cast<int>(pos.y),
        static_cast<int>(size.x), static_cast<int>(size.y)
      };
      SDL_FillRect(surf, &rect, col);
      CB_SDL_CHECKERRORS();
    }

    void Surface::flipHorizontal() {
      SDL_LockSurface(::get(*this));
      auto pData = reinterpret_cast<cb::byte*>(::get(*this)->pixels);
      auto size = getSize();
      auto hwidth = size.x / 2;
      auto pitch = unsigned(::get(*this)->pitch);
      auto bytes = unsigned(::get(*this)->format->BytesPerPixel);
      for(auto y = 0u; y < size.y; y++) {
        auto linebeg = y * pitch;
        auto lineend = (y + 1) * pitch - bytes;

        for(auto x = 0u; x < pitch/2; x += bytes) {
          auto idx1 = linebeg + x;
          auto idx2 = lineend - x;

          for(auto i = 0u; i < bytes; i++) {
            std::swap(pData[idx1 + i], pData[idx2 + i]);
          }
        }
      }
      SDL_UnlockSurface(::get(*this));
    }

    void Surface::flipVertical() {
      SDL_LockSurface(::get(*this));
      auto pData = reinterpret_cast<cb::byte*>(::get(*this)->pixels);
      auto size = getSize();
      auto pitch = unsigned(::get(*this)->pitch);
      auto bytes = unsigned(::get(*this)->format->BytesPerPixel);
      for(auto y = 0u; y < size.y/2; y++) {
        auto lineidx1 = y * pitch;
        auto lineidx2 = (size.y - 1 - y) * pitch;
        for(auto x = 0u; x < pitch; x ++) {
          std::swap(pData[lineidx1 + x], pData[lineidx2 + x]);
        }
      }
      SDL_UnlockSurface(::get(*this));
    }

    Surface Surface::loadBMP(cb::string const & filepath) {
      auto file = RWObj::fromFile(filepath, FileMode::read);
      return loadBMP(file);
    }

    Surface Surface::loadBMP(RWObj & rwObj) {
      auto surface = SDL_LoadBMP_RW(::get(rwObj), 0);
      CB_SDL_CHECKERRORS();
      return Surface(surface);
    }

    Surface Surface::loadPNG(cb::string const & filepath) {
      auto file = RWObj::fromFile(filepath, FileMode::read);
      return loadPNG(file);
    }

    Surface Surface::loadPNG(RWObj & rwObj) {
      auto surface = IMG_LoadPNG_RW(::get(rwObj));
      CB_IMG_CHECKERRORS();
      return Surface(surface);
    }

    Surface Surface::loadTGA(cb::string const & filepath) {
      auto file = RWObj::fromFile(filepath, FileMode::read);
      return loadTGA(file);
    }

    Surface Surface::loadTGA(RWObj & rwObj) {
      auto surface = IMG_LoadTGA_RW(::get(rwObj));
      CB_IMG_CHECKERRORS();
      return Surface(surface);
    }

    Surface Surface::loadJPG(cb::string const & filepath) {
      auto file = RWObj::fromFile(filepath, FileMode::read);
      return loadJPG(file);
    }

    Surface Surface::loadJPG(RWObj & rwObj) {
      auto surface = IMG_LoadJPG_RW(::get(rwObj));
      CB_IMG_CHECKERRORS();
      return Surface(surface);
    }

    Surface Surface::load(cb::string const & filepath) {
      auto file = RWObj::fromFile(filepath, FileMode::read);
      return load(file);
    }

    Surface Surface::load(RWObj & rwObj) {
      auto surface = IMG_Load_RW(::get(rwObj), 0);
      CB_IMG_CHECKERRORS();
      return Surface(surface);
    }

    bool Surface::saveBMP(cb::string const & filepath) const {
      auto file = RWObj::fromFile(filepath, FileMode::write);
      return saveBMP(file);
    }

    bool Surface::saveBMP(RWObj & rwObj) const {
      auto result = SDL_SaveBMP_RW(::get(*this), ::get(rwObj), 0);
      CB_SDL_CHECKERRORS();
      return result == 0;
    }

    bool Surface::savePNG(cb::string const & filepath) const {
      auto file = RWObj::fromFile(filepath, FileMode::write);
      return savePNG(file);
    }

    bool Surface::savePNG(RWObj & rwObj) const {
      auto result = IMG_SavePNG_RW(::get(*this), ::get(rwObj), 0);
      CB_SDL_CHECKERRORS();
      return result == 0;
    }
  }
}