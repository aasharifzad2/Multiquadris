#ifndef _not_implemented_h_
#define _not_implemented_h_


#include <string>
#include "base_exception.h"

class not_implemented : public base_exception
{
public:
    std::string message() const noexcept override;
};


#endif
