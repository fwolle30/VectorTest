#pragma once

#include <SDL2/SDL.h>

#include <string>
#include <map>

class AssetManager
{
public:
    AssetManager(SDL_Renderer *renderer);

    bool loadTexture(std::string name, std::string filename);
    bool loadTextureScaled(std::string name, std::string filename, int factor);
    SDL_Texture *getTexture(std::string name);
    SDL_Texture *getTextureTiled(std::string name, float h, float w);

    void cleanup();

private:
    std::map<std::string, SDL_Texture *> textures;

    SDL_Renderer *renderer;
};