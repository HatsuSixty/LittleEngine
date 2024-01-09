#pragma once

#include <raylib.h>

#include "Objects/Object.hpp"
#include "Player.hpp"

class Box : public Object {
private:
    Rectangle rec;
    Player* player;

public:
    Box(Vector2 position, Player* player);
    void update(ObjectManager* objmgr) override;
    Rectangle getCollisionRectangle() override;
    Rectangle getActualRectangle() override;
};
