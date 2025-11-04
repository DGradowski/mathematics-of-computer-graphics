#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Vector3f.h"
#include "Vector4f.h"

class Matrix4x4
{
public:
    float entries[16];

    Matrix4x4();
    Matrix4x4(float e0, float e1, float e2, float e3,
              float e4, float e5, float e6, float e7,
              float e8, float e9, float e10, float e11,
              float e12, float e13, float e14, float e15);
    Matrix4x4(const float* f);
    Matrix4x4(const Matrix4x4& mat);
    ~Matrix4x4();

    Matrix4x4 operator+(const Matrix4x4& mat) const;
    Matrix4x4 operator-(const Matrix4x4& mat) const;
    Matrix4x4 operator*(const float f) const;
    Matrix4x4 operator*(const Matrix4x4& mat) const;
    Vector4f operator*(const Vector4f& v) const;

    void LoadIdentity();
    Matrix4x4 getTranspose() const;

    void SetTranslationPart(const Vector3f& translation);
    void SetScale(const Vector3f& scaleFactor);
    void SetUniformScale(const float scaleFactor);

    void SetRotationAxis(const double angle, const Vector3f& axis);
    void SetRotationX(const double angle);
    void SetRotationY(const double angle);
    void SetRotationZ(const double angle);

    void print() const;
};

#endif // MATRIX4X4_H