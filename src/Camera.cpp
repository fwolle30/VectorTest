#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>

#include "Camera.hpp"

#include "Math/Point.hpp"
#include "Entity/Entity.hpp"
#include "Scene.hpp"
#include "InputManager.hpp"
#include "RenderWindow.hpp"

#include <stdio.h>

#define COLOR_RGBA(r, g, b, a) (((uint8_t)a << 24) | ((uint8_t)b << 16) | ((uint8_t)g << 8) | (uint8_t)r);

Camera::Camera(Point_2d position, float w, float h)
    : position(position), h(h), w(w) {}

Point_2d Camera::getPosition()
{
    return position;
}

void Camera::setPosition(Point_2d position)
{
    this->position = position;
}

SDL_FRect Camera::getViewPort()
{
    SDL_FRect result;

    float cw = w / 2;
    float ch = h / 2;

    result.x = position.x - cw;
    result.y = position.y - ch;
    result.h = h;
    result.w = w;

    return result;
}

void Camera::setScene(Scene *scene)
{
    this->scene = scene;
}

void Camera::update()
{
    SDL_FRect cwp = getViewPort();
    SDL_FRect sceneRect = scene->getSceneRect();

    float mx = w / 2;
    float my = h / 2;


    if (cwp.x < 0) {
        position.x = mx;
    }

    if (cwp.x + w > sceneRect.w) {
        position.x = sceneRect.w - mx;
    }

    if (cwp.y < 0) {
        position.y = my;
    }

    if (cwp.y + h > sceneRect.h) {
        position.y = sceneRect.h - my;
    }
}

void Camera::draw(SDL_Renderer *renderer)
{
    SDL_FRect vp = getViewPort();
    Point_2d offset(vp.x, vp.y);

    RenderWindow *wnd = scene->getRenderWindow();

    int wndHeight, wndWidth;
    wnd->getSize(&wndHeight, &wndWidth);

    offset = offset - Point_2d((wndWidth - w) / 2, (wndHeight - h) / 2);

    std::vector<Entity *> entities = scene->getObjectsInRect(vp);

    for (Entity *entity : entities)
    {
        entity->draw(renderer, offset);
    }

    float x1 = vp.x - offset.x;
    float y1 = vp.y - offset.y;
    float x2 = x1 + vp.w;
    float y2 = y1 + vp.h;

    uint32_t color = COLOR_RGBA(0x00, 0x00, 0x00, 0xff);

    boxColor(renderer, x1, y1, 0, y2, color);
    boxColor(renderer, x2, y1, wndWidth, y2, color);

    boxColor(renderer, 0, 0, wndWidth, y1, color);
    boxColor(renderer, 0, y2, wndWidth, wndHeight, color);

    boxColor(renderer, x2, y1, wndWidth, y2, color);
    rectangleColor(renderer, x1, y1, x2, y2, color);
}