#ifndef _invalid_command_h_
#define _invalid_command_h_


#include <string>
#include "base_exception.h"

class not_implemented : base_exception
{
    public:
    std::string message() const noexcept override;
};


#endif