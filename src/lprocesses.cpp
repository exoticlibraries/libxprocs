
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 January 2019
    \file processes.cpp
*/
#include <libopen/lprocesses.h> 

LIBOPEN_API LPROCESS GetProcessById( unsigned int processID )
{
    LPROCESS p; 
    p.Id = processID;
    #ifdef _WIN32
    HANDLE hProcess = OpenProcess( LPROCESS_QUERY_INFORMATION | LPROCESS_VM_READ, FALSE, processID );
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
    Get the list of running processes. The processes are returned in std::vector. 
    The first argument is a callback function that is invoked with the `LPROCESS` and 
    second argument `extraParam` if it not NULL everytime a `LPROCESS` is found. 
    If the callback function returns true it is added to the `std::vector<LPROCESS>` to 
    be returned if it returns false the `LPROCESS` is not added to the return value.
    If the first and seond param is `NULL` all running process is returned
    
    To get all the processes without any condition or calback the first and second parameters 
    should be `NULL` 
    
    \code{.cpp}
    std::vector<LPROCESS> processes = RunningProcesses(NULL, NULL);
    \endcode
 
    \param callbackCondition The call back function that must return either true or false.
    \param extraParam extra parameter passed to the callbackCondition callback function if specified.
    
    \return the std::vector of running LPROCESSes
    
*/
LIBOPEN_API std::vector<LPROCESS> RunningProcesses( ProcessCondition callbackCondition, void* extraParam ) 
{
    std::vector<LPROCESS> processes;
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
            LPROCESS p = GetProcessById((unsigned int)aProcesses[i] );
            if ( callbackCondition != NULL )
            {
                if (callbackCondition(p, extraParam) == true) {
                    processes.push_back(p);
                }
            }  
            else  
            {
                processes.push_back(p);
            }
        }
    }

    return processes;
}


/**

*/
bool CompareProcNameCondition( LPROCESS process, void* extraParam )
{
    if (process.exeName == ((char*) extraParam))
    {
        return true;
    }
    return false;
}

/**

*/
LIBOPEN_API LPROCESS GetProcessByName( const char* processName )
{
    LPROCESS process;
    std::vector<LPROCESS> processes = GetProcessesByName(processName);
    if ( processes.size() > 0) 
    {
        process = processes.at(0);
    }
    return process;
}


/**

*/
LIBOPEN_API std::vector<LPROCESS> GetProcessesByName( const char* processName )
{
    return RunningProcesses(&CompareProcNameCondition, (void*)processName);
}
