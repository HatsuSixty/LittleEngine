#include "Object.hpp"

#include "ObjectManager.hpp"
#include <raylib.h>

void ObjectManager::update()
{
    for (auto o : objects) {
        o->update(this);
    }
}

void ObjectManager::addObject(Object* obj)
{
    objects.push_back(obj);
}

bool ObjectManager::collides(Object* obj)
{
    for (auto o : objects) {
        if (o->getId() != obj->getId() && CheckCollisionRecs(obj->getCollisionRectangle(), o->getCollisionRectangle()))
            return true;
    }
    return false;
}
