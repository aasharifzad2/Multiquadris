
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "game.h"
#include "../excp/invalid_command.h"


void Game::play()
{
    while (true)
    {
        readCommand();
    }
}

Command Game::getCommand(std::string cmd)
{
    // Find all of the commands that match
    std::vector<std::string> matchingStrings;
    std::vector<Command> matchingCommands;
    for (auto cmdPair : commands)
    {
        if (cmd.length() > cmdPair.first.length()) continue;
        if (cmdPair.first.compare(0, cmd.length(), cmd) == 0)
        {
            matchingStrings.emplace_back(cmdPair.first);
            matchingCommands.emplace_back(cmdPair.second);
        }
    }
    
    // One matching command
    if (matchingCommands.size() == 1)
    {
        return matchingCommands[0];
    }
    
    // Zero or multiple matching commands
    throw invalid_command(cmd, matchingStrings);
}

void Game::readCommand()
{
    int mult;
    std::string input;
    Command cmd;
    
    std::cin >> mult;
    if (std::cin.eof())
    {
        exit(0);
    }
    if (!std::cin)
    {
        mult = 1;
        std::cin.clear();
    }
    
    std::cin >> input;
    
    if (mult < 0)
    {
        std::cerr << "Multiplier of '" << mult << "' is invalid, must be at least 0" << std::endl;
        return;
    }
    
    std::cout << mult << "x ";
    
    try
    {
        cmd = getCommand(input);
    }
    catch (invalid_command e)
    {
        std::cerr << e.message() << std::endl;
        return;
    }
    
    switch (cmd)
    {
        case Left:
            std::cout << "move left" << std::endl;
            break;
        case Right:
            std::cout << "move right" << std::endl;
            break;
        case Down:
            std::cout << "move down" << std::endl;
            break;
        case RotateCW:
            std::cout << "rotate cw" << std::endl;
            break;
        case RotateCCW:
            std::cout << "rotate ccw" << std::endl;
            break;
        case Drop:
            std::cout << "drop block" << std::endl;
            break;
        case LevelUp:
            std::cout << "increase difficulty" << std::endl;
            break;
        case LevelDown:
            std::cout << "decrease difficulty" << std::endl;
            break;
        case NoRandom:
            std::cout << "no random" << std::endl;
            break;
        case Random:
            std::cout << "randomize" << std::endl;
            break;
        case Sequence:
            std::cout << "sequence" << std::endl;
            break;
        case Restart:
            std::cout << "restart" << std::endl;
            break;
        case IBlock:
            std::cout << "force I" << std::endl;
            break;
        case JBlock:
            std::cout << "force J" << std::endl;
            break;
        case LBlock:
            std::cout << "force L" << std::endl;
            break;
        case OBlock:
            std::cout << "force O" << std::endl;
            break;
        case SBlock:
            std::cout << "force S" << std::endl;
            break;
        case ZBlock:
            std::cout << "force Z" << std::endl;
            break;
        case TBlock:
            std::cout << "force T" << std::endl;
            break;
    }
}
