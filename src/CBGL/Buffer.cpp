#include "stdafx.h"
#include <CBGL/Buffer.h>

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

    void CBuffer::SetDataPriv(void const * pData, std::size_t const & size, BufferUsage const & usage) {
      auto gbuf = bind(*this);
      glBufferData(static_cast<GLenum>(mTarget),
                   static_cast<GLsizeiptr>(size),
                   pData,
                   static_cast<GLenum>(usage));
      CB_GL_CHECKERRORS();
    }

    void CBuffer::SetSubDataPriv(std::size_t const & offset, void const * pData, std::size_t const & size) {
      auto gbuf = bind(*this);
      glBufferSubData(static_cast<GLenum>(mTarget),
                      static_cast<GLintptr>(offset),
                      static_cast<GLsizeiptr>(size),
                      pData);
      CB_GL_CHECKERRORS();
    }

    void drawArrays(PrimitiveType const primType, unsigned const indNum, int const indFirst) {
      glDrawArrays(static_cast<GLenum>(primType), indFirst, indNum);
      CB_GL_CHECKERRORS();
    }

    void drawArraysInstanced(PrimitiveType const primType, unsigned const indNum, unsigned const primNum, int const indFirst) {
      glDrawArraysInstanced(static_cast<GLenum>(primType), indFirst, indNum, primNum);
      CB_GL_CHECKERRORS();
    }

    void drawElementsVec(PrimitiveType const primType, unsigned const indNum, DataType const indType, const void * pIndData) {
      glDrawElements(static_cast<GLenum>(primType), indNum, static_cast<GLenum>(indType), pIndData);
      CB_GL_CHECKERRORS();
    }

    void drawElementsVecInstanced(PrimitiveType const primType, unsigned const indNum, unsigned const primNum, DataType const indType, const void * pIndData) {
      glDrawElementsInstanced(static_cast<GLenum>(primType), indNum, static_cast<GLenum>(indType), pIndData, primNum);
      CB_GL_CHECKERRORS();
    }

    void drawElements(PrimitiveType const primType, unsigned const indNum, DataType const indType, unsigned const indOffset) {
      glDrawElements(static_cast<GLenum>(primType), indNum, static_cast<GLenum>(indType), reinterpret_cast<const void*>(indOffset));
      CB_GL_CHECKERRORS();
    }

    void drawElementsInstanced(PrimitiveType const primType, unsigned const indNum, unsigned const primNum, DataType const indType, unsigned const indOffset) {
      glDrawElementsInstanced(static_cast<GLenum>(primType), indNum, static_cast<GLenum>(indType), reinterpret_cast<const void*>(indOffset), primNum);
      CB_GL_CHECKERRORS();
    }
  }
}