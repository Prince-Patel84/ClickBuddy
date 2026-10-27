#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace SistersCall {

/**
 * @brief Represents a rectangular region on the screen.
 * 
 * Windows Screen Coordinate System:
 * - (0, 0) is the TOP-LEFT corner of the primary display.
 * - X increases to the right.
 * - Y increases downwards.
 */
struct UIRect {
    int32_t x = 0;       // Left position in pixels
    int32_t y = 0;       // Top position in pixels
    int32_t width = 0;   // Width in pixels
    int32_t height = 0;  // Height in pixels

    // Helper method to check if the rectangle is valid and visible
    bool isValid() const {
        return width > 0 && height > 0;
    }

    // Helper to calculate the center point (useful for aiming arrows)
    int32_t centerX() const { return x + (width / 2); }
    int32_t centerY() const { return y + (height / 2); }
};

/**
 * @brief The languages natively supported by Sister's Call.
 * 
 * We use an 'enum class' (scoped enum) so values like 'Gujarati'
 * do not pollute the global namespace.
 */
enum class Language {
    Gujarati,
    Hindi,
    English
};

/**
 * @brief Classifies the role of an interactive UI element.
 * 
 * Maps directly to Windows UI Automation Control Types.
 */
enum class UIControlType {
    Unknown,
    Window,
    Button,
    EditField,     // Text input box
    MenuItem,
    TabItem,
    CheckBox,
    RadioButton,
    ListItem,
    Hyperlink
};

/**
 * @brief The pacing of the pedagogical guide.
 */
enum class LearnerPace {
    Slow,          // Beginner mode: explains every term with analogies
    Normal,        // Standard mode: clear instructions with brief context
    FastForward    // "I know this" mode: skips explanations, points straight to target
};

/**
 * @brief Direction from which a visual arrow should point to the target.
 */
enum class ArrowDirection {
    None,
    FromTop,
    FromBottom,
    FromLeft,
    FromRight
};

} // namespace SistersCall
