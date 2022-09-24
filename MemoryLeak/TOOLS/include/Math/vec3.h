#pragma once
#include <iostream>
#include <glm/glm.hpp>

namespace Math {
  struct Vec2;

  struct Vec3 {
    union {
      float x;
      float r;
    };
    union {
      float y;
      float g;
    };
    union {
      float z;
      float b;
    };

    Vec3(float x, float y, float z);
    Vec3(float i = 0);
    Vec3(const Vec3& vct);
    explicit Vec3(const glm::vec3& v);
    explicit Vec3(const Vec2& v);
    Vec3& operator+=(const Vec3& rhs);
    Vec3& operator-=(const Vec3& rhs);
    Vec3& operator*=(float rhs);
    Vec3& operator/=(float rhs);
    Vec3& operator=(const Vec3& rhs);
    Vec3 operator-() const;
    Vec3& Normalize();
    Vec3 Normalized() const;
    float Magnitude() const;
    float SqMagnitude() const;
    ~Vec3();
    /*
    Vec3(glm::vec3);
    glm::vec3 operator glm::vec3() const;
    Vec3 &operator=(const glm::vec3 &rhs);
    */
  };
  Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
  Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
  Vec3 operator*(const Vec3& lhs, float rhs);
  Vec3 operator*(float lhs, const Vec3& rhs);
  Vec3 operator/(const Vec3& lhs, float rhs);
  float Dot(const Vec3& lhs, const Vec3& rhs);
  Vec3 Cross(const Vec3& v1, const Vec3& v2);
  float Distance(const Vec3& lhs, const Vec3& rhs);
  float SqDistance(const Vec3& lhs, const Vec3& rhs);
  std::ostream& operator<<(std::ostream& os, const Vec3& rhs);
  /*
  Vec3 operator+(const Vec3 &lhs, const glm::vec3 &rhs);
  Vec3 operator+(const glm::vec3 &lhs, const Vec3 &rhs);
  Vec3 operator-(const Vec3 &lhs, const glm::vec3 &rhs);
  Vec3 operator-(const glm::vec3 &lhs, const Vec3 &rhs);
  float Dot(const Vec3 &lhs, const glm::vec3 &rhs);
  float Dot(const glm::vec3 &lhs, const Vec3 &rhs);
  float Distance(const Vec3 &lhs, const glm::vec3 &rhs);
  float Distance(const glm::vec3 &lhs, const Vec3 &rhs);
  float SqDistance(const Vec3 &lhs, const glm::vec3 &rhs);
  float SqDistance(const glm::vec3 &lhs, const Vec3 &rhs);
  */
}
