
#include "../src/libo-processes.cpp"
#include <iostream>

int main() 
{
    std::list<PROCESS> processes = RunningProcesses();
    std::list<PROCESS>::iterator it; 
    for(it = processes.begin(); it != processes.end(); ++it) 
        std::cout << "Id=" << it->Id << std::endl;
    return 0;
}

// g++ -IC:\Users\azeez\Documents\OPEN_SOURCE\LIBOPROJECTS\libo-processes\include\ list_running_processes.cpp -lpsapi