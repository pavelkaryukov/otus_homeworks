#pragma once
#include <string> 

class IMyCommand {
public:
    using log_text_t = std::string;
    virtual log_text_t Execute() = 0;
    virtual ~IMyCommand() = default;
};
