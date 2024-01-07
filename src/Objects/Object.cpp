#include "Object.hpp"

extern int objectIdTracker;

Object::Object()
{
    id = objectIdTracker;
    objectIdTracker += 1;
}

int Object::getId()
{
    return id;
}
