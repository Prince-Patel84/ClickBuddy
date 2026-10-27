cmake_minimum_required(VERSION 3.20)

# Semantic Version v0.1.0
project(SistersCall 
    VERSION 0.1.0 
    DESCRIPTION "An autonomous, multilingual desktop tutor for computer beginners"
    LANGUAGES CXX
)

# Enforce C++20 Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Force Unicode (_UNICODE and UNICODE) on all targets
add_compile_definitions(UNICODE _UNICODE)

# Strict warnings to prevent bugs and code smells
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ====================================================================
# Target 1: The Main Desktop Application (Sister's Call)
# ====================================================================
add_executable(sisters_call
    src/main.cpp
)

target_include_directories(sisters_call PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MINGW)
    # -mwindows: Suppress black console window in production
    # -municode: Unicode wWinMain entry point
    target_link_options(sisters_call PRIVATE -mwindows -municode)
endif()

# ====================================================================
# Target 2: Architecture Verification Test (Mock Pipeline)
# ====================================================================
add_executable(test_mock_pipeline
    tests/test_mock_pipeline.cpp
)

target_include_directories(test_mock_pipeline PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ====================================================================
# Target 3: Audio Playback Test (WinMM Subsystem)
# ====================================================================
add_executable(test_audio_playback
    tests/test_audio_playback.cpp
)

target_link_libraries(test_audio_playback PRIVATE
    winmm
)

# ====================================================================
# Target 4: Gujarati Neural Voice Playback Test (MCI Subsystem)
# ====================================================================
add_executable(test_gujarati_voice
    tests/test_gujarati_voice.cpp
)

target_link_libraries(test_gujarati_voice PRIVATE
    winmm
)
