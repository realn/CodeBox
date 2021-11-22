#pragma once

#include "Defines.h"
#include "Consts.h"

#include <vector>

namespace cb {
  namespace gl {
    class VertexSource {
    private:
      unsigned mIndex;
      DataType mType;
      unsigned mNumber;
      unsigned mStride;
      unsigned mOffset;
      unsigned mDivisor;
      bool mNormalized;

    public:
      VertexSource(unsigned const index,
                   DataType const type,
                   unsigned const number,
                   unsigned const stride,
                   unsigned const offset = 0,
                   unsigned const divisor = 0,
                   bool normalized = false
      )
        : mIndex(index)
        , mType(type)
        , mNumber(number)
        , mStride(stride)
        , mOffset(offset)
        , mDivisor(divisor)
        , mNormalized(normalized) {
      }

      unsigned getIndex() const { return mIndex; }
      DataType getType() const { return mType; }
      unsigned getNumber() const { return mNumber; }
      unsigned getStride() const { return mStride; }
      unsigned getOffset() const { return mOffset; }
      unsigned getDivisor() const { return mDivisor; }
      bool getNormalized() const { return mNormalized; }
    };

    class VertexDefinition {
    private:
      std::vector<VertexSource> mSources;

    public:
      VertexDefinition(std::vector<VertexSource> const& sources);
      VertexDefinition(std::initializer_list<VertexSource> const& sources);

      void bind() const;
      void unBind() const;
    };
  }
}
