
#include "placedBlock.h"
#include "../../excp/not_implemented.h"


PlacedBlock::~PlacedBlock() {}

int PlacedBlock::numCells() const
{
    return (int)cells.size();
}

void PlacedBlock::cellCleared(const Cell *cellptr)
{
    for (auto itr = cells.begin(); itr != cells.end(); )
    {
        // &**itr is the address to the cell
        if (itr->get() == cellptr)
        {
            itr = cells.erase(itr);
        }
        else
        {
            ++itr;
        }
    }
}
