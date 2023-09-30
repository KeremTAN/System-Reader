#ifndef WINDOWSREADER_HPP
#define WINDOWSREADER_HPP

#include "ISystemReader.hpp"

class WindowsReader : public ISystemReader {
public:
    WindowsReader()  = default;
    ~WindowsReader() = default;

    void getSystemInfo()    override;

private:
    void getRamInfo()       override;
    void getProcessorInfo() override;
    void getHDDInfo()       override;
};

#endif