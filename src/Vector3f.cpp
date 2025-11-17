#include "Vector3f.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

Vector3f::Vector3f(float x, float y, float z)
{
	pX = x;
	pY = y;
	pZ = z;
}

Vector3f::~Vector3f()
{
}

Vector3f::Vector3f(const Vector3f& vector)
{
	pX = vector.getX();
	pY = vector.getY();
	pZ = vector.getZ();
}

float Vector3f::getX() const
{
	return pX;
}

float Vector3f::getY() const
{
	return pY;
}

float Vector3f::getZ() const
{
	return pZ;
}

void Vector3f::operator+=(const Vector3f& vector)
{
	pX += vector.getX();
	pY += vector.getY();
	pZ += vector.getZ();
}

void Vector3f::operator-=(const Vector3f& vector)
{
	pX -= vector.getX();
	pY -= vector.getY();
	pZ -= vector.getZ();
}

Vector3f Vector3f::operator+(const Vector3f& vector) const
{
	float x = pX + vector.getX();
	float y = pY + vector.getY();
	float z = pZ + vector.getZ();
	return Vector3f(x, y, z);
}

Vector3f Vector3f::operator-(const Vector3f& vector) const
{
	float x = pX - vector.getX();
	float y = pY - vector.getY();
	float z = pZ - vector.getZ();
	return Vector3f(x, y, z);
}

void Vector3f::operator/=(float f)
{
	if (f == 0) throw std::invalid_argument("Vector can't be divided by zero");
	pX /= f;
	pY /= f;
	pZ /= f;
}

void Vector3f::operator*=(float f)
{
	pX *= f;
	pY *= f;
	pZ *= f;
}

Vector3f Vector3f::operator/(float f) const
{
	if (f == 0) throw std::invalid_argument("Vector can't be divided by zero");
	float x = pX / f;
	float y = pY / f;
	float z = pZ / f;
	return Vector3f(x, y, z);
}

Vector3f Vector3f::operator*(float f) const
{
	float x = pX * f;
	float y = pY * f;
	float z = pZ * f;
	return Vector3f(x, y, z);
}

bool Vector3f::operator==(const Vector3f& vector)
{
	if (getX() != vector.getX()) return false;
	if (getY() != vector.getY()) return false;
	if (getZ() != vector.getZ()) return false;
	return true;
}

float Vector3f::length() const
{
	return (float)sqrt((getX() * getX()) + (getY() * getY()) + (getZ() * getZ()));
}
Vector3f Vector3f::normalized()
{
	float l = length();
	if (l == 0) throw std::invalid_argument("Vector zero can't be normalized");
	float x = pX / l;
	float y = pY / l;
	float z = pZ / l;
	return Vector3f(x, y, z);
}

Vector3f Vector3f::dot(const Vector3f& vector) const
{
	float x = pX * vector.getX();
	float y = pY * vector.getY();
	float z = pZ * vector.getZ();
	return Vector3f(x, y, z);
}

float Vector3f::dotProduct(const Vector3f& vector) const
{
	Vector3f result = dot(vector);
	return result.getX() + result.getY() + result.getZ();
}

Vector3f Vector3f::cross(const Vector3f& vector) const
{
	float x = pY * vector.getZ() - pZ * vector.getY();
	float y = pZ * vector.getX() - pX * vector.getZ();
	float z = pX * vector.getY() - pY * vector.getX();
	return Vector3f(x, y, z);
}

float Vector3f::radAngle(const Vector3f& vector)
{
	float dotProd = dotProduct(vector);
	float lenA = length();
	float lenB = vector.length();
	float div = lenA * lenB;

	if (div == 0) throw std::invalid_argument("Can't calculate angle with vector zero");

	return std::acos(dotProd / div);
}


void Vector3f::print()
{
	std::cout << "(" << pX << ", " << pY << ", " << pZ << ")" << std::endl;
}
