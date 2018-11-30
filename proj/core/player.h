#ifndef _player_h_
#define _player_h_


#include "level.h"
#include "block/block.h"
#include "board.h"
#include "game.h"
#include "block/blockShape.h"


class Player
{
    int score = 0, highscore = 0, curLevel = 0;
    std::unique_ptr<Board> board;
    std::vector<Level> levels;
    std::shared_ptr<Block> curBlock;
    Game *game;
    
    void updateHighscore();
    void initLevels();
    
    public:
    Player(std::ifstream &);
    
    // Getters
    int getScore() const;
    int getHighScore() const;
    Board *getBoard() const;
    
    void drop();
    void levelUp(int);
    void levelDown(int);
    void noRandom(std::ifstream &);
    void random();
    void forceBlock(BlockShape);
    
    // Movement and rotation functions
    void moveRight(int);
    void moveLeft(int);
    void moveUp(int);
    void moveDown(int);
    void rotateCW(int);
    void rotateCCW(int);
    
    // Point functions (Observer)
    void rowsCleared(int);
    void blockCleared(int lvlGenerated);
    
    // Visitor Pattern : visit a display
    void display(Display &);
    
};

#endif
