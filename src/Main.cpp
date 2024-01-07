#include <iostream>

#include <raylib.h>

#include "Consts.hpp"
#include "Objects/ObjectManager.hpp"
#include "Player.hpp"

int objectIdTracker = 0;

class Box : public Object {
private:
    Rectangle rec;

public:
    Box(Vector2 position);
    void update(ObjectManager* objmgr) override;
    Rectangle getCollisionRectangle() override;
};

Box::Box(Vector2 position)
{
    rec = Rectangle {
        .x = position.x,
        .y = position.y,
        .width = 40,
        .height = 40,
    };
}

void Box::update(ObjectManager* objmgr)
{
    (void)objmgr;
    DrawRectangleRec(rec, YELLOW);
}

Rectangle Box::getCollisionRectangle()
{
    Rectangle coll = rec;
    coll.y += coll.height/2;
    coll.height /= 2;
    return coll;
}

int main()
{
    ObjectManager objectManager;
    Player player(Vector2{WIDTH, HEIGHT});
    Box box(Vector2{0, 0});
    Box box2(Vector2{(float)WIDTH/2, (float)HEIGHT/2});
    objectManager.addObject(&player);
    objectManager.addObject(&box);
    objectManager.addObject(&box2);

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
