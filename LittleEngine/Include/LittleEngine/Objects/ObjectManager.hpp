#pragma once

#include <raylib.h>
#include <vector>

#include "Object.hpp"
#include "LittleEngine/Tiles/Tileset.hpp"

class ObjectManager {
private:
    std::vector<Object*> m_objects;
    Tileset* m_tileset;

public:
    ObjectManager(Tileset* tileset);

    void addObject(Object* obj);
    bool collides(Object* obj);
    void update();
};
