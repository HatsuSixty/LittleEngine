#pragma once

#include <raylib.h>

class ObjectManager;

class Object {
private:
    int id;
public:
    Object();
    int getId();
    void printId(const char* file_name, int line);

    virtual void update(ObjectManager* objmgr) = 0;
    virtual Rectangle getCollisionRectangle() = 0;
    virtual Rectangle getActualRectangle() = 0;
};

#define printObjectId(object) (object).printId(__FILE__, __LINE__)
