
#include "player.h"
#include "level.h"
#include "../excp/not_implemented.h"
#include "../excp/invalid_block_placement.h"
#include "../display/display.h"
#include "level.h"


// MARK: - Static


// MARK: - Constructors & Destructor
Player::Player(std::ifstream &level0input) :
    board(std::make_unique<Board>(this)),
    levels(Level::initLevels(level0input))
{
    fallingBlock = levels[curLevel].getBlock();
}


// MARK: - Setters


// MARK: - Getters
int Player::getScore() const { return score; }

int Player::getHighScore() const { return highscore; }

int Player::getCurLevel() const { return curLevel; }

Board *Player::getBoard() const { return board.get(); }


// MARK: - Public Functions
void Player::drop()
{
    assertBlockFits();
    
    // Move block down until it is resting on a block
    while(board->blockFits(fallingBlock)) fallingBlock->moveDown();
    fallingBlock->moveUp();
    
    board->addBlock(fallingBlock);
    fallingBlock = levels[curLevel].getBlock();
    
    if (!board->blockFits(fallingBlock))
    {
        // TO DO: Game over
        throw not_implemented();
    }
}

void Player::levelUp(int mult)
{
    throw not_implemented();
}

void Player::levelDown(int mult)
{
    throw not_implemented();
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

// MARK: Movement Functions
void Player::moveRight(int mult)
{
    assertBlockFits();
    
    for (int i = 0; i < mult; i++)
    {
        fallingBlock->moveRight();
    }
    
    while (!board->blockFits(fallingBlock))
    {
        fallingBlock->moveLeft();
    }
}

void Player::moveLeft(int mult)
{
    assertBlockFits();
    
    for (int i = 0; i < mult; i++)
    {
        fallingBlock->moveLeft();
    }
    
    while (!board->blockFits(fallingBlock))
    {
        fallingBlock->moveRight();
    }
}

void Player::moveUp(int mult)
{
    assertBlockFits();
    
    for (int i = 0; i < mult; i++)
    {
        fallingBlock->moveUp();
    }
    
    while (!board->blockFits(fallingBlock))
    {
        fallingBlock->moveDown();
    }
}

void Player::moveDown(int mult)
{
    assertBlockFits();
    
    for (int i = 0; i < mult; i++)
    {
        fallingBlock->moveDown();
    }
    
    while (!board->blockFits(fallingBlock))
    {
        fallingBlock->moveUp();
    }
}

void Player::rotateCW(int mult)
{
    assertBlockFits();
    
    mult = mult % 4;
    for (int i = 0; i < mult; i++)
    {
        fallingBlock->rotateCW();
    }
    
    while (!board->blockFits(fallingBlock))
    {
        rotateCCW();
    }
}

void Player::rotateCCW(int mult)
{
    rotateCW(mult * 3);
}

// MARK: Points Functions
void Player::rowsCleared(int numRows)
{
    int points = curLevel + numRows;
    score += points*points;
    updateHighscore();
}

void Player::blockCleared(int lvlGenerated)
{
    score += lvlGenerated * lvlGenerated;
    updateHighscore();
}

// MARK: Display Functions
void Player::display(Display &d)
{
    d.accept(this);
}


// MARK: - Private Functions
void Player::updateHighscore()
{
    if (score > highscore) highscore = score;
}

void Player::assertBlockFits()
{
    if (!board->blockFits(fallingBlock))
    {
        throw invalid_block_placement();
    }
}
