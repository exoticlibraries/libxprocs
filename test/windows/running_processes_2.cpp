#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <Winbase.h>
#include <Psapi.h>
#include <Tlhelp32.h>
#include <iostream> 
#include <string>

void PrintProcessNameAndID( DWORD processID )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
    TCHAR szProcessPath[MAX_PATH] = TEXT("<unknown>");

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );
    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) ) {
            GetModuleBaseName( hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );
            GetModuleFileNameExA( hProcess, hMod, szProcessPath, sizeof(szProcessPath)/sizeof(TCHAR) );
        }
    }
    _tprintf( TEXT("%s-%s  (PID: %u)\n"), szProcessName, szProcessPath, processID );
    CloseHandle( hProcess );
}

int main( void ) 
{
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return 1;
    }
    cProcesses = cbNeeded / sizeof(DWORD);
    for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
            PrintProcessNameAndID( aProcesses[i] );
        }
    }

    return 0;
}

/**
https://docs.microsoft.com/en-us/windows/win32/psapi/enumerating-all-processes
https://docs.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-getmodulefilenameexa
https://docs.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-getmappedfilenamea

compile with 'g++ running_processes_2.cpp -lpsapi'
*/