# Development Log - Sister's Call

## Project Vision
An autonomous, patient, voice-guided desktop tutor that empowers users (especially beginners and non-English speakers) to navigate and master any software on Windows.
- **Languages Supported**: Gujarati (ગુજરાતી), Hindi (हिन्दी), English.
- **Philosophy**: Pedagogy & Empowerment over blind automation. Teaches concepts via analogies and visual overlays without capturing invasive screenshots.
- **Tech Stack**: Native C++ (Win32, COM, UI Automation, Direct2D/GDI+), Microsoft Neural Voices (Edge TTS), Lightweight LLM Reasoning.

---

## Chronological Milestones

### Milestone 0: Foundations (2026-10-27)
- **Status**: Completed
- **Achievements**:
  - Validated developer toolchain: MinGW `g++` (14.2.0), `cmake`, `git`.
  - Created `.gitignore` ignoring build artifacts, executables, and IDE noise.
  - Implemented the first native Win32 Unicode entry point (`wWinMain`) in `src/main.cpp`.
  - Successfully verified native multilingual rendering in Gujarati, Hindi, and English via `MessageBoxW`.
  - Initialized Git repository on `main` branch with author Prince Patel.
  - Established branching strategy (`main`, `develop`, `feat/*`).

### Milestone 1: Abstract Contracts & Mock Pipeline (2026-10-27)
- **Status**: Completed (Merged into `develop`)
- **Achievements**:
  - Implemented `include/core/Types.hpp` (shared coordinate system `UIRect`, `Language`, `UIControlType`, `LearnerPace`).
  - Defined strict abstract C++ contracts for all 4 subsystems:
    - `include/interfaces/IVoiceEngine.hpp` (asynchronous speech, callback buzzer, stop mechanism).
    - `include/interfaces/IGuideOverlay.hpp` (click-through visual cues, styling, bounds).
    - `include/interfaces/IEyes.hpp` (semantic UI tree extraction via COM, `std::optional` safety).
    - `include/interfaces/IBrain.hpp` (cognitive reasoning, pedagogy, curiosity trivia).
  - Authored `CMakeLists.txt` with C++20 standard, strict warnings (`-Wall -Wextra -Wpedantic`), and Unicode definitions.
  - Implemented `tests/test_mock_pipeline.cpp` verifying end-to-end integration across all 4 modules.
  - Addressed C++ function override default argument binding rules and UTF-16 console mode (`_O_U16TEXT`).
  - Achieved 100% clean compilation with zero warnings and zero memory leaks.

### Milestone 2: Production Voice Engine (`EdgeTtsVoiceEngine`) (2026-10-27)
- **Status**: Completed (Merged into `develop`)
- **Achievements**:
  - Implemented `EdgeTtsVoiceEngine` inheriting from `IVoiceEngine`.
  - Built isolated `.venv` environment for offline/online neural audio synthesis.
  - Implemented `gu-IN-DhwaniNeural` (Gujarati), `hi-IN-SwaraNeural` (Hindi), and `en-IN-NeerjaNeural` (English) mapping.
  - Implemented 64-bit string hashing (`std::hash`) for disk caching in `cache/audio/`, achieving instant 0ms latency on repeated phrases.
  - Multi-threaded asynchronous playback via `std::thread` and thread-safe control flags (`std::atomic<bool>`).
  - Implemented instant audio silencing (`stop()`) without dangling threads or leaked MCI handles.
  - **Universal Path Architecture**: Created `include/core/PathUtils.hpp`. Standardized root directory traversal via Win32 `GetModuleFileNameW`. Every executable in the project now runs reliably from any location (terminal, `build/` folder, or Windows File Explorer).
  - Verified 100% clean build and exit code 0 across all 5 CMake targets.

---

## Active Roadmap

- [x] Step 0: Project setup & Unicode Win32 verification
- [x] Step 1: Abstract Subsystem Contracts & CMake Mock Pipeline
- [x] Step 2: The Voice Engine (The Tongue) - Production `EdgeTtsVoiceEngine` & `PathUtils`
- [ ] Step 3: The Guide (Visual Overlay) - Native Win32 click-through transparent window
- [ ] Step 4: The Eyes - Inspecting Windows UI elements via COM / `IUIAutomation`
- [ ] Step 5: The Brain - Pedagogy, adaptive pacing, and intent reasoning
- [ ] Step 6: Autonomous Generalist Engine - Dynamic multi-step workflows
