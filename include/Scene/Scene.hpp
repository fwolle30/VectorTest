#pragma once

#include <SDL2/SDL.h>
#include <vector>

enum EntityType : short;
class Entity;
class InputManager;
class Camera;
class RenderWindow;

class Scene
{
public:
    Scene(float height, float with);

    void addEntity(Entity *entity);

    Entity *getNearestObject(Entity *from, float max_distance);
    Entity *getNearestObjectOfType(Entity *from, EntityType type, float max_distance);

    std::vector<Entity *> getObjectsInRange(Entity *from, float range);
    std::vector<Entity *> getObjectsOfTypeInRange(Entity *from, EntityType type, float range);

    std::vector<Entity *> getObjectsInRect(SDL_FRect rect);

    virtual void initialize();

    void update();
    void draw(SDL_Renderer *renderer);

    void setInputManager(InputManager *manager);
    InputManager *getInputManager();

    void setRenderWindow(RenderWindow *wnd);
    RenderWindow *getRenderWindow();

    void setCamera(Camera *camera);
    Camera* getCamera();

    SDL_FRect getSceneRect();

protected:
    float height, width;
    SDL_Texture *background;
    SDL_Texture *foreground;    

    Uint64 lastTicks = 0;
    InputManager *inputManager;
    Camera *camera;
    std::vector<Entity *> entities;
    
    RenderWindow* wnd;
};