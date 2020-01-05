
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 January 2019
    \file libo-processes.h
*/

#ifndef LIBO_PROCESSES_H
#define LIBO_PROCESSES_H

#include <list> 
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
#define LIBOPROCESSES_WINDLLEXPORT 1
/* Linux */
#else
#define LIBOPROCESSES_WINDLLEXPORT 0
#endif
#if LIBOPROCESSES_WINDLLEXPORT
#define LIBO_API __declspec(dllexport)
#else
#define LIBO_API extern
#endif

#ifndef MAX_PATH
#def MAX_PATH 1024
#endif

LIBO_API typedef struct PROCESS {
    long long Id;
    std::string exeName;
    std::string exePath;
    int threadCount;
    std::string windowTitle;
    long long lifeTime;
    //char[] icon;
    long long cpuUsage;
    long long memoryUsage;
    long long networkUsage;
    long long diskUsage;
    std::string ownerId;
} PROCESS;

/**
    if it returns true the find process loop continue
*/
typedef bool (*ProcessCondition)( PROCESS process, void* extraParam );

LIBO_API std::list<PROCESS> RunningProcesses( ProcessCondition callbackCondition, void* extraParam );
LIBO_API std::list<PROCESS> OpenedWindowedProcesses();

LIBO_API PROCESS GetProcessById( unsigned int processID );
LIBO_API PROCESS GetProcessByName( std::string processName );
LIBO_API std::list<PROCESS> GetProcessesByName( std::string processName );

LIBO_API bool ProcessPathFromId( int processId );

#if defined(__WIN32__) || defined(__WINDOWS__) || defined(_MSC_VER) || \
defined (_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WIN32
#def _WIN32
#endif
#endif

#endif
