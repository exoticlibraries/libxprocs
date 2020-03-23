/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 23 March 2020
    \file listenforprocess.cpp
*/

#define USE_HACKY_PROCESSES_MONITOR

#include "../src/processes.cpp"
#include <iostream>

using namespace libopen;

void ProcessStatusChange(PROCESS process, void* extraParam)
{
    if (process.status == PROCESS_STATUS::STARTED)
    {
        std::cout << process.exeName << " has started running" << std::endl;
    }
    
}

int main() 
{
#ifdef USE_HACKY_PROCESSES_MONITOR
    std::string name;
    std::cout << "Enter the process name plus ext e.g (brave.exe) to find : ";
    std::getline(std::cin, name);
    std::cout << "Finding processes with name " << name.c_str() << std::endl;
    PROCESS process = GetProcessByName(name.c_str());
    Hacky_MonitorProcess(process, &ProcessStatusChange, NULL);
    //std::vector<PROCESS> processes = RunningProcesses(&SpecificAppnameCondition, (void*)name.c_str());
    //std::vector<PROCESS>::iterator it; 
    //for(it = processes.begin(); it != processes.end(); ++it) 
    //    std::cout << "Id=" << it->Id << "," << it->exeName << "," << it->exePath << std::endl;
#endif
    return 0;
}

// Win: g++ listenforprocess.cpp -I../include/ -lpsapi