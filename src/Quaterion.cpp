#include "Quaterion.h"
#include <cmath>
#include <iostream>

Quaterion::Quaterion(float scalar, Vector3f vector) : scalar(scalar), vector(vector)
{
	
}

Quaterion::~Quaterion()
{

}

Quaterion Quaterion::operator+(const Quaterion& quaterion)
{
	float a = scalar + quaterion.getScalar();
	Vector3f v = vector + quaterion.getVector();
	return (Quaterion(a, v));
}

Quaterion Quaterion::operator-(const Quaterion& quaterion)
{
	float a = scalar - quaterion.getScalar();
	Vector3f v = vector - quaterion.getVector();
	return (Quaterion(a, v));
}

Quaterion Quaterion::operator/(const Quaterion& quaterion)
{
	Vector3f v1 = vector;
	Vector3f v2 = quaterion.getVector();
	float a1 = scalar;
	float a2 = quaterion.getScalar();

	float a = (a1 * a2 + v1.dotProduct(v2)) / (a2 * a2 + v2.dotProduct(v2));
	Vector3f v = (v2 * (-1 * a1) + (v1 * a2) - v1.cross(v2)) / (a2 * a2 + v2.dotProduct(v2));

	return Quaterion(a, v);
}

Quaterion Quaterion::operator*(const Quaterion& quaterion)
{
	float a = scalar * quaterion.getScalar() - vector.dotProduct(quaterion.getVector());
	Vector3f v = (quaterion.getVector() * scalar) + (vector * quaterion.getScalar()) + (vector.cross(quaterion.getVector()));
	return (Quaterion(a, v));
}

Quaterion Quaterion::conjugate()
{
	return Quaterion(scalar, vector * -1);
}

float Quaterion::magnitude() const
{
	float squaredNorm = scalar * scalar + vector.dotProduct(vector);
	return sqrt(squaredNorm);
}

Quaterion Quaterion::normalized() const
{
	float mag = magnitude();

	if (mag > 1e-6f)
	{
		float invMag = 1.0f / mag;
		return Quaterion(scalar * invMag, vector * invMag);
	}
	return Quaterion(1.0f, vector * 0.0f);
}

Vector3f Quaterion::rotate(Vector3f vector)
{
	Quaterion con = this->conjugate();
	Quaterion v(0, vector);
	Quaterion rotated = this->normalized() * v * con.normalized();
	return rotated.getVector();
}

float Quaterion::getScalar() const
{
	return scalar;
}

const Vector3f& Quaterion::getVector() const
{
	return vector;
}

void Quaterion::print()
{
	std::cout << "(" << scalar << ", " << vector.getX() << "i, " << vector.getY() << "j, " << vector.getZ() << "k)";
}
