#pragma once

#include "Defines.h"

namespace cb {
  namespace sdl {
    class CRWObj;
    class CSurface;

    ENUM_FLAG(FontStyle) {
      NORMAL = 0x00,
        BOLD = 0x01,
        ITALIC = 0x02,
        UNDERLINE = 0x04,
        STRIKETHROUGH = 0x08,
    };

    struct CGlyph {
      glm::ivec2 min;
      glm::ivec2 max;
      int advance = 0;
    };

    class CFont {
    private:
      void* mFont;

    public:
      CFont(cb::string const& filepath, unsigned const ptSize, unsigned const fontIndex = 0);
      CFont(CRWObj& obj, unsigned const ptSize, unsigned const fontIndex = 0);
      CFont(CFont const&) = delete;
      CFont(CFont&& other);
      ~CFont();

      void operator=(CFont const&) = delete;
      void operator=(CFont&& other);

      void SetStyle(FontStyle const style);
      void SetKerning(bool enabled);

      FontStyle GetStyle() const;
      bool GetKerning() const;
      unsigned GetHeight() const;
      int GetAscent() const;
      int GetDescent() const;
      int GetLineSkip() const;
      unsigned GetNumberOfFaces() const;
      bool IsFixedWidth() const;
      cb::string GetName() const;
      cb::string GetStyleName() const;
      bool GlyphIsProvided(wchar_t const ch) const;
      CGlyph GetGlyphMetrics(wchar_t const ch) const;
      glm::uvec2 GetSize(cb::string const& text) const;

      CSurface RenderGlyphSolid(wchar_t const ch, glm::vec4 const& color) const;
      CSurface RenderGlyphShaded(wchar_t const ch, glm::vec4 const& color, glm::vec4 const& bgColor) const;
      CSurface RenderGlyphBlended(wchar_t const ch, glm::vec4 const& color) const;

      CSurface RenderSolid(cb::string const& text, glm::u8vec4 const& color) const;
      CSurface RenderShaded(cb::string const& text, glm::u8vec4 const& color, glm::vec4 const& bgColor) const;
      CSurface RenderBlended(cb::string const& text, glm::u8vec4 const& color) const;
    };
  }
}
