
#include <windows.h>
#include <Winbase.h>
#include <Tlhelp32.h>
#include<iostream> 

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
        cout << pe32.szExeFile << ", " << pe32.th32ProcessID << ", " << pe32.cntThreads << endl;
    }
    CloseHandle(hProcessSnap);
}

/**
https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/
https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-process32next
https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-processentry32w

typedef struct tagPROCESSENTRY32 {
  DWORD     dwSize;
  DWORD     cntUsage;
  DWORD     th32ProcessID;
  ULONG_PTR th32DefaultHeapID;
  DWORD     th32ModuleID;
  DWORD     cntThreads;
  DWORD     th32ParentProcessID;
  LONG      pcPriClassBase;
  DWORD     dwFlags;
  CHAR      szExeFile[MAX_PATH];
} PROCESSENTRY32;

*/