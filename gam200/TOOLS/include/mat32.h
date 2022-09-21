#pragma once

#include <iostream>
#include <vector>
#include "math.h"
#include "vec2.h"

namespace Math {
  struct Mat3;

  struct Mat32 { // Mat32 works the same as Mat3. Since the last column is always (0,0,1), it's removed for optimisation purposes.
    std::vector<std::vector<float>> mtx;

  public:
    Mat32(float x1, float y1, float z1, float x2, float y2, float z2);
    Mat32(const Vec2& col1, const Vec2& col2, const Vec2& col3);
    Mat32(const Mat32& mat);
    explicit Mat32(const Mat3& mat);
    Mat32(float i = 1.f, float x = 0.f, float y = 0.f);
    ~Mat32();
    Mat32& operator=(const Mat32& mat);
    std::vector<float>& operator[](short i) { return mtx[i]; }
    const std::vector<float>& operator[](short i) const { return mtx[i]; }
  private:
    void Init();
  };
  Vec2 operator*(const Mat32& m, const Vec2& v);
  Vec2 operator*(const Vec2& v, const Mat32& m);
  Mat32 operator*(const Mat32& m1, const Mat32& m2);
  std::ostream& operator<<(std::ostream& out, const Mat32& m);
}

