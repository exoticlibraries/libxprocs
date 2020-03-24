/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 24 March 2020
    \file monitorprocesspath.cpp
    \description listen for processes in a specific path
*/

#define USE_HACKY_PROCESSES_MONITOR

#include "../src/processes.cpp"
#include <iostream>

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

int main() 
{
#ifdef USE_HACKY_PROCESSES_MONITOR
    std::string name;
    std::cout << "Enter the process to monitor : ";
    std::getline(std::cin, name);
    std::cout << "listen for status change of " << name.c_str() << std::endl << std::endl;
    Hacky_MonitorProcessPath(name.c_str(), &ProcessStatusChange, NULL);
#endif
    return 0;
}

// Win: g++ monitorprocesspath.cpp -I../include/ -lpsapi