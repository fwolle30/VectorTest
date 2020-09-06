#include "InputManager.hpp"

void InputManager::handleKeyEvent(SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        pressed[event->key.keysym.sym] = 1;
    } else if (event->type == SDL_KEYUP) {
        auto item = pressed.find(event->key.keysym.sym); 

        if (item != pressed.end()) {
            pressed.erase(item);
        }
    }
}

int InputManager::isPressed(SDL_Keycode key) {
    int result = 0;

    auto item = pressed.find(key); 
    if (item != pressed.end()) {
        result = pressed.at(key);
    }

    return result ;
}