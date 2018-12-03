
#include "commandInterpreter.h"
#include "singularCommand.h"
#include "repeatableCommand.h"
#include "../core/game.h"
#include "../excp/eof.h"
#include "../excp/invalid_command.h"

CommandInterpreter::CommandInterpreter(Game *game) :
    game(game)
{}


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

void CommandInterpreter::readCommand()
{
    try
    {
        int mult;
        readMultiplier(mult);
        Command &cmd = readKey();
        
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
        exit(0);
    }
    catch (invalid_command e)
    {
        std::cerr << e.message() << std::endl;
    }
}

void CommandInterpreter::readMultiplier(int &mult)
{
    std::cin >> mult;
    if (std::cin.eof())
    {
        throw eof();
    }
    
    if (!std::cin)
    {
        mult = 1;
        std::cin.clear();
    }
}

Command &CommandInterpreter::readKey()
{
    std::string key;
    std::cin >> key;
    if (std::cin.eof()) throw eof();
    
    std::vector<Command *> matchingCommands;
    
    for (auto &command : commands)
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
