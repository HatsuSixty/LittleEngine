#include "LittleEngine/Settings.hpp"

#include <raylib.h>
#include <string>

KeyboardKey Settings::secondaryInteractionKey = KEY_X;
KeyboardKey Settings::interactionKey = KEY_ENTER;
KeyboardKey Settings::moveDownKey = KEY_DOWN;
KeyboardKey Settings::moveLeftKey = KEY_LEFT;
KeyboardKey Settings::moveRightKey = KEY_RIGHT;
KeyboardKey Settings::moveUpKey = KEY_UP;
std::string Settings::defaultDialogImage = "./Assets/default_dialog_image.png";
std::string Settings::defaultDialogSound = "./Assets/default_dialog_sound.wav";
unsigned int Settings::brightColor = 0xFFD0EDFF;
unsigned int Settings::darkColor = 0x140810FF;
std::string Settings::defaultFont = "";

void Settings::setInteractionKey(KeyboardKey key) { interactionKey = key; }
void Settings::setMoveDownKey(KeyboardKey key) { moveDownKey = key; }
void Settings::setMoveLeftKey(KeyboardKey key) { moveLeftKey = key; }
void Settings::setMoveRightKey(KeyboardKey key) { moveRightKey = key; }
void Settings::setMoveUpKey(KeyboardKey key) { moveUpKey = key; }
void Settings::setDefaultDialogImage(std::string image)
{
    defaultDialogImage = image;
}
void Settings::setBrightColor(unsigned int color) { brightColor = color; }
void Settings::setDarkColor(unsigned int color) { darkColor = color; }
void Settings::setDefaultFont(std::string font) { defaultFont = font; }
