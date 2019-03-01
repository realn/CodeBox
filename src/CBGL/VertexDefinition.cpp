#include "stdafx.h"
#include <CBGL/VertexDefinition.h>

namespace cb {
  namespace gl {
    CVertexDefinition::CVertexDefinition(std::vector<CVertexSource> const & sources) 
      : mSources(sources)
    {}

    CVertexDefinition::CVertexDefinition(std::initializer_list<CVertexSource> const & sources) 
      : mSources(sources)
    {}

    void CVertexDefinition::Bind() const {
      for(auto& source : mSources) {
        glVertexAttribPointer(source.GetIndex(),
                              source.GetNumber(),
                              static_cast<GLenum>(source.GetType()),
                              source.GetNormalized() ? GL_TRUE : GL_FALSE,
                              source.GetStride(),
                              reinterpret_cast<const void*>(static_cast<size_t>(source.GetOffset())));
        glEnableVertexAttribArray(source.GetIndex());
        glVertexAttribDivisor(source.GetIndex(), source.GetDivisor());
      }
    }

    void CVertexDefinition::UnBind() const {
      for(auto& source : mSources) {
        glDisableVertexAttribArray(source.GetIndex());
      }
    }
  }
}