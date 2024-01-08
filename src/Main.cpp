#include <iostream>

#include <raylib.h>

#include "Consts.hpp"
#include "Objects/Object.hpp"
#include "Objects/ObjectManager.hpp"
#include "Player.hpp"

int objectIdTracker = 0;

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

int main()
{
    ObjectManager objectManager;

    Player player(Vector2 { WIDTH - 50, HEIGHT - 50 });
    Box testBoxA(Vector2 { 0, 0 }, &player);
    Box testBoxB(Vector2 { (float)WIDTH / 2, (float)HEIGHT / 2 }, &player);

    objectManager.addObject(&player);
    objectManager.addObject(&testBoxA);
    objectManager.addObject(&testBoxB);

    printObjectId(player);
    printObjectId(testBoxA);
    printObjectId(testBoxB);

    InitWindow(WIDTH, HEIGHT, "Little Escondido");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        objectManager.update();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
