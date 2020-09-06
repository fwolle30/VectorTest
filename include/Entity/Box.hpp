#pragma once

#include <SDL2/SDL.h>
#include "Entity.hpp"

struct Point_2d;

class Box : public Entity
{
public:
    Box(float x, float y, float h, float w);

    void update(double deltaTicks) override;
    void draw(SDL_Renderer *renderer, Point_2d camera_offset) override;

    SDL_FRect getBoundingBox() override;

    void initialize() override;

private:
    SDL_Texture *sprite;
    // bool playerNear;
    // Point_2d player;
};