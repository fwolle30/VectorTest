#include "Canvas.hpp"
#include "./Math/Vector.hpp"

#include <iostream>

Canvas::Canvas(SDL_Rect p_rect)
    : canvasRect(p_rect)
{
    ox = (p_rect.w / 2) + p_rect.x;
    oy = (p_rect.h / 2) + p_rect.y;
}

Canvas::~Canvas() {}

void Canvas::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    lineRGBA(renderer, 0, oy, canvasRect.w, oy, 100, 100, 100, 255);
    lineRGBA(renderer, ox, 0, ox, canvasRect.h, 100, 100, 100, 255);

    int mx, my;

    SDL_GetMouseState(&mx, &my);

    Vector_2d vA((float)mx - ox, oy - (float)my);

    Vector_2d vB = vA.normalize() * 100;

    lineRGBA(renderer, 0 + ox, 0 + oy, vB.x + ox, -vB.y + oy, 255, 0, 0, 255);

    SDL_RenderPresent(renderer);
}