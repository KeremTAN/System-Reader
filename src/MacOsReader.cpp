#ifdef __APPLE__

#include "MacOsReader.hpp"
#include <sstream>

void MacOsReader::getRamInfo(json& jsonData) {
    
    try {
        size_t len{ sizeof(long long) };
        long long ramSize{};
        sysctlbyname("hw.memsize", &ramSize, &len, NULL, 0);

        jsonData["Total RAM"] = std::to_string(ramSize / (1024 * 1024));
        //std::cout << "Total RAM: " << ramSize / (1024 * 1024) << " MB" << std::endl;  
    }
    catch(const std::exception& e) {
        std::cerr << "[Error] " << e.what() << '\n';
    }
}

void MacOsReader::getProcessorInfo(json& jsonData) {

    try {
        size_t len{};
        sysctlbyname("hw.model", NULL, &len, NULL, 0);

        std::unique_ptr<char[]> model(new char[len * sizeof(char)]);
        sysctlbyname("hw.model", model.get(), &len, NULL, 0);
        
        jsonData["Processor Model"] = model.get();
        //std::cout << "Processor Model: " << model << std::endl;   
    }
    catch(const std::exception& e) {
        std::cerr << "[Error] " << e.what() << '\n';
    }  
}

void MacOsReader::getHDDInfo(json& jsonData) {

    try {
        struct statvfs vfs;
        if (statvfs("/", &vfs) != -1) {

            unsigned long long total_space = vfs.f_frsize * vfs.f_blocks;
            unsigned long long available_space = vfs.f_frsize * vfs.f_bfree;
            
            jsonData["Total HDD Space"] = std::to_string(total_space / (1024 * 1024));
            jsonData["Free HDD Space"] = std::to_string(available_space / (1024 * 1024));
            
            //std::cout << "Total HDD Space: " << total_space / (1024 * 1024) << " MB" << std::endl;
            //std::cout << "Free  HDD Space: " << available_space / (1024 * 1024) << " MB" << std::endl;
        }

        else std::cerr << "[Error] Failed to Analyze HDD Information!" << std::endl;
    }
    catch(const std::exception& e) {
        std::cerr << "[Error] " << e.what() << '\n';
    }
}

void MacOsReader::getProcessorTemperature(json& jsonData) { // ??????????????????????????????????

    try {
        if (FILE* fp = popen("/opt/homebrew/Cellar/osx-cpu-temp/1.1.0/bin/osx-cpu-temp", "r")) {

            char buffer[128];
            while (fgets(buffer, sizeof(buffer), fp) != nullptr) { 
                jsonData["Processor Temperature"] = buffer;
                //std::cout << "Processor Temperature: " << buffer << " degree" << std::endl;
                break;
            }

            pclose(fp);
        }

        else std::cerr << "[Error] Failed to Run Sensors Command!" << std::endl;
    }
    catch(const std::exception& e) {
        std::cerr << "[Error] " << e.what() << '\n';
    }
}

#endif