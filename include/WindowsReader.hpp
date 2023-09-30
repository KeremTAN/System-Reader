#ifndef WINDOWSREADER_HPP
#define WINDOWSREADER_HPP

#include "ISystemReader.hpp"

class WindowsReader : public ISystemReader {
    using json = nlohmann::json;
public:
    WindowsReader()  = default;
    ~WindowsReader() = default;

private:
    void getRamInfo(const json&)               override;
    void getHDDInfo(const json&)               override;
    void getProcessorInfo(const json&)         override;
    void getProcessorTemperature(const json&)  override;
};

#endif