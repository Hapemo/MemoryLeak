#pragma once
#include <iostream>
#include "math.h"
#include "vec3.h"

namespace Math {
  struct Mat32;

  struct Mat3 {
    union {
      float mtx1[3][3];
      float mtx2[9];
    };

  public:
    Mat3(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
    Mat3(const Vec3& vct1, const Vec3& vct2, const Vec3& vct3);
    Mat3(const Mat3& mat);
    Mat3(float i = 1);
    explicit Mat3(const Mat32& mat);
    Mat3& operator=(const Mat3& mat);
    float* operator[](short idx) { return mtx1[idx]; }
    const float * operator[](short idx) const { return mtx1[idx]; }
    Mat3& Transpose();
    Mat3 Transposed() const;
    ~Mat3();
  };
  Vec3 operator*(const Mat3& lhs, const Vec3& rhs);
  Vec3 operator*(const Vec3& lhs, const Mat3& rhs);
  Mat3 operator*(const Mat3& lhs, const Mat3& rhs);
  std::ostream& operator<<(std::ostream& out, const Mat3& m);
}

