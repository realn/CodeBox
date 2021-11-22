#include "stdafx.h"
#include <CBGL/Program.h>
#include <CBGL/Shader.h>
#include <CBCore/StringConvert.h>

namespace cb {
  namespace gl {
    CProgram::CProgram() {
      mId = glCreateProgram();
      CB_GL_CHECKERRORS();
    }

    CProgram::CProgram(std::initializer_list<CShader> const& shaders,
      std::map<unsigned, cb::string> const& inLocations,
      std::map<unsigned, cb::string> const& outLocations)
      : CProgram()
    {
      attach(shaders);
      setInLocation(inLocations);
      setOutLocation(outLocations);
      link();
    }

    CProgram::CProgram(CProgram&&) = default;

    CProgram::~CProgram() {
      if (mId) {
        glDeleteProgram(mId);
        mId = 0;
      }
    }

    CProgram& CProgram::operator=(CProgram&&) = default;

    void CProgram::attach(CShader const& shader) {
      glAttachShader(mId, shader.getId());
      CB_GL_CHECKERRORS();
    }

    void CProgram::attach(std::initializer_list<CShader> const& shaders) {
      for (auto& shader : shaders) {
        attach(shader);
      }
    }

    void CProgram::attach(std::vector<CShader> const& shaders) {
      for (auto& shader : shaders) {
        attach(shader);
      }
    }

    bool CProgram::link() {
      glLinkProgram(mId);
      CB_GL_CHECKERRORS();
      return isLinked();
    }

    bool CProgram::isLinked() const {
      auto status = 0;
      glGetProgramiv(mId, GL_LINK_STATUS, &status);
      CB_GL_CHECKERRORS();
      return status == GL_TRUE;
    }

    bool CProgram::isValid() const {
      auto status = 0;
      glGetProgramiv(mId, GL_VALIDATE_STATUS, &status);
      CB_GL_CHECKERRORS();
      return status == GL_TRUE;
    }

    cb::string CProgram::getLinkLog() const {
      auto len = 0;
      glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &len);
      CB_GL_CHECKERRORS();
      if (len <= 0) {
        return cb::string();
      }

      auto log = cb::utf8string(static_cast<size_t>(len), 0);
      auto szLog = static_cast<GLchar*>(&log[0]);
      glGetProgramInfoLog(mId, len, nullptr, szLog);
      CB_GL_CHECKERRORS();

      return cb::fromUtf8(log);
    }

    void CProgram::setInLocation(unsigned const index, cb::string const& name) {
      auto vecName = cb::toUtf8(name);
      glBindAttribLocation(mId, index, vecName.data());
      CB_GL_CHECKERRORS();
    }

    void CProgram::setInLocation(std::map<unsigned, cb::string> const& locations) {
      for (auto& item : locations) {
        setInLocation(item.first, item.second);
      }
    }

    void CProgram::setOutLocation(unsigned const index, cb::string const& name) {
      auto vecName = cb::toUtf8(name);
      glBindFragDataLocation(mId, index, vecName.data());
      CB_GL_CHECKERRORS();
    }

    void CProgram::setOutLocation(std::map<unsigned, cb::string> const& locations) {
      for (auto& item : locations) {
        setOutLocation(item.first, item.second);
      }
    }

    AttributeId CProgram::getInLocation(const cb::string& name) const {
      auto vecName = cb::toUtf8(name);
      auto id = glGetAttribLocation(mId, vecName.data());
      CB_GL_CHECKERRORS();
      if (id < 0) {
        throw std::exception("Attribute location not found.");
      }
      return static_cast<AttributeId>(id);
    }

    UniformId CProgram::getUniformId(cb::string const& name) const {
      auto vecName = cb::toUtf8(name);
      auto id = glGetUniformLocation(mId, vecName.data());
      CB_GL_CHECKERRORS();
      if (id < 0) {
        throw std::exception("Uniform location not found.");
      }
      return static_cast<UniformId>(id);
    }

    void CProgram::setUniform(UniformId const id, int const& value) {
      glUniform1i(id, value);
      CB_GL_CHECKERRORS();
    }

    void CProgram::setUniform(UniformId const id, unsigned const& value) {
      glUniform1ui(id, value);
      CB_GL_CHECKERRORS();
    }

    void CProgram::setUniform(UniformId const id, float const& value) {
      glUniform1fv(id, 1, &value);
      CB_GL_CHECKERRORS();
    }

    void CProgram::setUniform(UniformId const id, glm::vec2 const& value) {
      glUniform2fv(id, 1, glm::value_ptr(value));
      CB_GL_CHECKERRORS();
    }

    void CProgram::setUniform(UniformId const id, glm::vec3 const& value) {
      glUniform3fv(id, 1, glm::value_ptr(value));
      CB_GL_CHECKERRORS();
    }

    void CProgram::setUniform(UniformId const id, glm::vec4 const& value) {
      glUniform4fv(id, 1, glm::value_ptr(value));
      CB_GL_CHECKERRORS();
    }

    void CProgram::setUniform(UniformId const id, glm::mat4 const& value) {
      glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
      CB_GL_CHECKERRORS();
    }

    void CProgram::bind() const {
      glUseProgram(mId);
      CB_GL_CHECKERRORS();
    }

    void CProgram::unBind() {
      glUseProgram(0);
      CB_GL_CHECKERRORS();
    }
  }
}