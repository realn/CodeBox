#include "stdafx.h"
#include <CBGL/VertexDefinition.h>

namespace cb {
  namespace gl {
    VertexDefinition::VertexDefinition(std::vector<VertexSource> const& sources)
      : mSources(sources) {
    }

    VertexDefinition::VertexDefinition(std::initializer_list<VertexSource> const& sources)
      : mSources(sources) {
    }

    void VertexDefinition::bind() const {
      for (auto& source : mSources) {
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

    void VertexDefinition::unBind() const {
      for (auto& source : mSources) {
        glDisableVertexAttribArray(source.getIndex());
      }
    }
  }
}