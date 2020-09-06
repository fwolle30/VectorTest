#pragma once

#include <SDL2/SDL.h>

#include "../Math/Point.hpp"

class Scene;

enum EntityType : short
{
    ENTITY_TYPE_PLAYER = 1,
    ENTITY_TYPE_WALL
};

class Entity
{
public:
    Entity(float x, float y, float h, float w);

    virtual void initialize() {};
    virtual void update(double deltaTicks) = 0;
    virtual void draw(SDL_Renderer *renderer, Point_2d camera_offset) = 0;

    void setScene(Scene *scene);

    Point_2d getPosition();
    virtual SDL_FRect getBoundingBox();
    virtual SDL_FRect getSpriteRect();    

    EntityType getType();

    bool dbg = false;

protected:
    Scene *scene;
    float x, y, h, w;
    EntityType type;
};