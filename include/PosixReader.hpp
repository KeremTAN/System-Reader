#ifndef POSIXSREADER_HPP
#define POSIXSREADER_HPP

#include "ISystemReader.hpp"


class PosixReader : public ISystemReader {
public:
    PosixReader()  = default;
    ~PosixReader() = default;

    void getSystemInfo()    override;

    void getRamInfo()       override;
    void getProcessorInfo() override;
};

#endif