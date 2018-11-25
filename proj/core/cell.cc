
#include "cell.h"
#include <memory>
#include "block/block.h"
#include "colour.h"
#include "../excp/not_implemented.h"
#include "../excp/no_parent_block.h"


void Cell::setWindow(Xwindow *window)
{
    throw not_implemented();
}

// Constructor
Cell::Cell(int row, int col, Block *parent) :
    parent(parent),
    filled(parent),
    row(row),
    col(col)
{
    colour = parent ? parent->getColour() : Colour::Black;
}

// Getter functions
int Cell::getRow() const { return row; }
int Cell::getCol() const { return col; }
bool Cell::isEmpty() const { return !filled; }
bool Cell::isFilled() const { return filled; }

// Setter functions
void Cell::setCol(int col) { this->col = col; }
void Cell::setRow(int row) { this->row = row; }

void Cell::setCoords(int row, int col)
{
    setRow(row);
    setCol(col);
}

// Observer Pattern : Subject (Cell) notifying observer (Block) that one of
//   the block's cells has been cleared
void Cell::notifyCleared() const
{
    parent->cellCleared(this);
}
