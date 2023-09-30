#ifndef POSIXSREADER_HPP
#define POSIXSREADER_HPP

#include "ISystemReader.hpp"


class PosixReader : public ISystemReader {
public:
    PosixReader()  = default;
    ~PosixReader() = default;

private:
    void getRamInfo()               override;
    void getHDDInfo()               override;
    void getProcessorInfo()         override;
    void getProcessorTemperature()  override;
};

#endif