#ifndef _player_h_
#define _player_h_


#include "level.h"
#include "block/block.h"
#include "board.h"
#include "game.h"
#include "block/blockShape.h"

class Display;

class Player {
    int score = 0; int highscore = 0;
    std::string name;
    Board * board;
    Level lvl;
    std::shared_ptr<Block> curBlock;
    Game *game;
    
    void updateHighscore();
    
    
    public:
    Player(Board *, Level);
    // Getters and setters
    int getScore() const;
    int getHighScore() const;
    std::string getName() const;
    Board *getBoard() const;
    void setName(std::string);
    
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
