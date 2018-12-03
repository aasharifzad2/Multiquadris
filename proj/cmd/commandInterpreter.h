#ifndef _command_interpreter_
#define _command_interpreter_


#include <iostream>
#include <vector>
#include <string>
#include "command.h"

class Game;

class CommandInterpreter
{
    Game *game;
    std::vector<std::shared_ptr<Command>> commands;
    std::vector<std::string> commandsRun;
    
public:
    CommandInterpreter(Game *);
    void addCommand(std::string, void(Game::*)(int));
    void addCommand(std::string, void(Game::*)());
    void readCommand();

private:
    void readMultiplier(int &);
    Command &readKey();
};


#endif
