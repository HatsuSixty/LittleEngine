// Example on how to use LittleEngine

#include <iostream>
#include <raylib.h>

#include "LittleEngine/Consts.hpp"
#include "LittleEngine/Objects/Object.hpp"
#include "LittleEngine/Objects/ObjectManager.hpp"
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
            .x = (float)(GetKeyStrength(KEY_RIGHT) - GetKeyStrength(KEY_LEFT)),
            .y = (float)(GetKeyStrength(KEY_DOWN) - GetKeyStrength(KEY_UP)),
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

public:
    Box(Vector2 position, Player* player)
    {
        rec = Rectangle {
            .x = position.x,
            .y = position.y,
            .width = 40,
            .height = 40,
        };
        this->player = player;
    }

    void update(ObjectManager* objmgr) override
    {
        (void)objmgr;
        if (CheckCollisionRecs(getActualRectangle(),
                               player->getActualRectangle())
            && IsKeyPressed(KEY_ENTER)) {
            std::cout << "Nice!\n";
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
    Box testBoxA(Vector2 { 0, (float)HEIGHT / 2 }, &player);
    Box testBoxB(Vector2 { (float)WIDTH / 2 - 20, (float)HEIGHT / 2 + 50 },
                 &player);

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
    Vector2 cameraTarget;

    while (!WindowShouldClose()) {
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(WHITE);

        /* Update objects and tiles */
        tileset.update();
        objectManager.update();

        /* Update camera */
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
