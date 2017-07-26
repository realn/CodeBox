#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    enum class FlipDir {
      Horizontal,
      Vertical,
    };

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

      SDL_Surface* Get() const { return mSurface; }

      CSurface Copy() const;
      CSurface Convert(PixelFormat const format) const;

      void Paste(glm::uvec2 const& dstPos, 
                 CSurface const& source);
      void Paste(glm::uvec2 const& dstPos, 
                 CSurface const& source, 
                 glm::uvec2 const& srcPos,
                 glm::uvec2 const& srcSize);
      void PasteScaled(glm::uvec2 const& dstPos, 
                       glm::uvec2 const& dstSize, 
                       CSurface const& source);
      void PasteScaled(glm::uvec2 const& dstPos,
                       glm::uvec2 const& dstSize,
                       CSurface const& source,
                       glm::uvec2 const& srcPos,
                       glm::uvec2 const& srcSize);
      void Flip(FlipDir const dir);

    private:
      void FlipHorizontal();
      void FlipVertical();
    };

    extern CSurface loadBMP(cb::string const& filepath);
  }
}