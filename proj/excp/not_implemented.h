
#ifndef _invalid_command_h_
#define _invalid_command_h_

#include <vector>
#include <string>
#include "base_exception.h"

class not_implemented : base_exception
{
    
    public:
    not_implemented();
    std::string message() const noexcept override;
};

#endif
