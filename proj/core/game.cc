
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "game.h"
#include "../display/display.h"
#include "../display/textDisplay.h"
#include "../display/richTextDisplay.h"
#include "../excp/invalid_command.h"
#include "../excp/not_implemented.h"


// MARK: - Static


// MARK: - Constructors & Destructor
Game::Game(Display &display) :
    playerIndex(0),
    tDisplay(display)
{
    
}


// MARK: - Setters


// MARK: - Getters
std::vector<Player *> Game::getPlayers() const
{
    std::vector<Player *> playerPtrs;
    for (int i = 0; i < players.size(); i++)
    {
        playerPtrs.emplace_back(players[i].get());
    }
    
    return playerPtrs;
}


// MARK: - Public Functions
void Game::play()
{
    while (true)
    {
        readCommand();
    }
}

void Game::addPlayer(std::ifstream &sequenceFile)
{
    players.emplace_back(std::make_unique<Player>(sequenceFile));
}


// MARK: - Private Functions
Player *Game::curPlayer() const
{
    return players[playerIndex].get();
}

Player *Game::nextPlayer() const
{
    int index = (playerIndex + 1) % players.size();
    return players[index].get();
}

// MARK: Command Functions
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
            curPlayer()->moveLeft(mult);
            break;
        case Right:
            curPlayer()->moveRight(mult);
            break;
        case Down:
            curPlayer()->moveDown(mult);
            break;
        case RotateCW:
            curPlayer()->rotateCW(mult);
            break;
        case RotateCCW:
            curPlayer()->rotateCCW(mult);
            break;
        case Drop:
            curPlayer()->drop();
            break;
        case LevelUp:
            curPlayer()->levelUp(mult);
            break;
        case LevelDown:
            curPlayer()->levelDown(mult);
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
    
    display(tDisplay);
}

// Visitor Pattern : Visit a display
void Game::display(Display &d)
{
    d.accept(this);
}
