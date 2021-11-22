#include "stdafx.h"
#include <CBGL/Program.h>
#include <CBGL/Shader.h>
#include <CBCore/StringConvert.h>

namespace cb {
  namespace gl {
    Program::Program() {
      mId = glCreateProgram();
      CB_GL_CHECKERRORS();
    }

    Program::Program(std::initializer_list<Shader> const& shaders,
      std::map<unsigned, cb::string> const& inLocations,
      std::map<unsigned, cb::string> const& outLocations)
      : Program()
    {
      attach(shaders);
      setInLocation(inLocations);
      setOutLocation(outLocations);
      link();
    }

    Program::Program(Program&&) = default;

    Program::~Program() {
      if (mId) {
        glDeleteProgram(mId);
        mId = 0;
      }
    }

    Program& Program::operator=(Program&&) = default;

    void Program::attach(Shader const& shader) {
      glAttachShader(mId, shader.getId());
      CB_GL_CHECKERRORS();
    }

    void Program::attach(std::initializer_list<Shader> const& shaders) {
      for (auto& shader : shaders) {
        attach(shader);
      }
    }

    void Program::attach(std::vector<Shader> const& shaders) {
      for (auto& shader : shaders) {
        attach(shader);
      }
    }

    bool Program::link() {
      glLinkProgram(mId);
      CB_GL_CHECKERRORS();
      return isLinked();
    }

    bool Program::isLinked() const {
      auto status = 0;
      glGetProgramiv(mId, GL_LINK_STATUS, &status);
      CB_GL_CHECKERRORS();
      return status == GL_TRUE;
    }

    bool Program::isValid() const {
      auto status = 0;
      glGetProgramiv(mId, GL_VALIDATE_STATUS, &status);
      CB_GL_CHECKERRORS();
      return status == GL_TRUE;
    }

    cb::string Program::getLinkLog() const {
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

    void Program::setInLocation(unsigned const index, cb::string const& name) {
      auto vecName = cb::toUtf8(name);
      glBindAttribLocation(mId, index, vecName.data());
      CB_GL_CHECKERRORS();
    }

    void Program::setInLocation(std::map<unsigned, cb::string> const& locations) {
      for (auto& item : locations) {
        setInLocation(item.first, item.second);
      }
    }

    void Program::setOutLocation(unsigned const index, cb::string const& name) {
      auto vecName = cb::toUtf8(name);
      glBindFragDataLocation(mId, index, vecName.data());
      CB_GL_CHECKERRORS();
    }

    void Program::setOutLocation(std::map<unsigned, cb::string> const& locations) {
      for (auto& item : locations) {
        setOutLocation(item.first, item.second);
      }
    }

    AttributeId Program::getInLocation(const cb::string& name) const {
      auto vecName = cb::toUtf8(name);
      auto id = glGetAttribLocation(mId, vecName.data());
      CB_GL_CHECKERRORS();
      if (id < 0) {
        throw std::exception("Attribute location not found.");
      }
      return static_cast<AttributeId>(id);
    }

    UniformId Program::getUniformId(cb::string const& name) const {
      auto vecName = cb::toUtf8(name);
      auto id = glGetUniformLocation(mId, vecName.data());
      CB_GL_CHECKERRORS();
      if (id < 0) {
        throw std::exception("Uniform location not found.");
      }
      return static_cast<UniformId>(id);
    }

    void Program::setUniform(UniformId const id, int const& value) {
      glUniform1i(id, value);
      CB_GL_CHECKERRORS();
    }

    void Program::setUniform(UniformId const id, unsigned const& value) {
      glUniform1ui(id, value);
      CB_GL_CHECKERRORS();
    }

    void Program::setUniform(UniformId const id, float const& value) {
      glUniform1fv(id, 1, &value);
      CB_GL_CHECKERRORS();
    }

    void Program::setUniform(UniformId const id, glm::vec2 const& value) {
      glUniform2fv(id, 1, glm::value_ptr(value));
      CB_GL_CHECKERRORS();
    }

    void Program::setUniform(UniformId const id, glm::vec3 const& value) {
      glUniform3fv(id, 1, glm::value_ptr(value));
      CB_GL_CHECKERRORS();
    }

    void Program::setUniform(UniformId const id, glm::vec4 const& value) {
      glUniform4fv(id, 1, glm::value_ptr(value));
      CB_GL_CHECKERRORS();
    }

    void Program::setUniform(UniformId const id, glm::mat4 const& value) {
      glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
      CB_GL_CHECKERRORS();
    }

    void Program::bind() const {
      glUseProgram(mId);
      CB_GL_CHECKERRORS();
    }

    void Program::unBind() {
      glUseProgram(0);
      CB_GL_CHECKERRORS();
    }
  }
}