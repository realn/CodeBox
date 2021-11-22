#pragma once

#include "Defines.h"

namespace cb {
  namespace gl {
    enum class ShaderType {
      FRAGMENT = 0x8B30,
      VERTEX = 0x8B31,
    };

    class Shader {
    private:
      OGLObjId mId = 0;
      ShaderType mType;

    public:
      Shader(ShaderType const type);
      Shader(ShaderType const type, cb::string const& source);
      Shader(Shader const&) = delete;
      Shader(Shader &&);
      ~Shader();

      OGLObjId getId() const { return mId; }

      Shader& operator=(Shader const&) = delete;
      Shader& operator=(Shader &&);

      void loadSource(cb::string const& source);
      bool compile();
      bool compile(cb::string const& source);
      bool isCompiled() const;
      cb::string getCompileLog() const;
    };
  }
}
