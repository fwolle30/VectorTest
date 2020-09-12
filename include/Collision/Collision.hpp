#pragma once

#include <SDL2/SDL.h>

struct Point_2d;
struct Vector_2d;

class Collision
{
public:
    static bool collideAABB(const SDL_FRect &a, const SDL_FRect &b);
    static bool collideAABB2(const SDL_FRect &a, const SDL_FRect &b, const Vector_2d &velocity, Point_2d &hit, float &length, Vector_2d &normal);

    static bool rayWithBox(const Point_2d &origin, const Vector_2d &dir, const SDL_FRect &b, Point_2d &hit, float &length, Vector_2d &normal);    
};