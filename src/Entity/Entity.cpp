#include "Entity/Entity.hpp"

#include "Scene.hpp"
#include "InputManager.hpp"
#include "./Math/Vector.hpp"

#include <algorithm>
#include <SDL2/SDL2_gfxPrimitives.h>

Entity::Entity(float x, float y, float h, float w)
    : x(x), y(y), h(h), w(w) {}

void Entity::setScene(Scene *scene)
{
    this->scene = scene;
}

Point_2d Entity::getPosition()
{
    return Point_2d(x, y);
}

SDL_FRect Entity::getBoundingBox()
{
    float hh = h / 2.0, hw = w / 2.0;

    SDL_FRect rect = {.x = x - hw,
                      .y = y - hh,
                      .w = w,
                      .h = h};

    return rect;
}

SDL_FRect Entity::getSpriteRect()
{
    float hh = h / 2.0, hw = w / 2.0;

    SDL_FRect rect = {.x = x - hw,
                      .y = y - hh,
                      .w = w,
                      .h = h};

    return rect;
}

EntityType Entity::getType()
{
    return type;
}
