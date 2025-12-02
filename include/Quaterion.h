#pragma once

#ifndef QUATERION_H
#define QUATERION_H

#include "Vector3f.h"

class Quaterion
{
public:
	Quaterion(float a, Vector3f vector);
	~Quaterion();

	Quaterion operator+(const Quaterion& quaterion);
	Quaterion operator-(const Quaterion& quaterion);
	Quaterion operator/(const Quaterion& quaterion);
	Quaterion operator*(const Quaterion& quaterion);

	float getScalar() const;
	const Vector3f& getVector() const;
	Quaterion conjugate();
	float magnitude() const;
	Quaterion normalized() const;
	Vector3f rotate(Vector3f vector);
	void print();

private:
	float scalar;
	Vector3f vector;
};

#endif // QUATERION_H
