#pragma once

#include "LittleEngine/Objects/Object.hpp"
#include "Tile.hpp"

class Tileset {
private:
    Tile* m_tiles;
    int m_width;
    int m_height;

public:
    Tileset(Tile* tiles, int count, int width, int height);
    ~Tileset();

    void update();
    Vector2 getDimensions();
    bool collides(Object* obj);
};
