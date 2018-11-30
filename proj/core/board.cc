
#include "board.h"
#include <vector>
#include "cell.h"
#include "player.h"
#include "block/block.h"
#include "../display/display.h"
#include "../excp/invalid_block_placement.h"

Board::Board(int numRows, int numCols, Player *player) :
    player(player),
    numRows(numRows),
    numCols(numCols)
{
    fillBoard();
}


// Return a 2D vector of pointers to the cells
std::vector<std::vector<Cell *>> Board::getCells() const
{
    std::vector<std::vector<Cell *>> cellptrs;
    for (auto row : cells)
    {
        std::vector<Cell *> rowToAdd;
        for (auto cell : row)
        {
            rowToAdd.emplace_back(cell.get());
        }
        
        cellptrs.emplace_back(rowToAdd);
    }
    
    return cellptrs;
}

// Getter: numCols
int Board::getNumCols() const { return numCols; }


// Returns true if the block does not go off the side of the board or clip other cells
bool Board::blockFits(std::shared_ptr<Block> block)
{
    auto blockCells = block->getCells();
    for (auto cell : blockCells)
    {
        int row = cell->getRow();
        int col = cell->getCol();
        if
        (
            row < 0 ||
            col < 0 ||
            row >= numRows ||
            col >= numCols ||
            cells.at(row).at(col)->isFilled()
        )
        {
            return false;
        }
    }
    
    return true;
}


void Board::addBlock(std::shared_ptr<Block> block)
{
    // Ensure that the block fits before trying to add it
    if (!blockFits(block)) throw invalid_block_placement();
    
    for (auto cell : block->getCells())
    {
        cells[cell->getRow()][cell->getCol()] = cell;
    }
    
    // Add the whole block to the board
    blocks.emplace_back(block);
}


void Board::clearFilledRows()
{
    int numRowsCleared = 0;
    
    // Erase all of the filled rows
    for (auto row = cells.begin(); row != cells.end(); )
    {
        // Check if the row needs to be cleared
        bool rowIsFilled = true;
        for (auto cell : *row)
        {
            if (cell->isEmpty())
            {
                rowIsFilled = false;
                break;
            }
        }
        
        if (rowIsFilled)
        {
            for (auto cell : *row)
            {
                cell->notifyCleared();
            }
            
            row = cells.erase(row);
            ++numRowsCleared;
        }
        else
        {
            ++row;
        }
    }
    
    // Remove placed blocks that are all gone
    for (auto itr = blocks.begin(); itr != blocks.end(); )
    {
        if ((*itr)->getNumCells() == 0)
        {
            player->blockCleared((*itr)->getLevelGenerated());
            itr = blocks.erase(itr);
        }
        {
            ++itr;
        }
    }
    
    // Calculate points for rows cleared
    player->rowsCleared(numRowsCleared);
    
    fillBoard();
    
    // Reset the coords of the cells
    for (int rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        for (int colIndex = 0; colIndex < numCols; ++colIndex)
        {
            cells.at(rowIndex).at(colIndex)->setCoords(rowIndex, colIndex);
        }
    }
}


// Visitor Pattern : visit a display
void Board::display(Display &d)
{
    d.accept(this);
}


// Fills the 2D vector of cells with empty cells
void Board::fillBoard()
{
    while (numRows != cells.size())
    {
        int rowNum = numRows - (int)cells.size() - 1;
        std::vector<std::shared_ptr<Cell>> row;
        
        for (int i = 0; i < numCols; i++)
        {
            row.insert(row.end(), std::make_shared<Cell>(rowNum, i));
        }
        
        cells.insert(cells.begin(), row);
    }
}
