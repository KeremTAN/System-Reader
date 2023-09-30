#ifndef WINDOWSREADER_HPP
#define WINDOWSREADER_HPP

#include "ISystemReader.hpp"

class WindowsReader : public ISystemReader {
public:
    WindowsReader()  = default;
    ~WindowsReader() = default;

private:
    void getRamInfo()               override;
    void getHDDInfo()               override;
    void getProcessorInfo()         override;
    void getProcessorTemperature()  override;
};

#endif