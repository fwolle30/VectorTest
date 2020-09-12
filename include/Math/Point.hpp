#pragma once

struct Vector_2d;

struct Point_2d
{
    float x;
    float y;

    Point_2d();
    Point_2d(float x, float y);

    void operator=(const Point_2d &b);

    Point_2d operator+(const Point_2d &b);
    Point_2d operator-(const Point_2d &b);
    Point_2d operator*(const Point_2d &b);
    Point_2d operator/(const Point_2d &b);

    operator Vector_2d();    

    Vector_2d distance(const Point_2d &b);
};