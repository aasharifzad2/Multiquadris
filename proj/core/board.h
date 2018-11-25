#ifndef _board_h_
#define _board_h_


#include <vector>
#include <memory>
#include "row.h"
#include "block/placedBlock.h"
class Cell;
class FallingBlock;

class Board
{
    int numRows, numCols;
    std::vector<PlacedBlock> blocks;
    std::vector<Row> rows;
    
    void addEmptyRows(int = 1);
    //TODO: lookup what a 'const shared_ptr' means
    const std::shared_ptr<Cell> cellAt(int row, int col) const;
    
    public:
    Board(int numRows, int numCols);
    bool blockFits(Block *);
    void addBlock(PlacedBlock);
    void clearFilledRows();
};


#endif
