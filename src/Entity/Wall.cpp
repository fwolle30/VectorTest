#include "./Entity/Wall.hpp"

#include "./Scene/Scene.hpp"
#include "RenderWindow.hpp"
#include "AssetManager.hpp"

Wall::Wall(float x, float y, bool fullHeight)
    : Entity(x, y, 32, 32), fullHeight(fullHeight)
{
    type = ENTITY_TYPE_WALL;
}

void Wall::initialize()
{
}

void Wall::update(double deltaTicks)
{
}

SDL_FRect Wall::getBoundingBox()
{
    float hh = h / 2.0, hw = w / 2.0;

    SDL_FRect rect = {.x = x - hw,
                      .y = y - hh,
                      .w = w,
                      .h = h};

    if (!fullHeight) {
        rect.y += 8;
        rect.h -= 8;
    }

    return rect;    
}

void Wall::draw(SDL_Renderer *renderer, Point_2d camera_offset)
{
    SDL_FRect bb = getBoundingBox();

    bb.x -= camera_offset.x;
    bb.y -= camera_offset.y;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRectF(renderer, &bb);
}
