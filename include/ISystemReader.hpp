#ifndef ISYSTEMREADER_HPP
#define ISYSTEMREADER_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <memory>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#include <winbase.h>
#else
#include <unistd.h>
#include <sys/sysctl.h>
#include <sys/statvfs.h>
#endif

class ISystemReader {
public:
    virtual ~ISystemReader() = default;

    inline void getSystemInfo() {

        getRamInfo();
        getHDDInfo();
        getProcessorInfo();
        getProcessorTemperature();
    };

private:
    virtual void getRamInfo() = 0;
    virtual void getHDDInfo() = 0;
    virtual void getProcessorInfo() = 0;
    virtual void getProcessorTemperature() = 0;
};

#endif