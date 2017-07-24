#include "stdafx.h"
#include "../Shader.h"

#include <CBStr/StringEx.h>

namespace cb {
  namespace gl {
    CShader::CShader(ShaderType const type) 
      : mId(0)
      , mType(type)
    {
      mId = glCreateShader(static_cast<GLenum>(mType));
      CB_GL_CHECKERRORS();
    }

    CShader::CShader(ShaderType const type, cb::string const & source)
      : CShader(type)
    {
      Compile(source);
    }

    CShader::CShader(CShader && other)
      : mId(0)
      , mType(ShaderType::VERTEX)
    {
      std::swap(mId, other.mId);
      std::swap(mType, other.mType);
    }

    CShader::~CShader() {
      if(mId) {
        glDeleteShader(mId);
        mId = 0;
      }
    }

    void CShader::operator=(CShader && other) {
      std::swap(mId, other.mId);
      std::swap(mType, other.mType);
    }

    void CShader::LoadSource(cb::string const & source) {
      auto sourceVec = cb::toUtf8(source, true);
      auto szSource = reinterpret_cast<GLchar const*>(sourceVec.data());

      glShaderSource(mId, 1, &szSource, nullptr);
      CB_GL_CHECKERRORS();
    }

    bool CShader::Compile() {
      glCompileShader(mId);
      CB_GL_CHECKERRORS();
      return IsCompiled();
    }

    bool CShader::Compile(cb::string const & source) {
      LoadSource(source);
      return Compile();
    }

    bool CShader::IsCompiled() const {
      auto status = 0;
      glGetShaderiv(mId, GL_COMPILE_STATUS, &status);
      CB_GL_CHECKERRORS();
      return status == GL_TRUE;
    }

    cb::string CShader::GetCompileLog() const {
      auto len = 0;
      glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &len);
      CB_GL_CHECKERRORS();
      if(len <= 0) {
        return cb::string();
      }

      auto log = cb::charvector(static_cast<size_t>(len));
      auto szLog = static_cast<GLchar*>(log.data());
      glGetShaderInfoLog(mId, len, nullptr, szLog);
      CB_GL_CHECKERRORS();

      return cb::fromUtf8(log);
    }
  }
}