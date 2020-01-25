#include <iostream>
#include "version.h"
#include <string>
#include <optional>
std::optional<int> TestFunc()
{
    return std::nullopt;
}

int main()
{
    std::cout << "Hello World!" << std::endl;
    std::cout << "Version: " << versions::GetCurrentProjectVersion() << std::endl;
    if (TestFunc() == std::nullopt) {
        std::cout << "gcc sucessfully updated" << std::endl;
    }
    return 0;
}
