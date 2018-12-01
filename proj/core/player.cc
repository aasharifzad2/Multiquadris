
#include "player.h"
#include "level.h"
#include "../excp/not_implemented.h"
#include "../excp/invalid_block_placement.h"
#include "../display/display.h"
#include "level.h"


// MARK: - Static


// MARK: - Constructors & Destructor
Player::Player() {}

Player::Player(std::ifstream &level0input) :
    score(0),
    highscore(0),
#ifdef DEBUG
    curLevel(2),
#else
    curLevel(0),
#endif
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

Block *Player::getFallingBlock() const { return fallingBlock.get(); }


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
    
    board->clearFilledRows();
}

void Player::levelUp(int mult)
{
    setLevel(curLevel + mult);
}

void Player::levelDown(int mult)
{
    setLevel(curLevel - mult);
}

void Player::noRandom(std::ifstream &stream)
{
    throw not_implemented();
}

void Player::random()
{
    throw not_implemented();
}

void Player::forceBlock(std::shared_ptr<Block> block)
{
    fallingBlock = block;
}

bool Player::hasEffect(Effect effect) const
{
    for (auto e : effects)
    {
        if (e == effect) return true;
    }
    return false;
}

// MARK: Movement Functions
void Player::moveRight(int mult)
{
    assertBlockFits();
    
    for (int i = 0; i < mult && board->blockFits(fallingBlock); i++)
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
    
    for (int i = 0; i < mult && board->blockFits(fallingBlock); i++)
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
    
    for (int i = 0; i < mult && board->blockFits(fallingBlock); i++)
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
    
    for (int i = 0; i < mult && board->blockFits(fallingBlock); i++)
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
        fallingBlock->rotateCCW();
    }
}

void Player::rotateCCW(int mult)
{
    assertBlockFits();
    
    mult = mult % 4;
    for (int i = 0; i < mult; i++)
    {
        fallingBlock->rotateCCW();
    }
    
    while (!board->blockFits(fallingBlock))
    {
        fallingBlock->rotateCW();
    }
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
    int points = lvlGenerated + 1;
    score += points * points;
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

void Player::setLevel(int lvl)
{
    if (lvl > LEVEL_MAX)
    {
        curLevel = (int)levels.size() - 1;
        
    }
    else if (lvl < LEVEL_MIN)
    {
        curLevel = 0;
    }
    else
    {
        curLevel = lvl;
    }
}
