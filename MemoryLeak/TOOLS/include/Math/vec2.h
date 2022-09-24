#pragma once
#include <iostream>
#include <glm/glm.hpp>

namespace Math {
  struct Vec3;

  struct Vec2 {
    union {
      float x;
      float r;
    };
    union {
      float y;
      float g;
    };

    Vec2(float x, float y);
    Vec2(float i = 0);
    Vec2(const Vec2& v);
    explicit Vec2(glm::vec2);
    explicit Vec2(const Vec3& v);
    ~Vec2();
    Vec2& operator+=(const Vec2& rhs);
    Vec2& operator-=(const Vec2& rhs);
    Vec2& operator*=(float rhs);
    Vec2& operator/=(float rhs);
    Vec2& operator=(const Vec2& rhs);
    Vec2 operator-() const;
    Vec2& Normalize();
    Vec2 Normalized() const;
    float Magnitude() const;
    float SqMagnitude() const;
    glm::vec2 ToGLM() const;
    /*
    Vec3(glm::vec3);
    glm::vec3 operator glm::vec3() const;
    Vec3 &operator=(const glm::vec3 &rhs);
    */
  };
  Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
  Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
  Vec2 operator*(const Vec2& lhs, float rhs);
  Vec2 operator*(float lhs, const Vec2& rhs);
  Vec2 operator/(const Vec2& lhs, float rhs);
  float Dot(const Vec2& lhs, const Vec2& rhs);
  float Distance(const Vec2& lhs, const Vec2& rhs);
  float SqDistance(const Vec2& lhs, const Vec2& rhs);
  std::ostream& operator<<(std::ostream& os, const Vec2& rhs);
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

