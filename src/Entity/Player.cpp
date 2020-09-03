#include "Entity/Player.hpp"
#include "InputManager.hpp"
#include "Scene.hpp"

#include "Collision/Collision.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

#include <iostream>

Player::Player(float x, float y)
    : Entity(x, y, 50, 50), direction(Vector_2d(0, 0)), speed(0.0), collision(false)
{
}

void Player::update(double deltaTicks)
{
    collision = false;
    InputManager *input = scene->getInputManager();

    int dirX = input->isPressed(SDLK_d) - input->isPressed(SDLK_a);
    int dirY = input->isPressed(SDLK_s) - input->isPressed(SDLK_w);

    const int STEP_HEIGHT = 10; // "Overshoot" Threshold for easier detection of boundarys (Increase this to allow climbing stairs on a platformer)

    Vector_2d newDir(dirX, dirY);

    if (newDir.length() > 0)
    {
        speed = 0.4;
        direction = newDir.normalize();

        float bx = x, by = y;
        updatePosition(deltaTicks);

        std::vector<Entity *> entities = scene->getObjectsInRange(this, 75);

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
                    Point_2d ePos = e->getPosition();

                    Point_2d p1(mbb.x, mbb.y);
                    Point_2d p2(mbb.x + mbb.w, mbb.y);
                    Point_2d p3(mbb.x + mbb.w, mbb.y + mbb.h);
                    Point_2d p4(mbb.x, mbb.y + mbb.h);

                    Point_2d e1(ebb.x, ebb.y);
                    Point_2d e2(ebb.x + ebb.w, ebb.y);
                    Point_2d e3(ebb.x + ebb.w, ebb.y + ebb.h);
                    Point_2d e4(ebb.x, ebb.y + ebb.h);

                    if ((p3.x > e1.x && p3.y < ePos.y - ebb.h / 2 + (STEP_HEIGHT * dirY)) && (p4.x < e2.x && p4.y < ePos.y - ebb.h / 2 + (STEP_HEIGHT * dirY))) // Top Boundary
                    {
                        y = ePos.y - ebb.h / 2 - h / 2;
                    }
                    else if ((p2.x > e4.x && p2.y > ePos.y + ebb.h / 2 + (STEP_HEIGHT * dirY)) && (p1.x < e3.x && p1.y > ePos.y + ebb.h / 2 + (STEP_HEIGHT * dirY))) // Bottom Boundary
                    {
                        y = ePos.y + ebb.h / 2 + h / 2;
                    }
                    else if ((p3.y > e1.y && p3.x < ePos.x - ebb.w / 2 + (STEP_HEIGHT * dirX)) && (p2.y < e4.y && p2.x < ePos.x - ebb.w / 2 + (STEP_HEIGHT * dirX))) // Left Boundary
                    {
                        x = ePos.x - ebb.w / 2 - w / 2;
                    }
                    else if ((p4.y > e2.y && p4.x > ePos.x - ebb.w / 2 + (STEP_HEIGHT * dirX)) && (p1.y < e3.y && p1.x > ePos.x + ebb.w / 2 + (STEP_HEIGHT * dirX))) // Right Boundary
                    {
                        x = ePos.x + ebb.w / 2 + w / 2;
                    }
                }
            }
        }
    }
}

void Player::draw(SDL_Renderer *renderer, Point_2d camera_offset)
{
    int r = std::min(w, h) / 2;
    if (!collision)
    {
        circleRGBA(renderer, x, y, r, 255, 255, 255, 255);
    }
    else
    {
        filledCircleRGBA(renderer, x, y, r, 255, 255, 255, 255);
    }
}

void Player::updatePosition(double deltaTicks)
{
    Vector_2d tmp = direction * (speed * deltaTicks);

    x += tmp.x;
    y += tmp.y;
}