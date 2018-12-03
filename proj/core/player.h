#ifndef _player_h_
#define _player_h_


#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <utility>
#include "level.h"
#include "block/block.h"
#include "board.h"
#include "block/blockShape.h"
class Game;

const std::string
    INITIAL_DEFAULT_BLOCK_SEQUENCE = "./blocksq/default.bsq";


class Player
{
    int score, highscore;
    int levelIndex;
    int curTurn, lastScoringTurn;
    Game *game;
    std::shared_ptr<std::ifstream> defaultBlockSequence;
    std::unique_ptr<Board> board;
    std::shared_ptr<Block> fallingBlock, nextBlock;
    std::vector<Level> levels;
    std::vector<Effect> effects;
    
public:
    Player(Game *);
    
    // Setters
    void setDefaultBlockSequence(std::ifstream);
    void setBoard(int numCols, int numRows);
    
    // Getters
    int getScore() const;
    int getHighScore() const;
    int getLevelIndex() const;
    Board *getBoard() const;
    Block *getFallingBlock() const;
    Block *getNextBlock() const;
    
    void restart();
    void drop();
    void levelUp(int);
    void levelDown(int);
    void unrandomizeCurLevel(std::ifstream &);
    void randomizeCurLevel();
    void forceBlock(std::shared_ptr<Block>);
    bool hasEffect(Effect) const;
    
    // Movement and rotation functions
    void moveRight(int = 1);
    void moveLeft(int = 1);
    void moveUp(int = 1);
    void moveDown(int = 1);
    void rotateCW(int = 1);
    void rotateCCW(int = 1);
    
    // Observer Pattern : Board notifies Player that they've scored points
    void rowsCleared(int);
    void blockCleared(int lvlGenerated);
    
    // Visitor Pattern : Visit a display
    void display(BQDisplay &);
    
private:
    // Returns the current level
    Level &curLevel();
    
    // Effects
    void applyHeavyLevel();
    void applyHeavySpecial();
    
    // If possible, the block moves down, otherwise it drops
    void moveDownOrDrop(int = 1);
    
    // sets the falling block from level
    void getBlock();
    void initLevels();
    // updates the levels that use the default filestream with block sequence
    void pushDefaultBlockSequence();
    // updates the highscore if it is broken
    void updateHighscore();
    // throws an exception if fallingBlock does not fit the board
    void assertBlockFits();
    // sets the level, going to the max/min level if trying to set out of bounds
    void setLevel(int);
};

#endif
