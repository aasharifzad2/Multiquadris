
#include <memory>
#include "definedBlockStream.h"
#include "../fallingBlock.h"
#include "../../../excp/invalid_block_sequence.h"


DefinedBlockStream::DefinedBlockStream(std::ifstream &sequence) :
    sequence(sequence) {}

std::unique_ptr<FallingBlock> DefinedBlockStream::getBlock()
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
            return std::unique_ptr<FallingBlock>(new IBlock());
        case 'J':
            return std::unique_ptr<FallingBlock>(new JBlock());
        case 'L':
            return std::unique_ptr<FallingBlock>(new LBlock());
        case 'O':
            return std::unique_ptr<FallingBlock>(new OBlock());
        case 'S':
            return std::unique_ptr<FallingBlock>(new SBlock());
        case 'Z':
            return std::unique_ptr<FallingBlock>(new ZBlock());
        case 'T':
            return std::unique_ptr<FallingBlock>(new TBlock());
        default:
            throw invalid_block_sequence(blockType);
    }
}
