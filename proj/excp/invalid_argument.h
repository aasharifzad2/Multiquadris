#ifndef _invalid_argument_h_
#define _invalid_argument_h_


#include "base_exception.h"
#include <vector>
#include <string>


class invalid_arg : public base_exception
{
    std::string arg;
    std::vector<std::string> okValues;

public:
    invalid_arg(std::string, std::vector<std::string>);
    std::string message() const noexcept override;
};


#endif
