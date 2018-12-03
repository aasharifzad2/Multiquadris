
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include "game.h"
#include "../display/display.h"
#include "../display/textDisplay.h"
#include "../display/richTextDisplay.h"
#include "../excp/invalid_command.h"
#include "../excp/not_implemented.h"

#include "block/shape/iBlock.h"
#include "block/shape/jBlock.h"
#include "block/shape/lBlock.h"
#include "block/shape/oBlock.h"
#include "block/shape/sBlock.h"
#include "block/shape/zBlock.h"
#include "block/shape/tBlock.h"



// MARK: - Static


// MARK: - Constructors & Destructor
Game::Game() :
    playerIndex(0)
{
    setNumPlayers(1);
    setRichTextEnabled(false);
    setGraphicsEnabled(false);
}


// MARK: - Setters
void Game::setNumPlayers(int numPlayers)
{
    if (numPlayers < MIN_NUM_PLAYERS)
    {
        std::cerr
            << "Sorry! You must have atleast one player"
            << std::endl;
        
        numPlayers = MIN_NUM_PLAYERS;
    }
    
    if (numPlayers > MAX_NUM_PLAYERS)
    {
        std::cerr
            << "Sorry! You can't have more than five players"
            << std::endl;
        
        numPlayers = MAX_NUM_PLAYERS;
    }
    
    while (players.size() < numPlayers)
    {
        players.emplace_back(std::make_unique<Player>());
    }
    
    while (players.size() > numPlayers)
    {
        players.pop_back();
    }
    
    if (playerIndex > numPlayers - 1)
    {
        playerIndex = numPlayers - 1;
    }
}

void Game::setSequences()
{
    throw not_implemented();
}

void Game::setGraphicsEnabled(bool enabled)
{
    if (enabled)
    {
        gDisplay = std::make_unique<GraphicDisplay>();
    }
    else
    {
        gDisplay = nullptr;
    }
}

void Game::setRichTextEnabled(bool enabled)
{
    if (enabled)
    {
        tDisplay = std::make_unique<RichTextDisplay>();
    }
    else
    {
        tDisplay = std::make_unique<TextDisplay>();
    }
}


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

int Game::getPlayerIndex() const { return playerIndex; }


// MARK: - Public Functions
void Game::play()
{
    display();

    while (true)
    {
        readCommand(std::cin);
    }
}

void Game::addPlayer(std::ifstream &sequenceFile)
{
    players.emplace_back(std::make_unique<Player>());
}


// MARK: - Private Functions
void Game::restart()
{
    for (auto &player : players)
    {
        player->restart();
    }
    
    playerIndex = 0;
}

Player *Game::curPlayer() const
{
    return players[playerIndex].get();
}

Player *Game::nextPlayer() const
{
    int index = (playerIndex + 1) % players.size();
    return players[index].get();
}

void Game::endTurn()
{
    playerIndex = (playerIndex + 1) % players.size();
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

void Game::printCommandInput() const
{
    for (auto cmd : commandsRead)
    {
        std::cout << cmd << std::endl;
    }
}

bool Game::readCommand(std::istream &in)
{
    int mult;
    std::string input;
    Command cmd;
    
    in >> mult;
    if (in.eof())
    {
        return false;
    }
    if (!in)
    {
        mult = 1;
        in.clear();
    }
    
    in >> input;
    
    if (mult < 0)
    {
        std::cerr << "Multiplier of '" << mult << "' is invalid, must be at least 0" << std::endl;
        return false;
    }
    
    try
    {
        cmd = getCommand(input);
    }
    catch (invalid_command e)
    {
        std::cerr << e.message() << std::endl;
        return false;
    }

    switch (cmd)
    {
        case Left:
        {
            curPlayer()->moveLeft(mult);
            break;
        }
        case Right:
        {
            curPlayer()->moveRight(mult);
            break;
        }
        case Down:
        {
            curPlayer()->moveDown(mult);
            break;
        }
        case RotateCW:
        {
            curPlayer()->rotateCW(mult);
            break;
        }
        case RotateCCW:
        {
            curPlayer()->rotateCCW(mult);
            break;
        }
        case Drop:
        {
            curPlayer()->drop();
            endTurn();
            break;
        }
        case LevelUp:
        {
            curPlayer()->levelUp(mult);
            break;
        }
        case LevelDown:
        {
            curPlayer()->levelDown(mult);
            break;
        }
        case NoRandom:
        {
            std::string filename;
            in >> filename;
            std::ifstream fstream{filename};
            curPlayer()->unrandomizeCurLevel(fstream);
            break;
        }
        case Random:
        {
            curPlayer()->randomizeCurLevel();
            break;
        }
        case Sequence:
        {
            std::string filename;
            in >> filename;
            std::ifstream file(filename);
            while (readCommand(file));
            break;
        }
        case Restart:
        {
            restart();
            break;
        }
        case ForceIBlock:
        {
            curPlayer()->forceBlock(std::make_shared<IBlock>());
            break;
        }
        case ForceJBlock:
        {
            curPlayer()->forceBlock(std::make_shared<JBlock>());
            break;
        }
        case ForceLBlock:
        {
            curPlayer()->forceBlock(std::make_shared<LBlock>());
            break;
        }
        case ForceOBlock:
        {
            curPlayer()->forceBlock(std::make_shared<OBlock>());
            break;
        }
        case ForceSBlock:
        {
            curPlayer()->forceBlock(std::make_shared<SBlock>());
            break;
        }
        case ForceZBlock:
        {
            curPlayer()->forceBlock(std::make_shared<ZBlock>());
            break;
        }
        case ForceTBlock:
        {
            curPlayer()->forceBlock(std::make_shared<TBlock>());
            break;
        }
        case PrintCommandInput:
        {
            printCommandInput();
            break;
        }
        case EnableGraphics:
        {
            setGraphicsEnabled();
            break;
        }
        case DisableGraphics:
        {
            setGraphicsEnabled(false);
            break;
        }
        case EnableRichText:
        {
            setRichTextEnabled();
            break;
        }
        case DisableRichText:
        {
            setRichTextEnabled(false);
            break;
        }
        case AddPlayer:
        {
            setNumPlayers((int)players.size() + mult);
            break;
        }
        case RemovePlayer: {
            setNumPlayers((int)players.size() - mult);
            break;
        }
    }
    
    commandsRead.emplace_back(std::to_string(mult) + input);
    
    display();
    return true;
}

// Visitor Pattern : Visit a display
void Game::display()
{
    if (tDisplay) tDisplay->accept(this);
    if (gDisplay) gDisplay->accept(this);
}
