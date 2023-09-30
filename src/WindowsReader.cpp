#ifdef _WIN32

#include "WindowsReader.hpp"


void WindowsReader::getSystemInfo() {

    getRamInfo();
    getProcessorInfo();
};

void WindowsReader::getRamInfo() {

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);
    GlobalMemoryStatusEx(&memInfo);

    std::cout << "Total RAM: " << memInfo.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;
    std::cout << "Free RAM: " << memInfo.ullAvailPhys / (1024 * 1024) << " MB" << std::endl;
};

void WindowsReader::getProcessorInfo() {
    
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    std::cout << "Processor Model: ";
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
};

#endif


