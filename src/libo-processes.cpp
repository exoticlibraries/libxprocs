
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 January 2019
    \file libo-processes.cpp
*/
#include <libo/libo-processes.h> 

LIBO_API PROCESS GetProcessById( unsigned int processID )
{
    PROCESS p; 
    p.Id = processID;
    #ifdef _WIN32
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID );
    if ( hProcess != NULL )
    {
        HMODULE hMod;
        DWORD cbNeeded;
        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) ) 
        {
            TCHAR szProcessName[MAX_PATH] = TEXT("");
            TCHAR szProcessPath[MAX_PATH] = TEXT("");
            
            GetModuleBaseName( hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );
            GetModuleFileNameExA( hProcess, hMod, szProcessPath, sizeof(szProcessPath)/sizeof(TCHAR) );
            p.exeName = szProcessName;
            p.exePath = szProcessPath;
            
            
            ZeroMemory( szProcessName, sizeof(szProcessName) );
            ZeroMemory( szProcessPath, sizeof(szProcessPath) );
        }
    }
    #else
    
    #endif
    
    return p;
}

/**
    Get the list of running processes. The processes are returned in std::list. 
 
    \param callbackCondition The call back function that must return either true or false.
    \param extraParam extra parameter passed to the callbackCondition callback function if specified.
    
    \return the std::list of running PROCESSes
    
*/
LIBO_API std::list<PROCESS> RunningProcesses( ProcessCondition callbackCondition, void* extraParam ) 
{
    std::list<PROCESS> processes;
    #ifdef _WIN32
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    #else
    unsigned int aProcesses[1024], cbNeeded, cProcesses;
    #endif
    unsigned int i;

    if (!EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ))
    {
        return processes;
    }
    cProcesses = cbNeeded / sizeof(DWORD);
    for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
            PROCESS p = GetProcessById((unsigned int)aProcesses[i] );
            processes.push_back(p);
            if ( callbackCondition != NULL )
            {
                if (callbackCondition(p, extraParam) == false) {
                    break;
                }
            }
        }
    }

    return processes;
}

LIBO_API PROCESS ProcessByName(std::string processName)
{
    PROCESS proc = {};
    std::string compare;
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        proc.Id = pe32.th32ProcessID;
        //get other datas
    } else {
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hProcessSnap, &pe32)) {
            if (pe32.szExeFile == processName) {
                proc.Id = pe32.th32ProcessID;
                //get other datas
            } else {
                while (Process32Next(hProcessSnap, &pe32)) { 
                    compare = pe32.szExeFile;
                    if (compare == processName) {
                        proc.Id = pe32.th32ProcessID;
                        //get other datas
                        break;
                    }
                }
            }
            CloseHandle(hProcessSnap);
        }
    }

    return proc;
}
