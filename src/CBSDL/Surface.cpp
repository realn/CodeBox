#include "stdafx.h"
#include <CBSDL/Surface.h>
#include <CBSDL/RWObj.h>

#include <SDL_surface.h>
#include <SDL_image.h>

inline SDL_RWops* Get(cb::sdl::CRWObj& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.Get());
}

inline SDL_RWops* Get(cb::sdl::CRWObj const& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.Get());
}

inline SDL_Surface* Get(cb::sdl::CSurface& surface) {
  return reinterpret_cast<SDL_Surface*>(surface.Get());
}

inline SDL_Surface* Get(cb::sdl::CSurface const& surface) {
  return reinterpret_cast<SDL_Surface*>(surface.Get());
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
        SDL_FreeSurface(::Get(*this));
        mSurface = nullptr;
      }
    }

    void CSurface::operator=(CSurface && other) {
      std::swap(mSurface, other.mSurface);
    }

    void CSurface::SetPixels(std::vector<cb::byte> const & data) {
      if(data.size() != ::Get(*this)->w * ::Get(*this)->h * ::Get(*this)->format->BytesPerPixel) {
        throw std::exception("Invalid data size to set to sdl surface.");
      }

      SDL_LockSurface(::Get(*this));
      auto pData = reinterpret_cast<cb::byte*>(::Get(*this)->pixels);
      std::memcpy(::Get(*this)->pixels, data.data(), data.size());
      SDL_UnlockSurface(::Get(*this));
    }

    glm::uvec2 CSurface::GetSize() const {
      return glm::uvec2(static_cast<unsigned>(::Get(*this)->w),
                        static_cast<unsigned>(::Get(*this)->h));
    }

    unsigned CSurface::GetDepth() const {
      return ::Get(*this)->format->BitsPerPixel;
    }

    PixelFormat CSurface::GetFormat() const {
      return static_cast<PixelFormat>(::Get(*this)->format->format);
    }

    cb::bytevector CSurface::GetPixels() const {
      auto len = ::Get(*this)->w * ::Get(*this)->h * ::Get(*this)->format->BytesPerPixel;
      auto result = cb::bytevector(len);
      SDL_LockSurface(::Get(*this));
      std::memcpy(result.data(), ::Get(*this)->pixels, len);
      SDL_UnlockSurface(::Get(*this));
      return result;
    }

    CSurface CSurface::Copy() const {
      SDL_LockSurface(::Get(*this));
      CB_SDL_CHECKERRORS();
      auto surface =
        SDL_CreateRGBSurfaceWithFormatFrom(::Get(*this)->pixels,
                                           ::Get(*this)->w,
                                           ::Get(*this)->h,
                                           ::Get(*this)->format->BitsPerPixel,
                                           ::Get(*this)->pitch,
                                           ::Get(*this)->format->format);
      SDL_UnlockSurface(::Get(*this));
      CB_SDL_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface CSurface::Convert(PixelFormat const format) const {
      auto surface = SDL_ConvertSurfaceFormat(::Get(*this), static_cast<Uint32>(format), 0);
      CB_SDL_CHECKERRORS();
      return CSurface(surface);
    }

    void CSurface::Paste(glm::uvec2 const & dstPos, CSurface const & source) {
      auto dstRect = toSdlRect(dstPos, glm::uvec2());
      SDL_BlitSurface(::Get(source), nullptr, ::Get(*this), &dstRect);
      CB_SDL_CHECKERRORS();
    }

    void CSurface::Paste(glm::uvec2 const & dstPos, CSurface const & source, 
                         glm::uvec2 const & srcPos, glm::uvec2 const & srcSize) {
      auto dstRect = toSdlRect(dstPos, glm::uvec2());
      auto srcRect = toSdlRect(srcPos, srcSize);
      SDL_BlitSurface(::Get(source), &srcRect, ::Get(*this), &dstRect);
      CB_SDL_CHECKERRORS();
    }

    void CSurface::PasteScaled(glm::uvec2 const & dstPos, glm::uvec2 const & dstSize, 
                               CSurface const & source) {
      auto dstRect = toSdlRect(dstPos, dstSize);
      SDL_BlitScaled(::Get(source), nullptr, ::Get(*this), &dstRect);
      CB_SDL_CHECKERRORS();
    }

    void CSurface::PasteScaled(glm::uvec2 const & dstPos, glm::uvec2 const & dstSize, 
                               CSurface const & source, 
                               glm::uvec2 const & srcPos, glm::uvec2 const & srcSize) {
      auto dstRect = toSdlRect(dstPos, dstSize);
      auto srcRect = toSdlRect(srcPos, srcSize);
      SDL_BlitScaled(::Get(source), &srcRect, ::Get(*this), &dstRect);
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

    void CSurface::Fill(glm::vec4 const & color) {
      Fill(glm::u8vec4(color * 255.0f));
    }

    void CSurface::Fill(glm::u8vec4 const & color) {
      auto surf = ::Get(*this);
      auto col = SDL_MapRGBA(surf->format, color.r, color.g, color.b, color.a);
      SDL_FillRect(surf, nullptr, col);
      CB_SDL_CHECKERRORS();
    }

    void CSurface::Fill(glm::vec4 const & color, glm::uvec2 const & pos, glm::uvec2 const & size) {
      Fill(glm::u8vec4(color * 255.0f), pos, size);
    }

    void CSurface::Fill(glm::u8vec4 const & color, glm::uvec2 const & pos, glm::uvec2 const & size) {
      auto surf = ::Get(*this);
      auto col = SDL_MapRGBA(surf->format, color.r, color.g, color.b, color.a);
      auto rect = SDL_Rect{
        static_cast<int>(pos.x), static_cast<int>(pos.y),
        static_cast<int>(size.x), static_cast<int>(size.y)
      };
      SDL_FillRect(surf, &rect, col);
      CB_SDL_CHECKERRORS();
    }

    void CSurface::FlipHorizontal() {
      SDL_LockSurface(::Get(*this));
      auto pData = reinterpret_cast<cb::byte*>(::Get(*this)->pixels);
      auto size = GetSize();
      auto hwidth = size.x / 2;
      auto pitch = unsigned(::Get(*this)->pitch);
      auto bytes = unsigned(::Get(*this)->format->BytesPerPixel);
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
      SDL_UnlockSurface(::Get(*this));
    }

    void CSurface::FlipVertical() {
      SDL_LockSurface(::Get(*this));
      auto pData = reinterpret_cast<cb::byte*>(::Get(*this)->pixels);
      auto size = GetSize();
      auto pitch = unsigned(::Get(*this)->pitch);
      auto bytes = unsigned(::Get(*this)->format->BytesPerPixel);
      for(auto y = 0u; y < size.y/2; y++) {
        auto lineidx1 = y * pitch;
        auto lineidx2 = (size.y - 1 - y) * pitch;
        for(auto x = 0u; x < pitch; x ++) {
          std::swap(pData[lineidx1 + x], pData[lineidx2 + x]);
        }
      }
      SDL_UnlockSurface(::Get(*this));
    }

    CSurface CSurface::LoadBMP(cb::string const & filepath) {
      auto file = CRWObj::FromFile(filepath, FileMode::Read);
      return LoadBMP(file);
    }

    CSurface CSurface::LoadBMP(CRWObj & rwObj) {
      auto surface = SDL_LoadBMP_RW(::Get(rwObj), 0);
      CB_SDL_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface CSurface::LoadPNG(cb::string const & filepath) {
      auto file = CRWObj::FromFile(filepath, FileMode::Read);
      return LoadPNG(file);
    }

    CSurface CSurface::LoadPNG(CRWObj & rwObj) {
      auto surface = IMG_LoadPNG_RW(::Get(rwObj));
      CB_IMG_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface CSurface::LoadTGA(cb::string const & filepath) {
      auto file = CRWObj::FromFile(filepath, FileMode::Read);
      return LoadTGA(file);
    }

    CSurface CSurface::LoadTGA(CRWObj & rwObj) {
      auto surface = IMG_LoadTGA_RW(::Get(rwObj));
      CB_IMG_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface CSurface::LoadJPG(cb::string const & filepath) {
      auto file = CRWObj::FromFile(filepath, FileMode::Read);
      return LoadJPG(file);
    }

    CSurface CSurface::LoadJPG(CRWObj & rwObj) {
      auto surface = IMG_LoadJPG_RW(::Get(rwObj));
      CB_IMG_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface CSurface::Load(cb::string const & filepath) {
      auto file = CRWObj::FromFile(filepath, FileMode::Read);
      return Load(file);
    }

    CSurface CSurface::Load(CRWObj & rwObj) {
      auto surface = IMG_Load_RW(::Get(rwObj), 0);
      CB_IMG_CHECKERRORS();
      return CSurface(surface);
    }
  }
}