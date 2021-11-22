#pragma once

#include "Defines.h"

#include <set>
#include <unordered_set>

namespace cb {
  namespace gl {
    class Shader;

    class Program {
    private:
      OGLObjId mId = 0;

    public:
      Program();
      Program(std::initializer_list<Shader> const& shaders,
               std::map<unsigned, cb::string> const& inLocations = {},
               std::map<unsigned, cb::string> const& outLocations = {});
      Program(Program const&) = delete;
      Program(Program &&);
      ~Program();

      Program& operator=(Program const&) = delete;
      Program& operator=(Program &&);

      void attach(Shader const& shader);
      void attach(std::initializer_list<Shader> const& shaders);
      void attach(std::vector<Shader> const& shaders);
      bool link();
      bool isLinked() const;
      bool isValid() const;

      cb::string getLinkLog() const;

      void setInLocation(unsigned const index, cb::string const& name);
      void setInLocation(std::map<unsigned, cb::string> const& locations);
      void setOutLocation(unsigned const index, cb::string const& name);
      void setOutLocation(std::map<unsigned, cb::string> const& locations);
      AttributeId getInLocation(const cb::string& name) const;

      UniformId getUniformId(cb::string const& name) const;
      void setUniform(UniformId const id, int const& value);
      void setUniform(UniformId const id, unsigned const& value);
      void setUniform(UniformId const id, float const& value);
      void setUniform(UniformId const id, glm::vec2 const& value);
      void setUniform(UniformId const id, glm::vec3 const& value);
      void setUniform(UniformId const id, glm::vec4 const& value);
      void setUniform(UniformId const id, glm::mat4 const& value);

      template<typename _Type>
      void setUniform(cb::string const& name, _Type const& value) {
        auto id = getUniformId(name);
        setUniform(id, value);
      }

      void bind() const;
      static void unBind();
    };
  }
}
