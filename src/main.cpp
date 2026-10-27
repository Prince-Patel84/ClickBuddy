#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
    const wchar_t* message = 
        L"Welcome to Sister's Call!\n\n"
        L"English: Your patient digital brother.\n"
        L"ગુજરાતી: તમારી સાથે શીખનાર તમારો ડિજિટલ ભાઈ.\n"
        L"हिन्दी: તમારી સાથે / आपकी डिजिटल यात्रा का सच्चा साथी।";

    const wchar_t* title = L"Sister's Call - Initializing";

    MessageBoxW(
        NULL,
        message,
        title,
        MB_OK | MB_ICONINFORMATION
    );

    return 0;
}
