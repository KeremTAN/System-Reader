#ifndef _WIN32

#include "PosixReader.hpp"


void PosixReader::getSystemInfo() {

    getRamInfo();
    getProcessorInfo();
};

void PosixReader::getRamInfo() {
    size_t len{ sizeof(long long) };
    long long ramSize{};
    sysctlbyname("hw.memsize", &ramSize, &len, NULL, 0);

    std::cout << "Total RAM: " << ramSize / (1024 * 1024) << " MB" << std::endl;
};

void PosixReader::getProcessorInfo() {
    
    size_t len{};
    sysctlbyname("hw.model", NULL, &len, NULL, 0);

    std::unique_ptr<char[]> model(new char[len * sizeof(char)]);
    sysctlbyname("hw.model", model.get(), &len, NULL, 0);
    
    std::cout << "Processor Model: " << model << std::endl;
};

#endif