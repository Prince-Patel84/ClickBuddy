#pragma once

#include "core/Types.hpp"
#include <string>
#include <vector>
#include <optional>

namespace SistersCall {

/**
 * @brief Represents a single interactive control or window on screen.
 * 
 * Forms a hierarchical tree representing the UI layout without
 * needing any raw pixel screenshots.
 */
struct UIElement {
    // Label or accessible name (e.g. L"Wi-Fi", L"Save", L"Environment Variables...")
    std::wstring name;

    // Control category (Button, EditField, Window, etc.)
    UIControlType type = UIControlType::Unknown;

    // Exact pixel coordinates on the desktop
    UIRect bounds;

    // Is the element enabled (clickable) or grayed out?
    bool isEnabled = true;

    // Does this element currently have keyboard focus?
    bool isFocused = false;

    // Child elements contained inside this control (e.g. buttons inside a toolbar)
    std::vector<UIElement> children;

    // Helper: checks if this element has a non-empty name and valid screen bounds
    bool isInteractive() const {
        return isEnabled && bounds.isValid() && !name.empty();
    }
};

/**
 * @brief Abstract Contract (Interface) for the Screen Perception Subsystem.
 * 
 * Interrogates the native Windows UI Automation (UIA) tree via COM
 * to provide structured, semantic understanding of what is on screen.
 */
class IEyes {
public:
    virtual ~IEyes() = default;

    /**
     * @brief Initializes the Windows COM library (CoInitializeEx) 
     *        and attaches to the OS IUIAutomation runtime.
     * @return true if Windows UI Automation is accessible.
     */
    virtual bool initialize() = 0;

    /**
     * @brief Traverses and returns the entire UI tree of the current active window.
     * 
     * This tree contains only the interactive elements, stripped of noise,
     * ready to be reasoned about by the Brain.
     */
    virtual UIElement getActiveWindowTree() = 0;

    /**
     * @brief Searches the active window for a specific element by name and optional type.
     * 
     * @param name The visible text or accessible label to search for.
     * @param type Optional control type filter (e.g. UIControlType::Button).
     * @return std::optional containing the element if found, or std::nullopt if missing.
     */
    virtual std::optional<UIElement> findElement(
        const std::wstring& name,
        UIControlType type = UIControlType::Unknown
    ) = 0;

    /**
     * @brief Retrieves whatever element the user currently has focused or selected.
     * @return std::optional containing the focused element, or std::nullopt.
     */
    virtual std::optional<UIElement> getFocusedElement() = 0;
};

} // namespace SistersCall
