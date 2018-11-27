#ifndef _board_h_
#define _board_h_


#include <vector>
#include <memory>
#include "row.h"
#include "block.h"
class Cell;
class Block;

class Board
{
    int numRows, numCols;
    std::vector<Block> blocks;
    std::vector<Row> rows;
    
    void addEmptyRows(int = 1);
    std::shared_ptr<Cell> getCell(int row, int col) const;
    
    public:
    Board(int numRows, int numCols);
    
    std::vector<const Row *> getRows() const;

    bool blockFits(std::shared_ptr<Block>);
    void addBlock(std::shared_ptr<Block>);
    void clearFilledRows();
    // Visitor Pattern : visit(Display)
    void display(Display &);
};


#endif
