#pragma once

#include <raylib.h>

namespace Settings {

extern unsigned int brightColor;
extern unsigned int darkColor;
extern KeyboardKey nextDialogKey;

void setBrightColor(unsigned int color);
void setDarkColor(unsigned int color);
void setNextDialogKey(KeyboardKey key);

}
