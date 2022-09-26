#include <glm/glm.hpp>
#include "vec2.h"
#include "vec3.h"

namespace Math {
  Vec2::Vec2(float _x, float _y) : x(_x), y(_y) {}

  Vec2::Vec2(float _i) : x(_i), y(_i) {}

  Vec2::Vec2(const Vec2& _v) : x(_v.x), y(_v.y) {}

  Vec2::Vec2(glm::vec2 _v) : x(_v.x), y(_v.y) {}

  Vec2::Vec2(const Vec3& _v) : x(_v.x), y(_v.y) {}
  
  Vec2::~Vec2() {} 

  Vec2& Vec2::operator+=(const Vec2& _rhs) {
    x += _rhs.x;
    y += _rhs.y;
    return *this;
  }

  Vec2& Vec2::operator-=(const Vec2& _rhs) {
    x -= _rhs.x;
    y -= _rhs.y;
    return *this;
  }

  Vec2& Vec2::operator*=(float _rhs) {
    x *= _rhs;
    y *= _rhs;
    return *this;
  }

  Vec2& Vec2::operator/=(float _rhs) {
    x /= _rhs;
    y /= _rhs;
    return *this;
  }

  bool Vec2::operator==(const Vec2& _rhs) {
      return (this->x == _rhs.x && this->y == _rhs.y);
  }

  Vec2& Vec2::operator=(const Vec2& _rhs) {
    x = _rhs.x;
    y = _rhs.y;
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

  glm::vec2 Vec2::ToGLM() const
  {
      return glm::vec2(this->x, this->y);
  }

  Vec2 operator+(const Vec2& _lhs, const Vec2& _rhs) {
    Vec2 temp = _lhs;
    return temp += _rhs;
  }

  Vec2 operator-(const Vec2& _lhs, const Vec2& _rhs) {
    Vec2 temp = _lhs;
    return temp -= _rhs;
  }

  Vec2 operator*(const Vec2& _lhs, float _rhs) {
    Vec2 temp = _lhs;
    return temp *= _rhs;
  }

  Vec2 operator*(float _lhs, const Vec2& _rhs) {
    return operator*(_rhs, _lhs);
  }

  Vec2 operator/(const Vec2& _lhs, float _rhs) {
    Vec2 temp = _lhs;
    return temp /= _rhs;
  }

  float Dot(const Vec2& _lhs, const Vec2& _rhs) {
    return _lhs.x * _rhs.x + _lhs.y * _rhs.y;
  }

  float Distance(const Vec2& _lhs, const Vec2& _rhs) {
    return (_lhs - _rhs).Magnitude();
  }

  float SqDistance(const Vec2& _lhs, const Vec2& _rhs) {
    return (_lhs-_rhs).SqMagnitude();
  }

  std::ostream& operator<<(std::ostream& os, const Vec2& _rhs) {
    os << '(' << _rhs.x << ", " << _rhs.y << ')';
    return os;
  }

}