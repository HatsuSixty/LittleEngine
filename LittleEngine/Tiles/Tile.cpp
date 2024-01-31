#include "LittleEngine/Tiles/Tile.hpp"

#include "LittleEngine/AssetManager.hpp"
#include <raylib.h>

Tile::Tile(Color color, bool collides)
{
    m_tileColor = color;
    m_isColor = true;
    m_collides = collides;
}

Tile::Tile(char const* filePath, Vector2 tileCoordinates, bool collides)
{
    m_texture = assetManager.loadTexture(filePath);
    m_tileCoordinates = tileCoordinates;
    m_collides = collides;
    m_isColor = false;
}

Tile::~Tile()
{
    if (!m_isColor)
        UnloadTexture(m_texture);
}

void Tile::render(int x, int y)
{
    if (m_isColor) {
        DrawRectangle(x, y, TILE_WIDTH, TILE_HEIGHT, m_tileColor);
    } else {
        DrawTexturePro(m_texture,
                       Rectangle {
                           .x = (float)m_tileCoordinates.x*TILE_WIDTH,
                           .y = (float)m_tileCoordinates.y*TILE_HEIGHT,
                           .width = (float)TILE_WIDTH,
                           .height = (float)TILE_HEIGHT,
                       },
                       Rectangle {
                           .x = (float)x,
                           .y = (float)y,
                           .width = (float)TILE_WIDTH,
                           .height = (float)TILE_HEIGHT,
                       },
                       Vector2 { 0, 0 }, 0.0f, WHITE);
    }
}
