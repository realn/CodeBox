#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace sdl {
    enum class FlipDir {
      Horizontal,
      Vertical,
    };

    class RWObj;

    class Surface {
      void* mSurface;

    public:
      Surface(glm::uvec2 const size, unsigned const depth, PixelFormat const format);
      explicit Surface(void* surface) : mSurface(surface) {}
      Surface(Surface const&) = delete;
      Surface(Surface && other);
      ~Surface();

      void operator=(Surface const&) = delete;
      void operator=(Surface && other);

      void setPixels(std::vector<cb::byte> const& data);

      glm::uvec2 getSize() const;
      unsigned getDepth() const;
      PixelFormat getFormat() const;
      cb::bytevector getPixels() const;

      void* get() const { return mSurface; }

      Surface copy() const;
      Surface convert(PixelFormat const format) const;

      void paste(glm::uvec2 const& dstPos, 
                 Surface const& source);
      void paste(glm::uvec2 const& dstPos, 
                 Surface const& source, 
                 glm::uvec2 const& srcPos,
                 glm::uvec2 const& srcSize);
      void pasteScaled(glm::uvec2 const& dstPos, 
                       glm::uvec2 const& dstSize, 
                       Surface const& source);
      void pasteScaled(glm::uvec2 const& dstPos,
                       glm::uvec2 const& dstSize,
                       Surface const& source,
                       glm::uvec2 const& srcPos,
                       glm::uvec2 const& srcSize);
      void flip(FlipDir const dir);

      void fill(glm::vec4 const& color);
      void fill(glm::u8vec4 const& color);
      void fill(glm::vec4 const& color, glm::uvec2 const& pos, glm::uvec2 const& size);
      void fill(glm::u8vec4 const& color, glm::uvec2 const& pos, glm::uvec2 const& size);

      static Surface loadBMP(cb::string const& filepath);
      static Surface loadBMP(RWObj& rwObj);
      static Surface loadPNG(cb::string const& filepath);
      static Surface loadPNG(RWObj& rwObj);
      static Surface loadTGA(cb::string const& filepath);
      static Surface loadTGA(RWObj& rwObj);
      static Surface loadJPG(cb::string const& filepath);
      static Surface loadJPG(RWObj& rwObj);

      static Surface load(cb::string const& filepath);
      static Surface load(RWObj& rwObj);

      bool saveBMP(cb::string const& filepath) const;
      bool saveBMP(RWObj& rwObj) const;
      bool savePNG(cb::string const& filepath) const;
      bool savePNG(RWObj& rwObj) const;

    private:
      void flipHorizontal();
      void flipVertical();
    };

  }
}