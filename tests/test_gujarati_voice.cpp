#include "core/PathUtils.hpp"

#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <fcntl.h>
#include <io.h>

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::wcout << L"===========================================================\n";
    std::wcout << L"       CLICKBUDDY - GUJARATI NEURAL VOICE PLAYBACK TEST    \n";
    std::wcout << L"===========================================================\n\n";

    std::wstring audioPath = (ClickBuddy::PathUtils::getAudioCacheDir() / L"hello_gujarati.mp3").wstring();
    std::wcout << L"[VoiceEngine]: Opening MP3 audio file: " << audioPath << L"\n";

    mciSendStringW(L"close all", NULL, 0, NULL);

    std::wstring openCommand = std::wstring(L"open \"") + audioPath + L"\" type mpegvideo alias cb_voice";
    MCIERROR err = mciSendStringW(openCommand.c_str(), NULL, 0, NULL);

    if (err != 0) {
        wchar_t errorText[256];
        mciGetErrorStringW(err, errorText, 256);
        std::wcout << L"[ERROR]: Failed to open audio file: " << errorText << L"\n";
        return 1;
    }

    std::wcout << L"[VoiceEngine]: Playing Gujarati neural voice asynchronously...\n";
    std::wcout << L"Text: \"નમસ્તે! હું તમારો ડિજિટલ સાથી છું. આપણે સાથે મળીને કમ્પ્યુટર શીખીશું.\"\n\n";

    mciSendStringW(L"play cb_voice", NULL, 0, NULL);

    wchar_t statusBuffer[128];
    bool isAudioPlaying = true;

    while (isAudioPlaying) {
        mciSendStringW(L"status cb_voice mode", statusBuffer, 128, NULL);

        if (wcscmp(statusBuffer, L"playing") == 0) {
            std::wcout << L"   [Audio State]: Still speaking in background...\n";
        } else {
            isAudioPlaying = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::wcout << L"\n[Callback Buzzer]: Voice has finished speaking!\n";

    mciSendStringW(L"close cb_voice", NULL, 0, NULL);

    std::wcout << L"===========================================================\n";
    std::wcout << L" [SUCCESS]: First Gujarati voice test passed completely!   \n";
    std::wcout << L"===========================================================\n";

    return 0;
}
