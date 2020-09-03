#pragma once

#include <SDL2/SDL.h>
#include <map>

class InputManager
{

public:
    void handleKeyEvent(SDL_Event *event);

    int isPressed(SDL_Keycode key);

private:
    std::map<SDL_Keycode, int> pressed;
};