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

    class Buffer {
    private:
      OGLObjId mId;
      BufferTarget mTarget;

    public:
      Buffer(BufferTarget const& target = BufferTarget::ARRAY);
      Buffer(Buffer const&) = delete;
      Buffer(Buffer&&) = default;
      ~Buffer();

      Buffer& operator=(Buffer const&) = delete;
      Buffer& operator=(Buffer&&) = default;

      void bind() const;
      void unBind() const;

      template<typename _Type, typename _TypeAlloc = std::allocator<_Type>>
      void setData(std::vector<_Type, _TypeAlloc> const& data, BufferUsage const& usage = BufferUsage::STATIC_DRAW) {
        setDataRaw(reinterpret_cast<void const*>(data.data()), data.size() * sizeof(_Type), usage);
      }
      template<typename _Type, size_t _TypeSize>
      void setData(std::array<_Type, _TypeSize> const& data, BufferUsage const& usage = BufferUsage::STATIC_DRAW) {
        setDataRaw(reinterpret_cast<void const*>(data.data()), data.size() * sizeof(_Type), usage);
      }
      template<typename _Type, typename _TypeAlloc = std::allocator<_Type>>
      void setData(std::initializer_list<_Type> const& data, BufferUsage const& usage = BufferUsage::STATIC_DRAW) {
        std::vector<_Type, _TypeAlloc> datavec(data);
        setData(datavec, usage);
      }

      template<typename _Type, typename _TypeAlloc = std::allocator<_Type>>
      void setSubData(std::vector<_Type, _TypeAlloc> const& data, size_t const offset = 0) {
        setSubDataRaw(offset, reinterpret_cast<void const*>(data.data()), data.size() * sizeof(_Type));
      }
      template<typename _Type, size_t _TypeSize>
      void setSubData(std::array<_Type, _TypeSize> const& data, size_t const offset = 0) {
        setSubDataRaw(offset, reinterpret_cast<void const*>(data.data()), data.size() * sizeof(_Type));
      }
      template<typename _Type, typename _TypeAlloc = std::allocator<_Type>>
      void setSubData(std::initializer_list<_Type> const& data, size_t const offset = 0) {
        std::vector<_Type, _TypeAlloc> datavec(data);
        setSubData(datavec, offset);
      }

      void setDataRaw(void const* pData, std::size_t const& size, BufferUsage const& usage);
      void setSubDataRaw(std::size_t const& offset, void const* pData, std::size_t const& size);
    };

    void drawArrays(PrimitiveType const primType,
                    unsigned const indNum,
                    int const indFirst = 0);
    void drawArraysInstanced(PrimitiveType const primType,
                             unsigned const indNum,
                             unsigned const primNum,
                             int const indFirst = 0);
    void drawElements(PrimitiveType const primType,
                      unsigned const indNum,
                      DataType const indType = DataType::UNSIGNED_SHORT,
                      unsigned const indOffset = 0);
    void drawElementsInstanced(PrimitiveType const primType,
                               unsigned const indNum,
                               unsigned const primNum,
                               DataType const indType = DataType::UNSIGNED_SHORT,
                               unsigned const indOffset = 0);
    void drawElementsVec(PrimitiveType const primType,
                         unsigned const indNum,
                         DataType const indType,
                         const void* pIndData);
    void drawElementsVecInstanced(PrimitiveType const primType,
                                  unsigned const indNum,
                                  unsigned const primNum,
                                  DataType const indType,
                                  const void* pIndData);

    template<typename _Type>
    void drawElements(PrimitiveType const primType, std::vector<_Type> const& indices, unsigned const indIndex = 0) {
      drawElementsVec(primType,
                      static_cast<unsigned>(indices.size()) - indIndex,
                      getDataType<_Type>(),
                      reinterpret_cast<const void*>(indices.data() + static_cast<size_t>(indIndex)));
    }
    template<typename _Type>
    void drawElementsInstanced(PrimitiveType const primType, unsigned const primNum, std::vector<_Type> const& indices, unsigned const indIndex = 0) {
      drawElementsVecInstanced(primType,
                               static_cast<unsigned>(indices.size()) - indIndex,
                               primNum,
                               getDataType<_Type>(),
                               reinterpret_cast<const void*>(indices.data() + static_cast<size_t>(indIndex)));
    }
  }
}
