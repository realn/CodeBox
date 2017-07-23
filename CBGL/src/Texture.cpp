#include "stdafx.h"
#include "../Texture.h"

namespace cb {
  namespace gl {
    CTexture::CTexture(glm::uvec2 const & size, TextureFormat const format) 
      : mId(0) 
      , mSize(size)
    {
      glGenTextures(1, &mId);
      glBindTexture(GL_TEXTURE_2D, mId);
      glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), mSize.x, mSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
      CB_GL_CHECKERRORS();
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

    void CTexture::Bind() const {
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, mId);
      CB_GL_CHECKERRORS();
    }

    void CTexture::UnBind() {
      glBindTexture(GL_TEXTURE_2D, 0);
      CB_GL_CHECKERRORS();
      glDisable(GL_TEXTURE_2D);
    }

    void CTexture::SetDataPriv(InputFormat const inputFormat, DataType const inputType, void const * pData) {
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mSize.x, mSize.y, static_cast<GLenum>(inputFormat), static_cast<GLenum>(inputFormat), pData);
      CB_GL_CHECKERRORS();
    }

    void setTextureUnit(unsigned unit) {
      glActiveTexture(GL_TEXTURE0 + unit);
      CB_GL_CHECKERRORS();
    }
  }
}