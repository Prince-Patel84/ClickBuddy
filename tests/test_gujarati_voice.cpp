#include "core/PathUtils.hpp"

#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <fcntl.h>
#include <io.h>

int main() {
    // Enable Unicode UTF-16 in console output
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::wcout << L"===========================================================\n";
    std::wcout << L"     SISTER'S CALL - NATIVE GUJARATI VOICE PLAYBACK TEST   \n";
    std::wcout << L"===========================================================\n\n";

    // Use PathUtils to dynamically find cache/audio/hello_gujarati.mp3
    std::wstring audioPath = (SistersCall::PathUtils::getAudioCacheDir() / L"hello_gujarati.mp3").wstring();
    std::wcout << L"[VoiceEngine]: Opening MP3 audio file: " << audioPath << L"\n";

    // 1. Reset any existing MCI aliases to keep the audio subsystem clean
    mciSendStringW(L"close all", NULL, 0, NULL);

    // 2. Open the MP3 file using the Win32 MPEGVideo audio device
    // We assign it a friendly alias named 'gujVoice' so we can control it
    std::wstring openCommand = std::wstring(L"open \"") + audioPath + L"\" type mpegvideo alias gujVoice";
    MCIERROR err = mciSendStringW(openCommand.c_str(), NULL, 0, NULL);

    if (err != 0) {
        wchar_t errorText[256];
        mciGetErrorStringW(err, errorText, 256);
        std::wcout << L"[ERROR]: Failed to open audio file: " << errorText << L"\n";
        return 1;
    }

    std::wcout << L"[VoiceEngine]: Playing Gujarati neural voice asynchronously...\n";
    std::wcout << L"Text: \"નમસ્તે! હું તમારો ડિજિટલ ભાઈ છું. આપણે સાથે મળીને કમ્પ્યુટર શીખીશું.\"\n\n";

    // 3. Play the audio asynchronously (WITHOUT 'wait')
    // This allows our C++ code to run in parallel while audio plays through the speakers!
    mciSendStringW(L"play gujVoice", NULL, 0, NULL);

    // 4. Polling loop demonstrating non-blocking status detection:
    // We check every 200ms if Windows is still playing the audio.
    // The exact moment it transitions to 'stopped', we trigger our callback!
    wchar_t statusBuffer[128];
    bool isAudioPlaying = true;

    while (isAudioPlaying) {
        mciSendStringW(L"status gujVoice mode", statusBuffer, 128, NULL);

        if (wcscmp(statusBuffer, L"playing") == 0) {
            std::wcout << L"   [Audio State]: Still speaking in background...\n";
        } else {
            // Audio has reached the end!
            isAudioPlaying = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // 5. Fire our completion event!
    std::wcout << L"\n[Callback Buzzer]: Voice has finished speaking!\n";

    // 6. Clean up the MCI device
    mciSendStringW(L"close gujVoice", NULL, 0, NULL);

    std::wcout << L"===========================================================\n";
    std::wcout << L" [SUCCESS]: First Gujarati voice test passed completely!   \n";
    std::wcout << L"===========================================================\n";

    return 0;
}
