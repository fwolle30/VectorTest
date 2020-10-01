#include "Entity/Player.hpp"
#include "InputManager.hpp"
#include "./Scene/Scene.hpp"

#include "RenderWindow.hpp"
#include "AssetManager.hpp"
#include "Collision/Collision.hpp"
#include "Camera.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>
#include <algorithm>
#include <iostream>
#include <cmath>

Player::Player(float x, float y)
    : Entity(x, y, 32, 32),
      direction(Vector_2d(0, 0)),
      speed(0.0),
      collision(false),
      animTicks(0),
      ticks(0)
{
    type = ENTITY_TYPE_PLAYER;
}

void Player::update(double deltaTicks)
{
    // frameCount = (frameCount + 1) % 10;
    ticks += deltaTicks;

    // if (frameCount == 0)
    // {
    collision = false;
    // }

    InputManager *input = scene->getInputManager();

    int dirX = input->isPressed(SDLK_d) - input->isPressed(SDLK_a);
    int dirY = input->isPressed(SDLK_s) - input->isPressed(SDLK_w);

    Vector_2d newDir(dirX, dirY);

    speed = 0.0f;

    if (newDir.length() > 0)
    {
        animTicks = std::max(float(animTicks + deltaTicks), 200.f);
        speed = 0.2f;
        direction = newDir.normalize();
        Vector_2d velocity = direction * speed * deltaTicks;

        Point_2d oldPos(x, y);

        float scanLength = Vector_2d(w, h).length();

        std::vector<Entity *> entities = scene->getObjectsOfTypeInRange(this, ENTITY_TYPE_WALL, scanLength);

        for (Entity *e : entities)
        {
            if (e != nullptr)
            {
                SDL_FRect mbb = getBoundingBox();
                SDL_FRect ebb = e->getBoundingBox();

                Point_2d hit;
                float length;
                Vector_2d normal;

                // Set the collision flag, but check only if the current entity caused the collision.
                // If we simply check against the Player collsion flag, we would limit the movement to the boundarys of the current object e.
                // Not nice for movement, because we allways stop in front of the next tile / object.
                bool check = Collision::collideAABB2(mbb, ebb, velocity, hit, length, normal);
                collision |= check;

                if (check && length <= 1.0f)
                {
                    velocity += normal * (velocity.abs() * (1.1f - length));
                }
            }
        }

        x = oldPos.x + velocity.x;
        y = oldPos.y + velocity.y;
    } else {
        animTicks = 0;
    }

    Camera *camera = scene->getCamera();
    camera->setPosition(getPosition());
}

void Player::draw(SDL_Renderer *renderer, Point_2d camera_offset)
{
    float dx = x - camera_offset.x, dy = y - camera_offset.y;
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    float ch = h / 2;
    float cw = w / 2;

    int dir = 0;

    int frame = 1 + std::abs((((int)(animTicks / 200) + 3) % 4) - 2) - 1;

    if (direction.y < 0)
    {
        dir = 3;
    }
    else
    {
        dir = 0;
    }

    if (direction.x < 0)
    {
        dir = 1;
    }
    else if (direction.x > 0)
    {
        dir = 2;
    }

    srcRect.x = frame * w;
    srcRect.y = dir * h;
    srcRect.h = h;
    srcRect.w = w;

    dstRect.x = dx - cw;
    dstRect.y = dy - ch;
    dstRect.h = h;
    dstRect.w = w;

    SDL_RenderCopy(renderer, sprite, &srcRect, &dstRect);

    SDL_FRect bb = getBoundingBox();

    bb.x -= camera_offset.x;
    bb.y -= camera_offset.y;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRectF(renderer, &bb);
}

void Player::initialize()
{
    RenderWindow *wnd = scene->getRenderWindow();
    AssetManager *assets = wnd->getAssetManager();

    assets->loadTextureScaled("player", "./assets/player.png", 2);
    sprite = assets->getTexture("player");
}

SDL_FRect Player::getBoundingBox()
{
    float hh = h / 2.0f;
    float hw = w / 2.0f;

    SDL_FRect rect;
    rect.x = (x - hw) + 4;
    rect.y = (y - hh) + 16;
    rect.h = h - 16;
    rect.w = w - 8;

    return rect;
}
