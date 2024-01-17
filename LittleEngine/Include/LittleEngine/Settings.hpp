#pragma once

#include <raylib.h>
#include <string>

namespace Settings {

extern KeyboardKey interactionKey;
extern KeyboardKey moveDownKey;
extern KeyboardKey moveLeftKey;
extern KeyboardKey moveRightKey;
extern KeyboardKey moveUpKey;
extern std::string defaultDialogImage;
extern unsigned int brightColor;
extern unsigned int darkColor;

void setInteractionKey(KeyboardKey key);
void setMoveDownKey(KeyboardKey key);
void setMoveLeftKey(KeyboardKey key);
void setMoveRightKey(KeyboardKey key);
void setMoveUpKey(KeyboardKey key);
void setDefaultDialogImage(std::string image);
void setBrightColor(unsigned int color);
void setDarkColor(unsigned int color);

}
