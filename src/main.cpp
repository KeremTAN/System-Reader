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
#endif

void getSystemInfo() {
    
    #ifdef _WIN32
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    std::cout << "Processor Architecture: ";
    switch (sysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            std::cout << "x64" << std::endl;
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            std::cout << "ARM" << std::endl;
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            std::cout << "x86" << std::endl;
            break;
        default:
            std::cout << "Unknown" << std::endl;
            break;
    }

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);
    GlobalMemoryStatusEx(&memInfo);

    std::cout << "Total RAM: " << memInfo.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;
    std::cout << "Free RAM: " << memInfo.ullAvailPhys / (1024 * 1024) << " MB" << std::endl;

    #else
    size_t len = 0;
    sysctlbyname("hw.model", NULL, &len, NULL, 0);

    std::unique_ptr<char[]> model(new char[len * sizeof(char)]);
    sysctlbyname("hw.model", model.get(), &len, NULL, 0);

    long long ramSize = 0;
    sysctlbyname("hw.memsize", &ramSize, &len, NULL, 0);

    std::cout << "Processor Model: " << model << std::endl;
    std::cout << "Total RAM: " << ramSize / (1024 * 1024) << " MB" << std::endl;

    #endif
}

int main() {
    while (true) {
        getSystemInfo();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
