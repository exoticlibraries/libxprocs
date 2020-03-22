/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 23 March 2020
    \file find_process_path_by_id.cpp
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
    std::string path = libopen::ProcessPathFromId(id);
    if (path.length() > 0) {
        std::cout << "Id=" << id << ",ProcessPath=" << path << std::endl;
    } else {
        std::cerr << "Cannot find the process with id " << id << std::endl;
    }
    return 0;
}


//Win: g++ findprocess.cpp -I../include/ -lpsapi