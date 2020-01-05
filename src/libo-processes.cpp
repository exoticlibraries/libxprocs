
/*P
    :copyright: 2019, Adewale Azeez
    :license: GNU General Public License v3.0 Copyright (c) 
    :author: Adewale Azeez <azeezadewale98@gmail.com>
    :date: 05 January 2019
    :filename: libo-processes.cpp
*/
#include <libo/libo-processes.h> 

PROCESS GetProcessById(unsigned int processID )
{
    PROCESS p; 
    p.Id = processID;
    
    return p;
}

LIBO_API std::list<PROCESS> RunningProcesses() 
{
    std::list<PROCESS> processes;
    unsigned int aProcesses[1024], cbNeeded, cProcesses;
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
            PROCESS p = GetProcessById( aProcesses[i] );
            processes.push_back(p);
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
