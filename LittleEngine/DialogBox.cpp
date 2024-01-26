#include "LittleEngine/DialogBox.hpp"

#include <cstring>
#include <iostream>
#include <raylib.h>

#include "AssetManager.hpp"
#include "LittleEngine/Consts.hpp"
#include "LittleEngine/Settings.hpp"

extern AssetManager assetManager;

bool isVectorZero(Vector2 a) { return a.x == 0 && a.y == 0; }

#define DIALOGBOX_INNER_PADDING 10
#define DIALOGBOX_PADDING 40
#define DIALOGBOX_HEIGHT 80
#define DIALOGBOX_BORDER_THICKNESS 5

void DialogBox::start(char const* dialogs[], int numDialogs, bool skippable,
                      char const* image, Vector2 textPosition, double speed)
{
    if (isInUse)
        return;

    isInUse = true;

    this->dialogs = (char const**)malloc(numDialogs * sizeof(char const**));
    std::memcpy(this->dialogs, dialogs, numDialogs * sizeof(char const**));

    if (image != NULL)
        this->texture = assetManager.loadTexture(image);
    else
        this->texture = assetManager.loadTexture(Settings::defaultDialogImage.c_str());

    this->numDialogs = numDialogs;
    if (Settings::defaultFont == "")
        this->font = GetFontDefault();
    else
        this->font = assetManager.loadFont(Settings::defaultFont.c_str());
    this->skippable = skippable;

    this->useCustomTextPosition = false;
    if (!isVectorZero(textPosition)) {
        this->textPosition = textPosition;
        this->useCustomTextPosition = true;
    }

    if (speed != 0)
        this->textSpeed = speed;
    else
        this->textSpeed = 0.05;
}

void DialogBox::start(char const* dialogs[], int numDialogs)
{
    start(dialogs, numDialogs, true, NULL, Vector2 { 0, 0 }, 0);
}

void DialogBox::startEx(char const* dialogs[], int numDialogs, bool skippable,
                        char const* image)
{
    start(dialogs, numDialogs, skippable, image, Vector2 { 0, 0 }, 0);
}

void DialogBox::startPro(char const* dialogs[], int numDialogs, bool skippable,
                         char const* image, Vector2 textPosition, double speed)
{
    start(dialogs, numDialogs, skippable, image, textPosition, speed);
}

void DialogBox::update()
{
    if (isInUse) {
        // Update current text if enough time has passed
        if ((timeSinceLastChar >= this->textSpeed
             || currentCharacterInDialog == 0)
            && (currentCharacterInDialog
                != (int)(strlen(dialogs[currentDialog])))) {
            inProgressDialog.push_back(
                dialogs[currentDialog][currentCharacterInDialog]);
            timeSinceLastChar = 0;
            currentCharacterInDialog += 1;
        }

        // Skip dialog if the player presses the secondary interaction key
        if (IsKeyPressed(Settings::secondaryInteractionKey) && skippable) {
            for (;
                 currentCharacterInDialog < (int)strlen(dialogs[currentDialog]);
                 ++currentCharacterInDialog) {
                inProgressDialog.push_back(
                    dialogs[currentDialog][currentCharacterInDialog]);
            }
        }

        // Update the elapsed amount of time since the last character
        // was added to the current text
        timeSinceLastChar += GetFrameTime();

        // Define textPos for later usage
        // In case textPosition is uninitialized, the useCustomTextPosition
        // variable should be set to false and textPos should be properly
        // updated
        Vector2 textPos = textPosition;

        if (!useCustomTextPosition) {
            /// Begin drawing borders ///
            auto rect = Rectangle {
                .x = DIALOGBOX_PADDING,
                .y = HEIGHT - DIALOGBOX_PADDING - DIALOGBOX_HEIGHT,
                .width = WIDTH - DIALOGBOX_PADDING * 2,
                .height = DIALOGBOX_HEIGHT,
            };
            // Will be used later
            textPos = Vector2 {
                rect.x + DIALOGBOX_IMAGE_WIDTH + DIALOGBOX_INNER_PADDING * 2,
                rect.y + DIALOGBOX_INNER_PADDING,
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
            /// End drawing borders ///

            /// Begin drawing image ///
            DrawTexturePro(
                texture,
                Rectangle {
                    .x = 0,
                    .y = 0,
                    .width = (float)texture.width,
                    .height = (float)texture.height,
                },
                Rectangle {
                    .x = rect.x + DIALOGBOX_INNER_PADDING,
                    .y = rect.y
                        + (rect.height / 2 - (float)DIALOGBOX_IMAGE_HEIGHT / 2),
                    .width = DIALOGBOX_IMAGE_WIDTH,
                    .height = DIALOGBOX_IMAGE_HEIGHT,
                },
                Vector2 { 0, 0 }, 0.0f, WHITE);
            /// End drawing image ///
        }

        /// Begin drawing text ///
        auto fontSize = 20.0f;
        DrawTextEx(font, inProgressDialog.c_str(), textPos, fontSize,
                   fontSize / 10, GetColor(Settings::brightColor));
        /// End drawing text ///

        // Go to next dialog if we finished the current one and the player
        // pressed the interaction key
        if (currentCharacterInDialog >= (int)strlen(dialogs[currentDialog])
            && IsKeyPressed(Settings::interactionKey)) {
            currentDialog += 1;
            currentCharacterInDialog = 0;
            inProgressDialog.clear();
        }

        // If we finished displaying all the dialogs, cleanup
        if (currentDialog >= numDialogs) {
            currentDialog = 0;
            isInUse = false;
            std::free(this->dialogs);
        }
    }
}
