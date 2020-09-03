#pragma once

#include <SDL2/SDL.h>

struct Point_2d;

class Collision
{
public:
    static bool collideAABB(SDL_FRect a, SDL_FRect b);
};
