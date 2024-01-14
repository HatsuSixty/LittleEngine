#pragma once

#include "Tile.hpp"

class Tileset {
private:
    Tile* tiles;
    int width;
    int height;

public:
    Tileset(Tile* tiles, int count, int width, int height);
    ~Tileset();

    void update();
    Vector2 getDimensions();
};
