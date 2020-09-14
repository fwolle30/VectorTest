#pragma once

#include "./Entity/Entity.hpp"
#include <SDL2/SDL.h>

class Wall : public Entity
{
public:
    Wall(float x, float y, bool fullHeight);

    virtual void initialize() override;
    virtual void update(double deltaTicks) override;
    virtual void draw(SDL_Renderer *renderer, Point_2d camera_offset) override;

    virtual SDL_FRect getBoundingBox() override;

private:
    SDL_Texture *sprite;
    bool fullHeight;
};