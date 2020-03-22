
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 January 2019
    \file processes.h
*/

#ifndef LIBOPEN_PROCESSES_H
#define LIBOPEN_PROCESSES_H

#include <iterator> 
#include <string>
#include <vector>

#ifdef _WIN32
/*
**  Windows 
**  Support Windows XP 
**  To avoid error message : procedure entry point **  InitializeConditionVariable could not be located **  in Kernel32.dll 
*/
#include <windows.h>
#include <Winbase.h>
#include <Psapi.h>
#include <Tlhelp32.h>
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x502
#define LIBOPENPROCESSES_WINDLLEXPORT 1
/* Linux */
#else
#define LIBOPENPROCESSES_WINDLLEXPORT 0
#endif
#if LIBOPENPROCESSES_WINDLLEXPORT
#define LIBOPEN_API __declspec(dllexport)
#else
#define LIBOPEN_API extern
#endif

#ifndef MAX_PATH
#def MAX_PATH 1024
#endif

namespace libopen {

/**
    The structure of a PROCESS with datas when last requested.
*/
LIBOPEN_API typedef struct PROCESS {
    unsigned int Id;                ///< The process Id
    std::string exeName;            ///< Base process executable name. e.g "devjammer.exe"
    std::string exePath;            ///< Full path to the executable that starts the process 
    int threadCount;                ///< Number of threads used currently by the process
    std::string windowTitle;        ///< Title of the Window if the process is GUI 
    unsigned int lifeTime;          ///< Unix time since the process began
    //char[] icon;                  ///< Icon of the process if exist in array
    unsigned int cpuUsage;          ///< Percentage of CPU used the last time the process status is requested
    unsigned int memoryUsage;       ///< Percentage of memory used the last time the process status is requested
    unsigned int networkUsage;      ///< Network bandwidth used the last time the process status is requested
    unsigned int diskUsage;         ///< Percentage of disk space used the last time the process status is requested
    unsigned int userId;            ///< The Id of the process owner/starter 
} PROCESS;

/**
    if it returns true the find process loop continue
*/
typedef bool (*ProcessCondition)( PROCESS process, void* extraParam );

LIBOPEN_API std::vector<PROCESS> RunningProcesses( ProcessCondition callbackCondition, void* extraParam );
LIBOPEN_API std::vector<PROCESS> OpenedWindowedProcesses();

bool CompareProcNameCondition( PROCESS process, void* extraParam );

LIBOPEN_API PROCESS GetProcessById( unsigned int processID );
LIBOPEN_API PROCESS GetProcessByName( const char* processName );
LIBOPEN_API std::vector<PROCESS> GetProcessesByName( const char* processName );

LIBOPEN_API bool ProcessPathFromId( int processId );

#if defined(__WIN32__) || defined(__WINDOWS__) || defined(_MSC_VER) || \
defined (_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WIN32
#def _WIN32
#endif
#endif

}

#endif
