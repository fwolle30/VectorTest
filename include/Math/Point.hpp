#pragma once

struct Vector_2d;

struct Point_2d
{
    float x;
    float y;

    Point_2d(float x, float y);

    void operator=(Point_2d b);

    operator Vector_2d();

    Point_2d operator+(Point_2d b);
    Point_2d operator-(Point_2d b);
    Point_2d operator*(Point_2d b);
    Point_2d operator/(Point_2d b);

    Vector_2d distance(Point_2d b);
};