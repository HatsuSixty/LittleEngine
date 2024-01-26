#pragma once

#include <string>
#include <unordered_map>
#include <raylib.h>

class AssetManager {
private:
    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Font> fonts;

public:
    Texture loadTexture(char const* path);
    Font loadFont(char const* font);
};
