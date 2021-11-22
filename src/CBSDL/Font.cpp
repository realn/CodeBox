#include "stdafx.h"
#include <CBSDL/Font.h>
#include <CBSDL/RWObj.h>
#include <CBSDL/Surface.h>
#include <CBCore/StringConvert.h>

#include <SDL_ttf.h>

inline SDL_RWops* get(cb::sdl::RWObj& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.get());
}

inline SDL_RWops* get(cb::sdl::RWObj const& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.get());
}


namespace cb {
  namespace sdl {
    namespace {
      inline TTF_Font* getFont(void* font) {
        return static_cast<TTF_Font*>(font);
      }
      inline TTF_Font const* getFont(void const * font) {
        return static_cast<TTF_Font const*>(font);
      }
      inline SDL_Color toColor(glm::vec4 const& color) {
        return {
          static_cast<Uint8>(color.r * 255.0f),
          static_cast<Uint8>(color.g * 255.0f),
          static_cast<Uint8>(color.b * 255.0f),
          static_cast<Uint8>(color.a * 255.0f),
        };
      }
    }

    Font::Font(cb::string const & filepath, unsigned const ptSize, unsigned const fontIndex) 
      : mFont(nullptr)
    {
      auto szFilepath = toUtf8(filepath);
      mFont = TTF_OpenFontIndex(szFilepath.data(), static_cast<int>(ptSize), static_cast<long>(fontIndex));
      CB_TTF_CHECKERRORS();
    }

    Font::Font(RWObj & obj, unsigned const ptSize, unsigned const fontIndex)
      : mFont(nullptr)
    {
      mFont = TTF_OpenFontIndexRW(::get(obj), 0, static_cast<int>(ptSize), static_cast<long>(fontIndex));
      CB_TTF_CHECKERRORS();
    }

    Font::Font(Font && other) :
      mFont(nullptr)
    {
      std::swap(mFont, other.mFont);
    }

    Font::~Font() {
      if(mFont) {
        TTF_CloseFont(static_cast<TTF_Font*>(mFont));
        mFont = nullptr;
      }
    }

    void Font::operator=(Font && other) {
      std::swap(mFont, other.mFont);
    }

    void Font::setStyle(FontStyle const style) {
      TTF_SetFontStyle(getFont(mFont), static_cast<int>(style));
      CB_TTF_CHECKERRORS();
    }

    void Font::setKerning(bool enabled) {
      TTF_SetFontKerning(getFont(mFont), enabled ? 1 : 0);
      CB_TTF_CHECKERRORS();
    }

    FontStyle Font::getStyle() const {
      auto res = TTF_GetFontStyle(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return static_cast<FontStyle>(res);
    }

    bool Font::getKerning() const {
      auto res = TTF_GetFontKerning(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return res != 0;
    }

    unsigned Font::getHeight() const {
      auto res = TTF_FontHeight(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return static_cast<unsigned>(res);
    }

    int Font::getAscent() const {
      auto res = TTF_FontAscent(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return res;
    }

    int Font::getDescent() const {
      auto res = TTF_FontDescent(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return res;
    }

    int Font::getLineSkip() const {
      auto res = TTF_FontLineSkip(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return res;
    }

    unsigned Font::getNumberOfFaces() const {
      auto res = TTF_FontFaces(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return static_cast<long>(res);
    }

    bool Font::isFixedWidth() const {
      auto res = TTF_FontFaceIsFixedWidth(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return res != 0;
    }

    cb::string Font::getName() const {
      auto fontName = TTF_FontFaceFamilyName(getFont(mFont));
      CB_TTF_CHECKERRORS();
      auto szFontName = utf8string(fontName);
      return fromUtf8(szFontName);
    }

    cb::string Font::getStyleName() const {
      auto styleName = TTF_FontFaceStyleName(getFont(mFont));
      CB_TTF_CHECKERRORS();
      auto szStyleName = utf8string(styleName);
      return fromUtf8(szStyleName);
    }

    bool Font::glyphIsProvided(wchar_t const ch) const {
      auto res = TTF_GlyphIsProvided(getFont(mFont), static_cast<Uint16>(ch));
      CB_TTF_CHECKERRORS();
      return res != 0;
    }

    Glyph Font::getGlyphMetrics(wchar_t const ch) const {
      auto res = Glyph();
      TTF_GlyphMetrics(getFont(mFont), static_cast<Uint16>(ch),
                       &res.min.x, &res.max.x, &res.min.y, &res.max.y, &res.advance);
      CB_TTF_CHECKERRORS();
      return res;
    }

    glm::uvec2 Font::getSize(cb::string const & text) const {
      int x, y;
      TTF_SizeUNICODE(getFont(mFont), 
                      reinterpret_cast<const Uint16*>(text.c_str()), &x, &y);
      CB_TTF_CHECKERRORS();
      return glm::uvec2(static_cast<unsigned>(x), static_cast<unsigned>(y));
    }

    Surface Font::renderGlyphSolid(wchar_t const ch, glm::vec4 const & color) const {
      auto surface = TTF_RenderGlyph_Solid(getFont(mFont), static_cast<Uint16>(ch),
                                           toColor(color));
      CB_TTF_CHECKERRORS();
      return Surface(surface);
    }

    Surface Font::renderGlyphShaded(wchar_t const ch, glm::vec4 const & color, glm::vec4 const & bgColor) const {
      auto surface = TTF_RenderGlyph_Shaded(getFont(mFont), static_cast<Uint16>(ch),
                                           toColor(color), toColor(bgColor));
      CB_TTF_CHECKERRORS();
      return Surface(surface);
    }

    Surface Font::renderGlyphBlended(wchar_t const ch, glm::vec4 const & color) const {
      auto surface = TTF_RenderGlyph_Blended(getFont(mFont), static_cast<Uint16>(ch),
                                           toColor(color));
      CB_TTF_CHECKERRORS();
      return Surface(surface);
    }

    Surface Font::renderSolid(cb::string const & text, glm::u8vec4 const & color) const {
      auto surface = TTF_RenderUNICODE_Solid(getFont(mFont), 
                                             reinterpret_cast<const Uint16*>(text.c_str()), 
                                             toColor(color));
      CB_TTF_CHECKERRORS();
      return Surface(surface);
    }

    Surface Font::renderShaded(cb::string const & text, glm::u8vec4 const & color, glm::vec4 const & bgColor) const {
      auto surface = TTF_RenderUNICODE_Shaded(getFont(mFont),
                                             reinterpret_cast<const Uint16*>(text.c_str()),
                                             toColor(color), toColor(bgColor));
      CB_TTF_CHECKERRORS();
      return Surface(surface);
    }

    Surface Font::renderBlended(cb::string const & text, glm::u8vec4 const & color) const {
      auto surface = TTF_RenderUNICODE_Blended(getFont(mFont),
                                             reinterpret_cast<const Uint16*>(text.c_str()),
                                             toColor(color));
      CB_TTF_CHECKERRORS();
      return Surface(surface);
    }

  }
}