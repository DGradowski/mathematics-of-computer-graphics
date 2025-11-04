#define _USE_MATH_DEFINES
#include <cmath>
#include "Matrix4x4.h"
#include <cstring>
#include <iostream>
#include <iomanip>

Matrix4x4::Matrix4x4()
{
	LoadIdentity();
}

Matrix4x4::Matrix4x4(float e0, float e1, float e2, float e3,
					 float e4, float e5, float e6, float e7,
					 float e8, float e9, float e10, float e11,
					 float e12, float e13, float e14, float e15)
{
	entries[0] = e0; entries[1] = e1; entries[2] = e2; entries[3] = e3;
	entries[4] = e4; entries[5] = e5; entries[6] = e6; entries[7] = e7;
	entries[8] = e8; entries[9] = e9; entries[10] = e10; entries[11] = e11;
	entries[12] = e12; entries[13] = e13; entries[14] = e14; entries[15] = e15;
}

Matrix4x4::Matrix4x4(const float* f)
{
	memcpy(entries, f, 16 * sizeof(float));
}

Matrix4x4::Matrix4x4(const Matrix4x4& mat)
{
	memcpy(entries, mat.entries, 16 * sizeof(float));
}

Matrix4x4::~Matrix4x4()
{
}

void Matrix4x4::LoadIdentity()
{
	memset(entries, 0, 16 * sizeof(float));
	entries[0] = 1.0f;
	entries[5] = 1.0f;
	entries[10] = 1.0f;
	entries[15] = 1.0f;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& mat) const
{
	return Matrix4x4(entries[0] + mat.entries[0], entries[1] + mat.entries[1], entries[2] + mat.entries[2], entries[3] + mat.entries[3],
					 entries[4] + mat.entries[4], entries[5] + mat.entries[5], entries[6] + mat.entries[6], entries[7] + mat.entries[7],
					 entries[8] + mat.entries[8], entries[9] + mat.entries[9], entries[10] + mat.entries[10], entries[11] + mat.entries[11],
					 entries[12] + mat.entries[12], entries[13] + mat.entries[13], entries[14] + mat.entries[14], entries[15] + mat.entries[15]);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& mat) const
{
	return Matrix4x4(entries[0] - mat.entries[0], entries[1] - mat.entries[1], entries[2] - mat.entries[2], entries[3] - mat.entries[3],
					 entries[4] - mat.entries[4], entries[5] - mat.entries[5], entries[6] - mat.entries[6], entries[7] - mat.entries[7],
					 entries[8] - mat.entries[8], entries[9] - mat.entries[9], entries[10] - mat.entries[10], entries[11] - mat.entries[11],
					 entries[12] - mat.entries[12], entries[13] - mat.entries[13], entries[14] - mat.entries[14], entries[15] - mat.entries[15]);
}

Matrix4x4 Matrix4x4::operator*(const float f) const
{
	return Matrix4x4(entries[0] * f, entries[1] * f, entries[2] * f, entries[3] * f,
					 entries[4] * f, entries[5] * f, entries[6] * f, entries[7] * f,
					 entries[8] * f, entries[9] * f, entries[10] * f, entries[11] * f,
					 entries[12] * f, entries[13] * f, entries[14] * f, entries[15] * f);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const
{
	Matrix4x4 result;
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			float sum = 0.0f;
			for (int k = 0; k < 4; ++k) {
				sum += entries[k * 4 + r] * mat.entries[c * 4 + k];
			}
			result.entries[c * 4 + r] = sum;
		}
	}
	return result;
}

Vector4f Matrix4x4::operator*(const Vector4f& v) const
{
	Vector4f res;
	res.x = entries[0] * v.x + entries[4] * v.y + entries[8] * v.z + entries[12] * v.w;
	res.y = entries[1] * v.x + entries[5] * v.y + entries[9] * v.z + entries[13] * v.w;
	res.z = entries[2] * v.x + entries[6] * v.y + entries[10] * v.z + entries[14] * v.w;
	res.w = entries[3] * v.x + entries[7] * v.y + entries[11] * v.z + entries[15] * v.w;
	return res;
}

Matrix4x4 Matrix4x4::getTranspose() const
{
	Matrix4x4 result;
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			result.entries[c * 4 + r] = entries[r * 4 + c];
		}
	}
	return result;
}


void Matrix4x4::SetTranslationPart(const Vector3f& translation)
{
	entries[12] = translation.getX();
	entries[13] = translation.getY();
	entries[14] = translation.getZ();
}

void Matrix4x4::SetScale(const Vector3f& scaleFactor)
{
	LoadIdentity();
	entries[0] = scaleFactor.getX();
	entries[5] = scaleFactor.getY();
	entries[10] = scaleFactor.getZ();
}

void Matrix4x4::SetUniformScale(const float scaleFactor)
{
	LoadIdentity();
	entries[0] = entries[5] = entries[10] = scaleFactor;
}

void Matrix4x4::SetRotationAxis(const double angle, const Vector3f& axis)
{
	Vector3f u = Vector3f(axis.getX(), axis.getY(), axis.getZ()).normalized();

	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);
	float oneMinusCosAngle = 1.0f - cosAngle;

	LoadIdentity();

	float ux = u.getX();
	float uy = u.getY();
	float uz = u.getZ();

	entries[0] = (ux * ux) + cosAngle * (1 - (ux * ux));
	entries[1] = (ux * uy) * oneMinusCosAngle + sinAngle * uz;
	entries[2] = (ux * uz) * oneMinusCosAngle - sinAngle * uy;

	entries[4] = (ux * uy) * oneMinusCosAngle - sinAngle * uz;
	entries[5] = (uy * uy) + cosAngle * (1 - (uy * uy));
	entries[6] = (uy * uz) * oneMinusCosAngle + sinAngle * ux;

	entries[8] = (ux * uz) * oneMinusCosAngle + sinAngle * uy;
	entries[9] = (uy * uz) * oneMinusCosAngle - sinAngle * ux;
	entries[10] = (uz * uz) + cosAngle * (1 - (uz * uz));
}

void Matrix4x4::SetRotationX(const double angle)
{
	LoadIdentity();
	entries[5] = (float)cos(M_PI * angle / 180);
	entries[6] = (float)sin(M_PI * angle / 180);
	entries[9] = -entries[6];
	entries[10] = entries[5];
}

void Matrix4x4::SetRotationY(const double angle)
{
	LoadIdentity();
	entries[0] = (float)cos(M_PI * angle / 180);
	entries[2] = -(float)sin(M_PI * angle / 180);
	entries[8] = -entries[2];
	entries[10] = entries[0];
}

void Matrix4x4::SetRotationZ(const double angle)
{
	LoadIdentity();
	entries[0] = (float)cos(M_PI * angle / 180);
	entries[1] = (float)sin(M_PI * angle / 180);
	entries[4] = -entries[1];
	entries[5] = entries[0];
}

void Matrix4x4::print() const
{
	std::cout << std::fixed << std::setprecision(3);
	for (int r = 0; r < 4; ++r) {
		std::cout << "[ ";
		for (int c = 0; c < 4; ++c) {
			std::cout << std::setw(8) << entries[c * 4 + r] << " ";
		}
		std::cout << "]" << std::endl;
	}
	std::cout << std::endl;
}