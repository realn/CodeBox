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
      CProgram(CProgram const&) = delete;
      CProgram(CProgram && other);
      ~CProgram();

      void operator=(CProgram const&) = delete;
      void operator=(CProgram && other);

      void Attach(CShader const& shader);
      bool Link();
      bool IsLinked() const;

      cb::string GetLinkLog() const;

      void SetInLocation(unsigned const index, cb::string const& name);
      void SetOutLocation(unsigned const index, cb::string const& name);

      UniformId GetUniformId(cb::string const& name) const;
      void SetUniform(UniformId const id, glm::mat4 const& matrix);

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
