#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>

#include "AssetManager.hpp"

AssetManager::AssetManager(SDL_Renderer *renderer) : renderer(renderer) {}

bool AssetManager::loadTexture(std::string name, std::string filename)
{
    auto found = textures.find(name);
    if (found != textures.end())
    {
        return true;
    }

    SDL_Surface *imgs = IMG_Load(filename.c_str());
    if (imgs == NULL)
    {
        return false;
    }

    SDL_ConvertSurfaceFormat(imgs, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_Texture *imgTx = SDL_CreateTextureFromSurface(renderer, imgs);
    SDL_FreeSurface(imgs);

    textures[name] = imgTx;

    return true;
}

bool AssetManager::loadTextureScaled(std::string name, std::string filename, int factor)
{
    auto found = textures.find(name);
    if (found != textures.end())
    {
        return true;
    }

    SDL_Surface *imgS = IMG_Load(filename.c_str());
    if (imgS == NULL)
    {
        return false;
    }

    int h = imgS->h * factor;
    int w = imgS->w * factor;

    SDL_ConvertSurfaceFormat(imgS, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_Texture *imgTx = SDL_CreateTextureFromSurface(renderer, imgS);
    SDL_FreeSurface(imgS);

    uint32_t format;
    SDL_QueryTexture(imgTx, &format, NULL, NULL, NULL);

    SDL_Texture *newTex = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetTextureBlendMode(newTex, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, newTex);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_Rect dstRect = {.x = 0, .y = 0, .w = w, .h = h};
    SDL_RenderCopy(renderer, imgTx, NULL, &dstRect);
    SDL_SetRenderTarget(renderer, NULL);

    SDL_DestroyTexture(imgTx);

    textures[name] = newTex;
    return true;
}

SDL_Texture *AssetManager::getTexture(std::string name)
{
    auto found = textures.find(name);
    if (found == textures.end())
    {
        return nullptr;
    }
    else
    {
        return (found->second);
    }
}

SDL_Texture *AssetManager::getTextureTiled(std::string name, float h, float w)
{
    auto found = textures.find(name);
    if (found == textures.end())
    {
        return NULL;
    }

    SDL_Texture *srcTex = found->second;

    std::ostringstream strStream;
    strStream << name << "_" << h << "x" << w;

    name = strStream.str();

    found = textures.find(name);
    if (found != textures.end())
    {
        return found->second;
    }

    int width, height;
    uint32_t format;

    SDL_QueryTexture(srcTex, &format, NULL, &width, &height);

    int passX = w / width;
    int passY = h / height;

    SDL_Texture *dstTex = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetTextureBlendMode(dstTex, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, dstTex);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);    

    for (int y = 0; y <= passY; y++)
    {
        for (int x = 0; x <= passY; x++)
        {
            SDL_Rect dst = {.x = x * width, .y = y * height, .w = width, .h = height};
            SDL_RenderCopy(renderer, srcTex, NULL, &dst);
        }
    }

    SDL_SetRenderTarget(renderer, NULL);

    textures[name] = dstTex;

    return dstTex;
}

void AssetManager::cleanup()
{
    for (auto element : textures)
    {
        SDL_DestroyTexture(element.second);
    }

    textures.clear();
}