#include "LittleEngine/DialogBox.hpp"

#include <cstring>
#include <iostream>
#include <raylib.h>

#include "AssetManager.hpp"
#include "LittleEngine/Consts.hpp"
#include "LittleEngine/Settings.hpp"

extern AssetManager assetManager;

#define DIALOGBOX_INNER_PADDING 10
#define DIALOGBOX_PADDING 40
#define DIALOGBOX_HEIGHT 80
#define DIALOGBOX_BORDER_THICKNESS 5

void DialogBox::start(DialogBoxParameters parameters)
{
    if (m_isInUse)
        return;
    m_isInUse = true;

    // DialogBox uses audio
    if (!IsAudioDeviceReady())
        InitAudioDevice();

    m_dialogs
        = (char const**)malloc(parameters.numDialogs * sizeof(char const**));
    std::memcpy(m_dialogs, parameters.dialogs,
                parameters.numDialogs * sizeof(char const**));

    m_texture = parameters.image == NULL
        ? assetManager.loadTexture(Settings::defaultDialogImage.c_str())
        : assetManager.loadTexture(parameters.image);

    m_useSound = false;
    if (parameters.useSound) {
        m_useSound = true;
        m_sound = parameters.sound == NULL
            ? assetManager.loadSound(Settings::defaultDialogSound.c_str())
            : assetManager.loadSound(parameters.sound);
    }

    m_numDialogs = parameters.numDialogs;

    m_font = Settings::defaultFont == ""
        ? GetFontDefault()
        : assetManager.loadFont(Settings::defaultFont.c_str());

    m_skippable = parameters.skippable;

    m_useCustomTextPosition = parameters.useCustomTextPosition;
    m_textPosition = parameters.textPosition;

    m_textSpeed = parameters.speed == 0 ? 0.05 : parameters.speed;
}

void DialogBox::update()
{
    if (m_isInUse) {
        // Update current text if enough time has passed
        if ((m_timeSinceLastChar >= m_textSpeed
             || m_currentCharacterInDialog == 0)
            && (m_currentCharacterInDialog
                != (int)(strlen(m_dialogs[m_currentDialog])))) {
            if (m_useSound)
                PlaySound(m_sound);
            m_inProgressDialog.push_back(
                m_dialogs[m_currentDialog][m_currentCharacterInDialog]);
            m_timeSinceLastChar = 0;
            m_currentCharacterInDialog += 1;
        }

        // Skip dialog if the player presses the secondary interaction key
        if (IsKeyPressed(Settings::secondaryInteractionKey) && m_skippable) {
            for (; m_currentCharacterInDialog
                 < (int)strlen(m_dialogs[m_currentDialog]);
                 ++m_currentCharacterInDialog) {
                m_inProgressDialog.push_back(
                    m_dialogs[m_currentDialog][m_currentCharacterInDialog]);
            }
        }

        // Update the elapsed amount of time since the last character
        // was added to the current text
        m_timeSinceLastChar += GetFrameTime();

        // Define textPos for later usage
        // In case textPosition is uninitialized, the useCustomTextPosition
        // variable should be set to false and textPos should be properly
        // updated
        Vector2 textPos = m_textPosition;

        if (!m_useCustomTextPosition) {
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
                m_texture,
                Rectangle {
                    .x = 0,
                    .y = 0,
                    .width = (float)m_texture.width,
                    .height = (float)m_texture.height,
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
        DrawTextEx(m_font, m_inProgressDialog.c_str(), textPos, fontSize,
                   fontSize / 10, GetColor(Settings::brightColor));
        /// End drawing text ///

        // Go to next dialog if we finished the current one and the player
        // pressed the interaction key
        if (m_currentCharacterInDialog
                >= (int)strlen(m_dialogs[m_currentDialog])
            && IsKeyPressed(Settings::interactionKey)) {
            m_currentDialog += 1;
            m_currentCharacterInDialog = 0;
            m_inProgressDialog.clear();
        }

        // If we finished displaying all the dialogs, cleanup
        if (m_currentDialog >= m_numDialogs) {
            m_currentDialog = 0;
            m_isInUse = false;
            std::free(m_dialogs);
        }
    }
}
