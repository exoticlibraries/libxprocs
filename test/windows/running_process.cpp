
#include <windows.h>
#include <Winbase.h>
#include <Tlhelp32.h>
#include <stdio.h>

void ListRunningProcess();

int main(int argc, char** argv) {
    ListRunningProcess();
}

void ListRunningProcess() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pe32.dwSize = sizeof(PROCESSENTRY32);

    while (Process32Next(hProcessSnap, &pe32)) { 
        printf("%s\n", pe32.szExeFile);
    }
    CloseHandle(hProcessSnap);
}

/**


**/