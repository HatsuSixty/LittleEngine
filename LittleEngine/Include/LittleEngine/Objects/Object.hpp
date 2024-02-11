#pragma once

#include <raylib.h>

class ObjectManager;

class Object {
private:
    int m_id;
    float m_moveSpeed;
    bool m_moving = false;
    Vector2 m_moveTarget = {0, 0};

public:
    Object();
    int getId();
    void printId(const char* file_name, int line);
    void updateImpl(ObjectManager* objmgr);
    void moveTo(Vector2 position, float speed);

    virtual void update(ObjectManager* objmgr) = 0;
    virtual Rectangle getCollisionRectangle() = 0;
    virtual Rectangle getActualRectangle() = 0;
    virtual void setPosition(Vector2 position) = 0;
};

#define printObjectId(object) (object).printId(__FILE__, __LINE__)
