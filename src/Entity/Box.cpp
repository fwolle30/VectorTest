#include "./Entity/Box.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "Scene.hpp"
#include "Entity/Player.hpp"
#include "Math/Point.hpp"
#include "RenderWindow.hpp"
#include "AssetManager.hpp"

Box::Box(float x, float y, float h, float w)
    : Entity(x, y, h, w)
{
    type = ENTITY_TYPE_WALL;
}

void Box::update(double deltaTicks) {}

void Box::draw(SDL_Renderer *renderer, Point_2d camera_offset)
{
    float wh = w / 2, hh = h / 2;

    float dx = x - camera_offset.x - wh, dy = y - camera_offset.y - hh;

    SDL_Rect dstRect = {.x = (int)dx, .y = (int)dy, .w = (int)w, .h = (int)h};
    SDL_RenderCopy(renderer, sprite, NULL, &dstRect);

    // SDL_FRect bb = getBoundingBox();
    // rectangleRGBA(renderer, bb.x - camera_offset.x, bb.y - camera_offset.y, bb.x - camera_offset.x + bb.w, bb.y - camera_offset.y + bb.h, 255, 255, 255, 255);
}

void Box::initialize()
{
    RenderWindow *wnd = scene->getRenderWindow();
    AssetManager *assets = wnd->getAssetManager();

    assets->loadTextureScaled("crate", "./assets/crate.png", 2);
    sprite = assets->getTexture("crate");
}

SDL_FRect Box::getBoundingBox()
{
    float hh = h / 2, hw = w / 2;

    SDL_FRect rect;

    rect.x = x - hw;
    rect.y = y;
    rect.h = h / 2;
    rect.w = w;

    return rect;
}