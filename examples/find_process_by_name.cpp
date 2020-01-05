
#include "../src/libo-processes.cpp"
#include <iostream>

int main() 
{
    PROCESS process = ProcessByName("AppMarket.exe");
    std::cout << "Id=" << process.Id << std::endl;
    return 0;
}

// g++ -IC:\Users\azeez\Documents\OPEN_SOURCE\LIBOPROJECTS\libo-processes\include\ find_process_by_name.cpp -lpsapi