#pragma once

#include <string>
#include <unordered_map>
#include <raylib.h>

class AssetManager {
private:
    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Font> fonts;
    std::unordered_map<std::string, Sound> sounds;

public:
    Texture loadTexture(char const* path);
    Font loadFont(char const* path);
    Sound loadSound(char const* path);
};
