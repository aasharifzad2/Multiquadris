
#include <memory>
#include "definedBlockStream.h"
#include "../block.h"
#include "../../../excp/invalid_block_sequence.h"


DefinedBlockStream::DefinedBlockStream(std::ifstream &sequence) :
    sequence(sequence) {}

std::unique_ptr<Block> DefinedBlockStream::getBlock()
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
            return std::unique_ptr<Block>(new IBlock());
        case 'J':
            return std::unique_ptr<Block>(new JBlock());
        case 'L':
            return std::unique_ptr<Block>(new LBlock());
        case 'O':
            return std::unique_ptr<Block>(new OBlock());
        case 'S':
            return std::unique_ptr<Block>(new SBlock());
        case 'Z':
            return std::unique_ptr<Block>(new ZBlock());
        case 'T':
            return std::unique_ptr<Block>(new TBlock());
        default:
            throw invalid_block_sequence(blockType);
    }
}
