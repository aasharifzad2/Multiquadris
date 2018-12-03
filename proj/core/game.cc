
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
    playerIndex(0),
    cmd(this)
{
    initCommands();
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
        players.emplace_back(std::make_unique<Player>(this));
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
        cmd.readCommand();
    }
}

void Game::over()
{
    display();
    
    std::cout
        << "%%%%%%%%%%%%%%%%%%%" << std::endl
        << "%%%  GAME OVER  %%%" << std::endl
        << "%%%%%%%%%%%%%%%%%%%" << std::endl
        << std::endl;
    
    if (players.size() == 1)
    {
        std::cout
            << "You ended with a highscore of: "
            << players[playerIndex]->getHighScore()
            << std::endl
            << std::endl;
    }
    else if (players.size() == 2)
    {
        std::cout
            << "Player " << (2-playerIndex) << " won!" << std::endl
            << "Player 1 highscore: "
            << players[0]->getHighScore() << std::endl
            << "Player 2 highscore: "
            << players[1]->getHighScore() << std::endl
            << std::endl;
    }
    else
    {
        // map for score and vectors of player numbers with that score
        std::map<int, std::vector<int>> scores;
        for (int i = 0; i < players.size(); i++)
        {
            // Add all the non-losing scorers to the score board
            if (i != playerIndex)
            {
                scores[players[i]->getHighScore()].emplace_back(i+1);
            }
        }
        
        int place = 1;
        for (auto itr = scores.rbegin(); itr != scores.rend(); ++itr)
        {
            for (auto playerNum : itr->second)
            {
                std::cout
                    << place
                    << ". Player "
                    << playerNum
                    << "    "
                    << itr->first
                    << std::endl;
            }
            
            place++;
        }
        
        // Print Loser's Score
        std::cout
            << place
            << ". Player "
            << playerIndex + 1
            << "    "
            << curPlayer()->getHighScore()
            << std::endl
            << std::endl;
        
    }
    
    exit(0);
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

void Game::endTurn()
{
    playerIndex = (playerIndex + 1) % players.size();
}

// Visitor Pattern : Visit a display
void Game::display()
{
    if (tDisplay) tDisplay->accept(this);
    if (gDisplay) gDisplay->accept(this);
}


// MARK: - Command Functions
void Game::initCommands()
{
    cmd.addCommand("left", &Game::moveBlockLeft);
    cmd.addCommand("right", &Game::moveBlockRight);
    cmd.addCommand("down", &Game::moveBlockDown);
    cmd.addCommand("clockwise", &Game::rotateBlockCW);
    cmd.addCommand("counterclockwise", &Game::rotateBlockCCW);
    cmd.addCommand("drop", &Game::dropBlock);
    cmd.addCommand("levelup", &Game::increaseCurPlayerLevel);
    cmd.addCommand("leveldown", &Game::decreaseCurPlayerLevel);
    cmd.addCommand("norandom", &Game::randomizeCurPlayerLevel);
    cmd.addCommand("random", &Game::unrandomizeCurPlayerLevel);
    cmd.addCommand("sequence", &Game::readSequence);
    cmd.addCommand("restart", &Game::restart);
    cmd.addCommand("I", &Game::forceIBlock);
    cmd.addCommand("J", &Game::forceJBlock);
    cmd.addCommand("L", &Game::forceLBlock);
    cmd.addCommand("O", &Game::forceOBlock);
    cmd.addCommand("S", &Game::forceSBlock);
    cmd.addCommand("Z", &Game::forceZBlock);
    cmd.addCommand("T", &Game::forceTBlock);
    cmd.addCommand("precmd", &Game::printCommandInput);
    cmd.addCommand("engraphics", &Game::enableGraphics);
    cmd.addCommand("disgraphics", &Game::disableGraphics);
    cmd.addCommand("enrichtext", &Game::enableRichText);
    cmd.addCommand("disrichtext", &Game::disableRichText);
    cmd.addCommand("addplayer", &Game::addPlayer);
    cmd.addCommand("removeplayer", &Game::removePlayer);
}

void Game::moveBlockLeft(int multiplier)
{
    curPlayer()->moveLeft(multiplier);
}

void Game::moveBlockRight(int multiplier)
{
    curPlayer()->moveRight(multiplier);
}

void Game::moveBlockDown(int multiplier)
{
    curPlayer()->moveDown(multiplier);
}

void Game::rotateBlockCW(int multiplier)
{
    curPlayer()->rotateCW(multiplier);
}

void Game::rotateBlockCCW(int multiplier)
{
    curPlayer()->rotateCCW(multiplier);
}

void Game::dropBlock()
{
    curPlayer()->drop();
    endTurn();
}

void Game::increaseCurPlayerLevel(int multiplier)
{
    curPlayer()->levelUp(multiplier);
}

void Game::decreaseCurPlayerLevel(int multiplier)
{
    curPlayer()->levelDown(multiplier);
}

void Game::randomizeCurPlayerLevel()
{
    curPlayer()->randomizeCurLevel();
}

void Game::unrandomizeCurPlayerLevel()
{
    std::string filename;
    //in >> filename;
    std::ifstream fstream{filename};
    curPlayer()->unrandomizeCurLevel(fstream);
}

void Game::readSequence()
{
//    std::string filename;
//    //in >> filename;
//    std::ifstream file(filename);
    //while (cmd.readCommand(file));
}

void Game::restart()
{
    for (auto &player : players)
    {
        player->restart();
    }
    
    playerIndex = 0;
}

void Game::forceIBlock()
{
    curPlayer()->forceBlock(std::make_shared<IBlock>());
}

void Game::forceJBlock()
{
    curPlayer()->forceBlock(std::make_shared<JBlock>());
}

void Game::forceLBlock()
{
    curPlayer()->forceBlock(std::make_shared<LBlock>());
}

void Game::forceOBlock()
{
    curPlayer()->forceBlock(std::make_shared<OBlock>());
}

void Game::forceSBlock()
{
    curPlayer()->forceBlock(std::make_shared<SBlock>());
}

void Game::forceZBlock()
{
    curPlayer()->forceBlock(std::make_shared<ZBlock>());
}

void Game::forceTBlock()
{
    curPlayer()->forceBlock(std::make_shared<TBlock>());
}

void Game::printCommandInput()
{
    for (auto cmd : commandsRead)
    {
        std::cout << cmd << std::endl;
    }
}

void Game::enableGraphics()
{
    setGraphicsEnabled(true);
}

void Game::disableGraphics()
{
    setGraphicsEnabled(false);
}

void Game::enableRichText()
{
    setRichTextEnabled(true);
}

void Game::disableRichText()
{
    setRichTextEnabled(false);
}

void Game::addPlayer(int multiplier)
{
    setNumPlayers((int)players.size() + multiplier);
}

void Game::removePlayer(int multiplier)
{
    setNumPlayers((int)players.size() - multiplier);
}
