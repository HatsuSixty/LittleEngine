#include "Player.hpp"

#include <raylib.h>
#include "Consts.hpp"
#include "Util.hpp"
#include "Objects/ObjectManager.hpp"

Player::Player(Vector2 position)
{
    rec = Rectangle {
        .x = position.x,
        .y = position.y,
        .width = PLAYER_WIDTH,
        .height = PLAYER_HEIGHT,
    };
}

void Player::update(ObjectManager* objmgr)
{
    auto direction = Vector2 {
        .x = (float)(GetKeyStrength(KEY_RIGHT) - GetKeyStrength(KEY_LEFT)),
        .y = (float)(GetKeyStrength(KEY_DOWN) - GetKeyStrength(KEY_UP)),
    };

    move(direction);

    if (objmgr->collides(this)) {
        move(Vector2 { .x = -direction.x, .y = -direction.y });
    }

    DrawRectangleRec(rec, RED);
}

Rectangle Player::getCollisionRectangle()
{
    Rectangle coll = rec;
    coll.y += coll.height/2;
    coll.height /= 2;
    return coll;
}

Rectangle Player::getActualRectangle()
{
    return rec;
}

void Player::move(Vector2 direction)
{
    rec.x += direction.x * PLAYER_SPEED * GetFrameTime();
    rec.y += direction.y * PLAYER_SPEED * GetFrameTime();
}
