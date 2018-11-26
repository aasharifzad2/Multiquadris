
#include "iBlock.h"
#include "../../cell.h"


IBlock::~IBlock() {}

IBlock::IBlock() : Block(Colour::Cyan)
{
    for (int i = 0; i < 4; i++)
    {
        cells.emplace_back(std::make_shared<Cell>(
            initialY, initialX + i, this)
        );
    }
}
