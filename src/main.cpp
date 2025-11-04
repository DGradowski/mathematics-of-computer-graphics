#include <iostream>
#include <iomanip>
#include "Matrix4x4.h"
#include "Vector4f.h"
#include "Vector3f.h"

int main()
{
	std::cout << "ZADANIE 2\n" << std::endl;

	std::cout << "2.1 Konstruktory i LoadIdentity\n" << std::endl;
	Matrix4x4 m_ident;
	std::cout << "Test LoadIdentity() (konstruktor domyslny):" << std::endl;
	m_ident.print();

	Matrix4x4 m_copy(m_ident);
	std::cout << "Test konstruktora kopiujacego:" << std::endl;
	m_copy.print();

	m_copy.entries[0] = 5.0f;
	m_ident.LoadIdentity();
	std::cout << "Test jawnego wywolania LoadIdentity() (na m_ident):" << std::endl;
	m_ident.print();


	std::cout << "2.2 Operatory arytmetyczne\n" << std::endl;
	Matrix4x4 m1;
	m1.SetTranslationPart(Vector3f(1.0f, 2.0f, 3.0f));
	std::cout << "M1 (Translacja o 1,2,3):" << std::endl;
	m1.print();

	Matrix4x4 m2;
	m2.SetScale(Vector3f(2.0f, 2.0f, 2.0f));
	std::cout << "M2 (Skalowanie x2):" << std::endl;
	m2.print();

	std::cout << "M1 + M2" << std::endl;
	(m1 + m2).print();

	std::cout << "M1 - M2" << std::endl;
	(m1 - m2).print();

	std::cout << "M1 * 3.0" << std::endl;
	(m1 * 3.0f).print();

	std::cout << "2.3 Operatory mnozenia\n" << std::endl;
	std::cout << "M1 * M2 (Mnozenie macierzy)" << std::endl;
	(m1 * m2).print();

	Vector4f v_test(1.0f, 1.0f, 1.0f, 1.0f);
	std::cout << "Wektor testowy V (1,1,1,1):" << std::endl;
	v_test.print();

	std::cout << "M1 * V (Transformacja wektora przez translacje)" << std::endl;
	(m1 * v_test).print();

	std::cout << "M2 * V (Transformacja wektora przez skale)" << std::endl;
	(m2 * v_test).print();

	std::cout << "2.4 Metody (Transpozycja)\n" << std::endl;
	m1.entries[1] = 7.0f;
	std::cout << "Zmodyfikowana M1 (dla testu transpozycji):" << std::endl;
	m1.print();
	std::cout << "Transpozycja M1 (M1.getTranspose())" << std::endl;
	m1.getTranspose().print();

	std::cout << "2.5 Metody (Transformacje)\n" << std::endl;
	Matrix4x4 m_transf;

	std::cout << "SetUniformScale(5.0f):" << std::endl;
	m_transf.SetUniformScale(5.0f);
	m_transf.print();

	std::cout << "SetRotationX(90):" << std::endl;
	m_transf.SetRotationX(90.0);
	m_transf.print();

	std::cout << "SetRotationY(90):" << std::endl;
	m_transf.SetRotationY(90.0);
	m_transf.print();

	std::cout << "SetRotationZ(90):" << std::endl;
	m_transf.SetRotationZ(90.0);
	m_transf.print();

	std::cout << "SetRotationAxis(45 stopni, os Y):" << std::endl;
	m_transf.SetRotationAxis(45.0, Vector3f(0.0f, 1.0f, 0.0f));
	m_transf.print();


	std::cout << "ZADANIE 3: OBROT WEKTORA\n" << std::endl;

	Vector4f v(1.0f, 0.0f, 0.0f, 1.0f);
	Matrix4x4 rotY;
	rotY.SetRotationY(90.0);

	std::cout << "Wektor wejsciowy V:" << std::endl;
	v.print();

	std::cout << "Macierz obrotu RotY(90):" << std::endl;
	rotY.print();

	Vector4f result = rotY * v;

	std::cout << "Wektor wynikowy (RotY * V):" << std::endl;
	result.print();

	std::cout << "ZADANIE 4: BRAK PRZEMIENNOSCI MNOZENIA\n" << std::endl;

	Matrix4x4 T;
	T.SetTranslationPart(Vector3f(5.0f, 0.0f, 0.0f));

	Matrix4x4 R;
	R.SetRotationZ(90.0);

	std::cout << "Macierz Translacji T (o 5 w X):" << std::endl;
	T.print();
	std::cout << "Macierz Rotacji R (o 90 w Z):" << std::endl;
	R.print();

	Matrix4x4 A = T * R;
	Matrix4x4 B = R * T;

	std::cout << "Wynik A = T * R (Obrot -> Translacja):" << std::endl;
	A.print();

	std::cout << "Wynik B = R * T (Translacja -> Obrot):" << std::endl;
	B.print();

	std::cout << "Jak widac, macierz A != B." << std::endl;
	std::cout << "Dowodzi to, ze mnozenie macierzy nie jest przemienne (MXN != NXM)." << std::endl;

	return 0;
}