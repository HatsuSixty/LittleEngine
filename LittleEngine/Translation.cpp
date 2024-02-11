#include "LittleEngine/Translation.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> splitString(std::string s, std::string delimiter)
{
    std::vector<std::string> tokens;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

    return tokens;
}

// https://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
void replaceAll(std::string& str, std::string const& from,
                std::string const& to)
{
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like
                                  // replacing 'x' with 'yx'
    }
}

std::unordered_map<std::string, std::string> translations;

void Translation::loadTranslation(char const* path)
{
    std::fstream file(path);

    std::string line;
    auto linum = 0;
    while (std::getline(file, line)) {
        auto keyValue = splitString(line, "=");
        if (keyValue.size() != 2) {
            std::cerr << path << ":" << linum
                      << ": WARNING: invalid syntax. Ignoring...\n";
            std::cerr
                << path << ":" << linum
                << ": NOTE: translations must be in the format `hello=olá=`\n";
        } else {
            replaceAll(keyValue[0], "\\n", "\n");
            replaceAll(keyValue[1], "\\n", "\n");
            translations[keyValue[0]] = keyValue[1];
        }
        linum++;
    }

    file.close();
}

char const* Translation::getText(char const* text)
{
    if (translations.contains(text))
        return translations[text].c_str();
    return text;
}
