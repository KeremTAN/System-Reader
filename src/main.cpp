#include "ISystemReader.hpp"
#include "WindowsReader.hpp"
#include "MacOsReader.hpp"

int main() {
    using json = nlohmann::json;

    #ifndef _WIN32
        std::unique_ptr<ISystemReader> sr = std::make_unique<MacOsReader>();
    #else
        std::unique_ptr<ISystemReader> sr = std::make_unique<WindowsReader>();
    #endif

    while (true) {
        json jsonData;
        sr->getSystemInfo(jsonData);
        std::cout << jsonData.dump(2) << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
