
#include <windows.h>
#include <Winbase.h>
#include <Tlhelp32.h>
#include <iostream> 
#include <string>

using namespace std; 

typedef string AnsiString;

bool FindRunningProcess(AnsiString process);

int main(int argc, char** argv) 
{
    if (argc > 1) {
        cout << "Is process running? '" << argv[1] << "' = " << (FindRunningProcess(argv[1]) ? "true" : "false" ) << endl;
        return 0;
    } else {
        cerr << "You need to specify the process name" ;
        return 1;
    }
}

bool FindRunningProcess(AnsiString process) 
{
    AnsiString compare;
    bool procRunning = false;

    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        procRunning = false;
    } else {
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hProcessSnap, &pe32)) {
            if (pe32.szExeFile == process) {
                procRunning = true;
            } else {
                while (Process32Next(hProcessSnap, &pe32)) { 
                    compare = pe32.szExeFile;
                    if (compare == process) {
                        procRunning = true;
                        break;
                    }
                }
            }
            CloseHandle(hProcessSnap);
        }
    }

    return procRunning;
}

/**
compile with 'g++ find_process.cpp'
*/