#pragma once

#include <raylib.h>

namespace Settings {

extern unsigned int brightColor;
extern unsigned int darkColor;
extern KeyboardKey interactionKey;
extern KeyboardKey moveUpKey;
extern KeyboardKey moveDownKey;
extern KeyboardKey moveLeftKey;
extern KeyboardKey moveRightKey;

void setBrightColor(unsigned int color);
void setDarkColor(unsigned int color);
void setInteractionKey(KeyboardKey key);
void setMoveUpKey(KeyboardKey key);
void setMoveDownKey(KeyboardKey key);
void setMoveLeftKey(KeyboardKey key);
void setMoveRightKey(KeyboardKey key);

}
