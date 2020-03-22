/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 January 2019
    \file find_process_by_name.cpp
*/

#include "../src/lprocesses.cpp"
#include <iostream>

int main() 
{
    LPROCESS process = GetProcessByName("javaw.exe");
    std::cout << "Id=" << process.Id << std::endl;
    return 0;
}
