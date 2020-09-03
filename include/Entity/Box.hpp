#pragma once

#include "Entity.hpp"

class Box : public Entity
{
public:
    Box(float x, float y, float h, float w);

    virtual void update(double deltaTicks);
    virtual void draw(SDL_Renderer *renderer, Point_2d camera_offset);
};