#include "./Entity/Box.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

Box::Box(float x, float y, float h, float w)
    : Entity(x, y, h, w) {}

void Box::update(double deltaTicks)
{
}

void Box::draw(SDL_Renderer *renderer, Point_2d camera_offset)
{
    float wh = w / 2, hh = h / 2;

    if (dbg)
    {
        rectangleColor(renderer, x - wh, y - hh, x + wh, y + hh, 0xff00ffff);
    } else {
        rectangleColor(renderer, x - wh, y - hh, x + wh, y + hh, 0xffffffff);
    }

    dbg = false;
} 