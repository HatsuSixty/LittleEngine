#include "Object.hpp"

#include "ObjectManager.hpp"
#include <raylib.h>

void ObjectManager::update()
{
    std::vector<Object*> update_stack;
    for (auto o : objects) {
        if (update_stack.empty()) {
            update_stack.push_back(o);
            continue;
        }
        if (o->getCollisionRectangle().y < update_stack.back()->getCollisionRectangle().y) {
            update_stack.insert(update_stack.begin(), o);
        } else {
            update_stack.push_back(o);
        }
    }

    for (auto o : update_stack) {
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
