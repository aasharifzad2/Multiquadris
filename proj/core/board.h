#ifndef _board_h_
#define _board_h_


#include <vector>
#include <memory>
#include "block.h"
class Cell;
class Block;
class Display;
class Player;

const int
    DEFAULT_NUM_ROWS = 15,
    DEFAULT_NUM_COLS = 11;

class Board
{
    int numRows, numCols;
    Player *player;
    std::vector<std::shared_ptr<Block>> blocks;
    std::vector<std::vector<std::shared_ptr<Cell>>> cells;
    
    
    void fillBoard();
    void addEmptyRows(int = 1);
    
    
    public:

    Board(Player *, int numRows = DEFAULT_NUM_ROWS, int numCols = DEFAULT_NUM_COLS);

    // Getters
    std::vector<std::vector<Cell *>> getCells() const;
    int getNumCols() const;
    
    bool blockFits(std::shared_ptr<Block>);
    void addBlock(std::shared_ptr<Block>);
    void clearFilledRows();
    // Visitor Pattern : visit(Display)
    void display(Display &);
};


#endif
