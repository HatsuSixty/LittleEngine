#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <raylib.h>

#include "Box.hpp"
#include "Consts.hpp"
#include "Objects/ObjectManager.hpp"
#include "Player.hpp"
#include "Tiles/Tile.hpp"
#include "Tiles/Tileset.hpp"

int objectIdTracker = 0;

int main()
{
    InitWindow(WIDTH, HEIGHT, "Little Escondido");
    SetTargetFPS(60);

    Tile tiles[] = {
        Tile("./assets/test_tiles.png", 2, 2, 0, 0),
        Tile("./assets/test_tiles.png", 2, 2, 0, 1),
        Tile("./assets/test_tiles.png", 2, 2, 1, 0),
        Tile("./assets/test_tiles.png", 2, 2, 1, 1),
        Tile(RED),
        Tile(GREEN),
        Tile(BLUE),
        Tile(GRAY),
        Tile(PINK),
        Tile(BLACK),
        Tile("./assets/test_tiles.png", 2, 2, 1, 1),
        Tile(BLUE),
    };
    Tileset tileset(tiles, sizeof(tiles) / sizeof(tiles[0]), TILESET_WIDTH+1);

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

    Camera2D camera = {
        .offset = Vector2 {
            (float)WIDTH/2 - (float)PLAYER_WIDTH/2,
            (float)HEIGHT/2 - (float)PLAYER_HEIGHT/2,
        },
        .target = Vector2 { 0, 0 },
        .rotation = 0.0f,
        .zoom = 1.0f,
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(WHITE);

        tileset.update();
        objectManager.update();

        auto playerRec = player.getActualRectangle();
        camera.target = Vector2 { playerRec.x, playerRec.y };

        EndMode2D();
        EndDrawing();
    }

    return 0;
}
