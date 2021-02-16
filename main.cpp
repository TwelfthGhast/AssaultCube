#include <iostream>
#include "utils/util.h"
#include <assert.h>

int main() {
    processIDUtil pid_class = processIDUtil();
    std::set<unsigned int> pids = pid_class.get_process_ids("AssaultCube.exe");
    assert(pids.size() == 1);
    auto pids_iterator = pids.begin();

    hookUtil hook_class = hookUtil();
    HANDLE process_handle = hook_class.get_handle(*pids_iterator);
    std::cout << "Got a handle!" << std::endl;
    hook_class.close_handle(process_handle);

    while (1) {};
    return 0;
}
