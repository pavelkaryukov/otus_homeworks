#include <iostream>
#include "version.h"
#include <string>
#include <optional>

int main()
{
    std::cout << "Hello World!" << std::endl;
    std::cout << "Version: " << versions::GetCurrentProjectVersion() << std::endl;
    return 0;
}
