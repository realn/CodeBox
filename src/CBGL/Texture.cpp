#include "stdafx.h"
#include <CBGL/Texture.h>

namespace cb {
  namespace gl {
    CTexture::CTexture(glm::uvec2 const & size, TextureFormat const format) 
      : mId(0) 
      , mSize(size)
    {
      glGenTextures(1, &mId);
      glBindTexture(GL_TEXTURE_2D, mId);
      SetFilter(TextureFilter::LINEAR, TextureFilter::LINEAR, TextureFilter::LINEAR);
      SetWrap(TextureWrap::CLAMP_TO_EDGE, TextureWrap::CLAMP_TO_EDGE);
      glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), mSize.x, mSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
      CB_GL_CHECKERRORS();
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    CTexture::CTexture(CTexture && other) 
      : mId(0)
    {
      std::swap(mId, other.mId);
      std::swap(mSize, other.mSize);
    }

    CTexture::~CTexture() {
      if(mId) {
        glDeleteTextures(1, &mId);
        mId = 0;
      }
    }

    void CTexture::operator=(CTexture && other) {
      std::swap(mId, other.mId);
      std::swap(mSize, other.mSize);
    }

    void CTexture::SetFilter(TextureFilter const minFilter, 
                             TextureFilter const magFilter, 
                             TextureFilter const mipmapFilter) {
      SetParamPriv(GL_TEXTURE_MIN_FILTER, GetMinFilter(minFilter, mipmapFilter));
      SetParamPriv(GL_TEXTURE_MAG_FILTER, static_cast<unsigned>(magFilter));
    }

    void CTexture::SetWrap(TextureWrap const wrapS, TextureWrap wrapT) {
      SetParamPriv(GL_TEXTURE_WRAP_S, static_cast<unsigned>(wrapS));
      SetParamPriv(GL_TEXTURE_WRAP_T, static_cast<unsigned>(wrapT));
    }

    void CTexture::Bind(unsigned const unit) const {
      glActiveTexture(GL_TEXTURE0 + unit);
      CB_GL_CHECKERRORS();
      glEnable(GL_TEXTURE_2D);
      CB_GL_CHECKERRORS();
      glBindTexture(GL_TEXTURE_2D, mId);
      CB_GL_CHECKERRORS();
    }

    void CTexture::UnBind(unsigned const unit) const {
      glActiveTexture(GL_TEXTURE0 + unit);
      CB_GL_CHECKERRORS();
      glBindTexture(GL_TEXTURE_2D, 0);
      CB_GL_CHECKERRORS();
      glDisable(GL_TEXTURE_2D);
      CB_GL_CHECKERRORS();
      glActiveTexture(GL_TEXTURE0);
    }

    void CTexture::SetDataPriv(InputFormat const inputFormat, DataType const inputType, void const * pData) {
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mSize.x, mSize.y, static_cast<GLenum>(inputFormat), static_cast<GLenum>(inputType), pData);
      CB_GL_CHECKERRORS();
      glGenerateMipmap(GL_TEXTURE_2D);
      CB_GL_CHECKERRORS();
    }

    void CTexture::SetParamPriv(unsigned param, unsigned value) {
      glTexParameteri(GL_TEXTURE_2D, param, value);
      CB_GL_CHECKERRORS();
    }

    unsigned CTexture::GetMinFilter(TextureFilter const minFilter, TextureFilter const mipFilter) {
      if(minFilter == TextureFilter::NEAREST) {
        if(mipFilter == TextureFilter::NEAREST) {
          return GL_NEAREST_MIPMAP_NEAREST;
        }
        else {
          return GL_NEAREST_MIPMAP_LINEAR;
        }
      }
      else {
        if(mipFilter == TextureFilter::NEAREST) {
          return GL_LINEAR_MIPMAP_NEAREST;
        }
        else {
          return GL_LINEAR_MIPMAP_LINEAR;
        }
      }
    }

    void setTextureUnit(unsigned unit) {
      glActiveTexture(GL_TEXTURE0 + unit);
      CB_GL_CHECKERRORS();
    }
  }
}