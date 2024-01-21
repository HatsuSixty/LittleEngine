#pragma once

#include <raylib.h>
#include <string>

#define DIALOGBOX_IMAGE_WIDTH 50
#define DIALOGBOX_IMAGE_HEIGHT 50

class DialogBox {
private:
    // Parameters
    // Are initialized in `start()`
    char const** dialogs;
    int numDialogs;
    Texture texture;
    Font font;
    bool skippable;
    Vector2 textPosition;
    bool useCustomTextPosition;
    double textSpeed;

    // State
    // Preinitialized
    bool isInUse = false;
    std::string inProgressDialog;
    double timeSinceLastChar = 0;
    int currentDialog = 0;
    int currentCharacterInDialog = 0;

    void start(char const* dialogs[], int numDialogs, bool skippable,
               char const* image, Vector2 textPosition, double speed);

public:
    void start(char const* dialogs[], int numDialogs);
    void startEx(char const* dialogs[], int numDialogs, bool skippable,
                 char const* image);
    void startPro(char const* dialogs[], int numDialogs, bool skippable,
                  char const* image, Vector2 textPosition, double speed);

    void update();
};
