

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include <unistd.h>
#include <stdint.h>

#include "RenderWindow.hpp"
#include "Scene.hpp"
#include "InputManager.hpp"
#include "Entity/Player.hpp"
#include "Entity/Box.hpp"

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

    RenderWindow window("Game", 1280, 720);

    Player player(150, 50);
    Box box1(150, 150, 50, 50);
    Box box2(200, 150, 50, 50);
    Box box3(250, 150, 50, 50);

    Scene scene;

    InputManager manager;
    scene.setInputManager(&manager);

    window.setScene(&scene);

    scene.addEntity(&player);
    scene.addEntity(&box1);
    scene.addEntity(&box2);
    scene.addEntity(&box3);

    bool gameRunning = true;

    SDL_Event event;

#if !__EMSCRIPTEN__
    while (gameRunning)
    {
        updateTick(&window);

        if (manager.isPressed(SDLK_ESCAPE)) {
            gameRunning = false;
        }

        wasteTimeMs(1); // neccessary for fluid animations (updating to often leads to stuttering)
    }
#else
    emscripten_set_main_loop_arg(updateTick, &window, -1, true);
#endif
 
    window.cleanUp();

    SDL_Quit();

    return 0;
}
