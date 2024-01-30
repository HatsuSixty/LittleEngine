#pragma once

#include <string>
#include <unordered_map>
#include <raylib.h>

class AssetManager {
private:
    std::unordered_map<std::string, Texture> m_textures;
    std::unordered_map<std::string, Font> m_fonts;
    std::unordered_map<std::string, Sound> m_sounds;

public:
    Texture loadTexture(char const* path);
    Font loadFont(char const* path);
    Sound loadSound(char const* path);
};
