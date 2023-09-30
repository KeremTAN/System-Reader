#ifndef ISYSTEMREADER_HPP
#define ISYSTEMREADER_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <memory>
#include <thread>
#include "nlohmann/json.hpp"

#ifdef _WIN32
#include <windows.h>
#include <winbase.h>
#else
#include <unistd.h>
#include <sys/sysctl.h>
#include <sys/statvfs.h>
#endif

class ISystemReader {
    using json = nlohmann::json;
public:
    virtual ~ISystemReader() = default;

    inline void getSystemInfo(const json& jsonData) {

        getRamInfo(jsonData);
        getHDDInfo(jsonData);
        getProcessorInfo(jsonData);
        getProcessorTemperature(jsonData);
    };

private:
    virtual void getRamInfo(const json&)                = 0;
    virtual void getHDDInfo(const json&)                = 0;
    virtual void getProcessorInfo(const json&)          = 0;
    virtual void getProcessorTemperature(const json&)   = 0;
};

#endif