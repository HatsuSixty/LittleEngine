#include "AssetManager.hpp"

#include <raylib.h>

Texture AssetManager::loadTexture(char const* path)
{
    auto it = m_textures.find(path);
    if (it != m_textures.end()) {
        return it->second;
    }

    auto img = LoadImage(path);
    auto txt = LoadTextureFromImage(img);
    UnloadImage(img);

    m_textures[path] = txt;
    return txt;
}

Font AssetManager::loadFont(char const* path)
{
    auto it = m_fonts.find(path);
    if (it != m_fonts.end()) {
        return it->second;
    }

    auto font = LoadFont(path);
    m_fonts[path] = font;

    return font;
}

Sound AssetManager::loadSound(char const* path)
{
    auto it = m_sounds.find(path);
    if (it != m_sounds.end()) {
        return it->second;
    }

    auto sound = LoadSound(path);
    m_sounds[path] = sound;

    return sound;
}
