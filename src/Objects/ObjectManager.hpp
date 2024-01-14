#pragma once

#include <raylib.h>
#include <vector>

#include "Object.hpp"
#include "Tiles/Tileset.hpp"

class ObjectManager {
private:
    std::vector<Object*> objects;
    Tileset* tileset;

public:
    ObjectManager(Tileset* tileset);

    void addObject(Object* obj);
    bool collides(Object* obj);
    void update();
};
