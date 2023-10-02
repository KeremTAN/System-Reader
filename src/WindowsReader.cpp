#ifdef _WIN32

#include "WindowsReader.hpp"

void WindowsReader::getRamInfo(const json& jsonData) {

    try {
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(memInfo);
        GlobalMemoryStatusEx(&memInfo);

        jsonData["1 - Total RAM"] = std::to_string(memInfo.ullTotalPhys / (1024 * 1024)) + " MB";
        jsonData["2 - Free  RAM"] = std::to_string(memInfo.ullAvailPhys / (1024 * 1024)) + " MB";
    }
    catch(const std::exception& e) {
        std::cerr <<"[Error] "<<e.what() << '\n';
    }
}

void WindowsReader::getHDDInfo(const json& jsonData) {

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

                    jsonData["2 - Total HDD Space of Driver"] = " " + drive + ": " + std::to_string(totalSpace) + " MB";
                    jsonData["3 - Free  HDD Space of Driver"] = " " + drive + ": " + std::to_string(freeSpace)  + " MB";
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

void WindowsReader::getProcessorInfo(const json& jsonData) {

    try {
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        
        switch (sysInfo.wProcessorArchitecture) {
            case PROCESSOR_ARCHITECTURE_AMD64:
                jsonData["5 - Processor Model"] = "x64";
            break;

            case PROCESSOR_ARCHITECTURE_ARM:
                jsonData["5 - Processor Model"] = "ARM";
            break;

            case PROCESSOR_ARCHITECTURE_INTEL:
                jsonData["5 - Processor Model"] = "x86";
            break;

            case PROCESSOR_ARCHITECTURE_ARM64:
                jsonData["5 - Processor Model"] = "ARM64";
            break;

            case PROCESSOR_ARCHITECTURE_IA64:
                jsonData["5 - Processor Model"] = "Intel Itanium-based";
            break;

            default:
                jsonData["5 - Processor Model"] = "Unknown";
            break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void WindowsReader::getProcessorTemperature(const json& jsonData) { // ??????????????????????????????????

    try {
        FILETIME idleTime, kernelTime, userTime;

        if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {

            ULONGLONG totalTime = ((ULONGLONG)kernelTime.dwLowDateTime + (ULONGLONG)userTime.dwLowDateTime) / 10000;
            
            jsonData["6 - Processor Temperature"] = static_cast<std::string>((totaltime / 100000)) + " degree";
        } 
        else std::cerr << "[Error] Failed to Run Sensors Command!" << std::endl;
    }
    catch(const std::exception& e) {
        std::cerr << "[Error] " << e.what() << '\n';
    }
    
}

#endif


