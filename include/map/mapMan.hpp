#pragma once

#include <raylib.h>
#include "core/cute_tiled.h"
#include "core/ctx.hpp"

enum TileType{
    Tile_GRASS, Tile_ROAD
};

struct TileData{
    Vector2i tilePos;
    int type;
    bool trueVal;
    bool isTileEmpty=1;
};

class mapMan{
private:
    float TILESIZE=32;
    Texture2D tileset = {};
    cute_tiled_map_t* cuteMap = nullptr;
    cute_tiled_tileset_t* cuteTS = nullptr;
    Vector2 tileCount;
public:
    mapMan();
    ~mapMan();

    void draw();

    TileData getTileByPos(Vector2 mousePos);
    Vector2 getRealPos(Vector2i pos) {return {pos.x*TILESIZE, pos.y*TILESIZE};};

    bool isInCollionWithID(Vector2 objPos, Vector2 objSize, int selectedID);
};

