#include "stdafx.h"
#include <CBMath/Rect.h>

namespace cb {
  CRect::CRect() {}

  CRect::CRect(const CRect & other) 
    : Min(other.Min), Max(other.Max)
  {}

  CRect::CRect(const glm::vec2 & min, const glm::vec2 & max) 
    : Min(min), Max(max)
  {}

  bool CRect::Contains(const CRect & other) const {
    return
      glm::all(glm::lessThanEqual(Min, other.Max)) &&
      glm::all(glm::greaterThanEqual(Max, other.Max));
  }

  bool CRect::Contains(const glm::vec2 & pos) const {
    return
      glm::all(glm::lessThanEqual(Min, pos)) &&
      glm::all(glm::greaterThanEqual(Max, pos));
  }

  bool CRect::Intersects(const CRect & other) const {
    return !(
      glm::any(glm::lessThan(Max, other.Min)) ||
      glm::any(glm::greaterThan(Min, other.Max))
      );
  }

  CRect CRect::operator+(const CRect & other) const {
    return CRect(
      glm::min(Min, other.Min),
      glm::max(Max, other.Max)
    );
  }

  bool CRect::operator==(const CRect & other) const {
    return Min == other.Min && Max == other.Max;
  }

  bool CRect::operator!=(const CRect & other) const {
    return !(*this == other);
  }

  bool CRect::operator<(const CRect & other) const {
    return glm::all(glm::lessThan(GetSize(), other.GetSize()));
  }

  bool CRect::operator<=(const CRect & other) const {
    return glm::all(glm::lessThanEqual(GetSize(), other.GetSize()));
  }

  bool CRect::operator>(const CRect & other) const {
    return glm::all(glm::greaterThan(GetSize(), other.GetSize()));
  }

  bool CRect::operator>=(const CRect & other) const {
    return glm::all(glm::greaterThanEqual(GetSize(), other.GetSize()));
  }

  void CRect::operator=(const CRect & other) {
    Min = other.Min;
    Max = other.Max;
  }

  void CRect::operator+=(const CRect & other) {
    *this = *this + other;
  }
}
