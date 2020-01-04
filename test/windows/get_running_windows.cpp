#include <windows.h>
#include <Winbase.h>
#include <Psapi.h>
#include <Tlhelp32.h>
#include <iostream> 
#include <string>

static BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam) {
    int length = GetWindowTextLength(hWnd);
    char* buffer = new char[length + 1];
    GetWindowText(hWnd, buffer, length + 1);
    std::string windowTitle(buffer);

    DWORD lpdwProcessId;
    GetWindowThreadProcessId(hWnd,&lpdwProcessId);
    if (IsWindowVisible(hWnd) && length != 0) {
        std::cout << lpdwProcessId << ":  " << windowTitle << std::endl;
    }
    return TRUE;
}

int main() {
    std::cout << "Enmumerating windows..." << std::endl;
    EnumWindows(enumWindowCallback, 0);
    return 0;
}

/**
https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlea?redirectedfrom=MSDN
http://msdn.microsoft.com/en-us/library/ms683197%28VS.85%29.aspx
https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtexta
https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowthreadprocessid

compile with 'g++ process_full_path.cpp -lpsapi'

*/