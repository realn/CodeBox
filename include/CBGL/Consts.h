#pragma once

#include <memory>

namespace cb {
  namespace gl {
    enum class DataType {
      BYTE = 0x1400,
      UNSIGNED_BYTE = 0x1401,
      SHORT = 0x1402,
      UNSIGNED_SHORT = 0x1403,
      INT = 0x1404,
      UNSIGNED_INT = 0x1405,
      FLOAT = 0x1406,
      BYTES_2 = 0x1407,
      BYTES_3 = 0x1408,
      BYTES_4 = 0x1409,
      DOUBLE = 0x140A,
    };

    template<typename _Type>
    DataType getDataType() { static_assert(false); }

    template<>
    constexpr DataType getDataType<float>() { return DataType::FLOAT; }

    template<>
    constexpr DataType getDataType<char>() { return DataType::BYTE; }

    template<>
    constexpr DataType getDataType<unsigned char>() { return DataType::UNSIGNED_BYTE; }

    template<>
    constexpr DataType getDataType<int>() { return DataType::INT; }

    template<>
    constexpr DataType getDataType<unsigned>() { return DataType::UNSIGNED_INT; }

    template<>
    constexpr DataType getDataType<short>() { return DataType::SHORT; }

    template<>
    constexpr DataType getDataType<unsigned short>() { return DataType::UNSIGNED_SHORT; }

  }
}
