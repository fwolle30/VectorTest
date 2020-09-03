#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Scene;

class RenderWindow
{
public:
    RenderWindow(const char *p_title, int p_h, int p_w);

    SDL_Texture *loadTexture(const char *p_filePath);

    void setScene(Scene *scene);
    Scene *getScene();

    void clear();

    void handleEvents(SDL_Event *event);

    void updateScene();
    void drawScene();

    void cleanUp();

private:
    Scene *scene;
    SDL_Window *window;
    SDL_Renderer *renderer;
};