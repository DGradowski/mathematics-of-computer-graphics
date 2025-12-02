#pragma once

#ifndef VECTOR4F_H
#define VECTOR4F_H

class Vector4f
{
public:
    float x, y, z, w;

    Vector4f(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
    ~Vector4f();

    void print() const;
};

#endif // VECTOR4F_H