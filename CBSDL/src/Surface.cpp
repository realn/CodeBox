#include "stdafx.h"
#include "../Surface.h"
#include "../RWObj.h"

#include <SDL_surface.h>

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

    CSurface::CSurface(glm::uvec2 const size, unsigned const depth, PixelFormat const format)
      : mSurface(nullptr) {
      mSurface = SDL_CreateRGBSurfaceWithFormat(0, size.x, size.y, depth,
                                                static_cast<unsigned>(format));
      CB_SDL_CHECKERRORS();
    }

    CSurface::CSurface(CSurface && other) : mSurface(nullptr) {
      std::swap(mSurface, other.mSurface);
    }

    CSurface::~CSurface() {
      if(mSurface) {
        SDL_FreeSurface(mSurface);
        mSurface = nullptr;
      }
    }

    void CSurface::operator=(CSurface && other) {
      std::swap(mSurface, other.mSurface);
    }

    void CSurface::SetPixels(std::vector<cb::byte> const & data) {
      if(data.size() != mSurface->w * mSurface->h * mSurface->format->BytesPerPixel) {
        throw std::exception("Invalid data size to set to sdl surface.");
      }

      SDL_LockSurface(mSurface);
      auto pData = reinterpret_cast<cb::byte*>(mSurface->pixels);
      std::memcpy(mSurface->pixels, data.data(), data.size());
      SDL_UnlockSurface(mSurface);
    }

    glm::uvec2 CSurface::GetSize() const {
      return glm::uvec2(static_cast<unsigned>(mSurface->w),
                        static_cast<unsigned>(mSurface->h));
    }

    unsigned CSurface::GetDepth() const {
      return mSurface->format->BitsPerPixel;
    }

    PixelFormat CSurface::GetFormat() const {
      return static_cast<PixelFormat>(mSurface->format->format);
    }

    cb::bytevector CSurface::GetPixels() const {
      auto len = mSurface->w * mSurface->h * mSurface->format->BytesPerPixel;
      auto result = cb::bytevector(len);
      SDL_LockSurface(mSurface);
      std::memcpy(result.data(), mSurface->pixels, len);
      SDL_UnlockSurface(mSurface);
      return result;
    }

    CSurface CSurface::Copy() const {
      SDL_LockSurface(mSurface);
      CB_SDL_CHECKERRORS();
      auto surface =
        SDL_CreateRGBSurfaceWithFormatFrom(mSurface->pixels,
                                           mSurface->w,
                                           mSurface->h,
                                           mSurface->format->BitsPerPixel,
                                           mSurface->pitch,
                                           mSurface->format->format);
      SDL_UnlockSurface(mSurface);
      CB_SDL_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface CSurface::Convert(PixelFormat const format) const {
      auto surface = SDL_ConvertSurfaceFormat(mSurface, static_cast<Uint32>(format), 0);
      CB_SDL_CHECKERRORS();
      return CSurface(surface);
    }

    void CSurface::Paste(glm::uvec2 const & dstPos, CSurface const & source) {
      auto dstRect = toSdlRect(dstPos, glm::uvec2());
      SDL_BlitSurface(source.Get(), nullptr, mSurface, &dstRect);
      CB_SDL_CHECKERRORS();
    }

    void CSurface::Paste(glm::uvec2 const & dstPos, CSurface const & source, 
                         glm::uvec2 const & srcPos, glm::uvec2 const & srcSize) {
      auto dstRect = toSdlRect(dstPos, glm::uvec2());
      auto srcRect = toSdlRect(srcPos, srcSize);
      SDL_BlitSurface(source.Get(), &srcRect, mSurface, &dstRect);
      CB_SDL_CHECKERRORS();
    }

    void CSurface::PasteScaled(glm::uvec2 const & dstPos, glm::uvec2 const & dstSize, 
                               CSurface const & source) {
      auto dstRect = toSdlRect(dstPos, dstSize);
      SDL_BlitScaled(source.Get(), nullptr, mSurface, &dstRect);
      CB_SDL_CHECKERRORS();
    }

    void CSurface::PasteScaled(glm::uvec2 const & dstPos, glm::uvec2 const & dstSize, 
                               CSurface const & source, 
                               glm::uvec2 const & srcPos, glm::uvec2 const & srcSize) {
      auto dstRect = toSdlRect(dstPos, dstSize);
      auto srcRect = toSdlRect(srcPos, srcSize);
      SDL_BlitScaled(source.Get(), &srcRect, mSurface, &dstRect);
      CB_SDL_CHECKERRORS();
    }

    void CSurface::Flip(FlipDir const dir) {
      switch(dir) {
      case FlipDir::Horizontal: FlipHorizontal(); break;
      case FlipDir::Vertical:   FlipVertical(); break;
      default:
        throw std::exception("Unknown sdl surface flip direction.");
      }
    }

    void CSurface::FlipHorizontal() {
      SDL_LockSurface(mSurface);
      auto pData = reinterpret_cast<cb::byte*>(mSurface->pixels);
      auto size = GetSize();
      auto hwidth = size.x / 2;
      auto pitch = unsigned(mSurface->pitch);
      auto bytes = unsigned(mSurface->format->BytesPerPixel);
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
      SDL_UnlockSurface(mSurface);
    }

    void CSurface::FlipVertical() {
      SDL_LockSurface(mSurface);
      auto pData = reinterpret_cast<cb::byte*>(mSurface->pixels);
      auto size = GetSize();
      auto pitch = unsigned(mSurface->pitch);
      auto bytes = unsigned(mSurface->format->BytesPerPixel);
      for(auto y = 0u; y < size.y/2; y++) {
        auto lineidx1 = y * pitch;
        auto lineidx2 = (size.y - 1 - y) * pitch;
        for(auto x = 0u; x < pitch; x ++) {
          std::swap(pData[lineidx1 + x], pData[lineidx2 + x]);
        }
      }
      SDL_UnlockSurface(mSurface);
    }

    CSurface CSurface::LoadBMP(cb::string const & filepath) {
      auto file = fromFile(filepath, FileMode::Read);
      return LoadBMP(file);
    }

    CSurface CSurface::LoadBMP(CRWObj & rwObj) {
      auto surface = SDL_LoadBMP_RW(rwObj.Get(), 0);
      CB_SDL_CHECKERRORS();
      return CSurface(surface);
    }
  }
}