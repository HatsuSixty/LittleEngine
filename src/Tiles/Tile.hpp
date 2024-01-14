#pragma once

#include <raylib.h>
#include "../Consts.hpp"

#define MINIMUM_TILESET_WIDTH 10
#define MINIMUM_TILESET_HEIGHT 10
#define TILE_WIDTH ((float)WIDTH / MINIMUM_TILESET_WIDTH)
#define TILE_HEIGHT ((float)HEIGHT / MINIMUM_TILESET_HEIGHT)

class Tile {
private:
    Texture texture;
    int numTilesX;
    int numTilesY;
    int tileIndexX;
    int tileIndexY;

    bool isColor;
    Color tileColor;

public:
    Tile(Color color);
    Tile(char const* filePath, int numX, int numY, int tileIndexX, int tileIndexY);
    ~Tile();

    void render(int x, int y);
};
