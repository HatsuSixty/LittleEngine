// Example on how to use LittleEngine

#include <iostream>
#include <raylib.h>

#include "LittleEngine/Consts.hpp"
#include "LittleEngine/DialogBox.hpp"
#include "LittleEngine/Objects/Object.hpp"
#include "LittleEngine/Objects/ObjectManager.hpp"
#include "LittleEngine/Settings.hpp"
#include "LittleEngine/Tiles/Tile.hpp"
#include "LittleEngine/Tiles/Tileset.hpp"
#include "LittleEngine/Util.hpp"

#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 80
#define PLAYER_SPEED 200.0f
class Player : public Object {
private:
    Rectangle rec;

public:
    Player(Vector2 position)
    {
        rec = Rectangle {
            .x = position.x,
            .y = position.y,
            .width = PLAYER_WIDTH,
            .height = PLAYER_HEIGHT,
        };
    }

    void update(ObjectManager* objmgr) override
    {
        auto direction = Vector2 {
            .x = (float)(GetKeyStrength(Settings::moveRightKey) - GetKeyStrength(Settings::moveLeftKey)),
            .y = (float)(GetKeyStrength(Settings::moveDownKey) - GetKeyStrength(Settings::moveUpKey)),
        };

        move(direction);

        if (objmgr->collides(this)) {
            move(Vector2 { .x = -direction.x, .y = -direction.y });
        }

        DrawRectangleRec(rec, RED);
    }

    Rectangle getCollisionRectangle() override
    {
        Rectangle coll = rec;
        coll.y += coll.height / 2;
        coll.height /= 2;
        return coll;
    }

    Rectangle getActualRectangle() override { return rec; }

    void move(Vector2 direction)
    {
        rec.x += direction.x * PLAYER_SPEED * GetFrameTime();
        rec.y += direction.y * PLAYER_SPEED * GetFrameTime();
    }
};

class Box : public Object {
private:
    Rectangle rec;
    Player* player;
    DialogBox* dialogBox;

public:
    Box(Vector2 position, Player* player, DialogBox* dialogBox)
    {
        rec = Rectangle {
            .x = position.x,
            .y = position.y,
            .width = 40,
            .height = 40,
        };
        this->player = player;
        this->dialogBox = dialogBox;
    }

    void update(ObjectManager* objmgr) override
    {
        (void)objmgr;
        if (CheckCollisionRecs(getActualRectangle(),
                               player->getActualRectangle())
            && IsKeyPressed(Settings::interactionKey)) {
            char const* dialogs[]
                = { "the quick brown fox jumps over the lazy dog",
                    "god yzal eht revo spmuj xof nworb kciuq eht" };
            dialogBox->start(dialogs, sizeof(dialogs) / sizeof(dialogs[0]));
        }
        DrawRectangleRec(rec, YELLOW);
    }

    Rectangle getCollisionRectangle() override
    {
        Rectangle coll = rec;
        coll.y += coll.height / 2;
        coll.height /= 2;
        return coll;
    }

    Rectangle getActualRectangle() override { return rec; }
};

int main()
{
    InitWindow(WIDTH, HEIGHT, "Little Escondido");
    SetTargetFPS(60);

    DialogBox dialogBox;

    Tile tiles[] = {
        Tile("./Assets/test_tiles.png", V2(0, 0), false),
        Tile("./Assets/test_tiles.png", V2(0, 1), false),
        Tile("./Assets/test_tiles.png", V2(1, 0), false),
        Tile("./Assets/test_tiles.png", V2(1, 1), false),
        Tile(RED, false),
        Tile(GREEN, false),
        Tile(BLUE, false),
        Tile(GRAY, true /* Specifies whether this tile
                         * can collide with objects or not */),
        Tile(PINK, false),
        Tile(BLACK, false),
        Tile("./Assets/test_tiles.png", V2(1, 1), false),
        Tile(BLUE, false),
    };
    Tileset tileset(tiles, sizeof(tiles) / sizeof(tiles[0]),
                    /* Dimensions of the tileset */
                    MINIMUM_TILESET_WIDTH + 1, MINIMUM_TILESET_HEIGHT + 1);

    /* Instantiate an ObjectManager and add objects to it */
    ObjectManager objectManager(&tileset);

    Player player(Vector2 { (float)WIDTH / 2 - (float)PLAYER_WIDTH / 2,
                            (float)HEIGHT / 2 - (float)PLAYER_HEIGHT / 2 });
    Box testBoxA(Vector2 { 0, (float)HEIGHT / 2 }, &player, &dialogBox);
    Box testBoxB(Vector2 { (float)WIDTH / 2 - 20, (float)HEIGHT / 2 + 50 },
                 &player, &dialogBox);

    objectManager.addObject(&player);
    objectManager.addObject(&testBoxA);
    objectManager.addObject(&testBoxB);

    printObjectId(player);
    printObjectId(testBoxA);
    printObjectId(testBoxB);

    /* Actual gameloop stuff */
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
        ClearBackground(WHITE);

        BeginMode2D(camera);

        /* Update objects, tiles, and dialogs */
        tileset.update();
        objectManager.update();
        scrollCameraWithPlayer(&camera, &player, &tileset);

        EndMode2D();

        dialogBox.update();

        EndDrawing();
    }

    return 0;
}
