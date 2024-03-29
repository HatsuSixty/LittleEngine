// Example on how to use LittleEngine

#include <cstddef>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "LittleEngine/Consts.hpp"
#include "LittleEngine/DialogBox.hpp"
#include "LittleEngine/Objects/Object.hpp"
#include "LittleEngine/Objects/ObjectManager.hpp"
#include "LittleEngine/Settings.hpp"
#include "LittleEngine/Tiles/Tile.hpp"
#include "LittleEngine/Tiles/Tileset.hpp"
#include "LittleEngine/Translation.hpp"
#include "LittleEngine/Util.hpp"

#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 80
#define PLAYER_SPEED 200.0f
class Player : public Object {
private:
    Rectangle m_rec;

    void move(Vector2 direction)
    {
        m_rec.x += direction.x * PLAYER_SPEED * GetFrameTime();
        m_rec.y += direction.y * PLAYER_SPEED * GetFrameTime();
    }

public:
    Player(Vector2 position)
    {
        m_rec = Rectangle {
            .x = position.x,
            .y = position.y,
            .width = PLAYER_WIDTH,
            .height = PLAYER_HEIGHT,
        };
    }

    void update(ObjectManager* objmgr) override
    {
        auto direction = Vector2 {
            .x = (float)(GetKeyStrength(Settings::moveRightKey)
                         - GetKeyStrength(Settings::moveLeftKey)),
            .y = (float)(GetKeyStrength(Settings::moveDownKey)
                         - GetKeyStrength(Settings::moveUpKey)),
        };

        move(direction);

        if (objmgr->collides(this)) {
            move(Vector2 { .x = -direction.x, .y = -direction.y });
        }

        DrawRectangleRec(m_rec, RED);
    }

    Rectangle getCollisionRectangle() override
    {
        Rectangle coll = m_rec;
        coll.y += coll.height / 2;
        coll.height /= 2;
        return coll;
    }

    Rectangle getActualRectangle() override { return m_rec; }

    void setPosition(Vector2 position) override
    {
        m_rec.x = position.x;
        m_rec.y = position.y;
    }
};

class Box : public Object {
private:
    Rectangle m_rec;
    Player* m_player;
    DialogBox* m_dialogBox;

public:
    Box(Vector2 position, Player* player, DialogBox* dialogBox)
    {
        m_rec = Rectangle {
            .x = position.x,
            .y = position.y,
            .width = 40,
            .height = 40,
        };
        m_player = player;
        m_dialogBox = dialogBox;
    }

    void update(ObjectManager* objmgr) override
    {
        (void)objmgr;
        if (CheckCollisionRecs(getActualRectangle(),
                               m_player->getActualRectangle())
            && IsKeyPressed(Settings::interactionKey)) {
            char const* dialogs[]
                = { Translation::getText(
                        "the quick brown fox jumps over the lazy\ndog"),
                    Translation::getText(
                        "god yzal eht revo spmuj xof nworb kciuq\neht") };
            m_dialogBox->start(DialogBoxParameters {
                .dialogs = dialogs,
                .numDialogs = sizeof(dialogs) / sizeof(dialogs[0]),
            });
        }
        DrawRectangleRec(m_rec, YELLOW);
    }

    Rectangle getCollisionRectangle() override
    {
        Rectangle coll = m_rec;
        coll.y += coll.height / 2;
        coll.height /= 2;
        return coll;
    }

    Rectangle getActualRectangle() override { return m_rec; }

    void setPosition(Vector2 position) override
    {
        m_rec.x = position.x;
        m_rec.y = position.y;
    }
};

int main()
{
    InitWindow(WIDTH, HEIGHT, "LittleEngine Example");
    SetTargetFPS(60);

    Translation::loadTranslation("./Example/TestTranslation.txt");

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

        if (IsKeyPressed(KEY_F1)) {
            char const* dialogs[]
                = { Translation::getText("This is a dialog box"),
                    Translation::getText("And it works!") };
            dialogBox.start(DialogBoxParameters {
                .dialogs = dialogs,
                .numDialogs = sizeof(dialogs) / sizeof(dialogs[0]),
                .skippable = false,
            });
        }
        if (IsKeyPressed(KEY_F2)) {
            char const* dialogs[] = { "Test1", "Test2" };
            dialogBox.start(DialogBoxParameters {
                .dialogs = dialogs,
                .numDialogs = sizeof(dialogs) / sizeof(dialogs[0]),
                .useSound = false,
                .useCustomTextPosition = true,
                .textPosition = Vector2 { 0, 0 },
            });
        }
        if (IsKeyPressed(KEY_F3)) {
            auto playerPos = Vector2 { player.getActualRectangle().x,
                                       player.getActualRectangle().y };
            player.moveTo(Vector2AddValue(playerPos, 10), 1.0f);
        }

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
