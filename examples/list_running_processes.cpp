/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 January 2019
    \file list_running_processes.cpp
*/

#include "../src/processes.cpp"
#include <iostream>

int main() 
{
    std::vector<PROCESS> processes = RunningProcesses(NULL, NULL);
    std::vector<PROCESS>::iterator it; 
    for(it = processes.begin(); it != processes.end(); ++it) 
        std::cout << "Id=" << it->Id << "," << it->exeName << "," << it->exePath << std::endl;
    return 0;
}

// g++ list_running_processes.cpp -I../include/ -lpsapi