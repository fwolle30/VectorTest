#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Scene;
class AssetManager;

class RenderWindow
{
public:
    RenderWindow(const char *p_title, int p_h, int p_w);

    // SDL_Texture *loadTexture(const char *p_filePath);

    void setScene(Scene *scene);
    Scene *getScene();

    SDL_Renderer *getRenderer();

    void clear();

    void handleEvents(SDL_Event *event);

    void updateScene();
    void drawScene();

    AssetManager* getAssetManager();

    void cleanUp();

    void getSize(int *h, int *w);

private:
    Scene *scene;
    SDL_Window *window;
    SDL_Renderer *renderer;
    AssetManager *assetManager;
};