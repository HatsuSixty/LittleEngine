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
        Tile("./assets/test_tiles.png", V2(0, 0), false),
        Tile("./assets/test_tiles.png", V2(0, 1), false),
        Tile("./assets/test_tiles.png", V2(1, 0), false),
        Tile("./assets/test_tiles.png", V2(1, 1), false),
        Tile(RED, false),
        Tile(GREEN, false),
        Tile(BLUE, false),
        Tile(GRAY, true),
        Tile(PINK, false),
        Tile(BLACK, false),
        Tile("./assets/test_tiles.png", V2(1, 1), false),
        Tile(BLUE, false),
    };
    Tileset tileset(tiles, sizeof(tiles) / sizeof(tiles[0]),
                    MINIMUM_TILESET_WIDTH + 1, MINIMUM_TILESET_HEIGHT + 1);

    ObjectManager objectManager(&tileset);

    Player player(Vector2 { (float)WIDTH / 2 - (float)PLAYER_WIDTH / 2,
                            (float)HEIGHT / 2 - (float)PLAYER_HEIGHT / 2 });
    Box testBoxA(Vector2 { 0, (float)HEIGHT / 2 }, &player);
    Box testBoxB(Vector2 { (float)WIDTH / 2 - 20, (float)HEIGHT / 2 + 50 },
                 &player);

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
    Vector2 cameraTarget;

    while (!WindowShouldClose()) {
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(WHITE);

        tileset.update();
        objectManager.update();

        camera.target = cameraTarget;

        auto playerRec = player.getActualRectangle();
        auto tilesetDims = tileset.getDimensions();
        if (((playerRec.x - camera.offset.x) >= 0)
            && ((playerRec.x + playerRec.width + camera.offset.x)
                <= tilesetDims.x)) {
            cameraTarget.x = playerRec.x;
        }
        if (((playerRec.y - camera.offset.y) >= 0)
            && ((playerRec.y + playerRec.height + camera.offset.y)
                <= tilesetDims.y)) {
            cameraTarget.y = playerRec.y;
        }

        EndMode2D();
        EndDrawing();
    }

    return 0;
}
