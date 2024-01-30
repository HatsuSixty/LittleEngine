#include "LittleEngine/Tiles/Tileset.hpp"

#include "LittleEngine/Tiles/Tile.hpp"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <raylib.h>

Tileset::Tileset(Tile* tiles, int count, int width, int height)
{
    assert(width >= MINIMUM_TILESET_WIDTH && "Invalid tileset width");
    assert(width >= MINIMUM_TILESET_HEIGHT && "Invalid tileset width");

    m_tiles = (Tile*)std::malloc(width * height * sizeof(Tile));
    m_width = width;
    m_height = height;
    std::memset(m_tiles, 0, width * height * sizeof(Tile));
    std::memcpy(m_tiles, tiles, count * sizeof(Tile));
}

Tileset::~Tileset() { std::free(m_tiles); }

void Tileset::update()
{
    for (auto x = 0; x < m_width; ++x) {
        for (auto y = 0; y < m_height; ++y) {
            auto tileX = x * TILE_WIDTH;
            auto tileY = y * TILE_HEIGHT;
            m_tiles[y * m_width + x].render(tileX, tileY);
        }
    }
}

Vector2 Tileset::getDimensions()
{
    return Vector2 { m_width * TILE_WIDTH, m_height * TILE_HEIGHT };
}

bool Tileset::collides(Object* obj)
{
    for (auto x = 0; x < m_width; ++x) {
        for (auto y = 0; y < m_height; ++y) {
            if (!m_tiles[y * m_width + x].m_collides)
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

            auto tilesetDims = getDimensions();
            auto objActualRec = obj->getActualRectangle();
            if ((objActualRec.x + objActualRec.width > tilesetDims.x)
                || (objActualRec.y + objActualRec.height > tilesetDims.y)
                || (objActualRec.x < 0) || (objActualRec.y < 0))
                return true;
        }
    }
    return false;
}
