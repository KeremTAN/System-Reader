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

    inline void getSystemInfo(json& jsonData) {

        getRamInfo(jsonData);
        getHDDInfo(jsonData);
        getProcessorInfo(jsonData);
        getProcessorTemperature(jsonData);
    };

private:
    virtual void getRamInfo(json&)                = 0;
    virtual void getHDDInfo(json&)                = 0;
    virtual void getProcessorInfo(json&)          = 0;
    virtual void getProcessorTemperature(json&)   = 0;
};

#endif