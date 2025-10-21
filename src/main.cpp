#include <iostream>
#include "Vector3f.h"

int main()
{
    // Zad1 - implementacja jest

    // Zad2

    std::cout << "Zad 2" << std::endl;

    Vector3f a = Vector3f(1, 2, 3);
    Vector3f b = Vector3f(4, 5, 6);

    if (a + b == b + a) std::cout << "Dodawanie jest przemienne" << std::endl;
    else std::cout << "Dodawanie nie jest przemienne" << std::endl;
    (a + b).print();
    (b + a).print();

    // Zad3
    std::cout << "Zad 3" << std::endl;

    Vector3f c = Vector3f(0, 3, 0);
    Vector3f d = Vector3f(5, 5, 0);

    std::cout << "Kat miedzy wektorem c i d: " << c.radAngle(d) << std::endl;

    // Zad4
    std::cout << "Zad 4" << std::endl;
    Vector3f e = Vector3f(4, 5, 1);
    Vector3f f = Vector3f(4, 1, 3);

    Vector3f res = e.cross(f);
    std::cout << "Wektor prostopadly do e i f: ";

    res.print();

    // Zad5
    std::cout << "Zad 5" << std::endl;
    std::cout << "Znormalizowany wektor:";
    res.normalized().print();

    return 0;
}
