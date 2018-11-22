
#include "base_exception.h"
#include "invalid_command.h"


invalid_command::invalid_command(std::string command, std::vector<std::string> matchingCommands) :
    base_exception(), command(command), matchingCommands(matchingCommands) {}

std::string invalid_command::message() const noexcept
{
    std::string msg = "Command '" + command + "' ";
    
    if (matchingCommands.size() == 0)
    {
        return msg + "does not match any supported commands.";
    }
    else
    {
        msg += "matches multiple commands: ";
        
        // Add all of the commands that match the given command
        for (int i = 0; i < matchingCommands.size(); i++)
        {
            msg += matchingCommands[i];
            if (i != matchingCommands.size() -1)
            {
                msg += ", ";
            }
        }
        
        return msg;
    }
}
