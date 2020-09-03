#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "InputManager.hpp"
#include "RenderWindow.hpp"
#include "Scene.hpp"
#include "Canvas.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
    : window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "Window failed to initialize: " << SDL_GetError() << std::endl;
    }

    // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
}

SDL_Texture *RenderWindow::loadTexture(const char *p_filePath)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
    {
        std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::drawScene()
{
    scene->draw(renderer);
}

void RenderWindow::setScene(Scene *scene)
{
    this->scene = scene;
}

void RenderWindow::updateScene()
{
    scene->update();
}

void RenderWindow::handleEvents(SDL_Event *event)
{
    InputManager* manager = scene->getInputManager();
    if (manager != nullptr) {
        manager->handleKeyEvent(event);
    } else {
        std::cout << "No Input Manager" << std::endl;
    }
}

Scene *RenderWindow::getScene()
{
    return scene;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
}
