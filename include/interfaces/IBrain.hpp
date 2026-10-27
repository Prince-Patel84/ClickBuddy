#pragma once

#include "core/Types.hpp"
#include "interfaces/IEyes.hpp"
#include <string>
#include <optional>

namespace SistersCall {

/**
 * @brief The physical action the learner is being guided to perform.
 */
enum class UserAction {
    Click,          // Standard left-click
    RightClick,     // Right-click for context menus
    DoubleClick,    // Double-click to open
    TypeText,       // Type into a text field or terminal
    Wait,           // Wait for a background process (like an installer)
    GoalAchieved    // Entire mission accomplished!
};

/**
 * @brief Represents a single guided step created by the Brain.
 * 
 * Contains both the instructional decision (where to click/type)
 * and the pedagogical teaching content (explanations and analogies).
 */
struct PedagogicalStep {
    // The target UI element name on screen to highlight
    std::wstring targetElementName;

    // The action the user needs to take
    UserAction action = UserAction::Click;

    // Text to type if action == UserAction::TypeText
    std::wstring textToType;

    // Encouraging, patient explanation in the learner's chosen language
    std::wstring spokenExplanation;

    // Optional real-world analogy or CS trivia to foster curiosity
    std::wstring curiosityTrivia;

    // True when the entire multi-step goal has reached completion
    bool isComplete = false;
};

/**
 * @brief Abstract Contract (Interface) for the Reasoning & Pedagogy Subsystem.
 * 
 * Ingests user goals and screen perceptions to formulate step-by-step
 * educational guidance. Can be backed by an LLM (Gemini/local) or rules engine.
 */
class IBrain {
public:
    virtual ~IBrain() = default;

    /**
     * @brief Initializes the reasoning engine (API credentials, prompt templates, local weights).
     * @return true if the engine is ready to reason.
     */
    virtual bool initialize() = 0;

    /**
     * @brief Formulates the next pedagogical step based on current screen perception.
     * 
     * @param userGoal What the user wants to accomplish (e.g. L"Setup C compiler").
     * @param screenTree The active window layout perceived by IEyes.
     * @param language The preferred language for spoken explanations.
     * @param pace The pacing mode (Slow, Normal, FastForward).
     * @return A complete PedagogicalStep with targets and native language explanation.
     */
    virtual PedagogicalStep decideNextStep(
        const std::wstring& userGoal,
        const UIElement& screenTree,
        Language language,
        LearnerPace pace = LearnerPace::Normal
    ) = 0;

    /**
     * @brief Handles mid-task verbal feedback from the learner.
     * 
     * E.g. If the user says "આ મને આવડે છે" (I know this) or "મને નથી સમજાતું" (I don't understand),
     * the Brain updates its internal learner profile to adjust pacing and detail.
     * 
     * @param feedback The transcribed user comment.
     */
    virtual void processUserFeedback(const std::wstring& feedback) = 0;

    /**
     * @brief Resets the current multi-step reasoning session.
     */
    virtual void resetSession() = 0;
};

} // namespace SistersCall
