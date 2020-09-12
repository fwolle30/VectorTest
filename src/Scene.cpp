#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>

#include "Scene.hpp"

#include "Entity/Entity.hpp"
#include "Math/Point.hpp"
#include "Math/Vector.hpp"

#include "Camera.hpp"
#include "Collision/Collision.hpp"
#include "RenderWindow.hpp"
#include "AssetManager.hpp"

const float FPS = 60;

Scene::Scene(float height, float width) : inputManager(nullptr), height(height), width(width) {}

void Scene::addEntity(Entity *entity)
{
    entity->setScene(this);
    entities.push_back(entity);
}

void Scene::update()
{
    Uint64 ticks = SDL_GetTicks(); // SDL_GetPerformanceCounter();
    double deltaTicks;

    if (lastTicks == 0)
    {
        lastTicks = ticks;
    }

    deltaTicks = (double)((ticks - lastTicks)); // * 1000 / (double)SDL_GetPerformanceFrequency());

    for (Entity *entity : entities)
    {
        entity->update(deltaTicks);
    }

    camera->update();
}

void Scene::draw(SDL_Renderer *renderer)
{
    std::sort(entities.begin(), entities.end(), [](Entity *a, Entity *b) {
        // Point_2d pa = a->getPosition();
        // Point_2d pb = b->getPosition();

        SDL_FRect ra = a->getSpriteRect();
        SDL_FRect rb = b->getSpriteRect();

        return (ra.y + ra.h < rb.y + rb.h);
    });

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_FRect cwp = camera->getViewPort();

    SDL_Rect src;

    src.x = std::max((int)cwp.x, 0);
    src.y = std::max((int)cwp.y, 0);
    src.h = (int)cwp.h;
    src.w = (int)cwp.w;

    SDL_RenderCopy(renderer, background, &src, NULL);

    camera->draw(renderer);

    SDL_RenderPresent(renderer);

    float deltaTicks = lastTicks;

    lastTicks = SDL_GetTicks();

    deltaTicks = lastTicks - deltaTicks;

    if (deltaTicks < 1000 / FPS)
    {
        SDL_Delay((1000 / FPS) - deltaTicks);
    }
    else
    {
        SDL_Delay(0);
    }
}

void Scene::setInputManager(InputManager *manager)
{
    inputManager = manager;
}

InputManager *Scene::getInputManager()
{
    return inputManager;
}

// ToDo: Make this function more efficient (BSP- or Quad-Trees?)
Entity *Scene::getNearestObject(Entity *from, float max_distance)
{
    Entity *found = nullptr;
    float minDistance = max_distance;

    Point_2d startPos = from->getPosition();

    for (Entity *entity : entities)
    {
        if (entity == from)
            continue;

        float l = entity->getPosition().distance(startPos).length();

        if (l < max_distance && minDistance > l)
        {
            minDistance = l;
            found = entity;
        }
    }

    return found;
}

// ToDo: Make this function more efficient (BSP- or Quad-Trees?)
std::vector<Entity *> Scene::getObjectsInRange(Entity *from, float range)
{
    std::vector<Entity *> found;

    Point_2d startPos = from->getPosition();

    for (Entity *entity : entities)
    {
        if (entity == from)
            continue;

        float l = entity->getPosition().distance(startPos).length();

        if (l < range)
        {
            found.push_back(entity);
        }
    }

    return found;
}

Entity *Scene::getNearestObjectOfType(Entity *from, EntityType type, float max_distance)
{
    Entity *found = nullptr;
    float minDistance = max_distance;

    Point_2d startPos = from->getPosition();

    for (Entity *entity : entities)
    {
        if (entity == from || entity->getType() != type)
            continue;

        float l = entity->getPosition().distance(startPos).length();

        if (l < max_distance && minDistance > l)
        {
            minDistance = l;
            found = entity;
        }
    }

    return found;
}

std::vector<Entity *> Scene::getObjectsOfTypeInRange(Entity *from, EntityType type, float range)
{
    std::vector<Entity *> found;

    Point_2d startPos = from->getPosition();

    for (Entity *entity : entities)
    {
        if (entity == from || entity->getType() != type)
            continue;

        float l = entity->getPosition().distance(startPos).length();

        if (l < range)
        {
            found.push_back(entity);
        }
    }

    return found;
}

void Scene::setCamera(Camera *camera)
{
    this->camera = camera;
    camera->setScene(this);
}

Camera *Scene::getCamera()
{
    return camera;
}

std::vector<Entity *> Scene::getObjectsInRect(SDL_FRect rect)
{
    std::vector<Entity *> found;

    for (Entity *entity : entities)
    {
        if (Collision::collideAABB(entity->getBoundingBox(), rect))
        {
            found.push_back(entity);
        }
    }

    return found;
}

void Scene::setRenderWindow(RenderWindow *wnd)
{
    this->wnd = wnd;
}

RenderWindow *Scene::getRenderWindow()
{
    return wnd;
}

SDL_FRect Scene::getSceneRect()
{
    SDL_FRect rect;

    rect.x = 0;
    rect.y = 0;
    rect.h = height;
    rect.w = width;

    return rect;
}

void Scene::initialize()
{
    int h, w;

    SDL_Renderer *renderer = wnd->getRenderer();
    AssetManager *assets = wnd->getAssetManager();

    assets->loadTextureScaled("background", "./assets/grass.png", 2);
    background = assets->getTextureTiled("background", height, width);
}