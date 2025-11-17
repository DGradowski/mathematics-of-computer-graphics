#include <iostream>
#include <iomanip>
#include <cmath>
#include "Matrix4x4.h"
#include "Vector4f.h"
#include "Vector3f.h"
#include "Quaterion.h"

int main()
{
	std::cout << "ZADANIE 3 - Kwateriony\n" << std::endl;
	Quaterion q1(1, Vector3f(2, 3, 4));
	Quaterion q2(0.5, Vector3f(-1, 2, -0.5));

	std::cout << "==== Zad 3.2 ====" << std::endl;
	std::cout << "q1 + q2 = ";
	(q1 + q2).print();
	std::cout << std::endl;

	std::cout << "q1 - q2 = ";
	(q1 - q2).print();
	std::cout << std::endl;


	std::cout << "q1 * q2 = ";
	(q1 * q2).print();
	std::cout << std::endl;


	std::cout << "q2 * q1 = ";
	(q2 * q1).print();
	std::cout << std::endl;


	std::cout << "q1 / q2 = ";
	(q1 / q2).print();
	std::cout << std::endl;
	std::cout << "==== Zad 3.3 ====" << std::endl;

	Vector3f p(-1, -1, -1);
	Quaterion q3(( -1.f * (sqrt(2.f) / 2.f)), Vector3f((sqrt(2.f) / 2.f), 0.f, 0.f));
	q3.rotate(p).print();
	return 0;
}