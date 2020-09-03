#pragma once

#include <SDL2/SDL.h>

#include "../Math/Point.hpp"

class Scene;
class Entity
{
public:
    Entity(float x, float y, float h, float w);

    virtual void update(double deltaTicks) = 0;

    virtual void draw(SDL_Renderer *renderer, Point_2d camera_offset) = 0;

    void setScene(Scene *scene);

    Point_2d getPosition();
    SDL_FRect getBoundingBox();

    bool dbg = false;

protected:
    Scene *scene;
    float x, y, h, w;
};