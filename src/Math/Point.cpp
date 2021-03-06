#include "./Math/Point.hpp"

#include "./Math/Vector.hpp"

#include <algorithm>

Point_2d::Point_2d() : x(0), y(0) {}
Point_2d::Point_2d(float x, float y) : x(x), y(y) {}

void Point_2d::operator=(const Point_2d &b)
{
    x = b.x;
    y = b.y;
}

Point_2d Point_2d::operator+(const Point_2d &b)
{
    return Point_2d(x + b.x, y + b.y);
}

Point_2d Point_2d::operator-(const Point_2d &b)
{
    return Point_2d(x - b.x, y - b.y);
}

Point_2d Point_2d::operator*(const Point_2d &b)
{
    return Point_2d(x * b.x, y * b.y);
}

Point_2d Point_2d::operator/(const Point_2d &b)
{
    return Point_2d(x / b.x, y / b.y);
}

Point_2d::operator Vector_2d()
{
    return Vector_2d(x, y);
}

Vector_2d Point_2d::distance(const Point_2d &b)
{
    int px = std::abs(x - b.x);
    int py = std::abs(y - b.y);

    return Vector_2d(px, py);
}
