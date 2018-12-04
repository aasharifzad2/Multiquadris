#include "invalid_argument.h"


invalid_arg::invalid_arg
(
    std::string arg,
    std::vector<std::string> okValues
) :
    arg(arg),
    okValues(okValues)
{}



std::string invalid_arg::message() const noexcept
{
    std::string message =
        "Argument '" + arg + "' is invalid. Try: \n";
    
    for (auto value : okValues)
    {
        message += "\n" + value;
    }
    
    return message;
}
