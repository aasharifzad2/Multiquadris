#ifndef _board_h_
#define _board_h_


#include <vector>
#include <memory>
#include "block/block.h"
class Cell;
class Block;
class BQDisplay;
class Player;

const int
    DEFAULT_NUM_ROWS = 18,
    DEFAULT_NUM_COLS = 11;

class Board
{
    Player *player;
    int numRows, numCols;
    std::vector<std::shared_ptr<Block>> blocks;
    std::vector<std::vector<std::shared_ptr<Cell>>> cells;
    
public:
    Board(Player *, int numRows = DEFAULT_NUM_ROWS, int numCols = DEFAULT_NUM_COLS);
  
    // Getters
    std::vector<std::vector<Cell *>> getCells() const;
    int getNumRows() const;
    int getNumCols() const;
    
    bool blockFits(std::shared_ptr<Block>);
    void addBlock(std::shared_ptr<Block>);
    void clearFilledRows();
    
    // Add one block to the middle of the board
    void addBrickToWall(int);
    
    // Visitor Pattern : visit(BQDisplay)
    void display(BQDisplay &);
    
private:
    void fillBoard();
};


#endif
