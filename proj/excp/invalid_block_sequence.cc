
#include "invalid_block_sequence.h"

invalid_block_sequence::invalid_block_sequence(char c) :
    invalidCharacter(c) {}

std::string invalid_block_sequence::message() const noexcept
{
    return "Sequence of blocks invalid: character '" + std::to_string(invalidCharacter) +"' invalid";
}
