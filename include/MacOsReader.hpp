#ifndef POSIXSREADER_HPP
#define POSIXSREADER_HPP

#include "ISystemReader.hpp"


class MacOsReader : public ISystemReader {
    using json = nlohmann::json;
public:
    MacOsReader()  = default;
    ~MacOsReader() = default;

private:
    void getRamInfo(json&)               override;
    void getHDDInfo(json&)               override;
    void getProcessorInfo(json&)         override;
    void getProcessorTemperature(json&)  override;
};

#endif