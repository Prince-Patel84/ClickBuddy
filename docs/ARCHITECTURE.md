# System Architecture - ClickBuddy

## Architectural Overview

ClickBuddy is organized into decoupled subsystems using pure abstract C++ interfaces (SOLID Dependency Inversion). It avoids heavy runtimes like Electron or Python interpreters for its core loop, ensuring a sub-25 MB RAM footprint and instantaneous startup on budget hardware.

```
+-----------------------------------------------------------------------+
|                              CORE LOOP                                |
|                                                                       |
|  [Voice Engine] <----+-----> [Brain / Reasoning] <----+-----> [Eyes]  |
|   (Speech I/O)       |         (Dynamic LLM)          |       (UIA)   |
|                      |                                |               |
|                      +-----> [Guide (Overlay)] <------+               |
+-----------------------------------------------------------------------+
```

## Subsystem Breakdown

### 1. The Eyes (`include/interfaces/IEyes.hpp`)
- Uses the native Windows Accessibility subsystem: **UI Automation (UIA)** via COM interface `IUIAutomation`.
- Traverses the active window's visual tree to find buttons, text boxes, and menus without taking heavy or privacy-invasive screenshots.
- Retrieves high-DPI-accurate bounding rectangles `(x, y, width, height)`.
- Crash-proof return values via modern `std::optional<UIElement>`.

### 2. The Guide (`include/interfaces/IGuideOverlay.hpp`)
- A borderless, fullscreen transparent click-through window.
- Utilizes Win32 Extended Window Styles: `WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST`.
- Renders glowing indicator rectangles, animated bouncy arrows, and contextual tooltips right over target buttons.
- Mouse clicks pass completely unobstructed to the underlying application.

### 3. The Voice Engine (`include/interfaces/IVoiceEngine.hpp` & `src/voice/EdgeTtsVoiceEngine.cpp`)
- Audio synthesis and streaming in Gujarati (`gu-IN-DhwaniNeural`), Hindi (`hi-IN-SwaraNeural`), and English (`en-IN-NeerjaNeural`).
- Multi-threaded asynchronous playback via `std::thread`.
- Local disk caching via 64-bit `std::hash` in `cache/audio/`, achieving instant 0ms latency on repeated phrases.
- Early cancellation and instant silencing via `std::atomic<bool>`.
- Completion notifications via `SpeechCompletionCallback` buzzers.

### 4. The Brain (`include/interfaces/IBrain.hpp`)
- Converts active UI state trees into compact structural representations.
- Drives the pedagogical state machine:
  - Detects hesitations (idle timers).
  - Handles interruptions ("I know this" -> fast forward).
  - Injects CS curiosity trivia and real-world analogies.

### 5. Path & Environment Subsystem (`include/core/PathUtils.hpp`)
- Universal root directory resolution via Win32 `GetModuleFileNameW`.
- Guarantees seamless execution from any directory, terminal, or File Explorer double-click.
