/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 23 March 2020
    \file findprocess2.cpp
    \description find process with part name of the process full path
*/

#include "../src/processes.cpp"
#include <iostream>

using namespace libopen;

bool SpecificAppnameCondition(PROCESS process, void* extraParam )
{
    if (process.exePath.find((char*) extraParam) != std::string::npos) {
        return true;
    }
    return false;
}

int main() 
{
    std::string name;
    std::cout << "Enter the process name : ";
    std::getline(std::cin, name);
    std::cout << "Finding processes with name " << name.c_str() << std::endl;
    std::vector<PROCESS> processes = RunningProcesses(&SpecificAppnameCondition, (void*)name.c_str());
    std::vector<PROCESS>::iterator it; 
    for(it = processes.begin(); it != processes.end(); ++it) 
        std::cout << ProcessToString(*it) << std::endl;
    return 0;
}

// Win: g++ findprocess2.cpp -I../include/ -lpsapi