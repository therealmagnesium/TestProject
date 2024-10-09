#pragma once
#include "Base.h"

#include <tmx.h>
#include <raylib.h>

struct Tile
{
    u32 id;
    Vector2 position;
    Vector2 size;
    float opacity;
    tmx_tileset* tileset;
    void* image;
};

struct Tilemap
{
    tmx_map* map;
};

Tilemap LoadTilemap(const char* path);
void DrawTile(Tile& tile, Rectangle& source);
void DrawTilemap(Tilemap& tilemap);
void FreeTilemap(Tilemap& tilemap);
