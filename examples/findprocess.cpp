/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 06 January 2019
    \file list_running_processes_2.cpp
*/

#include "../src/processes.cpp"
#include <iostream>

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
    std::string name;
    std::cout << "Enter the process name plus ext e.g (brave.exe) to find : ";
    std::getline(std::cin, name);
    std::cout << "Finding processes with name " << name.c_str();
    std::vector<PROCESS> processes = RunningProcesses(&SpecificAppnameCondition, (void*)name.c_str());
    std::vector<PROCESS>::iterator it; 
    for(it = processes.begin(); it != processes.end(); ++it) 
        std::cout << "Id=" << it->Id << "," << it->exeName << "," << it->exePath << std::endl;
    return 0;
}

// g++ findprocess.cpp -I../include/ -lpsapi