
#include "no_parent_block.h"


std::string no_parent_block::message() const noexcept
{
    return "This cell does not have a parent";
}

