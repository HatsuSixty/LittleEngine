#include "Tile.hpp"

#include <raylib.h>

Tile::Tile(Color color)
{
    tileColor = color;
    isColor = true;
}

Tile::Tile(char const* filePath, Vector2 tileCoordinates)
{
    auto image = LoadImage(filePath);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);

    this->tileCoordinates = tileCoordinates;

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
                           .x = (float)tileCoordinates.x*TILE_WIDTH,
                           .y = (float)tileCoordinates.y*TILE_HEIGHT,
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
