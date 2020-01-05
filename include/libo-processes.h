
/*P
    :copyright: 2019, Adewale Azeez
    :license: GNU General Public License v3.0 Copyright (c) 
    :author: Adewale Azeez <azeezadewale98@gmail.com>
    :date: 05 January 2019
    :filename: libo-processes.h
*/

#ifndef LIBO_PROCESSES_H
#define LIBO_PROCESSES_H

#include <list> 
#include <iterator> 
#include <string>

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

typedef struct Process {
    
} Process;

#if defined(__APPLE__) && defined(__MACH__)
#define OPERATINGSYSTEM "Mac OS X"
#endif

#if defined(__FreeBSD__)
#define OPERATINGSYSTEM "FreeBSD"
#endif

#if defined(__NetBSD__)
#define OPERATINGSYSTEM "NetBSD"
#endif

#if defined(__OpenBSD__)
#define OPERATINGSYSTEM "OpenBSD"
#endif

#if defined(__DragonFly__)
#define OPERATINGSYSTEM "DragonFly BSD"
#endif

#if defined(__linux) || defined(linux)
#define OPERATINGSYSTEM "Linux"
#endif

#if defined(sun) || defined(__sun)
    #if defined(__SVR4) || defined(__svr4__)
    #define OPERATINGSYSTEM "Solaris"
    #else
    #define    OPERATINGSYSTEM "SunOS"
    #endif
#endif

#if defined(__HAIKU__)
#define OPERATINGSYSTEM "Haiku"
#endif

#if defined(__WIN32__) || defined(__WINDOWS__) || defined(_MSC_VER) || \
defined (_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#define OPERATINGSYSTEM "Microsoft(R) Windows(TM)"
LIBO_API bool ProcessPathFromId(int processId);
LIBO_API Process ProcessByName(string processName);
LIBO_API list<Process> ProcessesByName(string processName);
#endif

#if defined(__REACTOS__)
#define OPERATINGSYSTEM "ReactOS"
#endif

#if defined(__GNU__)
#define OPERATINGSYSTEM "GNU Hurd"
#endif

#if defined(_AIX)
#define OPERATINGSYSTEM "AIX"
#endif

#if defined(__hpux) || defined(hpux)
#define OPERATINGSYSTEM "HP-UX"
#endif

#if defined(__minix)
#define OPERATINGSYSTEM "MINIX"
#endif

#if defined(PLAN9)
#define OPERATINGSYSTEM "Plan 9"
#endif

#if defined(__QNXNTO__)
#define OPERATINGSYSTEM "QNX Neutrino"
#endif

#if defined(__QNX__)
#define OPERATINGSYSTEM "QNX"
#endif

#if defined(_MIPS_ISA) || defined(_SGI_SOURCE)
#define OPERATINGSYSTEM "IRIX"
#endif

#if defined(__BEOS__)
#define OPERATINGSYSTEM "BeOS"
#endif

#if defined(UNIXV)
#define OPERATINGSYSTEM "UNIX - AT&T System V"
#endif

#if defined(UNIX7)
#define OPERATINGSYSTEM "UNIX - version 7"
#endif

#if defined(NEXTSTEP)
#define OPERATINGSYSTEM "NeXTStep"
#endif

#if defined(OPENSTEP)
#define OPERATINGSYSTEM "OPENSTEP"
#endif

#if defined(macintosh)
#define OPERATINGSYSTEM "Mac OS Classic"
#endif

#if defined(RHAPSODY) && !defined(MAC_OS_X_SERVER)
#define OPERATINGSYSTEM "Rhapsody (pre Mac OS X)"
#endif

#if defined(__OS2__) || defined(OS2) || defined(_OS2)
#define OPERATINGSYSTEM "OS2"
#endif

#if defined(AMIGA) || defined(__amigaos__)
#define OPERATINGSYSTEM "AmigaOS"
#endif

#if defined(__MSDOS__) || defined(__DOS__) || defined(FREEDOS)
#define OPERATINGSYSTEM "MS-DOS or FreeDOS"
#endif


#endif
