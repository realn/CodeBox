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

    class VertexSourceList {
    public:
      template<class _VertexType, class _Type>
      void add(u32 index, u32 divisor = 0, bool normalized = false) {
        add(index, getDataType<_Type>(), getDataTypeSize<_Type>(), sizeof(_VertexType), divisor, normalized);
      }
      template<class _VertexType, class _Type>
      void addWithOffset(u32 index, u32 offset, u32 divisor = 0, bool normalized = false) {
        addWithOffset(index, getDataType<_Type>(), getDataTypeSize<_Type>(), sizeof(_VertexType), offset, divisor, normalized);
      }

      template<class _Type>
      void addWithSize(u32 index, u32 stride, u32 divisor = 0, bool normalized = false) {
        add(index, getDataType<_Type>(), getDataTypeSize<_Type>(), stride, divisor, normalized);
      }
      template<class _Type>
      void addWithSizeAndOffset(u32 index, u32 offset, u32 stride, u32 divisor = 0, bool normalized = false) {
        addWithOffset(index, getDataType<_Type>(), getDataTypeSize<_Type>(), stride, offset, divisor, normalized);
      }

      const std::vector<VertexSource>& getSources() const { return sources; }

    private:
      u32 getOffset();
      void add(u32 index, DataType type, u32 number, u32 stride, u32 divisor, bool normalized);
      void addWithOffset(u32 index, DataType type, u32 number, u32 stride, u32 offset, u32 divisor, bool normalized);

      std::vector<VertexSource> sources;
    };

    class VertexDefinition {
    private:
      std::vector<VertexSource> mSources;

    public:
      VertexDefinition(std::vector<VertexSource> const& sources);
      VertexDefinition(std::initializer_list<VertexSource> const& sources);
      VertexDefinition(VertexSourceList const& sourceList);

      void bind() const;
      void unBind() const;
    };
  }
}
