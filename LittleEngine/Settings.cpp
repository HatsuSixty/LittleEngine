#include "LittleEngine/Settings.hpp"
#include <raylib.h>

unsigned int Settings::brightColor  = 0xFFD0EDFF;
unsigned int Settings::darkColor    = 0x140810FF;
KeyboardKey Settings::nextDialogKey = KEY_ENTER;

void Settings::setBrightColor(unsigned int color)
{
    brightColor = color;
}

void Settings::setDarkColor(unsigned int color)
{
    darkColor = color;
}

void Settings::setNextDialogKey(KeyboardKey key)
{
    nextDialogKey = key;
}
