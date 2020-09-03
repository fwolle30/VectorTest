#pragma once

struct  Point_2d;

struct Vector_2d
{
    float x, y;

    Vector_2d();
    Vector_2d(float x, float y);

    void operator=(Vector_2d b);

    Vector_2d operator+(Vector_2d b);
    Vector_2d operator*(float f);
    Vector_2d operator-(Vector_2d b);
    Vector_2d operator/(float f);

    float operator*(Vector_2d b);

    Vector_2d abs();

    float length();
    Vector_2d normalize();

    Vector_2d transform(float matrix[4]);
};