#ifndef _invalid_command_h_
#define _invalid_command_h_


#include <vector>
#include <string>
#include "base_exception.h"

class invalid_command : public base_exception
{
    std::string command;
    std::vector<std::string> matchingCommands;
    
public:
    invalid_command(std::string command, std::vector<std::string> matchingCommands);
    std::string message() const noexcept override;
};


#endif
