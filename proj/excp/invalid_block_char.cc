
#include "invalid_block_char.h"

invalid_block_char::invalid_block_char(char c) :
    invalidCharacter(c) {}

std::string invalid_block_char::message() const noexcept
{
    return "Sequence of blocks invalid: character '" + std::string(1, invalidCharacter) +"' invalid";
}
