
#include <string>
#include "base_exception.h"
#include "not_implemented.h"


not_implemented::not_implemented() {}

std::string not_implemented::message() const noexcept
{
    return "member not yet implented";
}
