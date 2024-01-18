#pragma once

#include <raylib.h>
#include <string>

#define DIALOGBOX_IMAGE_WIDTH 50
#define DIALOGBOX_IMAGE_HEIGHT 50

class DialogBox {
private:
    bool isInUse = false;

    char const** dialogs;
    int numDialogs;
    Texture texture;
    Font font;
    bool skippable;

    std::string inProgressDialog;
    double timeSinceLastChar = 0;
    int currentDialog = 0;
    int currentCharacterInDialog = 0;

public:
    void start(char const* dialogs[], int numDialogs, bool skippable = true, char const* image = NULL);
    void update();
};
