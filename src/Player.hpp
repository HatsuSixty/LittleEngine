#pragma once

#include "Objects/Object.hpp"

#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 80
#define PLAYER_SPEED 200.0f
class Player : public Object {
private:
    Rectangle rec;

public:
    Player(Vector2 position);
    void update(ObjectManager* objmgr) override;
    Rectangle getCollisionRectangle() override;
    Rectangle getActualRectangle() override;

    void move(Vector2 direction);
};
