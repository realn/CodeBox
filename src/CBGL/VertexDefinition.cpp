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

    VertexDefinition::VertexDefinition(VertexSourceList const& sourceList) : VertexDefinition(sourceList.getSources()) {
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

    u32 VertexSourceList::getOffset() {
      u32 offset = 0;
      for (auto& source : sources)
        offset += source.getStride();
      return offset;
    }

    void VertexSourceList::add(u32 index, DataType type, u32 number, u32 stride, u32 divisor, bool normalized) {
      sources.push_back(VertexSource(index, type, number, stride, getOffset(), divisor, normalized));
    }
    void VertexSourceList::addWithOffset(u32 index, DataType type, u32 number, u32 stride, u32 offset, u32 divisor, bool normalized) {
      sources.push_back(VertexSource(index, type, number, stride, offset, divisor, normalized));
    }
  }
}