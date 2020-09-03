#include "Collision/Collision.hpp"

#include "./Math/Point.hpp"
#include "./Math/Vector.hpp"

#include <vector>

bool Collision::collideAABB(SDL_FRect a, SDL_FRect b)
{

    if (a.x < b.x + b.w && a.x + a.w > b.x &&
        a.y < b.y + b.h && a.y + a.w > b.y)
    {
        return true;
    }

    return false;
}