
#include "board.h"
#include "row.h"
#include "cell.h"
#include "block/block.h"
#include "../excp/invalid_block_placement.h"

std::vector<Block> blocks;
std::vector<Row> rows;

Board::Board(int numRows, int numCols) : numRows(numRows), numCols(numCols)
{
    addEmptyRows(numRows);
}

bool Board::blockFits(Block *block)
{
    auto cells = block->getCells();
    for (auto cell : cells)
    {
        int row = cell->getRow();
        int col = cell->getCol();
        if
        (
            row < 0 ||
            col < 0 ||
            row >= numRows ||
            col >= numCols ||
            cellAt(row, col)->isFilled()
        )
        {
            return false;
        }
    }
    
    return true;
}

void Board::addBlock(Block block)
{
    // Ensure that the block fits before trying to add it
    if (!blockFits(&block)) throw invalid_block_placement();
    
    for (auto cell : block.getCells())
    {
        // Set the cell in the board to the one in the block
        Row cellRow = rows.at(cell->getRow());
        *cellRow.getCell(cell->getCol()) = *cell;
    }
}


void Board::clearFilledRows()
{
    // Erase filled rows
    for (auto row = rows.begin(); row != rows.end(); )
    {
        if (row->isFilled())
        {
            row->clear();
            row = rows.erase(row);
        }
        else
        {
            ++row;
        }
    }
    
    // Add rows at the top to replace the one's we removed
    addEmptyRows(numRows - (int)rows.size());
    
    // Change the coords of the cells in the shifted rows
    for (int i = 0; i < rows.size(); i++)
    {
        rows[i].setRowNum(i);
    }
    
    // Remove placed blocks that are all gone
    for (auto itr = blocks.begin(); itr != blocks.end(); )
    {
        if (itr->numCells() == 0)
        {
            itr = blocks.erase(itr);
        }
        {
            ++itr;
        }
    }
}

const std::shared_ptr<Cell> Board::cellAt(int row, int col) const
{
    return rows.at(row).getCell(col);
}

void Board::addEmptyRows(int numToAdd)
{
    for (int rowNum = numToAdd-1; rowNum >= 0; rowNum--)
    {
        rows.insert(rows.begin(), Row(rowNum, numCols));
    }
}
