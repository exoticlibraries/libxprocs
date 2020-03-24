
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 January 2019
    \file processes.cpp
*/
#include <libopen/processes.h> 
#include <iostream> //TODO: remove

namespace libopen {

/**
 */
LIBOPEN_API void InitProcess( PROCESS *process ) 
{
    process->status = PROCESS_STATUS::UNKNOWN;
    process->Id = 0;
    process->cpuUsage = 0;
    process->memoryUsage = 0;
    process->networkUsage = 0;
    process->diskUsage = 0;
    process->userId = 0;
    process->lifeTime = 0;
    process->threadCount = 1;
}

/**
 */
LIBOPEN_API PROCESS GetProcessById( unsigned int processID )
{
    PROCESS p; 
    InitProcess(&p);
    p.Id = processID;
    #ifdef _WIN32
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID );
    if ( hProcess != NULL )
    {
        p.status = PROCESS_STATUS::RUNNING;
        HMODULE hMod;
        DWORD cbNeeded;
        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) ) 
        {
            TCHAR szProcessName[MAX_PATH] = TEXT("");
            TCHAR szProcessPath[MAX_PATH] = TEXT("");
            
            GetModuleBaseName( hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );
            GetModuleFileNameExA( hProcess, hMod, (LPSTR)szProcessPath, sizeof(szProcessPath)/sizeof(TCHAR) );
            p.exeName = (char *)szProcessName;
            p.exePath = (char *)szProcessPath;
            
            
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
    return (process.exeName == ((char*) extraParam));
}

/**

*/
LIBOPEN_API PROCESS GetProcessByName( const char* processName )
{
    PROCESS process;
    InitProcess(&process);
    process.exeName = processName;
    std::vector<PROCESS> processes = GetProcessesByName(processName);
    if ( processes.size() > 0) 
    {
        process = processes.at(0);
        processes.clear();
    }
    return process;
}

/**
    //TODO: possibly return the first process spawned
*/
LIBOPEN_API std::vector<PROCESS> GetProcessesByName( const char* processName )
{
    return RunningProcesses(&CompareProcNameCondition, (void*)processName);
}

/**

*/
bool CompareProcPathLikeCondition( PROCESS process, void* extraParam )
{
    return (process.exePath.find((char*) extraParam) != std::string::npos);
}

/**
    Get the first process by part of the execuitable path value `PROCESS.exePath`
    //TODO: possibly return the first process spawned
*/
LIBOPEN_API PROCESS GetProcessByPart( const char* processName )
{
    PROCESS process;
    InitProcess(&process);
    process.exeName = processName;
    std::vector<PROCESS> processes = GetProcessesByPart(processName);
    if ( processes.size() > 0) 
    {
        process = processes.at(0);
        processes.clear();
    }
    return process;
}

/**

*/
LIBOPEN_API std::vector<PROCESS> GetProcessesByPart( const char* processName )
{
    return RunningProcesses(&CompareProcPathLikeCondition, (void*)processName);
}

/**

*/
LIBOPEN_API std::string GetProcessPathFromId( int processId ) 
{
    return GetProcessById(processId).exePath;
}

LIBOPEN_API std::string ProcessToString( PROCESS process )
{
    std::string str_value;
    str_value += "Id=";
    str_value += std::to_string(process.Id);
    str_value += ",Status=";
    str_value += std::to_string(process.status);
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
    return str_value;
}

// Listeners and lifecycles


// hacky

#ifdef USE_HACKY_PROCESSES_MONITOR

//use id as key
LIBOPEN_API void Hacky_MonitorProcess( const char* processName, ProcessStatusChanged processStatusCallback, void* extraParam )
{
    std::map<std::string, PROCESS_STATUS> mapOfProcess;
    PROCESS process;
    do {
        process = GetProcessByPart(processName);
        if (process.status == PROCESS_STATUS::UNKNOWN) {
            if (mapOfProcess.find(process.exeName) != mapOfProcess.end()) {
                if (mapOfProcess[process.exeName] != PROCESS_STATUS::STOPPED) {
                    process.status = PROCESS_STATUS::STOPPED;
                }
                mapOfProcess.erase(process.exeName);
            }
            goto report_process_status;
        }
        if (mapOfProcess.find(process.exeName) == mapOfProcess.end()) {
            process.status = PROCESS_STATUS::STARTED;
            mapOfProcess.insert(std::make_pair(process.exeName, PROCESS_STATUS::UNKNOWN));
        }
        if (mapOfProcess[process.exeName] != process.status) {
            mapOfProcess[process.exeName] = process.status;
            goto report_process_status;
        }
        
        continue;
        report_process_status:
            if (processStatusCallback != NULL) {
                processStatusCallback(process, extraParam);
            }
    } while(true);
}

//use id as key
//also convert name to lowercase
LIBOPEN_API void Hacky_MonitorProcessPath( const char* processName, ProcessStatusChanged processStatusCallback, void* extraParam )
{
    std::map<std::string, PROCESS> mapOfProcess;
    std::vector<PROCESS> processes;
    PROCESS process;
    do {
        processes = GetProcessesByPart(processName);
        std::vector<PROCESS>::iterator it; 
        std::set<std::string> found_processes;
        for(it = processes.begin(); it != processes.end(); ++it) {
            process = *it;
            found_processes.insert(process.exeName);
            if (process.status == PROCESS_STATUS::UNKNOWN) {
                if (mapOfProcess.find(process.exeName) != mapOfProcess.end()) {
                    if (mapOfProcess[process.exeName].status != PROCESS_STATUS::STOPPED) {
                        process.status = PROCESS_STATUS::STOPPED;
                    }
                    mapOfProcess.erase(process.exeName);
                }
                goto report_process_status;
            }
            if (mapOfProcess.find(process.exeName) == mapOfProcess.end()) {
                mapOfProcess.insert(std::make_pair(process.exeName, process));
                mapOfProcess[process.exeName].status = PROCESS_STATUS::STARTED;
            }
            goto report_process_status;
            
            continue;
            report_process_status:
                if (processStatusCallback != NULL) {
                    processStatusCallback(mapOfProcess[process.exeName], extraParam);
                    mapOfProcess[process.exeName].status = process.status;
                }
        }
        if (mapOfProcess.size() != processes.size()) {
            std::map<std::string, PROCESS>::iterator it;
            for (it = mapOfProcess.begin(); it != mapOfProcess.end(); it++ )
            {
                if (found_processes.find(it->first) == found_processes.end())
                {
                    if (mapOfProcess[it->first].status != PROCESS_STATUS::STOPPED) {
                        mapOfProcess[it->first].status = PROCESS_STATUS::STOPPED;
                    }
                    if (processStatusCallback != NULL) {
                        processStatusCallback(mapOfProcess[it->first], extraParam);
                    }
                    mapOfProcess.erase(it->first);
                }
            }
        }
        found_processes.clear();
    } while(true);
}

#endif

}