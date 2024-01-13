#pragma once

#include "Tile.hpp"
#include <cstddef>

class Tileset {
private:
    Tile* tiles;

public:
    Tileset(Tile* tiles, size_t count);
    ~Tileset();

    void update();
};
