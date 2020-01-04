
#include <windows.h>
#include <Winbase.h>
#include <Tlhelp32.h>
#include <stdio.h>

typedef const char* AnsiString;

bool FindRunningProcess(AnsiString process);

int main(int argc, char** argv) {
    if (argc > 1) {
        bool isRunning = FindRunningProcess((const char*)argv[1]);
        printf("Process '%s' = %i\n", argv[1], isRunning);
        return 0;
    } else {
        printf("You need to specify the process name");
    }
}

bool FindRunningProcess(const AnsiString process) {
/*
Function takes in a string value for the process it is looking for like ST3Monitor.exe
then loops through all of the processes that are currently running on windows.
If the process is found it is running, therefore the function returns true.
*/
    AnsiString compare;
    bool procRunning = false;

    printf("1\n");
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    printf("2\n");
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        printf("3\n");
        procRunning = false;
    } else {
        pe32.dwSize = sizeof(PROCESSENTRY32);
        printf("4\n");
        if (Process32First(hProcessSnap, &pe32)) { // Gets first running process
            if (pe32.szExeFile == process) {
                procRunning = true;
            } else {
                // loop through all running processes looking for process
                while (Process32Next(hProcessSnap, &pe32)) { 
                    // Set to an AnsiString instead of Char[] to make compare easier
                    compare = pe32.szExeFile;
                    printf("Found Process %s\n", compare);
                    if (compare == process) {
                        // if found process is running, set to true and break from loop
                        procRunning = true;
                        break;
                    }
                }
            }
            // clean the snapshot object
            CloseHandle(hProcessSnap);
        }
    }

    return procRunning;
}