#include <iostream>
#include "utils/util.h"
#include <assert.h>

int main() {
    processIDUtil pid_class = processIDUtil();
    std::set<unsigned int> pids = pid_class.get_process_ids("ac_client.exe");
    assert(pids.size() == 1);

    hookUtil hook_class = hookUtil();
    HANDLE process_handle = hook_class.get_handle(*pids.begin());
    std::cout << "Got a handle!" << std::endl;

    //00509B74 is player base
    int game_address = 0x00400000;
    int player_address = game_address + 0x00109b74;
    int buffer_size = 1024;

    int *base_address = (int *) memoryUtil().read_memory(process_handle, (LPVOID) player_address, sizeof(int));

    int *data = (int *) memoryUtil().read_memory(process_handle, (LPVOID) *base_address, buffer_size);

    while (1) {
        memoryUtil().write_memory(process_handle, (LPVOID) *base_address, data, buffer_size);
        Sleep(1);
    };
    return 0;
}
