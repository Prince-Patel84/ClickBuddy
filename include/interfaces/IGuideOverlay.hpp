#pragma once

#include "core/Types.hpp"
#include <string>
#include <cstdint>

namespace SistersCall {

/**
 * @brief Configuration for how a visual highlight should be rendered.
 */
struct HighlightStyle {
    // 32-bit ARGB color (Default: 0xFF00E676 - A warm, friendly emerald green)
    uint32_t borderColor = 0xFF00E676; 
    
    // Thickness of the highlight border in pixels
    int32_t borderWidth = 3;

    // If true, the highlight gently pulses in brightness to draw the eye
    bool pulsing = true;

    // Which side of the target box the pointer arrow should approach from
    ArrowDirection arrow = ArrowDirection::FromTop;

    // Optional short text label floating near the target box (e.g. L"અહીં ક્લિક કરો")
    std::wstring tooltipText;
};

/**
 * @brief Abstract Contract (Interface) for the Screen Overlay Subsystem.
 * 
 * Responsible for rendering non-intrusive visual cues (glowing boxes,
 * bouncy arrows, tooltips) directly over native Windows applications.
 * 
 * Crucial Requirement: The overlay window MUST use WS_EX_TRANSPARENT so
 * mouse clicks pass completely unobstructed to the application below.
 */
class IGuideOverlay {
public:
    virtual ~IGuideOverlay() = default;

    /**
     * @brief Initializes the transparent, borderless topmost window.
     * @return true if the graphics context and window were successfully created.
     */
    virtual bool initialize() = 0;

    /**
     * @brief Highlights an exact rectangular region on screen.
     * 
     * @param target The screen coordinates of the button/field to highlight.
     * @param style Visual options (color, arrow direction, pulsing, tooltip).
     */
    virtual void showHighlight(const UIRect& target, const HighlightStyle& style) = 0;

    /**
     * @brief Clears the current highlight, arrow, and tooltip from the screen.
     */
    virtual void clear() = 0;

    /**
     * @brief Checks if the overlay window is currently active and visible.
     */
    virtual bool isVisible() const = 0;

    /**
     * @brief Toggles the overall visibility of the overlay window.
     * @param visible true to show, false to hide.
     */
    virtual void setVisible(bool visible) = 0;
};

} // namespace SistersCall
