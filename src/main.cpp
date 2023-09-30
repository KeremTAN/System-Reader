#include "ISystemReader.hpp"
#include "WindowsReader.hpp"
#include "PosixReader.hpp"


int main() {
    std::unique_ptr<ISystemReader> sr = std::make_unique<PosixReader>();

    while (true) {
        sr->getSystemInfo();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
