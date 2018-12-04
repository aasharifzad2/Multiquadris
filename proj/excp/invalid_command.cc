
#include "base_exception.h"
#include "invalid_command.h"


invalid_command::invalid_command
(
    std::string key,
    std::vector<Command *> matchingCommands
) :
    base_exception(),
    key(key),
    matchingCommands(matchingCommands)
{}

std::string invalid_command::message() const noexcept
{
    std::string msg = "Command '" + key + "' ";
    
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
            msg += matchingCommands[i]->getKey();
            if (i != matchingCommands.size() -1)
            {
                msg += ", ";
            }
        }
        
        return msg;
    }
}
