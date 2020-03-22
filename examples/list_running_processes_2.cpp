/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 06 January 2019
    \file list_running_processes_2.cpp
*/

#include "../src/processes.cpp"
#include <iostream>

using namespace libopen;

bool SpecificAppnameCondition(PROCESS process, void* extraParam )
{
    if (process.exeName == ((char*) extraParam))
    {
        return true;
    }
    return false;
}

int main() 
{
    std::vector<PROCESS> processes = RunningProcesses(&SpecificAppnameCondition, (char*)"brave.exe");
    std::vector<PROCESS>::iterator it; 
    for(it = processes.begin(); it != processes.end(); ++it) 
        std::cout << "Id=" << it->Id << "," << it->exeName << "," << it->exePath << std::endl;
    return 0;
}

// g++ list_running_processes_2.cpp -I../include/ -lpsapi