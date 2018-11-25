#ifndef _no_parent_block_h_
#define _no_parent_block_h_


#include <string>
#include "base_exception.h"

class no_parent_block : base_exception
{
    public:
    std::string message() const noexcept override;
};


#endif
