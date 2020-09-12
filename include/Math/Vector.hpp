#pragma once

struct Point_2d;

struct Vector_2d
{
    float x, y;

    Vector_2d();
    Vector_2d(float x, float y);
    Vector_2d(const Point_2d &b);

    void operator=(const Vector_2d &b);

    Vector_2d operator+(const Vector_2d &b);
    Vector_2d operator-(const Vector_2d &b);
    Vector_2d operator*(const Vector_2d &b);    
    Vector_2d operator/(const Vector_2d &b);

    Vector_2d operator+=(const Vector_2d &b);

    Vector_2d operator/(float f);
    Vector_2d operator*(float f);

    operator Point_2d();

    Vector_2d abs();
    Vector_2d min(const Vector_2d &b);
    Vector_2d max(const Vector_2d &b);
    Vector_2d min(float b);
    Vector_2d max(float b);

    float length();
    Vector_2d normalize();

    Vector_2d transform(float matrix[4]);
};