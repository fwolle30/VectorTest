#include "TileSet.hpp"

TileSet::TileSet(AssetManager *manager, std::string name, std::string filename, uint size_h, uint size_w)
    : texture(nullptr),
      size_h(size_h),
      size_w(size_w),
      tilesize_h(0),
      tilesize_w(0)
{
    manager->loadTextureScaled(name, filename, 2);
    texture = manager->getTexture(name);

    int tsh, tsw;

    SDL_QueryTexture(texture, NULL, NULL, &tsw, &tsh);

    tilesize_h = tsh / size_h;
    tilesize_w = tsw / size_w;
}

TileSet::~TileSet()
{
}

SDL_Texture *TileSet::getTexture()
{
    return texture;
}

void TileSet::addTile(uint index, uint setIndex, std::string group, ushort bitmask)
{
    Tile tile = {
        .group = group,
        .index = index,
        .setIndex = setIndex,
        .bitmask = bitmask};

    set.push_back(tile);
}

SDL_Rect TileSet::getTileRectFromGroup(std::string group, uint index)
{
    uint setIndex = 0;
    bool found = false;

    SDL_Rect ret = {
        .x = 0,
        .y = 0,
        .w = 0,
        .h = 0};

    for (Tile t : set)
    {
        if (t.group.compare(group) == 0 && t.index == index)
        {
            found = true;
            setIndex = t.setIndex;
            break;
        }
    }

    if (found)
    {
        float x = (setIndex % size_w) * tilesize_w;
        float y = floor(setIndex / size_w) * tilesize_h;

        ret.x = x;
        ret.y = y;
        ret.h = tilesize_h;
        ret.w = tilesize_w;
    }

    return ret;
}

SDL_Rect TileSet::getTileRectFromBitmask(std::string group, ushort bitmask)
{
    uint setIndex = 0;
    bool found = false;
    SDL_Rect ret = {
        .x = 0,
        .y = 0,
        .w = 0,
        .h = 0};

    for (Tile t : set)
    {
        if (t.group.compare(group) == 0 && t.bitmask == bitmask)
        {
            found = true;
            setIndex = t.setIndex;
            break;
        }
    }

    if (found)
    {
        float x = (setIndex % size_w) * tilesize_w;
        float y = floor(setIndex / size_w) * tilesize_h;

        ret.x = x;
        ret.y = y;
        ret.h = tilesize_h;
        ret.w = tilesize_w;
    }

    return ret;
}

uint TileSet::getTileIndexFromBitmask(std::string group, ushort bitmask)
{
    uint setIndex = 9999;

    for (Tile t : set)
    {
        if (t.group.compare(group) == 0 && t.bitmask == bitmask)
        {
            setIndex = t.setIndex;
            break;
        }
    }

    return setIndex;
}