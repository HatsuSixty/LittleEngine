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

int objectIdTracker = 0;

#define TILESET_WIDTH 10
#define TILESET_HEIGHT 10
#define TILE_WIDTH ((float)WIDTH / TILESET_WIDTH)
#define TILE_HEIGHT ((float)HEIGHT / TILESET_HEIGHT)

class Tile {
private:
    Texture texture;
    int numTilesX;
    int numTilesY;
    int tileIndexX;
    int tileIndexY;

    bool isColor;
    Color tileColor;

public:
    Tile(Color color);
    Tile(char const* filePath, int numX, int numY, int tileIndexX, int tileIndexY);
    ~Tile();

    void render(int x, int y);
};

Tile::Tile(Color color)
{
    tileColor = color;
    isColor = true;
}

Tile::Tile(char const* filePath, int numX, int numY, int tileIndexX, int tileIndexY)
{
    auto image = LoadImage(filePath);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);

    numTilesX = numX;
    numTilesY = numY;
    this->tileIndexX = tileIndexX;
    this->tileIndexY = tileIndexY;

    isColor = false;
}

Tile::~Tile()
{
    if (!isColor)
        UnloadTexture(texture);
}

void Tile::render(int x, int y)
{
    if (isColor) {
        DrawRectangle(x, y, TILE_WIDTH, TILE_HEIGHT, tileColor);
    } else {
        DrawTexturePro(texture,
                       Rectangle {
                           .x = (float)tileIndexX*TILE_WIDTH,
                           .y = (float)tileIndexY*TILE_HEIGHT,
                           .width = (float)TILE_WIDTH,
                           .height = (float)TILE_HEIGHT,
                       },
                       Rectangle {
                           .x = (float)x,
                           .y = (float)y,
                           .width = (float)TILE_WIDTH,
                           .height = (float)TILE_HEIGHT,
                       },
                       Vector2 { 0, 0 }, 0.0f, WHITE);
    }
}

class Tileset {
private:
    Tile* tiles;

public:
    Tileset(Tile* tiles, size_t count);
    ~Tileset();

    void update();
};

Tileset::Tileset(Tile* tiles, size_t count)
{
    this->tiles
        = (Tile*)std::malloc(TILESET_WIDTH * TILESET_HEIGHT * sizeof(Tile));
    std::memset(this->tiles, 0, TILESET_WIDTH * TILESET_HEIGHT * sizeof(Tile));
    std::memcpy(this->tiles, tiles, count * sizeof(Tile));
}

Tileset::~Tileset() { std::free(tiles); }

void Tileset::update()
{
    for (auto x = 0; x < TILESET_WIDTH; ++x) {
        for (auto y = 0; y < TILESET_HEIGHT; ++y) {
            auto tileX = x * TILE_WIDTH;
            auto tileY = y * TILE_HEIGHT;
            tiles[y * TILESET_WIDTH + x].render(tileX, tileY);
        }
    }
}

int main()
{
    InitWindow(WIDTH, HEIGHT, "Little Escondido");
    SetTargetFPS(60);

    Tile tiles[] = {
        Tile("./assets/test_tiles.png", 2, 2, 0, 0),
        Tile("./assets/test_tiles.png", 2, 2, 0, 1),
        Tile("./assets/test_tiles.png", 2, 2, 1, 0),
        Tile("./assets/test_tiles.png", 2, 2, 1, 1),
    };
    Tileset tileset(tiles, sizeof(tiles) / sizeof(tiles[0]));

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

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        tileset.update();
        objectManager.update();

        EndDrawing();
    }

    // CloseWindow();

    return 0;
}
