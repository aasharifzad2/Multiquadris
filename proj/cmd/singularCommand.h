#ifndef _singular_command_h_
#define _singular_command_h_


#include "command.h"


class SingularCommand : public Command
{
    void (Game::*func)();
    
public:
    // Constructors
    SingularCommand(Game *, std::string, void(Game::*)());
    
    void execute(int multiplier) override;
};


#endif
