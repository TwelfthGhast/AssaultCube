//
// Created by Dennis Ying on 16/02/2021.
//

#include "util.h"
#include <iostream>

HANDLE hookUtil::get_handle(DWORD access, unsigned int process_id) {
    HANDLE processHandle = OpenProcess(
            access,     // Permission level you are seeking
            FALSE,      // Do child processes inherit permissions?
            process_id  // ProcessID you are hooking into
    );
    if (processHandle == NULL) {
        std::cerr << "Could not get handle: " << GetLastError() << std::endl;
        exit(1);
    } else {
        return processHandle;
    }
}

HANDLE hookUtil::get_handle(unsigned int process_id) {
    return hookUtil::get_handle(PROCESS_VM_READ | PROCESS_VM_WRITE, process_id);
}

void hookUtil::close_handle(HANDLE process_handle) {
    int result = CloseHandle(process_handle);
    if (result == 0) {
        std::cerr << GetLastError() << std::endl;
        exit(1);
    }
}