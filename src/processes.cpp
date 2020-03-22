
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 January 2019
    \file processes.cpp
*/
#include <libopen/processes.h> 

namespace libopen {

LIBOPEN_API PROCESS GetProcessById( unsigned int processID )
{
    PROCESS p; 
    p.status = PROCESS_STATUS::RUNNING;
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
    Get the list of running processes. The processes are returned in std::vector. 
    The first argument is a callback function that is invoked with the `PROCESS` and 
    second argument `extraParam` if it not NULL everytime a `PROCESS` is found. 
    If the callback function returns true it is added to the `std::vector<PROCESS>` to 
    be returned if it returns false the `PROCESS` is not added to the return value.
    If the first and seond param is `NULL` all running process is returned
    
    To get all the processes without any condition or calback the first and second parameters 
    should be `NULL` 
    
    \code{.cpp}
    std::vector<PROCESS> processes = RunningProcesses(NULL, NULL);
    \endcode
 
    \param callbackCondition The call back function that must return either true or false.
    \param extraParam extra parameter passed to the callbackCondition callback function if specified.
    
    \return the std::vector of running PROCESSes
    
*/
LIBOPEN_API std::vector<PROCESS> RunningProcesses( ProcessCondition callbackCondition, void* extraParam ) 
{
    std::vector<PROCESS> processes;
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
bool CompareProcNameCondition( PROCESS process, void* extraParam )
{
    if (process.exeName == ((char*) extraParam))
    {
        return true;
    }
    return false;
}

/**

*/
LIBOPEN_API PROCESS GetProcessByName( const char* processName )
{
    PROCESS process;
    std::vector<PROCESS> processes = GetProcessesByName(processName);
    if ( processes.size() > 0) 
    {
        process = processes.at(0);
    }
    //TODO: destroy other processes in the list
    return process;
}


/**

*/
LIBOPEN_API std::vector<PROCESS> GetProcessesByName( const char* processName )
{
    return RunningProcesses(&CompareProcNameCondition, (void*)processName);
}

/**

*/
LIBOPEN_API std::string ProcessPathFromId( int processId ) 
{
    return GetProcessById(processId).exePath;
}

LIBOPEN_API std::string process_to_string( PROCESS process )
{
    std::string str_value;
    if (process.status|PROCESS_STATUS::UNKNOWN != 0) {
        str_value += "Id=";
        str_value += std::to_string(process.Id);
        str_value += ",ExeName=";
        str_value += process.exeName.c_str();
        str_value += ",ExePath=";
        str_value += process.exePath.c_str();
        str_value += ",ThreadCount=";
        str_value += std::to_string(process.threadCount);
        str_value += ",LifeTime=";
        str_value += std::to_string(process.lifeTime);
        str_value += ",CpuUsage=";
        str_value += std::to_string(process.cpuUsage);
        str_value += ",DiskUsage=";
        str_value += std::to_string(process.diskUsage);
        str_value += ",MemoryUsage=";
        str_value += std::to_string(process.memoryUsage);
    }
    return str_value;
}

}