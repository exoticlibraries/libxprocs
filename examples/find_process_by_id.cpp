/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 January 2019
    \file find_process_by_name.cpp
*/

#include "../src/processes.cpp"
#include <iostream>

int main() 
{
    PROCESS process = GetProcessById(1);
    std::cout << "Id=" << process.exeName << std::endl;
    return 0;
}
