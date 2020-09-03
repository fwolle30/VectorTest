#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class Canvas
{
public:
    Canvas(SDL_Rect p_rect);
    ~Canvas();

    void draw(SDL_Renderer *renderer);
private:
    SDL_Rect canvasRect;
    int ox, oy;
};