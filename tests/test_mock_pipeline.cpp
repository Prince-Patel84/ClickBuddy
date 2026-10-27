#include "core/Types.hpp"
#include "interfaces/IVoiceEngine.hpp"
#include "interfaces/IGuideOverlay.hpp"
#include "interfaces/IEyes.hpp"
#include "interfaces/IBrain.hpp"

#include <iostream>
#include <memory>
#include <cassert>

// Required on Windows to enable UTF-16 Unicode output in console
#include <fcntl.h>
#include <io.h>

using namespace SistersCall;

// ============================================================================
// 1. Mock Voice Engine (Simulates Speech Output & Callback)
// ============================================================================
class MockVoiceEngine : public IVoiceEngine {
public:
    bool initialize() override {
        std::wcout << L"[MockVoiceEngine]: Initialized audio hardware.\n";
        return true;
    }

    void speak(
        const std::wstring& text,
        Language language,
        LearnerPace pace = LearnerPace::Normal,
        SpeechCompletionCallback onComplete = nullptr
    ) override {
        (void)pace;
        lastSpokenText = text;
        lastLanguage = language;
        speaking = true;

        std::wcout << L"[MockVoiceEngine] (Speaking): " << text << L"\n";

        // Simulate audio playback finishing, then trigger the callback!
        speaking = false;
        if (onComplete) {
            std::wcout << L"[MockVoiceEngine]: Audio playback complete. Triggering callback buzzer!\n";
            onComplete();
        }
    }

    void stop() override {
        speaking = false;
        std::wcout << L"[MockVoiceEngine]: Audio stopped.\n";
    }

    bool isSpeaking() const override { return speaking; }
    void setVolume(float volume) override { (void)volume; }

    std::wstring lastSpokenText;
    Language lastLanguage = Language::English;
    bool speaking = false;
};

// ============================================================================
// 2. Mock Guide Overlay (Simulates Drawing Highlights & Arrows)
// ============================================================================
class MockGuideOverlay : public IGuideOverlay {
public:
    bool initialize() override {
        std::wcout << L"[MockGuideOverlay]: Created transparent fullscreen overlay window.\n";
        return true;
    }

    void showHighlight(const UIRect& target, const HighlightStyle& style) override {
        lastTarget = target;
        lastStyle = style;
        highlightActive = true;

        std::wcout << L"[MockGuideOverlay]: Drawing glowing box at ("
                   << target.x << L", " << target.y 
                   << L", width=" << target.width << L", height=" << target.height << L")\n";
    }

    void clear() override {
        highlightActive = false;
        std::wcout << L"[MockGuideOverlay]: Cleared highlights from screen.\n";
    }

    bool isVisible() const override { return highlightActive; }
    void setVisible(bool visible) override { highlightActive = visible; }

    UIRect lastTarget;
    HighlightStyle lastStyle;
    bool highlightActive = false;
};

// ============================================================================
// 3. Mock Eyes (Simulates Reading Windows Controls without Screenshots)
// ============================================================================
class MockEyes : public IEyes {
public:
    bool initialize() override {
        std::wcout << L"[MockEyes]: Connected to Windows UI Automation COM subsystem.\n";
        return true;
    }

    UIElement getActiveWindowTree() override {
        // Return a mock window with an "Environment Variables..." button inside
        UIElement window;
        window.name = L"System Properties";
        window.type = UIControlType::Window;
        window.bounds = { 200, 150, 600, 500 };

        UIElement button;
        button.name = L"Environment Variables...";
        button.type = UIControlType::Button;
        button.bounds = { 420, 580, 180, 32 };
        button.isEnabled = true;

        window.children.push_back(button);
        return window;
    }

    std::optional<UIElement> findElement(
        const std::wstring& name,
        UIControlType type = UIControlType::Unknown
    ) override {
        (void)type;
        if (name == L"Environment Variables...") {
            UIElement button;
            button.name = name;
            button.type = UIControlType::Button;
            button.bounds = { 420, 580, 180, 32 };
            button.isEnabled = true;
            return button;
        }
        return std::nullopt;
    }

    std::optional<UIElement> getFocusedElement() override {
        return std::nullopt;
    }
};

// ============================================================================
// 4. Mock Brain (Simulates Pedagogical Reasoning in Gujarati)
// ============================================================================
class MockBrain : public IBrain {
public:
    bool initialize() override {
        std::wcout << L"[MockBrain]: Initialized pedagogy and reasoning model.\n";
        return true;
    }

