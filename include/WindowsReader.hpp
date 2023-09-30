#ifndef WINDOWSREADER_HPP
#define WINDOWSREADER_HPP

#include "ISystemReader.hpp"

class WindowsReader : public ISystemReader {
public:
    WindowsReader()  = default;
    ~WindowsReader() = default;

    void getSystemInfo()    override;

    void getRamInfo()       override;
    void getProcessorInfo() override;
};

#endif