#include <iostream>
#include <raylib.h>

#include "Consts.hpp"
#include "Objects/ObjectManager.hpp"
#include "Player.hpp"
#include "Box.hpp"

int objectIdTracker = 0;

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
