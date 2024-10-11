#pragma once
#include "Base.h"
#include "Entity.h"

#include <memory>
#include <tmx.h>
#include <raylib.h>
#include <vector>

namespace Scene
{
    struct Tile
    {
        u32 gid;
        tmx_tileset* tileset;
        std::shared_ptr<Entity> entity;
    };

    struct Tilemap
    {
        tmx_map* map;
        std::vector<Tile> tiles;
    };

    Tilemap LoadTilemap(const char* path);
    void FreeTilemap(Tilemap& tilemap);
}
