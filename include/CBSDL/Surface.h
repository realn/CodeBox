#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    enum class FlipDir {
      Horizontal,
      Vertical,
    };

    class CRWObj;

    class CSurface {
      void* mSurface;

    public:
      CSurface(glm::uvec2 const size, unsigned const depth, PixelFormat const format);
      explicit CSurface(void* surface) : mSurface(surface) {}
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

      void* Get() const { return mSurface; }

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

      void Fill(glm::vec4 const& color);
      void Fill(glm::u8vec4 const& color);
      void Fill(glm::vec4 const& color, glm::uvec2 const& pos, glm::uvec2 const& size);
      void Fill(glm::u8vec4 const& color, glm::uvec2 const& pos, glm::uvec2 const& size);

      static CSurface LoadBMP(cb::string const& filepath);
      static CSurface LoadBMP(CRWObj& rwObj);
      static CSurface LoadPNG(cb::string const& filepath);
      static CSurface LoadPNG(CRWObj& rwObj);
      static CSurface LoadTGA(cb::string const& filepath);
      static CSurface LoadTGA(CRWObj& rwObj);
      static CSurface LoadJPG(cb::string const& filepath);
      static CSurface LoadJPG(CRWObj& rwObj);

      static CSurface Load(cb::string const& filepath);
      static CSurface Load(CRWObj& rwObj);

      bool SaveBMP(cb::string const& filepath) const;
      bool SaveBMP(CRWObj& rwObj) const;
      bool SavePNG(cb::string const& filepath) const;
      bool SavePNG(CRWObj& rwObj) const;

    private:
      void FlipHorizontal();
      void FlipVertical();
    };

  }
}