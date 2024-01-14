#include "Tileset.hpp"

#include "Tile.hpp"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>

Tileset::Tileset(Tile* tiles, int count, int length)
{
    assert(length >= TILESET_WIDTH && "Invalid tilesed length");

    this->tiles = (Tile*)std::malloc(length * TILESET_HEIGHT * sizeof(Tile));
    this->length = length;
    std::memset(this->tiles, 0, length * TILESET_HEIGHT * sizeof(Tile));
    std::memcpy(this->tiles, tiles, count * sizeof(Tile));
}

Tileset::~Tileset() { std::free(tiles); }

void Tileset::update()
{
    for (auto x = 0; x < length; ++x) {
        for (auto y = 0; y < TILESET_HEIGHT; ++y) {
            auto tileX = x * TILE_WIDTH;
            auto tileY = y * TILE_HEIGHT;
            tiles[y * length + x].render(tileX, tileY);
        }
    }
}

Vector2 Tileset::getDimensions()
{
    return Vector2 { length * TILE_WIDTH, TILESET_HEIGHT * TILE_HEIGHT };
}
