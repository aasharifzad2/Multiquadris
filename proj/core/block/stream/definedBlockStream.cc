
#include <memory>
#include "definedBlockStream.h"
#include "../block.h"
#include "../../../excp/invalid_block_char.h"


DefinedBlockStream::DefinedBlockStream
(
    std::shared_ptr<std::ifstream> sequence
) :
    sequence(sequence)
{}

std::shared_ptr<Block> DefinedBlockStream::getBlock()
{
    char blockType;
    *sequence >> blockType;
    
    if (sequence->eof())
    {
        sequence->clear();
        sequence->seekg(0, sequence->beg);
        *sequence >> blockType;
    }
    
    return Block::makeBlock(blockType);
}
