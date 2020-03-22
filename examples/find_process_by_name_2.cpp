/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 January 2019
    \file find_process_by_name_2.cpp
*/

#include "../src/processes.cpp"
#include <iostream>

int main() 
{
    std::vector<libopen::PROCESS> processes = libopen::GetProcessesByName("svchost.exe");
    std::vector<libopen::PROCESS>::iterator it; 
    for(it = processes.begin(); it != processes.end(); ++it) 
        std::cout << libopen::ProcessToString(*it) << std::endl;
    return 0;
}
