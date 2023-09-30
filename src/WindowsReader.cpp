#ifdef _WIN32

#include "WindowsReader.hpp"

void WindowsReader::getRamInfo() {

    try {
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(memInfo);
        GlobalMemoryStatusEx(&memInfo);

        std::cout << "Total RAM: " << memInfo.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;
        std::cout << "Free  RAM: " << memInfo.ullAvailPhys / (1024 * 1024) << " MB" << std::endl;
    }
    catch(const std::exception& e) {
        std::cerr <<"[Error] "<<e.what() << '\n';
    }
}

void WindowsReader::getHDDInfo() {

    try {
        DWORD drives = GetLogicalDrives();
    
        for (char drive = 'A'; drive <= 'Z'; drive++) {
            if (drives & (1 << (drive - 'A'))) {
                
                ULARGE_INTEGER totalBytes;
                ULARGE_INTEGER freeBytes;

                wchar_t rootPath[] = { drive, L':', L'\\', L'\0' };
                if (GetDiskFreeSpaceExW(rootPath, &freeBytes, &totalBytes, NULL)) {

                    unsigned long long totalSpace = totalBytes.QuadPart / (1024 * 1024);
                    unsigned long long freeSpace = freeBytes.QuadPart / (1024 * 1024); 

                    std::cout << "Driver: " << drive << ": " << std::endl;
                    std::cout << "Total HDD Space: " << totalSpace << " MB" << std::endl;
                    std::cout << "Free  HDD Space: " << freeSpace << " MB" << std::endl;
                    std::cout << std::endl;
                }
                else {
                    
                    std::cerr << "[Error] Failed to Analyze HDD Information!\n"
                    <<"[Driver: " << drive << "]" <<'\n';
                }
            }
        }
    }
    catch(const std::exception& e) {
        std::cerr <<"[Error] "<<e.what() << '\n';
    }  
}

void WindowsReader::getProcessorInfo() {

    try {
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
                std::cout << "Unknown" << '\n';
            break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void WindowsReader::getProcessorTemperature() {

    try {
        FILETIME idleTime, kernelTime, userTime;

        if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {

            ULONGLONG totalTime = ((ULONGLONG)kernelTime.dwLowDateTime + (ULONGLONG)userTime.dwLowDateTime) / 10000;

            std::cout << "Processor Temperature: " << totalTime << " degree" << std::endl;
        } 
        else std::cerr << "[Error] Failed to Run Sensors Command!" << std::endl;
    }
    catch(const std::exception& e) {
        std::cerr << "[Error] " << e.what() << '\n';
    }
    
}

#endif


