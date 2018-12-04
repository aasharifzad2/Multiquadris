#ifndef _repeatable_command_h_
#define _repeatable_command_h_


#include "command.h"


class RepeatableCommand : public Command
{
    void (Game::*func)(int);
    
public:
    // Constructors
    RepeatableCommand(Game *, std::string, void(Game::*)(int));
    
    void execute(int multiplier) override;
};


#endif
