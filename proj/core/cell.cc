
#include "cell.h"
#include <memory>
#include "../excp/not_implemented.h"
#include "../excp/no_parent_block.h"


void Cell::setWindow(Xwindow *window)
{
    throw not_implemented();
}

Cell::Cell(int row, int col, PlacedBlock *parent) :
    row(row), col(col), parent(parent), filled(parent)
{
    if (filled)
    {
        colour = parent->getColour();
    }
}

int Cell::getRow() const { return row; }
int Cell::getCol() const { return col; }
bool Cell::isEmpty() const { return !filled; }
bool Cell::isFilled() const { return filled; }

void Cell::setCol(int col) { this->col = col; }
void Cell::setRow(int row) { this->row = row; }

void Cell::setCoords(int row, int col)
{
    setRow(row);
    setCol(col);
}


void Cell::notifyCleared() const
{
    if (!parent) throw no_parent_block();

    parent->cellCleared(this);
}

void Cell::draw()
{
    throw not_implemented();
}
