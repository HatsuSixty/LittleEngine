#include "Tileset.hpp"

#include "Tile.hpp"
#include <cstddef>
#include <cstdlib>
#include <cstring>

Tileset::Tileset(Tile* tiles, size_t count)
{
    this->tiles
        = (Tile*)std::malloc(TILESET_WIDTH * TILESET_HEIGHT * sizeof(Tile));
    std::memset(this->tiles, 0, TILESET_WIDTH * TILESET_HEIGHT * sizeof(Tile));
    std::memcpy(this->tiles, tiles, count * sizeof(Tile));
}

Tileset::~Tileset() { std::free(tiles); }

void Tileset::update()
{
    for (auto x = 0; x < TILESET_WIDTH; ++x) {
        for (auto y = 0; y < TILESET_HEIGHT; ++y) {
            auto tileX = x * TILE_WIDTH;
            auto tileY = y * TILE_HEIGHT;
            tiles[y * TILESET_WIDTH + x].render(tileX, tileY);
        }
    }
}
