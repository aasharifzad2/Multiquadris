
#ifndef _base_exception_h_
#define _base_exception_h_

#include <string>


class base_exception
{
    virtual std::string message() const noexcept = 0;
};

#endif
