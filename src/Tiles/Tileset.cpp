#include "Tileset.hpp"

#include "Tile.hpp"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <raylib.h>

Tileset::Tileset(Tile* tiles, int count, int width, int height)
{
    assert(width >= MINIMUM_TILESET_WIDTH && "Invalid tileset width");
    assert(width >= MINIMUM_TILESET_HEIGHT && "Invalid tileset width");

    this->tiles = (Tile*)std::malloc(width * height * sizeof(Tile));
    this->width = width;
    this->height = height;
    std::memset(this->tiles, 0, width * height * sizeof(Tile));
    std::memcpy(this->tiles, tiles, count * sizeof(Tile));
}

Tileset::~Tileset() { std::free(tiles); }

void Tileset::update()
{
    for (auto x = 0; x < width; ++x) {
        for (auto y = 0; y < height; ++y) {
            auto tileX = x * TILE_WIDTH;
            auto tileY = y * TILE_HEIGHT;
            tiles[y * width + x].render(tileX, tileY);
        }
    }
}

Vector2 Tileset::getDimensions()
{
    return Vector2 { width * TILE_WIDTH, height * TILE_HEIGHT };
}

bool Tileset::collides(Object* obj)
{
    for (auto x = 0; x < width; ++x) {
        for (auto y = 0; y < height; ++y) {
            if (!tiles[y * width + x].collides)
                continue;
            Rectangle a = obj->getCollisionRectangle();
            Rectangle b = {
                .x = x * TILE_WIDTH,
                .y = y * TILE_HEIGHT,
                .width = TILE_WIDTH,
                .height = TILE_HEIGHT,
            };
            if (CheckCollisionRecs(a, b))
                return true;
        }
    }
    return false;
}
