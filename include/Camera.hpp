#pragma once

#include <SDL2/SDL.h>

#include "Math/Point.hpp"

class Scene;

class Camera
{
public:
    Camera(Point_2d position, float w, float h);

    Point_2d getPosition();
    void setPosition(Point_2d position);

    SDL_FRect getViewPort();

    void setScene(Scene *scene);

    void update();
    void draw(SDL_Renderer *renderer);

private:
    Point_2d position;
    float h, w;
    Scene *scene;
};