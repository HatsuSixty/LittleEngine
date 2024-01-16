#pragma once

#include <string>

class DialogBox {
private:
    bool isInUse = false;

    char const** dialogs;
    char const* image;
    int numDialogs;

    std::string inProgressDialog;
    double timeSinceLastChar = 0;
    int currentDialog = 0;
    int currentCharacterInDialog = 0;

public:
    void start(char const* dialogs[], int numDialogs,
               char const* image = "./Assets/default_dialog_image.png");
    void update();
};
