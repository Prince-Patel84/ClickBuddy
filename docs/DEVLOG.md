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
  - Validated developer toolchain: MinGW `g++` (13.x), `cmake`, `git`.
  - Created `.gitignore` ignoring build artifacts, executables, and IDE noise.
  - Implemented the first native Win32 Unicode entry point (`wWinMain`) in `src/main.cpp`.
  - Successfully verified native multilingual rendering in Gujarati, Hindi, and English via `MessageBoxW`.
  - Initialized Git repository on `main` branch with author Prince Patel.
  - Established branching strategy (`main`, `develop`, `feat/*`).

---

## Active Roadmap

- [x] Step 0: Project setup & Unicode Win32 verification
- [ ] Step 1: Professional CMake build system (`CMakeLists.txt`)
- [ ] Step 2: The Voice Engine (The Tongue) - Offline/Online TTS in Gu/Hi/En
- [ ] Step 3: The Eyes - Inspecting Windows UI elements via COM / `IUIAutomation`
- [ ] Step 4: The Guide - Transparent click-through overlay with glowing boxes and arrows
- [ ] Step 5: The Brain - Pedagogy, adaptive pacing, and intent reasoning
- [ ] Step 6: Autonomous Generalist Engine - Dynamic multi-step workflows
