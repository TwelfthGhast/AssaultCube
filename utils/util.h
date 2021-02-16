//
// Created by Dennis Ying on 15/02/2021.
//

#ifndef ASSAULTCUBE_UTIL_H
#define ASSAULTCUBE_UTIL_H

#include <string>
#include <unordered_map>
#include <set>
#include <Windows.h>
#include <tlhelp32.h>

class processIDUtil {
    std::unordered_map<std::string, std::set<uint_fast32_t>> pid_map = {};

    void _load_process_ids();

    std::set<uint_fast32_t> _map_process_id(std::string process_name);

public:
    std::set<uint_fast32_t> get_process_ids(std::string process_name);

    std::set<uint_fast32_t> get_process_ids(std::string process_name, bool force_refresh);
};

class hookUtil {
public:
    HANDLE get_handle(DWORD access_level, unsigned int process_id);

    HANDLE get_handle(unsigned int process_id);

    void close_handle(HANDLE process_handle);
};

#endif //ASSAULTCUBE_UTIL_H
