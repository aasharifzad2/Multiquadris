#ifndef _player_h_
#define _player_h_


#include "level.h"
#include "block/block.h"
#include "board.h"
#include "game.h"
#include "block/blockShape.h"

class Player {
    int score;
    int highscore;
    std::string name;
    Board board;
    Level level;
    std::shared_ptr<Block> curBlock;
    Game *game;
    
    public:
    Player(Board, Level);
    
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
};

#endif
