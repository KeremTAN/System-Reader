#ifdef _WIN32

#include "WindowsReader.hpp"

void WindowsReader::getRamInfo() {

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);
    GlobalMemoryStatusEx(&memInfo);

    std::cout << "Total RAM: " << memInfo.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;
    std::cout << "Free  RAM: " << memInfo.ullAvailPhys / (1024 * 1024) << " MB" << std::endl;
}

void WindowsReader::getHDDInfo() {

    try {
        DWORD drives = GetLogicalDrives();
    
        for (char drive = 'A'; drive <= 'Z'; drive++) {
            if (drives & (1 << (drive - 'A'))) {

                char rootPath[] = {drive, ':', '\\', '\0'};
                
                ULARGE_INTEGER totalBytes;
                ULARGE_INTEGER freeBytes;

                if (GetDiskFreeSpaceEx(rootPath, &freeBytes, &totalBytes, NULL)) {

                    unsigned long long totalSpace = totalBytes.QuadPart / (1024 * 1024);
                    unsigned long long freeSpace = freeBytes.QuadPart / (1024 * 1024); 

                    std::cout << "Driver: " << drive << ": " << std::endl;
                    std::cout << "Total HDD Space: " << totalSpace << " MB" << std::endl;
                    std::cout << "Free  HDD Space: " << freeSpace << " MB" << std::endl;
                    std::cout << std::endl;
                }
                else {
                    
                    std::cerr << "[Error] HDD info could not analyze!\n"
                    <<"[Driver: " << drive << "]"<<std::endl;
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr <<"[Error] "<<e.what() <<std::endl;
    }  
}

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
}
void WindowsReader::getProcessorTemperature() {

}

#endif


