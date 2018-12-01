#ifndef _player_h_
#define _player_h_


#include "level.h"
#include "block/block.h"
#include "board.h"
#include "block/blockShape.h"
class Game;

class Player
{
    int score, highscore, curLevel;
    std::unique_ptr<Board> board;
    std::shared_ptr<Block> fallingBlock;
    std::vector<Level> levels;
    std::vector<Effect> effects;
    Game *game;
    
    
    public:
    Player();
    Player(std::ifstream &);
    
    // Getters
    int getScore() const;
    int getHighScore() const;
    int getCurLevel() const;
    Board *getBoard() const;
    Block *getFallingBlock() const;
    
    void drop();
    void levelUp(int);
    void levelDown(int);
    void noRandom(std::ifstream &);
    void random();
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
    void display(Display &);
    
private:
    // updates the highscore if it is broken
    void updateHighscore();
    // throws an exception if fallingBlock does not fit the board
    void assertBlockFits();
    // sets the level, going to the max/min level if trying to set out of bounds
    void setLevel(int);
};

#endif
