#include "Tilemap.h"

#include <raylib.h>
#include <tmx.h>

static void* TextureLoadCallback(const char* path)
{
    Texture2D* texture = new Texture;
    *texture = LoadTexture(path);
    return texture;
}

static void TextureFreeCallback(void* texture)
{
    UnloadTexture(*(Texture2D*)texture);
    delete (Texture2D*)texture;
    texture = NULL;
}

static Color IntToColor(int color)
{
    tmx_col_bytes res = tmx_col_to_bytes(color);
    return *((Color*)&res);
}

Tilemap LoadTilemap(const char* path)
{
    Tilemap tilemap;

    tmx_img_load_func = TextureLoadCallback;
    tmx_img_free_func = TextureFreeCallback;
    tilemap.map = tmx_load(path);

    if (!tilemap.map)
    {
        TraceLog(LOG_WARNING, "Failed to load tilemap %s!", path);
        return tilemap;
    }

    return tilemap;
}

static void DrawImageLayer(tmx_image* image)
{
    Texture2D* texture = (Texture2D*)image->resource_image;
    DrawTexture(*texture, 0, 0, WHITE);
}

static void DrawLayer(tmx_map* map, tmx_layer* layer)
{
    for (u32 i = 0; i < map->height; i++)
    {
        for (u32 j = 0; j < map->width; j++)
        {
            Tile tile;
            tile.id = (layer->content.gids[i * map->width + j]) & TMX_FLIP_BITS_REMOVAL;

            tmx_image* image = NULL;
            Rectangle source;

            if (map->tiles[tile.id] != NULL)
            {
                tile.tileset = map->tiles[tile.id]->tileset;
                image = map->tiles[tile.id]->image;
                source.x = map->tiles[tile.id]->ul_x;
                source.y = map->tiles[tile.id]->ul_y;
                source.width = map->tiles[tile.id]->width;
                source.height = map->tiles[tile.id]->height;

                if (image)
                    tile.image = image->resource_image;
                else
                    tile.image = tile.tileset->image->resource_image;

                tile.position.x = j * tile.tileset->tile_width;
                tile.position.y = i * tile.tileset->tile_height;
                tile.size.x = tile.tileset->tile_width;
                tile.size.y = tile.tileset->tile_height;

                DrawTile(tile, source);
            }
        }
    }
}

static void DrawAllLayers(tmx_map* map, tmx_layer* layers)
{
    while (layers)
    {
        if (layers->visible)
        {
            switch (layers->type)
            {
                case L_GROUP:
                    DrawAllLayers(map, layers->content.group_head);
                    break;
                case L_IMAGE:
                    DrawImageLayer(layers->content.image);
                    break;
                case L_LAYER:
                    DrawLayer(map, layers);
                    break;

                    /*
                    case L_OBJGR:
                        DrawAllLayers(map, layers->content.group_head);
                        break;*/

                default:
                    break;
            }
        }

        layers = layers->next;
    }
}

void DrawTile(Tile& tile, Rectangle& source)
{
    Texture2D* texture = (Texture*)tile.image;
    // DrawTextureRec(*texture, source, tile.position, WHITE);
    Rectangle dest;
    dest.x = tile.position.x * 4.f;
    dest.y = tile.position.y * 4.f;
    dest.width = tile.size.x * 4.f;
    dest.height = tile.size.y * 4.f;
    DrawTexturePro(*texture, source, dest, (v2){0.f, 0.f}, 0.f, WHITE);
}

void DrawTilemap(Tilemap& tilemap)
{
    DrawAllLayers(tilemap.map, tilemap.map->ly_head);
}

void FreeTilemap(Tilemap& tilemap)
{
    tmx_map_free(tilemap.map);
}
