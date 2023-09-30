#ifndef POSIXSREADER_HPP
#define POSIXSREADER_HPP

#include "ISystemReader.hpp"


class PosixReader : public ISystemReader {
    using json = nlohmann::json;
public:
    PosixReader()  = default;
    ~PosixReader() = default;

private:
    void getRamInfo(const json&)               override;
    void getHDDInfo(const json&)               override;
    void getProcessorInfo(const json&)         override;
    void getProcessorTemperature(const json&)  override;
};

#endif