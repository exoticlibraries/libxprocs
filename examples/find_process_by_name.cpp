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
    libopen::PROCESS process = libopen::GetProcessByName("javaw.exe");
    std::cout << libopen::ProcessToString(process) << std::endl;
    return 0;
}
