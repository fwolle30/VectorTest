#pragma once

#include <SDL2/SDL.h>
#include <vector>

class Entity;
class InputManager;

class Scene
{
public:
    Scene();

    void addEntity(Entity *entity);
    Entity *getEntity(int key); // Quick and Dirty!! TODO: Make this better

    Entity *getNearestObject(Entity *from, float length);
    std::vector<Entity *> getObjectsInRange(Entity *from, float max_distance);

    void update();
    void draw(SDL_Renderer *renderer);

    void setInputManager(InputManager *manager);
    InputManager *getInputManager();

private:
    Uint64 lastTicks = 0;
    InputManager *inputManager;
    // camera
    std::vector<Entity *> entities;
};