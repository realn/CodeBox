#include "stdafx.h"
#include "../Program.h"
#include "../Shader.h"

#include <CBStr/StringEx.h>

namespace cb {
  namespace gl {
    CProgram::CProgram() 
      : mId(0)
    {
      mId = glCreateProgram();
      CB_GL_CHECKERRORS();
    }

    CProgram::CProgram(std::initializer_list<CShader> const & shaders, 
                       std::map<unsigned, cb::string> const & inLocations, 
                       std::map<unsigned, cb::string> const & outLocations) 
      : CProgram()
    {
      Attach(shaders);
      SetInLocation(inLocations);
      SetOutLocation(outLocations);
      Link();
    }

    CProgram::CProgram(CProgram && other) 
      : mId(0)
    {
      std::swap(mId, other.mId);
    }

    CProgram::~CProgram() {
      if(mId) {
        glDeleteProgram(mId);
        mId = 0;
      }
    }

    void CProgram::operator=(CProgram && other) {
      std::swap(mId, other.mId);
    }

    void CProgram::Attach(CShader const & shader) {
      glAttachShader(mId, shader.GetId());
      CB_GL_CHECKERRORS();
    }

    void CProgram::Attach(std::initializer_list<CShader> const & shaders) {
      for(auto& shader : shaders) {
        Attach(shader);
      }
    }

    bool CProgram::Link() {
      glLinkProgram(mId);
      CB_GL_CHECKERRORS();
      return IsLinked();
    }

    bool CProgram::IsLinked() const {
      auto status = 0;
      glGetProgramiv(mId, GL_LINK_STATUS, &status);
      CB_GL_CHECKERRORS();
      return status == GL_TRUE;
    }

    cb::string CProgram::GetLinkLog() const {
      auto len = 0;
      glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &len);
      CB_GL_CHECKERRORS();
      if(len <= 0) {
        return cb::string();
      }

      auto log = cb::charvector(static_cast<size_t>(len));
      auto szLog = static_cast<GLchar*>(log.data());
      glGetProgramInfoLog(mId, len, nullptr, szLog);
      CB_GL_CHECKERRORS();

      return cb::fromUtf8(log);
    }

    void CProgram::SetInLocation(unsigned const index, cb::string const & name) {
      auto vecName = cb::toUtf8(name, true);
      glBindAttribLocation(mId, index, vecName.data());
      CB_GL_CHECKERRORS();
    }

    void CProgram::SetInLocation(std::map<unsigned, cb::string> const & locations) {
      for(auto& item : locations) {
        SetInLocation(item.first, item.second);
      }
    }

    void CProgram::SetOutLocation(unsigned const index, cb::string const & name) {
      auto vecName = cb::toUtf8(name, true);
      glBindFragDataLocation(mId, index, vecName.data());
      CB_GL_CHECKERRORS();
    }

    void CProgram::SetOutLocation(std::map<unsigned, cb::string> const & locations) {
      for(auto& item : locations) {
        SetOutLocation(item.first, item.second);
      }
    }

    UniformId CProgram::GetUniformId(cb::string const & name) const {
      auto vecName = cb::toUtf8(name, true);
      auto id = glGetUniformLocation(mId, vecName.data());
      CB_GL_CHECKERRORS();
      if(id < 0) {
        throw std::exception("Uniform location not found.");
      }
      return static_cast<UniformId>(id);
    }

    void CProgram::SetUniform(UniformId const id, glm::mat4 const & matrix) {
      glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
      CB_GL_CHECKERRORS();
    }

    void CProgram::Bind() const {
      glUseProgram(mId);
      CB_GL_CHECKERRORS();
    }

    void CProgram::UnBind() {
      glUseProgram(0);
      CB_GL_CHECKERRORS();
    }
  }
}