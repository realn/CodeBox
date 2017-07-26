#include "stdafx.h"
#include "../Surface.h"

#include <SDL_surface.h>

namespace cb {
  namespace sdl {
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

    CSurface CSurface::Convert(PixelFormat const format) const {
      auto surface = SDL_ConvertSurfaceFormat(mSurface, static_cast<Uint32>(format), 0);
      CB_SDL_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface loadBMP(cb::string const & filepath) {
      auto szFilepath = cb::toUtf8(filepath, true);
      auto file = SDL_RWFromFile(szFilepath.data(), "rb");
      CB_SDL_CHECKERRORS();
      auto surface = SDL_LoadBMP_RW(file, 1);
      CB_SDL_CHECKERRORS();
      return CSurface(surface);
    }
  }
}