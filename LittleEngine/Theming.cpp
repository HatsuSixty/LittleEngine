#include "LittleEngine/Theming.hpp"

unsigned int Theming::brightColor = 0xFFD0EDFF;
unsigned int Theming::darkColor   = 0x140810FF;

void Theming::setBrightColor(unsigned int color)
{
    brightColor = color;
}

void Theming::setDarkColor(unsigned int color)
{
    darkColor = color;
}
