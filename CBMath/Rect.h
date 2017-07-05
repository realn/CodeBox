#ifndef __CB_MATH_RECT_H__
#define __CB_MATH_RECT_H__

#include <glm/fwd.hpp>

namespace cb {
  class CRect {
  public:
    glm::vec2 Min;
    glm::vec2 Max;

    CRect();
    CRect(const CRect& other);
    CRect(const glm::vec2& min, const glm::vec2& max);

    glm::vec2 GetSize() const { return Max - Min; }
    float GetWidth() const { return Max.x - Min.x; }
    float GetHeight() const { return Max.y - Min.y; }
    glm::vec2 GetMinXMaxY() const { return glm::vec2(Min.x, Max.y); }
    glm::vec2 GetMaxXMinY() const { return glm::vec2(Max.x, Min.y); }

    bool Contains(const CRect& other) const;
    bool Contains(const glm::vec2& pos) const;

    bool Intersects(const CRect& other) const;

    CRect operator+(const CRect& other) const;

    bool operator==(const CRect& other) const;
    bool operator!=(const CRect& other) const;
    bool operator<(const CRect& other) const;
    bool operator<=(const CRect& other) const;
    bool operator>(const CRect& other) const;
    bool operator>=(const CRect& other) const;

    void operator=(const CRect& other);
    void operator+=(const CRect& other);
  };
}

#endif // !__CB_MATH_RECT_H__

