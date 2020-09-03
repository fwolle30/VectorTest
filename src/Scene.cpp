#include "Scene.hpp"

#include "Entity/Entity.hpp"
#include "Math/Point.hpp"
#include "Math/Vector.hpp"

Scene::Scene()
    : inputManager(nullptr) {}

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

    lastTicks = SDL_GetTicks();
}

void Scene::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    Point_2d camera_offset(0, 0);

    for (std::vector<Entity *>::iterator it = std::begin(entities); it != std::end(entities); ++it)
    {
        (*it)->draw(renderer, camera_offset);
    }

    SDL_RenderPresent(renderer);
}

void Scene::setInputManager(InputManager *manager)
{
    inputManager = manager;
}

InputManager *Scene::getInputManager()
{
    return inputManager;
}

Entity *Scene::getEntity(int key)
{
    if (key < 0 || key >= entities.size())
    {
        return nullptr;
    }
    else
    {
        return entities.at(key);
    }
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