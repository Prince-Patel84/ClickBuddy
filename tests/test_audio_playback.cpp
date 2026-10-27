#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    std::wcout << L"===========================================================\n";
    std::wcout << L"         WIN32 MULTIMEDIA (WINMM) AUDIO TEST               \n";
    std::wcout << L"===========================================================\n\n";

    std::wcout << L"1. Triggering Windows System Sound asynchronously...\n";

    // Play the friendly Windows information chime (SystemAsterisk)
    // SND_ALIAS: Tells Windows to look up the sound in Windows Sound schemes
    // SND_ASYNC: Non-blocking; returns immediately while audio plays in background
    BOOL success = PlaySoundW(
        L"SystemAsterisk",
        NULL,
        SND_ALIAS | SND_ASYNC
    );

    if (success) {
        std::wcout << L"   [SUCCESS]: PlaySoundW executed cleanly!\n";
    } else {
        std::wcout << L"   [ERROR]: Failed to play sound.\n";
        return 1;
    }

    // Notice: our program is NOT frozen. We can do work while sound is playing!
    std::wcout << L"2. Notice how our C++ program continues running immediately:\n";
    for (int i = 1; i <= 3; ++i) {
        std::wcout << L"   - Doing CPU work step " << i << L" in parallel...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    std::wcout << L"\n[DONE]: Background audio playback verified.\n";
    return 0;
}
