#pragma once

#include <raylib.h>
#include <string>

#define DIALOGBOX_IMAGE_WIDTH  50
#define DIALOGBOX_IMAGE_HEIGHT 50

class DialogBox {
private:
    bool isInUse = false;

    char const** dialogs;
    int numDialogs;
    Texture texture;

    std::string inProgressDialog;
    double timeSinceLastChar = 0;
    int currentDialog = 0;
    int currentCharacterInDialog = 0;

public:
    void start(char const* dialogs[], int numDialogs,
               char const* image = "./Assets/default_dialog_image.png");
    void update();
};
