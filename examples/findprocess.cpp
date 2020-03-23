/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 22 March 2020
    \file findprocess.cpp
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
    std::string name;
    std::cout << "Enter the process name plus ext e.g (brave.exe) to find : ";
    std::getline(std::cin, name);
    std::cout << "Finding processes with name " << name.c_str() << std::endl;
    std::vector<PROCESS> processes = RunningProcesses(&SpecificAppnameCondition, (void*)name.c_str());
    std::vector<PROCESS>::iterator it; 
    for(it = processes.begin(); it != processes.end(); ++it) 
        std::cout << ProcessToString(*it) << std::endl;
    return 0;
}

// Win: g++ findprocess.cpp -I../include/ -lpsapi