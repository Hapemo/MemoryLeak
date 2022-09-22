#include <iomanip>
#include "mat3.h"
#include "mat32.h"

namespace Math {
  Mat3::Mat3(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
    mtx2[0] = x1;
    mtx2[1] = y1;
    mtx2[2] = z1;
    mtx2[3] = x2;
    mtx2[4] = y2;
    mtx2[5] = z2;
    mtx2[6] = x3;
    mtx2[7] = y3;
    mtx2[8] = z3;
  }

  Mat3::Mat3(const Vec3& vct1, const Vec3& vct2, const Vec3& vct3) {
    mtx2[0] = vct1.x;
    mtx2[1] = vct1.y;
    mtx2[2] = vct1.z;
    mtx2[3] = vct2.x;
    mtx2[4] = vct2.y;
    mtx2[5] = vct2.z;
    mtx2[6] = vct3.x;
    mtx2[7] = vct3.y;
    mtx2[8] = vct3.z;
  }

  Mat3::Mat3(const Mat3& mat) {
    for (int i = 0; i < 9; ++i) {
      mtx2[i] = mat.mtx2[i];
    }
  }

  Mat3::Mat3(float i) {
    mtx2[0] = mtx2[4] = mtx2[8] = i;
    mtx2[1] = mtx2[2] = mtx2[3] = mtx2[5] = mtx2[6] = mtx2[7] = 0;
  }

  Mat3::Mat3(const Mat32& mat) {
    mtx1[0][0] = mat[0][0];
    mtx1[0][1] = mat[0][1];
    mtx1[0][2] = mat[0][2];
    mtx1[1][0] = mat[1][0];
    mtx1[1][1] = mat[1][1];
    mtx1[1][2] = mat[1][2];
    mtx1[2][0] = 0;
    mtx1[2][1] = 0;
    mtx1[2][2] = 1;
  }

  Mat3& Mat3::operator=(const Mat3& mat) {
    for (int i = 0; i < 9; ++i) {
      this->mtx2[i] = mat.mtx2[i];
    }
    return *this;
  }

  Mat3& Mat3::Transpose() {
    Mat3 temp = *this;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) {
        temp.mtx1[j][i] = mtx1[i][j];
      }
    return *this = temp;
  }

  Mat3 Mat3::Transposed() const {
    Mat3 temp = *this;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) {
        temp.mtx1[j][i] = mtx1[i][j];
      }
    return temp;
  }

  Mat3::~Mat3() {}
  Vec3 operator*(const Mat3& lhs, const Vec3& rhs) {
    float x = lhs.mtx2[0] * rhs.x + lhs.mtx2[3] * rhs.y + lhs.mtx2[6] * rhs.z;
    float y = lhs.mtx2[1] * rhs.x + lhs.mtx2[4] * rhs.y + lhs.mtx2[7] * rhs.z;
    float z = lhs.mtx2[2] * rhs.x + lhs.mtx2[5] * rhs.y + lhs.mtx2[8] * rhs.z;
    return { x, y, z };
  }

  Vec3 operator*(const Vec3& lhs, const Mat3& rhs) {
    return operator*(rhs, lhs);
  }

  Mat3 operator*(const Mat3& lhs, const Mat3& rhs) {
    Mat3 temp = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) {
        temp.mtx1[i][j] = 0;
        for (int k = 0; k < 3; k++) {
          temp.mtx1[i][j] += lhs.mtx1[i][k] * rhs.mtx1[k][j];
        }
      }
    return temp;
  }

  std::ostream& operator<<(std::ostream& out, const Mat3& m) {
    out << std::fixed << std::setprecision(7);
    out << "| " << m[0][0] << " , " << m[0][1] << " , " << m[0][2] << " |" << '\n';
    out << "| " << m[1][0] << " , " << m[1][1] << " , " << m[1][2] << " |" << '\n';
    out << "| " << m[2][0] << " , " << m[2][1] << " , " << m[2][2] << " |" << '\n';
    return out;
  }
}