
#include "oneByOneBlock.h"
#include "../../cell.h"


OneByOneBlock::~OneByOneBlock() {}

OneByOneBlock::OneByOneBlock(int row, int col) :
    Block('*', Colour::Brown)
{
    cells.emplace_back(std::make_shared<Cell>(row, col, this));
}
