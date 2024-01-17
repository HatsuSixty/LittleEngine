#include "LittleEngine/DialogBox.hpp"

#include <cstring>
#include <iostream>
#include <raylib.h>

#include "LittleEngine/Consts.hpp"
#include "LittleEngine/Settings.hpp"

#define DIALOGBOX_INNER_PADDING 10
#define DIALOGBOX_PADDING 40
#define DIALOGBOX_HEIGHT 80
#define DIALOGBOX_BORDER_THICKNESS 5

void DialogBox::start(char const* dialogs[], int numDialogs, char const* image)
{
    if (isInUse)
        return;

    isInUse = true;

    this->dialogs = (char const**)malloc(numDialogs * sizeof(char const**));
    std::memcpy(this->dialogs, dialogs, numDialogs * sizeof(char const**));

    Image img = LoadImage(image);
    this->texture = LoadTextureFromImage(img);
    UnloadImage(img);

    this->numDialogs = numDialogs;
}

void DialogBox::update()
{
    if (isInUse) {
        if ((timeSinceLastChar >= 0.05 || currentCharacterInDialog == 0)
            && (currentCharacterInDialog
                != (int)(strlen(dialogs[currentDialog])))) {
            inProgressDialog.push_back(
                dialogs[currentDialog][currentCharacterInDialog]);
            timeSinceLastChar = 0;
            currentCharacterInDialog += 1;
        }

        timeSinceLastChar += GetFrameTime();

        // Begin drawing borders

        auto rect = Rectangle {
            .x = DIALOGBOX_PADDING,
            .y = HEIGHT - DIALOGBOX_PADDING - DIALOGBOX_HEIGHT,
            .width = WIDTH - DIALOGBOX_PADDING * 2,
            .height = DIALOGBOX_HEIGHT,
        };
        DrawRectangleRec(rect, GetColor(Settings::darkColor));

        auto borderRect = rect;
        borderRect.x -= DIALOGBOX_BORDER_THICKNESS;
        borderRect.y -= DIALOGBOX_BORDER_THICKNESS;
        borderRect.width += DIALOGBOX_BORDER_THICKNESS * 2;
        borderRect.height += DIALOGBOX_BORDER_THICKNESS * 2;
        DrawRectangleLinesEx(borderRect, DIALOGBOX_BORDER_THICKNESS,
                             GetColor(Settings::brightColor));

        auto borderRect2 = borderRect;
        borderRect2.x -= 2;
        borderRect2.y -= 2;
        borderRect2.width += 2 * 2;
        borderRect2.height += 2 * 2;
        DrawRectangleLinesEx(borderRect2, 2, GetColor(Settings::darkColor));

        // End drawing borders

        // Draw image
        DrawTexturePro(texture,
                       Rectangle {
                           .x = 0,
                           .y = 0,
                           .width = (float)texture.width,
                           .height = (float)texture.height,
                       },
                       Rectangle {
                           .x = rect.x + DIALOGBOX_INNER_PADDING,
                           .y = rect.y + (rect.height / 2 - (float)DIALOGBOX_IMAGE_HEIGHT / 2),
                           .width = DIALOGBOX_IMAGE_WIDTH,
                           .height = DIALOGBOX_IMAGE_HEIGHT,
                       },
                       Vector2 { 0, 0 }, 0.0f, WHITE);

        DrawText(inProgressDialog.c_str(),
                 rect.x + DIALOGBOX_IMAGE_WIDTH + DIALOGBOX_INNER_PADDING * 2,
                 rect.y + DIALOGBOX_INNER_PADDING, 20, GetColor(0xFFD0EDFF));

        if (currentCharacterInDialog >= (int)strlen(dialogs[currentDialog])
            && IsKeyPressed(Settings::interactionKey)) {
            currentDialog += 1;
            currentCharacterInDialog = 0;
            inProgressDialog.clear();
        }

        if (currentDialog >= numDialogs) {
            currentDialog = 0;
            isInUse = false;
            std::free(this->dialogs);
            UnloadTexture(this->texture);
        }
    }
}
