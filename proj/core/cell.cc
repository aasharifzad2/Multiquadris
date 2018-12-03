
#include "cell.h"
#include <memory>
#include "block/block.h"
#include "colour.h"
#include "../excp/not_implemented.h"
#include "../excp/no_parent_block.h"
#include "../display/display.h"


// MARK: Static


// MARK: Constructors and Destructor
Cell::Cell(int row, int col, Block *parent) :
    parent(parent),
    filled(parent),
    row(row),
    col(col)
{}


// MARK: - Setters
void Cell::setCol(int col) { this->col = col; }
void Cell::setRow(int row) { this->row = row; }

void Cell::setCoords(int row, int col)
{
    setRow(row);
    setCol(col);
}


// MARK: - Getters
int Cell::getRow() const { return row; }
int Cell::getCol() const { return col; }
bool Cell::isEmpty() const { return !filled; }
bool Cell::isFilled() const { return filled; }

bool Cell::isInBlindZone() const
{
    return (col >= 2 && col <= 8 && row >= 2 && row <= 11);
}

char Cell::getSymbol() const
{
    return parent ? parent->getSymbol() : ' ';
}

Colour Cell::getColour() const
{
    return parent ? parent->getColour() : Colour::Black;
}


// MARK: - Public Functions
void Cell::notifyCleared() const
{
    parent->cellCleared(this);
}

void Cell::display(Display &d)
{
    d.accept(this);
}


// MARK: - Private Functions
