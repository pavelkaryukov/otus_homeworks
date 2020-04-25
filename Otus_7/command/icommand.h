#pragma once
#include <string> 

class IMyCommand {
public:
    using log_text_t = std::string;
    virtual std::string Execute() = 0;
    virtual ~IMyCommand() = default;
};
