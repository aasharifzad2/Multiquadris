
#include "cell.h"
#include "../excp/not_implemented.h"


Cell::Cell(int x, int y, PlacedBlock *parent) :
    x(x), y(y), parent(parent) {}

void Cell::setWindow(Xwindow *window)
{
    throw not_implemented();
}

bool Cell::isEmpty()
{
    throw not_implemented();
}

bool Cell::isFilled()
{
    throw not_implemented();
}

void Cell::notifyCleared()
{
    throw not_implemented();
}

void Cell::draw()
{
    throw not_implemented();
}
