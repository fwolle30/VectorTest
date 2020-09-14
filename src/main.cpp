#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include <unistd.h>
#include <stdint.h>

#include "RenderWindow.hpp"
#include "./Scene/Scene.hpp"
#include "InputManager.hpp"
#include "Entity/Player.hpp"
#include "Entity/Box.hpp"
#include "Camera.hpp"
#include "./Scene/TileMap.hpp"

#if __EMSCRIPTEN__
#include <emscripten.h>
#endif

Uint64 g_st = SDL_GetPerformanceCounter();

void wasteTimeMs(double p_time)
{
    double deltaTicks;

    do
    {
        Uint64 ticks = SDL_GetPerformanceCounter();
        deltaTicks = (double)((ticks - g_st) * 1000 / (double)SDL_GetPerformanceFrequency());
    } while (deltaTicks < p_time);

    g_st = SDL_GetPerformanceCounter();
}

void updateTick(void *arg)
{
    RenderWindow *window = (RenderWindow *)arg;

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        window->handleEvents(&event);
    }

    window->updateScene();
    window->drawScene();
}

int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "SDL_Init has failed: " << SDL_GetError() << std::endl;
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        std::cout << "IMG_Init has failed: " << SDL_GetError() << std::endl;
    }

    RenderWindow window("Game", 800, 576);

    TileMap scene("./assets/testmap.map");

    Camera camera(Point_2d(800 / 2, 576 / 2), 800, 576);

    scene.setCamera(&camera);

    InputManager manager;
    scene.setInputManager(&manager);

    window.setScene(&scene);

    scene.initialize();

    bool gameRunning = true;

    SDL_Event event;

#if !__EMSCRIPTEN__
    while (gameRunning)
    {
        updateTick(&window);

        if (manager.isPressed(SDLK_ESCAPE))
        {
            gameRunning = false;
        }
    }
#else
    emscripten_set_main_loop_arg(updateTick, &window, -1, true);
#endif

    window.cleanUp();

    IMG_Quit();
    SDL_Quit();

    return 0;
}
