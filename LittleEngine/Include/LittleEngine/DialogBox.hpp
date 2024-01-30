#pragma once

#include <raylib.h>
#include <string>

#define DIALOGBOX_IMAGE_WIDTH 50
#define DIALOGBOX_IMAGE_HEIGHT 50

struct DialogBoxParameters {
    // Mandatory
    char const** dialogs;
    int numDialogs;

    // Not mandatory
    bool skippable = true;
    char const* image = NULL;
    bool useSound = true;
    char const* sound = NULL;
    bool useCustomTextPosition = false;
    Vector2 textPosition;
    double speed = 0;
};

class DialogBox {
private:
    // Parameters
    // Are initialized in `start()`
    char const** m_dialogs;
    int m_numDialogs;
    Texture m_texture;
    Font m_font;
    bool m_useSound;
    Sound m_sound;
    bool m_skippable;
    Vector2 m_textPosition;
    bool m_useCustomTextPosition;
    double m_textSpeed;

    // State
    // Preinitialized
    bool m_isInUse = false;
    std::string m_inProgressDialog;
    double m_timeSinceLastChar = 0;
    int m_currentDialog = 0;
    int m_currentCharacterInDialog = 0;

public:
    void start(DialogBoxParameters parameters);
    void update();
};
