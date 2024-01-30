#include "LittleEngine/Objects/Object.hpp"

#include <iostream>

extern int objectIdTracker;

Object::Object()
{
    m_id = objectIdTracker;
    objectIdTracker += 1;
}

int Object::getId()
{
    return m_id;
}

void Object::printId(const char* file_name, int line)
{
    std::cout << file_name << ":" << line
              << ": Object ID: " << getId() << "\n";
}
