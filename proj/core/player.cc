
#include "player.h"
#include "level.h"
#include "game.h"
#include "../excp/not_implemented.h"
#include "../excp/invalid_block_placement.h"
#include "../display/display.h"


// MARK: - Static


// MARK: - Constructors & Destructor
Player::Player(Game *game) :
    score(0),
    highscore(0),
    levelIndex(0),
    curTurn(0),
    lastScoringTurn(0),
    game(game),
    defaultBlockSequence
    (
        std::make_unique<std::ifstream>
        (
            INITIAL_DEFAULT_BLOCK_SEQUENCE
        )
    )
{
    setBoard(DEFAULT_NUM_ROWS, DEFAULT_NUM_COLS);
    initLevels();
    nextBlock = curLevel().getBlock();
    getBlock();
}


// MARK: - Setters
void Player::setDefaultBlockSequence(std::ifstream blockInput)
{
    defaultBlockSequence =
        std::make_shared<std::ifstream>(std::move(blockInput));
    pushDefaultBlockSequence();
}

void Player::setBoard(int numRows, int numCols)
{
    board = std::make_unique<Board>(this, numRows, numCols);
}


// MARK: - Getters
int Player::getScore() const { return score; }

int Player::getHighScore() const { return highscore; }

int Player::getLevelIndex() const { return levelIndex; }

Board *Player::getBoard() const { return board.get(); }

Block *Player::getFallingBlock() const { return fallingBlock.get(); }

Block *Player::getNextBlock() const { return nextBlock.get(); }


// MARK: - Public Functions
void Player::restart()
{
    score = 0;
    curTurn = 0;
    lastScoringTurn = 0;
    defaultBlockSequence->seekg(0, defaultBlockSequence->beg);
    setBoard(DEFAULT_NUM_ROWS, DEFAULT_NUM_COLS);
    initLevels();
}

void Player::drop()
{
    assertBlockFits();
    
    // Move block down until it is resting on a block
    while(board->blockFits(fallingBlock))
    {
        fallingBlock->moveDown();
    }
    
    fallingBlock->moveUp();
    board->addBlock(fallingBlock);

    if (board->blockFits(nextBlock))
    {
        getBlock();
        board->clearFilledRows();
    }
    else
    {
        game->triggerGameOver();
    }
    
    ++curTurn;
    applyWallEffect();
}

void Player::levelUp(int mult)
{
    setLevel(levelIndex + mult);
}

void Player::levelDown(int mult)
{
    setLevel(levelIndex - mult);
}

void Player::unrandomizeCurLevel(std::ifstream &file)
{
    auto fstreamptr = std::make_shared<std::ifstream>(std::move(file));
    curLevel().setBlockSequence(fstreamptr);
    getBlock();
}

void Player::randomizeCurLevel()
{
    if (levelIndex == 0)
    {
        std::cerr << "Sorry! You can't randomize level 0." << std::endl;
        return;
    }
    
    curLevel() = Level::initLevel(levelIndex);
    getBlock();
}

void Player::forceBlock(std::shared_ptr<Block> block)
{
    fallingBlock = block;
    block->setLevelGenerated(curLevel().getNumber());
}

// MARK: Effect Functions
void Player::addEffect(Effect effect)
{
    effects.emplace_back(effect);
}

void Player::clearEffects()
{
    effects.clear();
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
    
    applyHeavyLevel();
    applyHeavySpecial();
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
    
    applyHeavyLevel();
    applyHeavySpecial();
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
    
    applyHeavyLevel();
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
    
    applyHeavyLevel();
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
    
    applyHeavyLevel();
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
    
    applyHeavyLevel();
}

// MARK: Scoring Functions
void Player::rowsCleared(int numRows)
{
    int points = levelIndex + numRows;
    score += points*points;
    updateHighscore();
    
    lastScoringTurn = curTurn+1;
    
    if (numRows >= 2)
    {
        game->triggerSpecialAction();
    }
}

void Player::blockCleared(int lvlGenerated)
{
    int points = lvlGenerated + 1;
    score += points * points;
    updateHighscore();
}

// MARK: Display Functions
void Player::display(BQDisplay &d)
{
    d.accept(this);
}


// MARK: - Private Functions
Level &Player::curLevel()
{
    return levels[levelIndex];
}

// MARK: Effects
void Player::applyHeavyLevel()
{
    if (curLevel().hasEffect(Effect::Heavy))
    {
        moveDownOrDrop();
    }
}

void Player::applyHeavySpecial()
{
    if (hasEffect(Effect::Heavy))
    {
        moveDownOrDrop(2);
    }
}

void Player::applyWallEffect()
{
    if (!curLevel().hasEffect(Effect::Wall)) return;
    int dryStreak = curTurn - lastScoringTurn;
    if (dryStreak != 0 && dryStreak % 5 == 0)
    {
        board->addBrickToWall(curLevel().getNumber());
    }
}

// MARK: Other
void Player::moveDownOrDrop(int mult)
{
    for (int i = 0; i < mult; i++)
    {
        fallingBlock->moveDown();
        if (!board->blockFits(fallingBlock))
        {
            fallingBlock->moveUp();
            drop();
            return;
        }
    }
}

void Player::getBlock()
{
    fallingBlock = nextBlock;
    nextBlock = curLevel().getBlock();
}

void Player::initLevels()
{
    levels = Level::initLevels();
    pushDefaultBlockSequence();
    
    getBlock();
}

void Player::pushDefaultBlockSequence()
{
    levels[0].setBlockSequence(defaultBlockSequence);
}

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
        levelIndex = (int)levels.size() - 1;
    }
    else if (lvl < LEVEL_MIN)
    {
        levelIndex = 0;
    }
    else
    {
        levelIndex = lvl;
    }
}
