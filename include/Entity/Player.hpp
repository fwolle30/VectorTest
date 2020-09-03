#pragma once

#include "Entity.hpp"
#include "../Math/Vector.hpp"

class Player : public Entity
{
public:
    Player(float x, float y);

    void update(double deltaTicks);
    void draw(SDL_Renderer *renderer, Point_2d camera_offset);

private:
    Vector_2d direction;
    float speed;
    bool collision;

    void updatePosition(double deltaTicks);
};