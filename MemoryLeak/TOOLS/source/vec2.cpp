#include "vec2.h"
#include "vec3.h"

namespace Math {
  Vec2::Vec2(float x, float y) : x(x), y(y) {}

  Vec2::Vec2(float i) : x(i), y(i) {}

  Vec2::Vec2(const Vec2& v) : x(v.x), y(v.y) {}

  Vec2::Vec2(const Vec3& v) : x(v.x), y(v.y) {}
  
  Vec2::~Vec2() {} 

  Vec2& Vec2::operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  Vec2& Vec2::operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  Vec2& Vec2::operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
  }

  Vec2& Vec2::operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    return *this;
  }

  Vec2& Vec2::operator=(const Vec2& rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

  Vec2 Vec2::operator-() const {
    return { -x, -y };
  }

  Vec2& Vec2::Normalize() {
    return *this /= this->Magnitude();
  }

  Vec2 Vec2::Normalized() const {
    return *this / this->Magnitude();
  }

  float Vec2::Magnitude() const {
    return sqrtf(x * x + y * y);
  }

  float Vec2::SqMagnitude() const {
    return x * x + y * y;
  }

  Vec2 operator+(const Vec2& lhs, const Vec2& rhs) {
    Vec2 temp = lhs;
    return temp += rhs;
  }

  Vec2 operator-(const Vec2& lhs, const Vec2& rhs) {
    Vec2 temp = lhs;
    return temp -= rhs;
  }

  Vec2 operator*(const Vec2& lhs, float rhs) {
    Vec2 temp = lhs;
    return temp *= rhs;
  }

  Vec2 operator*(float lhs, const Vec2& rhs) {
    return operator*(rhs, lhs);
  }

  Vec2 operator/(const Vec2& lhs, float rhs) {
    Vec2 temp = lhs;
    return temp /= rhs;
  }

  float Dot(const Vec2& lhs, const Vec2& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }

  float Distance(const Vec2& lhs, const Vec2& rhs) {
    return (lhs - rhs).Magnitude();
  }

  float SqDistance(const Vec2& lhs, const Vec2& rhs) {
    return (lhs-rhs).SqMagnitude();
  }

  std::ostream& operator<<(std::ostream& os, const Vec2& rhs) {
    os << '(' << rhs.x << ", " << rhs.y << ')';
    return os;
  }

}