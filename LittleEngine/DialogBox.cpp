#include "LittleEngine/DialogBox.hpp"

#include <cstring>
#include <iostream>
#include <raylib.h>

void DialogBox::start(char const* dialogs[], int numDialogs, char const* image)
{
    if (isInUse) return;

    isInUse = true;

    this->dialogs = (char const**)malloc(numDialogs*sizeof(char const**));
    std::memcpy(this->dialogs, dialogs, numDialogs*sizeof(char const**));

    this->image = image;
    this->numDialogs = numDialogs;
}

void DialogBox::update()
{
    if (isInUse) {
        if ((timeSinceLastChar >= 0.1 || currentCharacterInDialog == 0)
            && (currentCharacterInDialog != (int)(strlen(dialogs[currentDialog])))) {
            inProgressDialog.push_back(dialogs[currentDialog][currentCharacterInDialog]);
            timeSinceLastChar = 0;
            currentCharacterInDialog += 1;
        }

        timeSinceLastChar += GetFrameTime();
        DrawText(inProgressDialog.c_str(), 0, 0, 20, BLACK);

        if (currentCharacterInDialog >= (int)strlen(dialogs[currentDialog])
            && IsKeyPressed(KEY_ENTER)) {
            currentDialog += 1;
            currentCharacterInDialog = 0;
            inProgressDialog.clear();
        }

        if (currentDialog >= numDialogs) {
            currentDialog = 0;
            isInUse = false;
            std::free(this->dialogs);
        }
    }
}
