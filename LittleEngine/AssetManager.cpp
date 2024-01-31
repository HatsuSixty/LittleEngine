#include "LittleEngine/AssetManager.hpp"

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

Music AssetManager::loadMusic(char const* path)
{
    auto it = m_musics.find(path);
    if (it != m_musics.end()) {
        return it->second;
    }

    auto music = LoadMusicStream(path);
    m_musics[path] = music;

    return music;
}

Shader AssetManager::loadShader(char const* vsPath, char const* fsPath)
{
    auto key = ShaderKey { vsPath, fsPath };

    auto it = m_shaders.find(key);
    if (it != m_shaders.end()) {
        return it->second;
    }

    auto shader = LoadShader(vsPath, fsPath);
    m_shaders[key] = shader;

    return shader;
}
