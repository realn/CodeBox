#ifndef __CB_MATH_H__
#define __CB_MATH_H__

#include <glm/common.hpp>

namespace cb {
  template<typename _Type>
  const bool inRange(const _Type& x, const _Type& min, const _Type& max) {
    return min <= x && x <= max;
  }
}

#endif // !__CB_MATH_H__

