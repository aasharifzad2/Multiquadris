
#include "board.h"
#include "cell.h"
#include "row.h"
#include "block/fallingBlock.h"
#include "../excp/invalid_block_placement.h"

std::vector<PlacedBlock> blocks;
std::vector<Row> rows;

Board::Board(int numRows, int numCols) : numRows(numRows), numCols(numCols)
{
    addEmptyRows(numRows);
}

bool Board::blockFits(Block *block)
{
    auto cellCoords = block->getCellCoords();
    for (auto coord : cellCoords)
    {
        int cellRow = coord.first;
        int cellCol = coord.second;
        if
        (
            cellRow < 0 ||
            cellCol < 0 ||
            cellRow >= numRows ||
            cellCol >= numCols ||
            cellAt(cellRow, cellCol)->isFilled()
        )
        {
            return false;
        }
    }
    
    return true;
}

void Board::addBlock(PlacedBlock block)
{
    // Ensure that the block fits before trying to add it
    if (!blockFits(&block)) throw invalid_block_placement();
    
    for (auto cell : block.getCells())
    {
        // Set the cell in the board to the one in the block
        *rows.at(cell->getRow()).getCell(cell->getRow()) = *cell;
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
