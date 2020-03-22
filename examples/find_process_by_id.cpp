/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 January 2019
    \file find_process_by_name.cpp
*/

#include "../src/processes.cpp"
#include <iostream>

int main(int argc, char** argv) 
{
    if (argc < 2) {
        std::cerr << "Please specify the process id" << std::endl;
        return 1;
    }
    int id = std::atoi(argv[1]);
    libopen::PROCESS process = libopen::GetProcessById(id);
    if (process.status|libopen::UNKNOWN != 0) {
        std::cout << libopen::process_to_string(process) << std::endl;
    } else {
        std::cerr << "Cannot find the process with id " << id << std::endl;
    }
    return 0;
}
