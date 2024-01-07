#pragma once

#include <raylib.h>

class ObjectManager;

class Object {
private:
    int id;
public:
    Object();
    int getId();

    virtual void update(ObjectManager* objmgr) = 0;
    virtual Rectangle getCollisionRectangle() = 0;
};
