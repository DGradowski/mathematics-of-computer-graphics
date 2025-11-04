#include "Vector4f.h"
#include <iostream>
#include <iomanip>

Vector4f::Vector4f(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w)
{
}

Vector4f::~Vector4f()
{
}

void Vector4f::print() const
{
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "( " << std::setw(8) << x << ", "
              << std::setw(8) << y << ", "
              << std::setw(8) << z << ", "
              << std::setw(8) << w << " )" << std::endl;
}