#pragma once

#include "Defines.h"

#include <set>
#include <unordered_set>

namespace cb {
  namespace gl {
    class CShader;

    class CProgram {
    private:
      OGLObjId mId;

    public:
      CProgram();
      CProgram(std::initializer_list<CShader> const& shaders,
               std::map<unsigned, cb::string> const& inLocations = {},
               std::map<unsigned, cb::string> const& outLocations = {});
      CProgram(CProgram const&) = delete;
      CProgram(CProgram && other);
      ~CProgram();

      void operator=(CProgram const&) = delete;
      void operator=(CProgram && other);

      void Attach(CShader const& shader);
      void Attach(std::initializer_list<CShader> const& shaders);
      void Attach(std::vector<CShader> const& shaders);
      bool Link();
      bool IsLinked() const;
      bool IsValid() const;

      cb::string GetLinkLog() const;

      void SetInLocation(unsigned const index, cb::string const& name);
      void SetInLocation(std::map<unsigned, cb::string> const& locations);
      void SetOutLocation(unsigned const index, cb::string const& name);
      void SetOutLocation(std::map<unsigned, cb::string> const& locations);
      AttributeId GetInLocation(const cb::string& name) const;

      UniformId GetUniformId(cb::string const& name) const;
      void SetUniform(UniformId const id, int const& value);
      void SetUniform(UniformId const id, unsigned const& value);
      void SetUniform(UniformId const id, float const& value);
      void SetUniform(UniformId const id, glm::vec2 const& value);
      void SetUniform(UniformId const id, glm::vec3 const& value);
      void SetUniform(UniformId const id, glm::vec4 const& value);
      void SetUniform(UniformId const id, glm::mat4 const& value);

      template<typename _Type>
      void SetUniform(cb::string const& name, _Type const& value) {
        auto id = GetUniformId(name);
        SetUniform(id, value);
      }

      void Bind() const;
      static void UnBind();
    };
  }
}
