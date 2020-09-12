#include "Collision/Collision.hpp"

#include "./Math/Point.hpp"
#include "./Math/Vector.hpp"

#include <vector>
#include <algorithm>

bool Collision::collideAABB(const SDL_FRect &a, const SDL_FRect &b)
{

    if (a.x <= b.x + b.w &&
        a.x + a.w >= b.x &&
        a.y <= b.y + b.h &&
        a.y + a.h >= b.y)
    {
        return true;
    }

    return false;
}

bool Collision::collideAABB2(const SDL_FRect &a, const SDL_FRect &b, const Vector_2d &velocity, Point_2d &hit, float &length, Vector_2d &normal)
{
    if (velocity.x == 0 && velocity.y == 0)
        return 0;

    SDL_FRect expanded = b;
    expanded.x -= a.w / 2.0f;
    expanded.y -= a.h / 2.0f;
    expanded.h += a.h;
    expanded.w += a.w;

    Point_2d start(a.x + a.w / 2, a.y + a.h / 2);

    if (rayWithBox(start, velocity, expanded, hit, length, normal))
    {
        if (length <= 1.0f)
            return true;
    }

    return false;
}

bool Collision::rayWithBox(const Point_2d &origin, const Vector_2d &dir, const SDL_FRect &b, Point_2d &hit, float &length, Vector_2d &normal)
{
    Point_2d rp(b.x, b.y);
    Point_2d rs(b.w, b.h);

    Vector_2d near = Vector_2d(rp - origin) / dir;
    Vector_2d far = Vector_2d(rp + rs - origin) / dir;

    if (isnan(far.x) || isnan(far.y))
        return false;
    if (isnan(near.x) || isnan(near.y))
        return false;

    if (near.x > far.x)
        std::swap(near.x, far.x);
    if (near.y > far.y)
        std::swap(near.y, far.y);

    if (near.x > far.y || near.y > far.x)
        return false;

    float hitNear = std::max(near.x, near.y);
    float hitFar = std::min(far.x, far.y);

    if (hitFar < 0)
        return false;

    hit = Vector_2d(origin) + Vector_2d(dir) * hitNear;
    length = hitNear;

    if (near.x > near.y)
    {
        if (dir.x < 0)
        {
            normal = {1.0f, 0.0f};
        }
        else
        {
            normal = {-1.0f, 0.0f};
        }
    }
    else if (near.x < near.y)
    {
        if (dir.y < 0)
        {
            normal = {0.0f, 1.0f};
        }
        else
        {
            normal = {0.0f, -1.0f};
        }
    }

    return true;
}