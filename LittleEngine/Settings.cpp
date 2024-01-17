#include "LittleEngine/Settings.hpp"

#include <raylib.h>

unsigned int Settings::brightColor   = 0xFFD0EDFF;
unsigned int Settings::darkColor     = 0x140810FF;
KeyboardKey Settings::interactionKey = KEY_ENTER;
KeyboardKey Settings::moveUpKey      = KEY_UP;
KeyboardKey Settings::moveDownKey    = KEY_DOWN;
KeyboardKey Settings::moveLeftKey    = KEY_LEFT;
KeyboardKey Settings::moveRightKey   = KEY_RIGHT;

void Settings::setBrightColor(unsigned int color)
{
    brightColor = color;
}

void Settings::setDarkColor(unsigned int color)
{
    darkColor = color;
}

void Settings::setInteractionKey(KeyboardKey key)
{
    interactionKey = key;
}

void Settings::setMoveUpKey(KeyboardKey key)
{
    moveUpKey = key;
}

void Settings::setMoveDownKey(KeyboardKey key)
{
    moveDownKey = key;
}

void Settings::setMoveLeftKey(KeyboardKey key)
{
    moveLeftKey = key;
}

void Settings::setMoveRightKey(KeyboardKey key)
{
    moveRightKey = key;
}
