#include "Tilemap.h"
#include "Application.h"

#include <raylib.h>
#include <tmx.h>

using namespace Core;

namespace Scene
{
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

    static void SearchLayer(Tilemap& tilemap, tmx_layer* layer)
    {
        tmx_map* map = tilemap.map;
        for (u32 i = 0; i < map->height; i++)
        {
            for (u32 j = 0; j < map->width; j++)
            {
                Tile tile;
                u32 index = i * tilemap.map->width + j;
                const char* tag = TextFormat("Tile %d", index);
                tile.entity = App->CreateEntity(tag);

                tile.gid = (layer->content.gids[i * map->width + j]) & TMX_FLIP_BITS_REMOVAL;

                Rectangle source;
                tmx_image* image = NULL;

                if (tilemap.map->tiles[tile.gid] != NULL)
                {
                    auto& transform = tile.entity->AddComponent<TransformComponent>((v2){0.f, 0.f}, 0.f, (v2){4.f, 4.f});
                    auto& sprite = tile.entity->AddComponent<SpriteRendererComponent>();
                    auto& collider = tile.entity->AddComponent<BoxColliderComponent>(transform, (v2){0.f, 0.f}, (v2){0.f, 0.f});
                    collider.drawCollider = false;

                    tile.tileset = tilemap.map->tiles[tile.gid]->tileset;
                    image = tilemap.map->tiles[tile.gid]->image;
                    source.x = tilemap.map->tiles[tile.gid]->ul_x;
                    source.y = tilemap.map->tiles[tile.gid]->ul_y;
                    source.width = tilemap.map->tiles[tile.gid]->width;
                    source.height = tilemap.map->tiles[tile.gid]->height;

                    if (image)
                        sprite.texture = (Texture2D*)image->resource_image;
                    else
                        sprite.texture = (Texture2D*)tile.tileset->image->resource_image;

                    sprite.source = source;

                    transform.position.x = j * tile.tileset->tile_width * transform.scale.x;
                    transform.position.y = i * tile.tileset->tile_height * transform.scale.y;
                    collider.box.width = tile.tileset->tile_width * transform.scale.x;
                    collider.box.height = tile.tileset->tile_height * transform.scale.y;

                    tilemap.tiles.push_back(tile);
                }
            }
        }
    }

    static void SearchLayers(Tilemap& tilemap, tmx_layer* layers)
    {
        while (layers)
        {
            if (layers->visible)
            {
                switch (layers->type)
                {
                    case L_GROUP:
                        SearchLayers(tilemap, layers->content.group_head);
                        break;
                        /*
                        case L_IMAGE:
                            DrawImageLayer(layers->content.image);
                            break;*/

                    case L_LAYER:
                        SearchLayer(tilemap, layers);
                        break;

                    default:
                        break;
                }
            }

            layers = layers->next;
        }
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

        SearchLayers(tilemap, tilemap.map->ly_head);

        return tilemap;
    }

    void FreeTilemap(Tilemap& tilemap)
    {
        tmx_map_free(tilemap.map);
    }
}
