#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    class CSurface {
      SDL_Surface* mSurface;

    public:
      CSurface(glm::uvec2 const size, unsigned const depth, PixelFormat const format);
      explicit CSurface(SDL_Surface* surface) : mSurface(surface) {}
      CSurface(CSurface const&) = delete;
      CSurface(CSurface && other);
      ~CSurface();

      void operator=(CSurface const&) = delete;
      void operator=(CSurface && other);

      void SetPixels(std::vector<cb::byte> const& data);

      glm::uvec2 GetSize() const;
      unsigned GetDepth() const;
      PixelFormat GetFormat() const;
      cb::bytevector GetPixels() const;

      CSurface Convert(PixelFormat const format) const;
    };

    extern CSurface loadBMP(cb::string const& filepath);
  }
}