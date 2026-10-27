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

---

## Active Roadmap

- [x] Step 0: Project setup & Unicode Win32 verification
- [x] Step 1: Abstract Subsystem Contracts & CMake Mock Pipeline
- [ ] Step 2: The Guide (Visual Overlay) - Native Win32 click-through transparent window
- [ ] Step 3: The Voice Engine (The Tongue) - Real asynchronous audio synthesis in Gu/Hi/En
- [ ] Step 4: The Eyes - Inspecting Windows UI elements via COM / `IUIAutomation`
- [ ] Step 5: The Brain - Pedagogy, adaptive pacing, and intent reasoning
- [ ] Step 6: Autonomous Generalist Engine - Dynamic multi-step workflows
