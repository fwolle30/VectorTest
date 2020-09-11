#pragma once

#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "../Math/Vector.hpp"

class Player : public Entity
{
public:
    Player(float x, float y);

    void update(double deltaTicks) override;
    void draw(SDL_Renderer *renderer, Point_2d camera_offset) override;

    void initialize() override;
    
    SDL_FRect getBoundingBox() override;

private:
    Vector_2d direction;
    float speed;
    bool collision;
    int frameCount;

    SDL_Texture* sprite;

    float ticks;
    float animTicks;

    uint animStart;
    uint animFrames;
    uint animDuration;

    void updatePosition(double deltaTicks);
};