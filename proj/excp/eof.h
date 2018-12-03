#ifndef _eof_h_
#define _eof_h_


#include "base_exception.h"
#include <string>


class eof : public base_exception
{
public:
    std::string message() const noexcept override;
};


#endif
