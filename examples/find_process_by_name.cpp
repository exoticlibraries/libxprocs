
#include "../src/libo-processes.c"
#include <iostream>

int main() 
{
    PROCESS process = ProcessByName("AppMarket.exe");
    std::cout << "Id=" << process.Id << std::endl;
    return 0;
}