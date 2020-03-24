/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 23 March 2020
    \file listenforprocesses.cpp
*/

#define USE_HACKY_PROCESSES_MONITOR
#define THREADS_COUNT 2

#include "../src/processes.cpp"
#include <iostream>
#include <pthread.h>
#include <list>

using namespace libopen;

void ProcessStatusChange(PROCESS process, void* extraParam)
{
    if (process.status == PROCESS_STATUS::STARTED)
    {
        std::cout << (process.windowTitle.size() > 0 ? process.windowTitle : process.exeName) << " has started running" << std::endl;
        
    } else if (process.status == PROCESS_STATUS::STOPPED)
    {
        std::cout << (process.windowTitle.size() > 0 ? process.windowTitle : process.exeName) << " has stopped running" << std::endl;
    }
    
}

void *FindProcess(void *processPath)
{
    const char* name;
    name = (const char*)processPath;
    Hacky_MonitorProcessPath(name, &ProcessStatusChange, NULL);
    return NULL;
}

int main() 
{
#ifdef USE_HACKY_PROCESSES_MONITOR
    std::vector<std::string> processes_to_monitor;
    int i;
    int rc;
    int count;
    
    std::string count_input;
    std::cout << "How many program do you want to monitor : ";
    std::getline(std::cin, count_input);
    count = atoi(count_input.c_str());
    
    for( i = 0; i < count; i++ ) 
    {
        std::string name;
        std::cout << "Enter the program " << (i+1) << " name : ";
        std::getline(std::cin, name);
        processes_to_monitor.push_back(name);
    }
    for( i = 0; i < count; i++ ) 
    {
        pthread_t thread;
        rc = pthread_create(&thread, NULL, FindProcess, (void*)processes_to_monitor[i].c_str());
        
        if (rc) {
            std::cerr << "cannot monitor process " << processes_to_monitor[i] << std::endl;
            return -1;
        }
    }
    pthread_exit(NULL);
    
#endif
    return 0;
}

// Win: g++ listenforprocesses.cpp -I../include/ -lpsapi -lpthread