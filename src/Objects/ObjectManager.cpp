#include "Object.hpp"

#include "ObjectManager.hpp"
#include <raylib.h>

ObjectManager::ObjectManager(Tileset* tileset) { this->tileset = tileset; }

void ObjectManager::update()
{
    std::vector<Object*> updateStack;
    for (auto o : objects) {
        if (updateStack.empty()) {
            updateStack.push_back(o);
            continue;
        }
        if (o->getCollisionRectangle().y
            < updateStack.back()->getCollisionRectangle().y) {
            updateStack.insert(updateStack.begin(), o);
        } else {
            updateStack.push_back(o);
        }
    }

    for (auto o : updateStack) {
        o->update(this);
    }
}

void ObjectManager::addObject(Object* obj) { objects.push_back(obj); }

bool ObjectManager::collides(Object* obj)
{
    for (auto o : objects) {
        if ((o->getId() != obj->getId()
             && CheckCollisionRecs(obj->getCollisionRectangle(),
                                   o->getCollisionRectangle()))
            || tileset->collides(obj))
            return true;
    }
    return false;
}
