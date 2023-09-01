#pragma once

#define NOMINMAX
#include <Windows.h>
#include <string>
#include <initializer_list>

namespace Utils 
{
    std::uint8_t* PatternScan(void* module, const char* signature);

    std::uint8_t* PatternScan2(const char* module_name, const char* signature);

    std::uint8_t* pattern_scan_char(const char* module_name, const char* signature);

    void SetClantag(const char* tag);

    bool bind(int key, int style);
}
