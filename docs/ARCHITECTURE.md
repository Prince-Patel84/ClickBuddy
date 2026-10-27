# System Architecture - Sister's Call

## Architectural Overview

Sister's Call is organized into decoupled subsystems. It avoids heavy runtimes like Electron or Python interpreters for its core loop, ensuring a sub-30 MB RAM footprint and instantaneous startup on budget hardware.

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

### 1. The Eyes (`src/eyes/`)
- Uses the native Windows Accessibility subsystem: **UI Automation (UIA)** via COM interface `IUIAutomation`.
- Traverses the active window's visual tree to find buttons, text boxes, and menus without taking heavy or privacy-invasive screenshots.
- Retrieves high-DPI-accurate bounding rectangles `(x, y, width, height)`.

### 2. The Guide (`src/guide/`)
- A borderless, fullscreen transparent click-through window.
- Utilizes Win32 Extended Window Styles: `WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST`.
- Renders glowing indicator rectangles, animated bouncy arrows, and contextual tooltips right over target buttons.
- Mouse clicks pass completely unobstructed to the underlying application.

### 3. The Voice Engine (`src/voice/`)
- Audio synthesis and streaming in Gujarati, Hindi, and English.
- Asynchronous playback using native Windows Multimedia / Media Foundation or lightweight WebSockets to avoid blocking the main UI thread.

### 4. The Brain (`src/brain/`)
- Converts active UI state trees into compact structural representations.
- Drives the pedagogical state machine:
  - Detects hesitations (idle timers).
  - Handles interruptions ("I know this" -> fast forward).
  - Injects CS curiosity trivia and real-world analogies.

### 5. Multilingual Localization Engine (`src/i18n/`)
- First-class support for Gujarati, Hindi, and English string tables.
- Wide-string UTF-16 representation across all OS boundaries.
