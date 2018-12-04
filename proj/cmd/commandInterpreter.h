#ifndef _command_interpreter_
#define _command_interpreter_


#include <istream>
#include <vector>
#include <fstream>
#include <string>
#include "command.h"
#include "../core/block/block.h"

class Game;

class CommandInterpreter
{
    Game *game;
    std::vector<std::shared_ptr<Command>> commands, specialCommands;
    std::istream *curInput;
    
public:
    // These return true if the read was successful
    bool readBool(bool &);
    bool readFile(std::ifstream &);
    bool readBlock(std::shared_ptr<Block> &);

    
    // Constructor
    CommandInterpreter(Game *);
    
    // Add Commands
    void addCommand(std::string, void(Game::*)(int));
    void addCommand(std::string, void(Game::*)());
    void addSpecial(std::string, void(Game::*)());

    // Read Commands
    void readCommandsUntilEOF(std::istream &);
    void readCommand(std::istream &);
    void readSpecial();
    
private:
    void readMultiplier(int &);
    Command &readKeyFrom(std::vector<std::shared_ptr<Command>> &);
};


#endif
