#pragma once

#include <string>
#include <unordered_map>
#include <raylib.h>

struct ShaderKey {
    std::string vsPath;
    std::string fsPath;

    bool operator==(const ShaderKey& other) const {
        return vsPath == other.vsPath && fsPath == other.fsPath;
    }
};

namespace std {
    template <>
    struct hash<ShaderKey> {
        std::size_t operator()(const ShaderKey& s) const {
            return hash<std::string>()(s.vsPath) ^ (hash<std::string>()(s.fsPath) << 1);
        }
    };
}

class AssetManager {
private:
    std::unordered_map<std::string, Texture> m_textures;
    std::unordered_map<std::string, Font> m_fonts;
    std::unordered_map<std::string, Sound> m_sounds;
    std::unordered_map<std::string, Music> m_musics;
    std::unordered_map<ShaderKey, Shader> m_shaders;

public:
    Texture loadTexture(char const* path);
    Font loadFont(char const* path);
    Sound loadSound(char const* path);
    Music loadMusic(char const* path);
    Shader loadShader(char const* vsPath, char const* fsPath);
};

extern AssetManager assetManager;