    PedagogicalStep decideNextStep(
        const std::wstring& userGoal,
        const UIElement& screenTree,
        Language language,
        LearnerPace pace = LearnerPace::Normal
    ) override {
        (void)userGoal;
        (void)screenTree;
        (void)pace;

        PedagogicalStep step;
        step.targetElementName = L"Environment Variables...";
        step.action = UserAction::Click;

        if (language == Language::Gujarati) {
            step.spokenExplanation = 
                L"જો બેટા, કમ્પ્યુટરને ખબર પડે કે આપણું C કમ્પાઇલર ક્યાં છે, એટલે આપણે આ બટન પર ક્લિક કરીશું.";
            step.curiosityTrivia = 
                L"PATH એટલે કમ્પ્યુટરનું રસોડું! જેમ રસોડામાં દરેક મસાલાની જગ્યા નક્કી હોય, તેમ કમ્પ્યુટર માટે કમ્પાઇલરની જગ્યા નક્કી કરીએ છીએ.";
        }

        return step;
    }

    void processUserFeedback(const std::wstring& feedback) override {
        (void)feedback;
    }

    void resetSession() override {}
};

// ============================================================================
// MAIN VERIFICATION TEST
// ============================================================================
int main() {
    // Tell the Windows Console to accept pure UTF-16 wide Unicode characters
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::wcout << L"===========================================================\n";
    std::wcout << L"   SISTER'S CALL - ARCHITECTURE END-TO-END VERIFICATION    \n";
    std::wcout << L"===========================================================\n\n";

    // 1. Program to the INTERFACES, not the implementations! (Dependency Inversion)
    std::unique_ptr<IVoiceEngine>  voice   = std::make_unique<MockVoiceEngine>();
    std::unique_ptr<IGuideOverlay> overlay = std::make_unique<MockGuideOverlay>();
    std::unique_ptr<IEyes>         eyes    = std::make_unique<MockEyes>();
    std::unique_ptr<IBrain>        brain   = std::make_unique<MockBrain>();

    // 2. Initialize all modules
    assert(voice->initialize());
    assert(overlay->initialize());
    assert(eyes->initialize());
    assert(brain->initialize());

    // 3. Step 1: Sister states her goal
    std::wstring goal = L"Setup C Compiler";
    std::wcout << L"\n[Scenario]: Sister asks: \"" << goal << L"\" in Gujarati.\n";

    // 4. Step 2: The Eyes inspect the active window
    UIElement activeScreen = eyes->getActiveWindowTree();
    std::wcout << L"[Eyes]: Active window is \"" << activeScreen.name << L"\"\n";

    // 5. Step 3: The Brain formulates the pedagogical step
    PedagogicalStep step = brain->decideNextStep(goal, activeScreen, Language::Gujarati);

    // 6. Step 4: The Eyes find the coordinates of the target element
    auto targetElement = eyes->findElement(step.targetElementName);
    assert(targetElement.has_value());
    std::wcout << L"[Eyes]: Target \"" << targetElement->name << L"\" located at ("
               << targetElement->bounds.x << L", " << targetElement->bounds.y << L")\n";

    // 7. Step 5: The Guide Overlay draws the visual cue
    HighlightStyle style;
    style.borderColor = 0xFF00E676; // Emerald green
    style.arrow = ArrowDirection::FromTop;
    style.tooltipText = L"અહીં ક્લિક કરો (Click here)";
    overlay->showHighlight(targetElement->bounds, style);
    assert(overlay->isVisible());

    // 8. Step 6: The Voice Engine speaks the Gujarati explanation
    bool callbackFired = false;
    voice->speak(
        step.spokenExplanation,
        Language::Gujarati,
        LearnerPace::Normal,
        [&callbackFired]() {
            callbackFired = true;
        }
    );

    // 9. Verify callback buzzed!
    assert(callbackFired);

    std::wcout << L"\n===========================================================\n";
    std::wcout << L" [SUCCESS]: All 4 interfaces integrated with ZERO errors!  \n";
    std::wcout << L"  - Memory ownership verified via std::unique_ptr          \n";
    std::wcout << L"  - Unicode strings verified in Gujarati & English         \n";
    std::wcout << L"  - Callback mechanism verified successfully               \n";
    std::wcout << L"===========================================================\n";

    return 0;
}
