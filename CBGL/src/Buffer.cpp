#include "stdafx.h"
#include "../Buffer.h"

namespace cb {
  namespace gl {
    CBuffer::CBuffer(BufferTarget const & target) 
      : mId(0)
      , mTarget(target)
    {
      glGenBuffers(1, static_cast<GLuint*>(&mId));
      CB_GL_CHECKERRORS();
    }

    CBuffer::CBuffer(CBuffer && other) 
      : mId(0)
      , mTarget(BufferTarget::ARRAY)
    {
      std::swap(mId, other.mId);
      std::swap(mTarget, other.mTarget);
    }

    CBuffer::~CBuffer() {
      if(mId) {
        glDeleteBuffers(1, static_cast<GLuint*>(&mId));
        mId = 0;
      }
    }

    void CBuffer::operator=(CBuffer && other) {
      std::swap(mId, other.mId);
      std::swap(mTarget, other.mTarget);
    }

    void CBuffer::Bind() const {
      glBindBuffer(static_cast<GLenum>(mTarget), mId);
      CB_GL_CHECKERRORS();
    }

    void CBuffer::UnBind() const {
      glBindBuffer(static_cast<GLenum>(mTarget), 0);
      CB_GL_CHECKERRORS();
    }

    void CBuffer::UnBind(BufferTarget const & target) {
      glBindBuffer(static_cast<GLenum>(target), 0);
      CB_GL_CHECKERRORS();
    }

    void CBuffer::SetDataPriv(void const * pData, std::size_t const & size, BufferUsage const & usage) {
      glBufferData(static_cast<GLenum>(mTarget),
                   static_cast<GLsizeiptr>(size),
                   pData,
                   static_cast<GLenum>(usage));
      CB_GL_CHECKERRORS();
    }

    void CBuffer::SetSubDataPriv(std::size_t const & offset, void const * pData, std::size_t const & size) {
      glBufferSubData(static_cast<GLenum>(mTarget),
                      static_cast<GLintptr>(offset),
                      static_cast<GLsizeiptr>(size),
                      pData);
      CB_GL_CHECKERRORS();
    }

    void drawArrays(PrimitiveType const type, size_t const & count, int first) {
      glDrawArrays(static_cast<GLenum>(type), first, count);
      CB_GL_CHECKERRORS();
    }
  }
}