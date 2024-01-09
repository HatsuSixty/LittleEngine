#include "Box.hpp"
#include "Player.hpp"

#include <iostream>
#include <raylib.h>

Box::Box(Vector2 position, Player* player)
{
    rec = Rectangle {
        .x = position.x,
        .y = position.y,
        .width = 40,
        .height = 40,
    };
    this->player = player;
}

void Box::update(ObjectManager* objmgr)
{
    (void)objmgr;
    if (CheckCollisionRecs(getActualRectangle(), player->getActualRectangle())
        && IsKeyPressed(KEY_ENTER)) {
        std::cout << "Nice!\n";
    }
    DrawRectangleRec(rec, YELLOW);
}

Rectangle Box::getCollisionRectangle()
{
    Rectangle coll = rec;
    coll.y += coll.height / 2;
    coll.height /= 2;
    return coll;
}

Rectangle Box::getActualRectangle()
{
    return rec;
}
