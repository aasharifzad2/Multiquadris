
#include "row.h"


Row::Row(int rowNum, int numCells) : rowNum(rowNum)
{
    for (int i = 0; i < numCells; i++)
    {
        cells.emplace_back(std::make_shared<Cell>(Cell(rowNum, i, nullptr)));
    }
}

void Row::setRowNum(int rowNum)
{
    this->rowNum = rowNum;
}

const std::shared_ptr<Cell> Row::getCell(int index) const
{
    return cells.at(index);
}

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

void Row::clear()
{
    for (auto cell : cells)
    {
        cell->notifyCleared();
    }
}
