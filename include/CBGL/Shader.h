#pragma once

#include "Defines.h"

namespace cb {
  namespace gl {
    enum class ShaderType {
      FRAGMENT = 0x8B30,
      VERTEX = 0x8B31,
    };

    class CShader {
    private:
      OGLObjId mId = 0;
      ShaderType mType;

    public:
      CShader(ShaderType const type);
      CShader(ShaderType const type, cb::string const& source);
      CShader(CShader const&) = delete;
      CShader(CShader &&);
      ~CShader();

      OGLObjId getId() const { return mId; }

      CShader& operator=(CShader const&) = delete;
      CShader& operator=(CShader &&);

      void loadSource(cb::string const& source);
      bool compile();
      bool compile(cb::string const& source);
      bool isCompiled() const;
      cb::string getCompileLog() const;
    };
  }
}
