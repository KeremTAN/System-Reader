#include "ISystemReader.hpp"
#include "WindowsReader.hpp"
#include "MacOsReader.hpp"
#include "TcpForwarder.hpp"

int main() {
    using json = nlohmann::json;

    #ifdef _WIN32
        std::unique_ptr<ISystemReader> sr = std::make_unique<WindowsReader>();
    #elif __APPLE__
        std::unique_ptr<ISystemReader> sr = std::make_unique<MacOsReader>();
    #endif

    TcpForwarder tcp{};

    while (true) {
        json jsonData;
        sr->getSystemInfo(jsonData);
        //std::cout << jsonData.dump() << std::endl;
        tcp.sendJsonData(jsonData.dump().c_str());

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;
}
