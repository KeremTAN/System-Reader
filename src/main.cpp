#include "ISystemReader.hpp"
#include "WindowsReader.hpp"
#include "PosixReader.hpp"


int main() {

    #ifndef _WIN32
        std::unique_ptr<ISystemReader> sr = std::make_unique<PosixReader>();
    #else
        std::unique_ptr<ISystemReader> sr = std::make_unique<WindowsReader>();
    #endif

    while (true) {
        sr->getSystemInfo();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
