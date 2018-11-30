
#include "player.h"
#include "level.h"
#include "../excp/not_implemented.h"
#include "../excp/invalid_block_placement.h"
#include "../display/display.h"
#include "level.h"


Player::Player(std::ifstream &level0input) :
    board(std::make_unique<Board>(this)),
    levels(Level::initLevels(level0input))
{}

// Getters (start)
int Player::getScore() const { return score; }

int Player::getHighScore() const { return highscore; }

Board *Player::getBoard() const { return board.get(); }
// Getters (end)

void Player::drop()
{
    throw not_implemented();
}

void Player::levelUp(int mult)
{
    throw not_implemented();
    //int newLevel = level.curLevel() + mult;
}

void Player::levelDown(int mult)
{
    throw not_implemented();
    //int newLevel = level.curLevel() - mult;
}

void Player::noRandom(std::ifstream &stream)
{
    throw not_implemented();
}

void Player::random()
{
    throw not_implemented();
}


void Player::forceBlock(BlockShape shape)
{
    throw not_implemented();
}

// Movement: right
void Player::moveRight(int mult)
{
    if (!board->blockFits(curBlock))
    {
        throw invalid_block_placement();
    }
    
    for (int i = 0; i < mult; i++)
    {
        curBlock->moveRight();
    }
    
    while (!board->blockFits(curBlock))
    {
        curBlock->moveLeft();
    }
}

// Movement: left
void Player::moveLeft(int mult)
{
    if (!board->blockFits(curBlock))
    {
        throw invalid_block_placement();
    }
    
    for (int i = 0; i < mult; i++)
    {
        curBlock->moveLeft();
    }
    
    while (!board->blockFits(curBlock))
    {
        curBlock->moveRight();
    }
}

// Movement: up
void Player::moveUp(int mult)
{
    if (!board->blockFits(curBlock))
    {
        throw invalid_block_placement();
    }
    
    for (int i = 0; i < mult; i++)
    {
        curBlock->moveUp();
    }
    
    while (!board->blockFits(curBlock))
    {
        curBlock->moveDown();
    }
}

// Movement: down
void Player::moveDown(int mult)
{
    if (!board->blockFits(curBlock))
    {
        throw invalid_block_placement();
    }
    
    for (int i = 0; i < mult; i++)
    {
        curBlock->moveDown();
    }
    
    while (!board->blockFits(curBlock))
    {
        curBlock->moveUp();
    }
}

// Movement: rotate clockwise
void Player::rotateCW(int mult)
{
    if (!board->blockFits(curBlock))
    {
        throw invalid_block_placement();
    }
    
    mult = mult % 4;
    for (int i = 0; i < mult; i++)
    {
        curBlock->rotateCW();
    }
    
    while (!board->blockFits(curBlock))
    {
        curBlock->rotateCCW();
    }
}

// Movement: rotate counter clockwise
void Player::rotateCCW(int mult)
{
    if (!board->blockFits(curBlock))
    {
        throw invalid_block_placement();
    }
    
    mult = mult % 4;
    for (int i = 0; i < mult; i++)
    {
        curBlock->rotateCCW();
    }
    
    while (!board->blockFits(curBlock))
    {
        curBlock->rotateCW();
    }
}


// Point function (Observer Pattern)
void Player::rowsCleared(int numRows)
{
    int points = curLevel + numRows;
    score += points*points;
    updateHighscore();
}

// Point function (Observer Pattern)
void Player::blockCleared(int lvlGenerated)
{
    score += lvlGenerated * lvlGenerated;
    updateHighscore();
}

// Visitor Pattern : visit a display
void Player::display(Display &d)
{
    d.accept(this);
}

void Player::updateHighscore()
{
    if (score > highscore) highscore = score;
}
