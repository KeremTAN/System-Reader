#ifndef _WIN32

#include "PosixReader.hpp"

void PosixReader::getRamInfo() {

    size_t len{ sizeof(long long) };
    long long ramSize{};
    sysctlbyname("hw.memsize", &ramSize, &len, NULL, 0);

    std::cout << "Total RAM: " << ramSize / (1024 * 1024) << " MB" << std::endl;
}

void PosixReader::getProcessorInfo() {
    
    size_t len{};
    sysctlbyname("hw.model", NULL, &len, NULL, 0);

    std::unique_ptr<char[]> model(new char[len * sizeof(char)]);
    sysctlbyname("hw.model", model.get(), &len, NULL, 0);
    
    std::cout << "Processor Model: " << model << std::endl;
}

void PosixReader::getHDDInfo() {

    struct statvfs vfs;
    try {
        if (statvfs("/", &vfs) != -1) {

            unsigned long long total_space = vfs.f_frsize * vfs.f_blocks;
            unsigned long long available_space = vfs.f_frsize * vfs.f_bfree;
            
            std::cout << "Total HDD Space: " << total_space / (1024 * 1024) << " MB" << std::endl;
            std::cout << "Free  HDD Space: " << available_space / (1024 * 1024) << " MB" << std::endl;
        }

        else {
            std::cerr << "[Error] HDD info could not analyze." << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr <<"[Error] "<<e.what() <<std::endl;
    }
}

void PosixReader::getProcessorTemperature() {
    
}

#endif