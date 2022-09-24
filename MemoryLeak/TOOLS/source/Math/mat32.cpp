#include "mat32.h"
#include "mat3.h"
#include <iomanip>

namespace Math {
  void Mat32::Init() {
    mtx.resize(2);
    for (auto& row : mtx)
      row.resize(3);
  }

  Mat32::Mat32(float x1, float y1, float z1, float x2, float y2, float z2) {
    Init();
    mtx[0][0] = x1;
    mtx[0][1] = y1;
    mtx[0][2] = z1;
    mtx[1][0] = x2;
    mtx[1][1] = y2;
    mtx[1][2] = z2;
  }

  Mat32::Mat32(const Vec2& col1, const Vec2& col2, const Vec2& col3) {
    Init();
    mtx[0][0] = col1.x;
    mtx[1][0] = col1.y;
    mtx[0][1] = col2.x;
    mtx[1][1] = col2.y;
    mtx[0][2] = col3.x;
    mtx[1][2] = col3.y;
  }

  Mat32::Mat32(float i, float x, float y) {
    Init();
    mtx[0][0] = mtx[1][1] = i;
    mtx[0][1] = mtx[1][0] = 0;
    mtx[0][2] = x;
    mtx[1][2] = y;
  }

  Mat32::Mat32(const Mat3& mat) {
    Init();
    mtx[0][0] = mat.mtx2[0];
    mtx[0][1] = mat.mtx2[1];
    mtx[0][2] = mat.mtx2[2];
    mtx[1][0] = mat.mtx2[3];
    mtx[1][1] = mat.mtx2[4];
    mtx[1][2] = mat.mtx2[5];
  }

  Mat32::Mat32(const Mat32& mat) {
    Init();
    *this = mat;
  }

  Mat32& Mat32::operator=(const Mat32& mat) {
    this->mtx = mat.mtx;
    /*mtx[0][0] = mat.mtx[0][0];
    mtx[0][1] = mat.mtx[0][1];
    mtx[0][2] = mat.mtx[0][2];
    mtx[1][0] = mat.mtx[1][0];
    mtx[1][1] = mat.mtx[1][1];
    mtx[1][2] = mat.mtx[1][2];*/
    return *this;
  }

  Mat32::~Mat32() {}
  Vec2 operator*(const Mat32& m, const Vec2& v) {
    float x{ m[0][0] * v.x + m[0][1] * v.y + m[0][2] };
    float y{ m[1][0] * v.x + m[1][1] * v.y + m[1][2] };
    return { x, y };
  }

  Vec2 operator*(const Vec2& v, const Mat32& m) {
    return operator*(m, v);
  }

  Mat32 operator*(const Mat32& m1, const Mat32& m2) {
    Mat32 temp{ m1 };
    temp[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0];
    temp[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1];
    temp[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2];
    temp[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0];
    temp[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1];
    temp[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2];
    return temp;
  }

  std::ostream& operator<<(std::ostream& out, const Mat32& m) {
    out << std::fixed << std::setprecision(7);
    out << "| " << m[0][0] << " , " << m[0][1] << " , " << m[0][2] << " |" << '\n';
    out << "| " << m[1][0] << " , " << m[1][1] << " , " << m[1][2] << " |" << '\n';
    return out;
  }
}