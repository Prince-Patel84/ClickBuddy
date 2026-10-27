#pragma once

#include "interfaces/IVoiceEngine.hpp"
#include <thread>
#include <atomic>
#include <mutex>
#include <string>

namespace SistersCall {

/**
 * @brief Concrete implementation of IVoiceEngine powered by Microsoft Edge Neural TTS
 *        and native Win32 MCI audio playback.
 * 
 * Supports high-fidelity neural voices for Gujarati, Hindi, and English with
 * local file caching and thread-safe asynchronous playback.
 */
class EdgeTtsVoiceEngine : public IVoiceEngine {
public:
    EdgeTtsVoiceEngine();
    ~EdgeTtsVoiceEngine() override;

    // ========================================================================
    // IVoiceEngine Interface Implementation
    // ========================================================================
    bool initialize() override;

    void speak(
        const std::wstring& text,
        Language language,
        LearnerPace pace = LearnerPace::Normal,
        SpeechCompletionCallback onComplete = nullptr
    ) override;

    void stop() override;

    bool isSpeaking() const override;

    void setVolume(float volume) override;

private:
    // Maps Language enum to Microsoft Neural Voice identifiers
    std::wstring getVoiceForLanguage(Language lang) const;

    // Checks cache on disk; if missing, invokes edge-tts via virtual environment
    std::wstring getOrGenerateAudio(const std::wstring& text, const std::wstring& voiceName);

    // Thread-safe state flags
    std::atomic<bool> m_isSpeaking{false};
    std::atomic<bool> m_stopRequested{false};
    float m_volume = 1.0f;

    // Worker thread management
    std::thread m_workerThread;
    std::mutex m_speakMutex;
};

} // namespace SistersCall
