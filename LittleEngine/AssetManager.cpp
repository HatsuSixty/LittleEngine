#include "AssetManager.hpp"

#include <raylib.h>

Texture AssetManager::loadTexture(char const* path)
{
    auto it = textures.find(path);
    if (it != textures.end()) {
        return it->second;
    }

    auto img = LoadImage(path);
    auto txt = LoadTextureFromImage(img);
    UnloadImage(img);

    textures[path] = txt;
    return txt;
}

Font AssetManager::loadFont(char const* path)
{
    auto it = fonts.find(path);
    if (it != fonts.end()) {
        return it->second;
    }

    auto font = LoadFont(path);
    fonts[path] = font;

    return font;
}

Sound AssetManager::loadSound(char const* path)
{
    auto it = sounds.find(path);
    if (it != sounds.end()) {
        return it->second;
    }

    auto sound = LoadSound(path);
    sounds[path] = sound;

    return sound;
}
