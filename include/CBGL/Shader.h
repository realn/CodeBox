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
      OGLObjId mId;
      ShaderType mType;

    public:
      CShader(ShaderType const type);
      CShader(ShaderType const type, cb::string const& source);
      CShader(CShader const&) = delete;
      CShader(CShader && other);
      ~CShader();

      OGLObjId GetId() const { return mId; }

      void operator=(CShader const&) = delete;
      void operator=(CShader && other);

      void LoadSource(cb::string const& source);
      bool Compile();
      bool Compile(cb::string const& source);
      bool IsCompiled() const;
      cb::string GetCompileLog() const;
    };
  }
}
