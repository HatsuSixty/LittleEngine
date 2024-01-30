#pragma once

#include <raylib.h>
#include "../Consts.hpp"

#define MINIMUM_TILESET_WIDTH 10
#define MINIMUM_TILESET_HEIGHT 10
#define TILE_WIDTH ((float)WIDTH / MINIMUM_TILESET_WIDTH)
#define TILE_HEIGHT ((float)HEIGHT / MINIMUM_TILESET_HEIGHT)
#define V2(x, y) Vector2 { (x), (y) }

class Tile {
private:
    Texture m_texture;
    Vector2 m_tileCoordinates;

    bool m_isColor;
    Color m_tileColor;
public:
    bool m_collides;

    Tile(Color color, bool collides);
    Tile(char const* filePath, Vector2 tileCoordinates, bool collides);
    ~Tile();

    void render(int x, int y);
};
