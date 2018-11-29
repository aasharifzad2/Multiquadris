#ifndef _board_h_
#define _board_h_


#include <vector>
#include <memory>
#include "block.h"
class Cell;
class Block;
class Display;
class Player;

class Board
{
    int numRows, numCols;
    Player *player;
    std::vector<std::shared_ptr<Block>> blocks;
    std::vector<std::vector<std::shared_ptr<Cell>>> cells;
    
    
    void fillBoard();
    void addEmptyRows(int = 1);
    
    
    public:
    Board(int numRows, int numCols, Player *);

    std::vector<std::vector<Cell *>> getCells() const;
    
    bool blockFits(std::shared_ptr<Block>);
    void addBlock(std::shared_ptr<Block>);
    void clearFilledRows();
    // Visitor Pattern : visit(Display)
    void display(Display &);
};


#endif
