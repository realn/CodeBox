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

    void CVertexDefinition::bind() const {
      for(auto& source : mSources) {
        glVertexAttribPointer(source.getIndex(),
                              source.getNumber(),
                              static_cast<GLenum>(source.getType()),
                              source.getNormalized() ? GL_TRUE : GL_FALSE,
                              source.getStride(),
                              reinterpret_cast<const void*>(static_cast<size_t>(source.getOffset())));
        glEnableVertexAttribArray(source.getIndex());
        glVertexAttribDivisor(source.getIndex(), source.getDivisor());
      }
    }

    void CVertexDefinition::unBind() const {
      for(auto& source : mSources) {
        glDisableVertexAttribArray(source.getIndex());
      }
    }
  }
}