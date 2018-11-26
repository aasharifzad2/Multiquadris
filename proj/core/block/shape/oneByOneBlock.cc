
#include "oneByOneBlock.h"
#include "../../cell.h"


OneByOneBlock::~OneByOneBlock() {}

OneByOneBlock::OneByOneBlock(int x, int y) :
    Block('*', Colour::Brown)
{
    cells.emplace_back(std::make_shared<Cell>(y, x, this));
}
