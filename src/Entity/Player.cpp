#include "Entity/Player.hpp"
#include "InputManager.hpp"
#include "Scene.hpp"

#include "RenderWindow.hpp"
#include "AssetManager.hpp"
#include "Collision/Collision.hpp"
#include "Camera.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

#include <iostream>
#include <cmath>

Player::Player(float x, float y)
    : Entity(x, y, 64, 64), direction(Vector_2d(0, 0)), speed(0.0), collision(false), frameCount(0), ticks(0)
{
    type = ENTITY_TYPE_PLAYER;
}

void Player::update(double deltaTicks)
{
    frameCount = (frameCount + 1) % 10;
    ticks += deltaTicks;

    if (frameCount == 0)
    {
        collision = false;
    }

    InputManager *input = scene->getInputManager();

    int dirX = input->isPressed(SDLK_d) - input->isPressed(SDLK_a);
    int dirY = input->isPressed(SDLK_s) - input->isPressed(SDLK_w);

    const int STEP_HEIGHT = 10; // "Overshoot" Threshold for easier detection of boundarys (Increase this to allow climbing stairs on a platformer)

    Vector_2d newDir(dirX, dirY);

    speed = 0.0;

    if (newDir.length() > 0)
    {
        speed = 0.2;
        direction = newDir.normalize();

        float bx = x, by = y;
        updatePosition(deltaTicks);

        float scanLength = Vector_2d(w, h).length();

        std::vector<Entity *> entities = scene->getObjectsOfTypeInRange(this, ENTITY_TYPE_WALL, scanLength);

        for (Entity *e : entities)
        {
            if (e != nullptr)
            {
                e->dbg = true;
                SDL_FRect ebb = e->getBoundingBox();
                SDL_FRect mbb = getBoundingBox();

                // Set the collision flag, but check only if the current entity caused the collision.
                // If we simply check against the Player collsion flag, we would limit the movement to the boundarys of the current object e.
                // Not nice for movement, because we allways stop in front of the next tile / object.

                bool check = Collision::collideAABB(mbb, ebb);
                collision |= check;

                if (check)
                {
                    Point_2d p1(mbb.x, mbb.y);
                    Point_2d p2(mbb.x + mbb.w, mbb.y);
                    Point_2d p3(mbb.x + mbb.w, mbb.y + mbb.h);
                    Point_2d p4(mbb.x, mbb.y + mbb.h);

                    Point_2d e1(ebb.x, ebb.y);
                    Point_2d e2(ebb.x + ebb.w, ebb.y);
                    Point_2d e3(ebb.x + ebb.w, ebb.y + ebb.h);
                    Point_2d e4(ebb.x, ebb.y + ebb.h);

                    float bbXOffset = x - mbb.x;
                    float bbYOffset = y - mbb.y;

                    if ((p3.x > e1.x && p3.y < e1.y + (STEP_HEIGHT * dirY)) && (p4.x < e2.x && p4.y < e2.y + (STEP_HEIGHT * dirY))) // Top Boundary
                    {
                        y = e1.y + bbYOffset - mbb.h;
                    }
                    else if ((p2.x > e4.x && p2.y > e4.y + (STEP_HEIGHT * dirY)) && (p1.x < e3.x && p1.y > e3.y + (STEP_HEIGHT * dirY))) // Bottom Boundary
                    {
                        y = e4.y + bbYOffset;
                    }
                    else if ((p3.y > e1.y && p3.x < e1.x + (STEP_HEIGHT * dirX)) && (p2.y < e4.y && p2.x < e4.x + (STEP_HEIGHT * dirX))) // Left Boundary
                    {
                        x = e1.x + bbXOffset - mbb.w;
                    }
                    else if ((p4.y > e2.y && p4.x > e2.x + (STEP_HEIGHT * dirX)) && (p1.y < e3.y && p1.x > e3.x + (STEP_HEIGHT * dirX))) // Right Boundary
                    {
                        x = e2.x + bbXOffset;
                    }
                }
            }
        }
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

    int frame = 1;

    if (speed > 0)
    {
        frame = (int)(ticks / 1000 * 4) % 4;

        if (frame == 3)
        {
            frame = 1;
        }
    }

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

    // SDL_FRect bb = getBoundingBox();
    // rectangleRGBA(renderer, bb.x - camera_offset.x, bb.y - camera_offset.y, bb.x - camera_offset.x + bb.w, bb.y - camera_offset.y + bb.h, 255, 255, 255, 255);
}

void Player::updatePosition(double deltaTicks)
{
    Vector_2d tmp = direction * (speed * deltaTicks);

    x += std::round(tmp.x);
    y += std::round(tmp.y);
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
    float hh = h / (float)2;
    float hw = (w - (float)20) / (float)2;

    SDL_FRect rect;
    rect.x = x - hw;
    rect.y = (y + hh) - 20;
    rect.h = 20;
    rect.w = w - 20;

    return rect;
}