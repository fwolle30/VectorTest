#include "./Math/Vector.hpp"
#include <algorithm>
#include <cmath>

#include "./Math/Point.hpp"

Vector_2d::Vector_2d() : x(0), y(0) {}
Vector_2d::Vector_2d(float x, float y) : x(x), y(y)
{
    if (isnanf(x))
    {
        this->x = 0;
    }

    if (isnanf(y))
    {
        this->y = 0;
    }
}

void Vector_2d::operator=(Vector_2d b)
{
    x = b.x;
    y = b.y;
}

Vector_2d Vector_2d::operator+(Vector_2d b)
{
    return Vector_2d(x + b.x, y + b.y);
}

Vector_2d Vector_2d::operator*(float f)
{
    return Vector_2d(f * x, f * y);
}

Vector_2d Vector_2d::operator-(Vector_2d b)
{
    return Vector_2d(x - b.x, y - b.y);
}

Vector_2d Vector_2d::operator/(float f)
{
    return Vector_2d(x / f, y / f);
}

float Vector_2d::operator*(Vector_2d b)
{
    return x * b.x + y * b.y;
}

float Vector_2d::length()
{
    if (x == 0 && y == 0)
    {
        return 0;
    }

    return sqrtf((x * x) + (y * y));
}

Vector_2d Vector_2d::normalize()
{
    float l = length();

    if (l == 0)
    {
        return Vector_2d(0, 0);
    }
    return Vector_2d(x / l, y / l);
}

Vector_2d Vector_2d::transform(float matrix[4])
{
    float a = matrix[0], b = matrix[1], c = matrix[2], d = matrix[3];

    return Vector_2d(x * a + y * b, x * c + y * d);
}

Vector_2d Vector_2d::abs()
{
    return Vector_2d(std::abs(x), std::abs(y));
}

Vector_2d Vector_2d::min(Vector_2d b)
{
    return Vector_2d(std::min(x, b.x), std::min(y, b.y));
}

Vector_2d Vector_2d::max(Vector_2d b)
{
    return Vector_2d(std::max(x, b.x), std::max(y, b.y));
}

Vector_2d Vector_2d::min(float b)
{
    return Vector_2d(std::min(x, b), std::min(y, b));
}

Vector_2d Vector_2d::max(float b)
{
    return Vector_2d(std::max(x, b), std::max(y, b));
}