#pragma once

#include "Defines.h"
#include "Consts.h"

#include <vector>

namespace cb {
  namespace gl {
    class CVertexSource {
    private:
      unsigned mIndex;
      DataType mType;
      unsigned mNumber;
      unsigned mStride;
      unsigned mOffset;
      unsigned mDivisor;
      bool mNormalized;

    public:
      CVertexSource(unsigned const index,
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
        , mNormalized(normalized)
      {}

      unsigned getIndex() const { return mIndex; }
      DataType getType() const { return mType; }
      unsigned getNumber() const { return mNumber; }
      unsigned getStride() const { return mStride; }
      unsigned getOffset() const { return mOffset; }
      unsigned getDivisor() const { return mDivisor; }
      bool getNormalized() const { return mNormalized; }
    };

    class CVertexDefinition {
    private:
      std::vector<CVertexSource> mSources;

    public:
      CVertexDefinition(std::vector<CVertexSource> const& sources);
      CVertexDefinition(std::initializer_list<CVertexSource> const& sources);

      void bind() const;
      void unBind() const;
    };
  }
}
