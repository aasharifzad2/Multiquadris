
#ifndef __INVALID_COMMAND_H__
#define __INVALID_COMMAND_H__

#include <vector>
#include <string>
#include "base_exception.h"

class invalid_command : base_exception
{
    std::string command;
    std::vector<std::string> matchingCommands;
    
    public:
    invalid_command(std::string command, std::vector<std::string> matchingCommands);
    std::string message() const noexcept override;
};

#endif
