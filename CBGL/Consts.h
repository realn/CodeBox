#pragma once

#include <memory>

namespace cb {
  namespace gl {
    enum class DataType {
      
      FLOAT = 0x1406,
    };

    template<DataType type>
    size_t getDataSize() { static_assert(false); }

    template<typename _Type>
    DataType getDataType() { static_assert(false); }


    template<>
    constexpr DataType getDataType<float>() { return DataType::FLOAT; }

    template<>
    constexpr size_t getDataSize<DataType::FLOAT>() { return 4; }
  }
}
