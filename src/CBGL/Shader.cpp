#include "stdafx.h"
#include <CBGL/Shader.h>
#include <CBCore/StringConvert.h>

namespace cb {
  namespace gl {
    Shader::Shader(ShaderType const type)
      : mType(type) {
      mId = glCreateShader(static_cast<GLenum>(mType));
      CB_GL_CHECKERRORS();
    }

    Shader::Shader(ShaderType const type, cb::string const& source)
      : Shader(type) {
      compile(source);
    }

    Shader::Shader(Shader&&) = default;

    Shader::~Shader() {
      if (mId) {
        glDeleteShader(mId);
        mId = 0;
      }
    }

    Shader& Shader::operator=(Shader&& other) = default;

    void Shader::loadSource(cb::string const& source) {
      auto sourceVec = cb::toUtf8(source);
      auto szSource = reinterpret_cast<GLchar const*>(sourceVec.data());

      glShaderSource(mId, 1, &szSource, nullptr);
      CB_GL_CHECKERRORS();
    }

    bool Shader::compile() {
      glCompileShader(mId);
      CB_GL_CHECKERRORS();
      return isCompiled();
    }

    bool Shader::compile(cb::string const& source) {
      loadSource(source);
      return compile();
    }

    bool Shader::isCompiled() const {
      auto status = 0;
      glGetShaderiv(mId, GL_COMPILE_STATUS, &status);
      CB_GL_CHECKERRORS();
      return status == GL_TRUE;
    }

    cb::string Shader::getCompileLog() const {
      auto len = 0;
      glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &len);
      CB_GL_CHECKERRORS();
      if (len <= 0) {
        return cb::string();
      }

      auto log = cb::utf8string(static_cast<size_t>(len), 0);
      auto szLog = static_cast<GLchar*>(&log[0]);
      glGetShaderInfoLog(mId, len, nullptr, szLog);
      CB_GL_CHECKERRORS();

      return cb::fromUtf8(log);
    }
  }
}