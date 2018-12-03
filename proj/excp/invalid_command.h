#ifndef _invalid_command_h_
#define _invalid_command_h_


#include "base_exception.h"
#include <vector>
#include <string>
#include "../cmd/command.h"

class invalid_command : public base_exception
{
    std::string key;
    std::vector<Command *> matchingCommands;
    
public:
    invalid_command(std::string key, std::vector<Command *> matchingCommands);
    std::string message() const noexcept override;
};


#endif
