#ifndef POSIXSREADER_HPP
#define POSIXSREADER_HPP

#include "ISystemReader.hpp"


class PosixReader : public ISystemReader {
public:
    PosixReader()  = default;
    ~PosixReader() = default;

    void getSystemInfo()    override;

private:
    void getRamInfo()       override;
    void getProcessorInfo() override;
    void getHDDInfo()       override;
};

#endif