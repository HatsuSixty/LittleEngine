#pragma once

#include <raylib.h>

#include "LittleEngine/Objects/Object.hpp"
#include "LittleEngine/Tiles/Tileset.hpp"

int GetKeyStrength(int key);
void scrollCameraWithPlayer(Camera2D* camera, Object* player, Tileset* tileset);
