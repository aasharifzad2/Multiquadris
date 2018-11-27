
#include <memory>
#include "definedBlockStream.h"
#include "../block.h"
#include "../../../excp/invalid_block_sequence.h"


DefinedBlockStream::DefinedBlockStream(std::ifstream &sequence) :
    sequence(sequence) {}

std::shared_ptr<Block> DefinedBlockStream::getBlock()
{
    if (sequence.eof())
    {
        sequence.clear();
        sequence.seekg(0, sequence.beg);
    }
    
    char blockType;
    sequence >> blockType;
    
    switch (blockType)
    {
        case 'I':
            return std::make_shared<IBlock>();
        case 'J':
            return std::make_shared<JBlock>();
        case 'L':
            return std::make_shared<LBlock>();
        case 'O':
            return std::make_shared<OBlock>();
        case 'S':
            return std::make_shared<SBlock>();
        case 'Z':
            return std::make_shared<ZBlock>();
        case 'T':
            return std::make_shared<TBlock>();
        default:
            throw invalid_block_sequence(blockType);
    }
}
