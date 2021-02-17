#include "util.h"
#include <stdlib.h>
#include <iostream>

void *memoryUtil::read_memory(HANDLE process_handle, LPVOID address, int size) {
    void *buffer = malloc(size);
    BOOL rpm_status = ReadProcessMemory(
            process_handle,
            (LPCVOID) address,
            buffer,
            size,
            NULL
    );
    if (rpm_status == 0) {
        std::cerr << "Could not read process memory: " << GetLastError() << std::endl;
    }
    return buffer;
}

void memoryUtil::write_memory(HANDLE process_handle, LPVOID address, void *data, int size) {
    memoryUtil::write_memory(process_handle, address, data, size, FALSE);
}

void memoryUtil::write_memory(HANDLE process_handle, LPVOID address, void *data, int size, bool dealloc) {
    BOOL wpm_status = WriteProcessMemory(
            process_handle,
            (LPVOID) address,
            data,
            size,
            NULL
    );
    if (wpm_status == 0) {
        std::cerr << "Could not write to process memory: " << GetLastError() << std::endl;
        exit(1);
    } else if (dealloc) {
        free(data);
    }
}