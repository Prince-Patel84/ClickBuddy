#pragma once

#include "core/Types.hpp"
#include <string>
#include <functional>

namespace ClickBuddy {

/**
 * @brief Signature for the callback invoked when speech playback finishes.
 */
using SpeechCompletionCallback = std::function<void()>;

/**
 * @brief Abstract Contract (Interface) for the Voice Subsystem.
 * 
 * Any audio backend (Microsoft Edge TTS, Windows SAPI, or Mock)
 * must implement this interface.
 */
class IVoiceEngine {
public:
    virtual ~IVoiceEngine() = default;

    /**
     * @brief Initializes audio devices and loads voice models.
     * @return true if audio hardware is ready, false otherwise.
     */
    virtual bool initialize() = 0;

    /**
     * @brief Speaks text asynchronously in the specified language.
     * 
     * This function MUST NOT block the calling thread. It generates/streams
     * audio on a background thread and immediately returns control to the caller.
     * 
     * @param text The Unicode text to speak (supports Gujarati, Hindi, English).
     * @param language The language of the text.
     * @param pace Pacing (Slow for beginners, Normal, Brisk for fast-forward).
     * @param onComplete Optional callback invoked when playback finishes naturally.
     */
    virtual void speak(
        const std::wstring& text,
        Language language,
        LearnerPace pace = LearnerPace::Normal,
        SpeechCompletionCallback onComplete = nullptr
    ) = 0;

    /**
     * @brief Immediately silences any active speech.
     * 
     * Used when the user clicks an element early or says "I know this",
     * preventing the AI from talking over her.
     */
    virtual void stop() = 0;

    /**
     * @brief Checks if audio is currently playing.
     * @return true if speaking, false if silent.
     */
    virtual bool isSpeaking() const = 0;

    /**
     * @brief Sets playback volume.
     * @param volume Normalized volume between 0.0f (mute) and 1.0f (max).
     */
    virtual void setVolume(float volume) = 0;
};

} // namespace ClickBuddy
