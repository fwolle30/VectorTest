#include "./Scene/TileMap.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

#include "Entity/Wall.hpp"
#include "Entity/Player.hpp"
#include "RenderWindow.hpp"
#include "AssetManager.hpp"
#include "TileSet.hpp"

#define TILE_SIZE 32.f
#define TILE_SIZEH 16.f

TileMap::TileMap(std::string filename)
    : Scene(0, 0), filename(filename), tileset(nullptr)
{
}

std::vector<char> TileMap::getAdjacentTiles(int x, int y)
{
    std::vector<char> tiles;

    int tx = x - 1;
    int ty = y - 1;

    for (int i = ty; i < ty + 3; i++)
    {
        for (int j = tx; j < tx + 3; j++)
        {
            if (i < 0 || i >= mapHeight || j < 0 || j >= mapWidth)
            {
                tiles.push_back('.');
            }
            else
            {
                int idx = i * mapWidth + j;
                tiles.push_back(tileMap[idx]);
            }
        }
    }

    return tiles;
}

void TileMap::initialize()
{
    std::string line;
    std::fstream map(filename, std::ios::in | std::ios::binary);

    mapWidth = 0, mapHeight = 0;

    if (map.good())
    {
        while (std::getline(map, line))
        {
            mapWidth = std::max(line.length(), size_t(mapWidth));
            mapHeight++;

            for (int x = 0; x < mapWidth; x++)
            {
                char c;
                if (x < line.length())
                {
                    c = line.at(x);
                }
                else
                {
                    c = '.';
                }

                float mx = float(x) * TILE_SIZE + TILE_SIZEH;
                float my = (float(mapHeight) - 1.f) * TILE_SIZE + TILE_SIZEH;

                tileMap.push_back(c);

                switch (c)
                {
                case 'p':
                    addEntity(new Player(mx + 0.1f, my - 0.1f));
                    break;
                }
            }
        }
    }

    map.close();

    height = mapHeight * TILE_SIZE;
    width = mapWidth * TILE_SIZE;

    SDL_Renderer *renderer = getRenderWindow()->getRenderer();
    AssetManager *manager = getRenderWindow()->getAssetManager();
    tileset = new TileSet(manager, "level", "assets/tileset.png", 5, 7);

    tileset->addTile(0, 21, "floor", 0);
    tileset->addTile(1, 22, "floor", 0);
    tileset->addTile(2, 23, "floor", 0);
    tileset->addTile(3, 24, "floor", 0);
    tileset->addTile(4, 28, "floor", 0);
    tileset->addTile(5, 29, "floor", 0);
    tileset->addTile(6, 30, "floor", 0);
    tileset->addTile(7, 31, "floor", 0);

    tileset->addTile(0, 0, "wall", 510);

    tileset->addTile(1, 1, "wall", 508);
    tileset->addTile(1, 1, "wall", 509);
    tileset->addTile(1, 1, "wall", 504);
    tileset->addTile(1, 1, "wall", 505);

    tileset->addTile(2, 2, "wall", 507);

    tileset->addTile(11, 3, "wall", 216);
    tileset->addTile(11, 3, "wall", 472);

    tileset->addTile(12, 4, "wall", 432);
    tileset->addTile(12, 4, "wall", 436);
    tileset->addTile(12, 4, "wall", 496);

    tileset->addTile(3, 7, "wall", 502);
    tileset->addTile(3, 7, "wall", 438);
    tileset->addTile(3, 7, "wall", 439);

    tileset->addTile(5, 9, "wall", 475);
    tileset->addTile(5, 9, "wall", 479);
    tileset->addTile(5, 9, "wall", 219);
    tileset->addTile(5, 9, "wall", 223);

    tileset->addTile(6, 14, "wall", 447);

    tileset->addTile(7, 15, "wall", 63);
    tileset->addTile(7, 15, "wall", 127);
    tileset->addTile(7, 15, "wall", 319);

    tileset->addTile(8, 16, "wall", 255);

    tileset->addTile(9, 11, "wall", 27);
    tileset->addTile(9, 11, "wall", 31);
    tileset->addTile(9, 11, "wall", 91);

    tileset->addTile(10, 10, "wall", 54);
    tileset->addTile(10, 10, "wall", 55);

    tileset->addTile(13, 18, "wall", 511);

    SDL_Texture *setTexture = tileset->getTexture();

    Uint32 format;
    SDL_QueryTexture(setTexture, &format, NULL, NULL, NULL);

    background = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, width, height);
    foreground = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(background, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(foreground, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, background);
    SDL_SetRenderDrawColor(renderer, 28, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_SetRenderTarget(renderer, foreground);
    SDL_RenderClear(renderer);

    srand(time(NULL));

    for (size_t i = 0; i < tileMap.size(); i++)
    {
        char c = tileMap[i];

        int tx = i % mapWidth;
        int ty = floor(i / mapWidth);

        float mx = tx * TILE_SIZE;
        float my = ty * TILE_SIZE;

        float ex = float(tx) * TILE_SIZE + TILE_SIZEH;
        float ey = float(ty) * TILE_SIZE + TILE_SIZEH;

        if (c == ' ' || c == 'p')
        {
            SDL_Rect src = tileset->getTileRectFromGroup("floor", rand() % 7);
            SDL_Rect dst = {.x = int(mx), .y = int(my), .w = int(TILE_SIZE), .h = int(TILE_SIZE)};

            SDL_SetRenderTarget(renderer, background);
            SDL_RenderCopy(renderer, setTexture, &src, &dst);
        }
        else if (c == '#')
        {
            std::vector<char> adj = getAdjacentTiles(tx, ty);
            short bitmask = 0;

            for (char wt : adj)
            {
                if (wt == '#' || wt == '.')
                {
                    bitmask = bitmask << 1 | 1;
                }
                else
                {
                    bitmask = bitmask << 1 | 0;
                }
            }

            SDL_Rect src = tileset->getTileRectFromBitmask("wall", bitmask);

            if (src.h > 0 && src.w > 0)
            {
                SDL_Rect dst = {.x = int(mx), .y = int(my), .w = int(TILE_SIZE), .h = int(TILE_SIZE)};

                uint index = tileset->getTileIndexFromBitmask("wall", bitmask);

                switch (index)
                {
                case 10:
                case 11:
                case 15:
                    entities.push_back(new Wall(ex, ey, false));
                    SDL_SetRenderTarget(renderer, foreground);
                    break;

                default:
                    entities.push_back(new Wall(ex, ey, true));
                    SDL_SetRenderTarget(renderer, background);
                    break;
                }

                SDL_RenderCopy(renderer, setTexture, &src, &dst);
            }
            else
            {
                std::cout << bitmask << std::endl;
            }
        }
    }

    for (Entity *entity : entities)
        entity->initialize();

    SDL_SetRenderTarget(renderer, NULL);
}