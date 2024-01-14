#pragma once

#include "Tile.hpp"

class Tileset {
private:
    Tile* tiles;
    int length;

public:
    Tileset(Tile* tiles, int count, int length);
    ~Tileset();

    void update();
    Vector2 getDimensions();
};
