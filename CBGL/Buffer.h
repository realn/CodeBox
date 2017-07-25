#pragma once

#include "Defines.h"
#include "Consts.h"

#include <vector>
#include <array>

namespace cb {
  namespace gl {
    enum class BufferTarget {
      ARRAY = 0x8892,
      ELEMENT_ARRAY = 0x8893,
      UNIFORM = 0x8A11,
    };

    enum class BufferUsage {
      STREAM_DRAW = 0x88E0,
      STREAM_READ = 0x88E1,
      STREAM_COPY = 0x88E2,
      STATIC_DRAW = 0x88E4,
      STATIC_READ = 0x88E5,
      STATIC_COPY = 0x88E6,
      DYNAMIC_DRAW = 0x88E8,
      DYNAMIC_READ = 0x88E9,
      DYNAMIC_COPY = 0x88EA,
    };

    enum class PrimitiveType {
      POINTS = 0x0000,
      LINES = 0x0001,
      TRIANGLES = 0x0004,
    };

    class CBuffer {
    private:
      OGLObjId mId;
      BufferTarget mTarget;

    public:
      CBuffer(BufferTarget const& target = BufferTarget::ARRAY);
      CBuffer(CBuffer const&) = delete;
      CBuffer(CBuffer && other);
      ~CBuffer();

      void operator=(CBuffer const&) = delete;
      void operator=(CBuffer && other);

      void Bind() const;
      void UnBind() const;

      template<typename _Type, typename _TypeAlloc = std::allocator<_Type>>
      void SetData(std::vector<_Type, _TypeAlloc> const& data, BufferUsage const& usage = BufferUsage::STATIC_DRAW) {
        SetDataPriv(reinterpret_cast<void const*>(data.data()), data.size() * sizeof(_Type), usage);
      }
      template<typename _Type, size_t _TypeSize>
      void SetData(std::array<_Type, _TypeSize> const& data, BufferUsage const& usage = BufferUsage::STATIC_DRAW) {
        SetDataPriv(reinterpret_cast<void const*>(data.data()), data.size() * sizeof(_Type), usage);
      }
      template<typename _Type, typename _TypeAlloc = std::allocator<_Type>>
      void SetData(std::initializer_list<_Type> const& data, BufferUsage const& usage = BufferUsage::STATIC_DRAW) {
        std::vector<_Type, _TypeAlloc> datavec(data);
        SetData(datavec, usage);
      }

    private:
      void SetDataPriv(void const* pData, std::size_t const& size, BufferUsage const& usage);
      void SetSubDataPriv(std::size_t const& offset, void const* pData, std::size_t const& size);
    };

    extern void drawArrays(PrimitiveType const primType,
                           unsigned const indNum,
                           int const indFirst = 0);
    extern void drawArraysInstanced(PrimitiveType const primType,
                                    unsigned const indNum,
                                    unsigned const primNum,
                                    int const indFirst = 0);
    extern void drawElements(PrimitiveType const primType,
                             unsigned const indNum,
                             DataType const indType = DataType::UNSIGNED_SHORT,
                             unsigned const indOffset = 0);
    extern void drawElementsInstanced(PrimitiveType const primType,
                                      unsigned const indNum,
                                      unsigned const primNum,
                                      DataType const indType = DataType::UNSIGNED_SHORT,
                                      unsigned const indOffset = 0);
    extern void drawElementsVec(PrimitiveType const primType,
                                unsigned const indNum,
                                DataType const indType,
                                const void* pIndData);
    extern void drawElementsVecInstanced(PrimitiveType const primType,
                                         unsigned const indNum,
                                         unsigned const primNum,
                                         DataType const indType,
                                         const void* pIndData);

    template<typename _Type>
    void drawElements(PrimitiveType const primType, std::vector<_Type> const& indices, unsigned const indIndex = 0) {
      drawElementsVec(primType, indices.size() - indIndex, getDataType<_Type>(), reinterpret_cast<const void*>(indices.data() + indIndex));
    }
    template<typename _Type>
    void drawElementsInstanced(PrimitiveType const primType, unsigned const primNum, std::vector<_Type> const& indices, unsigned const indIndex = 0) {
      drawElementsVecInstanced(primType, indices.size() - indIndex, primNum, getDataType<_Type>(), reinterpret_cast<const void*>(indices.data() + indIndex));
    }
  }
}
