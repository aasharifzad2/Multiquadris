
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
void Row::setCell(Cell *cellptr)
{
    setCell(cellptr->getCol(), cellptr);
}

// Setter : cell at index
void Row::setCell(int index, Cell *cellptr)
{
    std::shared_ptr<Cell> shrd{cellptr};
    cells[index].swap(shrd);
}

// Getter : cell at index
Cell const * Row::getCell(int index) const
{
    return cells.at(index).get();
}

// Getter : cells
std::vector<const Cell *> Row::getCells() const
{
    std::vector<const Cell *> cellptrs;
    for (auto cell : cells)
    {
        cellptrs.push_back(cell.get());
    }
    return cellptrs;
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
