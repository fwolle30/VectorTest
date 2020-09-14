#pragma once

#include "Scene.hpp"
#include "TileSet.hpp"

#include <string>

class TileMap : public Scene
{
public:
    TileMap(std::string filename);

    void initialize() override;

    std::vector<char> getAdjacentTiles(int x, int y);

private:
    std::string filename;
    std::vector<char> tileMap;
    TileSet *tileset;
    uint mapWidth = 0, mapHeight = 0;
};