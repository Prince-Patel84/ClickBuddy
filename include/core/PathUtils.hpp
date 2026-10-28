#pragma once

#include <windows.h>
#include <filesystem>
#include <string>

namespace ClickBuddy {
namespace PathUtils {

/**
 * @brief Dynamically locates the project root directory by inspecting
 *        the running executable's path via GetModuleFileNameW and walking upwards.
 * 
 * Works 100% reliably whether launched from:
 * - Project root terminal
 * - Build directory (build/)
 * - Windows File Explorer double-click
 * - Desktop shortcut
 */
inline std::filesystem::path getAppRootDir() {
    wchar_t exePathBuf[MAX_PATH];
    GetModuleFileNameW(NULL, exePathBuf, MAX_PATH);
    std::filesystem::path current = std::filesystem::path(exePathBuf).parent_path();

    // Walk up directory tree until we find the root containing .venv or CMakeLists.txt
    while (!current.empty() && current != current.root_path()) {
        if (std::filesystem::exists(current / ".venv") || std::filesystem::exists(current / "CMakeLists.txt")) {
            return current;
        }
        current = current.parent_path();
    }

    // Fallback to current working directory
    return std::filesystem::current_path();
}

/**
 * @brief Returns the absolute path to the cache directory.
 */
inline std::filesystem::path getCacheDir() {
    return getAppRootDir() / "cache";
}

/**
 * @brief Returns the absolute path to the audio cache directory.
 */
inline std::filesystem::path getAudioCacheDir() {
    return getCacheDir() / "audio";
}

/**
 * @brief Returns the absolute path to a script or binary inside the virtual environment (.venv).
 */
inline std::filesystem::path getVenvScript(const std::wstring& scriptName) {
    return getAppRootDir() / ".venv" / "Scripts" / scriptName;
}

} // namespace PathUtils
} // namespace ClickBuddy
