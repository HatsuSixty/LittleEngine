#include "LittleEngine/Util.hpp"

#include <raylib.h>

#include "LittleEngine/Tiles/Tileset.hpp"
#include "LittleEngine/Objects/Object.hpp"

int GetKeyStrength(int key)
{
    if (IsKeyDown(key))
        return 1;
    return 0;
}

void scrollCameraWithPlayer(Camera2D* camera, Object* player, Tileset* tileset)
{
    auto playerRec = player->getActualRectangle();
    auto tilesetDims = tileset->getDimensions();
    if (((playerRec.x - camera->offset.x) >= 0)
        && ((playerRec.x + playerRec.width + camera->offset.x)
            <= tilesetDims.x)) {
        camera->target.x = playerRec.x;
    }
    if (((playerRec.y - camera->offset.y) >= 0)
        && ((playerRec.y + playerRec.height + camera->offset.y)
            <= tilesetDims.y)) {
        camera->target.y = playerRec.y;
    }
}
