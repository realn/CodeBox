#include "stdafx.h"
#include <CBSDL/Font.h>
#include <CBSDL/RWObj.h>
#include <CBSDL/Surface.h>
#include <CBCore/StringConvert.h>

#include <SDL_ttf.h>

inline SDL_RWops* Get(cb::sdl::CRWObj& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.Get());
}

inline SDL_RWops* Get(cb::sdl::CRWObj const& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.Get());
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

    CFont::CFont(cb::string const & filepath, unsigned const ptSize, unsigned const fontIndex) 
      : mFont(nullptr)
    {
      auto szFilepath = toUtf8(filepath);
      mFont = TTF_OpenFontIndex(szFilepath.data(), static_cast<int>(ptSize), static_cast<long>(fontIndex));
      CB_TTF_CHECKERRORS();
    }

    CFont::CFont(CRWObj & obj, unsigned const ptSize, unsigned const fontIndex)
      : mFont(nullptr)
    {
      mFont = TTF_OpenFontIndexRW(::Get(obj), 0, static_cast<int>(ptSize), static_cast<long>(fontIndex));
      CB_TTF_CHECKERRORS();
    }

    CFont::CFont(CFont && other) :
      mFont(nullptr)
    {
      std::swap(mFont, other.mFont);
    }

    CFont::~CFont() {
      if(mFont) {
        TTF_CloseFont(static_cast<TTF_Font*>(mFont));
        mFont = nullptr;
      }
    }

    void CFont::operator=(CFont && other) {
      std::swap(mFont, other.mFont);
    }

    void CFont::SetStyle(FontStyle const style) {
      TTF_SetFontStyle(getFont(mFont), static_cast<int>(style));
      CB_TTF_CHECKERRORS();
    }

    void CFont::SetKerning(bool enabled) {
      TTF_SetFontKerning(getFont(mFont), enabled ? 1 : 0);
      CB_TTF_CHECKERRORS();
    }

    FontStyle CFont::GetStyle() const {
      auto res = TTF_GetFontStyle(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return static_cast<FontStyle>(res);
    }

    bool CFont::GetKerning() const {
      auto res = TTF_GetFontKerning(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return res != 0;
    }

    unsigned CFont::GetHeight() const {
      auto res = TTF_FontHeight(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return static_cast<unsigned>(res);
    }

    int CFont::GetAscent() const {
      auto res = TTF_FontAscent(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return res;
    }

    int CFont::GetDescent() const {
      auto res = TTF_FontDescent(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return res;
    }

    int CFont::GetLineSkip() const {
      auto res = TTF_FontLineSkip(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return res;
    }

    unsigned CFont::GetNumberOfFaces() const {
      auto res = TTF_FontFaces(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return static_cast<long>(res);
    }

    bool CFont::IsFixedWidth() const {
      auto res = TTF_FontFaceIsFixedWidth(getFont(mFont));
      CB_TTF_CHECKERRORS();
      return res != 0;
    }

    cb::string CFont::GetName() const {
      auto fontName = TTF_FontFaceFamilyName(getFont(mFont));
      CB_TTF_CHECKERRORS();
      auto szFontName = utf8string(fontName);
      return fromUtf8(szFontName);
    }

    cb::string CFont::GetStyleName() const {
      auto styleName = TTF_FontFaceStyleName(getFont(mFont));
      CB_TTF_CHECKERRORS();
      auto szStyleName = utf8string(styleName);
      return fromUtf8(szStyleName);
    }

    bool CFont::GlyphIsProvided(wchar_t const ch) const {
      auto res = TTF_GlyphIsProvided(getFont(mFont), static_cast<Uint16>(ch));
      CB_TTF_CHECKERRORS();
      return res != 0;
    }

    CGlyph CFont::GetGlyphMetrics(wchar_t const ch) const {
      auto res = CGlyph();
      TTF_GlyphMetrics(getFont(mFont), static_cast<Uint16>(ch),
                       &res.min.x, &res.max.x, &res.min.y, &res.max.y, &res.advance);
      CB_TTF_CHECKERRORS();
      return res;
    }

    glm::uvec2 CFont::GetSize(cb::string const & text) const {
      int x, y;
      TTF_SizeUNICODE(getFont(mFont), 
                      reinterpret_cast<const Uint16*>(text.c_str()), &x, &y);
      CB_TTF_CHECKERRORS();
      return glm::uvec2(static_cast<unsigned>(x), static_cast<unsigned>(y));
    }

    CSurface CFont::RenderGlyphSolid(wchar_t const ch, glm::vec4 const & color) const {
      auto surface = TTF_RenderGlyph_Solid(getFont(mFont), static_cast<Uint16>(ch),
                                           toColor(color));
      CB_TTF_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface CFont::RenderGlyphShaded(wchar_t const ch, glm::vec4 const & color, glm::vec4 const & bgColor) const {
      auto surface = TTF_RenderGlyph_Shaded(getFont(mFont), static_cast<Uint16>(ch),
                                           toColor(color), toColor(bgColor));
      CB_TTF_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface CFont::RenderGlyphBlended(wchar_t const ch, glm::vec4 const & color) const {
      auto surface = TTF_RenderGlyph_Blended(getFont(mFont), static_cast<Uint16>(ch),
                                           toColor(color));
      CB_TTF_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface CFont::RenderSolid(cb::string const & text, glm::u8vec4 const & color) const {
      auto surface = TTF_RenderUNICODE_Solid(getFont(mFont), 
                                             reinterpret_cast<const Uint16*>(text.c_str()), 
                                             toColor(color));
      CB_TTF_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface CFont::RenderShaded(cb::string const & text, glm::u8vec4 const & color, glm::vec4 const & bgColor) const {
      auto surface = TTF_RenderUNICODE_Shaded(getFont(mFont),
                                             reinterpret_cast<const Uint16*>(text.c_str()),
                                             toColor(color), toColor(bgColor));
      CB_TTF_CHECKERRORS();
      return CSurface(surface);
    }

    CSurface CFont::RenderBlended(cb::string const & text, glm::u8vec4 const & color) const {
      auto surface = TTF_RenderUNICODE_Blended(getFont(mFont),
                                             reinterpret_cast<const Uint16*>(text.c_str()),
                                             toColor(color));
      CB_TTF_CHECKERRORS();
      return CSurface(surface);
    }

  }
}