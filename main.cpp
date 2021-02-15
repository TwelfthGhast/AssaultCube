#include <iostream>
#include "util.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    processIDUtil pid_class = processIDUtil();
    std::set<unsigned int> pids = pid_class.get_process_ids("firefox.exe");
    std::cout << pids.size() << std::endl;
    for (auto pid : pids) {
        std::cout << pid << std::endl;
    }

    while (1) {};
    return 0;
}
