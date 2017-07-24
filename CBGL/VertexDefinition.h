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

    public:
      CVertexSource(unsigned const index,
                    DataType const type,
                    unsigned const number,
                    unsigned const stride,
                    unsigned const offset = 0,
                    unsigned const divisor = 0)
        : mIndex(index)
        , mType(type)
        , mNumber(number)
        , mStride(stride)
        , mOffset(offset) 
        , mDivisor(divisor)
      {}

      unsigned GetIndex() const { return mIndex; }
      DataType GetType() const { return mType; }
      unsigned GetNumber() const { return mNumber; }
      unsigned GetStride() const { return mStride; }
      unsigned GetOffset() const { return mOffset; }
      unsigned GetDivisor() const { return mDivisor; }
    };

    class CVertexDefinition {
    private:
      std::vector<CVertexSource> mSources;

    public:
      CVertexDefinition(std::vector<CVertexSource> const& sources);
      CVertexDefinition(std::initializer_list<CVertexSource> const& sources);

      void Bind() const;
      void UnBind() const;
    };
  }
}
