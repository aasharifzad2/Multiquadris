#ifndef _invalid_block_placement_h_
#define _invalid_block_placement_h_

#include <string>
#include "base_exception.h"

class invalid_block_placement : public base_exception
{
public:
    std::string message() const noexcept override;
};

#endif
