#include "voice/EdgeTtsVoiceEngine.hpp"

#include <windows.h>
#include <mmsystem.h>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <chrono>

namespace SistersCall {

EdgeTtsVoiceEngine::EdgeTtsVoiceEngine() {
}

EdgeTtsVoiceEngine::~EdgeTtsVoiceEngine() {
    stop();

    if (m_workerThread.joinable()) {
        m_workerThread.join();
    }

    mciSendStringW(L"close sc_voice", NULL, 0, NULL);
}

bool EdgeTtsVoiceEngine::initialize() {
    std::filesystem::create_directories("cache/audio");
    mciSendStringW(L"close all", NULL, 0, NULL);
    return true;
}

std::wstring EdgeTtsVoiceEngine::getVoiceForLanguage(Language lang) const {
    switch (lang) {
        case Language::Gujarati:
            return L"gu-IN-DhwaniNeural";
        case Language::Hindi:
            return L"hi-IN-SwaraNeural";
        case Language::English:
        default:
            return L"en-IN-NeerjaNeural";
    }
}

std::wstring EdgeTtsVoiceEngine::getOrGenerateAudio(
    const std::wstring& text, 
    const std::wstring& voiceName
) {
    size_t hashValue = std::hash<std::wstring>{}(voiceName + L"_" + text);

    std::wstringstream ss;
    ss << L"cache\\audio\\" << voiceName << L"_" << hashValue << L".mp3";
    std::wstring cachedPath = ss.str();

    // Cache hit: file already exists
    if (std::filesystem::exists(cachedPath)) {
        return cachedPath;
    }

    // Cache miss: generate using edge-tts
    std::wstringstream cmd;
    cmd << L".\\.venv\\Scripts\\edge-tts.exe"
        << L" --voice \"" << voiceName << L"\""
        << L" --text \"" << text << L"\""
        << L" --write-media \"" << cachedPath << L"\""
        << L" > NUL 2>&1";

    int result = _wsystem(cmd.str().c_str());

    if (result == 0 && std::filesystem::exists(cachedPath)) {
        return cachedPath;
    }

    return L"";
}

void EdgeTtsVoiceEngine::speak(
    const std::wstring& text,
    Language language,
    [[maybe_unused]] LearnerPace pace,
    SpeechCompletionCallback onComplete
) {
    std::lock_guard<std::mutex> lock(m_speakMutex);

    stop();

    if (m_workerThread.joinable()) {
        m_workerThread.join();
    }

    m_stopRequested = false;
    m_isSpeaking = true;

    m_workerThread = std::thread([this, text, language, onComplete]() {
        std::wstring voice = getVoiceForLanguage(language);
        std::wstring audioFile = getOrGenerateAudio(text, voice);

        // If synthesis failed or was cancelled during download, exit
        if (audioFile.empty() || m_stopRequested) {
            m_isSpeaking = false;
            return;
        }

        mciSendStringW(L"close sc_voice", NULL, 0, NULL);

        std::wstring openCmd = L"open \"" + audioFile + L"\" type mpegvideo alias sc_voice";
        if (mciSendStringW(openCmd.c_str(), NULL, 0, NULL) != 0) {
            m_isSpeaking = false;
            return;
        }

        mciSendStringW(L"play sc_voice", NULL, 0, NULL);

        wchar_t statusBuf[128];
        while (!m_stopRequested) {
            mciSendStringW(L"status sc_voice mode", statusBuf, 128, NULL);

            if (wcscmp(statusBuf, L"playing") != 0) {
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        mciSendStringW(L"stop sc_voice", NULL, 0, NULL);
        mciSendStringW(L"close sc_voice", NULL, 0, NULL);

        bool finishedNaturally = !m_stopRequested;
        m_isSpeaking = false;

        // Callback only fires if audio finished naturally without interruption
        if (finishedNaturally && onComplete) {
            onComplete();
        }
    });
}

void EdgeTtsVoiceEngine::stop() {
    m_stopRequested = true;
    mciSendStringW(L"stop sc_voice", NULL, 0, NULL);
}

bool EdgeTtsVoiceEngine::isSpeaking() const {
    // If stop was requested, from the caller's perspective we are silent
    return m_isSpeaking && !m_stopRequested;
}

void EdgeTtsVoiceEngine::setVolume(float volume) {
    m_volume = volume;
}

} // namespace SistersCall
