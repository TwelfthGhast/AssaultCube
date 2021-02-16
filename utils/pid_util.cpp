//
// Created by Dennis Ying on 15/02/2021.
//

#include "util.h"
#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>

std::set<uint_fast32_t> processIDUtil::get_process_ids(std::string process_name, bool force_refresh) {
    if (force_refresh) {
        processIDUtil::_load_process_ids();
    }
    return processIDUtil::_map_process_id(process_name);
}

std::set<uint_fast32_t> processIDUtil::get_process_ids(std::string process_name) {
    return processIDUtil::get_process_ids(process_name, TRUE);
}

std::set<uint_fast32_t> processIDUtil::_map_process_id(std::string process_name) {
    auto search = processIDUtil::pid_map.find(process_name);
    if (search != processIDUtil::pid_map.end()) {
        return search->second;
    } else {
        return std::set<uint_fast32_t>();
    }
}

void processIDUtil::_load_process_ids() {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) {
        std::cout << GetLastError() << std::endl;
        exit(1);
    }

    PROCESSENTRY32 pe32;
    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process and exit if unsuccessful
    if(!Process32First(snap, &pe32) )
    {
        std::cout << GetLastError() << std::endl;
        CloseHandle(snap);  // clean the snapshot object
        exit(1);
    }

    processIDUtil::pid_map.insert({pe32.szExeFile, std::set<uint_fast32_t>({(uint_fast32_t) pe32.th32ProcessID})});
    while (Process32Next(snap, &pe32)) {
        if (processIDUtil::pid_map.find(pe32.szExeFile) != processIDUtil::pid_map.end()) {
            processIDUtil::pid_map[pe32.szExeFile].insert({(uint_fast32_t) pe32.th32ProcessID});
        } else {
            processIDUtil::pid_map.insert({pe32.szExeFile, std::set<uint_fast32_t>({(uint_fast32_t) pe32.th32ProcessID})});
        }
    }
}