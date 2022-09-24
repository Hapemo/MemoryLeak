#include "vec3.h"
#include "vec2.h"

namespace Math {
  Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

  Vec3::Vec3(float i) : x(i), y(i), z(i) {}

  Vec3::Vec3(const glm::vec3& v) : x(v.x), y(v.y), z(v.z) {}
  Vec3::Vec3(const Vec3& vct) : x(vct.x), y(vct.y), z(vct.z) {}
  Vec3::Vec3(const Vec2& v) : x(v.x), y(v.y), z(1) {}

  Vec3& Vec3::operator+=(const Vec3& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  Vec3& Vec3::operator-=(const Vec3& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  Vec3& Vec3::operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }

  Vec3& Vec3::operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }

  Vec3& Vec3::operator=(const Vec3& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }

  Vec3 Vec3::operator-() const {
    return { -x, -y, -z };
  }

  Vec3& Vec3::Normalize() {
    return *this /= this->Magnitude();
  }

  Vec3 Vec3::Normalized() const {
    return *this / this->Magnitude();
  }

  float Vec3::Magnitude() const {
    return sqrtf(x * x + y * y + z * z);
  }

  float Vec3::SqMagnitude() const {
    return x * x + y * y + z * z;
  }

  glm::vec3 Vec3::ToGLM() const
  {
      return glm::vec3(this->x, this->y, this->z);
  }

  Vec3::~Vec3() {}
  Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
    Vec3 temp = lhs;
    return temp += rhs;
  }

  Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
    Vec3 temp = lhs;
    return temp -= rhs;
  }

  Vec3 operator*(const Vec3& lhs, float rhs) {
    Vec3 temp = lhs;
    return temp *= rhs;
  }

  Vec3 operator*(float lhs, const Vec3& rhs) {
    return operator*(rhs, lhs);
  }

  Vec3 operator/(const Vec3& lhs, float rhs) {
    Vec3 temp = lhs;
    return temp /= rhs;
  }

  float Dot(const Vec3& lhs, const Vec3& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
  }

  Vec3 Cross(const Vec3& v1, const Vec3& v2) {
    Vec3 v{};
    v.x = v1.y * v2.z - v2.y * v1.z;
    v.y = v1.z * v2.x - v2.z * v1.x;
    v.z = v1.x * v2.y - v2.x * v1.y;
    return v;
  }

  float Distance(const Vec3& lhs, const Vec3& rhs) {
    return (lhs-rhs).Magnitude();
  }

  float SqDistance(const Vec3& lhs, const Vec3& rhs) {
    return (lhs - rhs).SqMagnitude();
  }

  std::ostream& operator<<(std::ostream& os, const Vec3& rhs) {
    os << '(' << rhs.x << ", " << rhs.y << ", " << rhs.z << ')';
    return os;
  }

}