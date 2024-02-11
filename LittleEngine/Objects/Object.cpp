#include "LittleEngine/Objects/Object.hpp"

#include <iostream>
#include <raymath.h>

#include "LittleEngine/Objects/ObjectManager.hpp"

extern int objectIdTracker;

bool Vector2GreaterOrEqual(Vector2 a, Vector2 b)
{
    return a.x >= b.x && a.y >= b.y;
}

Object::Object()
{
    m_id = objectIdTracker;
    objectIdTracker += 1;
}

int Object::getId() { return m_id; }

void Object::moveTo(Vector2 position, float speed)
{
    m_moveTarget = position;
    m_moving = true;
    m_moveSpeed = speed;
}

void Object::updateImpl(ObjectManager* objmgr)
{
    if (m_moving) {
        if (objmgr->pointCollides(m_moveTarget)) {
            m_moving = false;
            goto out;
        }

        auto oldPos
            = Vector2 { getActualRectangle().x, getActualRectangle().y };
        auto newPos
            = Vector2Multiply(Vector2MoveTowards(oldPos, m_moveTarget, 1.0f),
                              Vector2 { m_moveSpeed, m_moveSpeed });
        setPosition(newPos);

        if (objmgr->collides(this)) {
            setPosition(oldPos);
        }

        if (Vector2GreaterOrEqual(newPos, m_moveTarget)) {
            m_moving = false;
        }
    }
out:

    update(objmgr);
}

void Object::printId(char const* file_name, int line)
{
    std::cout << file_name << ":" << line << ": Object ID: " << getId() << "\n";
}
