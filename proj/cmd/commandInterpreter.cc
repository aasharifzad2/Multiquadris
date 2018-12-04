
#include "commandInterpreter.h"
#include <algorithm>
#include "singularCommand.h"
#include "repeatableCommand.h"
#include "../core/game.h"
#include "../excp/eof.h"
#include "../excp/invalid_command.h"
#include "../excp/invalid_block_char.h"



// MARK: - Static
bool CommandInterpreter::readBool
(
    bool &out
)
{
    std::vector<std::string> trueInputs =
    {
        "true", "t", "yes", "y", "+", "on", "enable", "en"
    };
    
    std::vector<std::string> falseInputs =
    {
        "false", "f", "no", "n", "-", "off", "disable", "dis"
    };
    
    std::string input;
    (*curInput) >> input;
    
    bool validIn =
        std::find
        (
            trueInputs.begin(),
            trueInputs.end(),
            input
        ) != trueInputs.end();

    if (validIn)
    {
        out = true;
        return true;
    }
    
    validIn =
        std::find
        (
             falseInputs.begin(),
             falseInputs.end(),
             input
        ) != falseInputs.end();
    
    if (validIn)
    {
        out = false;
    }
    
    return validIn;
}

bool CommandInterpreter::readFile
(
    std::ifstream &out
)
{
    std::string input;
    (*curInput) >> input;
    
    out = std::ifstream{input};
    
    return out.is_open();
}

bool CommandInterpreter::readBlock
(
    std::shared_ptr<Block> &out
)
{
    char c;
    (*curInput) >> c;
    try
    {
        out = Block::makeBlock(c);
        return true;
    }
    catch (invalid_block_char e)
    {
        std::cerr << e.message() << std::endl;
        return false;
    }
}


// MARK: - Constructor
CommandInterpreter::CommandInterpreter(Game *game) :
    game(game)
{}


// MARK: - Public Functions
// MARK: Add Commands
void CommandInterpreter::addCommand
(
    std::string key,
    void(Game::*fn)(int)
)
{
    commands.emplace_back
    (
        std::make_shared<RepeatableCommand>(game, key, fn)
    );
}

void CommandInterpreter::addCommand
(
    std::string key,
    void(Game::*fn)()
)
{
    commands.emplace_back
    (
        std::make_shared<SingularCommand>(game, key, fn)
    );
}

void CommandInterpreter::addSpecial
(
    std::string key,
    void(Game::*fn)()
)
{
    specialCommands.emplace_back
    (
        std::make_shared<SingularCommand>(game, key, fn)
    );
}

// MARK: Read Commands
void CommandInterpreter::readCommandsUntilEOF
(
    std::istream &in
)
{
    try
    {
        while (true)
        {
            readCommand(in);
        }
    }
    catch (eof)
    {
        return;
    }
}

void CommandInterpreter::readCommand
(
    std::istream &in
)
{
    curInput = &in;
    
    try
    {
        int mult;
        readMultiplier(mult);
        Command &cmd = readKeyFrom(commands);
        
        if (mult < 0)
        {
            std::cerr
                << "Multiplier of '"
                << mult
                << "' is invalid, must be at least 0"
                << std::endl;
        }
        
        cmd.execute(mult);
        game->display();
    }
    catch (eof)
    {
        throw;
    }
    catch (invalid_command e)
    {
        std::cerr << e.message() << std::endl;
    }
}

void CommandInterpreter::readSpecial()
{
    try
    {
        std::cout
            << "    FIGHT MILK!!!    "
            << std::endl
            << "Choose one of:";
        
        for (auto cmd : specialCommands)
        {
            std::cout << " '" << cmd->getKey() << "'";
        }
        
        std::cout << std::endl;
        
        Command &cmd = readKeyFrom(specialCommands);
        
        cmd.execute();
    }
    catch (eof)
    {
        throw;
    }
    catch (invalid_command e)
    {
        std::cerr << e.message() << std::endl;
    }
}


// MARK: - Private Functions
void CommandInterpreter::readMultiplier(int &mult)
{
    (*curInput) >> mult;
    if ((*curInput).eof())
    {
        throw eof();
    }
    
    if (!(*curInput))
    {
        mult = 1;
        (*curInput).clear();
    }
}

Command &CommandInterpreter::readKeyFrom
(
    std::vector<std::shared_ptr<Command>> &cmds
)
{
    std::string key;
    (*curInput) >> key;
    if ((*curInput).eof()) throw eof();
    
    std::vector<Command *> matchingCommands;
    
    for (auto &command : cmds)
    {
        if (command->keyMatches(key))
        {
            matchingCommands.emplace_back(command.get());
        }
    }
    
    // One matching command
    if (matchingCommands.size() == 1)
    {
        return *matchingCommands[0];
    }

    // Zero or multiple matching commands
    throw invalid_command(key, matchingCommands);
}
