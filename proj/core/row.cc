
#include "row.h"
#include <memory>
#include "cell.h"
#include "../display/display.h"


Row::Row(int rowNum, int numCells) : rowNum(rowNum)
{
    for (int i = 0; i < numCells; i++)
    {
        cells.emplace_back(std::make_shared<Cell>(Cell(rowNum, i)));
    }
}

// Setter : row field for all cells
void Row::setRowNum(int rowNum)
{
    this->rowNum = rowNum;
}

// Setter : cell at cell coordinate
void Row::setCell(std::shared_ptr<Cell> cell)
{
    setCell(cell->getCol(), cell);
}

// Setter : cell at index
void Row::setCell(int index, std::shared_ptr<Cell> cell)
{
    cells[index] = cell;
}

// Getter : cell at index
std::shared_ptr<Cell> Row::getCell(int index) const
{
    return cells.at(index);
}

// Getter : cells
std::vector<std::shared_ptr<Cell>> Row::getCells() const
{
    return cells;
}

// Returns true if all of the cells in the row are 'filled'
bool Row::isFilled()
{
    bool filled = true;
    for (auto cell : cells)
    {
        if (cell->isEmpty())
        {
            filled = false;
            break;
        }
    }
    
    return filled;
}

// Notifies the block in the row that they're cells are about to be cleared
void Row::clear()
{
    for (auto cell : cells)
    {
        cell->notifyCleared();
    }
}

// Visitor Pattern : visit a display
void Row::display(Display &d)
{
    d.accept(this);
}
