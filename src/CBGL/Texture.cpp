#include "stdafx.h"
#include <CBGL/Texture.h>

namespace cb {
  namespace gl {
    namespace {
      unsigned getMinFilter(TextureFilter const minFilter, TextureFilter const mipFilter) {
        if (minFilter == TextureFilter::NEAREST) {
          if (mipFilter == TextureFilter::NEAREST) {
            return GL_NEAREST_MIPMAP_NEAREST;
          }
          else {
            return GL_NEAREST_MIPMAP_LINEAR;
          }
        }
        else {
          if (mipFilter == TextureFilter::NEAREST) {
            return GL_LINEAR_MIPMAP_NEAREST;
          }
          else {
            return GL_LINEAR_MIPMAP_LINEAR;
          }
        }
      }
    }

    CTexture::CTexture(glm::uvec2 const & size, TextureFormat const format) 
      : mId(0) 
      , mSize(size)
    {
      glGenTextures(1, &mId);

      glBindTexture(GL_TEXTURE_2D, mId);
      glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), mSize.x, mSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
      CB_GL_CHECKERRORS();
      glBindTexture(GL_TEXTURE_2D, 0);

      setFilter(TextureFilter::LINEAR, TextureFilter::LINEAR, TextureFilter::LINEAR);
      setWrap(TextureWrap::CLAMP_TO_EDGE, TextureWrap::CLAMP_TO_EDGE);
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

    void CTexture::setFilter(TextureFilter const minFilter, 
                             TextureFilter const magFilter, 
                             TextureFilter const mipmapFilter) {
      auto gtex = gl::bind(*this);
      setParamPriv(GL_TEXTURE_MIN_FILTER, getMinFilter(minFilter, mipmapFilter));
      setParamPriv(GL_TEXTURE_MAG_FILTER, static_cast<unsigned>(magFilter));
    }

    void CTexture::setWrap(TextureWrap const wrapS, TextureWrap wrapT) {
      auto gtex = gl::bind(*this);
      setParamPriv(GL_TEXTURE_WRAP_S, static_cast<unsigned>(wrapS));
      setParamPriv(GL_TEXTURE_WRAP_T, static_cast<unsigned>(wrapT));
    }

    void CTexture::bind(unsigned const unit) const {
      glActiveTexture(GL_TEXTURE0 + unit);
      CB_GL_CHECKERRORS();
      glEnable(GL_TEXTURE_2D);
      CB_GL_CHECKERRORS();
      glBindTexture(GL_TEXTURE_2D, mId);
      CB_GL_CHECKERRORS();
    }

    void CTexture::unBind(unsigned const unit) const {
      glActiveTexture(GL_TEXTURE0 + unit);
      CB_GL_CHECKERRORS();
      glBindTexture(GL_TEXTURE_2D, 0);
      CB_GL_CHECKERRORS();
      glDisable(GL_TEXTURE_2D);
      CB_GL_CHECKERRORS();
      glActiveTexture(GL_TEXTURE0);
    }

    void CTexture::setDataRaw(InputFormat const inputFormat, DataType const inputType, void const * pData) {
      auto gtex = gl::bind(*this);
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mSize.x, mSize.y, static_cast<GLenum>(inputFormat), static_cast<GLenum>(inputType), pData);
      CB_GL_CHECKERRORS();
      glGenerateMipmap(GL_TEXTURE_2D);
      CB_GL_CHECKERRORS();
    }

    void CTexture::setParamPriv(unsigned param, unsigned value) {
      glTexParameteri(GL_TEXTURE_2D, param, value);
      CB_GL_CHECKERRORS();
    }
  }
}