
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "game.h"
#include "../display/display.h"
#include "../display/textDisplay.h"
#include "../excp/invalid_command.h"
#include "../excp/not_implemented.h"

#ifdef DEBUG
#include <fstream>
Game::Game() :
    tDisplay(std::cout)
{
    std::ifstream infile = std::ifstream("debug");
    player = new Player(infile);
}
#endif

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
            player->moveLeft(mult);
            break;
        case Right:
            player->moveRight(mult);
            break;
        case Down:
            player->moveDown(mult);
            break;
        case RotateCW:
            player->rotateCW(mult);
            break;
        case RotateCCW:
            player->rotateCCW(mult);
            break;
        case Drop:
            player->drop();
            break;
        case LevelUp:
            player->levelUp(mult);
            break;
        case LevelDown:
            player->levelDown(mult);
            break;
        case NoRandom:
            throw not_implemented();
        case Random:
            throw not_implemented();
            break;
        case Sequence:
            throw not_implemented();
            break;
        case Restart:
            throw not_implemented();
            break;
        case IBlock:
            throw not_implemented();
            break;
        case JBlock:
            throw not_implemented();
            break;
        case LBlock:
            throw not_implemented();
            break;
        case OBlock:
            throw not_implemented();
            break;
        case SBlock:
            throw not_implemented();
            break;
        case ZBlock:
            throw not_implemented();
            break;
        case TBlock:
            throw not_implemented();
            break;
    }
    
    player->display(tDisplay);
}

// Visitor Pattern : Visit a display
void Game::display(Display &d)
{
    d.accept(this);
}
