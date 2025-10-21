#pragma once

#ifndef VECTOR3F_H
#define VECTOR3F_H


class Vector3f {
public:
	Vector3f(float x, float y, float z);
	~Vector3f();
	Vector3f(const Vector3f& vector);

	float getX() const;
	float getY() const;
	float getZ() const;

	void operator+=(const Vector3f& vector);
	void operator-=(const Vector3f& vector);

	Vector3f operator+(const Vector3f& vector);
	Vector3f operator-(const Vector3f& vector);

	void operator/=(float f);
	void operator*=(float f);

	Vector3f operator/(float f);
	Vector3f operator*(float f);

	bool operator==(const Vector3f& vector);

	float length() const;

	Vector3f normalized();

	Vector3f dot(const Vector3f& vector);

	float dotProduct(const Vector3f& vector);

	Vector3f cross(const Vector3f& vector);

	float radAngle(const Vector3f& vector);

	void print();

private:
	float pX, pY, pZ;

};

#endif // !VECTOR3F_H
