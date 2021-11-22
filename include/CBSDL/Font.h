#pragma once

#include <CBCore/Flags.h>

#include "Defines.h"

namespace cb {
  namespace sdl {
    class RWObj;
    class Surface;

    ENUM_FLAG(FontStyle) {
      NORMAL = 0x00,
        BOLD = 0x01,
        ITALIC = 0x02,
        UNDERLINE = 0x04,
        STRIKETHROUGH = 0x08,
    };

    struct Glyph {
      glm::ivec2 min;
      glm::ivec2 max;
      int advance = 0;
    };

    class Font {
    private:
      void* mFont;

    public:
      Font(cb::string const& filepath, unsigned const ptSize, unsigned const fontIndex = 0);
      Font(RWObj& obj, unsigned const ptSize, unsigned const fontIndex = 0);
      Font(Font const&) = delete;
      Font(Font&& other);
      ~Font();

      void operator=(Font const&) = delete;
      void operator=(Font&& other);

      void setStyle(FontStyle const style);
      void setKerning(bool enabled);

      FontStyle getStyle() const;
      bool getKerning() const;
      unsigned getHeight() const;
      int getAscent() const;
      int getDescent() const;
      int getLineSkip() const;
      unsigned getNumberOfFaces() const;
      bool isFixedWidth() const;
      cb::string getName() const;
      cb::string getStyleName() const;
      bool glyphIsProvided(wchar_t const ch) const;
      Glyph getGlyphMetrics(wchar_t const ch) const;
      glm::uvec2 getSize(cb::string const& text) const;

      Surface renderGlyphSolid(wchar_t const ch, glm::vec4 const& color) const;
      Surface renderGlyphShaded(wchar_t const ch, glm::vec4 const& color, glm::vec4 const& bgColor) const;
      Surface renderGlyphBlended(wchar_t const ch, glm::vec4 const& color) const;

      Surface renderSolid(cb::string const& text, glm::u8vec4 const& color) const;
      Surface renderShaded(cb::string const& text, glm::u8vec4 const& color, glm::vec4 const& bgColor) const;
      Surface renderBlended(cb::string const& text, glm::u8vec4 const& color) const;
    };
  }
}
