#ifndef WINDOWSREADER_HPP
#define WINDOWSREADER_HPP

#include "ISystemReader.hpp"

class WindowsReader : public ISystemReader {
    using json = nlohmann::json;
public:
    WindowsReader()  = default;
    ~WindowsReader() = default;

private:
    void getRamInfo(json&)               override;
    void getHDDInfo(json&)               override;
    void getProcessorInfo(json&)         override;
    void getProcessorTemperature(json&)  override;
};

#endif