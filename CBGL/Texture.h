#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace gl {
    enum class TextureFormat {
      R8 = 0x8229,
      R16 = 0x822A,
      RG8 = 0x822B,
      RG16 = 0x822C,
      R16F = 0x822D,
      R32F = 0x822E,
      RG16F = 0x822F,
      RG32F = 0x8230,
      R8I = 0x8231,
      R8UI = 0x8232,
      R16I = 0x8233,
      R16UI = 0x8234,
      R32I = 0x8235,
      R32UI = 0x8236,
      RG8I = 0x8237,
      RG8UI = 0x8238,
      RG16I = 0x8239,
      RG16UI = 0x823A,
      RG32I = 0x823B,
      RG32UI = 0x823C,
      RGB4 = 0x804F,
      RGB5 = 0x8050,
      RGB8 = 0x8051,
      RGB10 = 0x8052,
      RGB12 = 0x8053,
      RGB16 = 0x8054,
      RGBA2 = 0x8055,
      RGBA4 = 0x8056,
      RGB5_A1 = 0x8057,
      RGBA8 = 0x8058,
      RGB10_A2 = 0x8059,
      RGBA12 = 0x805A,
      RGBA16 = 0x805B,
      DEPTH_COMPONENT16 = 0x81A5,
      DEPTH_COMPONENT24 = 0x81A6,
      DEPTH_COMPONENT32 = 0x81A7,
      DEPTH_COMPONENT32F = 0x8CAC,
      DEPTH32F_STENCIL8 = 0x8CAD,
      DEPTH24_STENCIL8 = 0x88F0,
    };

    enum class InputFormat {
      RED = 0x1903,
      RG = 0x8227,
      RGB = 0x1907,
      RGBA = 0x1908,
      BGR = 0x80E0,
      BGRA = 0x80E1,
    };

    enum class TextureFilter {
      NEAREST = 0x2600,
      LINEAR = 0x2601,
    };

    enum class TextureWrap {
      CLAMP = 0x2900,
      REPEAT = 0x2901,
      CLAMP_TO_EDGE = 0x812F,
      CLAMP_TO_BORDER = 0x812D,
      MIRRORED_REPEAT = 0x8370,
    };

    class CTexture {
    private:
      OGLObjId mId;
      glm::uvec2 mSize;

    public:
      CTexture(glm::uvec2 const& size, TextureFormat const format);
      CTexture(CTexture const&) = delete;
      CTexture(CTexture && other);
      ~CTexture();

      void operator=(CTexture const&) = delete;
      void operator=(CTexture && other);

      template<typename _Type>
      void SetData(InputFormat const inputFormat, std::vector<_Type> const& data) {
        SetDataPriv(inputFormat, getDataType<_Type>(), reinterpret_cast<void const*>(data.data()));
      }
      template<typename _Type, size_t _TypeSize>
      void SetData(InputFormat const inputFormat, std::array<_Type, _TypeSize> const& data) {
        SetDataPriv(inputFormat, getDataType<_Type>(), reinterpret_cast<void const*>(data.data()));
      }
      template<typename _Type>
      void SetData(InputFormat const inputFormat, std::initializer_list<_Type> const& data) {
        auto vecdata = std::vector<_Type>(data);
        SetData(inputFormat, vecdata);
      }

      void SetFilter(TextureFilter const minFilter,
                     TextureFilter const magFilter,
                     TextureFilter const mipmapFilter);
      void SetWrap(TextureWrap const wrapS, TextureWrap wrapT);

      void Bind(unsigned const unit = 0) const;
      void UnBind(unsigned const unit = 0) const;

    private:
      void SetDataPriv(InputFormat const inputFormat, DataType const inputType, void const* pData);
      void SetParamPriv(unsigned param, unsigned value);
      static unsigned GetMinFilter(TextureFilter const minFilter, TextureFilter const mipFilter);
    };
  }
}
