#include <windows.h>
#include <Winbase.h>
#include <Psapi.h>
#include <Tlhelp32.h>
#include <iostream> 
#include <string>

using namespace std; 

int main(int argc, char** argv) {
    if (argc > 1) {
        HANDLE processHandle = NULL;
        TCHAR filename[MAX_PATH];
        processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, atoi(argv[1]));
        if (processHandle != NULL) {
            if (GetModuleFileNameEx(processHandle, NULL, filename, MAX_PATH) == 0) {
                cout << "Failed to get module filename." << endl;
            } else {
                cout << "FilePath: " << filename << endl;
            }
            CloseHandle(processHandle);
        } else {
            cerr << "Failed to open process." << endl;
        }
        return 0;
    } else {
        cerr << "You need to specify the process id as first arg" ;
        return 1;
    }
}

/**
https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlea?redirectedfrom=MSDN
http://msdn.microsoft.com/en-us/library/ms683197%28VS.85%29.aspx

compile with 'g++ process_full_path.cpp -lpsapi'

*/