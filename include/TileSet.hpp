#pragma once

#include <string>
#include <vector>
#include <map>

#include <SDL2/SDL.h>

#include "AssetManager.hpp"

class TileSet
{
public:
  TileSet(AssetManager *manager, std::string name, std::string filename, uint size_h, uint size_w);
  ~TileSet();

  SDL_Texture *getTexture();

  void addTile(uint index, uint setIndex, std::string group, ushort bitmask);

  SDL_Rect getTileRectFromGroup(std::string group, uint index);
  SDL_Rect getTileRectFromBitmask(std::string group, ushort bitmask);

  uint getTileIndexFromBitmask(std::string group, ushort bitmask);

private:
  struct Tile
  {
    std::string group;
    uint index;
    uint setIndex;
    ushort bitmask;
  };

  std::vector<Tile> set;
  SDL_Texture *texture;

  uint size_h;
  uint size_w;
  uint tilesize_h;
  uint tilesize_w;
};