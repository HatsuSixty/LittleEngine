#pragma once

#include <raylib.h>
#include <vector>

#include "Object.hpp"

class ObjectManager {
private:
    std::vector<Object*> objects;

public:
    void addObject(Object* obj);
    bool collides(Object* obj);
    void update();
};
